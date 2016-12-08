#include <stdio.h>
#include <string.h>

#include "cnez-runtime.h"
#include "vm.h"


const unsigned char *text;
int main(int argc, char const *argv[]) {
  int count=0;
//for matching//
  char strs[8][10]={"Byte","47","48","byte"};
  char nstrs[8][10]={"bool"};
  char rstrs[8][10]={"bool"};
  char ostrs[8][10]={"option"};
  char sets[8][256]={0};
  sets[0][(int)'b']=1;
  sets[0][(int)'B']=1;
  sets[1][(int)'Z']=1;

  char rsets[8][256]={0};
  rsets[0][(int)'n']=1;
  rsets[0][(int)'N']=1;

  for(int i=(int)'A'; i<(int)'z'; i++) {
    rsets[0][i]=1;
  }


  char nsets[8][256]={0};
  nsets[0][(int)'x']=1;
  nsets[0][(int)'X']=1;
  char osets[8][256]={0};
  osets[0][(int)'p']=1;
  osets[0][(int)'P']=1;

  char inputtext[20];
//for Trees//
  static symbol_t tags[8]={"Byte","Num","Start","Mul","Div","Tree","Int","File"};
  static symbol_t labels[8]={"left","right"};

  const unsigned char replaces[8][10]={"true"};
  static symbol_t table[8]={"NAME","T1","T2"};
  static symbol_t table2[8]={"NAME","T1","T2"};

  const unsigned char symbol[8][8]={"a","aa","aaa"};



  printf("Please input text.\n");

  gets(inputtext);
  text = inputtext;       //input string
  ParserContext *pc = ParserContext_new(text,strlen(text));
  ParserContext_initTreeFunc(pc,NULL,NULL,NULL,NULL);
  initVM(pc);




  int instsSize = 100;
  Instruction *inst = malloc(sizeof(*inst) * instsSize);
  VM_Context *ctx = malloc(sizeof(*ctx));
  ctx->inst = inst;
  ctx->instSize = instsSize;
  ctx->ctx = pc;
  // Instruction *head = inst;
  parse(ctx);




  // Calc = (Int){$left  op  $right(Int)#Tree}*
  // op='*' #Mul /'/' #Div
  //
  // Int ={('1'/'2')#Int}
  // inst->op=Call;
  // inst->arg=2;
  // inst++;
  // inst->op=Jump;
  // inst->arg=;
  // inst++;
  // inst->op=Alt;
  // inst->arg=;
  // inst++;
  // inst->op=TFold;
  // inst->arg=;
  // inst++;
  // inst->op=Alt;
  // inst->arg=;
  // inst++;
  // inst->op=Byte;
  // inst->arg=;
  // inst++;
  // inst->op=TTag;
  // inst->arg=;
  // inst++;
  // inst->op=Succ;
  // inst->arg=;
  // inst++;
  // inst->op=TPush;
  // inst++;
  //



//A = { $left({'Byte' #Byte }) ' ' $right({'(47'/'48)' #Num }) #Start }
//         inst->op=TBegin;
//         inst->arg=0;
//         inst++;
//         inst->op=TPush;
//         inst++;
//         inst->op=Str;
//         inst->arg=0;//str[0]=Byte
//         inst++;
//         inst->op=TBegin;
//         inst->arg=-4;
//         inst++;
//         inst->op=TEnd;
//         inst->arg=0;
//         inst++;
//         inst->op=TEnd;
//         inst->arg=0; //tag[0]=Byte
//         inst++;
//         inst->op=TLink;
//         inst->arg=0; //label[0]=left
//         inst++;
//         inst->op=Byte;
//         inst->arg=32;
//         inst++;
//         inst->op=TPush;
//         inst++;
//         inst->op=TBegin;
//         inst->arg=0;
//         inst++;
//
// //10
//
//         inst->op=Alt;
//         inst->arg=20;
//         inst++;
//         inst->op=Str;
//         inst->arg=1;//Str[1]=47
//         inst++;
//         inst->op=Succ;
//         inst++;
//
//         inst->op=TEnd;
//         inst->arg=0;
//         inst++;
//         inst->op=TEnd;
//         inst->arg=1;//tags[1]=Num
//         inst++;
//         inst->op=TLink;
//         inst->arg=1;
//         inst++; //label[1]=right
//         inst->op=TEnd;
//         inst->arg=0;
//         inst++;
//         inst->op=TEnd;
//         inst->arg=2;//tags[2]=Start
//         inst++;
//         inst->op=Ret;
//         inst++;
//
//         inst->op=Str;
//         inst->arg=2;//str[2]=48
//         inst++;
// //20
//         inst->op=Jump;
//         inst->arg=14;
//         inst++;

// Calc = (Int){$left  op  $right(Int)}*
// op='*' #Mul /'/' #Div
//
// Int ={('1')#Int}
//
// inst->op=Call;
// inst->arg=3;
// inst++;
// inst->op=Jump;
// inst->arg=23;
// inst++;
// inst->op=Alt;
// inst->arg=21;
// inst++;
// inst->op=TFold;
// inst->arg=0;
// inst++;
// inst->op=TFold;//labels[0]=left
// inst->arg=0;
// inst++;
// inst->op=Alt;
// inst->arg=18;
// inst++;
// inst->op=Byte;
// inst->arg=42;
// inst++;
// inst->op=TTag;
// inst->arg=3;
// inst++;
// inst->op=Succ;
// inst++;
// inst->op=TPush;
// inst++;
// //10
// inst->op=Call;
// inst->arg=13;
// inst++;
//
// inst->op=Jump;
// inst->arg=23;
// inst++;
// inst->op=TLink;
// inst->arg=1;//labels[1]=right
// inst++;
//
// inst->op=TEnd;
// inst->arg=0;
// inst++;
// inst->op=TEnd;
// inst->arg=-1;
// inst++;
// inst->op=Step;
// inst++;
// inst->op=Jump;
// inst->arg=4;
// inst++;
// inst->op=Byte;
// inst->arg=47;
// inst++;
// inst->op=TTag;
// inst->arg=4;
// inst++;
// inst->op=Jump;
// inst->arg=10;
// inst++;
//
// //20
// inst->op=Byte;
// inst->arg=97;
// inst++;
// inst->op=Ret;
// inst++;
// inst->op=Byte;
// inst->arg=49;
// inst++;
//
// inst->op=TBegin;
// inst->arg=-1;
// inst++;
// inst->op=TEnd;
// inst->arg=0;
// inst++;
// inst->op=TEnd;
// inst->arg=6;
// inst++;
// inst->op=Ret;
// inst++;

  // START = <symbol NAME> S <symbol NAME> <is NAME> !.
  // NAME = 'A'+
  // S = [ ]+


//         File = { <block <symbol T1> <symbol T2 >> !<exists T1> !<exists T2> 'c' #File}
// T1 = 'a'
// T2 = 'b'
//
//
// inst->op=TBegin;
// inst->arg=0;
// inst++;
// inst->op=SOpen;
// inst++;
// inst->op=Pos;
// inst++;
// inst->op=Byte;
// inst->arg=97;
// inst++;
// inst->op=SDef;
// inst->arg=1;
// inst++;
// inst->op=Pos;
// inst++;
// inst->op=Byte;
// inst->arg=98;
// inst++;
// inst->op=SDef;
// inst->arg=2;
// inst++;
// inst->op=SClose;
// inst++;
// inst->op=Alt;
// inst->arg=14;
// inst++;
// //10
//
// inst->op=SExists;
// inst->arg=1;
// inst++;
// inst->op=Succ;
// inst++;
// inst->op=Fail;
// inst++;
// inst->op=Alt;
// inst->arg=18;
// inst++;
// inst->op=SExists;
// inst->arg=2;
// inst++;
// inst->op=Succ;
// inst++;
// inst->op=Fail;
// inst++;
// inst->op=Byte;
// inst->arg=99;
// inst++;
// inst->op=TEnd;
// inst->arg=0;
// inst++;
// inst->op=TEnd;
// inst->arg=7;
// inst++;
// //20
//
// inst->op=Ret;
// inst++;

  // File =  <symbol T1> <symbol T2 > <exists T1 'a'> <exists T2> 'c' #File
  // T1 = 'a'+
  // T2 = 'b'*
  // inst->op=Pos;
  // inst++;
  // inst->op=Byte;
  // inst->arg=97;
  // inst++;
  // inst->op=RByte;
  // inst->arg=97;
  // inst++;
  // inst->op=SDef;
  // inst->arg=1;
  // inst++;
  // inst->op=Pos;
  // inst++;
  // inst->op=RByte;
  // inst->arg=98;
  // inst++;
  // inst->op=SDef;
  // inst->arg=2;
  // inst++;
  // inst->op=SIsDef;
  // inst->arg=1;
  // inst++;
  // inst->op=SIsDef;
  // inst->arg=2;
  // inst++;
  // inst->op=SExists;
  // inst->arg=2;
  // inst++;
  // inst->op=Byte;
  // inst->arg=99;
  // inst++;
  // inst->op=TTag;
  // inst->arg=7;
  // inst++;
  // inst->op=Ret;
  // inst++;
}
//
// typedef struct Wstack {
//  size_t value;
//  struct Tree *tree;
// } Wstack;
// struct Wstack  *stacks;
// size_t          stack_size;
// size_t          unused_stack;
// size_t          fail_stack;
