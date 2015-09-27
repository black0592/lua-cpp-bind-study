#include "Script.h"

#include "Base/ExportHelp.h"

namespace Aurora
{

	void run_buildin_bindings()
	{
		RegisterGlobalFunction(GetLuaState(), "lua_setuserdata_metatable", lua_setuserdata_metatable);
	}
	

} // namespace aurora

