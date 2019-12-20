#ifndef __MAIN_CAMERA_HPP__
#define __MAIN_CAMERA_HPP__

template<class T>
class MainCamera
{
private:
	// ��p�p�����[�^
	inline static constexpr T MAX_FOV = static_cast<T>(1.00);
	inline static constexpr T MIN_FOV = static_cast<T>(0.01);

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
		if (fov < MIN_FOV) { fov = MIN_FOV; }
	}
	inline void ZoomOut()
	{
		fov += fov_magnification;
		if (fov > MAX_FOV) { fov = MAX_FOV; }
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