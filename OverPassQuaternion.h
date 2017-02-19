#pragma once
#include "OverPassPrerequisites.h"
#include "OverPassVector3.h"

namespace OverPass{

	class Quaternion
	{
	public:
		inline Quaternion()
			:w(1), x(0), y(0), z(0)
		{

		}
		inline Quaternion(float fw, float fx, float fy, float fz)
		{
			w = fw;
			x = fx;
			y = fy;
			z = fz;
		}
		inline void swap(Quaternion &other)
		{
			std::swap(w, other.w);
			std::swap(x, other.x);
			std::swap(y, other.y);
			std::swap(z, other.z);
		}
		inline float operator [](const int i) const
		{
			//assert(i < 4);
			return *(&w + i);
		}
		inline float& operator[] (const int i)
		{
			assert(i < 4);
			return *(&w + i);
		}
		inline Quaternion& operator = (const Quaternion& rkq)
		{
			w = rkq.w;
			x = rkq.x;
			y = rkq.y;
			z = rkq.z;
			return *this;
		}
		Quaternion operator+ (const Quaternion& rkQ) const;
		Quaternion operator- (const Quaternion& rkQ) const;
		Quaternion operator* (const Quaternion& rkQ) const;
	
		Quaternion operator* (float fScalar) const;
		//Vector3 operator* (const Vector3& rkVector) const;
		Quaternion operator- () const;
		
		inline bool operator== (const Quaternion& rhs) const
		{
			return (rhs.x == x) && (rhs.y == y) &&
				(rhs.z == z) && (rhs.w == w);
		}
		inline bool operator!= (const Quaternion& rhs) const
		{
			bool now=(rhs.x == x) && (rhs.y == y) &&
				(rhs.z == z) && (rhs.w == w);
			return !now;
		}

		
		
		float normalise(void);
		float Norm() const;

		static const float msEpsilon;
		static const Quaternion ZERO;
		static const Quaternion IDENTITY;
		float w, x, y, z;

	};
}