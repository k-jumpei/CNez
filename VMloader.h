#ifndef VMloader_H
#define VMloader_H
#include <stdio.h>
#include <string.h>
typedef char *symbol_t;
#define _Op ((symbol_t)1)
#define _Ops ((symbol_t)2)
#define MAXTAG 3
#define _opname ((symbol_t)1)
#define _args ((symbol_t)2)
#define _arg ((symbol_t)3)
#define MAXLABEL 4
void* VMloader_parse(const char *text, size_t len, void *, void* (*fnew)(symbol_t, const char *, size_t, size_t, void *), void  (*fset)(void *, size_t, symbol_t, void *, void *), void  (*fgc)(void *, int, void *));
long VMloader_match(const char *text, size_t len);
const char* VMloader_tag(symbol_t n);
const char* VMloader_label(symbol_t n);
#endif
