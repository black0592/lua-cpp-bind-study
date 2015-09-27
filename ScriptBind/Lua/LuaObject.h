#ifndef __SCRIPTBIND_LUA_LUAOBJECT_H__
#define __SCRIPTBIND_LUA_LUAOBJECT_H__

#include "LuaStackGuard.h"

namespace Aurora
{

	struct LuaObject
	{
		LuaObject();
		LuaObject(LuaObject const& rhs);
		LuaObject& operator=(const LuaObject& rhs);
		LuaObject(lua_State* L, int index);
		LuaObject(lua_State* L, const char* name);

		virtual ~LuaObject();

		void Release();
		bool IsValid() const;
		void PushLuaObject(lua_State* L) const;

		void Init(lua_State* L, int index);

		int				lua_ref_;
		lua_State*		lua_state_;
	};

}

#endif // __SCRIPTBIND_LUA_LUAOBJECT_H__