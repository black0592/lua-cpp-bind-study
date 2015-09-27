#include <stdarg.h>
#include <stdio.h>
#include <Windows.h>
#include "Debug.h"

namespace Aurora
{

// 	void __trace_w( const wchar_t* format, ... )
// 	{
// 		wchar_t* buf = new wchar_t[1024];  
// 		if(NULL == buf) return;
// 
// 		va_list args;   
// 		va_start(args, format);  
// 		ORC_VSPRINTFW(buf, 1024, format, args);
// 		va_end(args);
// 
// 		PrintConsoleW(buf);
// 		
// 		delete[] buf;
// 	}

	void __trace_a( const char* format, ... )
	{
// 		static char buf[1024];  
// 
// 		va_list args;   
// 		va_start(args, format);  
// #ifdef _WIN32
// 		vsprintf(buf, format, args);
// #else
// 		vsnprintf(buf, 1024, format, args); 
// #endif
// 		va_end(args);

		//PrintConsoleA(buf);
	}

	void __custom_assert(const char* description, unsigned int line, const char* function, const char* file/*, bool* bIgnoreAlways*/ )
	{
		static char temp_t[1024] = {0};
//		std::string temp_a;
// 	#if (ORC_ENCODE == ORC_UNICODE)
// 		std::wstring temp0;
// 		str_2_wstr(temp0, function);
// 		const char_t* tfunction = temp0.c_str();
// 
// 		std::wstring temp1;
// 		str_2_wstr(temp1, file);
// 		const char_t* tfile = temp1.c_str();
// 		ORC_SPRINTFW(temp_t, L"\n所在文件: %s\n所在函数: %s\n所在行数: %d\n错误信息: %s", tfile, tfunction, line, description); 
// 		wstr_2_str(temp_a, temp_t);
// 	#else
		sprintf(temp_t, "\nat file: %s\nat function: %s\nat line: %d\nerror: %s\n", file, function, line, description); 
//		temp_a = temp_t;
//	#endif

		::MessageBoxA(nullptr, temp_t, "assert failed!", MB_OK);
        
		_asm
		{
			int 3;
		}
	}

	bool __assert_a(const char* file, const char* function, unsigned int line, const char* format, ...)
	{
		static char buf[1024];

		va_list args;   
		va_start(args, format);  
		vsprintf(buf, format, args);   
		va_end(args);

		// #if ORC_ENCODE == ORC_UNICODE
		// 			string_t dest;
		// 			str_2_wstr(dest, buf);
		// 			__custom_assert(dest.c_str(), line, function, file/*, &bIgnoreAlways*/);
		// #else
		__custom_assert(buf, line, function, file/*, &bIgnoreAlways*/);
		//#endif
		return true;
	}

// 	bool __assert_w(const char* file, const char* function, unsigned int line, const wchar_t* format, ...)
// 	{
// 		if(!gIgnoreAlways)
// 		{
// 			wchar_t* buf = new wchar_t[1024];  
// 			if(NULL == buf) return false;
// 
// 			va_list args;   
// 			va_start(args, format);
//             wprintf(buf, format, args);
// 			va_end(args);
// 
// #if ORC_ENCODE != ORC_UNICODE
// 			string_t dest;
// 			wstr_2_str(dest, buf);
// 			__custom_assert(dest.c_str(), line, function, file/*, &bIgnoreAlways*/);
// #else
// 			__custom_assert(buf, line, function, file/*, &bIgnoreAlways*/);
// #endif
// 			delete buf;
// 		}
// 		return true;
// 	}

}





