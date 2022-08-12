#include <initializer_list>
#include <iostream>
#include <queue>
#include <string>


static void handleColors(std::queue<const char*>* s)
{
    if (!s->empty())
    {
        auto c = s->front();
        std::string token = "";
        std::string token2 = "";
        bool fg = true;
        size_t i = 0;

        for ( ; c[i] != '\0'; i++)
        {
            if (c[i] == '_') { fg = false; continue; }
            if (fg) token += c[i];
            else token2 += c[i];
        }

        if      (token == "yellow") std::cout << "\x1B[93m";
        else if (token == "red") std::cout << "\x1B[31m";
        else if (token == "green") std::cout << "\x1B[92m";
        else if (token == "blue") std::cout << "\x1B[94m";
        else if (token == "grey") std::cout << "\x1B[90m";
        else if (token == "magenta1") std::cout << "\x1B[35m";
        else if (token == "cyan1") std::cout << "\x1B[36m";
        else if (token == "magenta2") std::cout << "\x1B[95m";
        else if (token == "cyan2") std::cout << "\x1B[96m";
        else if (token == "white") std::cout << "\x1B[97m";
        else std::cout << "\033[37m";

        if (!fg)
        {
            if      (token2 == "yellow") std::cout << "\x1B[43m";
            else if (token2 == "red") std::cout << "\x1B[41m";
            else if (token2 == "green") std::cout << "\x1B[102m";
            else if (token2 == "blue") std::cout << "\x1B[104m";
            else if (token2 == "grey") std::cout << "\x1B[100m";
            else if (token2 == "magenta1") std::cout << "\x1B[45m";
            else if (token2 == "cyan1") std::cout << "\x1B[46m";
            else if (token2 == "magenta2") std::cout << "\x1B[105m";
            else if (token2 == "cyan2") std::cout << "\x1B[106m";
            else if (token2 == "white") std::cout << "\x1B[107m";
            else std::cout << "\033[0m";
        }

        s->pop();
    }
    else std::cout << "\033[0m";
}


//exhausive template
static void myPrintf(const char* format, std::queue<const char*> s)
{
    if (s.empty())
        std::cout << "\033[0m";
    std::cout << format << "\033[37m";
}


//core template
template<typename T, typename ... Args>
void myPrintf(const char* format, std::queue<const char*> s, T value, Args ... args)
{
    for ( ; *format != '\0'; format++ )
    {            
        if ( *format == '@' )
        {
            handleColors(&s);
            format++;
        }
        if ( *format == '%' )
        { 
            std::cout << value;
            myPrintf(format + 1, s, args ... );
            return;
        }
        std::cout << *format;
    }
}


//driver template
template <typename T, typename... Args>
void myPrintf(const char* format, std::initializer_list<const char*> list, T value, Args... args)
{
    myPrintf(format, std::queue<const char*>(list), value, args ...);
    std::cout << "\033[37m";
}


// captain Rework was lazy
template <typename T, typename... Args>
void myPrintf(std::string format, std::initializer_list<const char*> list, T value, Args... args)
{
    myPrintf(format.c_str(), std::queue<const char*>(list), value, args ...);
    std::cout << "\033[37m";
}

// int main(void)
// {
//     int p = 123;
//     int x0 = 555;
//     int x1 = 4324;
// 
//     myPrintf("@%:@ @%:@ % to %\n", {"y_grey", "_", "y", "grey"}, __FUNCTION__, p, x0, x1);
//     myPrintf("@-----@\n", {"y_grey", "_"}, "");
//     myPrintf("@smth driver:@ % @%: %\n", {"y_g", "_", "y_g"}, p, p, p);
//     myPrintf("@%:@ % @%:@ % to %\n", {"y_g", "_", "y", "grey"}, __FUNCTION__, p, p, x0, x1);
//     myPrintf("@-----@\n", {"y_r", "_"}, "");
//     myPrintf("%test% -> %: %\t%, %, @% \n", {"g", "grey", "y", "_r", "_", "g", "y_r"}, "", "", "p:", p, 3*p, x0, 3.14);
//     myPrintf("@test:@ %\n", {"g_y"}, 0);
//     myPrintf("@test:@ %\n", {"g_r"}, 2);
//     myPrintf("@test:@ % @%: %\n", {"y_r", "_", "g"}, 0, p, 12345);
//     myPrintf("@%:@ % @%:@ % to %\n", {"y_r", "_", "y", "grey"}, __FUNCTION__, p, 3.15, x0, x1);        
//     myPrintf("@-----@\n", {"y_r", "_"}, "");
// 
//     return 0;
// }

