#include "MyMath.h"
#include "Camera.h"
#include "Grid.h"
#include "Sphere.h"

#include <memory>

const char kWindowTitle[] = "LC1B_28_ムラタ_サクヤ_MT3_02_00";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Segement segment = {
		{-2.0f,-1.0f,0.0f},
		{3.0f,2.0f,2.0f},
	};

	Vec3f point = { -1.5f,0.6f,0.6f };
	Vec3f project = Project(point - segment.origin, segment.diff);
	Vec3f closestPoint = ClosestPoint(point, segment);

	Camera camera;
	camera.Init();

	Grid grid;

	Sphere pointSphere;
	Sphere closestPointSphere;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		// 計算結果をImGuiで描画
		ImGui::Begin("Result");

		ImGui::SliderFloat3("point", &point.x, -10.0f, 10.0f);
		ImGui::SliderFloat3("project", &project.x, -10.0f, 10.0f);
		ImGui::SliderFloat3("closestPoint", &closestPoint.x, -10.0f, 10.0f);

		ImGui::End();

		// 値の更新
		project = Project(point - segment.origin, segment.diff);
		closestPoint = ClosestPoint(point, segment);

		// カメラの更新処理
		camera.Update();

		// グリッド線の描画
		grid.DrawGrid(camera.GetViewMatrix(), camera.GetProjectionMatrix(), camera.GetViewportMatrix());

		// 点の描画 1
		pointSphere.DrawSphere(point, 0xff0000ff, camera.GetViewMatrix(), camera.GetProjectionMatrix(), camera.GetViewportMatrix());

		// 点の描画 2
		pointSphere.DrawSphere(closestPoint, 0x000000ff, camera.GetViewMatrix(), camera.GetProjectionMatrix(), camera.GetViewportMatrix());

		// 線分の描画
		Vec3f start = Transform(Transform(segment.origin, Multiply(camera.GetViewMatrix(), camera.GetProjectionMatrix())), camera.GetViewportMatrix());
		Vec3f end = Transform(Transform(segment.origin + segment.diff, Multiply(camera.GetViewMatrix(), camera.GetProjectionMatrix())), camera.GetViewportMatrix());

		Novice::DrawLine(
			static_cast<int>(start.x), static_cast<int>(start.y),
			static_cast<int>(end.x), static_cast<int>(end.y),
			0xffffffff
		);

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();

	return 0;
}
