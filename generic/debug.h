/**
 *  \file       theLink/libmsgque/debug.h
 *  \brief      \$Id: debug.h 107 2017-04-10 16:39:14Z dev1usr $
 *  
 *  (C) 2004 - NHI - #1 - Project - Group
 *  
 *  \version    \$Rev: 107 $
 *  \author     EMail: aotto1968 at t-online.de
 *  \attention  this software has GPL permissions to copy
 *  \attention  please contact AUTHORS for additional information
 */

#ifndef MQ_DEBUG_H
#define MQ_DEBUG_H

// #include "mqconfig.h"

#if defined(_MSC_VER)
// need for "getpid"
# include <process.h>
#elif defined(__CYGWIN__)
# include <winbase.h>
#endif

#if !defined(mq_getpid)
# define mq_getpid() 1
#endif

#if defined(HAVE_PTHREAD)
# include <pthread.h>
#endif

#if !defined(MQ_OUT)
# define MQ_OUT stderr
#endif

#define NX(s) fprintf(MQ_OUT, "%s(%s:%d:%d) -> %s \n", __func__, __FILE__, __LINE__, mq_getpid(), #s);fflush(MQ_OUT);

#define N0 NX(00000000000000000)
#define N1 NX(11111111111111111)
#define N2 NX(22222222222222222)
#define N3 NX(33333333333333333)
#define N4 NX(44444444444444444)
#define N5 NX(55555555555555555)

#if defined (MQ_HAS_THREAD)
# if defined(HAVE_PTHREAD) /* unix thread */
#  define MqThreadSelf() pthread_self()
#  define MqThreadSelfP() pthread_self()
# else /* windows THREAD */
BEGIN_C_DECLS
static mq_inline MQ_PTR MqThreadSelfP(void) {
  union tmp_u {
    DWORD   w;
    MQ_PTR  p;
  } t;
  t.p = NULL;
  t.w = GetCurrentThreadId();
  return t.p;
}
END_C_DECLS
#  define MqThreadSelf() GetCurrentThreadId()
# endif
#else /* no THREAD */
#  define MqThreadSelf() NULL
#  define MqThreadSelfP() NULL
#endif // MQ_HAS_THREAD

/*****************************************************************************/
/*                                                                           */
/*                              msgque/types                                 */
/*                                                                           */
/*****************************************************************************/

#if defined(MQ_HAS_THREAD)
# if defined(HAVE_PTHREAD) /* unix thread */
#   define MX(s) fprintf(MQ_OUT, "%s(%s:%d:%d:%li) -> %s \n", __func__, __FILE__, __LINE__, mq_getpid(), \
	      MqThreadSelfP(), #s);fflush(MQ_OUT);
# else /* windows THREAD */
#   define MX(s) fprintf(MQ_OUT, "%s(%s:%d:%d:%p) -> %s \n", __func__, __FILE__, __LINE__, mq_getpid(), \
	      MqThreadSelfP(), #s);fflush(MQ_OUT);
# endif
#else
# define MX(s) fprintf(MQ_OUT, "%s(%s:%d:%d) -> %s \n", __func__, __FILE__, __LINE__, mq_getpid(), #s);fflush(MQ_OUT);
#endif

#define M0 MX(00000000000000000)
#define M1 MX(11111111111111111)
#define M2 MX(22222222222222222)
#define M3 MX(33333333333333333)
#define M4 MX(44444444444444444)
#define M5 MX(55555555555555555)
#define M6 MX(66666666666666666)
#define M7 MX(77777777777777777)
#define M8 MX(88888888888888888)
#define M9 MX(99999999999999999)
#define MA MX(AAAAAAAAAAAAAAAAA)
#define MB MX(BBBBBBBBBBBBBBBBB)
#define MC MX(CCCCCCCCCCCCCCCCC)
#define MD MX(DDDDDDDDDDDDDDDDD)
#define ME MX(EEEEEEEEEEEEEEEEE)
#define MF MX(FFFFFFFFFFFFFFFFF)

#define MXI(s,i) fprintf(MQ_OUT, "%s(%s:%d) -> %s - %s\n", __func__, __FILE__, __LINE__, #s, i);fflush(MQ_OUT);

#define M0I(i) MXI(00000000000000000,i)
#define M1I(i) MXI(11111111111111111,i)
#define M2I(i) MXI(22222222222222222,i)
#define M3I(i) MXI(33333333333333333,i)
#define M4I(i) MXI(44444444444444444,i)
#define M5I(i) MXI(55555555555555555,i)
#define M6I(i) MXI(66666666666666666,i)
#define M7I(i) MXI(77777777777777777,i)
#define M8I(i) MXI(88888888888888888,i)
#define M9I(i) MXI(99999999999999999,i)
#define MAI(i) MXI(AAAAAAAAAAAAAAAAA,i)
#define MBI(i) MXI(BBBBBBBBBBBBBBBBB,i)
#define MCI(i) MXI(CCCCCCCCCCCCCCCCC,i)
#define MDI(i) MXI(DDDDDDDDDDDDDDDDD,i)
#define MEI(i) MXI(EEEEEEEEEEEEEEEEE,i)
#define MFI(i) MXI(FFFFFFFFFFFFFFFFF,i)

#define MQ_IX(x,s) MqLogV(x,__func__,0, #x "<" #s "> -> (%s:%d)\n", __FILE__, __LINE__);

#define MQ_I0 MQ_IX(MQ_CONTEXT_S,0000000000000000)
#define MQ_I1 MQ_IX(MQ_CONTEXT_S,1111111111111111)
#define MQ_I2 MQ_IX(MQ_CONTEXT_S,2222222222222222)
#define MQ_I3 MQ_IX(MQ_CONTEXT_S,3333333333333333)
#define MQ_I4 MQ_IX(MQ_CONTEXT_S,4444444444444444)
#define MQ_I5 MQ_IX(MQ_CONTEXT_S,5555555555555555)
#define MQ_I6 MQ_IX(MQ_CONTEXT_S,6666666666666666)
#define MQ_I7 MQ_IX(MQ_CONTEXT_S,7777777777777777)
#define MQ_I8 MQ_IX(MQ_CONTEXT_S,8888888888888888)
#define MQ_I9 MQ_IX(MQ_CONTEXT_S,9999999999999999)
#define MQ_IA MQ_IX(MQ_CONTEXT_S,aaaaaaaaaaaaaaaa)
#define MQ_IB MQ_IX(MQ_CONTEXT_S,bbbbbbbbbbbbbbbb)
#define MQ_IC MQ_IX(MQ_CONTEXT_S,cccccccccccccccc)
#define MQ_ID MQ_IX(MQ_CONTEXT_S,dddddddddddddddd)
#define MQ_IE MQ_IX(MQ_CONTEXT_S,eeeeeeeeeeeeeeee)

#define XI0(x) MQ_IX(x,0000000000000000)
#define XI1(x) MQ_IX(x,1111111111111111)
#define XI2(x) MQ_IX(x,2222222222222222)
#define XIB(x) MQ_IX(x,BBBBBBBBBBBBBBBB)
#define XIE(x) MQ_IX(x,EEEEEEEEEEEEEEEE)

#define MQ_IXP(x,s,p) MqDLogV(x,__func__,0, "<" #s "-" #x "-%s> -> (%s:%d)\n", p, __FILE__, __LINE__);

#define MQ_I0P MQ_IXP(MQ_CONTEXT_S,0000000000000000,prefix)

#if defined(MQ_HAS_THREAD)

#define MV(f,v)    fprintf(MQ_OUT,"%s(%s:%d:%d:%p) -> " #v "<" f ">\n", __func__, __FILE__, __LINE__, mq_getpid(), \
	      (void*) MqThreadSelf(), v);fflush(MQ_OUT);
#define MVP(f,v)   fprintf(MQ_OUT,"%s(%s:%d:%d:%p) -> %p:" #v "<" f ">\n", __func__, __FILE__, __LINE__, mq_getpid(), \
	      (void*) MqThreadSelf(), v, v);fflush(MQ_OUT);
#define MVA(f,v,a) fprintf(MQ_OUT,"%s(%s:%d:%d:%p) -> " #v "<" f ">\n", __func__, __FILE__, __LINE__, mq_getpid(), \
	      (void*) MqThreadSelf(), a);fflush(MQ_OUT);
#define MVvar(f,...) fprintf(MQ_OUT,"%s(%s:%d:%d:%p) -> " f ">\n", __func__, __FILE__, __LINE__, mq_getpid(), \
	      (void*) MqThreadSelf(), __VA_ARGS__);fflush(MQ_OUT);
#else

#define MV(f,v)    fprintf(MQ_OUT,"%s(%s:%d:%d) -> " #v "<" f ">\n", __func__, __FILE__, __LINE__, mq_getpid(), \
	      v);fflush(MQ_OUT);
#define MVP(f,v)   fprintf(MQ_OUT,"%s(%s:%d:%d) -> %p:" #v "<" f ">\n", __func__, __FILE__, __LINE__, mq_getpid(), \
	      v,v);fflush(MQ_OUT);
#define MVA(f,v,a) fprintf(MQ_OUT,"%s(%s:%d:%d) -> " #v "<" f ">\n", __func__, __FILE__, __LINE__, mq_getpid(), \
	      a);fflush(MQ_OUT);
#define MVvar(f,...) fprintf(MQ_OUT,"%s(%s:%d:%d) -> " f ">\n", __func__, __FILE__, __LINE__, mq_getpid(), \
	     __VA_ARGS__);fflush(MQ_OUT);
#endif

#define printI(var)	MV(MQ_FORMAT_I,	var)
#define printZ(var)	MV("%li",	var)
#define printS(var)	MV(MQ_FORMAT_S,	var)
#define printUI(var)	MV("%u",	var)
#define printY(var)	MV(MQ_FORMAT_Y,	var)
#define printFo(var)	MV("%o",	var)
#define printH(var)	MV("%c",	var)
#define printW(var)	MV(MQ_FORMAT_W, var)
#define printP(var)	MV("%p",	(void*)var)
#define printD(var)	MV(MQ_FORMAT_D,	var)
#define printF(var)	MV(MQ_FORMAT_F,	var)
#define printC(var)	MVP(MQ_FORMAT_C,var)
#define printc(var)	MV("%c",	var)
#define printX(var)	MV("%x",	var)
#define printO(var)	MVA("%s",	var,	(var==MQ_YES?"yes":"no"));

#define printCP(txt,var)  MVA("%p",txt,var)

#define printCC(v1,v2)	fprintf(MQ_OUT,"%s(%s:%d:%d:%p) -> " #v1 "<" MQ_FORMAT_C ">, " #v2 "<" MQ_FORMAT_C ">\n", \
  __func__, __FILE__, __LINE__, mq_getpid(), (void*) MqThreadSelf(), v1, v2);fflush(MQ_OUT);

#define MLV(x,f,v) MqLogV(x,__func__,0,"(%s:%d) -> " #v "<" f ">\n", __FILE__, __LINE__, v);
#define MLVA(x,f,t,v) MqLogV(x,__func__,0,"(%s:%d) -> " #t "<" f ">\n", __FILE__, __LINE__, v);

#define printLP(var)	MLV(MQ_CONTEXT_S, "%p",        var)
#define printLI(var)	MLV(MQ_CONTEXT_S, MQ_FORMAT_I, var)
#define printLW(var)	MLV(MQ_CONTEXT_S, MQ_FORMAT_W, var)
#define printLO(var)	MLV(MQ_CONTEXT_S, MQ_FORMAT_C, var == MQ_YES ? "yes" : "no" )
#define printLC(var)	MLV(MQ_CONTEXT_S, MQ_FORMAT_C, var)
#define printLH(var)	MLV(MQ_CONTEXT_S, "%c",        var)
#define printR(var)	MLVA(MQ_CONTEXT_S, MQ_FORMAT_C, RET, MqLogErrorCode(ret))
#define printLV(fmt,...)  MqLogV(MQ_CONTEXT_S,__func__,0,fmt,__VA_ARGS__)

#define printXLP(x,var)	  MLV(x, "%p"       , var)
#define printXLI(x,var)	  MLV(x, MQ_FORMAT_I, var)
#define printXLC(x,var)	  MLV(x, MQ_FORMAT_C, var)
#define printXLW(x,var)	  MLV(x, MQ_FORMAT_W, var)
#define printXLO(x,var)	  MLV(x, MQ_FORMAT_C, var == MQ_YES ? "yes" : "no" )
#define printXR(x,var)	  MLVA(x, MQ_FORMAT_C, RET, MqLogErrorCode(ret))
#define printXLV(x,fmt,...)  MqLogV(x,__func__,0,fmt,__VA_ARGS__)

#define printC2(var,len)  fprintf(MQ_OUT,"%s->" #var " = <" MQ_FORMAT_C  ">\n", __func__, MqLogC(var,len));fflush(MQ_OUT);
#define printC3(buf) fprintf(MQ_OUT, "%s->" #buf " = <" MQ_FORMAT_C  ">\n", __func__, MqLogC(MqBufferGetC(buf),buf->cursize));fflush(MQ_OUT);
#define printX2(var) fprintf(MQ_OUT, "%s->" #var " = <" "%hx"     ">\n", __func__, var);fflush(MQ_OUT);
#define printT(var)  fprintf(MQ_OUT, "%s->" #var " = <" MQ_FORMAT_C  ">\n", __func__, MqLogTypeName(var));fflush(MQ_OUT);
#define printPy(var) fprintf(MQ_OUT, "%s->" #var "(%p) = <", __func__, var); PyObject_Print(var,MQ_OUT,0); fprintf(MQ_OUT,">\n");fflush(MQ_OUT);

#define CL(code) if (MQ_IS_CLIENT(MQ_CONTEXT_S)) {code}

#define bufLog(fmt,...) {\
    char buf[1000];\
    snprintf(buf,1000,"echo '%-5i - %-30s : " fmt "' >> /tmp/buf.log",getpid(),__func__,__VA_ARGS__);\
    system(buf);\
}

#define printMI(msgque,var)  printLog(msgque,#var " = <" MQ_FORMAT_I  ">\n", var);fflush(MQ_OUT);

#define printM(mq) MqDLogV(mq,__func__,0,"(%s:%d) -> <" #mq ">\n", __FILE__, __LINE__);
#define printU(var) MqBufferLog(var->context, var, #var);
#define printXU(ctx,var) MqBufferLog(ctx, var, #var);
#define printUL(var) MqBufferLLog(MQ_CONTEXT_S, var, #var);
#define printXUL(x,var) MqBufferLLog(x, var, #var);
#define printXULS(x,var) MqBufferLLogS(x, var, __func__ , #var);
#define printULS(var) printXULS(MQ_CONTEXT_S, var);

#define printThread(str) fprintf(MQ_OUT,"%s(%s:%d) -> pid<%i>, id<%li> -> " #str "\n", __func__, __FILE__, __LINE__,\
      mq_getpid(), MqThreadSelf());fflush(MQ_OUT);

#define PRT(id) fprintf(MQ_OUT,"%s(%s:%d) -> " #id " - pid<%i>, thread<%p>\n", __func__, __FILE__, __LINE__, getpid(), \
			    (void*)MqThreadSelf());fflush(MQ_OUT);

#define PRT1(id,ptr) fprintf(MQ_OUT,"%s(%s:%d) -> " #id " - pid<%i>, thread<%p>, " #ptr "<%p>\n", \
  __func__, __FILE__, __LINE__, getpid(), (void*)MqThreadSelf(), (void*)ptr);fflush(MQ_OUT);

#define printERR(ctx) if (MqErrorGetCodeI(ctx) == MQ_ERROR) \
  MqDLogV(ctx,0,"ERROR -> %s\n", MqErrorGetText(ctx)); 

/*****************************************************************************/
/*                                                                           */
/*                            msgque/definition                              */
/*                                                                           */
/*****************************************************************************/

#define MQ_FORMAT_In(n)	"%"	MQ_CPPSTR(n) "i"
#define MQ_FORMAT_XI(n) "%"	MQ_CPPSTR(n) "x"
#define MQ_FORMAT_Dn(n)	"%1."	MQ_CPPSTR(n) "e"
#define MQ_FORMAT_Cn(n) "%"	MQ_CPPSTR(n) "s"

#define MQ_FORMAT_Y	"%hi"
#define MQ_FORMAT_O	"%hi"
#define MQ_FORMAT_S	"%hi"
#define MQ_FORMAT_I	"%i"
#define MQ_FORMAT_F	"%1.7e"
#define MQ_FORMAT_D	"%1.11e"
#define MQ_FORMAT_Z	"%i"
#define MQ_FORMAT_C	"%s"
#define MQ_FORMAT_B	"%p"
#define MQ_FORMAT_L	"%p"
#define MQ_FORMAT_P	"%p"
#define MQ_FORMAT_H	"%c"


// if "MQ_FORMAT_W" error than "mqconfig.h" is missing

#if defined(MQ_IS_POSIX)
# define MQ_FORMAT_W	  "%lli"
# define MQ_FORMAT_T	  "%lli"
# define MQ_FORMAT_X	  "%llx"
# define MQ_FORMAT_Xn(n)  "%"	MQ_CPPSTR(n) "llx"
# define MQ_FORMAT_Wn(n)  "%"	MQ_CPPSTR(n) "lli"
#elif defined(MQ_IS_WIN32)
# define MQ_FORMAT_W	  "%I64i"
# define MQ_FORMAT_T	  "%I64i"
# define MQ_FORMAT_X	  "%I64x"
# define MQ_FORMAT_Xn(n)  "%"	MQ_CPPSTR(n) "I64x"
# define MQ_FORMAT_Wn(n)  "%"	MQ_CPPSTR(n) "I64i"
#endif

#endif /* MQ_DEBUG_H */

// vim: tabstop=8
