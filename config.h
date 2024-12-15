#ifndef __SYLAR_CONFIG_H__
#define __SYLAR_CONFIG_H__
#include<memory>
#include<sstream>
#include<boost/lexical_cats.hpp>
#include<string>
#include<sylar/log.h>
#include<yaml-cpp/yaml.h>

namespace sylar{
// 配置类的基类
class ConfigVarBase{
public:
	typedef std::shared_ptr<ConfigVarBase> ptr;
	ConfigVarBase(const std::string& name, const std::string& description = "")
		:m_name(name),
		,m_description(description){
			std::transform(m_name.begin(), m_name.end(), m_name.begin(), ::tolower);
	}
	// 基类的析构函数必须使用虚函数
	virtual ~ConfigVarBase(){};

	// 定义纯虚函数
	const std::string& getName() const { return m_name; }
	const std::string& getDescription() const { return m_description; }
	
	virtual std:string toString() = 0;
	virtual bool fromString(const std::string& val) = 0;
protected:
	std::string m_name;	
	std::string m_description;

};

// 定义实现类
template <class T>
class ConfigVar : public ConfigVarBase{
public:
	typedef shared_ptr<ConfigVar> ptr;
	
	ConfigVar(const T& default_val
			,const std::string& name
			,const std::string& description = "")
			:ConfigVarBase(name, description){
		m_val = default_val;
	}	
	virtual std:string toString() override{
		try{
			return boost::lexical_cast<T>(val);		
		}catch(std::exception& e){
			SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ConfigVar::toString exception" << e.what() << " convert: string to " << typeid(m_val).name();
		}	
		return false;
	}
	virtual bool fromString(const std::string& val) override {
		try{
			m_val = boost::lexical_cast<T>(val);		
		}catch(std::exception& e){
			SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ConfigVar::toString exception" << e.what() << " convert: string to " << typeid(m_val).name();
		}	
		return false;
	}
	const T getValue() const {return m_val;}
	void setValue(const T& v){m_val = v;}
private:
	T m_val;

}; 


class Config{
public:
	typedef std::map<std::string, ConfigVarBase::ptr> ConfigVarMap;

	template<class T>
	static typename ConfigVar<T>::ptr Lookup(const std::string& name,
		const T& default_val, const std::string& description = ""){
		auto temp Lookup<T>(name);
		if(temp){
			SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << ""Lookup name = " << "exists";
			return tmp;
		}
		
		if(name.find_first_not_of("abcdefghijklmnopqrstuvwxyz._0123456789" != std::string::npos){
			SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "Lookup name invalid" << name;
			throw std::invalid_argument(name);	
		}

		typename ConfigVar<T>::ptr v(new ConfigVar<T>(name. default_val, description));
		s_datas[name] = v;
		return v;	
	}
	

	template<class T>
	static typename ConfigVar<T>::ptr Lookup(const std::string& name){
		auto it = s_datas.find(name);
		if(it == s_datas.end()){
			return nullptr;
		}
		return std::dynamic_pointer_cast<ConfigVar<T> >(it->second);
	}

	static void LoadFromYaml(const YAML::Node& root);
	static ConfigVarBase LookupBase(const std::string& name);
private:
private:
	static ConfigVarMap s_datas;

};




}

#endif 
