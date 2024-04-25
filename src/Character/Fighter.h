#pragma once

/**
* @fule Fighter.h
* @brief キャラクターファイターのクラス
*/


/**
* ファイターのクラス
*/
class Fighter : public CharacterBase 
{
public:
	//コンストラクタ
	Fighter();
	// デストラクタ
	~Fighter();

	/**
	* @fn
	* 初期処理用の関数
	* @param 何番目のキャラか
	* @detail コンストラクタでできない色々なものの初期化を行う関数
	*/
	void Init(int player_num)override;

	/**
	* @fn
	* アニメーション用の初期処理用関数
	*/
	void Animation_Init()override;              // アニメーション用の初期処理

	/**
	* @fn
	* 更新処理用の関数
	* @param １：カメラの向き
	* @param ２：SEのボリューム
	* @detail キャラの更新をまとめる関数
	* @detail 引数の説明
	* @detail カメラに対して前後左右に移動するためカメラの情報が必要
	* @detail SEのボリュームの変更を使うために必要
	*/
	void Update(Vector3* camera_rot, int SE_Volume)override;

	/**
	* @fn
	* プレイヤーの移動用の当たり判定更新処理（壁擦り）
	*/
	void Move_Hit_Update()override;

	/**
	* @fn
	* アクションに関するボタンの押し用の関数
	* @param カメラの向き
	*/
	void Attack_PressButton_Update(Vector3* camera_rot)override;

	void Attack_Update()override;   // 攻撃が行われた時に行う
	// ダメージを食らった時に行う関数
	// 引数
	// くらったダメージ
	void Damage_Update(int* m_attack_damage)override;

	void Block_Update()override;	// ガードが行われた時に行う
	void Draw() override;		// 描画処理
	void Exit() override;		// 終了処理
	void SE_Init()override;     // SEの初期化関数

public:
	const float MOVE_SPEED = 1.5f; // 走る用のスピード
};