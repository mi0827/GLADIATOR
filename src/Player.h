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
		ATTACK_ACTION, // 攻撃アクション
		BLOCK_ACTION,  // ガードアクション
		DAMAGE_ACTION  // ダメージアクション
	};

	//---------------
	// 定数
	//---------------
private:

	const float MOVE_SPEED = 3.0f; // 走る用のスピード
	const float WARP = 50.0f;      // キャラクターのワープする量

public:

	//---------------
	// 関数の定義
	//---------------
	// 各関数の定義
	Player(); // コンストラクタ
	void Init(int player_num) override;         // 初期処理
	void Animation_Init()override;              // アニメーション用の初期処理
	// カメラに対して前後左右に移動するため
	// カメラがどの方向にあるのかを情報として使う
	void Update(Vector3* camera_rot/*, bool status_*/) override;  // 更新処理
	void Move_Hit_Update()override;           // プレイヤーの移動用当たり判定更新処理（壁擦り）
	void Attack_PressButton_Update(Vector3* camera_rot)override; // アクションに関するボタン押し用の関数（見やすくするための関数）
	void Attack_Update()override;   // 攻撃が行われた時に行う
	void Damage_Update()override;	// ダメージを食らった時に行う
	void Block_Update()override;	// ガードが行われた時に行う
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

	// ダメージアニメーション用の列挙体
	enum DAMAGE_ANIM
	{
		DAMAGE_ANIM,     //< ダメージを受けた時のアニメーション
		DAMAGE_ANIM_1,   //< ダメージを受けた時のアニメーション
		DAMAGE_ANIM_2,   //< 吹き飛ぶアニメーション
		DAMAGE_ANIM_3,   //< 起き上がるアニメーション
		DAMAGE_ANIM_END, //< 最後負けた時のアニメーション

		DAMAGE_ANIM_MAX  // ダメージアニメーションの数
	};

	// ガードアニメーション用の列挙体　
	enum BLOCK_ANIM
	{
		BLOCK_ANIM, // ブロックアニメーション

		BLOCK_ANIM_MAX
	};


	// アクション用の当たり判定用の列挙体
	enum HIT_ACTION
	{
		THROW_ATTACK_1_HIT,    // 遠距離普通攻撃
		ATTACK_SHORT_NORMAL_1_HIT, // 近距離普通攻撃１用の当たり判定
		BLOCK_HIT,                 // ブロック用の当たり判定

		HIT_ACTION_MAX
	};
public:
	// bead 関連
	//------------------------------------
	// 弾が消えるまでのカウント用変数
	float lifespan_count = NULL;

public:
	// それぞれの攻撃ダメージの設定
	const int attack_damage[ATTACK_ANIM_MAX]
	{
		20,  // 遠距離攻撃
		100,  // 近距離攻撃１
		30,  // 近距離攻撃２
		10,  // スライディング
		150, // 必殺技
	};
	// 引数で使用するために移す
	const int* m_damage = attack_damage;

	// 近接攻撃にの当たり判定用の構造体
	struct Hit_capsule_data
	{
		Vector3 hit_top;   // トップの座標
		Vector3 hit_under; // アンダーの座標
		float hit_r;       // 半径
		float hit_anim_frame;  // アニメーションのフレーム(ここで出す)
	};

	Hit_capsule_data hit_areas[HIT_ACTION_MAX] =
	{
		// 投げアクション１
		{
			Vector3(8,   13, 8), // トップ
		  Vector3(6, 12.7, 6), // アンダー
		  1.0f,   // 半径
		  0.000, // フレーム}	
		},
		// 近距離攻撃１
	   {
		  Vector3(8,   13, 8), // トップ
		  Vector3(6, 12.7, 6), // アンダー
		  1.0f,   // 半径
		  18.000, // フレーム}	
	   },
	   //ガードアクション
	   {  Vector3(5,  17, 3), // トップ
		  Vector3(5,   5, 3), // アンダー
		  3.0f,   // 半径
		  0.0,    // フレーム
	   },
	};

	Hit_capsule_data* now_hit_area;





};