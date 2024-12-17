#ifndef __SYLAR_THREAD_H__
#define __SYLAR_THREAD_H__

#include<thread>
#include<functional>
#include<memory>
#include<pthread.h>


namespace sylar{


class Semaphore{
public:
	Semaphore(uint32_t count = 0);
	~Semaphore();

	void wait();
	void notify();

// 禁用拷贝构造函数
private:
	Semaphore(const Semaphore&) = delete;
	Semaphore(const Semaphore&) = delete;
	Semaphore& operator=(const Semaphore&) = delete;

private:
	sem_t m_semaphore;
};

// RAII 用类的生命周期控制 锁 的关闭和开启
template<class T>
struct ScopedLockImpl{
public:
	ScopedLockImpl(T& mutex): m_mutex(mutex){
		m_mutex.lock();
		m_locked = true;
	}
	~ScopedLockImpl(){
		unlock();
	}

	void lock(){
		if(!m_locked){
			m_mutex.lock();
			m_locked = true;
		}
	}
	
	void unlock(){
		if(m_locked){
			m_mutex.unlock();
			m_locked = false;
		}
	}
private:
	T& m_mutex;
	bool m_locked;

}

class Thread{
public:
	typedef std::shared_ptr<Thread> ptr;
	Thread(std::function<void()> cb, const std::string& name);
	~Thread();
	pid_t getId() const { return m_id; }
	const std::string& getName() const { return m_name; }
	
	void join();
	
	// 静态方法：方法名 首字母大写
	static Thread* GetThis();
	static const std::string& GetName();
	static void SetName(std::string& name);
	static void* run(void* arg);
private:
	// 禁止使用拷贝构造函数
	Thread(const Thread&) = delete;
	Thread(const Thread&&) = delete;
	Thread& operator=(constd Thread&) = delete;

private:
	pid_t m_id = -1;
	pthread_t m_thread = 0;
	std::function<void()> m_cb;
	std::string m_name;
};

}



#endif
