#pragma once

#include "define.h"
#include <iostream>
#include <Windows.h>
#include "mouse.h"
#include "fps.h"

//ウィンドウ情報保持変数
class WINDOW_INFO {
public:
//コンストラクタ
	WINDOW_INFO();

//変数宣言
	POINT size; //ウィンドウサイズ
	POINT b_size; //前フレームのウィンドウサイズ
	RECT window; //ウィンドウ左上右下座標(デスクトップ基準)
	HWND hwnd; //OpenGLの生成ウィンドウのハンドル
	//double fps; //ウィンドウの描画フレームレート
	MOUSE mouse; //マウスイベント保持クラス
	FPS fps;
	std::string title;

//関数宣言
	//描画前ループ関数
	void b_loop();

	//描画後ループ関数
	void a_loop();
};