#include "log.h"
#include <iostream>
#include <map>


namespace sylar{

const char* LogLevel::ToString(LogLevel::Level level){
	switch(level){
#define XX(name) \
	case LogLevel::name: \
		return #name; \
		break;
	
	XX(DEBUG);
	XX(INFO);
	XX(WARN);
	XX(ERROR);
	XX(FATAL);
#define XX
	default:
		return "UNKNOW";
	}
	return "UNKNOW";
}

class MessageFormatItem : public LogFormatter::FormatItem{
public:
	MessageFormatItem(const std::string& str = ""){}
	void format(std::ostream& os, Loggor::ptr loggor, LogLevel::Level level, LogEvent::ptr event) override{
		os << event->getCOntent();
	}
};

class LevelFormatItem : public LogFormatter::FormatItem{
public:
	LevelFormatItem(const std::string& str = ""){}
	void format(std::ostream& os, Loggor::ptr loggor, LogLevel::Level level, LogEvent::ptr event) override{
		os << LogLevel::ToString(level);
	}
};

class ElasxpseFormatItem : public LogFormatter::FormatItem{
public:
	ElasxpseFormatItem(const std::string& str = ""){}
	void format(std::ostream& os, Loggor::ptr loggor, LogLevel::Level level, LogEvent::ptr event) override{
		os << event->getElapse();
	}
};

class NameFormatItem : public LogFormatter::FormatItem{
public:
	NameFormatItem(const std::string& str = ""){}
	void format(std::ostream& os, Loggor::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
		os << logger->getName();
	}
};

class ThreadFormatItem : public LogFormatter::FormatItem{
public:
	ThreadFormatItem(const std::string& str = ""){}
	void format(std::ostream& os, Loggor::ptr loggor, LogLevel::Level level, LogEvent::ptr event) override{
		os << event->getThreadId();
	}
};

class FiberFormatItem : public LogFormatter::FormatItem{
public:
	FiberFormatItem(const std::string& str = ""){}
	void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event)	override{
		os << event->getFiberId();
	}
}

class DateFormatItem : public LogFormatter::FormatItem{
public:
	DateFormatItem(const std::string& format = "%Y:%m:%d %H:%M:%s")
		:m_format(format){	
	}

	void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event)	override{
		os << event-getTime();
	}
private:
	std::string m_format;	
}

class FilenameFormatItem : public LogFormatter::FormatItem{
public:
	FilenameFormatItem(const std::string& str = ""){}
	void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event)	override{
		os << event->getFile();
	}
}

class LineFormatItem : public LogFormatter::FormatItem{
public:
	LineFormatItem(const std::string& str = ""){}
	void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event)	override{
		os << event->getFile();
	}
}

class NewlineFormatItem : public LogFormatter::FormatItem{
public:
	NewlineFormatItem(const std::string& str = ""){}
	void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event)	override{
		os << std::endl;
	}
};























class StringFormatItem : public LogFormatter::FormatItem{
public:
	StringFormatItem(const std::string& str = ""){}
	void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event)	override{
		os << m_string;
	}
private:
	std::string m_string;
}
Logger::Logger(const std::string& name):m_name(name){

	

void Logger::delAppender(LogAppender::ptr appender){
	for(auto it = m_appenders.begin();
			it != m_appenders.end();
			it++){
		if(*it == appender){
			m_appenders.erase(it);
			break;
		}
	}
}

void Logger::log(LogLevel::Level level, LogEvent::ptr event){
	if(level >= m_level){
		auto self = shared_from_this();
		for(auto& i : m_appenders){
			i->log(self, level, event);
		}
	}
}	

void Logger::debug(Logger::Level level, LogEvent::ptr event){
	log(LogLevel::DEBUG, event);

}
void Logger::info(Logger::Level level, LogEvent::ptr event){
	log(LogLevel::INFO, event); 
}
void Logger::warn(Logger::Level level, LogEvent::ptr event){
	log(LogLevel::WARN, event);
}
void Logger::error(Logger::Level level, LogEvent::ptr event){
	log(LogLevel::ERROR, event);
}
void Logger::fatal(Logger::Level level, LogEvent::ptr event){
	log(LogLevel::FATAL, event);
}
	
FileLogApperder::FileLogApperder(const std::string& filename){

}

void FileLogApperder::log(LogLevel::Level level, LogEvent::ptr event){
	if(level >= m_level){
		m_filename << m_formatter->format(logger, level, event);
	}
}

bool FileLogAppernder::reopen(){
	if(m_filename){
		m_filestream.close();
	}	
	m_filestream.open(m_filename);
	return !!m_filestream;
}

void StdoutLogAppender::log(LogLevel::Level level, LogEvent::ptr event){
	if(level >= m_level){
		std::cout << m_formatter.format(event);
	}	
}

void Logger::log(LogLevel::Level level, LogEvent::ptr event){
	if(level >= m_level){
		auto self = shared_from_this();
		for(auto& i : m_appenders){
			i->log(self, level, event);
		}
	}
}

















LogFormatter::LogFormatter(const std::string& pattern):m_pattern(pattern){
	init();
}

std::string LogFormatter::format(std::shared_ptr<Logger> loggor, LogEvent::ptr event){
	std stringstream ss;
	for(auto& i : m_items){
		i->format(ss, event);
	}	
	return ss.str();
}

void LogFormatter::init(){
	std::vector<std::tuple<std::string, std::string, int>> vec;
	std::string nstr;
	for(size_t i = 0; i < m_pattern.size(); i++){
		if(m_pattern[i] != '%'){
			nstr.append(1, m_pattern[i]);
			continue;	
		}

		if((i + 1) < m_pattern.size()){
			if(m_patternp[i+1] == '%'){
				nstr.append(1, '%');
				continue;
			}
		}
	

		size_t n = i+1;
		int fmt_status = 0;
		size_t fmt_begin= 0;

		std::string str;
		std::string fmt;
		while(n < m_pattern.size()){
			if(!isalpha(m_pattern[n] != '}'){
				str = m_pattern.substr(i+1, n-i-1);
				fmt_status = 1; 	//解析格式
				fmt_begin++;
				++n;
				vontinue;
			}	
		}
		if(fmt_status == 1){
			if(m_pattern[n] == '}'){
				fmt = m_pattern.substr(fmt_begin + 1, n - fmt_begin - 1);
				fmt_status = 2;
				break;
			}
		}
		++n;		
	}	
}






























































	static std::map<std::string, std::function<FormatItem::ptr(const std::string& str)>> s_format_items = {
#define XX(str, C) \
		(#str, [](const std::string& fmt){ return FormatItem::ptr(new C(fmt));})
		
		XX(m, MessageFormatItem),
		XX(p, LevelFormatItem),
		XX(r, ElasxpseFormatItem),
		XX(c, NameFormatItem),
		XX(t, ThreadFormatItem),
		XX(n, NewlineFormatItem),
		XX(d, DateTimeFormatItem),
		XX(l, LineFormatItem),
#undef XX
	};
	
	for(auto& i :vsc){
		if(std::get<2>(i) == 0){
			m_items.push_back(FormatItem::ptr(new StringFormatItem(std::get<0>(i))));	else{
			auto it = s_format_items.find(std::get<0>(i));
			if(it == s_format_items.end()){
				m_items.push_back(FormatItem::ptr(new StringFormatItem("<<error_format %" + std::get<0>(i) + ">>")));
			}else{
				m_items.push_back(it->second(std::get<1>(i)));
			}
		}
		
	std::cout << std::get<0>(i) << " - " << std::get<1>(i) << " - " << std::get<2>(i) << std::endl;
	}
)

























