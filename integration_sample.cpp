#include <iostream>
#include <functional>
#include "Base/ExportHelp.h"
#include "ScriptBind/Script.h"
using namespace Aurora;


inline void doFile(lua_State *L, const char *fileName) 
{
	bool ret = luaL_dofile(L, fileName ) == 0;
	if(!ret)
	{
		const char* error_info = lua_tostring(L, -1);
		LUA_ERROR(L, "%s", error_info);
	}
}

class BaseClass
{
public:
	BaseClass() : x_(0) {}
	void SetX(int x) {x_ = x; printf("TestClass SetX to %d\n", x);}
	int GetX() /*const*/ {printf("TestClass GetX %d\n", x_); return x_;}
	int Foo5(int, int, int, int, int){}
	static void Print() {printf("BaseClass Print\n");}

	int x_;
};

class DerivedClass : public BaseClass
{
public:
	DerivedClass() {}
	DerivedClass(int) {}
	static void Print() {printf("DerivedClass Print\n");}
};

class ScriptComponent 
{
public: 
	ScriptComponent() {}

	void SetScriptClass(LuaTable sptClass) 
	{
		script_class_ = sptClass;

		script_init_func_ = sptClass.Get<LuaFunction>("OnInit");
		script_start_func_ = sptClass.Get<LuaFunction>("OnStart");
	}

	void Init() 
	{
		if(script_init_func_.IsValid())
			script_init_func_(this);
	}

	void Start() 
	{
		if(script_start_func_.IsValid())
			script_start_func_(this);
	}

	void print()
	{
		printf("ScriptComponent print\n");
	}

private:
	LuaTable		script_class_;
	LuaFunction		script_init_func_;
	LuaFunction		script_start_func_;
};

inline ScriptComponent* doComponent(lua_State *L, const char *fileName, const char *compName)
{
	LuaFunction func(L, "LoadComponentFile");
	func(fileName, compName);
	LuaTable sptClass = func.Return<LuaTable>();
	LuaFunction newFunc = sptClass.Get<LuaFunction>("new");
	newFunc();

	ScriptComponent* component = newFunc.Return<ScriptComponent*>();
	component->SetScriptClass(sptClass);
	return component;
}

void test_lua(lua_State* L)
{
	run_buildin_bindings();

	BEGIN_BASE_CLASS(BaseClass)
		CONSTRUCTOR()
		METHOD(GetX)
		METHOD(SetX)
		METHOD_STATIC(Print)
	END_CLASS()

	BEGIN_INHERITED_CLASS(DerivedClass, BaseClass)
		CONSTRUCTOR()
		METHOD_STATIC(Print)
	END_CLASS()

	BEGIN_BASE_CLASS(ScriptComponent)
		CONSTRUCTOR()
		METHOD(print)
	END_CLASS()

	BaseClass bc;

	doFile(L, "class.lua");
	doFile(L, "buildin.lua");
 	doFile(L, "sample1.lua");


	ScriptComponent* t1 = doComponent(L, "test_comp.lua", "TestSptComp");
	t1->Init();
	t1->Start();

	ScriptComponent* t2 = doComponent(L, "test_comp1.lua", "TestSptComp1");
	t2->Init();
	t2->Start();


	printf("test finished\n");
}

int main() 
{
	// test lua
 	lua_State* L = OpenLua();
 	test_lua(L);
 	CloseLua(L);

	// pause
	std::cin.ignore(1);
	return 0;
}