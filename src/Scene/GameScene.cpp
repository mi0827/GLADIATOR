#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/System/Vector2.h"
#include "src/Hit/Hit.h" // あたり判定
#include "src/Sound/BGM.h"
#include "src/Sound/SE.h"
#include "src/Hit/HitStop.h"
#include "src/Base.h"
// キャラクター.h
#include "src/Character/Base/Character_Base.h"
#include "src/Effect/Effect.h"
#include "src/Character/Player.h"
#include "src/Character/Ninja.h"
#include "src/Character/Fighter.h"
// オブジェクトクラス
#include "src/Object/Object.h"
// フィールド.h
#include "src/Field/Field.h"
// カメラ.h
#include "src/Camera.h"

#include "src/Scene/Base/Scene_Base.h"
#include "GameScene.h"
constexpr int PLAYER_MAX = 2;   // プレイヤーの数、カメラの数も一緒


// 各クラスのオブジェクト
BGM game_bgm;
SE se_game;
CharacterBase* players[2];      // キャラクターの二人呼ぶ用の配列 
Camera* camera[2];              // キャラクタと同じ数

Field field;
HitStop hit_stop;
constexpr int TIME_MAX = 60;    // 制限時間 (今だけ10秒)
constexpr int END_TIME_MAX = 5; // エンドの時間制限


//------------------------------------------
// ゲーム開始の最初の設定
//------------------------------------------
GameScene::GameScene()
{
}

//------------------------------------------------
// 初期処理(各クラスのコンストラクタできないもの)
//------------------------------------------------
void GameScene::Init()
{
	players[0] = new Fighter;
	players[1] = new Player;
	// プレイヤー０にカメラ０をつける
	// プレイヤー１にカメラ１をつける
	camera[0] = new Camera(0);
	camera[1] = new Camera(1);
	// 各クラスの初期設定
	field.Init();
	field.Field_Init();
	players[0]->Init(0);
	players[1]->Init(1);
	// ゲームパッドの設定
	players[0]->SetPadNo(PAD_NO::PAD_NO1, DX_INPUT_PAD1);//DX_INPUT_PAD1);

	players[1]->SetPadNo(PAD_NO::PAD_NO2, DX_INPUT_PAD2);//DX_INPUT_PAD2);

	for (int i = 0; i < PLAYER_MAX; i++) 
	{
		camera[i]->PlayField_Init();
	}
	// ゲームパッドの設定
	camera[0]->SetPadNo(DX_INPUT_PAD1);
	camera[1]->SetPadNo(DX_INPUT_PAD2);

	// 最初はマックス値から始める
	m_time_count = TIME_MAX;      // タイマーの設定
	m_flame_count = FLAME_MAX;    // フレームカウントの設定
	m_end_count = END_TIME_MAX;   // エンドに行くまでのカウントダウン
	m_scene_change_judge = false; // 最初はシーンの切り替えをしてはいけない
	m_status_flag = false;        // 最初はステータス更新をしてほしくない
	m_play_scene = Play_Tutorial; // 最初はチュートリアルシーン

	SE_Init(); // SEの初期化
	BGM_Init(); // BGMの初期化
	Light_Init(); // ライトの初期化
	//SetLightEnable(FALSE);

}

//----------------------------------------
// 更新処理
//----------------------------------------
void GameScene::Update(int bgm_volume, int se_volume)
{

	int light_num = 0;
	light_num = GetEnableLightHandleNum();

	game_bgm.BGM_ChangeVolume(bgm_volume, BGM_MAX); // BGMのボリューム変更処理
	se_game.SE_ChangeVolume(se_volume, SE_MAX);	 // SEのボリューム変更処理   
	if (!m_fight_start_flag) 
	{
		// ヒットストップしてほしいかしてほしくないか
		m_stop = hit_stop.Hit_Stop();
		if (!m_stop)
		{
			Character_Update(se_volume); // キャラクターたちの更新処理
		}
	}

	// 各クラスの更新処理
	field.Update();

	for (int i = 0; i < PLAYER_MAX; ++i)
	{
		camera[i]->Update(&players[i]->m_pos);
	}


	switch (m_play_scene)
	{
	case Play_Tutorial:
		m_status_flag = false;        // ステータス更新をしてほしくない
		Tutorial_Update();
		break;
	case Play_Main:
		m_status_flag = true;         // ステータス更新をしてほしくない
		PlayMain_Update();
		break;
	case Play_End:
		m_status_flag = false;        // 最初はステータス更新をしてほしくない
		PlayEnd_Update();
		break;
	};
	Light_Update();
	
}

//-------------------------------------
// 描画処理
//-------------------------------------
void GameScene::Draw()
{
	// オリジナルのライトの向きを取ってくる
	m_original_light_rot = GetLightDirection();

	// 各クラスの描画処理
	for (int i = 0; i < PLAYER_MAX; i++) 
	{
		camera[i]->Draw_Set();       // カメラの描画前設定（ ※ 描画処理の一番最初にすること）
		// DXライブラリのカメラとEffekseerのカメラを同期する。
		Effekseer_Sync3DSetting();

		field.Draw();

		// プレイヤ―を描画させるための配列
		for (int j = 0; j < PLAYER_MAX; j++) 
		{
			players[j]->Draw();
		}
		players[i]->Draw_Status(i);

		// Effekseer描画処理
		// DrawEffekseer3D();

	}



	for (int i = 0; i < PLAYER_MAX; i++)
	{

		camera[i]->Draw(i); // カメラの描画処理（ ※ 描画処理の一番最後にすること）
	}
	switch (m_play_scene)
	{
	case Play_Tutorial:

		Tutorial_Draw();
		break;
	case Play_Main:
		Time_Draw();               // タイマーを描画するのはプレイ中だけ
		break;
	case Play_End:
		End_Draw();
		break;
	};
}

//------------------------------------
// 終了処理
//------------------------------------
void GameScene::Exit()
{
	// 各クラスの終了処理
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		players[i]->Exit();
		camera[i]->Exit();
	}
	field.Exit();
	// newしていたクラスの解放
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		delete players[i];
		players[i] = nullptr;
		delete camera[i];
		camera[i] = nullptr;
	}

	// ライトの初期化
	for (int i = 0; i < light_MAX; i++) 
	{
		DeleteLightHandle(m_light_handle[i]);
	}
}

//------------------------------------
// SEの初期化
//------------------------------------
void GameScene::SE_Init()
{
	se_game.SE_ContainerNew(SE_MAX); // SEの配列作成
	// SEの読み込み
	se_game.Load_SE("Data/SE/Game/ready.mp3", READY);
}

//------------------------------------
// BGMの初期化
//------------------------------------
void GameScene::BGM_Init()
{
	// bgm用の配列の準備
	game_bgm.BGM_ContainerNew(BGM_MAX);
	game_bgm.Load_BGM("Data/BGM/Game/tutorial.mp3", TUTORIAL_BGM); // チュートリアルのBGM
	game_bgm.Load_BGM("Data/BGM/Game/battle1.mp3", BATTLE_1_BGM);  // プレイメインのBGM１
	game_bgm.Load_BGM("Data/BGM/Game/battle2.mp3", BATTLE_2_BGM);  // プレイメインのBGM２
	game_bgm.Load_BGM("Data/BGM/Game/battle3.mp3", BATTLE_2_BGM);  // プレイメインのBGM3
	// 最初はチュートリアルbgmを流す
	game_bgm.Play_BGM(DX_PLAYTYPE_LOOP, true, TUTORIAL_BGM);
}

//------------------------------------
// ライトの初期化
//------------------------------------
void GameScene::Light_Init()
{
	// もとからあるライトの値をもらってくる
	m_original_dif_color = GetLightDifColor();
	m_original_spc_color = GetLightSpcColor();
	m_original_amb_color = GetLightAmbColor();


	for (int i = 0; i < light_MAX; i++)
	{
		// ライトの作成
		m_light_handle[i] = CreateDirLightHandle(VGet(0.0f, 1.0f, 0.0f));

		//light_handle[i] = CreateDirLightHandle(VGet(1.0f, 0.0f, 0.0f));

		// ライトの座標設定
		m_light_pos.set(500, 200, 500);
		SetLightPositionHandle(m_light_handle[i], m_light_pos.VGet());
		//	スポットライトの向きの設定（とりあえず真下を向かせています）
		m_light_rot.set(-4.0f, -1.0f, -2.0f);
		SetLightDirectionHandle(m_light_handle[i], m_light_rot.VGet());
		// ライトの色の変更
		SetLightDifColorHandle(m_light_handle[i], GetColorF(1.0f, 1.0f, 1.0f, 0.0f));

	}
}

//------------------------------------
// ライトの更新処理
//------------------------------------
void GameScene::Light_Update()
{
	for (int i = 0; i < light_MAX; i++)
	{
		/*SetLightPositionHandle(light_handle[i], light_pos.VGet());*/

		// 新たに追加したスポットライトの向きを変更しましす
		SetLightDirectionHandle(m_light_handle[i], m_light_rot.VGet());
		// 色を変更する場合
		SetLightDifColorHandle(m_light_handle[i], GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
		//	スポットライトの色の設定
		SetLightDifColorHandle(m_light_handle[i], GetColorF(m_original_dif_color.r, m_original_dif_color.g, m_original_dif_color.b, 1.0f));
		// 十字キーでライトの向きを変更
		// 調整に使うもの
		/*if (CheckHitKey(KEY_INPUT_RIGHT)) {
			light_rot.x += 0.1f;
		}
		if (CheckHitKey(KEY_INPUT_LEFT)) {
			light_rot.x -= 0.1f;
		}
		if (CheckHitKey(KEY_INPUT_UP)) {
			light_rot.z += 0.1f;
		}
		if (CheckHitKey(KEY_INPUT_DOWN)) {
			light_rot.z -= 0.1f;
		}*/

	}
}

//------------------------------------
// チュートリアルの更新処理
//------------------------------------
void GameScene::Tutorial_Update()
{
	// プレイヤー１

	if (IsPadRepeat(PAD_ID::PAD_X, players[0]->m_pad_no)) 
	{
		if (!m_ready_flag1) 
		{
			m_button_count1++; // ボタンの長押しカウントを増やす
			if (m_button_count1 >= BUTTON_COUNT_MAX) 
			{
				// カウントが一定以上になると準備完了
				m_ready_flag1 = true;
				// 指定のSEが再生中じゃなかったら
				if (!se_game.Playing_SE(READY))
				{
					// SEの再生
					se_game.Play_SE(READY, DX_PLAYTYPE_BACK, true);
				}
				PadVidation(players[0]->m_pad_input, 1000, 300, -1);
			}
		}
	}
	else {
		// 押されていない時はカウントを減らす
		m_button_count1--;
		if (m_button_count1 < 0) 
		{
			// ボタンカウントがマイナスにならないようにする
			m_button_count1 = 0;
		}
	}
	// プレイヤー２
	if (IsPadRepeat(PAD_ID::PAD_X, players[1]->m_pad_no)) 
	{
		if (!m_ready_flag2) 
		{
			m_button_count2++; // ボタンの長押しカウントを増やす
			if (m_button_count2 >= BUTTON_COUNT_MAX)
			{
				// カウントが一定以上になると準備完了
				m_ready_flag2 = true;
				// 指定のSEが再生中じゃなかったら
				if (!se_game.Playing_SE(READY))
				{
					// SEの再生
					se_game.Play_SE(READY, DX_PLAYTYPE_BACK, true);
				}
				PadVidation(players[1]->m_pad_input, 1000, 300, -1);
			}
		}
	}
	else {
		// 押されていない時はカウントを減らす
		m_button_count2--;
		if (m_button_count2 < 0)
		{
			// ボタンカウントがマイナスにならないようにする
			m_button_count2 = 0;
		}
	}

	// 両プレイヤーが準備完了なら(今だけ一人で実行できるようにする)
	if (m_ready_flag1 /*&& ready_flag2*/)
	{
		for (int i = 0; i < PLAYER_MAX; i++)
		{
			players[i]->Reset_Status(); // ステータスをリセットしておく
		}
		// 座標と向きを最初の設定に戻す
		players[0]->m_pos.set(350.0f, 0.0f, 150.0f);           // 初期座標の設定
		players[0]->m_rot.set(0.0f, 0.0f, 0.0f);               // 向きの設定
		players[1]->m_pos.set(350.0f, 0.0f, 450.0f);           // 初期座標の設定
		players[1]->m_rot.set(0.0f, 180.0f, 0.0f);             // 向きの設定

		
		// 試合開始までのフラグを立てる
		m_fight_start_flag = true;

	}
	// ファイトフラグが立ったら
	if (m_fight_start_flag)
	{
		m_fight_start_count++; // ファイトカウントを増やす
		if (m_fight_start_count >= FIGHT_START_COUNT_MAX)
		{
			// 一定時間たったら
			m_play_scene = Play_Main; // プレイメインに移動
			m_fight_start_flag = false;
			game_bgm.Stop_BGM(TUTORIAL_BGM); // チュートリアルBGMを止める
			game_bgm.Play_BGM(DX_PLAYTYPE_BACK, true, BATTLE_2_BGM); // バトル用のBGMに変える
		}


	}
}

//------------------------------------
// メインプレイシーンの更新処理
//------------------------------------
void GameScene::PlayMain_Update()
{
	int player1 = 0;
	int player2 = 1;
	bool is_both_no_guard =	// 両方とも攻撃中
		(
			players[player1]->m_block_flag == false &&
			players[player2]->m_block_flag == false
			);
	bool is_player1_guard =	// プレイヤー1がガード中
		(
			players[player1]->m_block_flag == true &&
			players[player2]->m_attack_flag == true
			);
	bool is_player2_guard =	// プレイヤー2がガード中
		(
			players[player1]->m_attack_flag == true &&
			players[player2]->m_block_flag == true
			);

	// プレイヤー1の攻撃とプレイヤー2の攻撃
	if (is_both_no_guard == true)
	{
		// 通常の当たり判定を行う
		Attack_Hit(player1, player2);
		Attack_Hit(player2, player1);
	}
	// プレイヤー1のガードとプレイヤー2の攻撃
	else if (is_player1_guard == true)
	{
		Block_Hit(player1, player2);
	}
	// プレイヤー1の攻撃とプレイヤー2のガード
	else if (is_player2_guard)
	{
		Block_Hit(player2, player1);
	}

	Time_Update(m_time_count); // タイマーの更新
	// タイマーが０になったら
	if (m_time_count == 0) 
	{
		m_play_scene = Play_End; // プレイエンドに進む
	}

	// どちらかのキャラの体力がゼロになったらエンドに移動
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (players[i]->m_now_hp == 0)
		{
			m_play_scene = Play_End; // プレイエンドに進む
		}
	}
}

//------------------------------------
// プレイエンドの更新処理
//------------------------------------
void GameScene::PlayEnd_Update()
{
	Time_Update(m_end_count);

	Play_Victory_Draw(players[0], players[1]);

	if (m_end_count <= 0)
	{
		m_end_count = 0;
		// タイマーが終わったら
		m_scene_change_judge = true; // シーンの切り替えを許可する
		game_bgm.Stop_BGM(BATTLE_2_BGM); // BGMを止める
	}
}

//---------------------------------------------------------------------------
// キャラクターの更新処理（移動時のお互いのあたり判定）
//---------------------------------------------------------------------------
void GameScene::Character_Update(int se_volume)
{
	// キャラクターの移動（壁擦り）処理
	for (int player = 0; player < PLAYER_MAX; player++)
	{
		players[player]->Update(&camera[player]->m_rot, se_volume/*, status_flag*/);
		// 立方体とプレイヤーのあたり判定
		for (int i = 0; i < field.m_obj_max; i++) 
		{
			if (CheckBoxHit3D(players[player]->m_pos, players[player]->m_move_hit_box_size, field.objects[i]->m_cube_hit_pos, field.objects[i]->m_cube_size_half))
			{
				players[player]->m_move_judge = true; // 移動に支障があるのTureを返す
				players[player]->Get_other(&field.objects[i]->m_cube_hit_pos, &field.objects[i]->m_cube_size_half); // Playerに当たった相手の情報を渡する
				players[player]->Move_Hit_Update();   // 壁擦り用の関数
			}
			else 
			{
				players[player]->m_move_judge = false;
			}
		}
	}

	// プレイヤーとプレイヤーの移動あたり判定
	if (CheckBoxHit3D(players[0]->m_pos, players[0]->m_move_hit_box_size, players[1]->m_pos, players[1]->m_move_hit_box_size))
	{
		players[0]->m_move_judge = true; // 移動に支障があるのTureを返す
		players[0]->Get_other(&players[1]->m_pos, &players[1]->m_move_hit_box_size); // Playerに当たった相手の情報を渡する
		players[0]->Move_Hit_Update();   // 壁擦り用の関数
	}
	else 
	{
		players[0]->m_move_judge = false;
	}
	// プレイヤーとプレイヤーの移動あたり判定
	if (CheckBoxHit3D(players[1]->m_pos, players[1]->m_move_hit_box_size, players[0]->m_pos, players[0]->m_move_hit_box_size))
	{
		players[1]->m_move_judge = true; // 移動に支障があるのTureを返す
		players[1]->Get_other(&players[0]->m_pos, &players[0]->m_move_hit_box_size); // Playerに当たった相手の情報を渡する
		players[1]->Move_Hit_Update(); // 壁擦り用の関数
	}
	else 
	{
		players[1]->m_move_judge = false;
	}
}

//---------------------------------------------------------------------------
// タイマーの更新処理
//---------------------------------------------------------------------------
void GameScene::Time_Update(int& time_count)
{
	m_flame_count--;               // フレームカウントを減らす
	if (m_flame_count < 0) 
	{       // フレームカウントが０になったら
		time_count--;            // タイマーを減らす
		m_flame_count = FLAME_MAX; // フレームカウントを設定しなおす
	}

	// タイマーがゼロになったら
	if (time_count <= 0)
	{
		time_count = 0; // ゼロで止める
	}
}

//---------------------------------------------------------------------------
// タイマーの描画処理
//---------------------------------------------------------------------------
void GameScene::Time_Draw()
{
	SetFontSize(100); // フォントサイズの変更
	// 文字列の設定
	const char* name = "[%02d]";
	// 描画座標の定義
	float w, h;
	Draw_String_Size(&w, &h, name);

	// 描画
	DrawFormatStringF(SCREEN_W / 2 - w / 2 + 50, h / 2, GetColor(255, 255, 0), name, m_time_count);
	SetFontSize(18); // フォントサイズを戻す
}

//---------------------------------------------------------------------------
// チュートリアルでの描画処理
//---------------------------------------------------------------------------
void GameScene::Tutorial_Draw()
{
	if (!m_fight_start_flag) 
	{
		int original_font_size = GetFontSize();
		SetFontSize(55); // フォントサイズの変更
		// 文字列の設定
		const char* name = "チュートリアル";
		// 描画座標の定義
		float w, h;
		Draw_String_Size(&w, &h, name);
		// 描画
		DrawFormatStringF(SCREEN_W / 2 - w / 2, h - 25, GetColor(255, 255, 0), name, m_time_count);
		SetFontSize(original_font_size); // フォントサイズを戻す

		Ready_Draw();
	}
	else 
	{
		int original_font_size = GetFontSize();
		SetFontSize(200); // フォントサイズの変更
		// 文字列の設定
		const char* name;
		if (m_fight_start_count <= FIGHT_START_COUNT_MAX / 2) 
		{
			name = "READY";
		}
		else 
		{
			name = "FIGHT";
		}
		// 描画座標の定義
		float w, h;
		Draw_String_Size(&w, &h, name);
		if (m_fight_start_count <= FIGHT_START_COUNT_MAX / 2) 
		{
			m_draw_fight_pos_x += 15; // 文字の移動をする
		}
		else
		{
			m_draw_fight_pos_x += 18; // 文字の移動をする
		}
		// 画面右端までいったら
		if (m_draw_fight_pos_x - (int)w >= SCREEN_W)
		{
			m_draw_fight_pos_x = 0 - (int)w; // 画面左端に移動
		}
		// 描画
		DrawFormatStringF((float)(m_draw_fight_pos_x -(w / 2)), (float)(SCREEN_H / 2 - h / 2), GetColor(255, 255, 0), name, m_time_count);
		SetFontSize(original_font_size); // フォントサイズを戻す
	}


}

//---------------------------------------------------------------------------
// 準備完了を描画させるだけの関数
//---------------------------------------------------------------------------
void GameScene::Ready_Draw()
{
	//=====================
	// 一つ目の円
	//=====================
	{
		//	準備オッケー用円の定数
		const int CENTER_X = SCREEN_W / 2 - 150;		//	円の中心Ｘ座標
		const int CENTER_Y = SCREEN_H - 150;		//	Ｙ座標
		const int RADIUS = 100;			//	半径
		//	線を上向きから開始したいので開始角度
		const float OFFSET = -90.0f;
		//	今のスピードが PLAYER_MOV_SPEED を最大としたときにどのくらいの割合か（ 0.0f ～ 1.0f ）
		float rate = m_button_count1 / BUTTON_COUNT_MAX;
		// 三角形のをいくつかくか
		int count = 360 * (int)rate;
		if (m_ready_flag1)
		{
			// 準備が完了したら常に円を描画する
			count = 360 * 1;
		}
		// この数分だけ三角形描画を繰り返す
		for (int i = 0; i < count; i++)
		{
			// 一つ目のの点の角度
			float r1 = i + OFFSET;
			// この方向にRADIS 分先に進めら座標
			float x1 = CENTER_X + RADIUS * cosf(TO_RADIAN(r1));
			float y1 = CENTER_Y + RADIUS * sinf(TO_RADIAN(r1));

			// 二つ目の
			float r2 = r1 + 1;
			// この方向にRADIS 分先に進めら座標
			float x2 = CENTER_X + RADIUS * cosf(TO_RADIAN(r2));
			float y2 = CENTER_Y + RADIUS * sinf(TO_RADIAN(r2));

			DrawTriangleAA(CENTER_X, CENTER_Y, x1, y1, x2, y2, GetColor(0, 255, 255), TRUE);
		}
		//	この割合的に角度はどのくらい進んでいるのか（ -90.0f から始めた時に何度か）
		float rot = 360.0f * rate + OFFSET;
		float rot_triangle = 360.0f * rate;
		//	線を引くための１点目は CENTER_X CENTER_Y
		//	２点目は CENTER_X CENTER_Y から rot の方向に RADIUS 分進んだところ
		float x = CENTER_X + RADIUS * cosf(TO_RADIAN(rot));
		float y = CENTER_Y + RADIUS * sinf(TO_RADIAN(rot));

		//	この２点を結んで線の描画
		if (!m_ready_flag1)
		{
			// 準備が完了していない時だけ描画する
			DrawLineAA(CENTER_X, CENTER_Y, x, y, GetColor(255, 255, 0), 5.0f);
		}
		//	メーター枠の円の描画
		DrawCircleAA(CENTER_X, CENTER_Y, RADIUS, 100, GetColor(255, 255, 255), FALSE, 3.0f);
		// ここでとってきた文字をセットしておく
		// 文字列の描画と描画幅の取得で2回使うのでここで定義しときます
		int original_font_size = GetFontSize();

		SetFontSize(50); // フォントサイズの変更
		if (m_ready_flag1)
		{
			const char* name = "ready";
			// 描画幅の取得
			int w = GetDrawStringWidth(name, -1);
			// 文字列の高さ取得
			int h = GetFontSize();
			// 描画文字の
			DrawString(CENTER_X - w / 2, CENTER_Y - h / 2, name, GetColor(128, 0, 0)); // 下
		}
		else 
		{
			const char* name = "OK:X";
			int w = GetDrawStringWidth(name, -1);
			// 文字列の高さ取得
			int h = GetFontSize();
			// 描画文字の
			DrawString(CENTER_X - w / 2, CENTER_Y - h / 2, name, GetColor(128, 0, 0)); // 下
		}

		SetFontSize(original_font_size); // フォントサイズを戻す
	}

	//=====================
	// 二つ目の円
	//=====================
	{
		//	準備オッケー用円の定数
		const int CENTER_X = SCREEN_W / 2 + 150; // 中心Ｘ座標
		const int CENTER_Y = SCREEN_H - 150;	 // Ｙ座標
		const int RADIUS = 100;			         // 半径
		//	線を上向きから開始したいので開始角度
		const float OFFSET = -90.0f;
		//	今のスピードが PLAYER_MOV_SPEED を最大としたときにどのくらいの割合か（ 0.0f ～ 1.0f ）
		int rate = m_button_count2 / BUTTON_COUNT_MAX;
		// 三角形のをいくつかくか
		int count = 360 * rate;
		if (m_ready_flag2) 
		{
			// 準備が完了したら常に円を描画する
			count = 360 * 1;
		}
		// この数分だけ三角形描画を繰り返す
		for (int i = 0; i < count; i++) 
		{
			// 一つ目のの点の角度
			float r1 = i + OFFSET;
			// この方向にRADIS 分先に進めら座標
			float x1 = CENTER_X + RADIUS * cosf(TO_RADIAN(r1));
			float y1 = CENTER_Y + RADIUS * sinf(TO_RADIAN(r1));

			// 二つ目の
			float r2 = r1 + 1;
			// この方向にRADIS 分先に進めら座標
			float x2 = CENTER_X + RADIUS * cosf(TO_RADIAN(r2));
			float y2 = CENTER_Y + RADIUS * sinf(TO_RADIAN(r2));

			DrawTriangleAA(CENTER_X, CENTER_Y, x1, y1, x2, y2, GetColor(0, 255, 255), TRUE);
		}
		//	この割合的に角度はどのくらい進んでいるのか（ -90.0f から始めた時に何度か）
		float rot = 360.0f * rate + OFFSET;
		float rot_triangle = 360.0f * rate;
		//	線を引くための１点目は CENTER_X CENTER_Y
		//	２点目は CENTER_X CENTER_Y から rot の方向に RADIUS 分進んだところ
		float x = CENTER_X + RADIUS * cosf(TO_RADIAN(rot));
		float y = CENTER_Y + RADIUS * sinf(TO_RADIAN(rot));

		//	この２点を結んで線の描画
		if (!m_ready_flag2) 
		{
			// 準備が完了していない時だけ描画する
			DrawLineAA(CENTER_X, CENTER_Y, x, y, GetColor(255, 255, 0), 5.0f);
		}

		//	メーター枠の円の描画
		DrawCircleAA(CENTER_X, CENTER_Y, RADIUS, 100, GetColor(255, 255, 255), FALSE, 5.0f);
		// ここでとってきた文字をセットしておく
		// 文字列の描画と描画幅の取得で2回使うのでここで定義しときます
		int original_font_size = GetFontSize();

		SetFontSize(50); // フォントサイズの変更
		if (m_ready_flag2)
		{
			{
				const char* name = "ready";
				// 描画幅の取得
				int w = GetDrawStringWidth(name, -1);
				// 文字列の高さ取得
				int h = GetFontSize();
				// 描画文字の
				DrawString(CENTER_X - w / 2, CENTER_Y - h / 2, name, GetColor(128, 0, 0)); // 下

			}
		}
		else {
			{
				const char* name = "OK:X";
				int w = GetDrawStringWidth(name, -1);
				// 文字列の高さ取得
				int h = GetFontSize();
				// 描画文字の
				DrawString(CENTER_X - w / 2, CENTER_Y - h / 2, name, GetColor(128, 0, 0)); // 下
			}
		}
		SetFontSize(original_font_size); // フォントサイズを戻す
	}
}

//---------------------------------------------------------------------------
// エンドでの描画処理
//---------------------------------------------------------------------------
void GameScene::End_Draw()
{
	int original_font_size = GetFontSize();
	SetFontSize(60); // フォントサイズの変更
	// 文字列の設定
	const char* name = "END";
	// 描画座標の定義
	float w, h;
	Draw_String_Size(&w, &h, name);

	// 描画(今がなんのシーンなのかがわかるように)
	DrawFormatStringF((float)(SCREEN_W / 2 - (int)w / 2), h, GetColor(255, 255, 0), name, m_time_count);
	SetFontSize(original_font_size); // フォントサイズを戻す

	// 勝敗の描画
	Play_Victory_Draw(players[0], players[1]);
}

//---------------------------------------------------------------------------
// 勝者を描画する用の変数
//---------------------------------------------------------------------------
void GameScene::Play_Victory_Draw(CharacterBase* character1, CharacterBase* character2)
{
	// 元のフォントサイズ
	int original_font_size = GetFontSize();
	// hpをわかりやすいようにする
	float hp1 = character1->m_now_hp;
	float hp2 = character2->m_now_hp;

	Vector2 draw_pos1; // プレイヤー１に対しての描画座標
	draw_pos1.set(SCREEN_W / 2 - ((SCREEN_W / 2) / 2), SCREEN_H / 2);
	Vector2 draw_pos2; // プレイヤー２に対しての描画座標
	draw_pos2.set(SCREEN_W / 2 + ((SCREEN_W / 2) / 2), SCREEN_H / 2);

	SetFontSize(100); // フォントサイズの変更
	// 文字列の設定
	const char* draw_string = "DRAW";
	const char* winner_string = "WINNER";
	const char* loser_string = "LOSER";
	// 描画座標の定義
	Vector2 draw;
	Vector2 winner;
	Vector2 loser;
	// 描画座標設定
	Draw_String_Size(& draw.x, & draw.y, draw_string);
	Draw_String_Size(&winner.x, &winner.y, winner_string);
	Draw_String_Size(&loser.x, &loser.y, loser_string);
	if (hp1 == hp2) 
	{
		// 残りhpが同じなら
		DrawStringF(draw_pos1.x - draw.x / 2, draw_pos1.y, draw_string, GetColor(255, 255, 0));
		DrawStringF(draw_pos2.x - draw.x / 2, draw_pos2.y, draw_string, GetColor(255, 255, 0));
	}
	if (hp1 > hp2)
	{
		// hp1のほうが残りhpが多いい場合
		DrawStringF(draw_pos1.x - winner.x / 2, draw_pos1.y, winner_string, GetColor(255, 0, 0));
		DrawStringF(draw_pos2.x - loser.x / 2, draw_pos2.y, loser_string, GetColor(0, 0, 255));
	}
	if (hp2 > hp1)
	{
		// hp2のほうが残りhpが多いい場合
		DrawStringF(draw_pos1.x - loser.x / 2, draw_pos1.y, loser_string, GetColor(0, 0, 255));
		DrawStringF(draw_pos2.x - winner.x / 2, draw_pos2.y, winner_string, GetColor(255, 0, 0));
	}
	SetFontSize(original_font_size); // フォントサイズを戻す
}

//---------------------------------------------------------------------------
// 文字列の幅、高さをとる関数
//---------------------------------------------------------------------------
void GameScene::Draw_String_Size(float* w, float* h, const char* sting)
{
	// 描画幅の取得,
	*w = (float)GetDrawStringWidth(sting, -1);
	// 文字列の高さ取得
	*h = (float)GetFontSize();
}

//---------------------------------------------------------------------------
// 攻撃のあたり判定をとる関数
// player1が：攻撃側
// player2が：受ける側
//---------------------------------------------------------------------------
void GameScene::Attack_Hit(int player1, int player2)
{
	// 当たり判定を取っていいときに当たっていたらダメージを入れる
	// (当たり判定と攻撃フラグがたっていたら)
	if (players[player1]->m_cd_hit_flag && players[player1]->m_attack_flag) 
	{
		if (HitCheck_Capsule_Capsule(players[player1]->m_hit_cd_pos_top.VGet(), players[player1]->m_hit_cd_pos_under.VGet(), players[player1]->m_hit_cd_r,
			players[player2]->m_hit_body_pos_top.VGet(), players[player2]->m_hit_body_pos_under.VGet(), players[player2]->m_hit_body_r))
		{
			// 当たり判定があったら
			// なおダメージフラグが降りてたら
			if (!players[player2]->m_damage_flag) 
			{
				players[player2]->m_hp_count.x -= players[player1]->m_attack_damage[players[player1]->m_attack_anim_pick]; // ダメージを入れる
				players[player2]->Damage_Update(&players[player1]->m_attack_damage[players[player1]->m_attack_anim_pick]);
				players[player2]->m_damage_flag = true; // ダメージを食らってるようにする
				hit_stop.Stop_Count_Reset(); // ヒットストップをさせる
				int  time = players[player1]->m_attack_damage[players[player1]->m_attack_anim_pick];
				PadVidation(players[player2]->m_pad_input, 1000, 10 * time, -1);
			}
		}
	}
}

// 当たり判定用の構造体（わかりやすいように）
struct Capsule
{
	VECTOR top_pos;
	VECTOR bottom_pos;
	float   r;
};

// カプセル同志のあたり判定を使いやすくしたもの
bool HitCheck_Capsule_Capsule(const Capsule& cp1, const Capsule& cp2)
{
	//float angle = atan2f(cp2.bottom_pos.y - cp1.bottom_pos.y, cp2.bottom_pos.x - cp1.bottom_pos.x);
	//float dgree = TO_DEGREE(angle);
	return HitCheck_Capsule_Capsule(cp1.top_pos,
		cp1.bottom_pos,
		cp1.r,
		cp2.top_pos,
		cp2.bottom_pos,
		cp2.r) == 1;
}

//---------------------------------------------------------------------------
// ガードのあたり判定をとる関数
// player1が：ガード側
// player2が：攻撃側
//---------------------------------------------------------------------------
void GameScene::Block_Hit(int player1, int player2)
{

	// 当たり判定を取っていいときに当たっていたらダメージを入れる
	// プレイヤー０の攻撃判定とプレイヤー1のガードの判定

	// 攻撃用カプセル
	Capsule player2_hit_cp =
	{
		players[player2]->m_hit_cd_pos_top.VGet(),
		players[player2]->m_hit_cd_pos_under.VGet(),
		players[player2]->m_hit_cd_r
	};
	// ガードしているとき
	Capsule player1_cp =
	{
		players[player1]->m_block_top.VGet(),
		players[player1]->m_block_under.VGet(),
		players[player1]->m_block_r
	};
	// ガードしていないとき
	Capsule player1_no_cp =
	{
		players[player1]->m_hit_body_pos_top.VGet(),
		players[player1]->m_hit_body_pos_under.VGet(),
		players[player1]->m_hit_body_r
	};

	// ------------------------------------------------
	//	ガードしている人に対しての当たり判定を行うかどうか
	// ------------------------------------------------
	// 当たり判定をしていいかどうか
	bool can_check_hit = players[player1]->m_cd_hit_flag && players[player1]->m_block_flag;
	//　プレイヤー１方向ベクトル(殴る方)
	Vector3 vec1 = players[1]->m_pos - players[0]->m_pos;
	// プレイヤー２の方向ベクトル（殴られる方）
	Vector3 vec2;
	vec2.set(sinf(TO_RADIAN(players[1]->m_pos.y)), 0, cosf(TO_RADIAN(players[1]->m_pos.y)));
	// これでうまくいっている
	float vec = GetVector3Dot(vec1, vec2);
	//printfDx("%d\n", vec);
	if (can_check_hit)
	{
		// どの方向からガードカプセルに攻撃が当たったのかを調べる
		// その方向がガードカプセル側であれば、”何もしない”
		// そうじゃなければ、”ダメージ処理”

			// player1のガード用カプセルとplayer2の攻撃用カプセルが当たったとき
		if (HitCheck_Capsule_Capsule(player1_no_cp, player2_hit_cp))
		{
			// ガードの後ろからじゃないとあたらない
			// と、殴ってくる方のあたり判定を行っていいとき
			if (vec <= 0.0f && players[player2]->m_cd_hit_flag) {
				// player1の本体用のカプセルとplayer2の攻撃用カプセルが当たったとき
				players[player1]->m_hp_count.x -= players[player2]->m_attack_damage[players[player2]->m_attack_anim_pick]; // ダメージを入れる
				players[player1]->m_damage_flag = true; // ダメージを受けているフラグを上げる
				players[player1]->m_block_flag = false; // ガードを離すためにガード中のフラグを下げる
				//cd_hit_flag = false
				int  time = players[player1]->m_attack_damage[players[player1]->m_attack_anim_pick];
				PadVidation(players[player2]->m_pad_input, 1000, 500, -1);
				if (!m_stop) 
				{
					hit_stop.Stop_Count_Reset(); // ヒットストップをさせる
				}
			}
		}
	}
}

//---------------------------------------------------------------------------
// キャラクターのステータス描画処理
//---------------------------------------------------------------------------
void GameScene::Draw_Status()
{
	DrawBox(    (int)players[0]->m_hp_pos.x, (int)(players[0]->m_hp_pos.y),         (int)(players[0]->m_hp_count.x), (int)(players[0]->m_hp_count.y), GetColor(0, 255, 0), TRUE);
	DrawLineBox((int)players[0]->m_hp_pos.x, (int)players[0]->m_hp_pos.y,   HP_MAX, (int)players[0]->m_hp_count.y,   GetColor(255, 255, 255));

	DrawBox(    (int)(SCREEN_W / 2 + players[1]->m_hp_pos.x), (int)players[1]->m_hp_pos.y,   (int)(SCREEN_W / 2 + players[1]->m_hp_count.x), (int)players[1]->m_hp_count.y,   GetColor(0, 255, 0), TRUE);
	DrawLineBox((int)(SCREEN_W / 2 + players[1]->m_hp_pos.x), (int)(players[1]->m_hp_pos.y), (int)(SCREEN_W / 2 + HP_MAX),                   (int)(players[1]->m_hp_count.y), GetColor(255, 255, 255));
}
