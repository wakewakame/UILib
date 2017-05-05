#pragma once

#include "define.h"
#include "mouse.h"
#include "fps.h"

//ウィンドウ情報保持変数
class WINDOW_INFO {
private:
//変数宣言
	//前フレーム時のウィンドウサイズ保持
	WindowPoint b_size;

//関数宣言
	//ウィンドウリサイズイベント処理関数
	static void resize_event(GLFWwindow *window, int width, int heigh);
	
	//ウィンドウリサイズフラグ処理
	void resize_flag_event();

public:
//コンストラクタ
	WINDOW_INFO();

//変数宣言
	WindowPoint size; //ウィンドウサイズ
	bool resize_flag;//ウィンドウサイズ変更フラグ(ウィンドウリサイズ変更直後のフレームのみ1)
	HWND hwnd; //OpenGLの生成ウィンドウのハンドル
	GLFWwindow *gl_hwnd; //OpenGLの生成GLウィンドウのハンドル
	MOUSE mouse; //マウスイベント保持クラス
	FPS fps; //フレームレート管理クラス
	std::string title; //ウィンドウタイトル

//関数宣言
	//WINDOW_INFOのインスタンス取得関数
	static WINDOW_INFO *get_instance(GLFWwindow *const window);

	//GLウィンドウハンドル設定関数
	void set_GLhwnd(GLFWwindow *set_gl_hwnd);

	//ウィンドウサイズ変更関数
	void set_window_size(int width, int heigh);

	//ループ関数(描画前に置く)
	void loop();
};