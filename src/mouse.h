#pragma once

#include "define.h"
#include "get_event.h"

class MOUSE : public GET_EVENT {
public:
//構造体定義
	struct Click {
		bool l; //lクリック
		bool r; //rクリック
		bool wheel; //ホイール
	};

//変数宣言
	WindowPoint mouse; //マウス座標
	WindowPoint b_mouse; //前フレームのマウス座標
	Click push; //押されてたらずっと1
	Click b_push; //前フレームのpush
	Click click; //押されたフレームのみ1
	double wheel; //ホイールの操作量
	bool wheel_flag; //ホイールイベントが発生したとき用フラグ

//関数宣言
	//GLウィンドウハンドル設定関数
	void SetGLhwnd(GLFWwindow *set_gl_hwnd);

	//指定RECT内に存在するかどうか
	bool hit(WindowRect area);
	bool hit(WindowPoint pos, double size);

	//ループ関数
	void loop();

	//コンストラクタ
	MOUSE();

private:
//関数宣言
	//マウスイベント取得関数
	void get_event();

	//マウスホイールイベント取得用コールバック関数
	static void get_wheel(GLFWwindow *const window, double x, double y);

	//クリック判定
	void judge_click();
};