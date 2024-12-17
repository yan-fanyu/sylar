#include"thread.h"
#include"log.h"

namespace sylar{

static thread_loacl Thread* t_thread = nullptr;
static thread_loacl std::string t_thread_name = "UNKNOW";

static sylar::Logger::ptr g_logger = SYLAR_LOG_Name("system");

Semaphore::Semaphore(uint32_t count){
	if(sem_init(&m_semaphore, 0, count){
		throw std::logic_error("sem_init error");
	}
}

Semaphore::~Semaphore(){
	sem_destory(&m_semaphore);
}

void Semaphore::wait(){
	if(sem_wait(&m_semaphore)){
		return;
	}	
}

void Semaphore::notify(){
	if(sem_post(&m_semaphore)){
		throw std::logic_error("em_post error");
	}	
}

static Thread* Thread::GetThis(){
	return t_thread;
}
static const std::string& Thread::GetName(){
	return t_thread_name;
}

static void Thread::SetName(std::string& name){
	if(t_thread){
		t_thread->m_name = name;
	}
	t_thread_name = name;
}

Thread::tid_t getId() const { return m_id; }

const std::string& Thread::getName() const { return m_name; }

// 构造函数
Thread::Thread(std::function<void()> cb, const std::string& name){
	if(name.empty()){
		m_name = "UNKNOW";
	}
	int rt = pthread_create(&m_thread, nullptr, &Thread::run, this);
	if(rt){
		SYLAR_LOG_ERROR(g_logger) << "pthread_creates thread fail, rt=" <<
			re << " name = " << name;
		throw std::logic_error("pthread_create error");
	}
}

// 析构函数
Thread::~Thread(){
	if(m_thread){
		pthread_detach(m_thread);	
	}
}
void Thread::join(){
	if(m_thread){	
		int rt = pthread_join(m_thread, nullptr);
		if(rt){
			SYLAR_LOG_ERROR(g_logger) << "pthread_creates thread fail, rt=" 				<< rt << " name = " << m_name;
			throw std::logic_error("pthread_create error");
		}
m_thread = 0;
	}	
}
	
void* Thread::run(void* arg){
	Thread* thread = (Thread*)arg;
	t_thread = thread;
	thread->m_id = sylar::GetThreadId();
	pthread_setname_np(pthread_self(), thread->m_name.substr(0, 15).c_str());

	std::function<void()> cd;
	cb.swap(thread->m_cb);
	return 0;
}


}
