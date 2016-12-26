#ifndef VM_H
#define VM_H
#include <stdlib.h>
#include "parser-context.h"
#include "cnez-runtime.h"

static char strs[64][32]={"\0"};
static char nstrs[64][32]={"\0"};
static char rstrs[64][32]={"\0"};
static char ostrs[64][32]={"\0"};
static char sets[64][256]={0};
static char rsets[64][256]={0};
static char nsets[64][256]={0};
static char osets[64][256]={0};
static char tags[64][16]={"\0"};
static char labels[64][16]={"\0"};
static char replaces[64][16]={"\0"};
static char table[64][16]={"\0"};
static char table2[64][16]={"\0"};
static char symbol[64][8]={"\0"};


enum nezvm_opcode {
  Byte,//0
  NByte,
  RByte,
  OByte,

  Str,
  NStr,
  RStr,
  OStr,

  Set,
  NSet,
  RSet,//10
  OSet,

  NAny,
  Any,

  TBegin,
  TTag,
  TLink,
  TReplace,
  TFold,
  TEnd,
  TPush,//20
  TPop,

  Nop,
  Exit,
  Alt,
  Succ,
  Jump,
  Ret,
  Back,
  Pos,
  Move,//30
  Call,
  Step,
  True,
  False,
  Fail,

  SOpen,
  SClose,
  SDef,
  SIs,
  SIsa,
  SExists,
  SMask,
  SMatch,
  SIsDef,
Lookup,
Lookup2,
Memo,
MemoFail,
TLookup,
TLookup2,
TMemo
  // SMask,

};

typedef struct Instruction {
  uint8_t op;
  int arg;

} Instruction;

typedef struct VM_Context {
  Instruction* inst;
  int instSize;
  ParserContext *ctx;

} VM_Context;

void initVM(ParserContext *pc);
// void print_stack(Wstack s);
// void print_stack2(ParserContext *pc);

#endif
