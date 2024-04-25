#pragma once

/**
* @file Move.h
* @ brief キャラの移動用のクラス
*/
class Move :public Base
{
public:

	Move();
	~Move();

	/**
	* @fn
	* @brief 更新処理
	* @param １：今動いていいかの変数
	* @param ２：カメラの向き
	* @param ３：プレイヤーの向いている向き
	* @param ４：移動スピード
	* @param ５：プレイヤーの座標
	* @param ６：パッドの番号
	* @param ７：スティックの値
	* @detail 移動に関するものの更新処理
	*/
	void Update(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed, Vector3* player_pos, PAD_NO m_pad_no, Vector3 m_mov);

	/**
	* @fn
	* @brief 移動に関する当たり判定用の関数
	* @param １：自分 (キャラ) の座標(今の座標)
	* @param ２：自分（キャラ）の座標(当たり判定前の)
	* @param ３：自分（キャラ）の当たり判定のサイズ（中心から見たサイズ）
	* @param ４：壁の座標
	* @param ５：壁の当たり判定のサイズ（中心から見たサイズ）
	* @detail 移動の壁擦り用関数
	*/
	void Move_Hit(Vector3* player_pos, Vector3* before_pos, Vector3* hit_size, Vector3* other_pos, Vector3* other_size);

	/**
	* @fn
	* @brief ゲームパッドでの移動用関数
	* @param １：動いていいのかの変数
	* @param ２：スティックの値
	* @param ３：キャラの向いている向き
　　* @param ４：キャラの座標
	* @param ５：移動スピード
	* @detail ゲームパッドでの移動用関数
	*/
	void Move_GamePad(bool* m_check_move, Vector3* mov, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed);

	/**
	* @fn
	* @brief ゲームパッドでの移動用関数
	* @param １：動いていいのかの変数
	* @param ２：カメラの向き
	* @param ３：キャラの向いている向き
	* @param ４：キャラの座標
	* @param ５：移動スピード
	* @detail ゲームパッドでの移動用関数
	*/
	void Move_Front(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed);

	/**
	* @fn
	* @brief ゲームパッドでの移動用関数
	* @param １：動いていいのかの変数
	* @param ２：カメラの向き
	* @param ３：キャラの向いている向き
	* @param ４：移動スピード
	* @detail ゲームパッドでの移動用関数
	*/
	void Move_Dhindo(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed);


	/**
	* @fn
	* @brief ゲームパッドでの移動用関数
	* @param １：動いていいのかの変数
	* @param ２：カメラの向き
	* @param ３：キャラの向いている向き
	* @param ４：移動スピード
	* @detail ゲームパッドでの移動用関数
	*/
	void Move_Left(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed);


	/**
	* @fn
	* @brief ゲームパッドでの移動用関数
	* @param １：動いていいのかの変数
	* @param ２：カメラの向き
	* @param ３：キャラの向いている向き
	* @param ４：移動スピード
	* @detail ゲームパッドでの移動用関数
	*/
	void Move_Right(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed);


public:
	//! プレイヤーの座標を入れておくもの
	Vector3 m_player_pos = { 0.0f,0.0f,0.0f };

	//! プレイヤーの移動スピードを入れておくもの
	// static const float player_mov_speed;

	//! プレイヤーの向きを入れておくもの
	Vector3 m_player_rot = { 0.0f,0.0f,0.0f };

	//! カメラの向きを入れておくもの
	Vector3 m_camera_rot = { 0.0f,0.0f,0.0f };
};