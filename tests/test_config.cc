#include"sylar/config.h"
#include"sylar/log.h"
#include<yaml-cpp/yaml.h>

sylar::ConfigVar<int>::ptr g_int_value_config = 
	sylar::Config::Lookup("system.port", (int)8080, "system port");

sylar::ConfigVar<float>::ptr g_float_value_config = 
	sylar::Config::Lookup("system.value", (float)10.2f, "system value");

void print_yaml(const YAML::NIde& node, int level){	
}

void test_yaml(){
	YAML::Node root = YAML::LoadFIle("/home/sylar/worksapce/sylar/bin/conf/log.yml);
	print_yaml(node, 0);
}

int main(){
	SYLAR_LOG_INFO(SYLAR_LOG_ROOT) << g_int_value_config->getValue();
	SYLAR_LOG_INFO(SYLAR_LOG_ROOT) << g_int_value_config->toString();
	
	test_yaml();
	return 0;
}
