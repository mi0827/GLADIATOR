#pragma once

// シーンクラスたちのベースクラス
class Scene_Base
{
public:


	// 初期処理
	virtual void Init() = 0;
	// 更新処理
	// 引数
	// １：BGMのボリューム
	// ２：SEのボリューム
	virtual void Update(int bgm_volume, int se_volume) = 0;
	// 描画処理
	virtual void Draw() = 0;
	// 終了処理
	virtual void Exit() = 0;

	//// 今のシーンから次のシーンに切り替える関数
	//void Scene_Change_Judge(int* now_scene, int* next_scene);

	//// フレームから時間に置き換える関数
	//void Flame_Time_Update(int* flame, int* time);
public:
	const int FLAME_MAX = 60; // 一秒何フレームか

	bool scene_change_judge ; // シーンの切り替えを行っていいか (trueになったらシーンの切り替え可能)

};