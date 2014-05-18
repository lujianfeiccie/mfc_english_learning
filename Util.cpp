#include "StdAfx.h"
#include "Util.h"
Util::Util(void)
{
}
Util::~Util(void)
{
}
void __cdecl Util::LOG(const char* fmt, ...)
{
    char buf[4096], *p = buf;
    va_list args;
 
 
    va_start(args, fmt);
    p += vsnprintf_s(p, sizeof(buf), _TRUNCATE, fmt, args);
    va_end(args);
 
 
    while ( p > buf && isspace(p[-1]) )
        *--p = '\0';
    *p++ = '\r';
    *p++ = '\n';
    *p = '\0';
 
 
    OutputDebugStringA(buf); //output as ANSI string //OutputDebugString
}  