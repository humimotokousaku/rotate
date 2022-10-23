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
typedef struct Matrix2x2 {
	float m[2][2];
};

//回転の関数
Vector2 Multiply(Vector2 vector, Matrix2x2 matrix, Vector2 pos) {
	Vector2 Multiply;
	Multiply.x = ((vector.x * matrix.m[0][0]) + (vector.y * matrix.m[1][0])) + pos.x;
	Multiply.y = ((vector.x * matrix.m[0][1]) + (vector.y * matrix.m[1][1])) + pos.y;
	return Multiply;
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// 画像
	int direction = Novice::LoadTexture("./TD1_direction.png");

	// 宣言
	// player
	Player player = {
		{kWindowWidth / 2,kWindowHeight / 2},
		{4.0f,4.0f},
		16.0f,
		true,
		BLUE
	};

	// 回転
	float theta0 = 0.0f;

	int width = 128;
	int height = 128;

	//回転前
	Vector2 leftTop = { -width / 2,height / 2 };
	Vector2 rightTop = { width / 2, height / 2 };
	Vector2 leftBottom = { -width / 2, -height / 2 };
	Vector2 rightBottom = { width / 2,-height / 2 };

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

		theta0 += 1.0 / 32.0f * M_PI;

		///変数の初期化
		Matrix2x2 theta;
		theta.m[0][0] = cosf(theta0);
		theta.m[0][1] = sinf(theta0);
		theta.m[1][0] = -sinf(theta0);
		theta.m[1][1] = cosf(theta0);
		//回転後
		Vector2 rotatedLeftTop = Multiply(leftTop, theta, player.pos);
		Vector2 rotatedRightTop = Multiply(rightTop, theta, player.pos);
		Vector2 rotatedLeftBottom = Multiply(leftBottom, theta, player.pos);
		Vector2 rotatedRightBottom = Multiply(rightBottom, theta, player.pos);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		// 回転してる円
		Novice::DrawQuad(
			rotatedLeftTop.x, rotatedLeftTop.y,
			rotatedRightTop.x,rotatedRightTop.y,
			rotatedLeftBottom.x, rotatedLeftBottom.y,
			rotatedRightBottom.x, rotatedRightBottom.y,
			0, 0,
			128, 128,
			direction,
			WHITE
		);
		// player
		Novice::DrawEllipse(
			player.pos.x, player.pos.y, player.size, player.size, 0.0f, BLUE,
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
