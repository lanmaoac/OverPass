#pragma once
#include "OverPassPrerequisites.h"
#include "OverPassQuaternion.h"
namespace OverPass {
	class Vector3
	{
	public:
		float x, y, z;
		inline Vector3()
		{

		}
		inline Vector3(const float fx, const float  fy, const float fz)
			:x(fx), y(fy), z(fz)
		{
		}
		inline Vector3(const int afCoordinate[3])
		{
			x = (float)afCoordinate[0];
			y = (float)afCoordinate[1];
			z = (float)afCoordinate[2];
		}
		inline Vector3 (const float scaler)
			:x(scaler)
			,y(scaler)
			,z(scaler)
		{

		}
		inline void swap(Vector3& other)
		{
			std::swap(x, other.x);
			std::swap(y, other.y);
			std::swap(z, other.z);
		}
		inline float operator [](const int i) const
		{
			assert(i < 3);
			return *(&x + i);
		}
		inline float& operator[](const int i)
		{
			assert(i < 3);
			return *(&x + i);
		}
		inline Vector3 operator = (const Vector3& rkVector)
		{
			x = rkVector.x;
			y = rkVector.y;
			z = rkVector.z;
			return *this;
		}
		inline bool operator == (const Vector3& rkVector) const
		{
			return (x == rkVector.x && y == rkVector.y && z == rkVector.z);
		}

		inline bool operator != (const Vector3& rkVector) const
		{
			return (x != rkVector.x || y != rkVector.y || z != rkVector.z);
		}

		// arithmetic operations
		inline Vector3 operator + (const Vector3& rkVector) const
		{
			return Vector3(
				x + rkVector.x,
				y + rkVector.y,
				z + rkVector.z);
		}

		inline Vector3 operator - (const Vector3& rkVector) const
		{
			return Vector3(
				x - rkVector.x,
				y - rkVector.y,
				z - rkVector.z);
		}

		inline Vector3 operator * (const float fScalar) const
		{
			return Vector3(
				x * fScalar,
				y * fScalar,
				z * fScalar);
		}

		inline Vector3 operator * (const Vector3& rhs) const
		{
			return Vector3(
				x * rhs.x,
				y * rhs.y,
				z * rhs.z);
		}

		inline Vector3 operator / (const float fScalar) const
		{
			assert(fScalar != 0.0);

			float fInv = 1.0f / fScalar;

			return Vector3(
				x * fInv,
				y * fInv,
				z * fInv);
		}
		inline Vector3 operator / (const Vector3& rhs) const
		{
			return Vector3(
				x / rhs.x,
				y / rhs.y,
				z / rhs.z);
		}

		inline const Vector3& operator + () const
		{
			return *this;
		}

		inline Vector3 operator - () const
		{
			return Vector3(-x, -y, -z);
		}

		inline Vector3& operator += (const Vector3& rkVector)
		{
			x += rkVector.x;
			y += rkVector.y;
			z += rkVector.z;

			return *this;
		}

		inline Vector3& operator += (const float fScalar)
		{
			x += fScalar;
			y += fScalar;
			z += fScalar;
			return *this;
		}

		inline Vector3& operator -= (const Vector3& rkVector)
		{
			x -= rkVector.x;
			y -= rkVector.y;
			z -= rkVector.z;

			return *this;
		}

		inline Vector3& operator -= (const float fScalar)
		{
			x -= fScalar;
			y -= fScalar;
			z -= fScalar;
			return *this;
		}

		inline Vector3& operator *= (const float fScalar)
		{
			x *= fScalar;
			y *= fScalar;
			z *= fScalar;
			return *this;
		}

		inline Vector3& operator *= (const Vector3& rkVector)
		{
			x *= rkVector.x;
			y *= rkVector.y;
			z *= rkVector.z;

			return *this;
		}

		inline Vector3& operator /= (const float fScalar)
		{
			assert(fScalar != 0.0);

			float fInv = 1.0f / fScalar;

			x *= fInv;
			y *= fInv;
			z *= fInv;

			return *this;
		}

		inline Vector3& operator /= (const Vector3& rkVector)
		{
			x /= rkVector.x;
			y /= rkVector.y;
			z /= rkVector.z;

			return *this;
		}

		inline float length() const
		{
			return std::sqrt(x*x + y*y + z*z);
		}
		inline float squaredLength() const
		{
			return x*x + y*y + z*z;
		}
		inline float distance(const Vector3& rhs) const
		{
			return (*this - rhs).length();
		}
		inline float squaredDistance(const Vector3& rhs) const
		{
			return (*this - rhs).squaredLength();

		}
		inline float dotProduct(const Vector3& rhs) const {
			return x*rhs.x + y*rhs.y + z*rhs.z;
		}
		inline void normalise()
		{
			float fLength = length();
			if (fLength > 0.0f)
			{
				float fInvLength = 1.0f / fLength;
				x *= fInvLength;
				y *= fInvLength;
				z *= fInvLength;
			}
		}
		inline Vector3 crossProduct(const Vector3& rkVector3) const
		{
			return Vector3(
				y*rkVector3.z - z*rkVector3.y,
				z*rkVector3.x - x*rkVector3.z,
				x*rkVector3.y-y*rkVector3.x);
		}
		inline bool operator < (const Vector3& rhs) const
		{
			if (x < rhs.x && y < rhs.y && z < rhs.z)
				return true;
			return false;
		}
		void printf(void)
		{
			std::printf("%f %f %f\n",x,y,z);
		}

		/** Returns true if the vector's scalar components are all smaller
		that the ones of the vector it is compared against.
		*/
		inline bool operator > (const Vector3& rhs) const
		{
			if (x > rhs.x && y > rhs.y && z > rhs.z)
				return true;
			return false;
		}
		static const Vector3 ZERO;
		static const Vector3 UNIT_X;
		static const Vector3 UNIT_Y;
		static const Vector3 UNIT_Z;
		static const Vector3 NEGATIVE_UNIT_X;
		static const Vector3 NEGATIVE_UNIT_Y;
		static const Vector3 NEGATIVE_UNIT_Z;
		static const Vector3 UNIT_SCALE;

	};
}