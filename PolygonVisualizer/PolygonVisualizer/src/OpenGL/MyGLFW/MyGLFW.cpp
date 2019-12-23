#include "./MyGLFW.hpp"

MyGLFW::MyGLFW() :
	m_window(nullptr),
	m_now_key{}, m_prev_key{}, m_key_state{},
	m_aspect(0), m_window_size{}, m_scale(WORLD_LENGTH_1),
	m_timer_count(0.0f), last_time(0.0f), elapsed_time(0.0f),
	m_scroll_vec_x(0), m_scroll_vec_y(0),
	m_mouse_button(MOUSE_BUTTON::NONE)
{
	if(glfwInit() == GL_FALSE)
	{
		std::cout << "ERROR: glfw Init" << std::endl;
		std::abort();
	}
	atexit(glfwTerminate);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	for(int i = 0;i < ALPHABET;i++)
	{
		m_now_key[i] = m_prev_key[i] = false;
		m_key_state[i] = KeyState::STATE::NONE;
	}
}

MyGLFW::~MyGLFW()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void MyGLFW::InitMode()
{
	/* カリング設定 */
	glFrontFace(GL_CCW);    /* CounterClockWise */
	glCullFace(GL_BACK);    /* 背面削除 */
	glEnable(GL_CULL_FACE); /* 背面カリングを有効 */

	/* デプスバッファの設定 */
	glClearDepthf(1.0f);     /* 深度値を1.0(初期値と同じ) */
	glDepthFunc(GL_LESS);    /* ポリゴン深度がデプスバッファより小さい時に表示 */
	glEnable(GL_DEPTH_TEST); /* デプスバッファを有効 */
}
void MyGLFW::SetCallBack()
{
	glfwSetWindowUserPointer(m_window, this);
	glfwSetWindowSizeCallback(m_window, WindowCallBack);
	glfwSetScrollCallback(m_window, MouseScrollCallBack);
	glfwSetCursorPosCallback(m_window, MouseCursorCallBack);
	glfwSetMouseButtonCallback(m_window, MouseButtonCallBack);
}
/* キー入力コールバック関数 */
/* NOTE: 同時押しに対応していないため, デバッグ以外には使用しない. */
void MyGLFW::KeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	MyGLFW *win_p = static_cast<MyGLFW*>(glfwGetWindowUserPointer(window));

	const int check_range = key - CHAR_BIAS;
	if(check_range >= 0 && check_range < ALPHABET)
	{
		win_p->m_prev_key[check_range] = win_p->m_now_key[check_range];
		if(action != 0) { win_p->m_now_key[check_range] = true; }
		else { win_p->m_now_key[check_range] = false; }

		if(!win_p->m_prev_key[check_range] && win_p->m_now_key[check_range])
		{ win_p->m_key_state[check_range] = KeyState::STATE::PUSH; }
		else if(win_p->m_prev_key[check_range] && !win_p->m_now_key[check_range])
		{ win_p->m_key_state[check_range] = KeyState::STATE::RELEASE; }
	}
}
// ウィンドウ変更時コールバック関数
void MyGLFW::WindowCallBack(GLFWwindow *window,int width,int height)
{
	int fb_width, fb_height;
	glfwGetFramebufferSize(window, &fb_width, &fb_height);
	glViewport(0, 0, fb_width, fb_height);
	
	MyGLFW *win_p = static_cast<MyGLFW*>(glfwGetWindowUserPointer(window));
	if(win_p)
	{
		/* アスペクト比の計算 */
		win_p->m_aspect = static_cast<GLfloat>(width)/static_cast<GLfloat>(height);
		/* ウィンドウサイズの保存 */
		win_p->m_window_size[0] = static_cast<GLfloat>(width);
		win_p->m_window_size[1] = static_cast<GLfloat>(height);
	}
}
// マウススクロール時コールバック関数
void MyGLFW::MouseScrollCallBack(GLFWwindow* window, double xoffset, double yoffset)
{
	MyGLFW* win_p = static_cast<MyGLFW*>(glfwGetWindowUserPointer(window));
	win_p->m_scroll_vec_x = static_cast<int>(xoffset);
	win_p->m_scroll_vec_y = static_cast<int>(yoffset);
}
// マウスカーソルコールバック関数
void MyGLFW::MouseCursorCallBack(GLFWwindow* window, double xpos, double ypos)
{
	MyGLFW* win_p = static_cast<MyGLFW*>(glfwGetWindowUserPointer(window));
	win_p->m_mouse_pos_x = static_cast<GLfloat>(xpos);
	win_p->m_mouse_pos_y = static_cast<GLfloat>(ypos);
}
// マウスボタンコールバック関数
void MyGLFW::MouseButtonCallBack(GLFWwindow* window, int button, int action, int mods)
{
	MyGLFW* win_p = static_cast<MyGLFW*>(glfwGetWindowUserPointer(window));
	if (button == GLFW_MOUSE_BUTTON_RIGHT)  { win_p->m_mouse_button ^= MOUSE_BUTTON::RIGHT; }
	if (button == GLFW_MOUSE_BUTTON_MIDDLE) { win_p->m_mouse_button ^= MOUSE_BUTTON::MIDDLE; }
	if (button == GLFW_MOUSE_BUTTON_LEFT)   { win_p->m_mouse_button ^= MOUSE_BUTTON::LEFT; }
}

void MyGLFW::InitWindow(const int &width,const int &height,const char *title)
{
	/* width, height, title, fullscreen, multi */
	m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if(!m_window)
	{
		std::cout << "ERROR: Create Window" << std::endl;
		glfwTerminate();
		std::abort();
	}
	glfwMakeContextCurrent(m_window);
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		std::cout << "ERROR: glew Init" << std::endl;
		std::abort();
	}
	/*
		ドライバのバージョンによってglewInitでエラーが起こるため, glewInit時のエラーを無視する.
		OpenGL3.3移行の機能を使用時に発生する.
		参考: (https:)//www.khronos.org/opengl/wiki/OpenGL_Loading_Library
	*/
	glGetError();

	glfwSwapInterval(1);
	InitMode();
	SetCallBack();
	WindowCallBack(m_window, width, height);
	glfwSetTime(0.0f);
	last_time = static_cast<GLfloat>(glfwGetTime());
}
