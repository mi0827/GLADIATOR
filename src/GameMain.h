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

// シーン切り替え用の関数
void Scene_Change_Judge(int& now_scene, const int& next_scene);

