#include "CameraControl.h"
#include <opencv2/opencv.hpp>

/* 内部状態保持用構造体 */
struct CameraInternal {
    cv::VideoCapture cap;
    cv::Mat frame;
};

extern "C" {

void* CameraControl_init(void) {
    CameraInternal* internal = new CameraInternal();
    
    /* カメラ(デバイス0)をオープン */
    if (!internal->cap.open(0)) {
        delete internal;
        return NULL;
    }

    /* 処理負荷軽減のため解像度を320x240に設定 */
    internal->cap.set(cv::CAP_PROP_FRAME_WIDTH, 320);
    internal->cap.set(cv::CAP_PROP_FRAME_HEIGHT, 240);
    
    return (void*)internal;
}

void CameraControl_deinit(void* handler) {
    CameraInternal* internal = (CameraInternal*)handler;
    if (internal) {
        internal->cap.release();
        delete internal;
    }
}

void CameraControl_capture(void* handler) {
    CameraInternal* internal = (CameraInternal*)handler;
    if (internal) {
        internal->cap >> internal->frame;
    }
}

int16_t CameraControl_get_line_position(void* handler) {
    CameraInternal* internal = (CameraInternal*)handler;
    if (!internal || internal->frame.empty()) return 0;

    cv::Mat gray, binary;
    /* グレースケールに変換 */
    cv::cvtColor(internal->frame, gray, cv::COLOR_BGR2GRAY);
    /* 二値化 (黒いラインを白として抽出) */
    cv::threshold(gray, binary, 80, 255, cv::THRESH_BINARY_INV);

    /* 画面下部のROI(注目領域)で重心計算 */
    cv::Mat roi = binary(cv::Rect(0, 160, 320, 80));
    cv::Moments mu = cv::moments(roi, false);

    if (mu.m00 > 0) {
        /* 重心のX座標 - 画面中央(160) = 偏差 */
        return (int16_t)((mu.m10 / mu.m00) - 160);
    }
    return 0;
}

}