#include "LuaBind.h"

namespace Aurora
{
	lua_State* gLuaState = nullptr;

	lua_State* OpenLua()
	{
		ASSERT(!gLuaState, "should not call OpenLua more than once");

		lua_State* L = luaL_newstate();
		luaL_openlibs(L);

		_CHECK_STACK(L);
		lua_newtable(L); // meta table
		lua_pushvalue(L, -1);
		lua_pushstring(L, "v");
		lua_setfield(L, -2, "__mode"); // set as weak-value table
		lua_setmetatable(L, -2);
		lua_setglobal(L, "_objects");

		gLuaState = L;

		return L;
	}

	lua_State* GetLuaState()
	{
		ASSERT(gLuaState, "should call OpenLua before GetLuaState");

		return gLuaState;
	}

	void CloseLua(lua_State* L) 
	{
		gLuaState = nullptr;
		ReleaseAllCaches();
		lua_close(L);
	}

}