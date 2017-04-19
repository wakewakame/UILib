#pragma once

#include "define.h"
#include "get_event.h"

class MOUSE : public GET_EVENT {
public:
	struct Click {
		bool l; //lクリック
		bool r; //rクリック
		bool wheel; //ホイール
	};
	//変数宣言
	WindowPos mouse; //マウス座標
	WindowPos b_mouse; //前フレームのマウス座標
	Click push; //押されてたらずっと1
	Click b_push; //前フレームのpush
	Click click; //押されたフレームのみ1

	MOUSE();
	//指定RECT内に存在するかどうか
	bool in(RECT area);
	bool in(POINT pos, int size);
	//クリック判定
	void hudg_click();
	//ループ関数
	void loop();
};