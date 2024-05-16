#include <Novice.h>
#include <imgui.h>
#include "MakeMatrix.h"
#include "MatrixMath.h"
#include "Vector3Math.h"
#include "Draw.h"

const char kWindowTitle[] = "LE2B_17_ナガイ_コハク_3次元の当たり判定(球)";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//ウィンドウサイズ
	float kWindowWidth = 1280.0f;
	float kWindowHeight = 720.0f;

	Sphere ASphere{ Vector3(0.0f,0.0f,0.0f),0.5f };
	Sphere BSphere{ Vector3(1.0f,0.0f,-1.0f),0.1f };

	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };

	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };

	Draw draw;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		float distance = Vector3Math::Length(Vector3Math::Subtract(ASphere.center,BSphere.center));

		draw.Pipeline(cameraTranslate, cameraRotate, kWindowWidth, kWindowHeight);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		ImGui::Begin("Debug");
		ImGui::DragFloat3("ASphere.Center", &ASphere.center.x, 0.01f);
		ImGui::DragFloat("ASphere.Radius", &ASphere.radius, 0.01f);
		ImGui::DragFloat3("BSphere.Center", &BSphere.center.x, 0.01f);
		ImGui::DragFloat("BSphere.Radius", &BSphere.radius, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::End();

		draw.DrawGrid();

		draw.DrawSphere(BSphere, WHITE);

		if (distance <= ASphere.radius + BSphere.radius) {

			draw.DrawSphere(ASphere, RED);

		} else {

			draw.DrawSphere(ASphere, WHITE);

		}

		///
		/// ↑描画処理ここまで
		///

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
