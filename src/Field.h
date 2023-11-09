#pragma once

#include "Base.h"


//	Field(フィールド)クラス
// Baseクラスを継承
class Field : public Base
{
	//---------------
	// 定数
	//---------------
private:
	const float MODEL_SIZE = 50.0f; // モデルサイズ

public:
	//---------------
	// 関数の定義
	//---------------
	// コンストラクタ
	Field();	//	初期化処理
	void Init();        //　初期処理

	int Field_Init(); // フィールドのオブジェクトの初期化

	void Update();		//	更新処理
	void Draw();		//	描画処理
	void Exit();		//	終了処理



	//---------------
	// 変数の定義
	//---------------
public:
	// 一つのマスの大きさ
	const int m_field_size = 0;        // サイズ
	const int m_field_size_x = 50; // X方向にどれだけか
	const int m_field_size_y = 50; // Z方向にどれだけか

//	int m_field_obj_max = 0; // 何個のオブジェクトが必要か

	// オブジェクトクラス型のポインタはいてる　
	std::vector<Object*> objects;

	// オブジェクトの描画位置を微妙にずらすための配列変数
	//float z_pos[OBJECT_MAX];

	// フィールドのオブジェクトを置く座標用の二次元配列
	// int* MapData;

	// int* map_num; // mapデータに何番が入っていいるかを知るための変数



private:
	int m_model; // モデル用の変数
};
