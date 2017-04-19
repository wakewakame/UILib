#include "mouse.h"
#include "win_info.h"

MOUSE::MOUSE() {
//変数初期化
	push.l = 0;
	push.r = 0;
	push.wheel = 0;
	b_push.l = 0;
	b_push.r = 0;
	b_push.wheel = 0;
	click.l = 0;
	click.r = 0;
	click.wheel = 0;
	mouse.x = 0.0;
	mouse.y = 0.0;
	b_mouse.x = 0.0;
	b_mouse.y = 0.0;
	wheel = 0.0;
	wheel_flag = 0;
}

void MOUSE::SetGLhwnd(GLFWwindow *set_gl_hwnd) {
	//代入
	gl_hwnd = set_gl_hwnd;

	//マウスホイールイベント取得
	glfwSetScrollCallback(gl_hwnd, get_wheel);
}

bool MOUSE::hit(WindowRect area) {
	if (
		(area.left <= mouse.x) &&
		(area.top <= mouse.y) &&
		(area.right >= mouse.x) &&
		(area.bottom >= mouse.y)
		) {
		return 1;
	}
	return 0;
}

bool MOUSE::hit(WindowPoint pos, double size) {
	return hit({
		pos.x - size / 2.0,
		pos.y - size / 2.0,
		pos.x + size / 2.0,
		pos.y + size / 2.0
	});
}

void MOUSE::judge_click() {
	if ((push.l == 1) && (b_push.l == 0)) {
		click.l = 1;
	}
	else {
		click.l = 0;
	}
	if ((push.r == 1) && (b_push.r == 0)) {
		click.r = 1;
	}
	else {
		click.r = 0;
	}
	if ((push.wheel == 1) && (b_push.wheel == 0)) {
		click.wheel = 1;
	}
	else {
		click.wheel = 0;
	}
}

void MOUSE::loop() {
	get_event();
}

void MOUSE::get_event() {
	//一時代入
	b_mouse = mouse;
	b_push = push;

	//マウスカーソル座標の取得
	glfwGetCursorPos(gl_hwnd, &mouse.x, &mouse.y);

	//マウスクリックイベント取得
	push.l = (glfwGetMouseButton(gl_hwnd, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS); //左クリック
	push.r = (glfwGetMouseButton(gl_hwnd, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS); //右クリック
	push.wheel = (glfwGetMouseButton(gl_hwnd, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS); //ホイールクリック

	//ホイール取得フラグリセット
	if (wheel_flag == 1) {
		wheel_flag = 0;
	}else {
		wheel = 0.0;
	}

	//クリック判定
	judge_click();
}

void MOUSE::get_wheel(GLFWwindow *const window, double x, double y) {
	WINDOW_INFO::get_instance(window)->mouse.wheel_flag = 1;
	WINDOW_INFO::get_instance(window)->mouse.wheel += y;
}