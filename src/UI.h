#pragma once

#include "define.h"
#include "Frame.h"
#include "Animation.h"
#include "FBO.h"
#include "GraphPara.h"

//グラフ描画クラス
class Graph : public Frame {
private:
	void main_draw();
	std::vector<int> wave;
	void glColor(double R, double G, double B, double A = 255.0) {
		glColor4d(R / 255.0, G / 255.0, B / 255.0, A / 255.0);
	}
public:
	Graph(Frame *set_parent = nullptr) : Frame(set_parent) {

	}
	//波形情報と描画範囲
	graph grp;
	//波形を塗りつぶすかどうか
	bool fill_wave;
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