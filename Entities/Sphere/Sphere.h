#pragma once
#include "MyMath.h"

/// <summary>
/// グリッド球クラス
/// </summary>
class Sphere {
private:
	/// <summary>
	/// メンバ変数
	/// </summary>

	// 半径
	float radius_{};

	/// <summary>
	/// 各点の構造体
	/// </summary>
	struct Point {

		Matrix4x4 worldMatrix_;
		Matrix4x4 worldViewProjectionMatrix_;

		Vec3f localPos_;
		Vec3f screenPos_;
	};

	Point a{}, b{}, c{}, center{};

	Vec3f ndcPosA_{};
	Vec3f ndcPosB_{};
	Vec3f ndcPosC_{};

public:
	/// <summary>
	/// メンバ関数
	/// </summary>

	// コンストラクタ
	Sphere() {

		// 球の半径
		radius_ = 0.01f;

		// 球の中心
		center.localPos_ = { 0.0f,0.0f,0.0f };
	}
	// デストラクタ
	~Sphere() {}

	// 球を描画する関数
	void DrawSphere(const Vec3f& point, uint32_t color, const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix, const Matrix4x4& viewportMatrix);
};