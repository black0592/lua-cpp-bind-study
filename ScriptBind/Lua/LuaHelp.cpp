#include "LuaHelp.h"
#include "LuaBind.h"

namespace Aurora
{


	int lua_setuserdata_metatable() {
		lua_State* L = GetLuaState();
		//if(!lua_isuserdata(L, -2)) LUA_ERROR(L, "");
		//if(!lua_istable(L, -1)) LUA_ERROR(L, "");
		lua_pushvalue(L, -2);
		lua_pushvalue(L, -2);
		return lua_setmetatable(L, -2);
	}

	static const char* _lua_pop_string(lua_State* L)
	{
		lua_pop(L, 1);
		const char* str = lua_tostring(L, 0);
		return str;
	}

	static int _lua_handle_error(lua_State* L)
	{
		lua_getglobal(L, "debug");
		if(!lua_istable(L, -1))
		{
			lua_pop(L, 1);
			return 1;
		}

		lua_getfield(L, -1, "traceback");
		if(!lua_isfunction(L, -1))
		{
			lua_pop(L, 2);
			return 1;
		}

		lua_pushvalue(L, 1);
		lua_pushinteger(L, 2);
		lua_call(L, 2, 1);
		return 1;
	}

	int _lua_call(lua_State* L, int params_num, int result_count, int /*n*/)
	{
		int size = lua_gettop(L);
		int handler = lua_gettop(L) - params_num;
		lua_pushcfunction(L, _lua_handle_error);
		lua_insert(L, handler);

		int ret = 0;
		if(lua_pcall(L, params_num, result_count, handler))
		{
			ret = LUA_ERRRUN;
			LUA_ERROR(L, _lua_pop_string(L));
		} 
		lua_remove(L, handler);

		if(((lua_gettop(L) + (int)params_num + 1 - result_count) != size))
		{
			LUA_ERROR(L, "Lua error: lua stack size changed!");
		}

		return ret;
	}

	//////////////////////////////////////////////////////////////////////////

}

