#pragma once
#ifndef __SCRIPTBIND_LUA_LUASTACKGUARD_H__
#define __SCRIPTBIND_LUA_LUASTACKGUARD_H__

#include "LuaHelp.h"
#include "Base/Debug.h"

struct LuaStackGuard
{
	LuaStackGuard(lua_State *p)
	{
		state_=p;
		top_=lua_gettop(state_);
	}
	~LuaStackGuard()
	{
		lua_settop(state_,top_);
	}
private:
	int			top_;
	lua_State*	state_;
};

#define _GUARD_STACK(ls)  LuaStackGuard __guard__(ls);

#ifdef _DEBUG
struct LuaStackValidator
{
	LuaStackValidator( lua_State *state,const char *text )
	{
		text_ = text;
		state_ = state;
		top_ = lua_gettop(state_);
	}
	~LuaStackValidator()
	{
		if (top_ != lua_gettop(state_))
		{
			ERROR("lua stack validator error in fuc:%s\n", text_);
			lua_settop(state_,top_);
		}
	}

	const char*		text_;
	lua_State*		state_;
	int				top_;
};
#define _CHECK_STACK(L) LuaStackValidator __stackCheck((L),__FUNCTION__);
#else
#define _CHECK_STACK(L)
#endif

#endif // __SCRIPTBIND_LUA_LUASTACKGUARD_H__