#include "VMloader.h"

#include "vm.h"

static const char *loadFile(const char *path, size_t *size);
void* root(int ac, const char **av, void* (*parse)(const char *input, size_t len));

int ustrcmp(const unsigned char* left, const unsigned char* right) {
  return 0;
}

Instruction* loadinst(char* filename){
  size_t len;

  const char *input = loadFile(filename, &len);
  Tree *tree = (Tree*)VMloader_parse(input, len, NULL, NULL, NULL, NULL);
  int instsSize=30;
  Instruction *inst = (Instruction*)malloc(sizeof(*inst) * instsSize);
  int count[10]={0};
  for(int i=0; i<tree->size; i++) {
    //matching
    if(strcmp((const char*)tree->childs[i]->childs[0]->text,"byte")) {
      inst->op=Byte;
      inst->arg=atoi((const char*)tree->childs[i]->childs[1]->text);
      inst++;
    }
    // else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"nbyte")) {
    //   inst->op=NByte;
    //   inst->arg=atoi((const char*)tree->childs[i]->childs[1]->text);
    //   inst++;
    // } else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"rbyte")) {
    //   inst->op=RByte;
    //   inst->arg=atoi((const char*)tree->childs[i]->childs[1]->text);
    //   inst++;
    // } else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"obyte")) {
    //   inst->op=OByte;
    //   inst->arg=atoi((const char*)tree->childs[i]->childs[1]->text);
    //   inst++;
    // } else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"str")) {
    //   inst->op=Str;
    //   inst->arg=count[0];
    //   count[0]++;
    //   inst++;
    //
    // } else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"rstr")) {
    //   inst->op=RStr;
    //   inst->arg=count[1];
    //   count[1]++;
    //   inst++;
    //
    // } else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"nstr")) {
    //   inst->op=NStr;
    //   inst->arg=count[2];
    //   count[2]++;
    //   inst++;
    // } else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"ostr")) {
    //   inst->op=OStr;
    //   inst->arg=count[3];
    //   count[3]++;
    //   inst++;
    // }  //AST
    // else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"tbegin")) {
    //   inst->op=TBegin;
    //   inst++;
    // }else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"tend")) {
    //   inst->op=TEnd;
    //   inst->arg=atoi((const char*)tree->childs[i]->childs[1]->text);
    //   inst++;
    //   inst->op=TEnd;
    //   inst->arg=count[4]++;
    //   inst++;
    // }else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"treplace")) {
    //   inst->op=TReplace;
    //   inst->arg=count[5];
    //   count[5]++;
    //   inst++;
    //   inst->op=TReplace;
    //   inst->arg=atoi((const char*)tree->childs[i]->childs[1]->text);
    //   inst++;
    // }else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"tlink")) {
    //   inst->op=TLink;
    //   inst->arg=count[6];
    //   count[6]++;
    //   inst++;
    // }else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"tfold")) {
    //   inst->op=TFold;
    //   inst->arg=count[6];
    //   count[6]++;
    //   inst++;
    // } else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"ttag")) {
    //   inst->op=TTag;
    //   inst->arg=count[4];
    //   count[4]++;
    //   inst++;
    // }else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"tpush")) {
    //   inst->op=TPush;
    //   inst++;
    // }else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"tpop")) {
    //   inst->op=TPop;
    //   inst++;
    // }///Basic Control
    // else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"nop")) {
    //   inst->op=Nop;
    //   inst++;
    // } else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"exit")) {
    //   inst->op=Exit;
    //   inst++;
    // } else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"alt")) {
    //   inst->op=Alt;
    //   inst->arg=inst->arg=atoi((const char*)tree->childs[i]->childs[1]->text);
    //   inst++;
    //
    // } else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"succ")) {
    //   inst->op=Succ;
    //   inst++;
    // } else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"jump")) {
    //   inst->op=Alt;
    //   inst->arg=inst->arg=atoi((const char*)tree->childs[i]->childs[1]->text);
    //   inst++;
    // } else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"ret")) {
    //   inst->op=Ret;
    //   inst++;
    // } else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"back")) {
    //   inst->op=Back;
    //   inst->arg=inst->arg=atoi((const char*)tree->childs[i]->childs[1]->text);
    //   inst++;
    // } else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"pos")) {
    //   inst->op=Pos;
    //   inst->arg=inst->arg=atoi((const char*)tree->childs[i]->childs[1]->text);
    //   inst++;
    // }else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"move")) {
    //   inst->op=Move;
    //   inst->arg=inst->arg=atoi((const char*)tree->childs[i]->childs[1]->text);
    //   inst++;
    // }else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"call")) {
    //   inst->op=Call;
    //   inst->arg=inst->arg=atoi((const char*)tree->childs[i]->childs[1]->text);
    //   inst++;
    // } else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"step")) {
    //   inst->op=Step;
    //   inst++;
    // }else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"false")) {
    //   inst->op=False;
    //   inst++;
    // }else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"true")) {
    //   inst->op=True;
    //   inst++;
    // }else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"fail")) {
    //   inst->op=Fail;
    //   inst++;
    // }//Symbol
    // else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"sopen")) {
    //   inst->op=SOpen;
    //   inst++;
    // }else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"sclose")) {
    //   inst->op=SClose;
    //   inst++;
    // }else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"sdef")) {
    //   inst->op=SDef;
    //   inst->arg=count[6];
    //   //table[count[6]]= (const char*)tree->childs[i]->childs[1]->text;
    //   count[6]++;
    //
    //   inst++;
    // }else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"sis")) {
    //   inst->op=SIs;
    //   inst->arg=count[7];
    //   //table[count[7]]= (const char*)tree->childs[i]->childs[1]->text;
    //   count[7]++;
    //
    //   inst++;
    // }else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"sisa")) {
    //   inst->op=SIsa;
    //   inst->arg=count[7];
    //   //table[count[7]]= (const char*)tree->childs[i]->childs[1]->text;
    //   count[7]++;
    //
    //   inst++;
    // }else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"sexists")) {
    //   inst->op=SExists;
    //   inst->arg=count[7];
    //   //table[count[7]]= (const char*)tree->childs[i]->childs[1]->text;
    //   count[7]++;
    //
    //   inst++;
    // }else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"smatch")) {
    //   inst->op=SMatch;
    //   inst->arg=count[7];
    //   //table[count[7]]= (const char*)tree->childs[i]->childs[1]->text;
    //   count[7]++;
    //   inst++;
    // }else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"smask")) {
    //   inst->op=SMask;
    //   inst->arg=count[7];
    //   //table[count[7]]= (const char*)tree->childs[i]->childs[1]->text;
    //   count[7]++;
    //   inst++;
    // }else if(strcmp((const char*)tree->childs[i]->childs[0]->text,"sisdef")) {
    //   inst->op=SIsDef;
    //   inst->arg=count[7];
    //   //table[count[7]]= (const char*)tree->childs[i]->childs[1]->text;
    //   count[7]++;
    //   inst++;
    //   inst->op=SIsDef;
    //   inst->arg=count[8];
    //   //table[count[7]]= (const char*)tree->childs[i]->childs[1]->text;
    //   count[8]++;
    //   inst++;
    // }
    //
    else{
      printf("else");
      exit(1);
    }
  }
  return NULL;
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
// void* VMloader_parse(const char *text, size_t len, void *thunk, void* (*fnew)(symbol_t, const unsigned char *, size_t, size_t, void *), void (*fset)(void *, size_t, symbol_t, void *, void *), void (*fgc)(void *, int, void *)) {
//   void* result = NULL;
//   ParserContext * c = ParserContext_new((const unsigned char*)text, len);
//   ParserContext_initTreeFunc(c,thunk,fnew,fset,fgc);
//   // if (pOps(c)) {
//   //   result = c->left;
//   //   if (result == NULL) {
//   //     result = c->fnew(0, (const unsigned char*)text, (c->pos - (const unsigned char*)text), 0, c->thunk);
//   //   }
//   // }
//   ParserContext_free(c);
//   return result;
// }
