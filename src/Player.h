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
	void Init(int player_num) override;         // 初期処理
	// カメラに対して前後左右に移動するため
	// カメラがどの方向にあるのかを情報として使う
	void Update(Vector3* camera_rot) override;  // 更新処理
	void Move_Hit_Update()override;

	void Draw() override;		// 描画処理
	void Exit() override;		//終了処理


	//---------------
	// 変数の定義
	//---------------
private:


	//---------------------------------
	// アニメーション用の列挙体
	enum Animation
	{
		ANIM_IDLE, // アイドル
		ANIM_RUN,  // 走る

		ANIM_MAX // アニメーションの最大個数
	};

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


public:
	// bead 関連
	//------------------------------------
	// 弾が消えるまでのカウント用変数
	float lifespan_count = NULL;

public:
	// それぞれの攻撃ダメージの設定
	int attack_damage[ATTACK_ANIM_MAX]
	{
		20,  // 遠距離攻撃
		30,  // 近距離攻撃１
		30,  // 近距離攻撃２
		10,  // スライディング
		150, // 必殺技
	};



	// 近接攻撃にの当たり判定用の構造体
	struct Hit_capsule_data
	{
		Vector3 hit_top;   // トップの座標
		Vector3 hit_under; // アンダーの座標
		float hit_r;       // 半径
		float hit_anim_frame;  // アニメーションのフレーム(ここで出す)
	};

	Hit_capsule_data hit_areas[ATTACK_ANIM_MAX] =
	{
		//遠距離普通攻撃
		 { Vector3(0,0,0), // トップ
		   Vector3(0,0,0), // アンダー
		   0.0f,   // 半径
		   0.0,    // フレーム
		 }
		 // 近距離攻撃１
		,{
		   Vector3(8,   13, 8), // トップ
		   Vector3(6, 12.7, 6), // アンダー
		   1.0f,   // 半径
		   18.000, // フレーム}	
		}
		// 近距離攻撃2
		,{
		   Vector3(0,0,0), // トップ
		   Vector3(0,0,0), // アンダー
		   0.0f,   // 半径
		   0.000, // フレーム} //
		}
		// スライディング
		,{
		   Vector3(8,1,10), // トップ
		   Vector3(8,0,10),     // アンダー
		   1.0f,   // 半径
		   0.000, // フレーム} // 
		}
		// 必殺技
		,{
		   Vector3(0,0,0), // トップ
		   Vector3(0,0,0),     // アンダー
		   1.0f,   // 半径
		   18.000, // フレーム} //
		}

	};
	Hit_capsule_data* now_hit_area;



	// 弾が何かにあたったか
	bool bead_hit_judg;
	// 弾変数
	Vector3* bead_pos = 0; // 座標
	float bead_r = 0;      // 半径

};