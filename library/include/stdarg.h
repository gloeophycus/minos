#ifndef STDARG_H
#define STDARG_H

typedef int __gnu_va_list;
typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;

#define va_start(v, l) __builtin_va_start(v, l)
#define va_end(v) __builtin_va_end(v)
#define va_arg(v, l) __builtin_va_arg(v, l)

int vsprintf(char *buffer, const char *string, va_list ap);

#endif