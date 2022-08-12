#pragma once
#include "MyLogger.h"
#include "Command.h"


struct LoggerHandler
{
	LoggerHandler() : m_logger( MyLogger() ) {}

	void fire_log_file_loaded(const Log_variant& obj) const { m_logger.log(LogType::FileLoaded, obj); }
	void fire_log_obj_created(const Log_variant& obj) const { m_logger.log(LogType::ObjectGenerated, obj); }
	void fire_log_frendly_msg(const Log_variant& obj) const { m_logger.log(LogType::Message, obj); }
	void fire_log_stagechange(const Log_variant& obj) const { m_logger.log(LogType::StageChanged, obj); }
	void fire_log_error		 (const Log_variant& obj) const { m_logger.log(LogType::Error, obj); }

	void begin(std::string msg) const { m_logger.begin(msg); }
	void begin() const { m_logger.begin(); }

private:
	const MyLogger m_logger;
};


using Command_var = Command<LoggerHandler, Log_variant>;
template<> Command_var::~Command() {}


struct FireMsgLog : public Command_var
{
	void execute(const LoggerHandler& handler, const Log_variant& obj) override { handler.fire_log_frendly_msg(obj); }
};


struct FireStageChangeLog : public Command_var
{
	void execute(const LoggerHandler& handler, const Log_variant& obj) override { handler.fire_log_stagechange(obj); }
};


struct FireFileLoadedLog : public Command_var
{
	void execute(const LoggerHandler& handler, const Log_variant& obj) override { handler.fire_log_file_loaded(obj); }
};


struct FireObjectCreatedLog : public Command_var
{
	void execute(const LoggerHandler& handler, const Log_variant& obj) override { handler.fire_log_obj_created(obj); }
};

struct FireErrorLog : public Command_var
{
	void execute(const LoggerHandler& handler, const Log_variant& obj) override { handler.fire_log_error(obj); }
};

