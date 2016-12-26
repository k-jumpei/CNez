#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "cnez-runtime.h"
#define UNUSE_MAIN 0


static int _T = 0;
static int _L = 0;
static int _S = 0;
static const unsigned char _set0[256] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static const unsigned char _index1[256] = {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,2,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,2,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static const unsigned char _set2[256] = {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static int _Lopname = 1;
static const unsigned char _set3[256] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static int _Largs = 2;
static int _Larg = 3;
static const unsigned char _set4[256] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static int _TLABEL = 1;
static int _TOp = 2;
static int _TOps = 3;
// Prototypes
// '"'? { [#-$(-)\--.0-9A-Z_a-z~]+ } '"'?
static inline int pArg(ParserContext * c) {
  if (ParserContext_prefetch(c) == 34) {
    ParserContext_move(c,1);
  }
  ParserContext_beginTree(c,0);
  if (!_set4[ParserContext_read(c)]) {
    return 0;
  }
  while (_set4[ParserContext_prefetch(c)]) {
    ParserContext_move(c,1);
  }
  ParserContext_endTree(c,0,_T,NULL, 0);
  if (ParserContext_prefetch(c) == 34) {
    ParserContext_move(c,1);
  }
  return 1;
}
// $arg(([\t ]* Arg))
static inline int e3(ParserContext * c) {
  size_t left = ParserContext_saveTree(c);
  while (_set2[ParserContext_prefetch(c)]) {
    ParserContext_move(c,1);
  }
  if (!pArg(c)) {
    return 0;
  }
  ParserContext_linkTree(c,_Larg);
  ParserContext_backTree(c,left);
  return 1;
}
// [\t ]* $args(({ $arg(Arg) ($arg(([\t ]* Arg)))* }))
static inline int e2(ParserContext * c) {
  while (_set2[ParserContext_prefetch(c)]) {
    ParserContext_move(c,1);
  }
  {
    size_t left = ParserContext_saveTree(c);
    ParserContext_beginTree(c,0);
    {
      size_t left1 = ParserContext_saveTree(c);
      if (!pArg(c)) {
        return 0;
      }
      ParserContext_linkTree(c,_Larg);
      ParserContext_backTree(c,left1);
    }
    while (1) {
      const unsigned char * pos = c->pos;
      size_t left3 = ParserContext_saveTree(c);
      size_t log = ParserContext_saveLog(c);
      // $arg(([\t ]* Arg))
      if (!e3(c)) {
        c->pos = pos;
        ParserContext_backTree(c,left3);
        ParserContext_backLog(c,log);
        break;
      }
    }
    ParserContext_endTree(c,0,_T,NULL, 0);
    ParserContext_linkTree(c,_Largs);
    ParserContext_backTree(c,left);
  }
  return 1;
}
// [\t ]* $opname(({ [A-Za-z]+ })) ([\t ]* $args(({ $arg(Arg) ($arg(([\t ]* Arg)))* })))?
static inline int e1(ParserContext * c) {
  while (_set2[ParserContext_prefetch(c)]) {
    ParserContext_move(c,1);
  }
  {
    size_t left = ParserContext_saveTree(c);
    ParserContext_beginTree(c,0);
    if (!_set3[ParserContext_read(c)]) {
      return 0;
    }
    while (_set3[ParserContext_prefetch(c)]) {
      ParserContext_move(c,1);
    }
    ParserContext_endTree(c,0,_T,NULL, 0);
    ParserContext_linkTree(c,_Lopname);
    ParserContext_backTree(c,left);
  }
  const unsigned char * pos = c->pos;
  size_t left2 = ParserContext_saveTree(c);
  size_t log = ParserContext_saveLog(c);
  // [\t ]* $args(({ $arg(Arg) ($arg(([\t ]* Arg)))* }))
  if (!e2(c)) {
    c->pos = pos;
    ParserContext_backTree(c,left2);
    ParserContext_backLog(c,log);
  }
  return 1;
}
// ![\t ] $opname(({ [.0-9?A-Z_a-z~]+ #LABEL }))
static inline int e4(ParserContext * c) {
  if (_set2[ParserContext_prefetch(c)]) {
    return 0;
  }
  {
    size_t left = ParserContext_saveTree(c);
    ParserContext_beginTree(c,0);
    if (!_set0[ParserContext_read(c)]) {
      return 0;
    }
    while (_set0[ParserContext_prefetch(c)]) {
      ParserContext_move(c,1);
    }
    ParserContext_endTree(c,0,_TLABEL,NULL, 0);
    ParserContext_linkTree(c,_Lopname);
    ParserContext_backTree(c,left);
  }
  return 1;
}
// ![\t ] $opname(({ [.0-9?A-Z_a-z~]+ #LABEL })) / [\t ]* $opname(({ [A-Za-z]+ })) ([\t ]* $args(({ $arg(Arg) ($arg(([\t ]* Arg)))* })))?
static inline int e5(ParserContext * c) {
  int temp = 1;
  if (temp) {
    const unsigned char * pos = c->pos;
    size_t left = ParserContext_saveTree(c);
    size_t log = ParserContext_saveLog(c);
    // ![\t ] $opname(({ [.0-9?A-Z_a-z~]+ #LABEL }))
    if (e4(c)) {
      temp = 0;
    } else {
      c->pos = pos;
      ParserContext_backTree(c,left);
      ParserContext_backLog(c,log);
    }
  }
  if (temp) {
    const unsigned char * pos4 = c->pos;
    size_t left5 = ParserContext_saveTree(c);
    size_t log6 = ParserContext_saveLog(c);
    // [\t ]* $opname(({ [A-Za-z]+ })) ([\t ]* $args(({ $arg(Arg) ($arg(([\t ]* Arg)))* })))?
    if (e1(c)) {
      temp = 0;
    } else {
      c->pos = pos4;
      ParserContext_backTree(c,left5);
      ParserContext_backLog(c,log6);
    }
  }
  if (temp) {
    return 0;
  }
  return 1;
}
// { ([\t ]* $opname(({ [A-Za-z]+ })) ([\t ]* $args(({ $arg(Arg) ($arg(([\t ]* Arg)))* })))? / ![\t ] $opname(({ [.0-9?A-Z_a-z~]+ #LABEL })) / (![\t ] $opname(({ [.0-9?A-Z_a-z~]+ #LABEL })) / [\t ]* $opname(({ [A-Za-z]+ })) ([\t ]* $args(({ $arg(Arg) ($arg(([\t ]* Arg)))* })))?)) #Op }
static inline int pOp(ParserContext * c) {
  ParserContext_beginTree(c,0);
  int temp = 1;
  switch(_index1[ParserContext_prefetch(c)]) {
  case 0:
    return 0;
  case 1:
    // [\t ]* $opname(({ [A-Za-z]+ })) ([\t ]* $args(({ $arg(Arg) ($arg(([\t ]* Arg)))* })))?
    temp = e1(c);
    break;
  case 2:
    // ![\t ] $opname(({ [.0-9?A-Z_a-z~]+ #LABEL }))
    temp = e4(c);
    break;
  case 3:
    // ![\t ] $opname(({ [.0-9?A-Z_a-z~]+ #LABEL })) / [\t ]* $opname(({ [A-Za-z]+ })) ([\t ]* $args(({ $arg(Arg) ($arg(([\t ]* Arg)))* })))?
    temp = e5(c);
    break;
  }
  if (!temp) {
    return 0;
  }
  ParserContext_endTree(c,0,_TOp,NULL, 0);
  return 1;
}
// 'L' [.0-9?A-Z_a-z~]+ '\n'
static inline int e7(ParserContext * c) {
  if (ParserContext_read(c) != 76) {
    return 0;
  }
  if (!_set0[ParserContext_read(c)]) {
    return 0;
  }
  while (_set0[ParserContext_prefetch(c)]) {
    ParserContext_move(c,1);
  }
  if (ParserContext_read(c) != 10) {
    return 0;
  }
  return 1;
}
// $(('\n' ('L' [.0-9?A-Z_a-z~]+ '\n')* Op))
static inline int e6(ParserContext * c) {
  size_t left = ParserContext_saveTree(c);
  if (ParserContext_read(c) != 10) {
    return 0;
  }
  while (1) {
    const unsigned char * pos = c->pos;
    // 'L' [.0-9?A-Z_a-z~]+ '\n'
    if (!e7(c)) {
      c->pos = pos;
      break;
    }
  }
  if (!pOp(c)) {
    return 0;
  }
  ParserContext_linkTree(c,_L);
  ParserContext_backTree(c,left);
  return 1;
}
// [.0-9?A-Z_a-z~]+ '\n'
static inline int e0(ParserContext * c) {
  if (!_set0[ParserContext_read(c)]) {
    return 0;
  }
  while (_set0[ParserContext_prefetch(c)]) {
    ParserContext_move(c,1);
  }
  if (ParserContext_read(c) != 10) {
    return 0;
  }
  return 1;
}
// ([.0-9?A-Z_a-z~]+ '\n')* { $(Op) ($(('\n' ('L' [.0-9?A-Z_a-z~]+ '\n')* Op)))* #Ops }
static inline int pOps(ParserContext * c) {
  while (1) {
    const unsigned char * pos = c->pos;
    // [.0-9?A-Z_a-z~]+ '\n'
    if (!e0(c)) {
      c->pos = pos;
      break;
    }
  }
  ParserContext_beginTree(c,0);
  {
    size_t left = ParserContext_saveTree(c);
    if (!pOp(c)) {
      return 0;
    }
    ParserContext_linkTree(c,_L);
    ParserContext_backTree(c,left);
  }
  while (1) {
    const unsigned char * pos2 = c->pos;
    size_t left3 = ParserContext_saveTree(c);
    size_t log = ParserContext_saveLog(c);
    // $(('\n' ('L' [.0-9?A-Z_a-z~]+ '\n')* Op))
    if (!e6(c)) {
      c->pos = pos2;
      ParserContext_backTree(c,left3);
      ParserContext_backLog(c,log);
      break;
    }
  }
  ParserContext_endTree(c,0,_TOps,NULL, 0);
  return 1;
}
#ifndef UNUSE_MAIN
#include <sys/time.h> // for using gettimeofday

static const char *get_input(const char *path, size_t *size)
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

static double timediff(struct timeval *s, struct timeval *e)
{
  double t1 = (e->tv_sec - s->tv_sec) * 1000.0;
  double t2 = (e->tv_usec - s->tv_usec) / 1000.0;
  return t1 + t2; /* ms */
}

int cnez_main(int ac, const char **av, void* (*parse)(const char *input, size_t len))
{
  int j;
  size_t len;
  if(ac == 1) {
    fprintf(stdout, "Usage: %s file [or input-text]\n", av[0]);
    return 1;
  }
  for(j = 1; j < ac; j++) {
    const char *input = get_input(av[j], &len);
    if(getenv("BENCH") != NULL) {
      double tsum = 0.0;
      double t[5];
      int i = 0;
      for(i = 0; i < 5; i++) {
        struct timeval s, e;
        gettimeofday(&s, NULL);
        void *data = parse(input, len);
        gettimeofday(&e, NULL);
        if(data == NULL) {
          fprintf(stdout, "%s FAIL %f[ms]\n", av[j], timediff(&s, &e));
          break;
        }
        t[i] = timediff(&s, &e);
        tsum += t[i];
        cnez_free(data);
      }
      if(tsum != 0.0) {
        fprintf(stdout, "%s OK %.4f[ms] %.3f %.3f %.3f %.3f %.3f\n", av[j], tsum / 5, t[0], t[1], t[2], t[3], t[4]);
      }
    }
    else {
      void *data = parse(input, len);
      cnez_dump(data, stdout);
      fprintf(stdout, "\n");
      if(getenv("MEM") != NULL) {
        cnez_dump_memory("Memory Usage", data);
      }
      cnez_free(data);
    }
  }
  return 0;
}
#endif/*UNUSE_MAIN*/
void* VMloader_parse(const char *text, size_t len, void *thunk, void* (*fnew)(symbol_t, const unsigned char *, size_t, size_t, void *), void (*fset)(void *, size_t, symbol_t, void *, void *), void (*fgc)(void *, int, void *)) {
  void* result = NULL;
  ParserContext * c = ParserContext_new((const unsigned char*)text, len);
  ParserContext_initTreeFunc(c,thunk,fnew,fset,fgc);
  if (pOps(c)) {
    result = c->left;
    if (result == NULL) {
      result = c->fnew(0, (const unsigned char*)text, (c->pos - (const unsigned char*)text), 0, c->thunk);
    }
  }
  ParserContext_free(c);
  return result;
}
static void* cnez_parse(const char *text, size_t len) {
  return VMloader_parse(text, len, NULL, NULL, NULL, NULL);
}
long VMloader_match(const char *text, size_t len) {
  long result = -1;
  ParserContext * c = ParserContext_new((const unsigned char*)text, len);
  ParserContext_initNoTreeFunc(c);
  if (pOps(c)) {
    result = c->pos-c->inputs;
  }
  ParserContext_free(c);
  return result;
}
// const char* VMloader_tag(symbol_t n) {
//   return _tags[n];
// }
// const char* VMloader_label(symbol_t n) {
//   return _labels[n];
// }
#ifndef UNUSE_MAIN
int main(int ac, const char **argv) {
  return cnez_main(ac, argv, cnez_parse);
}
#endif/*MAIN*/
// End of File
