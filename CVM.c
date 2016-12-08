#include <stdio.h>
#include <string.h>
#define CNEZ_NOGC  1

#include "cnez-runtime.h"
#include "vm.h"
#define LABEL(OP) case OP:
#define NEXT break;
#define FAIL() goto L_fail
#define Bottom -1 //Stackbottom//
// typedef struct Instruction {
//   unsigned short op;
//   int arg;
//
// } Instruction;
//

int main(int argc, char const *argv[]) {
  int catchstacktop=0;
  int usedstacktop=0;
//for matching//
  char strs[8][10]={"Byte","47","48"};
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
  static symbol_t tags[8]={"Byte","Num","Start"};
  static symbol_t labels[8]={"left","right"};

  const unsigned char replaces[8][10]={"true"};
  static symbol_t table[8]={"B","right"};

  symbol_t *p="Var";
  size_t val;


  printf("Please input text.\n");
  gets(inputtext);
  const unsigned char *text = inputtext; //input string
  ParserContext *pc = ParserContext_new(text, 50);
  ParserContext *stack = ParserContext_new(text, 50);
  ParserContext *stacktree = ParserContext_new(text, 50);
  ParserContext *stacksymbol = ParserContext_new(text, 50);

  ParserContext_initTreeFunc(pc,NULL,NULL,NULL,NULL);

  push(pc,Bottom);


  int instsSize = 30;
  Instruction *inst = malloc(sizeof(*inst) * instsSize);
  Instruction *head = inst;

  //delete later(Memo)
  //ParserContext_beginTree(ParserContext *c, int shift)
  //ParserContext_tagTree(ParserContext *c, symbol_t tag)
  //ParserContext_valueTree(ParserContext *c, const unsigned char *text, size_t len)
  // ParserContext_linkTree(ParserContext *c, symbol_t label)
  //ParserContext_foldTree(ParserContext *c, int shift, symbol_t label)
  //ParserContext_endTree(ParserContext *c, int shift, symbol_t tag, const unsigned char *text, size_t len)

  // Calc = (Int){$left  op  $right(Int)}*
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

  inst->op=TBegin;
  inst->arg=0;
  inst++;
  inst->op=TPush;
  inst++;
  inst->op=Str;
  inst->arg=0;//str[0]=Byte
  inst++;
  inst->op=TBegin;
  inst->arg=-4;
  inst++;
  inst->op=TEnd;
  inst->arg=0;
  inst++;
  inst->op=TEnd;
  inst->arg=0; //tag[0]=Byte
  inst++;
  inst->op=TLink;
  inst->arg=0; //label[0]=left
  inst++;
  inst->op=Byte;
  inst->arg=32;
  inst++;
  inst->op=TPush;
  inst++;
  inst->op=TBegin;
  inst->arg=0;
  inst++;

//10

  inst->op=Alt;
  inst->arg=20;
  inst++;
  inst->op=Str;
  inst->arg=1;//Str[1]=47
  inst++;
  inst->op=Succ;
  inst++;

  inst->op=TEnd;
  inst->arg=0;
  inst++;
  inst->op=TEnd;
  inst->arg=1;//tags[1]=Num
  inst++;
  inst->op=TLink;
  inst->arg=1;
  inst++; //label[1]=right
  inst->op=TEnd;
  inst->arg=0;
  inst++;
  inst->op=TEnd;
  inst->arg=2;//tags[2]=Start
  inst++;
  inst->op=Ret;
  inst++;

  inst->op=Str;
  inst->arg=2;//str[2]=48
  inst++;
//20
  inst->op=Jump;
  inst->arg=14;
  inst++;


  inst=head-1;


  for (int i = 0; i < instsSize; i++) {
Jump:
    switch ((++inst)->op) {
      LABEL(Byte) {
        if(ParserContext_prefetch(pc)!=inst->arg||ParserContext_eof(pc)) {
          printf("Byte");
          FAIL();
        }else
          printf("Byte Success");
        ParserContext_move(pc,1);

        printf("%c\n", inst->arg);
        NEXT;
      }

      LABEL(Str){
        if(ParserContext_match(pc,strs[inst->arg],(int)strlen(strs[inst->arg]))) {
          printf("Str Success\n");
          NEXT;
        }else{  printf("Str");
                FAIL(); }

      }
      LABEL(Set){

        if(sets[inst->arg][(int)ParserContext_read(pc)]) {
          printf("Set Success\n");
          NEXT;
        }
        printf("Set");
        FAIL();
      }
      LABEL(Any) {
        if(!ParserContext_eof(pc)) {
          ParserContext_move(pc,1);
          printf("Any Success\n");
          NEXT;
        }
        printf("Any \n");
        FAIL();

      }
      LABEL(NByte){
        if(ParserContext_prefetch(pc)==inst->arg||ParserContext_eof(pc)) {
          printf("NByte");
          FAIL();
        }else{
          ParserContext_move(pc,1);
          printf("NByte Success\n");
          NEXT;
        }
      }
      LABEL(NStr){
        if(ParserContext_match(pc,nstrs[inst->arg],(int)strlen(nstrs[inst->arg]))||ParserContext_eof(pc)) {

          printf("NStr");
          FAIL();
        }else{
          printf("NStr Success\n");
          printf("%c",ParserContext_prefetch(pc));

          NEXT;
        }
      }

      LABEL(NSet){
        if ((nsets[inst->arg][(int)ParserContext_prefetch(pc)])||ParserContext_eof(pc)) {
          printf("NSet\n");
          FAIL();

        }
        printf("NSetSuccess\n");

        ParserContext_move(pc,1);
        NEXT;
      }

      LABEL(NAny){
        if(ParserContext_eof(pc)) {
          printf("NAny Success\n");
          NEXT;
        }
        printf("NAny");
        FAIL();
      }

      LABEL(RByte){

        while(ParserContext_prefetch(pc)==inst->arg) {
          printf("RByte Success\n");

          ParserContext_move(pc,1);
        }

        NEXT;
      }

      LABEL(RStr){
        while(ParserContext_match(pc,rstrs[inst->arg],(int)strlen(rstrs[inst->arg]))) {
          printf("RStr Success\n");
        }
        NEXT;

      }
      LABEL(RSet){

        while(rsets[inst->arg][(int)ParserContext_prefetch(pc)]) {
          printf("RSetSuccess\n");


          ParserContext_move(pc,1);
        }
        NEXT;
      }
      LABEL(OByte){
        if(ParserContext_prefetch(pc)==inst->arg) {
          if(inst->arg==0) {
            NEXT;
          }
          printf("OByte Success\n");
          ParserContext_move(pc,1);
        }else{
          printf("OByte Through\n");
        }
        NEXT;
      }
      LABEL(OStr){
        printf("%c\n",*(pc->pos));

        if(ParserContext_match(pc,ostrs[inst->arg],(int)strlen(ostrs[inst->arg]))) {
          printf("OStr Success\n");
        }else{
          printf("OStr Through\n");       //for debug
        }
        printf("%c",*(pc->pos-1));
        NEXT;


      }
      LABEL(OSet){
        if(osets[inst->arg][ParserContext_prefetch(pc)])  //&& sc.eof()
        {  printf("OSet Success\n");
           ParserContext_move(pc,1); }else{
          printf("OSet Through\n");       //for debug
        }

        NEXT;

      }
      LABEL(TBegin)  //ParserContext_beginTree(ParserContext *c, int shift)
      {
        printf("TBegin Success\n");
        ParserContext_beginTree(pc,inst->arg);
        DEBUG_dumplog(pc);


        NEXT;

      }
      LABEL(TTag)  //ParserContext_tagTree(ParserContext *c, symbol_t tag)
      {
        printf("TTag Success\n");
        ParserContext_tagTree(pc,tags[inst->arg]);
        DEBUG_dumplog(pc);


        NEXT;
      } LABEL(TReplace) //ParserContext_valueTree(ParserContext *c, const unsigned char *text, size_t len)
      {
        int work;
        work=inst->arg;
        inst++;
        printf("work=%d",work);
        printf("arg=%d",inst->arg);

        printf("TReplace Success\n");


        ParserContext_valueTree(pc,replaces[work],inst->arg);
        DEBUG_dumplog(pc);

        NEXT;
      }
      LABEL(TLink)  // ParserContext_linkTree(ParserContext *c, symbol_t label)
      {
        printf("TLink Success\n");
        ParserContext_linkTree(pc,labels[inst->arg]);
        DEBUG_dumplog(pc);
        NEXT;

      } LABEL(TFold) //ParserContext_foldTree(ParserContext *c, int shift, symbol_t label)
      {
        int work;
        work=inst->arg;
        inst++;
        printf("TFold Success\n");

        ParserContext_foldTree(pc,work,labels[inst->arg]);
        DEBUG_dumplog(pc);
        NEXT;


      }

      LABEL(TEnd)  //ParserContext_endTree(ParserContext *c, int shift, symbol_t tag, const unsigned char *text, size_t len)
      {
        int work;
        work=inst->arg;
        inst++;

        printf("TEnd Success\n");



        ParserContext_endTree(pc,work,tags[inst->arg],NULL,0);


        DEBUG_dumplog(pc);
        cnez_dump(pc->left, stdout);

        NEXT;

      }
      LABEL(Nop)
      {
        printf("Nop Success\n");
        NEXT;
      }
      LABEL(Exit){
        fprintf(stderr, "exit error%d\n", inst->arg);
        exit(1);
        NEXT;
      }
      LABEL(Alt){
        printf("Alt Success\n");
        push(pc,inst->arg);
        NEXT;
      } LABEL(Succ){
        printf("Succ Success\n");

        popW(pc);

        NEXT;
      } LABEL(Jump){
        printf("Jump Success\n");
        inst=head+(inst->arg)-2;
        NEXT;
      } LABEL(Ret){
        printf("Ret Success\n");
        return 0;
        NEXT;

      }
      LABEL(Pos){
        printf("Pos Success\n");
        push(stack,pc->pos);
        NEXT;
      }
      LABEL(Back){
        printf("Back Success\n");
        ParserContext_back(pc,popW(stack)->value);
        NEXT;
      }
      LABEL(Move){
        printf("Move Success\n");
        ParserContext_move(pc,inst->arg);
        NEXT;
      } LABEL(TPush){
        printf("Tpush Success\n");
        pushW(stacktree,ParserContext_saveLog(pc),pc->left);
        NEXT;


      } LABEL(TPop){
        printf("Tpop Success\n");
        Wstack *work=popW(stacktree);
        pc->left=work->tree;
        ParserContext_backLog(pc,work->value);
        NEXT;
      }
      // LABEL(SOpen){
      //   printf("SOpen Success\n");
      //   push(stacksymbol,ParserContext_saveSymbolPoint(pc));
      //   NEXT;
      //
      // }LABEL(SClose){
      //   printf("SClose Success\n");
      //   backSymbolPoint(stacksymbol,);
      // ParserContext_backSymbolPoint(ParserContext *c, int savePoint)

      //   push(stacksymbol,ParserContext_saveSymbolPoint(pc));
      //
      // }
      //   LABEL(SDef){
      //     printf("SDef Success\n");
      //     ParserContext_addSymbol(pc,table[inst->arg],popW(pc)->value);
      //     NEXT;
      //   }
      //   LABEL(SExists){
      //     printf("SExists Success\n");
      //     ParserContext_addSymbol(pc,table[inst->arg],popW(pc)->value);
      //     NEXT;
      //   ParserContext_existsSymbol(pc,)
      //   }
      //   LABEL(SIs){
      //     printf("SDIs Success\n");
      //   if(ParserContext_equals(pc,table[inst->arg],popW(pc)->value))
      //   {NEXT;
      //   }else {
      //     FAIL();
      //   }
      // }
      //
      //   LABEL(SMatch){
      //     printf("SMatch Success\n");
      //   if(ParserContext_matchSymbol(pc,table[inst->arg]))
      //   {
      //     NEXT;
      //   }else {
      //     FAIL();
      //   }LABEL(SIsa){
      //     printf("SIsa Success\n");
      //   if(ParserContext_contains(pc,table[inst->arg]))
      //   {
      //     NEXT;
      //   }else {
      //     FAIL();
      //   }
      // }LABEL(SMask){
      //
      // }LABEL(SIsDef){
      //   printf("SIsDef\n");
      //
      //   //(ParserContext *c, symbol_t table, const unsigned char *symbol, size_t length)
      // if(ParserContext_existsSymbol(pc,table[inst->arg]))
      // {
      //   NEXT;
      // }else {
      //   FAIL();
      // }

      // LABEL(Call){
      //   printf("Call Success\n");
      //   push(pc,inst->arg);
      //   NEXT;
      //
      // }LABEL(Fail){
      //   printf("Call Success\n");
      //
      //
      // }








    }
  }
  return 0;
L_fail:

  val=((popW(pc))->value);

  if(val==Bottom) {

    printf("fail\n");
  }
  else{
    printf(" Fail and Jump\n");

    inst=head+val-2;
    goto Jump;
  }
}
