#include "LuaTable.h"

namespace Aurora
{

	LuaTable::LuaTable() : LuaObject()
	{

	}

	LuaTable::LuaTable( lua_State* L ) : LuaObject()
	{
		lua_newtable(L);
		Init(L, -1);
	}

}

