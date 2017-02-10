#include "OverPassQuaternion.h"
namespace OverPass{

	const float Quaternion::msEpsilon = 1e-03;
	const Quaternion Quaternion::ZERO(0, 0, 0, 0);
	const Quaternion Quaternion::IDENTITY(1, 0, 0, 0);


	Quaternion Quaternion::operator+ (const Quaternion& rkQ) const {
		return Quaternion(w + rkQ.w, x + rkQ.x, y + rkQ.y, z + rkQ.z);
	}
	Quaternion Quaternion::operator- (const Quaternion& rkQ) const {
		return Quaternion(w - rkQ.w, x - rkQ.x, y - rkQ.y, z - rkQ.z);
	}
	Quaternion Quaternion::operator* (const Quaternion& rkQ) const
	{
		return Quaternion
			(
				w * rkQ.w - x * rkQ.x - y * rkQ.y - z * rkQ.z,
				w * rkQ.x + x * rkQ.w + y * rkQ.z - z * rkQ.y,
				w * rkQ.y + y * rkQ.w + z * rkQ.x - x * rkQ.z,
				w * rkQ.z + z * rkQ.w + x * rkQ.y - y * rkQ.x
				);
	}
	Quaternion Quaternion::operator* (const float fScalar)const
	{
		return Quaternion{ fScalar*w,fScalar*x,fScalar*y,fScalar*z };
	}
	Quaternion Quaternion::operator-() const
	{
		return Quaternion(-w, -x, -y, -z);
	}
	Vector3 Quaternion::operator* (const Vector3& v) const
	{
		// nVidia SDK implementation
		Vector3 uv, uuv;
		Vector3 qvec(x, y, z);
		uv = qvec.crossProduct(v);
		uuv = qvec.crossProduct(uv);
		uv *= (2.0f * w);
		uuv *= 2.0f;

		return v + uv + uuv;

	}
	float Quaternion::normalise(void)
	{
		float len = Norm();
		float factor = 1.0f / std::sqrtf(len);
		*this = *this*factor;
		return len;
	}
	float Quaternion::Norm() const 
	{
		return x*x+y*y+z*z+w*w;
	}
}