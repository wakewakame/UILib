#include "win_info.h"

WINDOW_INFO::WINDOW_INFO() {
	size = { 640,480 }; //ウィンドウサイズ
	b_size = { 640, 480 }; //前フレームのウィンドウサイズ
	hwnd = nullptr; //OpenGLの生成ウィンドウのハンドル
	fps.SetFPS(30.0); //フレームレート設定
	title = "UILib"; //ウィンドウタイトル設定
}

WINDOW_INFO *WINDOW_INFO::get_instance(GLFWwindow *const window) {
	return (WINDOW_INFO*)glfwGetWindowUserPointer(window);
}

void WINDOW_INFO::set_GLhwnd(GLFWwindow *set_gl_hwnd) {
	//代入
	gl_hwnd = set_gl_hwnd;
	hwnd = (HWND)gl_hwnd;

	//コールバック関数用自クラスのポインタ指定
	glfwSetWindowUserPointer(gl_hwnd, this);

	//代入
	mouse.SetGLhwnd(gl_hwnd);
}

void WINDOW_INFO::b_loop() {
	mouse.loop();
}

void WINDOW_INFO::a_loop() {
	fps.Wait();
}