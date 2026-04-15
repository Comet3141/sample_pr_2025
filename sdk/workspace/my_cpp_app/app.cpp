#include <new> 
#include "app.h"
#include "Motor.h"
#include "ColorSensor.h"
#include "Clock.h"
#include "ForceSensor.h"
#include "Walker.h"
#include "LineMonitor.h"
#include "LineTracer.h"
#include "SimpleTimer.h"
#include "Starter.h"
#include "Scenario.h"
#include "ScenarioTracer.h"
#include "RandomWalker.h"

using namespace spikeapi;

/* 1. インスタンス管理用ポインタ */
static Clock* pClock = nullptr;
static ColorSensor* pColorSensor = nullptr;
static ForceSensor* pForceSensor = nullptr;
static Motor* pLeftWheel = nullptr;
static Motor* pRightWheel = nullptr;

static Walker* pWalker = nullptr;
static LineMonitor* pLineMonitor = nullptr;
static LineTracer* pLineTracer = nullptr;
static SimpleTimer* pSimpleTimer = nullptr;
static Starter* pStarter = nullptr;
static Scenario* pScenario = nullptr;
static ScenarioTracer* pScenarioTracer = nullptr;
static RandomWalker* pRandomWalker = nullptr;

/**
 * システム生成（デバイスとロジックのインスタンス化）
 */
static void user_system_create() {
    // シミュレータ側の認識待ち時間を十分に確保
    tslp_tsk(3000U * 1000U); 

    // デバイス生成
    pClock       = new Clock();
    pColorSensor = new ColorSensor(EPort::PORT_E);
    
    // 【修正点】接続先に合わせて PORT_D を指定
    pForceSensor = new ForceSensor(EPort::PORT_D); 

    pLeftWheel   = new Motor(EPort::PORT_B, Motor::EDirection::COUNTERCLOCKWISE, true);
    pRightWheel  = new Motor(EPort::PORT_A, Motor::EDirection::CLOCKWISE, true);

    // ロジック生成（依存関係順）
    pWalker         = new Walker(*pLeftWheel, *pRightWheel);
    pLineMonitor    = new LineMonitor(*pColorSensor);
    pLineTracer     = new LineTracer(pLineMonitor, pWalker);
    pSimpleTimer    = new SimpleTimer(*pClock);
    pStarter        = new Starter(*pForceSensor);
    pScenario       = new Scenario(nullptr); 
    pScenarioTracer = new ScenarioTracer(pWalker, pScenario, pSimpleTimer);
    
    // RandomWalker の生成
    pRandomWalker   = new RandomWalker(pLineTracer, pScenarioTracer, pStarter, pSimpleTimer, *pClock);

    // 安定化のためのウェイト
    tslp_tsk(1000U * 1000U);
}

/**
 * メインタスク（メインループ）
 */
void main_task(intptr_t unused) {
    user_system_create();  
    
    // 周期タスク（tracer_task）の開始
    sta_cyc(CYC_TRACER);
    
    // 終了指示があるまで待機
    slp_tsk();  
    
    // 終了処理
    stp_cyc(CYC_TRACER);
    if(pLeftWheel) pLeftWheel->stop();
    if(pRightWheel) pRightWheel->stop();
    ext_tsk();
}

/**
 * 周期タスク（デフォルト 4ms 周期）
 */
void tracer_task(intptr_t exinf) {
    // インスタンス生成が完了するまで安全のためにチェック
    if (pRandomWalker != nullptr) {
        pRandomWalker->run();
    }
}