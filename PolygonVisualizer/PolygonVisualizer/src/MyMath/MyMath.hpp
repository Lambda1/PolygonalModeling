#ifndef __MY_MATH_HPP__
#define __MY_MATH_HPP__

/* ���w�N���X */
/* NOTE: ���ʏ��� */

#include <iostream>
#include <cmath>

namespace my
{
	class math
	{
		inline static double* m_sin_table = nullptr;
		inline static int m_resolution = 0;
	public:
		/* �ϐ� */
		inline static constexpr double PI = 3.14159265;

		/* �R�s�[�֎~ */
		math() = delete;
		math(const math&) = delete;
		math& operator=(const math&) = delete;
		/* �f�X�g���N�^ */
		~math()
		{
			if (m_sin_table)
			{
				delete[] m_sin_table;
				m_sin_table = nullptr;
			}
		}

		/* ���W�A��-�p�x�ϊ� */
		inline static double toDegree(const double& radian) { return (radian * 180.0) / PI; }
		inline static double toRadian(const double& degree) { return (degree / 180.0) * PI; }
		inline static double NormalizeRadian(double radian)
		{
			if (radian < 0.0 || radian > 2.0 * PI)
			{
				const int div = static_cast<int>(radian / (2.0 * PI));
				radian -= (div * (2.0 * PI)); /* �]�蕪��2PI������ */

				if (radian < 0.0) radian += (2.0 * PI);
			}
			return radian;
		}

		/* �]�� */
		template<class T>
		inline static int mod(const T& value, const T& key)
		{
			return (static_cast<int>(value) % static_cast<int>(key));
		}

		/* �O�p�֐� */
		/* �e�[�u�������� */
		/* NOTE: �������ߖ�̂���, 0-90�x�ŏ����� */
		inline static void InitTrigonoMetric(const int &resolution)
		{
			/* �m�ۍς݂̎���, �������Ȃ� */
			if (m_sin_table) return;
			
			m_resolution = resolution;
			m_sin_table = new double[m_resolution + 1];

			if (!m_sin_table)
			{
				std::cerr << "ERROR: SIN TABLE IS NULL." << std::endl;
				std::abort();
			}

			for (int i = 0; i <= m_resolution; ++i)
			{
				m_sin_table[i] = std::sin((static_cast<double>(i) / m_resolution) * (PI / 2.0));
			}
		}
		/* sin */
		inline static double sin(double radian)
		{
			if (!m_sin_table) { return 0.0; }
			
			/* �p�x�̐��K�� */
			radian = NormalizeRadian(radian);
			/* [0,90] */
			if (radian <= (PI / 2.0))
			{
				const double value = radian / (PI / 2.0) * m_resolution;
				return m_sin_table[static_cast<int>(value) % (m_resolution+1)];
			}
			/* [90,180] */
			else if (radian <= PI)
			{
				const double value = (PI - radian) / (PI / 2.0) * m_resolution;
				return m_sin_table[static_cast<int>(value) % (m_resolution+1)];
			}
			/* [180,270) */
			else if (radian >= PI && radian <= (PI / 2.0) * 3.0)
			{
				const double value = (radian - PI) / (PI / 2.0) * m_resolution;
				return -m_sin_table[static_cast<int>(value) % (m_resolution+1)];
			}

			const double value = (PI * 2.0 - radian) / (PI / 2.0) * m_resolution;
			return -m_sin_table[static_cast<int>(value) % (m_resolution+1)];
		}
		/* cos */
		/* NOTE: sin�ɂ��ϊ� */
		inline static double cos(const double& radian)
		{
			if (!m_sin_table) { return 0.0; }
			return sin(radian + PI / 2.0);
		}
		/* tan */
		/* NOTE: sin-cos�ɂ��ϊ� */
		inline static double tan(const double& radian)
		{
			if (!m_sin_table) { return 0.0; }
			return (sin(radian)/cos(radian));
		}
	};
};

#endif