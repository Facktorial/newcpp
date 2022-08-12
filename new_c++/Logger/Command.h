template <typename Handler, typename Object>
struct Command
{
	virtual ~Command();
	virtual void execute(const Handler& h, const Object& obj) = 0;	
	//virtual void execute() = 0;	
};

