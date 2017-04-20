#include "win_info.h"

WINDOW_INFO::WINDOW_INFO() {
//変数初期化
	size = { 640.0, 480.0 }; //ウィンドウサイズ
	b_size = size;
	resize_flag = 0;
	hwnd = nullptr; //OpenGLの生成ウィンドウのハンドル
	gl_hwnd = nullptr;
	fps.SetFPS(30.0); //フレームレート設定
	title = "UILib"; //ウィンドウタイトル設定
}

void WINDOW_INFO::resize_event(GLFWwindow *window, int width, int heigh) {
	WINDOW_INFO::get_instance(window)->b_size = WINDOW_INFO::get_instance(window)->size;
	WINDOW_INFO::get_instance(window)->size.x = (double)width;
	WINDOW_INFO::get_instance(window)->size.y = (double)heigh;
}

void WINDOW_INFO::resize_flag_event() {
	if (size != b_size) {
		resize_flag = 1;
		b_size = size;
	}
	else {
		if (resize_flag) {
			resize_flag = 0;
		}
	}
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

	//ウィンドウリサイズイベントのコールバック関数登録
	glfwSetWindowSizeCallback(gl_hwnd, resize_event);

	//代入
	mouse.SetGLhwnd(gl_hwnd);
}

void WINDOW_INFO::set_window_size(int width, int heigh) {
	if (gl_hwnd == nullptr) {
		size = { (double)width, (double)heigh };
	}
	else {
		resize_event(gl_hwnd, (double)width, (double)heigh);
	}
}

void WINDOW_INFO::loop() {
	//描画後処理
	fps.Wait();

	//描画前処理
	mouse.loop();
	resize_flag_event();
}