#ifdef __cplusplus
extern "C" {
#endif

#include "spikeapi.h"
  
/* タスク優先度 */
#define MAIN_PRIORITY    (TMIN_APP_TPRI + 1) /* メインタスク */
#define TRACER_PRIORITY  (TMIN_APP_TPRI + 2) /* ライントレースタスク */

/* タスク周期の定義 */
/* 100msから4ms(4000)に変更：これで高速走行でもブレを抑えられます */
#define LINE_TRACER_PERIOD  (4 * 1000) 


#ifndef STACK_SIZE
#define STACK_SIZE      (4096)
#endif /* STACK_SIZE */

#ifndef TOPPERS_MACRO_ONLY

extern void main_task(intptr_t exinf);
extern void tracer_task(intptr_t exinf);

#endif /* TOPPERS_MACRO_ONLY */

#ifdef __cplusplus
}
#endif