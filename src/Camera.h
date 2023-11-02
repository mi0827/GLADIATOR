#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	カメラクラス
// Baseクラスを継承
class Camera : public Base
{
public:
	//---------------
	// 関数の定義
	//---------------
	// コンストラクタ
	Camera();

	void Init();        //　初期処理
	// プレイヤーの情報を受け取る形にします
	// 今回はプレイヤーのｎ後ろにカメラをお嫌いの出
	// プレイヤーの座標と向きを受け取れるようにします
	void Update(Vector3* player_pos);		//	更新処理
	void Draw();		//	描画処理
	void Exit();		//	終了処理

	//---------------
	// 変数の定義
	//---------------
private:
	// カメラが見る座標
	Vector3 m_look;

	// マウスの移動量用の変数
	float m_mouse_move_x; // X座標の移動量
	float m_mouse_move_y; // Y座標の移動量
};
