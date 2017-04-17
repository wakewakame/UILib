#pragma once
#pragma comment(lib, "opengl32.lib")

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <Windows.h>
#include "win_info.h"
#include "Frame.h"

class UILib {
private:
//変数宣言
	//ウィンドウ情報保持変数初期化
	WINDOW_INFO win;
	//GLFWのハンドル
	GLFWwindow *GLhwnd;
	//フレーム管理クラス
	Frame frm;
	//フラグ
		//終了フラグ
		bool f_exit;

//関数宣言
	//ウィンドウとビューポートを同期
	void resize();
	//エラー発生時処理関数
	bool error(bool val);

public:
//関数宣言
	//初期化関数
	void init();
	//ループ関数
	void loop();
	//描画関数
	void render();
	//終了時処理
	void exit();
};

/*
-メモ1-
フレームごとにframe*型のIDを付け、
それらをライブラリを使うユーザーが保持する
フレームIDを指定する関数を作り、
現在指定されているフレームIDに新たなフレームやUIパーツをくっつけていく
時にはUIパーツ自身が指定フレーム内に新たなフレームをくっつけ、
UIを配置していくこともある
フレームの付加はすべてnewで行うが、newするのはライブラリ側で、
フレームやUIパーツをnewし、ポインタを返す関数も作る

-メモ2-
早急にfpsを指定する方法
or
それが難しそうなら現在のフレームレートを取得する方法
を調べ、実装

-メモ3-
フレームマネジメントクラスの作成(もっと単純できれいな方法があればそっち)
*/