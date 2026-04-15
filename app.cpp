/******************************************************************************
 * app.cpp (for SPIKE)
 * ETロボコン2025用：スタート待機を確実に行う修正版
 *****************************************************************************/

#include "app.h"
#include "RandomWalker.h"

#include "Light.h"
#include "Button.h"
#include "Display.h"

using namespace spikeapi;

// デバイスオブジェクトの静的確保
ColorSensor gColorSensor(EPort::PORT_E);
ForceSensor gForceSensor(EPort::PORT_D);
Motor       gLeftWheel(EPort::PORT_B,Motor::EDirection::COUNTERCLOCKWISE,true);
Motor       gRightWheel(EPort::PORT_A,Motor::EDirection::CLOCKWISE,true);
Clock       gClock;

// オブジェクトの定義
static Walker          *gWalker;
static LineMonitor     *gLineMonitor;
static Starter         *gStarter;
static SimpleTimer     *gScenarioTimer;
static SimpleTimer     *gWalkerTimer;
static LineTracer      *gLineTracer;
static Scenario        *gScenario;
static ScenarioTracer  *gScenarioTracer;
static RandomWalker    *gRandomWalker;

// シーン構成
static Scene gScenes[] = {
    { TURN_LEFT,   1250 * 1000, 0 },
    { GO_STRAIGHT, 5000 * 1000, 0 }
};

/**
 * システム生成
 */
static void user_system_create() {
    tslp_tsk(2U * 1000U);

    gWalker          = new Walker(gLeftWheel, gRightWheel);
    gStarter         = new Starter(gForceSensor);
    gLineMonitor     = new LineMonitor(gColorSensor);
    gScenarioTimer   = new SimpleTimer(gClock);
    gWalkerTimer     = new SimpleTimer(gClock);
    gLineTracer      = new LineTracer(gLineMonitor, gWalker);
    gScenario        = new Scenario(0);
    gScenarioTracer  = new ScenarioTracer(gWalker, gScenario, gScenarioTimer);
    gRandomWalker    = new RandomWalker(gLineTracer, gScenarioTracer, gStarter, gWalkerTimer);

    for (uint32_t i = 0; i < (sizeof(gScenes)/sizeof(gScenes[0])); i++) {
        gScenario->add(&gScenes[i]);
    }
    
    Light light;
    light.turnOnColor(Light::EColor::ORANGE);
}

/**
 * システム破棄
 */
static void user_system_destroy() {
    gLeftWheel.stop();
    gRightWheel.stop();
    delete gRandomWalker;
    delete gScenarioTracer;
    delete gScenario;
    delete gLineTracer;
    delete gWalkerTimer;
    delete gScenarioTimer;
    delete gLineMonitor;
    delete gStarter;
    delete gWalker;
}

/**
 * メインタスク
 */
void main_task(intptr_t unused) {
    user_system_create(); 

    // --- スタート待機処理の強化 ---
    
    // 1. もし最初から押されていたら、一旦離されるまで待つ（誤作動防止）
    while (gStarter->isPushed()) {
        tslp_tsk(10U * 1000U);
    }

    // 2. 物理的に「カチッ」と押されるまで待つ
    while (!gStarter->isPushed()) {
        tslp_tsk(10U * 1000U);
    }

    // 3. チャタリング防止（少しだけ待ってから開始）
    tslp_tsk(500U * 1000U); 
    
    // ----------------------------

    sta_cyc(CYC_TRACER);
    slp_tsk();  
    stp_cyc(CYC_TRACER);
    user_system_destroy();
    ext_tsk();
}

/**
 * ライントレースタスク
 */
void tracer_task(intptr_t exinf) {
    Button button;
    if (button.isLeftPressed()) {
        wup_tsk(MAIN_TASK);
    } else {
        gLineTracer->run();
    }
    ext_tsk();
}