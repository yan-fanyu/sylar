#include <util.h>

namespace sylar{
pid_t GetThreadId(){
	return syscall(SYS_gettid);
}

uint32_t GetFiberID(){
	return 0;
}

}
