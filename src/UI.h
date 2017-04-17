#pragma once

#include "define.h"
#include "Frame.h"
#include "Animation.h"
#include "FBO.h"
#include "GraphPara.h"

//グラフ描画クラス
class Graph : public Frame {
private:
	//波形を塗りつぶすかどうか
	bool fill_wave;
	void main_draw();
public:
	graph g;
	Graph(graph set_g, int set_length, Frame *set_parent = nullptr, bool set_lock = 0, bool set_fill_wave = 0, std::string set_name = "", std::string set_description = "");
};

//フェードグラフ描画クラス
class Fade : public Frame {

};


//ボタン描画クラス
class Button : public Frame {

};

//ボリューム描画クラス
class Volume : public Frame {

};

//個数選択描画クラス
class Figure : public Frame {

};

//波形の形選択描画クラス
class WaveForm : public Frame {

};