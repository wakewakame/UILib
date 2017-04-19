#pragma once
#pragma comment(lib, "winmm.lib")

#include <Windows.h>
#include <mmsystem.h>

class FPS{
private:
	//変数初期化
	DWORD bef; //前フレームの時刻
	DWORD gap; //前フレームで取得した時刻との差
	double fps; //設定するフレームレート
	double r_fps; //現在のフレームレート
	double speed; //60fpsを基準としたアニメーションのフレーム間の移動速度の倍率
	double load; //GPU負荷の取得((描画にかかった時間/フレーム更新時間)*100)

public:
	//関数初期化
	void SetFPS(double f); //初期化関数(デフォルトは30)
	void Wait(); //フレームレート調節用待機関数
	double GetFPS(); //現在のフレームレート取得関数
	double GetSpeed(); //60fpsを基準としたアニメーションのフレーム間の移動速度の倍率取得
	double GetLoad(); //GPU負荷の取得((描画にかかった時間/フレーム更新時間)*100)
};