#ifndef __SYLAR__LOG_H
#define __SYLAR__LOG_H

#include <list>
#include <string>
#include <stdint.h>
#include <memory>
#include <stringsteam>
#include <fstream>

namesapce sylar{

// 日志事件
class LogEvent{
	typedef std::shared_ptr<LogEvent> ptr;
	LogEvent();
private:
	const char* m_file = nullptr;	// 文件名
	int32_t m_line = 0;				// 行号
	uint32_t m_eplase = 0;			// 从程序执行到现在有多少毫秒
	uint32_t m_thread_Id = 0;		// 线程id
	uint32_t m_fiberId = 0;			// 携程id
	uint64_t m_time = 0;			// 时间戳
	std::string m_content;
};

// 日志级别
class LogLevel{
public:
	enum Level{
		DEBUG = 1,
		INFO = 2,
		WARN = 3,
		ERROR = 4,
		FATAL = 5
	};
};

// 日志格式器
class LogFormatter{
public:
	typedef std::shared_ptr<LogFormatter> ptr;
	std::string format(LogEvent::ptr event);
	LogFormatter(const std::string& pattern);
private:
	class FormatItem(){
	public:
		virtual ~FormatItem() {}
		virtual std::string format(LogEvent::ptr event) = 0;
	};
private:
}

// 日志输出地
class LogAppender{
public:
	typedef std::shared_ptr<LogAppender> ptr;
	virtual ~LogAppender(){}
	virtual void log(LogLevel::Level level, LogEvent::ptr event) = 0;
private:
	LogLevel::Level m_level;
}

// 日志器
class Logger{
public:
	typedef std::shared_ptr<Logger> ptr;
	Logger(const std::string& name = "root");
	void log(LogLevel::Level level, LogEvent::ptr event);

	void debug(LogEvent:ptr event);
	void info(LogEvent:ptr event);
	void warn(LogEvent::ptr event);
	void error(LogEvent::ptr event);
	void fatal(LogEvent::ptr event);
	
	void addAppender(LogAppender::ptr appender);
	void delAppender(LogAppender::ptr appender);
	LogLevel::Level getLevel() const {return m_level;}
	void setLevel(LogLevel::Level val){m_level = val;}
private:
	std::string m_name;							// 日志名称
	LogLevel::Level m_level;					// 日志级别
	std::list<LogAppender::ptr> m_appenders;	// Appender集合			
}

// 输出到控制台的 Appender
class StdoutLogAppender : public LogAppender{
public:
	typedef std::shared_ptr<StdoutLogAppender> ptr;
 	void log(Logger::ptr logger, LogLevel::Level level , LogEvent::ptr event) override;
};

// 定义输出到文件的Appender
class FileLogApperder : public LogAppender{
public:
	typedef std::shared_ptr<FileLogApperder> ptr;
	FileLogApperder(const std::string& filename);
	void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;

	// 重新打开文件，文件代开成功返回true
	bool reopen();

private:
	std::string m_filename;
	std::ofstream m_filestream;
};


}

#endif 
