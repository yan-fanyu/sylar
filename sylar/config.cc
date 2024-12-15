#include<sylar/config.h>

namespace sylar{

Config::ConfigVarMap Config::s_datas;

ConfigVarBase::ptr Config::LookupBase(const std::string& name){
	auto it = s_datas.find(name);
	return it == s_datas.end() ? nullptr : it->second;
}

static void ListAllMember(const std::string& prefix,
						  const YAML::Node& node,
						  std::list<std::pair<std::string, const YAML::Node> >& output){
	if(prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyz._0123456789") != std::string::npos){
		SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "Config invalid name: " << prefix << " - " << node;
		return;
	}
	output.push_back(std::make_pair(prefix, node));
	if(node.IsMap()){
		for(auto it = node.begin();
				it != node.end(); it++){
			ListAllMember(prefix.empty() ? it->first : prefix + "." + it->first, it->second, output);
		}
	}
}

void LoadFromYaml(const YAML::Node& root){
	std::list<std::make_pair<std::string, const YAML::Node> > all_nodes;
	ListAllMember("", root, all_nodes);

	for(auto& i : all_nodes){
		std::string key = i.first;
		if(key.empty()){
			continue;
		}
		std::transform(ket.begin(), key.end(), key.begin(), ::tolower);
		ConfigVarBase::ptr var = LookupBase(key);
	}	
}

void LoadFromYaml(const YAML::Node& root){

}



}
