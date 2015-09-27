#include <iostream>
#include <functional>
#include <RTTI/jrtti.h>
#include "ScriptBind/Lua/LuaBind.h"
using namespace Aurora;

lua_State* L = nullptr;

inline void doFile(lua_State *L, const char *fileName) 
{
	luaL_dofile(L, fileName );
}

inline int test_global_func0()
{
	printf("call test_global_func0\n");
	return 1;
}

inline int test_global_func1(const char* p1)
{
	printf("call test_global_func1 %s\n", p1);
	return 2;
}

inline void test_global_func_void0()
{
	printf("call test_global_func_void0\n");
}

inline void test_global_func_void1(const char* p1)
{
	printf("call test_global_func_void1 %s\n", p1);
}

class BaseClass
{
public:
	BaseClass() : x_(0) {}
	BaseClass(int x) : x_(x) {}

	void SetX(int x) {x_ = x; printf("TestClass SetX to %d\n", x);}
	int GetX() /*const*/ {printf("TestClass GetX %d\n", x_); return x_;}

	int x_;
};

class DrivedClass : public BaseClass
{
public:
	DrivedClass(int x) : BaseClass(x) {}
};

void test_lua(lua_State* L)
{
	REGISTER_GLOBAL_FUNC(L, test_global_func0);
	REGISTER_GLOBAL_FUNC(L, test_global_func1);
	REGISTER_GLOBAL_FUNC(L, test_global_func_void0);
	REGISTER_GLOBAL_FUNC(L, test_global_func_void1);
 
	REGISTER_INHERIT_CLASS(L, DrivedClass, BaseClass);
	REGISTER_CONSTRUCOTR(L, DrivedClass, int);

	REGISTER_CLASS(L, BaseClass);
 	REGISTER_CONSTRUCOTR(L, BaseClass, int);

	RegisterProperty<BaseClass>(L, "X", &BaseClass::x_);

	doFile(L, "sample.lua");
	LuaFunction<void> lua_print_func(L, "luaPrint");
	lua_print_func("hello");

	LuaFunction<int> lua_sum_func(L, "luaSum");
	int sum = lua_sum_func(1, 2);

	LuaTable t(L, "testTable");
	printf("%d=%s\n", 1, t.Get<char*>(1));
	t.Set(1, "world");
	printf("%d=%s\n", 1, t.Get<char*>(1));

	printf("lua test finished\n");
}

int main() 
{
	// test lua
	L = OpenLua();
	test_lua(L);
	CloseLua(L);

	// pause
	std::cin.ignore(1);
	return 0;
}