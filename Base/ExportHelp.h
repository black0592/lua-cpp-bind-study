#ifndef __CORE_BASE_EXPORTHELP_H__
#define __CORE_BASE_EXPORTHELP_H__

#include "ScriptBind/Lua/LuaBind.h"

namespace Aurora
{

#define BEGIN_ABSTRACT_CLASS(TYPE) {\
class TYPE##_REGIST_HELP \
{ \
public: \
	typedef TYPE type; \
	TYPE##_REGIST_HELP() \
	{ \
		std::string CLASS_NAME(#TYPE); \
		RegisterClass<type>(GetLuaState(), #TYPE); \

#define BEGIN_BASE_CLASS(TYPE) {\
class TYPE##_REGIST_HELP \
{ \
public: \
	typedef TYPE type; \
	TYPE##_REGIST_HELP() \
	{ \
		std::string CLASS_NAME(#TYPE); \
		RegisterClass<type>(GetLuaState(), #TYPE); \

#define BEGIN_INHERITED_CLASS(TYPE, PARENT) \
	BEGIN_BASE_CLASS(TYPE) \
	RegisterParent<TYPE, PARENT>(); \

#define CONSTRUCTOR(...) RegisterConstructor<type>(GetLuaState(), "new", &Constructor<type, ##__VA_ARGS__>);  

#define METHOD(NAME) RegisterMethod<type>(GetLuaState(), #NAME, &type::##NAME);

#define METHOD_STATIC(NAME) RegisterStaticMethod<type>(GetLuaState(), #NAME, &type::##NAME);

#define PROPERTY(NAME) RegisterProperty<type>(GetLuaState(), #NAME, &type::##NAME);

#define PROPERTY_RENAMED(NAME, ANOTHER_NAME)RegisterProperty<type>(GetLuaState(), #ANOTHER_NAME, &type::##NAME);

#define END_CLASS() \
	} \
} tmp; }\


}

#endif // __CORE_BASE_EXPORTHELP_H__