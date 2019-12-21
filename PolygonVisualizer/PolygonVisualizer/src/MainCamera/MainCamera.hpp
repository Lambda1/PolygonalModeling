#ifndef __MAIN_CAMERA_HPP__
#define __MAIN_CAMERA_HPP__

template<class T>
class MainCamera
{
private:
	// ��p�p�����[�^
	inline static constexpr double MAX_FOV = 3.1415926535;
	inline static constexpr double MIN_FOV = 0.001;

	// �g�嗦
	T fov_magnification;

public:
	// �J�������W
	T x, y, z, w;
	// up�x�N�g��
	T up_x, up_y, up_z;
	// �����_���W
	T gx, gy, gz;
	// ��p
	T fov;

	MainCamera():
		fov_magnification(0),
		x(0), y(0), z(0), w(1),
		up_x(0), up_y(1), up_z(0),
		gx(0), gy(0), gz(0),
		fov(1.0)
	{
	}
	virtual ~MainCamera()
	{
	}

	// �Y�[������
	inline void ZoomIn ()
	{
		fov -= fov_magnification;
		if (fov < static_cast<T>(MIN_FOV)) { fov = static_cast<T>(MIN_FOV); }
	}
	inline void ZoomOut()
	{
		fov += fov_magnification;
		if (fov > static_cast<T>(MAX_FOV)) { fov = static_cast<T>(MAX_FOV); }
	}

	// Setter
	inline void SetPos(const T& x, const T& y, const T& z)
	{
		this->x = x, this->y = y, this->z = z;
	}
	inline void SetGazePos(const T& x, const T& y, const T& z)
	{
		this->gx = x, this->gy = y, this->gz = z;
	}
	inline void SetMagnification(const T& magnification)
	{
		fov_magnification = magnification;
	}
};

#endif