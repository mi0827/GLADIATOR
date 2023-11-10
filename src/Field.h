#pragma once

#include "Base.h"
#include "Object.h"

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
	int Field_Init();   // フィールド上にオブジェクトの置く数を返す関数
	void Object_Init(); // オブジェクトの座標、サイズの初期設定
	void Update();		//	更新処理
	void Draw();		//	描画処理
	void Exit();		//	終了処理



	//---------------
	// 変数の定義
	//---------------
public:
	//---------------
	// マップ情報の設定
	//---------------
	
	// 一つのマスの大きさ
	const int m_field_size = 100;   // サイズ
	std::vector<Object*> objects;  // オブジェクトクラス型のポインタはいてる　
	int obj_max = 0;               // オブジェクトの数



private:
	


	int m_model; // モデル用の変数
};
