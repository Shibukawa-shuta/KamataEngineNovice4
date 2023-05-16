#include <Novice.h>

const char kWindowTitle[] = "LE2D_07_シブカワシュウタ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};


	typedef struct Player {
		//プレイヤー
		float posX;      //プレイヤー座標
		float posY;      //プレイヤー座標
		float playerLeftspeed;  //左移動
		float playerRightspeed; //右移動

		//半径
		float Radius;    //半径

		//速さ

		float speed;     //速さ

		//ジャンプ処理
		float jumpSpeed; //ジャンプ速さ
		float startSpeed;//始まりの速さ
		int jumpflag;    //ジャンプフラグ
		int glidingflag; //滑空フラグ
		int jumpcount;
		int Frame;       //フレーム
		int Frame1;      //フレーム

		//重力
		const float gravity;   //重力
	};

	Player player{
		500.0f, //プレイヤー座標
		500.0f, //プレイヤー座標
		0.0f,   //左移動
		0.0f,   //右移動
		32.0f,  //半径
		0.0f,   //速さ
	    0.0f,   //ジャンプ速さ
		30.0f,   //始まりの速さ
		0,   //ジャンプフラグ
		0,   // kakkuu 
		0,
		60,   //フレーム
		0,  //フレーム
		9.8f    //重力
	};



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
		
		//プレイヤー移動　左右
		if (keys[DIK_A] == 0)
		{
			player.playerLeftspeed = 5.0;
			player.posX += player.playerLeftspeed;
		}

		if (keys[DIK_D] == 0)
		{
			player.playerRightspeed = 5.0;
			player.posX -= player.playerRightspeed;

		}

		//スペースキー押したとき
		if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0 && player.jumpflag == 0 && player.posY == 500.0f)
		{
			player.jumpflag = 1;
		}

		//ジャンプフラグ　1の時
	    if (player.jumpflag == 1) 
		{

			player.jumpSpeed = player.startSpeed - player.gravity * (static_cast<float> (player.Frame) / 50.0f);
			player.posY -= player.jumpSpeed;

			player.jumpcount = 1;
			player.Frame++;
			
		
			//プレイヤーY座標 + フレーム
			player.posY += player.Frame;

			//ジャンプ　落ちる処理　0リセット
			if (player.Frame > 60)
			{
				player.Frame = 0;
			}

			////ジャンプフラグリセット
			//if (player.posY <= 150.0f) 
			//{
			//	player.jumpflag = 0;
			//}
			 
			
			////ジャンプフラグリセット
			if (player.Frame == 0)
			{
				player.jumpflag = 0;
			}

		}
		
		
		
		//滑空ジャンプ　処理
		if (player.posY <= 150.0f)
		{
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0 && player.jumpSpeed <= 0)
			{
				player.glidingflag = 1;
				player.jumpflag = 0;
			}
		}
		
		if (player.jumpflag == 0)
		{
			player.jumpSpeed = -0.9f;
			player.posY -= player.jumpSpeed;
		}
		


		//プレイヤー　移動制限↓

		//プレイヤー制限　右
		if (player.posX <= 20)
		{
			player.posX = 20;
		}

		//プレイヤー制限　左
		if (player.posX >= 1260)
		{
			player.posX = 1260;
		}
		//プレイヤー制限　下
		if (player.posY >= 500)
		{
			player.posY = 500;
		}
		//プレイヤー制限　ue
		if (player.posY <= 20)
		{
			player.posY = 20;
		}

		///
		/// ↑更新処理ここまで
		///



		///
		/// ↓描画処理ここから
		///
		



		//背景
		Novice::DrawBox(0,0,1280,720,0.0f,BLACK,kFillModeSolid);

		//線
		Novice::DrawLine(0,520,1280,520,WHITE);

		//プレイヤー(丸)
		Novice::DrawEllipse(player.posX,player.posY, 20, 20, 0, WHITE, kFillModeSolid);

		//文字
		Novice::ScreenPrintf(30, 30, "SPACE KEY : JUMP");
		Novice::ScreenPrintf(30, 50, "playerX :%0.0f", player.posX);
		Novice::ScreenPrintf(30, 70, "playerY :%0.0f",player.posY);
		Novice::ScreenPrintf(30, 90, "Frame :%d", player.Frame);
		Novice::ScreenPrintf(30, 110, "jumpspeed :%0.0f", player.jumpSpeed);
		Novice::ScreenPrintf(30, 130, "jumpflag :%d", player.jumpflag);
		Novice::ScreenPrintf(30, 150, "jumpflag :%d", player.glidingflag);



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
