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

	void Field_Init(); // フィールドのオブジェクトの初期化

	void Update();		//	更新処理
	void Draw();		//	描画処理
	void Exit();		//	終了処理



	//---------------
	// 変数の定義
	//---------------
public:
	
	const int field_size_x = 50; 
	const int field_size_y = 50;


	// フィールドのオブジェクトを置く座標用の二次元配列
	// int* MapData;

	// int* map_num; // mapデータに何番が入っていいるかを知るための変数


	
private:
	int m_model; // モデル用の変数
};
