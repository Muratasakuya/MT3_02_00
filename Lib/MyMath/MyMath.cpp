﻿#include "MyMath.h"

/// <summary>
/// πの値の取得
/// </summary>
/// <returns></returns>
float Pi() { return static_cast<float>(M_PI); }

/// <summary>
/// 内積
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
float Dot(const Vec3f& v1, const Vec3f& v2) {

	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/// <summary>
/// 長さ、ノルム
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
float Length(const Vec3f& v) {

	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

/// <summary>
/// 正規化
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
Vec3f Normalize(const Vec3f& v) {

	float length = Length(v);
	if (length != 0) {
		return Vec3f(v.x / length, v.y / length, v.z / length);
	}
	else {

		// 値が入ってなければnullで返す
		return Vec3f(0.0f, 0.0f, 0.0f);
	}
}

/// <summary>
/// クロス積
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vec3f Cross(const Vec3f& v1, const Vec3f& v2) {

	return Vec3f(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	);
}

/// <summary>
/// 4x4行列の加算
/// </summary>
/// <param name="m1"></param>
/// <param name="m2"></param>
/// <returns></returns>
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {

	Matrix4x4 matrix;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}
	return matrix;
}

/// <summary>
/// 4x4行列の減算
/// </summary>
/// <param name="m1"></param>
/// <param name="m2"></param>
/// <returns></returns>
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {

	Matrix4x4 matrix;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}
	return matrix;
}

/// <summary>
/// 4x4行列の積
/// </summary>
/// <param name="m1"></param>
/// <param name="m2"></param>
/// <returns></returns>
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {

	Matrix4x4 matrix;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix.m[i][j] = 0;
			for (int k = 0; k < 4; ++k) {
				matrix.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return matrix;
}

/// <summary>
/// 4x4行列の逆行列
/// </summary>
/// <param name="m"></param>
/// <returns></returns>
Matrix4x4 Inverse(const Matrix4x4& m) {

	Matrix4x4 matrix = {};

	float det =
		m.m[0][0] * (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] +
			m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][3] * m.m[3][2] -
			m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][3] * m.m[2][2] * m.m[3][1]) -
		m.m[0][1] * (m.m[1][0] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][0] +
			m.m[1][3] * m.m[2][0] * m.m[3][2] - m.m[1][0] * m.m[2][3] * m.m[3][2] -
			m.m[1][2] * m.m[2][0] * m.m[3][3] - m.m[1][3] * m.m[2][2] * m.m[3][0]) +
		m.m[0][2] * (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] +
			m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][0] * m.m[2][3] * m.m[3][1] -
			m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][3] * m.m[2][1] * m.m[3][0]) -
		m.m[0][3] * (m.m[1][0] * m.m[2][1] * m.m[3][2] + m.m[1][1] * m.m[2][2] * m.m[3][0] +
			m.m[1][2] * m.m[2][0] * m.m[3][1] - m.m[1][0] * m.m[2][2] * m.m[3][1] -
			m.m[1][1] * m.m[2][0] * m.m[3][2] - m.m[1][2] * m.m[2][1] * m.m[3][0]);

	float invDet = 1.0f / det;

	matrix.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] +
		m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][3] * m.m[3][2] -
		m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][3] * m.m[2][2] * m.m[3][1]) *
		invDet;
	matrix.m[0][1] = (m.m[0][1] * m.m[2][3] * m.m[3][2] + m.m[0][2] * m.m[2][1] * m.m[3][3] +
		m.m[0][3] * m.m[2][2] * m.m[3][1] - m.m[0][1] * m.m[2][2] * m.m[3][3] -
		m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2]) *
		invDet;
	matrix.m[0][2] = (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] +
		m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][3] * m.m[3][2] -
		m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][3] * m.m[1][2] * m.m[3][1]) *
		invDet;
	matrix.m[0][3] = (m.m[0][1] * m.m[1][3] * m.m[2][2] + m.m[0][2] * m.m[1][1] * m.m[2][3] +
		m.m[0][3] * m.m[1][2] * m.m[2][1] - m.m[0][1] * m.m[1][2] * m.m[2][3] -
		m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2]) *
		invDet;

	matrix.m[1][0] = (m.m[1][0] * m.m[2][3] * m.m[3][2] + m.m[1][2] * m.m[2][0] * m.m[3][3] +
		m.m[1][3] * m.m[2][2] * m.m[3][0] - m.m[1][0] * m.m[2][2] * m.m[3][3] -
		m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2]) *
		invDet;
	matrix.m[1][1] = (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] +
		m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][3] * m.m[3][2] -
		m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][3] * m.m[2][2] * m.m[3][0]) *
		invDet;
	matrix.m[1][2] = (m.m[0][0] * m.m[1][3] * m.m[3][2] + m.m[0][2] * m.m[1][0] * m.m[3][3] +
		m.m[0][3] * m.m[1][2] * m.m[3][0] - m.m[0][0] * m.m[1][2] * m.m[3][3] -
		m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2]) *
		invDet;
	matrix.m[1][3] = (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] +
		m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][3] * m.m[2][2] -
		m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][3] * m.m[1][2] * m.m[2][0]) *
		invDet;

	matrix.m[2][0] = (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] +
		m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][0] * m.m[2][3] * m.m[3][1] -
		m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][3] * m.m[2][1] * m.m[3][0]) *
		invDet;
	matrix.m[2][1] = (m.m[0][0] * m.m[2][3] * m.m[3][1] + m.m[0][1] * m.m[2][0] * m.m[3][3] +
		m.m[0][3] * m.m[2][1] * m.m[3][0] - m.m[0][0] * m.m[2][1] * m.m[3][3] -
		m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1]) *
		invDet;
	matrix.m[2][2] = (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] +
		m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][0] * m.m[1][3] * m.m[3][1] -
		m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][3] * m.m[1][1] * m.m[3][0]) *
		invDet;
	matrix.m[2][3] = (m.m[0][0] * m.m[1][3] * m.m[2][1] + m.m[0][1] * m.m[1][0] * m.m[2][3] +
		m.m[0][3] * m.m[1][1] * m.m[2][0] - m.m[0][0] * m.m[1][1] * m.m[2][3] -
		m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1]) *
		invDet;

	matrix.m[3][0] = (m.m[1][0] * m.m[2][2] * m.m[3][1] + m.m[1][1] * m.m[2][0] * m.m[3][2] +
		m.m[1][2] * m.m[2][1] * m.m[3][0] - m.m[1][0] * m.m[2][1] * m.m[3][2] -
		m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1]) *
		invDet;
	matrix.m[3][1] = (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] +
		m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][0] * m.m[2][2] * m.m[3][1] -
		m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][2] * m.m[2][1] * m.m[3][0]) *
		invDet;
	matrix.m[3][2] = (m.m[0][0] * m.m[1][2] * m.m[3][1] + m.m[0][1] * m.m[1][0] * m.m[3][2] +
		m.m[0][2] * m.m[1][1] * m.m[3][0] - m.m[0][0] * m.m[1][1] * m.m[3][2] -
		m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1]) *
		invDet;
	matrix.m[3][3] = (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] +
		m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][0] * m.m[1][2] * m.m[2][1] -
		m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][2] * m.m[1][1] * m.m[2][0]) *
		invDet;

	if (det == 0) {

		return matrix;
	}

	return matrix;
}

/// <summary>
/// 4x4行列の転置行列
/// </summary>
/// <param name="m"></param>
/// <returns></returns>
Matrix4x4 Transpose(const Matrix4x4& m) {

	Matrix4x4 matrix;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix.m[i][j] = m.m[j][i];
		}
	}

	return matrix;
}

/// <summary>
/// 4x4行列の単位行列
/// </summary>
/// <returns></returns>
Matrix4x4 MakeIdentity4x4() {

	Matrix4x4 matrix;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix.m[i][j] = (i == j) ? 1.0f : 0.0f;
		}
	}

	return matrix;
}

/// <summary>
/// 4x4行列の拡縮行列
/// </summary>
/// <param name="scale"></param>
/// <returns></returns>
Matrix4x4 MakeScaleMatrix(const Vec3f& scale) {

	Matrix4x4 scaleMatrix = {
		scale.x, 0.0f, 0.0f ,0.0f,
		0.0f, scale.y, 0.0f, 0.0f,
		0.0f, 0.0f, scale.z, 0.0f,
		0.0f ,0.0f, 0.0f, 1.0f
	};

	return scaleMatrix;
}

/// <summary>
/// 4x4行列のX軸回転行列
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 MakePitchMatrix(float radian) {

	float cosTheta = std::cos(radian);
	float sinTheta = std::sin(radian);

	Matrix4x4 pitchMatrix = {
		1.0f, 0.0f,0.0f,0.0f,
		0.0f, cosTheta, sinTheta, 0.0f,
		0.0f, -sinTheta, cosTheta, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f };

	return pitchMatrix;
}

/// <summary>
/// 4x4行列のY軸回転行列
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 MakeYawMatrix(float radian) {

	float cosTheta = std::cos(radian);
	float sinTheta = std::sin(radian);

	Matrix4x4 yawMatrix = {
		cosTheta, 0.0f, -sinTheta, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		sinTheta, 0.0f, cosTheta, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	return yawMatrix;
}

/// <summary>
/// 4x4行列のZ軸回転行列
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 MakeRollMatrix(float radian) {

	float cosTheta = std::cos(radian);
	float sinTheta = std::sin(radian);

	Matrix4x4 rollMatrix = {
		cosTheta, sinTheta, 0.0f, 0.0f,
		-sinTheta, cosTheta, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f,0.0f,0.0f, 1.0f
	};

	return rollMatrix;
}

/// <summary>
/// 4x4行列の回転行列
/// </summary>
/// <param name="rotate"></param>
/// <returns></returns>
Matrix4x4 MakeRotateMatrix(const Vec3f& rotate) {

	Matrix4x4 pitchMatrix = MakePitchMatrix(rotate.x);	// X軸回転行列
	Matrix4x4 yawMatrix = MakeYawMatrix(rotate.y);		// Y軸回転行列
	Matrix4x4 rollMatrix = MakeRollMatrix(rotate.z);	// Z軸回転行列

	Matrix4x4 rotateMatrix = Multiply(pitchMatrix, Multiply(yawMatrix, rollMatrix));

	return rotateMatrix;
}

/// <summary>
/// 4x4行列の平行移動行列
/// </summary>
/// <param name="translate"></param>
/// <returns></returns>
Matrix4x4 MakeTranslateMatrix(const Vec3f& translate) {

	Matrix4x4 translateMatrix = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		translate.x, translate.y, translate.z, 1.0f
	};

	return translateMatrix;
}

/// <summary>
/// 4x4行列のアフィン変換
/// </summary>
/// <param name="scale"></param>
/// <param name="rotate"></param>
/// <param name="translate"></param>
/// <returns></returns>
Matrix4x4 MakeAffineMatrix(const Vec3f& scale, const Vec3f& rotate, const Vec3f& translate) {

	Matrix4x4 matrix = {};

	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
	Matrix4x4 rotateMatrix = MakeRotateMatrix(rotate);
	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);

	matrix = Multiply(scaleMatrix, rotateMatrix);
	matrix = Multiply(matrix, translateMatrix);

	return matrix;
}

/// <summary>
/// 4x4行列の座標変換
/// </summary>
/// <param name="vector"></param>
/// <param name="matrix"></param>
/// <returns></returns>
Vec3f Transform(const Vec3f& vector, const Matrix4x4& matrix) {

	Vec3f result;

	// ベクトルと行列の乗算
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] +
		matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] +
		matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] +
		matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] +
		matrix.m[3][3];

	// ベクトルの正規化
	if (w != 0.0f) {
		result.x /= w;
		result.y /= w;
		result.z /= w;
	}

	return result;
}

/// <summary>
/// 正射影ベクトル
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vec3f Project(const Vec3f& v1, const Vec3f& v2) {

	Vec3f diff = Normalize(v2);

	float t = Dot(v1, diff);

	Vec3f projectionA = diff * t;

	return projectionA;
}

/// <summary>
/// 最近接点
/// </summary>
/// <param name="point"></param>
/// <param name="segment"></param>
/// <returns></returns>
Vec3f ClosestPoint(const Vec3f& point, const Segement& segment) {

	Vec3f projection = segment.origin + Project(point - segment.origin, segment.diff);

	// clamp
	float t = std::clamp(Dot(projection - segment.origin, segment.diff) / Dot(segment.diff, segment.diff), 0.0f, 1.0f);

	return segment.origin + segment.diff * t;
}