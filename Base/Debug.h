#ifndef __CORE_BASE_DEBUG_H__
#define __CORE_BASE_DEBUG_H__


namespace Aurora
{
	bool __assert_a(const char* file, const char* function, unsigned int line, const char* format, ...);
	void __trace_a(const char* format, ...);

#ifdef _DEBUG
	#define ASSERTA(CONDITION, FORMAT, ...) {(!!(CONDITION) || Aurora::__assert_a(__FILE__, __FUNCTION__, __LINE__, FORMAT, ##__VA_ARGS__));}
	#define TRACEA(FORMAT, ...) Aurora::__trace_a(FORMAT, ##__VA_ARGS__)
#else
    #define ORC_ASSERTA(CONDITION, FORMAT, ...) 
	#define ORC_TRACEA(FORMAT, ...)
#endif


#define ASSERT ASSERTA
#define	TRACE TRACEA
#define ERROR(FORMAT, ...) ASSERTA(false, FORMAT, ##__VA_ARGS__)

}



#endif //__CORE_BASE_DEBUG_H__
