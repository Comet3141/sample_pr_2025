/******************************************************************************
 * LineTracer.cpp (for SPIKE)
 * PID制御の実装 ＋ ログ出力対応
 *****************************************************************************/

#include "LineTracer.h"
#include <stdio.h> // printf用に追加

// PIDゲインの設定
const float LineTracer::Kp = 0.8; //0.7~0.85
const float LineTracer::Ki = 0.02;//0.01~0.03
const float LineTracer::Kd = 8.0;//7.0~9.0
const int   LineTracer::bias = 0;

static int  log_count = 0; // 表示間引き用のカウンタ
  
/**
 * コンストラクタ
 */
LineTracer::LineTracer(const LineMonitor* lineMonitor,
                       Walker* walker)
    : mLineMonitor(lineMonitor),
      mWalker(walker),
      mIsInitialized(false),
      mOldDiff(0),
      mIntegral(0.0f) {
}

/**
 * ライントレースを実行
 */
void LineTracer::run() {
    if (mIsInitialized == false) {
        mWalker->init();
        mIsInitialized = true;
    }

    int diffReflection = mLineMonitor->calDiffReflection();

    // I項：偏差を積み上げる
    mIntegral += (float)diffReflection;

    // PID計算
    float p_term = Kp * diffReflection;
    float i_term = Ki * mIntegral;
    float d_term = Kd * (diffReflection - mOldDiff);
    float turn   = p_term + i_term + d_term + bias;
    
    // --- パソコン側へのログ出力 ---
    // 10回に1回（100msごと）表示
    if (log_count++ >= 10) {
        printf("Diff:%3d | P:%5.2f I:%5.2f D:%5.2f | Turn:%5.2f\n", 
                diffReflection, p_term, i_term, d_term, turn);
        log_count = 0;
    }
    // ----------------------------

    mWalker->setCommand(turn);
    mWalker->run();

    mOldDiff = diffReflection;
}

/**
 * PID制御による操作量の計算
 * (runメソッド内で計算するように変更したため、こちらはガワだけ残すか消去します)
 */
float LineTracer::calcPropValue(int diffBrightness) {
    return 0; 
}