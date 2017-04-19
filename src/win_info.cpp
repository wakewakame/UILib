#include "win_info.h"

WINDOW_INFO::WINDOW_INFO() {
	size = { 640,480 }; //ウィンドウサイズ
	b_size = { 640, 480 }; //前フレームのウィンドウサイズ
	hwnd = nullptr; //OpenGLの生成ウィンドウのハンドル
	fps.SetFPS(30.0);
	title = "UILib";
}

void WINDOW_INFO::set_GLhwnd(GLFWwindow *set_gl_hwnd) {
	gl_hwnd = set_gl_hwnd;
	hwnd = (HWND)gl_hwnd;
	mouse.SetGLhwnd(gl_hwnd);
}

void WINDOW_INFO::b_loop() {
	mouse.loop();
}

void WINDOW_INFO::a_loop() {
	fps.Wait();
}