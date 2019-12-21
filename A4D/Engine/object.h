#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <map>

typedef void* (*Constructor)();

class CObjectFactory
{
public:
	static void registerClass(std::string className, Constructor constructor, size_t type_id)
	{
		name_constructors()[className] = constructor;
		id_constructors()[type_id] = constructor;
	}

	static void* createObjectByName(const std::string& className)
	{
		Constructor constructor = NULL;

		if (name_constructors().find(className) != name_constructors().end())
			constructor = name_constructors().find(className)->second;

		if (constructor == NULL)
			return NULL;

		return (*constructor)();
	}

	static void * createObjectById(size_t id)
	{
		Constructor constructor = NULL;

		if (id_constructors().find(id) != id_constructors().end())
			constructor = id_constructors().find(id)->second;

		if (constructor == NULL)
			return NULL;

		return (*constructor)();
	}
private:
	inline static std::map<std::string, Constructor>& name_constructors()
	{
		static std::map<std::string, Constructor> instance;
		return instance;
	}
	inline static std::map<size_t, Constructor> & id_constructors()
	{
		static std::map<size_t, Constructor> instance;
		return instance;
	}
};


#define REGISTER_CLASS(class_name) \
class class_name##Helper { \
public: \
    class_name##Helper() \
    { \
        CObjectFactory::registerClass(#class_name, class_name##Helper::creatObjFunc, typeid(class_name).hash_code()); \
    } \
    static void* creatObjFunc() \
    { \
        return new class_name; \
    } \
}; \
class_name##Helper class_name##helper;


#endif