#pragma once
#include "Character_Base.h"

// Playerクラス
// CharacterBaseクラスを継承
class Player : public CharacterBase
{
	// プレイヤーがどのアクションをしているかの判断用の列挙体
	enum ActionMode
	{
		NORMAL_ACTION, // アイドルや走るアニメーションをしている
		ATTACK_ACTION // 攻撃アクション
	};

	//---------------
	// 定数
	//---------------
private:

	const float MOVE_SPEED = 3.0f; // 走る用のスピード


public:

	//---------------
	// 関数の定義
	//---------------
	// 各関数の定義
	Player(); // コンストラクタ
	void Init() override;        //　初期処理
	// カメラに対して前後左右に移動するため
	// カメラがどの方向にあるのかを情報として使う
	void Update(Vector3* camera_rot) override;		//	更新処理
	void move2(Vector3* camera_rot) ;		//	更新処理

	void Draw()override;		//	描画処理
	void Exit()override;		//	終了処理


	//---------------
	// 変数の定義
	//---------------
public:
	//-----------------------------------------------
	// プレイヤーの当たり判定用変数
	//==============================
	// 当たり判定があったときの各処理の判断用変数
	// bool m_move_judg; // いまは移動していいていいかの判断
	// bool m_attack_judg; // 今攻撃中なのかの判断 



	//===============================
	// カプセル型の当たり判定用変数
	// Vector3 m_hit_body_pos_top;     // カプセルの上側 
	// Vector3 m_hit_body_pos_under;   // 下側
	// const float m_hit_body_r = 2.0f;  // 半径


private:
	//int  action_mode; // 今どのモードなのかを判断する用の変数
	// 移動中かどうか
	//bool m_check_move;

	//---------------------------------
	// アニメーション用の列挙体
	enum Animation
	{
		ANIM_IDLE, // アイドル
		ANIM_RUN,  // 走る

		ANIM_MAX // アニメーションの最大個数
	};
	// 普通アニメーション読み込み用の配列
	int anim_model[ANIM_MAX];
	//モデルにアニメーションをアタッチする用の配列（アタッチ番号を取得する）
	int anim_attach[ANIM_MAX];
	//アニメーションが何フレーム科を取得、それを保存する用の配列
	float anim_total[ANIM_MAX];
	// それぞれのアニメーションがどのくらうのわりあいになるか（0.0f ~ 1.0f）
	float anim_rate[ANIM_MAX];
	// アニメーションが何フレーム進んでいるのか
	float anim_frame[ANIM_MAX];


	// 攻撃アニメーション用の列挙体
	enum ATTACK_ANIM
	{
		ATTACK_LONG_NORMAL_ANIM,    // 遠距離普通攻撃
		ATTACK_SHORT_NORMAL_1_ANIM, // 近距離普通攻撃１
		ATTACK_SHORT_NORMAL_2_ANIM, // 近距離普通攻撃２
		ATTACK_SLIDE_ANIM,          // スライディング
		ATTACK_SPECIAL_ANIM,        // スペシャル


		ATTACK_ANIM_MAX // 攻撃アニメーションの数
	};
	// 各攻撃アニメーションアニメーション読み込み用の配列
	int attack_anim_model[ATTACK_ANIM_MAX];
	// モデルに攻撃アニメーションをアタッチする用の配列（アタッチ番号を取得する）
	int attack_anim_attach[ATTACK_ANIM_MAX];
	// 攻撃アニメーションが何フレーム科を取得、それを保存する用の配列
	float  attack_anim_total[ATTACK_ANIM_MAX];
	// それぞれの攻撃アニメーションがどのくらうのわりあいになるか（0.0f ~ 1.0f）
	float attack_anim_rate[ATTACK_ANIM_MAX];
	// 攻撃アニメーションが何フレーム進んでいるのか
	float attack_anim_frame[ATTACK_ANIM_MAX];
	// どのアニメーションをしているのかを判断する用
	int attack_anim_pick;

	// bead 関連
	//------------------------------------
	// 弾が消えるまでのカウント用変数
	float lifespan_count = 120.0f;

public:

	// 弾が何かにあたったか
	bool bead_hit_judg;
	// 弾変数
	Vector3* bead_pos = 0;
	
};