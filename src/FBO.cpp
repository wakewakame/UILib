#include "FBO.h"

FBO::FBO() {
	now_index = -1;
}

FBO::~FBO() {
	for (int i = 0; i < buffer.size(); i++) {
		glDeleteFramebuffers(1, &buffer[i].color);
		glDeleteTextures(1, &buffer[i].color_render);
		glDeleteFramebuffers(1, &buffer[i].alpha);
		glDeleteTextures(1, &buffer[i].alpha_render);
	}
}

void FBO::createFBO(GLuint *FBO, GLuint *Tex, WindowPoint size) {
	//フレームバッファ生成
	glGenFramebuffers(1, FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, *FBO);
	//テクスチャ生成
	glGenTextures(1, Tex);
	glBindTexture(GL_TEXTURE_2D, *Tex);
	//サイズ色要素数指定
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	//拡大縮小処理等のメソッド選択
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//FBOにテクスチャ紐づけ
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, *Tex, 0);
	//ビューポート指定
	glViewport(0, 0, size.x, size.y);
	//変換行列の初期化
	glLoadIdentity();
	//スクリーン上の表示領域をビューポートの大きさに比例させる
	glOrtho(0.0, size.x, size.y, 0.0, -1.0, 1.0);
	//Bind解除
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::set_alpha() {
	glBindFramebuffer(GL_FRAMEBUFFER, buffer[now_index].color);
	glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_ONE, GL_ZERO);
	glColor4d(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, buffer[now_index].alpha_render);
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0, 1.0); glVertex2d(0.0, 0.0);
	glTexCoord2d(0.0, 0.0); glVertex2d(0.0, buffer[now_index].size.y);
	glTexCoord2d(1.0, 0.0); glVertex2d(buffer[now_index].size.x, buffer[now_index].size.y);
	glTexCoord2d(1.0, 1.0); glVertex2d(buffer[now_index].size.x, 0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glFlush();
}

int FBO::add(WindowPoint size) {
	//仮バッファの生成
	Buffer buf;
	//FBO生成
	createFBO(&buf.color, &buf.color_render, size);
	createFBO(&buf.alpha, &buf.alpha_render, size);
	//バッファサイズ設定
	buf.size = size;
	//バッファ追加
	buffer.push_back(buf);
	//バッファIDを返す
	return buffer.size() - 1;
}

void FBO::change_c(int index) {
	if (now_index != -1 && index != now_index) {
		set_alpha();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, buffer[index].color);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	now_index = index;
}

void FBO::change_a(int index) {
	if (now_index != -1 && index != now_index) {
		set_alpha();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, buffer[now_index].alpha);
	glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ZERO);
	now_index = index;
}

void FBO::change_r() {
	if (now_index == -1) {
		return;
	}
	set_alpha();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	now_index = -1;
}

void FBO::draw(int index, WindowPoint pos, WindowPoint size) {
	if (size.x == -1.0 || size.y == -1.0) {
		size = buffer[index].size;
	}
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE);
	glColor4d(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, buffer[index].color_render);
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0, 1.0); glVertex2d(pos.x, pos.y);
	glTexCoord2d(0.0, 0.0); glVertex2d(pos.x, pos.y+size.y);
	glTexCoord2d(1.0, 0.0); glVertex2d(pos.x+size.x, pos.y+size.y);
	glTexCoord2d(1.0, 1.0); glVertex2d(pos.x+size.x, pos.y);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glFlush();
}

WindowPoint FBO::get_size(int index) {
	return buffer[index].size;
}