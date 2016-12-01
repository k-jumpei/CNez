#ifndef VM_H
#define VM_H

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

  Nop,
  Exit,
  Alt,
  Succ,
  Jump,
  Ret,
  Back,
  Pos,
  Move,
  TPush,
  TPop,
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

void initVM(ParserContext *pc);
void print_stack(Wstack s);
void print_stack2(ParserContext *pc);

#endif
