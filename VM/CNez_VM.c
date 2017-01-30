#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "vm.h"
#include "VMloader.h"
#define CNEZ_NOGC  1
#define LABEL(OP) case OP:
#define NEXT break;
#define FAIL() goto L_fail
#define Bottom -100 //Stackbottom//

size_t val;
const unsigned char *text;
int count=0;

static const char *loadFile(const char *path, size_t *size);
void printinst(Instruction* inst,int instSize);
void set_setting(Tree* data,char set[8][256],int count,int i);
void print_stack(Wstack s);
void print_stack2(ParserContext *pc);

int main (int argc,char* argv[]){
  printf("A\n");
  char inputtext[3000000];
  FILE *fp;
  fp=fopen(argv[2],"r");
  if(fp==NULL) {
    fp=stdin;
    fgets(inputtext,512,fp);
  }
  else{  int k=0;
         while((inputtext[k]=(char)fgetc(fp))!=EOF) {
           k++;
         }}

  fclose(fp);
  printf("%s",inputtext);
  VM_Context *vm_ctx= malloc((sizeof(*vm_ctx)));

  // printf("Please input text.\n");
  // fgets(inputtext,sizeof(inputtext),stdin);
  text = inputtext;
  printf("A\n");
  vm_ctx->ctx= ParserContext_new(text,strlen(text));
  initVM(vm_ctx->ctx);
  parse(vm_ctx,argv[1]);
  print_parse(vm_ctx->ctx);
}

int prepare(Instruction *inst, Instruction* head,char* p) {
  int instSize=0;
  inst=head-2;
  inst->op=False;
  inst++;
  inst->op=True;
  inst++;
  instSize=loadinst(inst,p);
  return instSize;
}

int parse(VM_Context *vm_ctx,char* p) {
  Instruction *inst = malloc(sizeof(*inst) * 2000);
  ParserContext *pc = vm_ctx->ctx;
  Instruction *head = inst;
  int instsSize = prepare(inst, head,p);

  inst=head-1;
  for (int i = 0; i < 9000000; i++) {
Jump:
    switch ((++inst)->op) {
      LABEL(Byte) {
        if(ParserContext_prefetch(pc)!=inst->arg||ParserContext_eof(pc)) {
          FAIL();
        }else{
          ParserContext_move(pc,1);
          NEXT;
        }
      }
      LABEL(Str){
        if(ParserContext_match(pc,strs[inst->arg],(int)strlen(strs[inst->arg]))) {
          NEXT;
        }else{
          FAIL();
        }
      }
      LABEL(Set){
        if(sets[inst->arg][(int)ParserContext_read(pc)]) {
          NEXT;
        }
        FAIL();
      }
      LABEL(Any) {
        if(!ParserContext_eof(pc)) {
          ParserContext_move(pc,1);
          NEXT;
        }
        FAIL();
      }
      LABEL(NByte){
        if(ParserContext_prefetch(pc)==inst->arg||ParserContext_eof(pc)) {
          FAIL();
        }else{
          NEXT;
        }
      }
      LABEL(NStr){
        if(ParserContext_match(pc,nstrs[inst->arg],(int)strlen(nstrs[inst->arg]))||ParserContext_eof(pc)) {
          FAIL();
        }else{
          NEXT;
        }
      }

      LABEL(NSet){
        if ((nsets[inst->arg][(int)ParserContext_prefetch(pc)])||ParserContext_eof(pc)) {
          FAIL();
        }
        NEXT;
      }
      LABEL(NAny){
        if(ParserContext_eof(pc)) {
          NEXT;
        }
        FAIL();
      }
      LABEL(RByte){
        while(ParserContext_prefetch(pc)==inst->arg) {
          ParserContext_move(pc,1);
        }
        NEXT;
      }

      LABEL(RStr){
        while(ParserContext_match(pc,rstrs[inst->arg],(int)strlen(rstrs[inst->arg]))) {
        }
        NEXT;
      }
      LABEL(RSet){
        while(rsets[inst->arg][(int)ParserContext_prefetch(pc)]) {
          ParserContext_move(pc,1);
        }
        NEXT;
      }
      LABEL(OByte){
        if(ParserContext_prefetch(pc)==inst->arg) {
          if(inst->arg==0) {
            NEXT;
          }
          ParserContext_move(pc,1);
        }else{
        }
        NEXT;
      }
      LABEL(OStr){

        if(ParserContext_match(pc,ostrs[inst->arg],(int)strlen(ostrs[inst->arg]))) {
        }else{
        }
        NEXT;
      }
      LABEL(OSet){
        if(osets[inst->arg][ParserContext_prefetch(pc)])                          //&& sc.eof()
        {
          ParserContext_move(pc,1);
        }else{
          //for debug
        }

        NEXT;

      }
      LABEL(TBegin)                    //ParserContext_beginTree(ParserContext *c, int shift)
      {
        ParserContext_beginTree(pc,inst->arg);


        NEXT;

      }
      LABEL(TTag)                    //ParserContext_tagTree(ParserContext *c, symbol_t tag)
      {
        ParserContext_tagTree(pc,tags[inst->arg]);


        NEXT;
      } LABEL(TReplace)                    //ParserContext_valueTree(ParserContext *c, const unsigned char *text, size_t len)
      {
        int work;
        work=inst->arg;
        inst++;


        ParserContext_valueTree(pc,replaces[work],inst->arg);
        NEXT;
      }
      LABEL(TLink)                    // ParserContext_linkTree(ParserContext *c, symbol_t label)
      {
        Wstack *s=popW(pc);

        ParserContext_backLog(pc,s->value);

        if(inst->arg==-1) {
          ParserContext_linkTree(pc,NULL);
        }else{

          ParserContext_linkTree(pc,labels[inst->arg]);
        }
        NEXT;

      } LABEL(TFold)                    //ParserContext_foldTree(ParserContext *c, int shift, symbol_t label)
      {
        int work;
        work=inst->arg;
        inst++;
        ParserContext_foldTree(pc,work,labels[inst->arg]);
        NEXT;


      }

      LABEL(TEnd)                    //ParserContext_endTree(ParserContext *c, int shift, symbol_t tag, const unsigned char *text, size_t len)
      {
        int work;
        work=inst->arg;
        inst++;



        if(inst->arg!=-1) {
          ParserContext_endTree(pc,work,tags[inst->arg],NULL,0);
          cnez_dump3(pc->left, stdout);

        }else{
          ParserContext_endTree(pc,work,NULL,NULL,0);
          cnez_dump3(pc->left, stdout);

        }

        NEXT;
      }
      LABEL(Nop)
      {
        NEXT;
      }
      LABEL(Exit){
        fprintf(stderr, "exit error%d\n", inst->arg);
        exit(1);
        NEXT;
      }
      LABEL(Alt){

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
        Wstack s0=pc->stacks[pc->fail_stack];
        pc->unused_stack=pc->fail_stack-1;
        pc->fail_stack=s0.value;

        // popW(pc);

        NEXT;
      } LABEL(Jump){
        inst=head+(inst->arg)-2;
        NEXT;
      } LABEL(Ret){

        Wstack *s=popW(pc);
        // print_stack2(pc);

        inst=head+s->value-2;
        NEXT;

      }
      LABEL(Pos){
        push(pc,pc->pos-text);
        NEXT;
      }
      LABEL(Back){
        ParserContext_back(pc,popW(pc)->value);
        NEXT;
      }
      LABEL(Move){
        ParserContext_move(pc,inst->arg);
        NEXT;
      } LABEL(TPush){
        pushW(pc,ParserContext_saveLog(pc),pc->left);



        NEXT;


      } LABEL(TPop){
        Wstack *work=popW(pc);
        pc->left=work->tree;
        ParserContext_backLog(pc,work->value);
        NEXT;
      }
      LABEL(Step){
        Wstack *s1=&(pc->stacks[pc->fail_stack+1]);
        if(s1->num==pc->pos-text) {
          FAIL();
        }
        s1->num=pc->pos-text;
        Wstack *s0=&(pc->stacks[pc->fail_stack]);
        s0->tree=pc->left;
        Wstack *s2=&(pc->stacks[pc->fail_stack+2]);
        s2->value=ParserContext_saveLog(pc);
        s2->num=ParserContext_saveSymbolPoint(pc);
        NEXT;


      }
      LABEL(SOpen){
        Wstack *s=unusedStack(pc);
        s->value=ParserContext_saveSymbolPoint(pc);
        NEXT;

      } LABEL(SClose){
        // print_stack2(pc);

        Wstack *s=popW(pc);
        ParserContext_backSymbolPoint(pc,s->value);
        // print_stack2(pc);

        NEXT;
      } LABEL(SDef){
        ParserContext_addSymbol(pc,table[inst->arg],(popW(pc)->value)+text);
        NEXT;
      }  LABEL(SIs){

        if(ParserContext_equals(pc,table2[inst->arg],(popW(pc)->value)+text))
        {
          NEXT;
        }else {
          FAIL();
        }
      } LABEL(SIsa){

        if(ParserContext_contains(pc,table2[inst->arg],(popW(pc)->value)+text))
        {
          NEXT;
        }else {
          FAIL();
        }
      } LABEL(SExists){
        if(ParserContext_exists(pc,table2[inst->arg]))
        {
          NEXT;
        }else {
          FAIL();
        }
      } LABEL(SMatch){
        if(ParserContext_matchSymbol(pc,table2[inst->arg])) {

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
        if(ParserContext_existsSymbol(pc,table2[work],symbol[inst->arg],strlen(symbol[inst->arg])))
        {

          NEXT;
        }else {
          FAIL();
        }
      }

      LABEL(Call){
        Wstack *s=unusedStack(pc);
        s->value=inst->arg;

        NEXT;

      }
      LABEL(Lookup){
        int work;
        work=inst->arg;
        inst++;

        switch(ParserContext_memoLookup(pc,inst->arg)) {
        case NotFound:
          break;
        case SuccFound:
          inst=head+work-2;
          NEXT;

        default:
          FAIL();
        }
        NEXT;
      }
      LABEL(Memo){
        Wstack s0=pc->stacks[pc->fail_stack];
        Wstack s1=pc->stacks[pc->fail_stack+1];
        pc->unused_stack=pc->fail_stack-1;
        pc->fail_stack=s0.value;

        ParserContext_memoSucc(pc,inst->arg,text+s1.num);

        NEXT;

      }  LABEL(MemoFail){

        ParserContext_memoFail(pc,inst->arg);

        FAIL();

      }
      LABEL(TLookup){

        int work;
        work=inst->arg;
        inst++;

        switch(ParserContext_memoLookupTree(pc,inst->arg)) {
        case NotFound:

          break;
        case SuccFound:
          inst=(head-1)+work-1;
          break;

        default:
          FAIL();
        }
        NEXT;
      }
      LABEL(TMemo){
        Wstack s0=pc->stacks[pc->fail_stack];
        Wstack s1=pc->stacks[pc->fail_stack+1];
        pc->unused_stack=pc->fail_stack-1;
        pc->fail_stack=s0.value;

        ParserContext_memoTreeSucc(pc,inst->arg,text+s1.num);
        NEXT;

      }
      LABEL(True){
        printf("\x1b[34m");

        cnez_dump3(pc->left, stdout);
        printf("\n\x1b[30m");

        printf("--------------------------\n");
        return 0;
      }
      LABEL(False){
        exit(1);
      } LABEL(Fail){
        FAIL();
      }



    }
  }
  return 0;
L_fail:;
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

    printf("Fail\n");
  }
  else{
    inst=head+val-2;
    goto Jump;
  }
}


void print_stack(Wstack s){
  printf("val=%d" "num=%d\n",s.value,s.num);

}

void print_stack2(ParserContext *pc){
  for(int i=0; i<=pc->unused_stack; i++) {
    printf("s[%d]",i);
    print_stack(*(pc->stacks+i));
  }
}
void initVM(ParserContext *pc){
  ParserContext_initTreeFunc(pc,NULL,NULL,NULL,NULL);
  ParserContext_initMemo(pc,1024,256);
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
int loadinst(Instruction* inst,char* filename){
  Instruction* head=inst;
  size_t len;
  int work=0;

  int instSize=0;
  int jumppos[512]={0};
  int twoinstpos[512]={0};
  int jumpcount=0;
  int twoinstcount=0;
  int instpos=1;
  const char *input = loadFile(filename, &len);
  Tree* data=(Tree*)VMloader_parse(input, len, NULL, NULL, NULL, NULL);

  // Tree *tree = (Tree*)parse(input, len);

  // cnez_dump(parse(input, len),stdout);



  int count[13]={0};
  for(int i=0; i<data->size; i++) {
    //   //matching
    if(strncmp(data->childs[i]->childs[0]->text,"byte",data->childs[i]->childs[0]->len)==0) {
      inst->op=Byte;
      inst->arg=atoi((const char*)data->childs[i]->childs[1]->childs[0]->text);
      inst++;
      instSize++;
    } else if(strncmp(data->childs[i]->childs[0]->text,"nbyte",data->childs[i]->childs[0]->len)==0) {
      inst->op=NByte;
      inst->arg=atoi((const char*)data->childs[i]->childs[1]->childs[0]->text);
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"rbyte",data->childs[i]->childs[0]->len)==0) {
      inst->op=RByte;
      inst->arg=atoi((const char*)data->childs[i]->childs[1]->childs[0]->text);
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"obyte",data->childs[i]->childs[0]->len)==0) {
      inst->op=OByte;
      inst->arg=atoi((const char*)data->childs[i]->childs[1]->childs[0]->text);
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"str",data->childs[i]->childs[0]->len)==0) {
      inst->op=Str;
      inst->arg=count[0];
      strncpy(strs[count[0]],data->childs[i]->childs[1]->childs[0]->text,data->childs[i]->childs[1]->childs[0]->len);
      count[0]++;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"nstr",data->childs[i]->childs[0]->len)==0) {
      inst->op=NStr;
      inst->arg=count[1];
      strncpy(nstrs[count[1]],data->childs[i]->childs[1]->childs[0]->text,data->childs[i]->childs[1]->childs[0]->len);
      count[1]++;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"rstr",data->childs[i]->childs[0]->len)==0) {
      inst->op=RStr;
      inst->arg=count[2];
      strncpy(rstrs[count[2]],data->childs[i]->childs[1]->childs[0]->text,data->childs[i]->childs[1]->childs[0]->len);
      count[2]++;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"ostr",data->childs[i]->childs[0]->len)==0) {
      inst->op=OStr;
      inst->arg=count[3];
      strncpy(ostrs[count[3]],data->childs[i]->childs[1]->childs[0]->text,data->childs[i]->childs[1]->childs[0]->len);
      count[3]++;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"set",data->childs[i]->childs[0]->len)==0) {
      inst->op=Set;
      inst->arg=count[10];
      count[10]++;
      set_setting(data,sets,inst->arg,i);
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"nset",data->childs[i]->childs[0]->len)==0) {
      inst->op=NSet;
      inst->arg=count[11];
      count[11]++;
      set_setting(data,nsets,inst->arg,i);
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"rset",data->childs[i]->childs[0]->len)==0) {
      inst->op=RSet;
      inst->arg=count[12];
      count[12]++;
      set_setting(data,rsets,inst->arg,i);
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"oset",data->childs[i]->childs[0]->len)==0) {
      inst->op=OSet;
      inst->arg=count[13];
      count[13]++;
      set_setting(data,osets,inst->arg,i);
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"any",data->childs[i]->childs[0]->len)==0) {
      inst->op=Any;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"nany",data->childs[i]->childs[0]->len)==0) {
      inst->op=NAny;
      inst++;
      instSize++;
    }
    //AST
    else if(strncmp(data->childs[i]->childs[0]->text,"tbegin",data->childs[i]->childs[0]->len)==0) {
      inst->op=TBegin;
      inst->arg=atoi((const char*)data->childs[i]->childs[1]->childs[0]->text);
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"ttag",data->childs[i]->childs[0]->len)==0) {
      inst->op=TTag;
      inst->arg=count[5];

      strncpy(tags[inst->arg],(data->childs[i]->childs[1]->childs[0]->text+1),data->childs[i]->childs[1]->childs[0]->len-1);
      count[5]++;
      inst++;
      instSize++;

    }else if(strncmp(data->childs[i]->childs[0]->text,"tlink",data->childs[i]->childs[0]->len)==0) {
      inst->op=TLink;

      if(strncmp(data->childs[i]->childs[1]->childs[0]->text,"null",data->childs[i]->childs[1]->childs[0]->len)==0)
      {
        inst->arg=-1;
      } else{
        inst->arg=count[6];
        strncpy(labels[inst->arg],(data->childs[i]->childs[1]->childs[0]->text+1),data->childs[i]->childs[1]->childs[0]->len-1);

        count[6]++;
      }

      inst++;
      instSize++;

    }else if(strncmp(data->childs[i]->childs[0]->text,"treplace",data->childs[i]->childs[0]->len)==0) {
      twoinstpos[twoinstcount]=instpos;
      twoinstcount++;

      inst->op=TReplace;
      inst->arg=count[7];
      strncpy(replaces[inst->arg],(data->childs[i]->childs[1]->childs[0]->text+1),data->childs[i]->childs[1]->childs[0]->len-1);
      count[7]++;
      inst++;
      instSize++;
      inst->op=TReplace;
      inst->arg=atoi((const char*)data->childs[i]->childs[1]->childs[1]->text);
      inst++;
      instSize++;

    }else if(strncmp(data->childs[i]->childs[0]->text,"tfold",data->childs[i]->childs[0]->len)==0) {
      twoinstpos[twoinstcount]=instpos;
      twoinstcount++;

      inst->op=TFold;
      inst->arg=atoi((const char*)data->childs[i]->childs[1]->childs[0]->text);
      inst++;
      instSize++;
      inst->op=TFold;
      inst->arg=count[6];
      strncpy(labels[inst->arg],(data->childs[i]->childs[1]->childs[1]->text+1),data->childs[i]->childs[1]->childs[1]->len-1);
      count[6]++;
      inst++;
      instSize++;

    }else if(strncmp(data->childs[i]->childs[0]->text,"tend",data->childs[i]->childs[0]->len)==0) {
      twoinstpos[twoinstcount]=instpos;
      twoinstcount++;

      inst->op=TEnd;
      inst->arg=atoi((const char*)data->childs[i]->childs[1]->childs[0]->text);
      inst++;
      instSize++;
      inst->op=TEnd;
      if(strncmp(data->childs[i]->childs[1]->childs[1]->text,"null",data->childs[i]->childs[1]->childs[1]->len)==0)
      {
        inst->arg=-1;
      } else{
        inst->arg=count[5];
        strncpy(tags[inst->arg],(data->childs[i]->childs[1]->childs[1]->text+1),data->childs[i]->childs[1]->childs[1]->len-1);
        count[5]++;
      }
      inst++;
      instSize++;
    }
    else if(strncmp(data->childs[i]->childs[0]->text,"tpush",data->childs[i]->childs[0]->len)==0) {
      inst->op=TPush;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"tpop",data->childs[i]->childs[0]->len)==0) {
      inst->op=TPop;
      inst++;
      instSize++;
    }  //Basic Control
    else if(strncmp(data->childs[i]->childs[0]->text,"nop",data->childs[i]->childs[0]->len)==0) {
      inst->op=Nop;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"exit",data->childs[i]->childs[0]->len)==0) {
      inst->op=Exit;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"alt",data->childs[i]->childs[0]->len)==0) {
      inst->op=Alt;
      inst->arg=atoi((const char*)(data->childs[i]->childs[1]->childs[0]->text+1));
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"succ",data->childs[i]->childs[0]->len)==0) {
      inst->op=Succ;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"jump",data->childs[i]->childs[0]->len)==0) {
      jumppos[jumpcount]=instpos-jumpcount;
      jumpcount++;
      inst->op=Jump;
      inst->arg=atoi((const char*)(data->childs[i]->childs[1]->childs[0]->text+1));
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"ret",data->childs[i]->childs[0]->len)==0) {
      inst->op=Ret;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"back",data->childs[i]->childs[0]->len)==0) {
      inst->op=Back;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"pos",data->childs[i]->childs[0]->len)==0) {
      inst->op=Pos;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"move",data->childs[i]->childs[0]->len)==0) {
      inst->op=Move;
      inst->arg=atoi((const char*)(data->childs[i]->childs[1]->childs[0]->text));
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"call",data->childs[i]->childs[0]->len)==0) {
      inst->op=Call;
      inst->arg=atoi((const char*)(data->childs[i]->childs[1]->childs[0]->text+1));
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"step",data->childs[i]->childs[0]->len)==0) {
      inst->op=Step;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"true",data->childs[i]->childs[0]->len)==0) {
      inst->op=True;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"false",data->childs[i]->childs[0]->len)==0) {
      inst->op=False;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"fail",data->childs[i]->childs[0]->len)==0) {
      inst->op=Fail;
      inst++;
      instSize++;
    }
    //Symbol
    else if(strncmp(data->childs[i]->childs[0]->text,"sopen",data->childs[i]->childs[0]->len)==0) {
      inst->op=SOpen;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"sclose",data->childs[i]->childs[0]->len)==0) {
      inst->op=SClose;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"sdef",data->childs[i]->childs[0]->len)==0) {
      inst->op=SDef;
      inst->arg=count[7];
      strncpy(table[inst->arg],(data->childs[i]->childs[1]->childs[0]->text),data->childs[i]->childs[1]->childs[0]->len);
      count[7]++;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"sis",data->childs[i]->childs[0]->len)==0) {
      inst->op=SIs;
      inst->arg=count[8];
      strncpy(table2[inst->arg],(data->childs[i]->childs[1]->childs[0]->text),data->childs[i]->childs[1]->childs[0]->len);
      count[8]++;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"sisa",data->childs[i]->childs[0]->len)==0) {
      inst->op=SIsa;
      inst->arg=count[8];
      strncpy(table2[inst->arg],(data->childs[i]->childs[1]->childs[0]->text),data->childs[i]->childs[1]->childs[0]->len);
      count[8]++;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"sexists",data->childs[i]->childs[0]->len)==0) {
      inst->op=SExists;
      inst->arg=count[8];
      strncpy(table2[inst->arg],(data->childs[i]->childs[1]->childs[0]->text),data->childs[i]->childs[1]->childs[0]->len);
      count[8]++;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"smatch",data->childs[i]->childs[0]->len)==0) {
      inst->op=SMatch;
      inst->arg=count[8];
      strncpy(table2[inst->arg],(data->childs[i]->childs[1]->childs[0]->text),data->childs[i]->childs[1]->childs[0]->len);
      count[8]++;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"sisdef",data->childs[i]->childs[0]->len)==0) {
      twoinstpos[twoinstcount]=instpos;
      twoinstcount++;
      inst->op=SIsDef;
      inst->arg=count[8];
      strncpy(table2[inst->arg],(data->childs[i]->childs[1]->childs[0]->text),data->childs[i]->childs[1]->childs[0]->len);
      count[8]++;
      inst++;
      instSize++;
      inst->op=SIsDef;
      inst->arg=count[9];
      strncpy(symbol[inst->arg],(data->childs[i]->childs[1]->childs[1]->text),data->childs[i]->childs[1]->childs[1]->len);
      count[9]++;
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"lookup",data->childs[i]->childs[0]->len)==0) {
      twoinstpos[twoinstcount]=instpos;
      twoinstcount++;

      inst->op=Lookup;
      inst->arg=atoi((const char*)data->childs[i]->childs[1]->childs[0]->text+1);
      inst++;
      instSize++;
      inst->op=Lookup2;
      inst->arg=atoi((const char*)data->childs[i]->childs[1]->childs[0]->text);
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"memo",data->childs[i]->childs[0]->len)==0) {
      inst->op=Memo;
      inst->arg=atoi((const char*)data->childs[i]->childs[1]->childs[0]->text);
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"memofail",data->childs[i]->childs[0]->len)==0) {
      inst->op=MemoFail;
      inst->arg=atoi((const char*)data->childs[i]->childs[1]->childs[0]->text);
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"tlookup",data->childs[i]->childs[0]->len)==0) {
      twoinstpos[twoinstcount]=instpos;
      twoinstcount++;

      inst->op=TLookup;
      inst->arg=atoi((const char*)data->childs[i]->childs[1]->childs[0]->text+1);
      inst++;
      instSize++;
      inst->op=TLookup2;
      inst->arg=atoi((const char*)data->childs[i]->childs[1]->childs[1]->text);
      inst++;
      instSize++;
    }else if(strncmp(data->childs[i]->childs[0]->text,"tmemo",data->childs[i]->childs[0]->len)==0) {
      inst->op=TMemo;
      inst->arg=atoi((const char*)data->childs[i]->childs[1]->childs[0]->text);
      inst++;
      instSize++;
    }
    // }else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"smask")) {
    //   inst->op=SMask;
    //   inst->arg=count[7];
    //   //table[count[7]]= (const char*)tree->childs[i]->childs[1]->text;
    //   count[7]++;
    //   inst++;
    else{
      inst->op=Nop;
      inst++;
      instSize++;
      // exit(1);
    }
    instpos++;
  }
  inst=head;
  for(int i=0; i<instSize; i++) {
    work=0;
    if((inst+i)->op==Alt||(inst+i)->op==Jump||(inst+i)->op==Call||(inst+i)->op==Lookup||(inst+i)->op==TLookup) {
      for(int j=0; j<jumpcount; j++) {
        if((inst+i)->arg>=jumppos[j]) {
          work++;

        }
      }
      (inst+i)->arg=(inst+i)->arg+work;
    }
  }
  for(int i=0; i<instSize; i++) {
    work=0;
    if((inst+i)->op==Alt||(inst+i)->op==Jump||(inst+i)->op==Call||(inst+i)->op==Lookup||(inst+i)->op==TLookup) {
      for(int j=0; j<twoinstcount; j++) {
        if((inst+i)->arg>twoinstpos[j]) {
          work++;
        }
      }

      (inst+i)->arg=(inst+i)->arg+work;

    }
  }


  // printinst(head,instSize);
  return instSize;
}



static const char *loadFile(const char *path, size_t *size)
{
  FILE *fp = fopen(path, "rb");
  if(fp != NULL) {
    size_t len;
    fseek(fp, 0, SEEK_END);
    len = (size_t) ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *buf = (char *) calloc(1, len + 1);
    size_t readed = fread(buf, 1, len, fp);
    if(readed != len) {
      fprintf(stderr, "read error: %s\n", path);
      exit(1);
    }
    fclose(fp);
    size[0] = len;
    return (const char*)buf;
  }
  size[0] = strlen(path);
  return path;
}

void printinst(Instruction* inst,int instSize){
  for(int i=0; i<instSize; i++) {
    switch ((inst+i)->op) {
      LABEL(Byte) {
        printf("%d:instop=Byte,instarg=%d\n",i+1,(inst+i)->arg);
        break;

      }
      LABEL(Str) {
        printf("%d:instop=Str,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(Set) {
        printf("%d:instop=Set,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(Any) {
        printf("%d:instop=Any,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(NByte) {
        printf("%d:instop=NByte,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(NStr) {
        printf("%d:instop=NStr,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(NSet) {
        printf("%d:instop=NSet,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(NAny) {
        printf("%d:instop=NAny,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(RByte) {
        printf("%d:instop=RByte,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(RStr) {
        printf("%d:instop=RStr,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(RSet) {
        printf("%d:instop=RSet,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(OByte) {
        printf("%d:instop=OByte,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(OStr) {
        printf("%d:instop=OStr,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(OSet) {
        printf("%d:instop=OSet,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(TBegin) {
        printf("%d:instop=TBegin,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(TTag) {
        printf("%d:instop=TTag,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(TLink) {
        printf("%d:instop=TLink,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(TReplace) {
        printf("%d:instop=TReplace,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(TFold) {
        printf("%d:instop=TFold,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(TEnd) {
        printf("%d:instop=TEnd,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(TPush) {
        printf("%d:instop=TPush,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(TPop) {
        printf("%d:instop=TPop,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(Nop) {
        printf("%d:instop=Nop,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(Exit) {
        printf("%d:instop=Exit,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(Alt) {
        printf("%d:instop=Alt,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(Succ) {
        printf("%d:instop=Succ,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(Jump) {
        printf("%d:instop=Jump,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(Ret) {
        printf("%d:instop=Ret,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(Back) {
        printf("%d:instop=Back,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(Pos) {
        printf("%d:instop=Pos,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(Move) {
        printf("%d:instop=Move,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(Call) {
        printf("%d:instop=Call,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(Step) {
        printf("%d:instop=Step,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(True) {
        printf("%d:instop=True,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(False) {
        printf("%d:instop=False,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(Fail) {
        printf("%d:instop=Fail,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(SOpen) {
        printf("%d:instop=SOpen,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(SClose) {
        printf("%d:instop=SClose,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(SDef) {
        printf("%d:instop=SDef,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(SIs) {
        printf("%d:instop=SIs,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(SIsa) {
        printf("%d:instop=SIsa,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(SExists) {
        printf("%d:instop=SExists,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(SMask) {
        printf("%d:instop=SMask,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(SMatch) {
        printf("%d:instop=SMatch,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
      LABEL(SIsDef) {
        printf("%d:instop=SIsDef,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }  LABEL(Lookup) {
        printf("%d:instop=Lookup,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }  LABEL(Memo) {
        printf("%d:instop=Memo,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }  LABEL(MemoFail) {
        printf("%d:instop=MemoFail,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      } LABEL(TLookup) {
        printf("%d:instop=TLookup,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      } LABEL(TLookup2) {
        printf("%d:instop=TLookup2,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }  LABEL(TMemo) {
        printf("%d:instop=TMemo,instarg=%d\n",i+1,(inst+i)->arg);
        break;
      }
    default: {
      printf("else\n");
    }
    }
  }
}

void set_setting(Tree* data,char set[16][256],int count,int i){
  int No=0;
  for(int j=0; j<data->childs[i]->childs[1]->childs[0]->len; j++) {
    if(strncmp(data->childs[i]->childs[1]->childs[0]->text+j,"0",1)==0) {
      No=No+4;
    }else if(strncmp(data->childs[i]->childs[1]->childs[0]->text+j,"1",1)==0) {
      set[count][No+3]=1;
      No=No+4;
    }else if(strncmp(data->childs[i]->childs[1]->childs[0]->text+j,"2",1)==0) {
      set[count][No+2]=1;
      No=No+4;
    }else if(strncmp(data->childs[i]->childs[1]->childs[0]->text+j,"3",1)==0) {
      set[count][No+3]=1;
      set[count][No+2]=1;
      No=No+4;
    }else if(strncmp(data->childs[i]->childs[1]->childs[0]->text+j,"4",1)==0) {
      set[count][No+1]=1;
      No=No+4;
    }else if(strncmp(data->childs[i]->childs[1]->childs[0]->text+j,"5",1)==0) {
      set[count][No+3]=1;
      set[count][No+1]=1;
      No=No+4;
    }else if(strncmp(data->childs[i]->childs[1]->childs[0]->text+j,"6",1)==0) {
      set[count][No+1]=1;
      set[count][No+2]=1;
      No=No+4;
    }else if(strncmp(data->childs[i]->childs[1]->childs[0]->text+j,"7",1)==0) {
      set[count][No+3]=1;
      set[count][No+1]=1;
      set[count][No+2]=1;
      No=No+4;
    }else if(strncmp(data->childs[i]->childs[1]->childs[0]->text+j,"8",1)==0) {
      set[count][No]=1;
      No=No+4;
    }else if(strncmp(data->childs[i]->childs[1]->childs[0]->text+j,"9",1)==0) {
      set[count][No]=1;
      set[count][No+3]=1;
      No=No+4;
    }else if(strncmp(data->childs[i]->childs[1]->childs[0]->text+j,"a",1)==0) {
      set[count][No]=1;
      set[count][No+2]=1;
      No=No+4;
    }else if(strncmp(data->childs[i]->childs[1]->childs[0]->text+j,"b",1)==0) {
      set[count][No]=1;
      set[count][No+2]=1;
      set[count][No+3]=1;
      No=No+4;
    }else if(strncmp(data->childs[i]->childs[1]->childs[0]->text+j,"c",1)==0) {
      set[count][No]=1;
      set[count][No+1]=1;
      No=No+4;
    }else if(strncmp(data->childs[i]->childs[1]->childs[0]->text+j,"d",1)==0) {
      set[count][No]=1;
      set[count][No+1]=1;
      set[count][No+3]=1;
      No=No+4;
    }else if(strncmp(data->childs[i]->childs[1]->childs[0]->text+j,"e",1)==0) {
      set[count][No]=1;
      set[count][No+1]=1;
      set[count][No+2]=1;

      No=No+4;
    }else if(strncmp(data->childs[i]->childs[1]->childs[0]->text+j,"f",1)==0) {
      set[count][No]=1;
      set[count][No+1]=1;
      set[count][No+2]=1;
      set[count][No+3]=1;
      No=No+4;
    }else{printf("else\n"); }


  }
}
