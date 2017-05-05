#pragma once

#include "define.h"
#include "win_info.h"
#include "FBO.h"
#include "Frame.h"
#include "UI.h"

class UILib {
private:
//変数宣言
	//終了フラグ
	bool f_exit;

//関数宣言
	//ウィンドウとビューポートを同期
	void viewport_resize();
	//エラー発生時処理関数
	bool error(bool val);

public:
//変数宣言
	//ウィンドウ情報保持変数初期化
	WINDOW_INFO win;
	//rootフレーム生成
	Frame window;

//関数宣言
	//初期化関数
	void init();
	//ループ関数
	void loop();
	//描画関数
	void render();
	//リサイズ処理関数(リサイズイベント以外で呼ぶときはinit=1)
	void window_resize(bool init = 0);
	//終了時処理
	void exit();
};

/*
-メモ1-
Frameクラスの変数のほとんどをカプセル化する。
理由:いちいち変数の変更ごとにrootフレームからget_length
かけるのがだるいから、関数に変数の値の変更とともに
get_lengthをrootフレームからかけさせる。
*/