#pragma once

#include "Base.h"

// キャラクタークラス
// Baseクラスを継承
class CharacterBase : public Base
{
public:

#define HP_MAX 350 // HPの最大値
	//---------------
	// 関数の定義
	//---------------
	//virtual と = 0 しておくことで派生クラスでオーバーロードできる
	CharacterBase();
	virtual void Init(int player_num) = 0;        // 初期処理
	// カメラに対して前後左右に移動するため
	// カメラがどの方向にあるのかを情報として使う
	virtual void Update(Vector3* camera_rot) = 0;		// 更新処理
	virtual void Move_Hit_Update() = 0; // 壁擦り用の関数
	
	virtual void Draw() = 0;		    // 描画処理
	virtual void Exit() = 0;		    // 終了処理

	//---------------------------------------------------------------------------
	// 移動用関数
	// 引数
	// １：今動いていいのか
	// ２：いまは移動していいていいかの判断
	//---------------------------------------------------------------------------
	// 前移動
	void Move_Front(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed);
	// 後ろ移動
	void Move_Dhindo(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed);
	// 左移動
	void Move_Left(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed);
	// 右移動
	void Move_Right(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed);

	// キャラクターの移動用関数(ゲームパッド用)
	void Move_GamePad(bool* m_check_move, Vector3* mov, Vector3* camera_rot, const float* mov_speed);

	// キャラクターの壁擦り用関数
	void Move_Hit(Vector3* before_pos, Vector3* hit_size, Vector3* other_pos, Vector3* other_size);

	// 普通アニメーション変数のNew用関数
	void Nomal_Anim_New(int ANIM_MAX);
	// 普通アニメーションの初期設定
	void Nomal_Anim_Init(int ANIM_IDLE, int ANIM_MAX, int index);

	// 攻撃アニメーション変数のNew用関数
	void Attack_Anim_New(int ATTACK_ANIM_MAX);
	// 攻撃アニメーションの初期設定
	void Attack_Anim_Init(int ATTACK_ANIM_MAX, int index);

	// アニメーション変数をdeleteする用の関数
	void Anim_Delete(int ANIM_MAX, int ATTACK_ANIM_MAX);

	// 攻撃にあったアニメーションさせる関数
	void Attack_Action(int index);


	// 当たり判定のあったとき当たった相手の情報をとってくる関数
	void Get_other(float* hit_other_x, float* hit_other_z, float* hit_other_r); // カプセル、円

	void Get_other(Vector3* hit_other_1, Vector3* hit_other_2);               // 立方体
	//---------------
	// 定数の定義
	//---------------
public:

	//---------------
	// 変数の定義
	//---------------
public:
	// ゲームパッド用の変数
	int pad_input;

protected:

	//---------------------------------------------------------------------------
	// モデルアニメーション用変数
	//---------------------------------------------------------------------------
	int	m_model = 0;	  // 各キャラのモデルを入れる用の変数
	int anim_num = 0;     // 各継承先のクラスでのアニメーションを切り替える用の変数
	int action_mode;      // 今攻撃モードなのか普通モードなのかを判別するを判断する用の変数

	//---------------------------------------------------------------------------
	// 普通アニメーション読み込み用の配列
	//---------------------------------------------------------------------------
	int* anim_model;    // アニメーションモデル
	int* anim_attach;   //モデルにアニメーションをアタッチする用の配列（アタッチ番号を取得する）
	float* anim_total;  //アニメーションが何フレーム科を取得、それを保存する用の配列
	float* anim_rate;	// それぞれのアニメーションがどのくらうのわりあいになるか（0.0f ~ 1.0f）
	float* anim_frame;  // アニメーションが何フレーム進んでいるのか

	//---------------------------------------------------------------------------
	// 攻撃アニメーション用変数
	//---------------------------------------------------------------------------
	int* attack_anim_model;   // 各攻撃アニメーションアニメーション読み込み用の配列
	int* attack_anim_attach;  // モデルに攻撃アニメーションをアタッチする用の配列（アタッチ番号を取得する）
	float* attack_anim_total; // 攻撃アニメーションが何フレーム科を取得、それを保存する用の配列
	float* attack_anim_rate;  // それぞれの攻撃アニメーションがどのくらうのわりあいになるか（0.0f ~ 1.0f）
	float* attack_anim_frame; // 攻撃アニメーションが何フレーム進んでいるのか
	int attack_anim_pick;     // どのアニメーションをしているのかを判断する用

public:
	//---------------------------------------------------------------------------
	// 各キャラの当たり判定用変数
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	// 当たり判定があったときの各処理の判断用変数
	//---------------------------------------------------------------------------
	bool m_move_judge;         // いまは移動していいていいかの判断
	bool m_attack_judge;       // 今攻撃中なのかの判断 
	Vector3 m_hit_other_pos;   // 当たり判定があった相手の座標を入れる
	Vector3 m_hit_other_size;  // 当たり判定があった相手のサイズを入れる（立方体の場合）

	//---------------------------------------------------------------------------
	// カプセル型の当たり判定用変数
	//---------------------------------------------------------------------------
	Vector3 m_hit_body_pos_top;     // カプセルの上側 
	Vector3 m_hit_body_pos_under;   // 下側
	float m_hit_body_r = 0;         // 半径

	//---------------------------------------------------------------------------
	// 移動用当たり判定（ボックス）
	//---------------------------------------------------------------------------
	Vector3 m_move_hit_box_pos;  // キャラの足の下にパネルのようにして使う
	Vector3 m_move_hit_box_size; // パネルサイズ
	Vector3 m_character_size;    // プレイヤーをボックスとしたときの大きさ(中心座標からPANEL_HAL)

	//---------------------------------------------------------------------------
	// 攻撃時の当たり判定用変数（カプセル）
	//---------------------------------------------------------------------------
	Vector3 m_hit_attack_pos_top;     // カプセルの上側 
	Vector3 m_hit_attack_pos_under;   // 下側
	float m_hit_attack_r = 0;         // 半径
protected:
	//---------------------------------------------------------------------------
	// 移動に関する物
	//---------------------------------------------------------------------------
	bool m_check_move;    // 移動中かどうかを判断する変数
	Vector3 mov;          //  ゲームパッド用移動用ベクトル用変数
public:
	Vector3 before_mov;   // 毎フレーム移動前の座標をいれる用の変数

	//---------------------------------------------------------------------------
	// キャラクターのステータス用の変数
	//---------------------------------------------------------------------------
	// キャラクターの体力
	Vector2 m_hp_pos; // 描画座標
	Vector2 m_hp_count; // 計算用
};