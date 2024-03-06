#include "WinMain.h"
#include "System/Vector3.h"
#include "System/Vector2.h"
#include "Hit/Hit.h" // あたり判定
#include "Base.h"
#include "System/InputPad.h"
#include "System/Option.h"
// キャラクター.h
#include "Character/Base/Character_Base.h"
#include "Character/Player.h"
#include "Character/Ninja.h"
// オブジェクトクラス
#include "Object/Object.h"
// フィールド.h
#include "Field/Field.h"
// カメラ.h
#include "Camera.h"

#include "Scene/Base/Scene_Base.h"
#include "Scene/GameScene.h"
#include "Scene/TitleScene.h"
#include "Scene/EndScene.h"
#include "GameMain.h"

Option option;

Scene_Base* scene;
// 各シーンのオブジェクト
TiteleScene titel_scene; // タイトル
GameScene play_scene;    // ゲームプレイシーン
EndScene end_scene;      // エンド


int scene_num; // 今どのシーン名のを見る用の変数
// 各シーンでの使い分けをするためのシーンの列挙隊
enum Scene
{
	Titele, // タイトル
	Play,  // メインのプレイシーン
	End,   // エンド

	Scene_Max // シーンの最大数
};

// 初期処理
void GameInit()
{
	// 最初はタイトルシーンから始める
	scene = new TiteleScene;
	scene->Init(); // タイトルシーンの初期化

	scene_num = Titele; // 最初はタイトルシーンから始める
	 
	option.Init(); 
	option.m_option_flag = false; // 最初は開かない

}

// 更新処理
void GameUpdate()
{
	// サウンド変更用関数
	option.Update();
	switch (scene_num)
	{
	case Titele: // タイトルシーン

		scene->Update(option.m_BGM_Volume, option.m_SE_Volume);
		if (scene->m_scene_change_judge) {                             // シーンの切り替えの許可が下りれば
			scene->Exit();                                           // dekete前に終了処理を回す
			Scene_Change_Judge(scene_num, Play);                     // シーンの切り替え
			delete scene;                                            // シーンの切り替えの前にタイトルシーンを初期化
			scene = new GameScene;                                   // 次のシーンをnewしておく
			scene->Init();                                           // 次のシーンの初期処理もここで済ます
		}
		break;

	case Play:  // プレイシーン
		scene->Update(option.m_BGM_Volume, option.m_SE_Volume);
		if (scene->m_scene_change_judge) {                              // シーンの切り替えの許可が下りれば
			scene->Exit();                                            // dekete前に終了処理を回す
			Scene_Change_Judge(scene_num, End);  // シーンの切り替え	                                                        
			delete scene;                                            // シーンの切り替えの前にタイトルシーンを初期化
			scene = new EndScene;                                    // 次のシーンをnewしておく
			scene->Init();                                           // 次のシーンの初期処理もここで済ます
		}
		break;
	case End:  // エンドシーン
		scene->Update(option.m_BGM_Volume, option.m_SE_Volume);
		if (scene->m_scene_change_judge) {                             // シーンの切り替えの許可が下りれば
			scene->Exit();                                           // dekete前に終了処理を回す
			Scene_Change_Judge(scene_num, Titele);                   // シーンの切り替え
			delete scene;                                            // シーンの切り替えの前にタイトルシーンを初期化
			scene = new TiteleScene;                                 // 次のシーンをnewしておく
			scene->Init();                                           // 次のシーンの初期処理もここで済ます
		}
		break;
	}

}

// 描画処理
void GameDraw()
{
	
	scene->Draw(); // 各シーン
	option.Draw(); // オプション画面
}

// 終了処理
void GameExit()
{
	scene->Exit();
}


//----------------------------------------------
// 今のシーンから次のシーンに切り替える関数
//----------------------------------------------
void Scene_Change_Judge(int& now_scene, const int& next_scene)
{
	// 今のシーン番号に次行いたいシーン番号を入れる
	now_scene = next_scene;
}
