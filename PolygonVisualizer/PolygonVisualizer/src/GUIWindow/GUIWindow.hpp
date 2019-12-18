#ifndef __GUI_WINDOW_HPP__
#define __GUI_WINDOW_HPP__

class GUIWindow
{
public:
	virtual ~GUIWindow() {}

	// XVˆ—
	virtual void Update() = 0;
};

#endif // !__GUI_WINDOW_HPP__