#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "vm.h"

#define CNEZ_NOGC  1

#define LABEL(OP) case OP:
#define NEXT break;
#define FAIL() goto L_fail
#define Bottom -100 //Stackbottom//

size_t val;
const unsigned char *text;
int count=0;

int main (int argc,char* argv[]){
  VM_Context *vm_ctx= malloc(sizeof(*vm_ctx));
  vm_ctx->instSize = 200;
  char inputtext[20];

  printf("Please input text.\n");
  gets(inputtext);
  text = inputtext;
  vm_ctx->ctx= ParserContext_new(text,strlen(text));
  initVM(vm_ctx->ctx);
  parse(vm_ctx,argv[1]);


}

int prepare(Instruction *inst, Instruction* head,char* p) {
  int instSize=0;
  inst=head-2;
  inst->op=False;
  inst++;
  inst->op=True;
  inst++;
  instSize=loadinst(inst,p);
  // inst->op=Pos;
  // inst++;
  // inst->op=Byte;
  // inst->arg=65;
  // inst++;
  // inst->op=RByte;
  // inst->arg=65;
  // inst++;
  // inst->op=SDef;
  // inst->arg=0;
  // inst++;
  // inst->op=Byte;
  // inst->arg=32;
  // inst++;
  // inst->op=RByte;
  // inst->arg=32;
  // inst++;
  // inst->op=Pos;
  // inst++;
  // inst->op=Byte;
  // inst->arg=65;
  // inst++;
  // inst->op=RByte;
  // inst->arg=65;
  // inst++;
  // inst->op=SDef;
  // inst->arg=0;
  // inst++;
  // inst->op=Byte;
  // inst->arg=32;
  // inst++;
  // inst->op=RByte;
  // inst->arg=32;
  // inst++;
  // inst->op=Pos;
  // inst++;
  // inst->op=Byte;
  // inst->arg=65;
  // inst++;
  // inst->op=RByte;
  // inst->arg=65;
  // inst++;
  // // inst->op=SIs;
  // // inst->arg=0;
  // // inst++;
  // inst->op=SIsa;
  // inst->arg=0;
  // inst++;
  // inst->op=NAny;
  // inst++;
  //
  // inst->op=Ret;
  // inst++;
  return instSize;
}

int parse(VM_Context *vm_ctx,char* p) {
  Instruction *inst = malloc(sizeof(*inst) * vm_ctx->instSize);

  // inst = vm_ctx->inst;

  ParserContext *pc = vm_ctx->ctx;
  Instruction *head = inst;
  int instsSize = prepare(inst, head,p);

  inst=head-1;
  for (int i = 0; i < instsSize; i++) {
Jump:
    switch ((++inst)->op) {
      LABEL(Byte) {

        if(ParserContext_prefetch(pc)!=inst->arg||ParserContext_eof(pc)) {
          printf("Byte");

          FAIL();
        }else{
          printf("Byte Success\n");
          ParserContext_move(pc,1);

          NEXT;
        }
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
          printf("OStr Through\n");                                 //for debug
        }
        printf("%c",*(pc->pos-1));
        NEXT;


      }
      LABEL(OSet){
        if(osets[inst->arg][ParserContext_prefetch(pc)])                          //&& sc.eof()
        {  printf("OSet Success\n");
           ParserContext_move(pc,1); }else{
          printf("OSet Through\n");                                 //for debug
        }

        NEXT;

      }
      LABEL(TBegin)                    //ParserContext_beginTree(ParserContext *c, int shift)
      {
        printf("TBegin Success\n");
        ParserContext_beginTree(pc,inst->arg);
        // DEBUG_dumplog(pc);


        NEXT;

      }
      LABEL(TTag)                    //ParserContext_tagTree(ParserContext *c, symbol_t tag)
      {
        printf("TTag Success\n");
        ParserContext_tagTree(pc,tags[inst->arg]);

        // DEBUG_dumplog(pc);


        NEXT;
      } LABEL(TReplace)                    //ParserContext_valueTree(ParserContext *c, const unsigned char *text, size_t len)
      {
        int work;
        work=inst->arg;
        inst++;
        printf("TReplace Success\n");


        ParserContext_valueTree(pc,replaces[work],inst->arg);
        // DEBUG_dumplog(pc);

        NEXT;
      }
      LABEL(TLink)                    // ParserContext_linkTree(ParserContext *c, symbol_t label)
      {
        printf("TLink Success\n");
        Wstack *s=popW(pc);

        ParserContext_backLog(pc,s->value);

        ParserContext_linkTree(pc,labels[inst->arg]);
        // DEBUG_dumplog(pc);
        NEXT;

      } LABEL(TFold)                    //ParserContext_foldTree(ParserContext *c, int shift, symbol_t label)
      {
        int work;
        work=inst->arg;
        inst++;
        printf("TFold Success\n");

        ParserContext_foldTree(pc,work,labels[inst->arg]);
        // DEBUG_dumplog(pc);
        NEXT;


      }

      LABEL(TEnd)                    //ParserContext_endTree(ParserContext *c, int shift, symbol_t tag, const unsigned char *text, size_t len)
      {
        int work;
        work=inst->arg;
        inst++;

        printf("TEnd Success\n");


        if(inst->arg!=-1) {
          printf("TEnd 1\n");
          ParserContext_endTree(pc,work,tags[inst->arg],NULL,0);
        }else{
          printf("TEnd 2\n");

          ParserContext_endTree(pc,work,NULL,NULL,0);
        }

        // DEBUG_dumplog(pc);
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

        Wstack* s0=unusedStack(pc);
        Wstack* s1=unusedStack(pc);
        Wstack* s2=unusedStack(pc);
        s0->value=pc->fail_stack;
        pc->fail_stack=pc->unused_stack-2;
        s0->tree=pc->left;
        s1->value=inst->arg;
        s1->num=pc->pos-text;
        s2->value=ParserContext_saveLog(pc);
        s2->num=ParserContext_saveSymbolPoint(pc);
        // print_stack2(pc);
        // Wstack *s0=unusedStack(pc);
        // s0->value=inst->arg;
        //
        // push(pc,inst->arg);
        NEXT;
      } LABEL(Succ){
        printf("Succ Success\n");

        Wstack s0=pc->stacks[pc->fail_stack];
        pc->unused_stack=pc->fail_stack-1;
        pc->fail_stack=s0.value;

        // popW(pc);

        NEXT;
      } LABEL(Jump){
        printf("Jump Success\n");
        inst=head+(inst->arg)-2;
        NEXT;
      } LABEL(Ret){
        printf("Ret Success\n");


        Wstack *s=popW(pc);
        // print_stack2(pc);

        inst=head+s->value-2;
        NEXT;

      }
      LABEL(Pos){
        printf("Pos Success\n");
        push(pc,pc->pos-text);
        printf("Pos Success\n");
        NEXT;
      }
      LABEL(Back){
        printf("Back Success\n");
        ParserContext_back(pc,popW(pc)->value);
        NEXT;
      }
      LABEL(Move){
        printf("Move Success\n");
        ParserContext_move(pc,inst->arg);
        NEXT;
      } LABEL(TPush){
        printf("Tpush Success\n");
        pushW(pc,ParserContext_saveLog(pc),pc->left);



        NEXT;


      } LABEL(TPop){
        printf("Tpop Success\n");
        Wstack *work=popW(pc);
        pc->left=work->tree;
        ParserContext_backLog(pc,work->value);
        NEXT;
      }
      LABEL(Step){
        printf("Step Success\n");
        Wstack *s1=&(pc->stacks[pc->fail_stack+1]);
        if(s1->num==pc->pos-text) {
          printf("Step ");
          FAIL();
        }
        // print_stack2(pc);

        s1->num=pc->pos-text;
        Wstack *s0=&(pc->stacks[pc->fail_stack]);
        s0->tree=pc->left;
        Wstack *s2=&(pc->stacks[pc->fail_stack+2]);
        s2->value=ParserContext_saveLog(pc);
        s2->num=ParserContext_saveSymbolPoint(pc);
        // print_stack2(pc);
        NEXT;


      }
      LABEL(SOpen){
        printf("SOpen Success\n");
        Wstack *s=unusedStack(pc);
        s->value=ParserContext_saveSymbolPoint(pc);
        NEXT;

      } LABEL(SClose){
        printf("SClose Success\n");
        // print_stack2(pc);

        Wstack *s=popW(pc);
        ParserContext_backSymbolPoint(pc,s->value);
        // print_stack2(pc);

        NEXT;
      } LABEL(SDef){
        printf("SDef Success\n");
        ParserContext_addSymbol(pc,table[inst->arg],(popW(pc)->value)+text);
        NEXT;
      }  LABEL(SIs){

        if(ParserContext_equals(pc,table2[inst->arg],(popW(pc)->value)+text))
        {printf("SIs Success\n");
         NEXT; }else {  printf("SIs");
                        FAIL(); }
      } LABEL(SIsa){

        if(ParserContext_contains(pc,table2[inst->arg],(popW(pc)->value)+text))
        {  printf("SIsa Success\n");
           NEXT; }else {  printf("SIsa");
                          FAIL(); }
      } LABEL(SExists){
        if(ParserContext_exists(pc,table2[inst->arg]))
        {  printf("SExists Success\n");
           NEXT; }else {  printf("Exists");
                          FAIL(); }
      } LABEL(SMatch){
        printf("SMatch Success\n");
        if(ParserContext_matchSymbol(pc,table[inst->arg])) {
          NEXT;
        }else {
          FAIL();
        }
      } LABEL(SMask){
        Wstack *s=unusedStack(pc);
        s->value=ParserContext_saveSymbolPoint(pc);
        ParserContext_addSymbolMask(pc,table[inst->arg]);
      }
      LABEL(SIsDef){                     //symbolまで定義されているか

        int work;
        work=inst->arg;
        inst++;

        //(ParserContext *c, symbol_t table, const unsigned char *symbol, size_t length)
        if(ParserContext_existsSymbol(pc,table[work],symbol[inst->arg],strlen(symbol[inst->arg])))
        { printf("SIsDef Success\n");

          NEXT; }else { printf("SIsDef");
                        FAIL(); }
      }

      LABEL(Call){
        printf("Call Success\n");
        Wstack *s=unusedStack(pc);
        s->value=inst->arg;

        NEXT;

      }
      LABEL(True){
        printf("End True\n");
        cnez_dump(pc->left, stdout);

        return 0;
      }
      LABEL(False){
        printf("End False\n");
        exit(1);
      } LABEL(Fail){
        printf("Fail");
        FAIL();
      }



    }
  }
  return 0;
L_fail:;
  count++;
  if(count==20) {
    exit(1);
  }
  // print_stack2(pc);
  Wstack s0 = pc->stacks[pc->fail_stack];
  Wstack s1 = pc->stacks[pc->fail_stack+1];
  Wstack s2 = pc->stacks[pc->fail_stack+2];
  pc->unused_stack=pc->fail_stack-1;
  pc->fail_stack=s0.value;
  pc->left=s0.tree;
  ParserContext_back(pc,s1.num+text);
  ParserContext_backLog(pc,s2.value);
  ParserContext_backSymbolPoint(pc,s2.num);
  val=s1.value;
  if(val==Bottom) {

    printf("fail\n");
  }
  else{
    printf(" Fail and Jump\n");

    inst=head+val-2;
    goto Jump;
  }
}


// void print_stack(Wstack s){
//   printf("val=%d" "num=%d\n",s.value,s.num);
//
// }
// void print_stack2(ParserContext *pc){
//   for(int i=0; i<=pc->unused_stack; i++) {
//     printf("s[%d]",i);
//     print_stack(*(pc->stacks+i));
//   }
// }
void initVM(ParserContext *pc){
  ParserContext_initTreeFunc(pc,NULL,NULL,NULL,NULL);
  ParserContext_initMemo(pc,10,5);
  pc->stacks[0].value=Bottom;
  pc->stacks[1].num=pc->pos-text;
  pc->stacks[1].value=-1;
  pc->stacks[2].value=ParserContext_saveSymbolPoint(pc);
  pc->stacks[2].num=ParserContext_saveLog(pc);
  pc->stacks[3].num=0;
  pc->stacks[3].value=0;
  pc->fail_stack=0;
  pc->unused_stack=3;
}
