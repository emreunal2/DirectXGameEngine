

#pragma once
#include <memory>
#include <DX3D/Math/Vector3D.h>
#include <DX3D/Math/Vector4D.h>

class Matrix4x4
{
public:
	Matrix4x4()
	{
		m_mat[0][0] = 1;
		m_mat[1][1] = 1;
		m_mat[2][2] = 1;
		m_mat[3][3] = 1;
	}

	void setIdentity()
	{
		::memset(m_mat, 0, sizeof(float) * 16);
		m_mat[0][0] = 1;
		m_mat[1][1] = 1;
		m_mat[2][2] = 1;
		m_mat[3][3] = 1;
	}

	void setTranslation(const Vector3D& translation)
	{
		m_mat[3][0] = translation.getx();
		m_mat[3][1] = translation.gety();
		m_mat[3][2] = translation.getz();
	}

	void setScale(const Vector3D& scale)
	{
		m_mat[0][0] = scale.getx();
		m_mat[1][1] = scale.gety();
		m_mat[2][2] = scale.getz();
	}

	void setRotationX(f32 x)
	{
		m_mat[1][1] = cos(x);
		m_mat[1][2] = sin(x);
		m_mat[2][1] = -sin(x);
		m_mat[2][2] = cos(x);
	}

	void setRotationY(f32 y)
	{
		m_mat[0][0] = cos(y);
		m_mat[0][2] = -sin(y);
		m_mat[2][0] = sin(y);
		m_mat[2][2] = cos(y);
	}

	void setRotationZ(f32 z)
	{
		m_mat[0][0] = cos(z);
		m_mat[0][1] = sin(z);
		m_mat[1][0] = -sin(z);
		m_mat[1][1] = cos(z);
	}

	f32 getDeterminant()
	{
		Vector4D minor;
		f32 det;

		Vector4D v1 = Vector4D(this->m_mat[0][0], this->m_mat[1][0], this->m_mat[2][0], this->m_mat[3][0]);
		Vector4D v2 = Vector4D(this->m_mat[0][1], this->m_mat[1][1], this->m_mat[2][1], this->m_mat[3][1]);
		Vector4D v3 = Vector4D(this->m_mat[0][2], this->m_mat[1][2], this->m_mat[2][2], this->m_mat[3][2]);


		minor.cross(v1, v2, v3);
		det = -(this->m_mat[0][3] * minor.getx() + this->m_mat[1][3] * minor.gety() + this->m_mat[2][3] * minor.getz() +
			this->m_mat[3][3] * minor.getm_w());
		return det;
	}

	void inverse()
	{
		i32 a, j;
		f32 det;

		det = this->getDeterminant();
		if (!det) return;
		Matrix4x4 out;
		Vector4D v, vec[3];
		for (i32 i = 0; i<4; i++)
		{
			for (j = 0; j<4; j++)
			{
				if (j != i)
				{
					a = j;
					if (j > i) a -= 1;
					vec[a].setx(this->m_mat[j][0]);
					vec[a].sety(this->m_mat[j][1]);
					vec[a].setz(this->m_mat[j][2]);
					vec[a].setm_w(this->m_mat[j][3]);
				}
			}
			v.cross(vec[0], vec[1], vec[2]);

			out.m_mat[0][i] = (float)pow(-1.0f, i) * v.getx() / det;
			out.m_mat[1][i] = (float)pow(-1.0f, i) * v.gety() / det;
			out.m_mat[2][i] = (float)pow(-1.0f, i) * v.getz() / det;
			out.m_mat[3][i] = (float)pow(-1.0f, i) * v.getm_w() / det;
		}

		this->setMatrix(out);
	}


	void operator *=(const Matrix4x4& matrix)
	{
		Matrix4x4 out;
		for (i32 i = 0; i < 4; i++)
		{
			for (i32 j = 0; j < 4; j++)
			{
				out.m_mat[i][j] =
					m_mat[i][0] * matrix.m_mat[0][j] + m_mat[i][1] * matrix.m_mat[1][j] + 
					m_mat[i][2] * matrix.m_mat[2][j] + m_mat[i][3] * matrix.m_mat[3][j];
			}
		}
		setMatrix(out);
	}

	void setMatrix(const Matrix4x4& matrix)
	{
		::memcpy(m_mat, matrix.m_mat, sizeof(float) * 16);
	}

	Vector3D getXDirection()
	{
		return Vector3D(m_mat[0][0], m_mat[0][1], m_mat[0][2]);
	}
	Vector3D getYDirection()
	{
		return Vector3D(m_mat[1][0], m_mat[1][1], m_mat[1][2]);
	}
	Vector3D getZDirection()
	{
		return Vector3D(m_mat[2][0], m_mat[2][1], m_mat[2][2]);
	}
	
	Vector3D getTranslation()
	{
		return Vector3D(m_mat[3][0], m_mat[3][1], m_mat[3][2]);
	}

	void setPerspectiveFovLH(f32 fov, f32 aspect, f32 znear, f32 zfar)
	{
		f32 yscale = 1.0f / tan(fov / 2.0f);
		f32 xscale = yscale / aspect;
		m_mat[0][0] = xscale;
		m_mat[1][1] = yscale;
		m_mat[2][2] = zfar / (zfar - znear);
		m_mat[2][3] = 1.0f;
		m_mat[3][2] = (-znear*zfar)/ (zfar - znear);
		m_mat[3][3] = 0.0f;
	}


	void setOrthoLH(f32 width,f32 height,f32 near_plane, f32 far_plane)
	{
		setIdentity();
		m_mat[0][0] = 2.0f / width;
		m_mat[1][1] = 2.0f / height;
		m_mat[2][2] = 1.0f / (far_plane - near_plane);
		m_mat[3][2] = -(near_plane / (far_plane - near_plane));
	}

	~Matrix4x4() = default;

private:
	f32 m_mat[4][4] = {};
};