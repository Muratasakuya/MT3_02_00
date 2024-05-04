﻿#pragma once
#include <algorithm>
#include <stdint.h>
#include <Novice.h>
#include <Matrix4x4.h>
#include <ImGui.h>
#include "Vector.h"

/// <summary>
/// 線分
/// </summary>
struct Segement {

	Vec3f origin; // 始点
	Vec3f diff;   // 終点への差分ベクトル
};

/// <summary>
/// πの値の取得
/// </summary>
/// <returns></returns>
float Pi();

/// <summary>
/// 内積
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
float Dot(const Vec3f& v1, const Vec3f& v2);

/// <summary>
/// 長さ、ノルム
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
float Length(const Vec3f& v);

/// <summary>
/// 正規化
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
Vec3f Normalize(const Vec3f& v);

/// <summary>
/// クロス積
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vec3f Cross(const Vec3f& v1, const Vec3f& v2);

/// <summary>
/// 4x4行列の加算
/// </summary>
/// <param name="m1"></param>
/// <param name="m2"></param>
/// <returns></returns>
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

/// <summary>
/// 4x4行列の減算
/// </summary>
/// <param name="m1"></param>
/// <param name="m2"></param>
/// <returns></returns>
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

/// <summary>
/// 4x4行列の積
/// </summary>
/// <param name="m1"></param>
/// <param name="m2"></param>
/// <returns></returns>
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

/// <summary>
/// 4x4行列の逆行列
/// </summary>
/// <param name="m"></param>
/// <returns></returns>
Matrix4x4 Inverse(const Matrix4x4& m);

/// <summary>
/// 4x4行列の転置行列
/// </summary>
/// <param name="m"></param>
/// <returns></returns>
Matrix4x4 Transpose(const Matrix4x4& m);

/// <summary>
/// 4x4行列の単位行列
/// </summary>
/// <returns></returns>
Matrix4x4 MakeIdentity4x4();

/// <summary>
/// 4x4行列の拡縮行列
/// </summary>
/// <param name="scale"></param>
/// <returns></returns>
Matrix4x4 MakeScaleMatrix(const Vec3f& scale);

/// <summary>
/// 4x4行列のX軸回転行列
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 MakePitchMatrix(float radian);

/// <summary>
/// 4x4行列のY軸回転行列
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 MakeYawMatrix(float radian);

/// <summary>
/// 4x4行列のZ軸回転行列
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 MakeRollMatrix(float radian);

/// <summary>
/// 4x4行列の回転行列
/// </summary>
/// <param name="rotate"></param>
/// <returns></returns>
Matrix4x4 MakeRotateMatrix(const Vec3f& rotate);

/// <summary>
/// 4x4行列の平行移動行列
/// </summary>
/// <param name="translate"></param>
/// <returns></returns>
Matrix4x4 MakeTranslateMatrix(const Vec3f& translate);

/// <summary>
/// 4x4行列のアフィン変換
/// </summary>
/// <param name="scale"></param>
/// <param name="rotate"></param>
/// <param name="translate"></param>
/// <returns></returns>
Matrix4x4 MakeAffineMatrix(const Vec3f& scale, const Vec3f& rotate, const Vec3f& translate);

/// <summary>
/// 4x4行列の座標変換
/// </summary>
/// <param name="vector"></param>
/// <param name="matrix"></param>
/// <returns></returns>
Vec3f Transform(const Vec3f& vector, const Matrix4x4& matrix);

/// <summary>
/// 正射影ベクトル
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vec3f Project(const Vec3f& v1, const Vec3f& v2);

/// <summary>
/// 最近接点
/// </summary>
/// <param name="point"></param>
/// <param name="segment"></param>
/// <returns></returns>
Vec3f ClosestPoint(const Vec3f& point, const Segement& segment);