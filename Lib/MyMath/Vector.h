#pragma once
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

/// <summary>
/// 二次元ベクトル
/// </summary>
struct Vec2f {

	float x;
	float y;

	Vec2f operator+(const Vec2f& other) const {
		return { x + other.x, y + other.y };
	}

	Vec2f operator-(const Vec2f& other) const {
		return { x - other.x, y - other.y };
	}

	Vec2f operator*(float scalar) const {
		return { x * scalar, y * scalar };
	}

	Vec2f& operator+=(const Vec2f& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	Vec2f& operator-=(const Vec2f& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
};

/// <summary>
/// 三次元ベクトル
/// </summary>
struct Vec3f {

	float x;
	float y;
	float z;

	Vec3f operator+(const Vec3f& other) const {
		return { x + other.x, y + other.y, z + other.z };
	}

	Vec3f operator-(const Vec3f& other) const {
		return { x - other.x, y - other.y, z - other.z };
	}

	Vec3f& operator+=(const Vec3f& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vec3f& operator-=(const Vec3f& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	// 乗算演算子のオーバーロード
	Vec3f operator*(float scalar) const {
		return Vec3f(x * scalar, y * scalar, z * scalar);
	}

	// オーバーロードされた乗算演算子の逆向きのオーバーロード
	friend Vec3f operator*(float scalar, const Vec3f& vec) {
		return Vec3f(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}
};

/// <summary>
/// 四次元ベクトル
/// </summary>
struct Vec4f {

	float x;
	float y;
	float z;
	float w;

	Vec4f operator+(const Vec4f& other) const {
		return { x + other.x, y + other.y, z + other.z, w + other.w };
	}

	Vec4f operator-(const Vec4f& other) const {
		return { x - other.x, y - other.y, z - other.z, w - other.w };
	}

	Vec4f operator*(float scalar) const {
		return { x * scalar, y * scalar, z * scalar, w * scalar };
	}
};