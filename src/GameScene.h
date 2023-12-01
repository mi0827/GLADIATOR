#pragma once

class GameScene
{
public:
	GameScene();
	~GameScene();
	// 初期処理
	void GameInit();

	// 更新処理
	void GameUpdate();

	// 描画処理
	void GameDraw();

	// 終了処理
	void GameExit();

	// 移動時のお互いのあたり判定v
	void Move_Hit();

	// タイマーの更新処理
	void Time_Update();
	// タイマーの描画
	void Time_Draw();

	// 攻撃のあたり判定を行う関数
	void Attack_Hit(int player1, int player2);
	// ガードの当たり判定
	void Block_Hit(int player1, int player2);
	// キャラクターのステータス描画処理
	void Draw_Status();

private:

};