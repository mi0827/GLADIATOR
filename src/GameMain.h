#pragma once

#define SCREEN_W	800
#define SCREEN_H	450


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

// 攻撃のあたり判定を行う関数
void Attack_Hit();
// キャラクターのステータス描画処理
void Draw_Status();