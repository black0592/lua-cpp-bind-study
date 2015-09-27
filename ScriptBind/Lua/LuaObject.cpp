#include "LuaObject.h"

namespace Aurora
{

	LuaObject::LuaObject() : lua_ref_(LUA_REFNIL), lua_state_(NULL)
	{

	}

	LuaObject::LuaObject( LuaObject const& rhs )
	{
		if(rhs.IsValid()) 
		{
			lua_rawgeti(rhs.lua_state_, LUA_REGISTRYINDEX, rhs.lua_ref_);
			Init(rhs.lua_state_, -1);
		}
		else
		{
			lua_ref_ = LUA_REFNIL;
		}
	}

	LuaObject::LuaObject( lua_State* L, int index )
	{
		int oldTop=lua_gettop(L);
		Init(L, index);
		lua_settop(L,oldTop);
	}

	LuaObject::LuaObject( lua_State* L, const char* name )
	{
		int oldTop=lua_gettop(L);
		lua_getglobal(L, name);
		Init(L, -1);
		lua_settop(L,oldTop);
	}

	LuaObject& LuaObject::operator=( const LuaObject& rhs )
	{
		if(rhs.IsValid()) 
		{
			lua_rawgeti(rhs.lua_state_, LUA_REGISTRYINDEX, rhs.lua_ref_);
			Init(rhs.lua_state_, -1);
		}
		else
		{
			lua_ref_ = LUA_REFNIL;
		}
		return *this;
	}

	LuaObject::~LuaObject()
	{
		Release();
	}

	void LuaObject::Release()
	{
		if (IsValid()) 
			luaL_unref(lua_state_, LUA_REGISTRYINDEX, lua_ref_);
		lua_ref_ = NULL;
		lua_state_ = NULL;
	}

	bool LuaObject::IsValid() const
	{
		//return lua_ref_ != LUA_REFNIL;
		return true;
	}

	void LuaObject::Init( lua_State* L, int index )
	{
		if (lua_istable(L, index) || lua_isfunction(L, index)) 
		{
			lua_ref_ = luaL_ref(L, LUA_REGISTRYINDEX);
		}
		else 
		{
			lua_ref_ = LUA_REFNIL;
			ERROR("can't not find lua object\n");
		}
		lua_state_ = L;
	}

	void LuaObject::PushLuaObject( lua_State* L ) const
	{
		if(IsValid()) 
			lua_rawgeti(L, LUA_REGISTRYINDEX, lua_ref_);
		else 
			lua_pushnil(L);
	}


}

