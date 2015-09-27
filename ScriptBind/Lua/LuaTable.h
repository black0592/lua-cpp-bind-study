#ifndef __SCRIPTBIND_LUA_LUATABLE_H__
#define __SCRIPTBIND_LUA_LUATABLE_H__

#include "LuaObject.h"

namespace Aurora
{

	struct LuaTable : public LuaObject
	{
		LuaTable();
		LuaTable(lua_State* L);
		LuaTable(lua_State* L, int index) : LuaObject(L, index) {}
		LuaTable(lua_State* L, const char* name) : LuaObject(L, name) {}

		template<typename K,typename V> inline void Set(K key, V value);
		template<typename V, typename K> inline V Get(K key);
	};

	//////////////////////////////////////////////////////////////////////////

	template<typename K,typename V>
	inline void LuaTable::Set(K key, V value) 
	{
		if ( IsValid() )
		{
			int oldTop=lua_gettop(lua_state_);

			lua_rawgeti(lua_state_, LUA_REGISTRYINDEX, lua_ref_);
			Push(lua_state_, key); 
			Push(lua_state_, value);
			lua_settable(lua_state_, -3);

			lua_settop(lua_state_, oldTop);
		}
	}

	template<typename V, typename K>
	inline V LuaTable::Get(K key) 
	{
		int oldTop=lua_gettop(lua_state_);
		if ( IsValid() ) 
		{
			lua_rawgeti(lua_state_, LUA_REGISTRYINDEX, lua_ref_);
			Push(lua_state_, key);
			lua_gettable(lua_state_, -2);
		}
		else
		{
			lua_pushnil(lua_state_);
		}

		V result = Pop<V>(lua_state_, -1);
		lua_settop(lua_state_, oldTop);
		return result;
	}

	template<> inline void Push(lua_State* L, LuaTable ret) { ret.PushLuaObject(L);};
	template<> inline LuaTable	Pop(lua_State* L, int index) { return LuaTable(L, index);};
}

#endif // __SCRIPTBIND_LUA_LUATABLE_H__