#pragma once
#include"Base.h"

class Object : public Base
{
public:
	//---------------
	// 関数の定義
	//---------------
	// 各関数の定義
	Object();// コンストラクタ



	void Init(float* i);        //　初期処理
	void Update();		//	更新処理
	void CreateObjects(); // オブジェクトを作る関数
	void Draw();		//	描画処理
	void Exit();		//	終了処理

	//---------------
	// 変数の定義
	//---------------
private:
	//-------------------------------------------------
	// 円錐関連
	Vector3 m_cone_top_pos;    // 円錐の頂点座標
	Vector3 m_cone_bottom_pos; // 円錐の底辺の中心座標
	float   m_cone_r;          // 円錐の中心座標
	float   m_cone_color;      // 色 

public:
	//--------------------------
	// 立方体関連
	Vector3 m_cube_top_pos;     // 立方体の上の座標
	Vector3 m_cube_bottom_pos;  // 立方体の下の座標
	Vector3 m_cube_hit_pos;     // 当たり判定用の座標（cubeの中心から当たり判定をとるため）
	Vector3 m_cube_size;        // サイズ
	Vector3 m_cube_size_half;   // サイズの半分のサイズ（cubeの中心から当たり判定をとるため）
	float   m_cube_color;       // 色
};