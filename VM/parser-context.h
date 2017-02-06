#ifndef PARSER_CONTEXT_H
#define PARSER_CONTEXT_H
#include <string.h>

struct Tree;
struct TreeLog;
struct MemoEntry;

// typedef unsigned long int symbol_t;
typedef char* symbol_t;

typedef struct ParserContext {
  const unsigned char  *inputs;
  size_t length;
  const unsigned char  *pos;
  struct Tree *left;
  // AST
  struct TreeLog *logs;
  size_t log_size;
  size_t unused_log;
  // stack
  struct Wstack  *stacks;


  size_t stack_size;
  size_t unused_stack;
  size_t fail_stack;
  // SymbolTable
  struct SymbolTableEntry* tables;
  size_t tableSize;
  size_t tableMax;
  size_t stateValue;
  size_t stateCount;
  unsigned long int count;
  // Memo
  struct MemoEntry *memoArray;
  size_t memoSize;
  // APIs
  void *thunk;
  void* (*fnew)(symbol_t, const unsigned char *, size_t, size_t, void *);
  void (*fsub)(void *, size_t, symbol_t, void *, void *);
  void (*fgc)(void *, int, void*);
} ParserContext;

#endif
