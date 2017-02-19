#pragma once


#ifndef __Matrix3_H__
#define __Matrix3_H__

#include "OverPassPrerequisites.h"

#include "OverPassVector3.h"

namespace OverPass
{

	class  Matrix4
	{
	public:
		float m[4][4];
		Matrix4()
		{
			m[0][0] = 1.0;
		}
		~Matrix4()
		{
		}
		inline Matrix4(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33)
		{
			m[0][0] = m00;
			m[0][1] = m01;
			m[0][2] = m02;
			m[0][3] = m03;
			m[1][0] = m10;
			m[1][1] = m11;
			m[1][2] = m12;
			m[1][3] = m13;
			m[2][0] = m20;
			m[2][1] = m21;
			m[2][2] = m22;
			m[2][3] = m23;
			m[3][0] = m30;
			m[3][1] = m31;
			m[3][2] = m32;
			m[3][3] = m33;
		}
		static const Matrix4 ZERO;
		static const Matrix4 ZEROAFFINE;
		static const Matrix4 IDENTITY;
		/** Useful little matrix which takes 2D clipspace {-1, 1} to {0,1}
		and inverts the Y. */
		static const Matrix4 CLIPSPACE2DTOIMAGESPACE;
	};
}
#endif
