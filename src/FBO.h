#pragma once
#include "define.h"

//レンダーバッファとフレームバッファ保持構造体
struct Buffer {
	GLuint color; //カラーFBO
	GLuint alpha; //アルファFBO
	GLuint color_render; //カラーテクスチャ
	GLuint alpha_render; //アルファテクスチャ
	WindowPoint size; //バッファ竿時
};

//フレームバッファクラス
class FBO {
private:
	//変数初期化
	//バッファの配列
	std::vector<Buffer> buffer;
	//現在使用しているバッファのインデックス(-1ならレンダーバッファ)
	int now_index;
	//フレームバッファ生成
	void createFBO(GLuint *FBO, GLuint *Tex, WindowPoint size);
	//アルファバッファをカラーバッファに適合
	void set_alpha();

public:
	//コンストラクタ
	FBO();
	//デストラクタ
	~FBO();
	//フレームバッファの追加
	int add(WindowPoint size);
	//カラーフレームバッファの切り替え
	void change_c(int index);
	//アルファフレームバッファの切り替え
	void change_a(int index);
	//スクリーンに切替
	void change_r();
	//指定カラーバッファ描画
	void draw(int index, WindowPoint pos, WindowPoint size = {-1.0,-1.0});
	//フレームサイズ取得関数
	WindowPoint get_size(int index);
};