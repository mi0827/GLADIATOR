#include "WinMain.h"
#include "GameMain.h"

#include "GameScene.h"
#include "TitleScene.h"

TiteleScene titel_scene;
GameScene play_scene; // ゲームプレイシーンのオブジェクト

int scene_num; // 今どのシーン名のを見る用の変数
// 各シーンでの使い分けをするためのシーンの列挙隊
enum Scene
{
	Titele, // タイトル
	Play,  // メインのプレイシーン
	End,   // エンド

	Scene_Max // シーンの最大数
};

// 初期処理(各シーンの)
void GameInit()
{
	titel_scene.Init();
	play_scene.Init(); 

	scene_num = Titele; // 最初はタイトルシーンから始める
}

// 更新処理
void GameUpdate()
{
	switch (scene_num)
	{
	case Titele: // タイトルシーン
		
		titel_scene.Update();
		if (titel_scene.scene_change_judge) {    // シーンの切り替えの許可が下りれば
			Scene_Change_Judge(scene_num, Play); // シーンの切り替え
		}
		break;

	case Play:  // プレイシーン
		play_scene.Update();
		break;
	case End:  // エンドシーン
		break;
	}

	
}

// 描画処理
void GameDraw()
{
	switch (scene_num)
	{
	case Titele: // タイトルシーン

		titel_scene.Draw();
		// titel_scene.Draw();
		break;

	case Play:  // プレイシーン
		play_scene.Draw();
		break;
	case End:  // エンドシーン
		break;
	}
	
}

// 終了処理
void GameExit()
{
	titel_scene.Exit();
	play_scene.Exit();
}


//----------------------------------------------
// 今のシーンから次のシーンに切り替える関数
//----------------------------------------------
void Scene_Change_Judge(int& now_scene, const int& next_scene)
{
	// 今のシーン番号に次行いたいシーン番号を入れる
	now_scene = next_scene;
}