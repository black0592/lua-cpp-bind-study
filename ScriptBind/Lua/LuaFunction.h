#ifndef __SCRIPTBIND_LUA_LUAFUNCTION_H__
#define __SCRIPTBIND_LUA_LUAFUNCTION_H__

#include "LuaObject.h"

namespace Aurora
{

	struct LuaFunction : public LuaObject
	{
	public:
		LuaFunction() : LuaObject() {}
		LuaFunction(lua_State* L, int index) : LuaObject(L, index) {}
		LuaFunction(lua_State* L, const char* name) : LuaObject(L, name) {}

		void operator()() 
		{
			lua_rawgeti(lua_state_, LUA_REGISTRYINDEX, lua_ref_);
			_lua_call(lua_state_, 0, 1, 0);
		}

		template<typename P1>
		void operator()(P1 p1) 
		{
			lua_rawgeti(lua_state_, LUA_REGISTRYINDEX, lua_ref_);
			Push(lua_state_, p1);
			_lua_call(lua_state_, 1, 1, 0);
		}

		template<typename P1, typename P2>
		void operator()(P1 p1, P2 p2) 
		{
			lua_rawgeti(lua_state_, LUA_REGISTRYINDEX, lua_ref_);
			Push(lua_state_, p1);
			Push(lua_state_, p2);
			_lua_call(lua_state_, 2, 1, 0);
		}

		template<typename P1, typename P2, typename P3>
		void operator()(P1 p1, P2 p2, P3 p3) 
		{
			lua_rawgeti(lua_state_, LUA_REGISTRYINDEX, lua_ref_);
			Push(lua_state_, p1); 
			Push(lua_state_, p2); 
			Push(lua_state_, p3);
			_lua_call(lua_state_, 3, 1, 0);
		}

		template<typename P1, typename P2, typename P3, typename P4>
		void operator()(P1 p1, P2 p2, P3 p3, P4 p4)
		{
			lua_rawgeti(lua_state_, LUA_REGISTRYINDEX, lua_ref_);
			Push(lua_state_, p1);
			Push(lua_state_, p2);
			Push(lua_state_, p3);
			Push(lua_state_, p4);
			_lua_call(lua_state_, 4, 1, 0);
		}

		template<typename P1, typename P2, typename P3, typename P4, typename P5>
		void operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) 
		{
			lua_rawgeti(lua_state_, LUA_REGISTRYINDEX, lua_ref_);
			Push(lua_state_, p1);
			Push(lua_state_, p2);
			Push(lua_state_, p3);
			Push(lua_state_, p4);
			Push(lua_state_, p5);
			_lua_call(lua_state_, 5, 1, 0);
		}

		template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
		void operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) 
		{
			lua_rawgeti(lua_state_, LUA_REGISTRYINDEX, lua_ref_);
			Push(lua_state_, p1);
			Push(lua_state_, p2);
			Push(lua_state_, p3); 
			Push(lua_state_, p4);
			Push(lua_state_, p5);
			Push(lua_state_, p6);
			_lua_call(lua_state_, 6, 1, 0);
		}

		template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
		void operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7) 
		{
			lua_rawgeti(lua_state_, LUA_REGISTRYINDEX, lua_ref_);
			Push(lua_state_, p1);
			Push(lua_state_, p2);
			Push(lua_state_, p3);
			Push(lua_state_, p4); 
			Push(lua_state_, p5);
			Push(lua_state_, p6);
			Push(lua_state_, p7);
			_lua_call(lua_state_, 7, 1, 0);
		}

		template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
		void operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8) 
		{
			lua_rawgeti(lua_state_, LUA_REGISTRYINDEX, lua_ref_);
			Push(lua_state_, p1);
			Push(lua_state_, p2); 
			Push(lua_state_, p3);
			Push(lua_state_, p4); 
			Push(lua_state_, p5); 
			Push(lua_state_, p6);
			Push(lua_state_, p7);
			Push(lua_state_, p8);
			_lua_call(lua_state_, 8, 1, 0);
		}

		template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
		void operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9) 
		{
			lua_rawgeti(lua_state_, LUA_REGISTRYINDEX, lua_ref_);
			Push(lua_state_, p1);
			Push(lua_state_, p2);
			Push(lua_state_, p3);
			Push(lua_state_, p4);
			Push(lua_state_, p5);
			Push(lua_state_, p6);
			Push(lua_state_, p7);
			Push(lua_state_, p8); 
			Push(lua_state_, p9);
			_lua_call(lua_state_, 9, 1, 0);
		}

		template<typename R>
		R Return() 
		{
			ReturnValueFromLua();
		}
	};

	template<> inline void Push(lua_State* L, const LuaFunction& ret) { ret.PushLuaObject(L);};
	template<> inline LuaFunction Pop(lua_State* L, int index) { return LuaFunction(L, index);};
}

#endif // __SCRIPTBIND_LUA_LUAFUNCTION_H__