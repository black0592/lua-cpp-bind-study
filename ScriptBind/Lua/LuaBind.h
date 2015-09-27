#ifndef __SCRIPTBIND_LUA_LUACLASSBINDER_H__
#define __SCRIPTBIND_LUA_LUACLASSBINDER_H__

#include <string>
#include <vector>
#include "LuaHelp.h"
#include "LuaFunction.h"

namespace Aurora
{
	inline static void CacheMethod(struct GenericMethod* method);
	inline static void CacheFunction(struct GenericFunction* function);
	inline static void CacheClassMetaData(struct ClassMetaData* data);
	inline static void ReleaseAllCaches();

	lua_State* OpenLua();
	lua_State* GetLuaState();
	void CloseLua(lua_State* L);

	struct GenericMethod
	{
		virtual ~GenericMethod() {}
		GenericMethod() {}
		inline virtual int Call(lua_State *L) { return 0;}
	};

	struct GenericFunction
	{
		virtual ~GenericFunction() {}
		GenericFunction() {}
		inline virtual int Call(lua_State *L) { return 0;}
	};

//////////////////////////////////////////////////////////////////////////

#define METHODCLASSES_PARAM_LIST_0 typename T
#define METHODCLASSES_PARAM_LIST_1 METHODCLASSES_PARAM_LIST_0, typename P1
#define METHODCLASSES_PARAM_LIST_2 METHODCLASSES_PARAM_LIST_1, typename P2
#define METHODCLASSES_PARAM_LIST_3 METHODCLASSES_PARAM_LIST_2, typename P3
#define METHODCLASSES_PARAM_LIST_4 METHODCLASSES_PARAM_LIST_3, typename P4
#define METHODCLASSES_PARAM_LIST_5 METHODCLASSES_PARAM_LIST_4, typename P5
#define METHODCLASSES_PARAM_LIST_6 METHODCLASSES_PARAM_LIST_5, typename P6
#define METHODCLASSES_PARAM_LIST_7 METHODCLASSES_PARAM_LIST_6, typename P7
#define METHODCLASSES_PARAM_LIST_8 METHODCLASSES_PARAM_LIST_7, typename P8
#define METHODCLASSES_PARAM_LIST_9 METHODCLASSES_PARAM_LIST_8, typename P9
#define METHODCLASSES_SP_PARAM_LIST_0 T
#define METHODCLASSES_SP_PARAM_LIST_1 METHODCLASSES_SP_PARAM_LIST_0, P1
#define METHODCLASSES_SP_PARAM_LIST_2 METHODCLASSES_SP_PARAM_LIST_1, P2
#define METHODCLASSES_SP_PARAM_LIST_3 METHODCLASSES_SP_PARAM_LIST_2, P3
#define METHODCLASSES_SP_PARAM_LIST_4 METHODCLASSES_SP_PARAM_LIST_3, P4
#define METHODCLASSES_SP_PARAM_LIST_5 METHODCLASSES_SP_PARAM_LIST_4, P5
#define METHODCLASSES_SP_PARAM_LIST_6 METHODCLASSES_SP_PARAM_LIST_5, P6
#define METHODCLASSES_SP_PARAM_LIST_7 METHODCLASSES_SP_PARAM_LIST_6, P7
#define METHODCLASSES_SP_PARAM_LIST_8 METHODCLASSES_SP_PARAM_LIST_7, P8
#define METHODCLASSES_SP_PARAM_LIST_9 METHODCLASSES_SP_PARAM_LIST_8, P9
#define PARAM_LIST_0
#define PARAM_LIST_1 PARAM_LIST_0  P1
#define PARAM_LIST_2 PARAM_LIST_1, P2
#define PARAM_LIST_3 PARAM_LIST_2, P3
#define PARAM_LIST_4 PARAM_LIST_3, P4
#define PARAM_LIST_5 PARAM_LIST_4, P5
#define PARAM_LIST_6 PARAM_LIST_5, P6
#define PARAM_LIST_7 PARAM_LIST_6, P7
#define PARAM_LIST_8 PARAM_LIST_7, P8
#define PARAM_LIST_9 PARAM_LIST_8, P9
#define READ_METHOD_PARAM_LIST_0
#define READ_METHOD_PARAM_LIST_1 READ_METHOD_PARAM_LIST_0  Pop<P1>(L,2)
#define READ_METHOD_PARAM_LIST_2 READ_METHOD_PARAM_LIST_1, Pop<P2>(L,3)
#define READ_METHOD_PARAM_LIST_3 READ_METHOD_PARAM_LIST_2, Pop<P3>(L,4)
#define READ_METHOD_PARAM_LIST_4 READ_METHOD_PARAM_LIST_3, Pop<P4>(L,5)
#define READ_METHOD_PARAM_LIST_5 READ_METHOD_PARAM_LIST_4, Pop<P5>(L,6)
#define READ_METHOD_PARAM_LIST_6 READ_METHOD_PARAM_LIST_5, Pop<P6>(L,7)
#define READ_METHOD_PARAM_LIST_7 READ_METHOD_PARAM_LIST_6, Pop<P7>(L,8)
#define READ_METHOD_PARAM_LIST_8 READ_METHOD_PARAM_LIST_7, Pop<P8>(L,9)
#define READ_METHOD_PARAM_LIST_9 READ_METHOD_PARAM_LIST_8, Pop<P9>(L,10)

#define MAKE_METHODCLASSX(N)\
	template<typename R, METHODCLASSES_PARAM_LIST_##N >\
	struct MethodClass##N : GenericMethod\
	{\
	typedef R (T::* TFUNC)(PARAM_LIST_##N);\
	TFUNC func_;\
	MethodClass##N(TFUNC func): func_(func) {};\
	~MethodClass##N(){};\
	inline virtual int Call(lua_State *L) {\
	T* obj = Pop<T*>(L, 1);\
	Push(L, (obj->*func_)(READ_METHOD_PARAM_LIST_##N));\
	return 1;\
	};\
	};

#define MAKE_VOID_METHODCLASSX(N) \
	template<METHODCLASSES_PARAM_LIST_##N >\
	struct MethodClass##N<void, METHODCLASSES_SP_PARAM_LIST_##N> : GenericMethod\
	{\
	typedef void (T::* TFUNC)(PARAM_LIST_##N);\
	TFUNC func_;\
	MethodClass##N(TFUNC func): func_(func) {};\
	~MethodClass##N(){};\
	inline virtual int Call(lua_State *L) {\
	T* obj = Pop<T*>(L, 1);\
	(obj->*func_)(READ_METHOD_PARAM_LIST_##N);\
	return 0;\
	};\
	};

		MAKE_METHODCLASSX(0)
		MAKE_METHODCLASSX(1)
		MAKE_METHODCLASSX(2)
		MAKE_METHODCLASSX(3)
		MAKE_METHODCLASSX(4)
		MAKE_METHODCLASSX(5)
		MAKE_METHODCLASSX(6)
		MAKE_METHODCLASSX(7)
		MAKE_METHODCLASSX(8)
		MAKE_METHODCLASSX(9)

		MAKE_VOID_METHODCLASSX(0)
		MAKE_VOID_METHODCLASSX(1)
		MAKE_VOID_METHODCLASSX(2)
		MAKE_VOID_METHODCLASSX(3)
		MAKE_VOID_METHODCLASSX(4)
		MAKE_VOID_METHODCLASSX(5)
		MAKE_VOID_METHODCLASSX(6)
		MAKE_VOID_METHODCLASSX(7)
		MAKE_VOID_METHODCLASSX(8)
		MAKE_VOID_METHODCLASSX(9)

//////////////////////////////////////////////////////////////////////////

#define FUNCTIONCLASSX_PARAM_LIST_0 typename R
#define FUNCTIONCLASSX_PARAM_LIST_1 FUNCTIONCLASSX_PARAM_LIST_0, typename P1
#define FUNCTIONCLASSX_PARAM_LIST_2 FUNCTIONCLASSX_PARAM_LIST_1, typename P2
#define FUNCTIONCLASSX_PARAM_LIST_3 FUNCTIONCLASSX_PARAM_LIST_2, typename P3
#define FUNCTIONCLASSX_PARAM_LIST_4 FUNCTIONCLASSX_PARAM_LIST_3, typename P4
#define FUNCTIONCLASSX_PARAM_LIST_5 FUNCTIONCLASSX_PARAM_LIST_4, typename P5
#define FUNCTIONCLASSX_PARAM_LIST_6 FUNCTIONCLASSX_PARAM_LIST_5, typename P6
#define FUNCTIONCLASSX_PARAM_LIST_7 FUNCTIONCLASSX_PARAM_LIST_6, typename P7
#define FUNCTIONCLASSX_PARAM_LIST_8 FUNCTIONCLASSX_PARAM_LIST_7, typename P8
#define FUNCTIONCLASSX_PARAM_LIST_9 FUNCTIONCLASSX_PARAM_LIST_8, typename P9
#define FUNCTIONCLASSX_VOID_RL_PARAM_LIST_0
#define FUNCTIONCLASSX_VOID_RL_PARAM_LIST_1 FUNCTIONCLASSX_VOID_RL_PARAM_LIST_0  typename P1
#define FUNCTIONCLASSX_VOID_RL_PARAM_LIST_2 FUNCTIONCLASSX_VOID_RL_PARAM_LIST_1, typename P2
#define FUNCTIONCLASSX_VOID_RL_PARAM_LIST_3 FUNCTIONCLASSX_VOID_RL_PARAM_LIST_2, typename P3
#define FUNCTIONCLASSX_VOID_RL_PARAM_LIST_4 FUNCTIONCLASSX_VOID_RL_PARAM_LIST_3, typename P4
#define FUNCTIONCLASSX_VOID_RL_PARAM_LIST_5 FUNCTIONCLASSX_VOID_RL_PARAM_LIST_4, typename P5
#define FUNCTIONCLASSX_VOID_RL_PARAM_LIST_6 FUNCTIONCLASSX_VOID_RL_PARAM_LIST_5, typename P6
#define FUNCTIONCLASSX_VOID_RL_PARAM_LIST_7 FUNCTIONCLASSX_VOID_RL_PARAM_LIST_6, typename P7
#define FUNCTIONCLASSX_VOID_RL_PARAM_LIST_8 FUNCTIONCLASSX_VOID_RL_PARAM_LIST_7, typename P8
#define FUNCTIONCLASSX_VOID_RL_PARAM_LIST_9 FUNCTIONCLASSX_VOID_RL_PARAM_LIST_8, typename P9
#define FUNCTIONCLASSX_SP_PARAM_LIST_0 void
#define FUNCTIONCLASSX_SP_PARAM_LIST_1 FUNCTIONCLASSX_SP_PARAM_LIST_0, P1
#define FUNCTIONCLASSX_SP_PARAM_LIST_2 FUNCTIONCLASSX_SP_PARAM_LIST_1, P2
#define FUNCTIONCLASSX_SP_PARAM_LIST_3 FUNCTIONCLASSX_SP_PARAM_LIST_2, P3
#define FUNCTIONCLASSX_SP_PARAM_LIST_4 FUNCTIONCLASSX_SP_PARAM_LIST_3, P4
#define FUNCTIONCLASSX_SP_PARAM_LIST_5 FUNCTIONCLASSX_SP_PARAM_LIST_4, P5
#define FUNCTIONCLASSX_SP_PARAM_LIST_6 FUNCTIONCLASSX_SP_PARAM_LIST_5, P6
#define FUNCTIONCLASSX_SP_PARAM_LIST_7 FUNCTIONCLASSX_SP_PARAM_LIST_6, P7
#define FUNCTIONCLASSX_SP_PARAM_LIST_8 FUNCTIONCLASSX_SP_PARAM_LIST_7, P8
#define FUNCTIONCLASSX_SP_PARAM_LIST_9 FUNCTIONCLASSX_SP_PARAM_LIST_8, P9
#define READ_FUNCTION_PARAM_LIST_0
#define READ_FUNCTION_PARAM_LIST_1 READ_FUNCTION_PARAM_LIST_0  Pop<P1>(L,1)
#define READ_FUNCTION_PARAM_LIST_2 READ_FUNCTION_PARAM_LIST_1, Pop<P2>(L,2)
#define READ_FUNCTION_PARAM_LIST_3 READ_FUNCTION_PARAM_LIST_2, Pop<P3>(L,3)
#define READ_FUNCTION_PARAM_LIST_4 READ_FUNCTION_PARAM_LIST_3, Pop<P4>(L,4)
#define READ_FUNCTION_PARAM_LIST_5 READ_FUNCTION_PARAM_LIST_4, Pop<P5>(L,5)
#define READ_FUNCTION_PARAM_LIST_6 READ_FUNCTION_PARAM_LIST_5, Pop<P6>(L,6)
#define READ_FUNCTION_PARAM_LIST_7 READ_FUNCTION_PARAM_LIST_6, Pop<P7>(L,7)
#define READ_FUNCTION_PARAM_LIST_8 READ_FUNCTION_PARAM_LIST_7, Pop<P8>(L,8)
#define READ_FUNCTION_PARAM_LIST_9 READ_FUNCTION_PARAM_LIST_8, Pop<P9>(L,9)

#define MAKE_FUNCTIONCLASSX(N)\
	template<FUNCTIONCLASSX_PARAM_LIST_##N >\
	struct FunctionClass##N : GenericFunction\
	{\
		typedef R (* TFUNC)(PARAM_LIST_##N);\
		TFUNC func_;\
		FunctionClass##N(TFUNC func): func_(func) {};\
		~FunctionClass##N() {};\
		inline virtual int Call(lua_State *L) \
		{\
			Push(L, (*func_)(READ_FUNCTION_PARAM_LIST_##N));\
			return 1;\
		};\
	};

#define MAKE_VOID_FUNCTIONCLASSX(N) \
	template<FUNCTIONCLASSX_VOID_RL_PARAM_LIST_##N >\
	struct FunctionClass##N<FUNCTIONCLASSX_SP_PARAM_LIST_##N> : GenericFunction\
	{\
		typedef void (* TFUNC)(PARAM_LIST_##N);\
		TFUNC func_;\
		FunctionClass##N( TFUNC func): func_(func) {};\
		~FunctionClass##N() {};\
		inline virtual int Call(lua_State *L)\
		{\
			(*func_)(READ_FUNCTION_PARAM_LIST_##N);\
			return 0;\
		};\
	};

 		MAKE_FUNCTIONCLASSX(0)
		MAKE_FUNCTIONCLASSX(1)
		MAKE_FUNCTIONCLASSX(2)
		MAKE_FUNCTIONCLASSX(3)
		MAKE_FUNCTIONCLASSX(4)
		MAKE_FUNCTIONCLASSX(5)
		MAKE_FUNCTIONCLASSX(6)
		MAKE_FUNCTIONCLASSX(7)
		MAKE_FUNCTIONCLASSX(8)
		MAKE_FUNCTIONCLASSX(9)
 
 		MAKE_VOID_FUNCTIONCLASSX(0)
		MAKE_VOID_FUNCTIONCLASSX(1)
		MAKE_VOID_FUNCTIONCLASSX(2)
		MAKE_VOID_FUNCTIONCLASSX(3)
		MAKE_VOID_FUNCTIONCLASSX(4)
		MAKE_VOID_FUNCTIONCLASSX(5)
		MAKE_VOID_FUNCTIONCLASSX(6)
		MAKE_VOID_FUNCTIONCLASSX(7)
		MAKE_VOID_FUNCTIONCLASSX(8)
		MAKE_VOID_FUNCTIONCLASSX(9)

	//////////////////////////////////////////////////////////////////////////

	inline int GenericFuncCallProxy(lua_State *L)
	{
		GenericFunction* func = (GenericFunction*)lua_touserdata(L, lua_upvalueindex(1));
		return func->Call(L);
	}

	inline void RegisterGlobalFunction(lua_State* L, const char* name, GenericFunction* func_class) 
	{
		CacheFunction(func_class);
		lua_pushlightuserdata(L, func_class);
		lua_pushcclosure(L, GenericFuncCallProxy, 1);
		lua_setglobal(L, name);
	}

	template<typename R>
	inline void RegisterGlobalFunction(lua_State* L, const char* name, R (*func)()) 
	{
		RegisterGlobalFunction(L, name, new FunctionClass0<R>(func));
	}

	template<typename R, typename P1>
	inline void RegisterGlobalFunction(lua_State* L, const char* name, R (*func)(P1)) 
	{
		RegisterGlobalFunction(L, name, new FunctionClass1<R, P1>(func));
	}

	template<typename R, typename P1, typename P2>
	inline void RegisterGlobalFunction(lua_State* L, const char* name, R (*func)(P1, P2)) 
	{
		RegisterGlobalFunction(L, name, new FunctionClass2<R, P1, P2>(func));
	}

	template<typename R, typename P1, typename P2, typename P3>
	inline void RegisterGlobalFunction(lua_State* L, const char* name, R (*func)(P1, P2, P3)) 
	{
		RegisterGlobalFunction(L, name, new FunctionClass3<R, P1, P2, P3>(func));
	}

	template<typename R, typename P1, typename P2, typename P3, typename P4>
	inline void RegisterGlobalFunction(lua_State* L, const char* name, R (*func)(P1, P2, P3, P4)) 
	{
		RegisterGlobalFunction(L, name, new FunctionClass4<R, P1, P2, P3, P4>(func));
	}

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
	inline void RegisterGlobalFunction(lua_State* L, const char* name, R (*func)(P1, P2, P3, P4, P5)) 
	{
		RegisterGlobalFunction(L, name, new FunctionClass5<R, P1, P2, P3, P4, P5>(func));
	}

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	inline void RegisterGlobalFunction(lua_State* L, const char* name, R (*func)(P1, P2, P3, P4, P5, P6)) 
	{
		RegisterGlobalFunction(L, name, new FunctionClass6<R, P1, P2, P3, P4, P5, P6>(func));
	}

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	inline void RegisterGlobalFunction(lua_State* L, const char* name, R (*func)(P1, P2, P3, P4, P5, P6, P7)) 
	{
		RegisterGlobalFunction(L, name, new FunctionClass7<R, P1, P2, P3, P4, P5, P6, P7>(func));
	}

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	inline void RegisterGlobalFunction(lua_State* L, const char* name, R (*func)(P1, P2, P3, P4, P5, P6, P7, P8)) 
	{
		RegisterGlobalFunction(L, name, new FunctionClass8<R, P1, P2, P3, P4, P5, P6, P7, P8>(func));
	}

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	inline void RegisterGlobalFunction(lua_State* L, const char* name, R (*func)(P1, P2, P3, P4, P5, P6, P7, P8, P9)) 
	{
		RegisterGlobalFunction(L, name, new FunctionClass9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9>(func));
	}

	//////////////////////////////////////////////////////////////////////////

	template<typename T>
	struct NullLifePolicy
	{
		static inline void OnAllocated(T* /*self*/) {}
		static inline void OnGC(T* /*self*/) {}
		static inline void OnConstructor(T* /*self*/) {}
	};

	template<typename T>
	struct CounterLifePolicy
	{
		static inline void OnAllocated(T* self) {self->OnAddRef();}
		static inline void OnGC(T* self) {self->OnRelease();}
		static inline void OnConstructor(T* self) {self->OnRelease();}
	};

	template<typename T>
	struct UserData 
	{
		UserData(T* obj): cpp_obj_(obj) {};
		~UserData() {};

		T* cpp_obj_;
	};

	struct ClassMetaData
	{
	public:
		ClassMetaData() : parent_(nullptr), meta_table_ref_(LUA_REFNIL), lua_state_(nullptr) {}
		virtual ~ClassMetaData() {}
		
		inline void ReleaseBeforeCloseLua() 
		{
			if(IsValidRef()) luaL_unref(lua_state_, LUA_REGISTRYINDEX, meta_table_ref_); meta_table_ref_=LUA_REFNIL;
		}
		inline void SetParent(ClassMetaData* parent) {parent_ = parent;}
		inline ClassMetaData* GetParent() {return parent_;}
		inline const char* GetName() {return name_.c_str();}
		inline void SetName(const char* name) {name_ = name;}
		inline bool IsValidRef() {return meta_table_ref_ != LUA_REFNIL && meta_table_ref_ != LUA_NOREF;}
		inline void PushMetaTable(lua_State* L) 
		{
			int ref = IsValidRef() ? meta_table_ref_ : LUA_REFNIL;
			lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
		}

		ClassMetaData*	parent_;
		int				meta_table_ref_;
		lua_State*		lua_state_;
		std::string		name_;

	private:
		ClassMetaData(ClassMetaData const& rhs);
		ClassMetaData& operator=(const ClassMetaData& rhs);
	};

	template<typename T, typename P = NullLifePolicy<T> >
	struct ScriptMetaClass
	{
		typedef P LifePolicy;

		inline static const char* GetName() {return meta_data_.GetName();}
		inline static void SetName(const char* name) {meta_data_.SetName(name);}
		inline static void SetParent(ClassMetaData* parent) {meta_data_.SetParent(parent);}
		inline static ClassMetaData* GetParent() {return meta_data_.GetParent();}
		inline static bool IsBuild() {return meta_data_.IsValidRef();}
		inline static ClassMetaData* GetClassMetaData() {return &meta_data_;}
		inline static void PushMetaTable(lua_State* L) {meta_data_.PushMetaTable(L);}
		inline static int PushObject(lua_State* L, T* obj)
		{
			lua_getglobal(L, "_objects");
			lua_pushlightuserdata(L, (void*)obj);
			lua_rawget(L, -2 );
			// if already exist, just get it
			if(lua_isnil(L, -1))
			{ 
				lua_pop(L, 1 );
				LifePolicy::OnAllocated(obj);

				// set metatable to userdata
				UserData<T>** ud = static_cast<UserData<T>**>(lua_newuserdata(L, sizeof(UserData<T>*)));
				*ud = new UserData<T>(obj);
				ScriptMetaClass<T>::PushMetaTable(L);
				lua_setmetatable(L, -2);

				// add userdata to _object table
				lua_pushlightuserdata(L, (void*)obj);
				lua_pushvalue(L, -2);
				lua_rawset(L, -4);
			}
			lua_remove(L, -2);

			return 1;
		}

		static ClassMetaData	meta_data_;
	};
	template<typename T, typename P > ClassMetaData ScriptMetaClass<T, P>::meta_data_;

	template<typename T>
	inline int DeleteObjectOnGC(lua_State* L)
	{
		UserData<T>* user_data = *static_cast<UserData<T>**>(luaL_checkudata(L, -1, ScriptMetaClass<T>::GetName()));
		ScriptMetaClass<T>::LifePolicy::OnGC(static_cast<T*>(user_data->cpp_obj_));
		delete (user_data);
		return 0;
	}

	template<typename T>
	inline int CallOnLuaIndex(lua_State* L)
	{
		const char* key = lua_tostring(L, 2);
		if(!PushFromMetaData(L, ScriptMetaClass<T>::GetClassMetaData(), key))
			return 0;
		return 1;
	}

	template<typename T>
	inline void RegisterClass(lua_State* L, const char* name) 
	{
		int oldTop = lua_gettop(L);

		luaL_newmetatable(L, (std::string(name)+"_meta").c_str());  // create a metatable in the registry

		lua_pushstring(L, "__index");
		lua_pushvalue(L, -2);
		lua_settable(L, -3); // metatable.__index = metatable

		lua_pushstring(L, "__gc");
		lua_pushcfunction(L, &DeleteObjectOnGC<T>);
		lua_rawset(L, -3); // metatable.__gc = DeleteObjectOnGC

		// set native flag
		lua_pushstring(L, "__is_native_class");
		lua_pushboolean(L, true);
		lua_settable(L, -3); 

		// set class name
		lua_pushstring(L, "classname");
		lua_pushstring(L, ScriptMetaClass<T>::GetName());
		lua_settable(L, -3); 
		
		// init meta data
		ScriptMetaClass<T>::SetName(name);
		ClassMetaData* meta_data = ScriptMetaClass<T>::GetClassMetaData();
		if (lua_istable(L, -1)) 
		{
			meta_data->meta_table_ref_ = luaL_ref(L, LUA_REGISTRYINDEX);
			meta_data->lua_state_ = L;
		}
		else
		{
			ERROR("can't not find lua table:%s\n", name);
		}

		//////////////////////////////////////////////////////////////////////////

		// create table for static info
		lua_newtable(L);
		//lua_pushvalue (L, -1);
		ScriptMetaClass<T>::PushMetaTable(L);
		lua_setmetatable(L, -2);

		// set static table to global
		lua_pushglobaltable(L);
		lua_pushstring(L, name);
		lua_pushvalue(L, -3);
		lua_settable(L, -3);

		// 
		lua_settop(L, oldTop);
	}

	template<typename T, typename P>
	inline void RegisterParent() 
	{
		ScriptMetaClass<T>::SetParent(ScriptMetaClass<P>::GetClassMetaData());

		lua_State* L = GetLuaState();
		ScriptMetaClass<P>::PushMetaTable(L);
		// copy parent table to child table
		lua_pushnil(L); 
		while (lua_next(L, -2) != 0)
		{
			ScriptMetaClass<T>::PushMetaTable(L);
			lua_pushvalue(L, -3); // key
			lua_pushvalue(L, -2); // value
			lua_rawset(L, -3);

			lua_pop(L, 2);
		}
	}

	template<typename T, typename P>
	inline void RegisterClass(lua_State* L, const char* name) 
	{
		//ORC_ASSERT(ScriptMetaClass<P>::IsBuild(), "%s's parent should be registered before itself", name);
		RegisterClass<T>(L, name);
		RegisterParent<T, P>();
	}

	//////////////////////////////////////////////////////////////////////////

	template<typename T>
	inline int CreateLuaUserData(lua_State *L, T* obj) 
	{
		int ret = ScriptMetaClass<T>::PushObject(L, obj);
		ScriptMetaClass<T>::LifePolicy::OnConstructor(obj);
		return ret;
	}

	template<typename T>
	inline int Constructor(lua_State *L) 
	{
		return CreateLuaUserData<T>(L, new T());
	}

	template<typename T, typename P1>
	inline int Constructor(lua_State *L) 
	{
		return CreateLuaUserData<T>(L, new T(Pop<P1>(L,1)));
	}

	template<typename T, typename P1, typename P2>
	inline int Constructor(lua_State *L) 
	{
		return CreateLuaUserData<T>(L, new T(Pop<P1>(L, 1), Pop<P2>(L, 2)));
	}

	template<typename T, typename P1, typename P2, typename P3>
	inline int Constructor(lua_State *L)
	{
		return CreateLuaUserData<T>(L, new T(Pop<P1>(L, 1), Pop<P2>(L, 2), Pop<P3>(L, 3)));
	}

	template<typename T, typename P1, typename P2, typename P3, typename P4>
	inline int Constructor(lua_State *L) 
	{
		return CreateLuaUserData<T>(L, new T(Pop<P1>(L, 1), Pop<P2>(L, 2), Pop<P3>(L, 3), Pop<P4>(L, 4)));
	}

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
	inline int Constructor(lua_State *L) 
	{
		return CreateLuaUserData<T>(L, new T(Pop<P1>(L, 1), Pop<P2>(L, 2), Pop<P3>(L, 3), Pop<P4>(L, 4), Pop<P5>(L, 5)));
	}

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	inline int Constructor(lua_State *L)
	{
		return CreateLuaUserData<T>(L, new T(Pop<P1>(L, 1), Pop<P2>(L, 2), Pop<P3>(L, 3), Pop<P4>(L, 4), Pop<P5>(L, 5), Pop<P6>(L, 6)));
	}

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	inline int Constructor(lua_State *L)
	{
		return CreateLuaUserData<T>(L, new T(Pop<P1>(L, 1), Pop<P2>(L, 2), Pop<P3>(L, 3), Pop<P4>(L, 4), Pop<P5>(L, 5), Pop<P6>(L, 6), Pop<P7>(L, 7)));
	}

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	inline int Constructor(lua_State *L)
	{
		return CreateLuaUserData<T>(L, new T(Pop<P1>(L, 1), Pop<P2>(L, 2), Pop<P3>(L, 3), Pop<P4>(L, 4), Pop<P5>(L, 5), Pop<P6>(L, 6), Pop<P7>(L, 7), Pop<P8>(L, 8)));
	}

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	inline int Constructor(lua_State *L)
	{
		return CreateLuaUserData<T>(L, new T(Pop<P1>(L, 1), Pop<P2>(L, 2), Pop<P3>(L, 3), Pop<P4>(L, 4), Pop<P5>(L, 5), Pop<P6>(L, 6), Pop<P7>(L, 7), Pop<P8>(L, 8), Pop<P9>(L, 9)));
	}

	//////////////////////////////////////////////////////////////////////////

	template<typename T>
	inline void RegisterMethod(lua_State* L, const char* name, GenericMethod* method) 
	{
		ScriptMetaClass<T>::PushMetaTable(L);

		if(lua_istable(L, -1)) 
		{
			CacheMethod(method);
			lua_pushstring(L, name);
			lua_pushlightuserdata(L, method);
			lua_pushcclosure(L, &MethodFuncCallProxy, 1);
			lua_rawset(L, -3);
		}
		else 
		{
			ERROR("please register class %s before regist method\n",  ScriptMetaClass<T>::GetName());
		}
		lua_pop(L, 1);
	}

	template<typename T>
	inline void RegisterStaticMethod(lua_State* L, const char* name, GenericFunction* func) 
	{
		ScriptMetaClass<T>::PushMetaTable(L);

		if(lua_istable(L, -1)) 
		{
			CacheFunction(func);
			lua_pushstring(L, name);
			lua_pushlightuserdata(L, func);
			lua_pushcclosure(L, &GenericFuncCallProxy, 1);
			lua_rawset(L, -3);
		}
		else 
		{
			ERROR("please register class %s before regist static method\n",  ScriptMetaClass<T>::GetName());
		}
		lua_pop(L, 1);
	}

	template<typename T>
	inline void RegisterConstructor(lua_State *L, const char* name,  int (*func) (lua_State *L)) 
	{
		ScriptMetaClass<T>::PushMetaTable(L);

		if(lua_istable(L, -1)) 
		{
			lua_pushstring(L, name);
			lua_pushcclosure(L, func, 0);
			lua_rawset(L, -3);
		}
		else 
		{
			ERROR("please register class %s before regist static method\n",  ScriptMetaClass<T>::GetName());
		}
		lua_pop(L, 1);
	}

	template<typename T, typename P>
	struct PropGetMethodClass : GenericMethod
	{
		P T::* prop_;
		PropGetMethodClass(P T::* prop): prop_(prop) {};
		~PropGetMethodClass(){};
		inline virtual int Call(lua_State *L) 
		{
			T* obj = Pop<T*>(L, 1);
			Push(L, obj->*prop_);
			return 1;
		};
	};

	template<typename T, typename P>
	struct PropSetMethodClass : GenericMethod
	{
		P T::* prop_;
		PropSetMethodClass(P T::* prop): prop_(prop) {};
		~PropSetMethodClass(){};
		inline virtual int Call(lua_State *L) 
		{
			T* obj = Pop<T*>(L, 1);
			obj->*prop_ = Pop<P>(L, 2);
			return 0;
		};
	};

	template<typename T, typename P>
	inline void RegisterProperty(lua_State* L, const char* name, P T::*prop)
	{
		RegisterMethod<T>(L, name, new PropGetMethodClass<T, P>(prop));
		RegisterMethod<T>(L, name, new PropSetMethodClass<T, P>(prop));
	}

	//////////////////////////////////////////////////////////////////////////

	inline int MethodFuncCallProxy(lua_State *L) 
	{
		GenericMethod* method = (GenericMethod*)lua_touserdata(L, lua_upvalueindex(1));
		return method->Call(L);
	}

	template<typename T, typename R>
	inline void RegisterMethod(lua_State* L, const char* name, R (T::*func)()) 
	{
		RegisterMethod<T>(L, name, new MethodClass0<R, T>(func));
	}

	template<typename T, typename R, typename P1>
	inline void RegisterMethod(lua_State* L, const char* name, R (T::*func)(P1)) 
	{
		RegisterMethod<T>(L, name, new MethodClass1<R, T, P1>(func));
	}

	template<typename T, typename R, typename P1, typename P2>
	inline void RegisterMethod(lua_State* L, const char* name, R (T::*func)(P1, P2)) 
	{
		RegisterMethod<T>(L, name, new MethodClass2<R, T, P1, P2>(func));
	}

	template<typename T, typename R, typename P1, typename P2, typename P3>
	inline void RegisterMethod(lua_State* L, const char* name, R (T::*func)(P1, P2, P3)) 
	{
		RegisterMethod<T>(L, name, new MethodClass3<R, T, P1, P2, P3>(func));
	}

	template<typename T, typename R, typename P1, typename P2, typename P3, typename P4>
	inline void RegisterMethod(lua_State* L, const char* name, R (T::*func)(P1, P2, P3, P4))
	{
		RegisterMethod<T>(L, name, new MethodClass4<R, T, P1, P2, P3, P4>(func));
	}

	template<typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
	inline void RegisterMethod(lua_State* L, const char* name, R (T::*func)(P1, P2, P3, P4, P5))
	{
		RegisterMethod<T>(L, name, new MethodClass5<R, T, P1, P2, P3, P4, P5>(func));
	}

	template<typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	inline void RegisterMethod(lua_State* L, const char* name, R (T::*func)(P1, P2, P3, P4, P5, P6))
	{
		RegisterMethod<T>(L, name, new MethodClass6<R, T, P1, P2, P3, P4, P5, P6>(func));
	}

	template<typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	inline void RegisterMethod(lua_State* L, const char* name, R (T::*func)(P1, P2, P3, P4, P5, P6, P7)) 
	{
		RegisterMethod<T>(L, name, new MethodClass7<R, T, P1, P2, P3, P4, P5, P6, P7>(func));
	}

	template<typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	inline void RegisterMethod(lua_State* L, const char* name, R (T::*func)(P1, P2, P3, P4, P5, P6, P7, P8)) 
	{
		RegisterMethod<T>(L, name, new MethodClass8<R, T, P1, P2, P3, P4, P5, P6, P7, P8>(func));
	}

	template<typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	inline void RegisterMethod(lua_State* L, const char* name, R (T::*func)(P1, P2, P3, P4, P5, P6, P7, P8, P9))
	{
		RegisterMethod<T>(L, name, new MethodClass9<R, T, P1, P2, P3, P4, P5, P6, P7, P8, P9>(func));
	}


	//////////////////////////////////////////////////////////////////////////

	template<typename T, typename R>
	inline void RegisterStaticMethod(lua_State* L, const char* name, R (*func)()) 
	{
		RegisterStaticMethod<T>(L, name, new FunctionClass0<R>(func));
	}

	template<typename T, typename R, typename P1>
	inline void RegisterStaticMethod(lua_State* L, const char* name, R (*func)(P1)) 
	{
		RegisterStaticMethod<T>(L, name, new  FunctionClass1<R, P1>(func));
	}

	template<typename T, typename R, typename P1, typename P2>
	inline void RegisterStaticMethod(lua_State* L, const char* name, R (*func)(P1, P2)) 
	{
		RegisterStaticMethod<T>(L, name, new FunctionClass2<R, P1, P2>(func));
	}

	template<typename T, typename R, typename P1, typename P2, typename P3>
	inline void RegisterStaticMethod(lua_State* L, const char* name, R (*func)(P1, P2, P3)) 
	{
		RegisterStaticMethod<T>(L, name, new FunctionClass3<R, P1, P2, P3>(func));
	}

	template<typename T, typename R, typename P1, typename P2, typename P3, typename P4>
	inline void RegisterStaticMethod(lua_State* L, const char* name, R (*func)(P1, P2, P3, P4))
	{
		RegisterStaticMethod<T>(L, name, new FunctionClass4<R, P1, P2, P3, P4>(func));
	}

	template<typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
	inline void RegisterStaticMethod(lua_State* L, const char* name, R (*func)(P1, P2, P3, P4, P5))
	{
		RegisterStaticMethod<T>(L, name, new FunctionClass5<R, P1, P2, P3, P4, P5>(func));
	}

	template<typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	inline void RegisterStaticMethod(lua_State* L, const char* name, R (*func)(P1, P2, P3, P4, P5, P6))
	{
		RegisterStaticMethod<T>(L, name, new FunctionClass6<R, P1, P2, P3, P4, P5, P6>(func));
	}

	template<typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	inline void RegisterStaticMethod(lua_State* L, const char* name, R (*func)(P1, P2, P3, P4, P5, P6, P7)) 
	{
		RegisterStaticMethod<T>(L, name, new FunctionClass7<R, P1, P2, P3, P4, P5, P6, P7>(func));
	}

	template<typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	inline void RegisterStaticMethod(lua_State* L, const char* name, R (*func)(P1, P2, P3, P4, P5, P6, P7, P8)) 
	{
		RegisterStaticMethod<T>(L, name, new FunctionClass8<R, P1, P2, P3, P4, P5, P6, P7, P8>(func));
	}

	template<typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	inline void RegisterStaticMethod(lua_State* L, const char* name, R (*func)(P1, P2, P3, P4, P5, P6, P7, P8, P9))
	{
		RegisterStaticMethod<T>(L, name, new FunctionClass9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9>(func));
	}


	//////////////////////////////////////////////////////////////////////////

	static std::vector<GenericFunction*>	gCachedFunctions;
	static std::vector<GenericMethod*>		gCachedMethods;
	static std::vector<ClassMetaData*>		gCachedMetaDatas;

	inline static void CacheMethod(GenericMethod* method)
	{
		gCachedMethods.push_back(method);
	}

	inline static void CacheFunction(GenericFunction* function)
	{
		gCachedFunctions.push_back(function);
	}

	inline static void CacheClassMetaData(ClassMetaData* data)
	{
		gCachedMetaDatas.push_back(data);
	}

	inline static void ReleaseAllCaches()
	{
		for (auto itr = gCachedFunctions.begin(); itr != gCachedFunctions.end(); ++itr) 
			delete *itr;
		gCachedFunctions.clear();

		for (auto itr = gCachedMethods.begin(); itr != gCachedMethods.end(); ++itr) 
			delete *itr;
		gCachedMethods.clear();

		for (auto itr = gCachedMetaDatas.begin(); itr != gCachedMetaDatas.end(); ++itr)
			(*itr)->ReleaseBeforeCloseLua();
		gCachedMetaDatas.clear();
	}

}

#endif // __SCRIPTBIND_LUA_LUACLASSBINDER_H__