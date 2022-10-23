#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

const char kWindowTitle[] = "LC1B_26_フミモトコウサク";

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

// 構造体
typedef struct Vector2 {
	float x;
	float y;
};
typedef struct Player {
	Vector2 pos;
	Vector2 speed;
	float size;
	int isAlive;
	unsigned int color;
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// 画像
///	int direction = Novice::LoadTexture("./TD1_direction.png");

	// 宣言
	// player
	Player player = {
		{kWindowWidth / 2,kWindowHeight / 2},
		{4.0f,4.0f},
		16.0f,
		true,
		BLUE
	};

	// 回転する円
	int kCircleCenterX = 400;
	int kCircleCenterY = 400;
	int kCircleRadius = 20;
	int kRedCircleRadius = 10;

	// 回転の中心点
	int circleCenterOffsetX;
	int circleCenterOffsetY;
	// 円の中心
	int circleCenterX;
	int circleCenterY;
	// 回転
	const float kRotateAngle = 1.0f / 64.0f * M_PI;
	float theta = 0.0f;


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
		// 移動処理
		if (keys[DIK_W]) {
			player.pos.y -= player.speed.y;
		}
		if (keys[DIK_A]) {
			player.pos.x -= player.speed.x;
		}
		if (keys[DIK_S]) {
			player.pos.y += player.speed.y;
		}
		if (keys[DIK_D]) {
			player.pos.x += player.speed.x;
		}
		// 回転するためにthetaを足す
		theta += kRotateAngle;

		// まずクリックした位置が原点になるように円の中心点を移動
		circleCenterOffsetX = kCircleCenterX - (kCircleCenterX - player.size);
		circleCenterOffsetY = kCircleCenterY - (kCircleCenterY - player.size);

		// 回転させる
		circleCenterX =
			(circleCenterOffsetX * cosf(theta) - circleCenterOffsetY * sinf(theta));
		circleCenterY =
			(circleCenterOffsetY * cosf(theta) + circleCenterOffsetX * sinf(theta));

		// 移動した分を戻す
		circleCenterX += player.pos.x;
		circleCenterY += player.pos.y;

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		// 回転してる円
		Novice::DrawEllipse(circleCenterX, circleCenterY, kCircleRadius, kCircleRadius, 0.0f, RED, kFillModeSolid);

		// player
		Novice::DrawEllipse(
			player.pos.x, player.pos.y, kRedCircleRadius, kRedCircleRadius, 0.0f, BLUE,
			kFillModeSolid);
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
