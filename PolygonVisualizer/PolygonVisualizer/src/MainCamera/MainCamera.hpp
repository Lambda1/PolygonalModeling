#ifndef __MAIN_CAMERA_HPP__
#define __MAIN_CAMERA_HPP__

template<class T>
class MainCamera
{
private:

public:
	// カメラ座標
	T x, y, z, w;
	// upベクトル
	T up_x, up_y, up_z;

	MainCamera():
		x(0), y(0), z(0), w(1),
		up_x(0), up_y(1), up_z(0)
	{
	}
	virtual ~MainCamera()
	{
	}

	inline void SetPos(const T& x, const T& y, const T& z)
	{
		this->x = x, this->y = y, this->z = z;
	}
};

#endif