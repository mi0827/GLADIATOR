#include "WinMain.h"
#include "GameMain.h"

#include "GameScene.h"

GameScene play_scene; // ゲームプレイシーンのオブジェクト


// 初期処理(各シーンの)
void GameInit()
{
	play_scene.GameInit(); 
}

// 更新処理
void GameUpdate()
{
	play_scene.GameUpdate();
	
}

// 描画処理
void GameDraw()
{
	play_scene.GameDraw();
	
}

// 終了処理
void GameExit()
{
	play_scene.GameExit();

}
