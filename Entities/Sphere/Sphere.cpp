#include "Sphere.h"

/// <summary>
/// 球を描画する関数
/// </summary>
void Sphere::DrawSphere(
	const Vec3f& point, uint32_t color, const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix, const Matrix4x4& viewportMatrix) {

	ImGui::Begin("Sphere");

	ImGui::SliderFloat3("translate", &center.localPos_.x, -10.0f, 10.0f);
	ImGui::SliderFloat("radius", &radius_, 0.0f, 10.0f);

	ImGui::End();

	center.localPos_ = point;

	// 分割数
	const uint32_t kSubdivision = 12;
	// 緯度分割1つ文の角度
	const float kLatEvery = Pi() / kSubdivision;
	// 経度分割1つ分の角度
	const float kLonEvery = 2.0f * Pi() / kSubdivision;

	// 緯度方向に分割 -π/2 ~ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {

		// 現在の緯度
		float lat = -Pi() / 2.0f + kLatEvery * latIndex;

		// 経度の方向に分割 0 ~ 2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {

			// 現在の経度
			float lon = lonIndex * kLonEvery;

			// world座標系でのa、b、cを求める
			a.localPos_ =
			{ radius_ * std::cos(lat) * std::cos(lon),radius_ * std::sin(lat),radius_ * std::cos(lat) * std::sin(lon) };

			a.localPos_ += center.localPos_;

			b.localPos_ =
			{ radius_ * std::cos(lat + kLatEvery) * std::cos(lon),radius_ * std::sin(lat + kLatEvery),radius_ * std::cos(lat + kLatEvery) * std::sin(lon) };

			b.localPos_ += center.localPos_;

			c.localPos_ =
			{ radius_ * std::cos(lat) * std::cos(lon + kLonEvery),radius_ * std::sin(lat),radius_ * std::cos(lat) * std::sin(lon + kLonEvery) };

			c.localPos_ += center.localPos_;

			/****************************************************************************************************************************/
			// a地点の変換
			a.worldMatrix_ =
				MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, a.localPos_);
			ndcPosA_ =
				Transform(a.localPos_, Multiply(viewMatrix, projectionMatrix));
			a.screenPos_ =
				Transform(ndcPosA_, viewportMatrix);

			/****************************************************************************************************************************/
			// b地点の変換
			b.worldMatrix_ =
				MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, b.localPos_);
			ndcPosB_ =
				Transform(b.localPos_, Multiply(viewMatrix, projectionMatrix));
			b.screenPos_ =
				Transform(ndcPosB_, viewportMatrix);

			/****************************************************************************************************************************/
			// c地点の変換
			c.worldMatrix_ =
				MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, c.localPos_);
			ndcPosC_ =
				Transform(c.localPos_, Multiply(viewMatrix, projectionMatrix));
			c.screenPos_ =
				Transform(ndcPosC_, viewportMatrix);

			/****************************************************************************************************************************/
			// ab、bcで描画
			// ab
			Novice::DrawLine(
				static_cast<int>(a.screenPos_.x), static_cast<int>(a.screenPos_.y),
				static_cast<int>(b.screenPos_.x), static_cast<int>(b.screenPos_.y),
				color
			);

			// bc
			Novice::DrawLine(
				static_cast<int>(a.screenPos_.x), static_cast<int>(a.screenPos_.y),
				static_cast<int>(c.screenPos_.x), static_cast<int>(c.screenPos_.y),
				color
			);
		}
	}
}