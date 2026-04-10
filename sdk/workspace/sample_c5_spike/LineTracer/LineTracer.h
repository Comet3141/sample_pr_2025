#ifndef LINETRACER_H
#define LINETRACER_H

#include "spikeapi.h"

/* アプリケーション側(app.c)から1回だけ呼ばれる構成関数 */
void LineTracer_Configure(pbio_port_id_t left_motor, pbio_port_id_t right_motor, pbio_port_id_t color_sensor);

/* 周期タスク(app.cfg)から100msごとに呼ばれるライントレース関数 */
void tracer_task(intptr_t exinf);

#endif /* LINETRACER_H */