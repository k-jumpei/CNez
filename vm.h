#ifndef VM_H
#define VM_H
#include <stdlib.h>
#include "parser-context.h"

enum nezvm_opcode {
  Byte,
  NByte,
  RByte,
  OByte,

  Set,
  RSet,
  NSet,
  OSet,

  Str,
  RStr,
  NStr,
  OStr,
  NAny,
  Any,

  TBegin,
  TTag,
  TLink,
  TReplace,
  TFold,
  TEnd,
  TPush,
  TPop,

  Nop,
  Exit,
  Alt,
  Succ,
  Jump,
  Ret,
  Back,
  Pos,
  Move,
  Call,
  Step,
  False,
  True,
  Fail,

  SOpen,
  SClose,
  SDef,
  SIs,
  SIsa,
  SExists,
  SMask,
  SMatch,
  SIsDef


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
void print_stack(Wstack s);
void print_stack2(ParserContext *pc);

#endif
