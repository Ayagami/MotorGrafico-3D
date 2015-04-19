#pragma once
#include "../myEngine_API.h"

namespace DoMaRe{
	class MYENGINE_API Vector3{
	public:
		Vector3(float x, float y, float z);

		Vector3();

		float x;

		float y;

		float z;

		Vector3& operator =(const Vector3& vector);

		Vector3 operator +(const Vector3& vector) const; 

		Vector3 operator -(const Vector3& vector) const; 

		Vector3 operator *(const float& escalar)const; 

		Vector3 operator /(const float& n)const;

		Vector3& operator +=(const Vector3& vector);

		Vector3& operator -=(const Vector3& vector);

		Vector3& operator *=(const float& escalar);

		Vector3& operator /=(const float& n);



		bool operator ==(const Vector3& vector) const;

		bool operator !=(const Vector3& vector) const;

		float GetMagnitude() const;

		Vector3 Normalize();
	};
}