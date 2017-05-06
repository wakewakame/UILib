#include "UI.h"

void Graph::main_draw() {
	//描画効率化のため、ピクセルの数に合わせて描画
	int index = 0; //配列から値を参照するときのインデックス
	float percentage = 0.0f;
	float height; //今描画する波の高さ
	float zero = Utility::Proportion(0.0f, grp.val_min, grp.val_max, (float)(pos.bottom), (float)(pos.top)); //グラフy座標が0のときのフレームy座標
	if (wave.size() != size.x) {
		wave.resize(size.x);
	}
	//波形の描画位置算出
	for (int i = 0; i < size.x; i++) {
		percentage = Utility::Proportion((float)i, 0.0f, (float)size.x, (float)grp.start_index, (float)grp.end_index); //一時代入
		index = (int)percentage; //波形配列のインデックス算出
		percentage = percentage - (float)index; //int,floatの性質上必ず正の数になる
		//(念の為)index+1>=num_sampleになったらループ脱出
		if (index + 1 >= grp.num_sample) {
			break;
		}
		//今描画する波の高さ
		height =
			Utility::Proportion(grp.samples[index], grp.val_min, grp.val_max, (float)(pos.bottom), (float)(pos.top)) * (1.0f - percentage) +
			Utility::Proportion(grp.samples[index + 1], grp.val_min, grp.val_max, (float)(pos.bottom), (float)(pos.top)) * (percentage);
		wave[i] = height;
	}
	//x軸描画
	glLineWidth(1.0f);
	glColor(255, 255, 255, 128);
	glBegin(GL_LINES);
	glVertex2d(pos.left, zero);
	glVertex2d(pos.right, zero);
	glEnd();
	//塗りつぶし
	if (fill_wave) {
		glLineWidth(1.0f);
		glColor(0, 128, 198, 50);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < size.x; i++) {
			glVertex2d(pos.left + i, zero);
			glVertex2d(pos.left + i, wave[i]);
			glVertex2d(pos.left + i, zero);
		}
		glEnd();
	}
	//波形描画
	glDisable(GL_POLYGON_SMOOTH);
	glLineWidth(1.5f);
	glColor(0, 128, 198, 255);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < size.x; i++) {
		glVertex2d(pos.left + i, wave[i]);
	}
	glEnd();
}