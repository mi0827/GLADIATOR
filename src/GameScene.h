#pragma once

#include "Scene_Base.h"
class GameScene :public Scene_Base
{
public:
	GameScene();
	// ~GameScene();
	// 初期処理
	void Init()override;

	// 更新処理
	void Update()override;

	// 描画処理
	void Draw()override;

	// 終了処理
	void Exit()override;

	// チュートリアルの更新処理
	void Tutorial_Update();
	// メインプレイシーンの更新処理
	void PlayMain_Update();
	// プレイエンドの更新処理
	void PlayEnd_Update();

	// キャラクターの更新処理（移動時のお互いのあたり判定）
	void Character_Update();

	// タイマーの更新処理
	void Time_Update(int& time_count);
	// タイマーの描画
	void Time_Draw();

	// 攻撃のあたり判定を行う関数
	void Attack_Hit(int player1, int player2);
	// ガードの当たり判定
	void Block_Hit(int player1, int player2);
	// キャラクターのステータス描画処理
	void Draw_Status();


	enum play_scene
	{
		Play_Tutorial, // チュートリアルシーン
		Play_Main,     // ゲームメインシーン
		Play_End,      // プレイENDシーン

		Play_Max       // プレイシーンの最大
	};
private:

	int time_count;     // フレーム数を現実の時間で計算する用の変数
	int flame_count;    // フレーム数をカウントをする変数
	int play_scene;     // チュートリアルの途中かを判別
	int end_count;      // エンドシーンの時間
	bool status_flag;   // ステータス更新処理していいかのフラグ
};