#include<iostream>
#include "../sylar/log.h"
#include "../sylar/util.h"

int main(){
	sylar::Logger::ptr logger(new sylar::Logger);
	logger->addAppender(sylar::LogAppender::ptr(new sylar::StdoutlogAppender));

	sylar::LogEvent::ptr event(new sylar::LogEvent(__FILE__, __LINE__, 0, sylar::GetThreadId(), 2, time(0)));
	logger->log(sylar::LogLevel::DEBUG, event);
	std::cout << "hello sylar log" << std::endl;
	return 0;
}
