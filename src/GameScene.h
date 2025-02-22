#pragma once
// #include "Character_Base.h"


class GameScene :public Scene_Base
{
public:
	GameScene();
	// ~GameScene();
	// 初期処理
	void Init()override;

	// 更新処理
	void Update(int bgm_volume, int se_volume)override;

	// 描画処理
	void Draw()override;

	// 終了処理
	void Exit()override;

	// SEの初期化
	void SE_Init();
	// BGMの初期化
	void BGM_Init();

	// ライトの初期化
	void Light_Init();
	// ライトの更新処理
	void Light_Update();

	// チュートリアルの更新処理
	void Tutorial_Update();
	// メインプレイシーンの更新処理
	void PlayMain_Update();
	// プレイエンドの更新処理
	void PlayEnd_Update();
	// エンドシーンでの勝敗に関する関数
	void Play_Victory_Draw(CharacterBase* character1, CharacterBase* character2); // 勝者を決める関数

	// 描画用の文字列のサイズ調整
	void Draw_String_Size(float* w, float* h, const char* sting);

	// キャラクターの更新処理
	void Character_Update(int se_volume);
	// タイマーの更新処理
	void Time_Update(int& time_count);
	// タイマーの描画
	void Time_Draw();
	// チュートリアルでの描画処理
	void Tutorial_Draw();
	// 準備完了を描画させるだけの関数
	void Ready_Draw();
	// エンドでの描画処理
	void End_Draw();

	// 攻撃のあたり判定を行う関数
	void Attack_Hit(int player1, int player2);
	// ガードの当たり判定
	void Block_Hit(int player1, int player2);
	// キャラクターのステータス描画処理
	void Draw_Status();

	// ゲームシーン
	enum play_scene
	{
		Play_Tutorial, // チュートリアルシーン
		Play_Main,     // ゲームメインシーン
		Play_End,      // プレイENDシーン

		Play_Max       // プレイシーンの最大
	};

	// SE
	enum play_se
	{
		READY, // チュートリアルの準備完了

		SE_MAX // SEの最大数
	};

	// BGM
	enum BGM
	{
		TUTORIAL_BGM,  // チュートリアルのBGM
		BATTLE_1_BGM,  // プレイメインのBGM１
		BATTLE_2_BGM,  // プレイメインのBGM２
		BATTLE_3_BGM,  // プレイメインのBGM３
		BGM_MAX        // BGMの最大数
	};

private:

	int time_count;     // フレーム数を現実の時間で計算する用の変数
	int flame_count;    // フレーム数をカウントをする変数
	int play_scene;     // チュートリアルの途中かを判別
	int end_count;      // エンドシーンの時間
	bool status_flag;   // ステータス更新処理していいかのフラグ

	//-------------------------------------------
	// チュートリアルで使う変数
	//-------------------------------------------
	const float BUTTON_COUNT_MAX = 180; // ３秒
	// 準備完了フラグ
	bool ready_flag1 = false;
	bool ready_flag2 = false;
	// ボタンの長押しをカウントする用の変数
	float button_count1 = 0;
	int button_count2 = 0;

	// ヒットストップ科の判断用変数
	bool stop;

	// ライト用の変数
	static const int light_MAX = 1;
	int light_handle[light_MAX]; // ライトハンドル
	COLOR_F original_dif_color; 
	COLOR_F original_spc_color;
	COLOR_F original_amb_color;
	Vector3 original_light_rot; // 初期ライトの向き
	Vector3 light_rot; // ライトの回転
	Vector3 light_pos; // ライトのポジション

	static const int FIGHT_START_COUNT_MAX = 300; // 戦いが始まるまでの準備時間
	bool fight_start_flag = false; // 戦いが始まる用のフラグ
	int fight_start_count = 0; // レディーされから戦いが始まるまでのカウント

	int draw_fight_pos_x = 0; // Lady,Fightの描画座標用変数
	//int shadowmap_handle; // シャドーマっプ
};