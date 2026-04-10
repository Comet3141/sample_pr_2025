#ifndef CAMERACONTROL_H
#define CAMERACONTROL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* カメラ制御の初期化 */
void* CameraControl_init(void);

/* カメラの終了処理 */
void CameraControl_deinit(void* handler);

/* フレームの取得 */
void CameraControl_capture(void* handler);

/* ライン位置の解析結果を取得 */
int16_t CameraControl_get_line_position(void* handler);

#ifdef __cplusplus
}
#endif

#endif /* CAMERACONTROL_H */