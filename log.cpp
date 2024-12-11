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

LogFormatter::LogFormatter(const std::string& pattern):m_pattern(pattern){

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
			
		}
	}


	
}
