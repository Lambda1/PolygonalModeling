#ifndef __MY_GLFW_HPP__
#define __MY_GLFW_HPP__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdlib>

#include "./KeyBoardState.hpp"

class MyGLFW
{
	GLFWwindow *m_window;

	/* キーボード処理 */
	inline static constexpr int ALPHABET = 26;
	inline static constexpr int CHAR_BIAS = static_cast<int>('A');
	inline static int KEY_PRESS = 1;
	bool m_now_key[ALPHABET], m_prev_key[ALPHABET];
	KeyState::STATE m_key_state[ALPHABET];

	/* 画面処理 */
	inline static constexpr GLfloat WORLD_LENGTH_1 = 100.0f; /* ワールド座標における1の長さを100ピクセルで表現 */
	inline static constexpr GLfloat PI = 3.14159f;
	GLfloat m_aspect;         /* aspect ratio */
	GLfloat m_window_size[2]; /* width, height */
	GLfloat m_scale;          /* ワールド座標に対するデバイス座標の拡大率 */

	/* 時間処理 */
	GLfloat m_timer_count; /* 経過時間 */
	GLfloat last_time, elapsed_time; /* FPS処理用 */

	/* マウス処理 */
	int m_scroll_vec_x, m_scroll_vec_y; // マウススクロール方向のベクトル(正規化済み)

	void InitMode();
	
	void SetCallBack();
	static void KeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void WindowCallBack(GLFWwindow *window,int width,int height);
	static void MouseScrollCallBack(GLFWwindow* window, double xoffset, double yoffset);

	public:
	MyGLFW();
	~MyGLFW();

	void InitWindow(const int &width,const int &height,const char *title);

	inline bool MainLoop() const { return (glfwWindowShouldClose(m_window) == GL_FALSE); }
	inline void SwapBuffer() { glfwSwapBuffers(m_window); }
	inline void PollEvents() { glfwPollEvents(); }
	inline void Clear(){ glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); }
	inline void ErrorCheck()
	{
		GLint error = glGetError();
		if(error == 0) return;
		switch(error)
		{
			case GL_INVALID_ENUM: std::cout << "GL_INVALID_ENUM" << std::endl; break;
			case GL_INVALID_VALUE: std::cout << "GL_INVALID_VALUE" << std::endl; break;
			case GL_INVALID_OPERATION: std::cout << "GL_INVALID_OPERATION" << std::endl; break;
			case GL_STACK_OVERFLOW: std::cout << "GL_STACK_OVERFLOW" << std::endl; break;
			case GL_STACK_UNDERFLOW: std::cout << "GL_STACK_UNDERFLOW" << std::endl; break;
			case GL_OUT_OF_MEMORY: std::cout << "GL_OUT_OF_MEMORY" << std::endl; break;
			case GL_INVALID_FRAMEBUFFER_OPERATION: std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl; break;
			case GL_CONTEXT_LOST: std::cout << "GL_CONTEXT_LOST" << std::endl; break;
			case GL_TABLE_TOO_LARGE: std::cout << "GL_TABLE_TOO_LARGE" << std::endl; break;
			default: std::cout << error << std::endl;
		}
	}

	/* FPS処理 */
	/* NOTE: 効率化のため, inline化 */
	inline bool ProcessFPS(const GLfloat &fps_time)
	{
		elapsed_time = static_cast<GLfloat>(glfwGetTime()) - last_time;
		if(elapsed_time >= 1.0f/fps_time)
		{
			last_time = static_cast<GLfloat>(glfwGetTime());
			return true;
		}
		return false;
	}

	/* キー入力処理 */
	/* HACK: 毎フレームごとに処理するため, 高速化を行う. */
	inline void KeyProcess()
	{
		for (int i = 0; i < ALPHABET; ++i)
		{
			m_prev_key[i] = m_now_key[i];
			m_now_key[i] = (glfwGetKey(m_window, CHAR_BIAS + i) == KEY_PRESS ? true : false);
			if (!m_now_key[i] && !m_prev_key[i]) { m_key_state[i] = KeyState::STATE::NONE; }
			else if (m_now_key[i] && !m_prev_key[i]) { m_key_state[i] = KeyState::STATE::PUSH; }
			else if (m_now_key[i] && m_prev_key[i]) { m_key_state[i] = KeyState::STATE::HOLD; }
			else { m_key_state[i] = KeyState::STATE::RELEASE; }
		}
	}

	// 変数リセット
	// スクロール変数のクリア
	inline void ResetScrollValue() { m_scroll_vec_x = m_scroll_vec_y = 0; }

	/* Getter */
	inline GLFWwindow* GetWindow() const { return m_window; }
	inline const KeyState::STATE* GetKeyState() const { return m_key_state; }
	inline const KeyState::STATE GetKey(const char& key) const { return (static_cast<int>(key - 'a') < 0 || static_cast<int>(key - 'a') > (int)'z' ? KeyState::STATE::NONE : m_key_state[static_cast<int>(key - 'a')]); }
	inline GLfloat  GetAspect() const { return m_aspect; }
	inline const GLfloat* GetWindowSize() const { return m_window_size; }
	inline GLfloat GetWindowScale() const { return m_scale; }
	inline GLfloat GetWidthScale() const { return m_window_size[0] / m_scale; }
	inline GLfloat GetHeightScale() const { return m_window_size[1] / m_scale; }
	inline GLfloat GetWindowScaleReciprocal() const { return 1.0f/m_scale; }
	inline GLfloat GetFovy(const GLfloat &ang) const { return m_scale * (((ang/m_scale)/180.0f) * PI); }
	inline GLfloat GetTimer() const { return static_cast<GLfloat>(glfwGetTime()); }
	inline int GetScrollVecX() const { return m_scroll_vec_x; }
	inline int GetScrollVecY() const { return m_scroll_vec_y; }
};

#endif
