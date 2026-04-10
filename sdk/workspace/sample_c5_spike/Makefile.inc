APPL_COBJS += LineTracer.o

# C++のオブジェクトファイルとして CameraControl.o を追加
APPL_CXXOBJS += CameraControl.o

# インクルードパスの追加 (必要に応じて)
INCLUDES += -I$(ETROBO_HRP3_WORKSPACE)/sample_c5_spike

# OpenCVを使用するためのライブラリリンク設定
# ラズパイ上でビルドする場合、pkg-configを使ってパスを通すのが確実です
LDLIBS += `pkg-config --libs opencv4`