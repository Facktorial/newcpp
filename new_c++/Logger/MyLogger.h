#pragma once
#include <string>
#include <variant>
#include <vector>
#include <queue>
#include <tuple>
#include "MyPrintf.h"


template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;


enum class LogType
{
	FileLoaded,
	ObjectGenerated,
	Message,
	StageChanged,
	Error,
	Basic
};


// there is #include <source_location> in C++20.... RIP
struct Location
{
	Location() : empty(true) {}
	Location(std::string name, int l, int col, std::string fn)
		: file_name(name), line(l), column(col), func_name(fn), empty(false)
	{}

	std::string file_name;
	int line;
	int column;
	std::string func_name;
	bool empty;

	// create string to be extended to use as format for myPrintf
	std::string to_string() const
	{
		if (empty) { return "@ @"; }  // FIXME
		return "@" + file_name + "(" + std::to_string(line) + ":" + std::to_string(column) + ") `" + func_name + "`:@";
	}
};


struct Message
{
	Message(std::string msg, Location l) : message(msg), location(l) {}

	std::string message;
	Location location;
};


struct Data 
{
	Data(std::string mess, std::vector<std::string> vec, Location l) : message(mess), data(vec), location(l) {}

	std::string message;
	std::vector<std::string> data;
	Location location;
};


using Log_variant = std::variant<Message, Data>;
using ColorsSetting = std::tuple<std::string, std::string, std::string>;

static ColorsSetting pick_colors(LogType t)
{
	std::string col1, col2, bg;

	switch (t)
	{
		case LogType::FileLoaded:		{ col1 = "cyan2"; col2 = "cyan1"; bg = ""; break; }
		case LogType::ObjectGenerated:	{ col1 = "blue"; col2 = "cyan1"; bg = ""; break; }
		case LogType::Message:			{ col1 = "white"; col2 = ""; bg = ""; break; }
		case LogType::StageChanged:		{ col1 = "green"; col2 = ""; bg = ""; break; }
		case LogType::Error:			{ col1 = "red"; col2 = "yellow"; bg = "_red"; break; }
		case LogType::Basic:			{ col1 = "white"; col2 = ""; bg = "_black"; break; }
	}

	return std::make_tuple(col1, col2, bg);
}


struct MyLogger
{
	void begin(std::string msg) const
	{
		std::cout <<
			"------------------------------------------------------------------------------------------\n\n\n" << 
			msg <<
			"\n\n\n------------------------------------------------------------------------------------------\n\n\n"; 
	}

	void begin() const
	{
		std::cout <<
			"------------------------------------------------------------------------------------------\n\n\n" << 
			"Welcome to my ??? playground.`\n\n\n"
			"------------------------------------------------------------------------------------------\n\n\n"; 

		//Message msg { "This is stage_change_log!", Location(__FILE__, __LINE__, 69, __FUNCTION__)  };
		//log(LogType::StageChanged, msg);
		//Message msg2 { "This is creation_log!", Location(__FILE__, __LINE__, 69, __FUNCTION__)  };
		//log(LogType::ObjectGenerated, msg2);
		//Message msg3 { "This is msg_log!", Location(__FILE__, __LINE__, 69, __FUNCTION__)  };
		//log(LogType::Message, msg3);
		//Message msg4 { "This is file_load_log!", Location(__FILE__, __LINE__, 69, __FUNCTION__)  };
		//log(LogType::FileLoaded, msg4);
		//Message msg5 { "This is error_log!", Location(__FILE__, __LINE__, 69, __FUNCTION__)  };
		//log(LogType::Error, msg5);
		//puts("\n\n");
	}

	void log(LogType type, Log_variant vis) const
	{
		auto [prim, second, bg] = pick_colors(type);	

		std::visit(overloaded {
				[prim_color=prim, secondary_color=second, bg_color=bg](const Message& msg) {
					myPrintf(
						msg.location.to_string() + " @%\n",
						{ std::string(secondary_color + bg_color).c_str(), "_", prim_color.c_str() },
						msg.message.c_str()
					);		
				},
				[prim_color=prim, secondary_color=second, bg_color=bg](const Data& data) {
					myPrintf(
						data.location.to_string() + " @%\n",
						{ std::string(secondary_color + bg_color).c_str(), "_", prim_color.c_str() },
						data.message.c_str()
					);

					for (auto token : data.data) { myPrintf("\t@%\n", { secondary_color.c_str() }, token.c_str()); }
				},
		}, vis);
	}
};

