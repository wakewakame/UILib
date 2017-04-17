#include "win_info.h"

WINDOW_INFO::WINDOW_INFO() {
	size = { 640,480 }; //ウィンドウサイズ
	b_size = { 640, 480 }; //前フレームのウィンドウサイズ
	window = { 0, 0, 640, 480 }; //ウィンドウ左上右下座標(デスクトップ基準)
	hwnd = nullptr; //OpenGLの生成ウィンドウのハンドル
	fps.SetFPS(30.0);
	title = "UILib";
}

void WINDOW_INFO::b_loop() {
	mouse.loop();
}

void WINDOW_INFO::a_loop() {
	fps.Wait();
}