#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>
#include <math.h>
#include "../Hooks/wglSwapBuffers/Libs/Imgui/imgui.h"

struct ViewMatrix
{
	constexpr float* operator[](int index) noexcept
	{
		return data[index];
	}

	constexpr const float* operator[](int index) const noexcept
	{
		return data[index];
	}

	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;

		};
		float data[4][4];
	};
};

struct Vector3
{
	constexpr Vector3(const float x = 0.f, const float y = 0.f, const float z = 0.f) noexcept :
		x(x), y(y), z(z) { }

	constexpr Vector3 operator+(const Vector3& other) const noexcept
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	constexpr Vector3 operator-(const Vector3& other) const noexcept
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	constexpr Vector3 operator*(const Vector3& other) const noexcept
	{
		return Vector3(x * other.x, y * other.y, z * other.z);
	}

	constexpr Vector3 operator*(const float scale) const noexcept
	{
		return Vector3(x * scale, y * scale, z * scale);
	}
	constexpr Vector3 operator/(const float scale) const noexcept
	{
		return Vector3(x / scale, y / scale, z / scale);
	}

	constexpr float operator[](const size_t index) const noexcept
	{
		if (index == 0) return x;
		if (index == 1) return y;
		if (index == 2) return z;
	}

	const Vector3 Normalize()
	{
		const float len = std::sqrt(x * x + y * y + z * z);

		if (len != 0.)
		{
			x /= len;
			y /= len;
			z /= len;
		}
		return *this;
	}
	float LengthTo(const Vector3& other) const noexcept
	{
		return std::sqrtf((x - other.x) * (x - other.x) +
			(y - other.y) * (y - other.y) +
			(z - other.z) * (z - other.z));
	}
	bool IsEqual(const Vector3& other, const float margin = std::numeric_limits<float>::epsilon()) const noexcept
	{
		return (std::fabsf(x - other.x) < margin &&
			std::fabsf(y - other.y) < margin &&
			std::fabsf(z - other.z) < margin);
	}

	constexpr Vector3 Scale(const float scale) const noexcept
	{
		return Vector3{ x * scale, y * scale, z * scale };
	}

	float Length() const noexcept
	{
		return std::sqrtf(x * x + y * y + z * z);
	}
	float sqrMagnitude() const noexcept
	{
		return x * x + y * y + z * z;
	}
	//Vector3 operator*(const Matrix4x4& mat) const noexcept
	//{
	//	Vector4 result;

	//	result.x = x * mat[0][0] + y * mat[1][0] + z * mat[2][0] + w * mat[3][0];
	//	result.y = x * mat[0][1] + y * mat[1][1] + z * mat[2][1] + w * mat[3][1];
	//	result.z = x * mat[0][2] + y * mat[1][2] + z * mat[2][2] + w * mat[3][2];
	//	result.w = x * mat[0][3] + y * mat[1][3] + z * mat[2][3] + w * mat[3][3];

	//	return result.ToVector3();
	//}
	float x, y, z;

};
struct Vector2
{
public:
	float x, y;

	Vector2() { x = y = 0; }
	Vector2(const float x, const float y) : x(x), y(y) {}
	Vector2 operator + (const Vector2& rhs) const { return Vector2(x + rhs.x, y + rhs.y); }
	Vector2 operator - (const Vector2& rhs) const { return Vector2(x - rhs.x, y - rhs.y); }
	Vector2 operator * (const float& rhs) const { return Vector2(x * rhs, y * rhs); }
	Vector2 operator / (const float& rhs) const { return Vector2(x / rhs, y / rhs); }
	Vector2& operator += (const Vector2& rhs) { return *this = *this + rhs; }
	Vector2& operator -= (const Vector2& rhs) { return *this = *this - rhs; }
	Vector2& operator *= (const float& rhs) { return *this = *this * rhs; }
	Vector2& operator /= (const float& rhs) { return *this = *this / rhs; }
	float operator[](int i) const {
		return ((float*)this)[i];
	}
	operator ImVec2()
	{
		return ImVec2(this->x, this->y);
	}
	Vector2 Min(const Vector2 vec) const noexcept
	{
		return Vector2{ min(x, vec.x), min(y, vec.y) };
	}
	Vector2 Max(const Vector2 vec) const noexcept
	{
		return Vector2{ max(x, vec.x), max(y, vec.y) };
	}
	static Vector2 Min(const Vector2 vec, const Vector2 vec2) noexcept
	{
		return Vector2{ min(vec2.x, vec.x), min(vec2.y, vec.y) };
	}
	static Vector2 Max(const Vector2 vec, const Vector2 vec2) noexcept
	{
		return Vector2{ max(vec2.x, vec.x), max(vec2.y, vec.y) };
	}
	float LengthTo(const Vector2& other) const noexcept
	{
		return std::sqrtf((x - other.x) * (x - other.x) +
			(y - other.y) * (y - other.y));
	}

	float& operator[](int i);
	float dot() const { return x * x + y * y; }
	float Length() const { return sqrtf(dot()); }
};