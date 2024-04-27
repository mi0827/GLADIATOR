#pragma once

/**
* @file Model.h
* @ brief モデル用のクラス
*/
class Model :public Base
{
public:
	//-----------
	// 関数
	//-----------

	Model();
	~Model();

	/**
	* @fn
	* @brief モデル読み込み用関数
	* @param (data[256]) モデルデータのパス
	* @detail モデルを読み込むための関数
	*/
	void LoadModel(const char data[256]);

	/**
	* @fn
	* @brief モデル描画用の関数
	* @detail モデルを描画するための関数
	*/
	void DrawModel();

	/**
	* @fn
	* @brief モデルの座標をもらってくる用関数
	* @return 現在のモデルの座標
	* @detail 現在の座標のモデルを知るため用関数
	*/
	Vector3 GetModelPos();

	/**
	* @fn
	* @brief モデルの座標をセットする用関数
	* @param セットしたい座標
	* @detail セットしたい座標をモデルをにセットする用関数
	*/
	void SetModelPos(Vector3 pos);

	/**
	* @fn
	* @brief モデルの向きをもらってくる用の関数
	* @return 現在にのモデルの向き
	* @detail 現在のモデルの向きを知るための用の関数
	*/
	Vector3 GetModelRot();

	/**
	* @fn
	* @brief モデルに向きをセットする用関数
	* @param セットしたい向き
	* @detail セットしたい向きをモデルをにセットする用関数
	*/
	void SetModelRot(Vector3 rot);

	/**
	* @fn
	* @brief モデルのスケールをセットする用関数
	* @param セットしたいスケール
	* @detail セットしたいスケールをモデルをにセットする用関数
	*/
	void SetModelScale(Vector3 rot);

public:

	// 変数

	//! モデル用の変数
	int m_model;

	/**
    * @struct transform
    * モデルの座標、回転、スケールをまとめたもの
    */
	struct Transform
	{
		Vector3 pos{ 0.0f,0.0f,0.0f };
		Vector3 rot{ 0.0f,0.0f,0.0f };
		Vector3 scale{ 0.1f,0.1f,0.1f };
	};
	Transform transform;


	
};