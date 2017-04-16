#include "win_info.h"

MOUSE::MOUSE() {
	push.l = 0;
	push.r = 0;
	push.wheel = 0;
	b_push.l = 0;
	b_push.r = 0;
	b_push.wheel = 0;
	click.l = 0;
	click.r = 0;
	click.wheel = 0;
	mouse.x = 0;
	mouse.y = 0;
	b_mouse.x = 0;
	b_mouse.y = 0;
}

bool MOUSE::in(RECT area) {
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

bool MOUSE::in(POINT pos, int size) {
	return in({
		pos.x - size / 2,
		pos.y - size / 2,
		pos.x + size / 2,
		pos.y + size / 2
	});
}

void MOUSE::hudg_click() {
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
	hudg_click();
}

WINDOW_INFO::WINDOW_INFO() {
	size = { 640,480 }; //ウィンドウサイズ
	b_size = { 640, 480 }; //前フレームのウィンドウサイズ
	window = { 0, 0, 640, 480 }; //ウィンドウ左上右下座標(デスクトップ基準)
	hwnd = nullptr; //OpenGLの生成ウィンドウのハンドル
	fps = 30.0; //ウィンドウの描画フレームレート
	speed = 60.0 / fps; //60fpsを基準としたアニメーションのフレーム間の移動速度の倍率
	title = "UILib";
}

void WINDOW_INFO::loop() {
	speed = 60.0 / fps;
	mouse.loop();
}