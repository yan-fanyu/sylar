#include"sylar/config.h"
#include"sylar/log.h"
#include<yaml-cpp/yaml.h>

sylar::ConfigVar<int>::ptr g_int_value_config = 
	sylar::Config::Lookup("system.port", (int)8080, "system port");

sylar::ConfigVar<float>::ptr g_float_value_config = 
	sylar::Config::Lookup("system.value", (float)10.2f, "system value");

void print_yaml(const YAML::NIde& node, int level){	
<<<<<<< HEAD
	if(node.IsScalar()){
		SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
			<< node.Scalar() << " - " << node.Type() << " - " << level;
	}else if(node.IsNull()){
		SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
			<< "NULL - " << node.Type() << " - " << level;
	}else if(node.IsMap()){
		for(auto it = node.begin(); it != node.end(); it++){
			SYLAR_LOG_ROOT(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
			<< it->first << " - " << it->second.Type() << " - " << level;
			print_yaml(it->second, level + 1);
		}
	}else if(node.IsSequence()){
		for(size_t i = 0; i < node.size(); ++i){
			
			SYLAR_LOG_ROOT(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
			<< i << " - " << node[i].Type() << " - " << level;
			print_yaml(node[i], level + 1);
		}
	}
=======
>>>>>>> 532a61386e785b5b6c8332dceeaa96fa30f81d4b
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
