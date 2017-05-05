#pragma once
#pragma comment(lib, "opengl32.lib")


#include <vector>
#include <math.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;


int main(void)
{
	// We would expect width and height to be 1024 and 768
	int windowWidth = 1024;
	int windowHeight = 768;
	{
		// Initialise GLFW
		if (!glfwInit())
		{
			fprintf(stderr, "Failed to initialize GLFW\n");
			getchar();
			return -1;
		}

		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		// Open a window and create its OpenGL context
		window = glfwCreateWindow(1024, 768, "Tutorial 14 - Render To Texture", NULL, NULL);
		if (window == NULL) {
			fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
			getchar();
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);

		// But on MacOS X with a retina screen it'll be 1024*2 and 768*2, so we get the actual framebuffer size:
		glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

		// Initialize GLEW
		glewExperimental = true; // Needed for core profile
		if (glewInit() != GLEW_OK) {
			fprintf(stderr, "Failed to initialize GLEW\n");
			getchar();
			glfwTerminate();
			return -1;
		}

		// Ensure we can capture the escape key being pressed below
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

		// Dark blue background
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	}

	// ---------------------------------------------
	// Render to Texture - specific code begins here
	// ---------------------------------------------

	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	GLuint FramebufferName = 0;
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	// The texture we're going to render to
	GLuint renderedTexture;
	glGenTextures(1, &renderedTexture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, renderedTexture);

	// Give an empty image to OpenGL ( the last "0" means "empty" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, windowWidth, windowHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	// Poor filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

								   // Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;




	// Render to our framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	// Render on the whole framebuffer, complete from the lower left corner to the upper right
	glViewport(0, 0, windowWidth, windowHeight);
	//変換行列の初期化
	glLoadIdentity();
	//スクリーン上の表示領域をビューポートの大きさに比例させる
	glOrtho(0.0, (double)windowWidth, (double)windowHeight, 0.0, -1.0, 1.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Render to the screen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Render on the whole framebuffer, complete from the lower left corner to the upper right
	glViewport(0, 0, windowWidth, windowHeight);
	//変換行列の初期化
	glLoadIdentity();
	//スクリーン上の表示領域をビューポートの大きさに比例させる
	glOrtho(0.0, (double)windowWidth, (double)windowHeight, 0.0, -1.0, 1.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//----------------------------------------------------------------------------------
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

#include <math.h>

	do {
		static double a = 0.0;
		a += 0.05;

		// Render to our framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//画面初期化
		glClearColor(1.0f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//line描画
		glLineWidth(1.0f);
		glDisable(GL_POLYGON_SMOOTH);
		glBegin(GL_QUADS);
		glColor4d(0.0/255.0,128.0/255.0, 198.0/255.0 , 1.0);
		glVertex2d(0.0, 0.0);
		glColor4d(0.0/255.0, 198.0/255.0, 240.0/255.0, 1.0);
		glVertex2d(0.0, windowHeight);
		glColor4d(0.7, 1.0, 0.5, 1.0);
		glVertex2d(windowWidth, windowHeight);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glVertex2d(windowWidth, 0.0);
		glEnd();
		//バッファに描画
		glFlush();

		// Render to the screen
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Clear the screen
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Bind our texture in Texture Unit 0
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, renderedTexture);
		glBegin(GL_POLYGON);
		/*
		glTexCoord2d(0.0, 0.0); glVertex2d(0.0, 0.0);
		glTexCoord2d(0.0, 1.0); glVertex2d(0.0, windowHeight);
		glTexCoord2d(1.0, 1.0); glVertex2d(windowWidth, windowHeight);
		glTexCoord2d(1.0, 0.0); glVertex2d(windowWidth, 0.0);
		*/

		glTexCoord2d(0.0, 1.0); glVertex2d(0.0, 0.0);
		glTexCoord2d(0.0, 0.0); glVertex2d(0.0, windowHeight);
		glTexCoord2d(1.0, 0.0); glVertex2d(windowWidth, windowHeight);
		glTexCoord2d(1.0, 1.0); glVertex2d(windowWidth, 0.0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		//バッファに描画
		glFlush();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	glDeleteFramebuffers(1, &FramebufferName);
	glDeleteTextures(1, &renderedTexture);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

