#include "fps.h"

void FPS::SetFPS(double f) {
	if (f <= 0.0) {
		f = 30.0;
	}
	fps = f;
	bef = timeGetTime();
	gap = 1.0;
	speed = speed = 60.0 / fps;
}

void FPS::Wait() {
	//フレーム間の時差取得
	gap = timeGetTime() - bef;

	//フレームレート調節
	if ((1000.0 / fps) > (double)gap) {
		Sleep(
			(DWORD)(
				(1000.0 / fps) - (double)gap
			)
		);
	}

	//現在のフレームレート取得
	r_fps = 1000.0 / (double)(timeGetTime() - bef);

	//60fpsを基準としたアニメーションのフレーム間の移動速度の倍率算出
	speed = speed = 60.0 / r_fps;

	//現在時刻一時保存
	bef = timeGetTime();
	return;
}

double FPS::GetFPS() {
	return r_fps;
}

double FPS::GetSpeed() {
	return speed;
}