#pragma once


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

	const float MOVE_SPEED = 1.5f; // 走る用のスピード
	const float WARP = 50.0f;      // キャラクターのワープする量
	const float HIT_BODY_R = 3.0f; // このキャラの体の当たり判定の半径
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
	void Update(Vector3* camera_rot, int SE_Volume/*, bool status_*/) override;  // 更新処理
	void Move_Hit_Update()override;           // プレイヤーの移動用当たり判定更新処理（壁擦り）
	void Attack_PressButton_Update(Vector3* camera_rot)override; // アクションに関するボタン押し用の関数（見やすくするための関数）
	void Attack_Update()override;   // 攻撃が行われた時に行う
	void Damage_Update(int* m_attack_damage)override;	// ダメージを食らった時に行う
	void Block_Update()override;	// ガードが行われた時に行う
	void Draw() override;		// 描画処理
	void Exit() override;		// 終了処理
	void SE_Init()override;     // SEの初期化関数

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
		ATTACK_PUNCH_1_ANIM,        // パンチ１
		ATTACK_PUNCH_2_ANIM,        // パンチ２
		ATTACK_PUNCH_3_ANIM,        // パンチ３
		ATTACK_PUNCH_4_ANIM,        // パンチ４（コンボの最後の技*キックになってる）
		ATTACK_WARP_ANIM,          // スライディング
		ATTACK_SPECIAL_ANIM,        // スペシャル

		ATTACK_ANIM_MAX             // 攻撃アニメーションの数
	};

	// SE用の列挙体
	enum SE
	{
		SE_LONG,    // 投げ技
		SE_PUNCH_1, // パンチ１
		SE_PUNCH_2, //	パンチ２
		SE_PUNCH_3, //	パンチ３
		SE_KICK,	// キック
		SE_SPECIAL, // 必殺技 

		SE_MAX // SEの最大数
	};

	// アクション用の当たり判定用の列挙体
	enum HIT_ACTION
	{
		THROW_ATTACK_HIT,          // 遠距離普通攻撃当たり判定
		ATTACK_PUNCH_1_HIT,        // パンチ攻撃１用の当たり判定
		ATTACK_PUNCH_2_HIT,        // パンチ攻撃２用の当たり判定
		ATTACK_PUNCH_3_HIT,        // パンチ攻撃３用の当たり判定 
		ATTACK_PUNCH_4_HIT,        // パンチ４（コンボの最後の技*キックになってる）
		BLOCK_HIT,                 // ブロック用の当たり判定
		SPECIAL_HIT,               // 必殺技の当たり判定

		HIT_ACTION_MAX             // 当たり判定の数
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
		BLOCK_ANIM,  // ブロックアニメーション


		BLOCK_ANIM_MAX
	};

	// エフェクトの列挙体
	enum EFFECT
	{
		THROW_EFFECT,    // 遠距離技
		PUNCH_EFFECT,    // パンチ
		PUNCH2_EFFECT,   // パンチ２
		GUARD_EFFECT,    // ガード用
		SPECIAL_EFFECT,  // 必殺技１
		SPECIAL2_EFFECT, // 必殺技２
		WARP_EFFECT,     // ワープ

		EFFECT_MAX       // エフェクトの最大数
	};

public:
	//------------------------------------
	// bead 関連
	//------------------------------------
	// 弾が消えるまでのカウント用変数
	float lifespan_count = NULL;

public:
	// それぞれの攻撃ダメージの設定
	const int attack_damage[ATTACK_ANIM_MAX]
	{
		40,  // 遠距離攻撃
		40,  // パンチ１
		40,  // パンチ２
		50,  // パンチ３
		70,  // パンチ４
		20,  // スライディング
		400, // 必殺技
	};
	// 引数で使用するために移す
	const int* m_damage = attack_damage;


	// 近接攻撃にの当たり判定用の構造体
	struct Hit_capsule_data
	{
		Vector3 hit_top = { 0.0f,0.0f,0.0f };   // トップの座標
		Vector3 hit_under = { 0.0f,0.0f,0.0f }; // アンダーの座標
		float hit_r = 0.0f;       // 半径
		float hit_anim_frame =0.0f;  // アニメーションのフレーム(ここで出す)
	};


	// 当たり判定の場所
	Hit_capsule_data hit_areas[HIT_ACTION_MAX] =
	{
		// 投げアクション１
		{
		  Vector3(0, 0, 0), // トップ
		  Vector3(0, 0, 0), // アンダー
		  2.0f,   // 半径
		  0.000, // フレーム}	
		},
		// パンチ攻撃１
		{
		  Vector3(8,   13, 8), // トップ
		  Vector3(6, (float)12.7, 6), // アンダー
		  1.5f,   // 半径
		  15.000, // フレーム}	
		},
		{ // パンチ攻撃２
		  Vector3(7.5,   12.5, 7.5), // トップ
		  Vector3(6, 12, 6), // アンダー
		  1.5f,   // 半径
		  15.000, // フレーム}	
		},
		{ // パンチ攻撃３
		  Vector3(9,   13, 9), // トップ
		  Vector3(5.5, (float)12.7, 5.5), // アンダー
		  1.5f,   // 半径
		  55.000, // フレーム}	
		},
		{ // パンチ攻撃４（パンチじゃなくてキックが出る）
		  Vector3(15,  14, 15), // トップ
		  Vector3(7,   11,  7), // アンダー
		  1.5f,   // 半径
		  50.000, // フレーム}	
		},
		// ガードアクション
		{
		   Vector3(5,  17, 3), // トップ
		   Vector3(5,   5, 3), // アンダー
		   3.0f,   // 半径
		   0.0,    // フレーム
		},
		// 必殺技
		{
		   Vector3(0,  0, 0), // トップ
		   Vector3(0,  0, 0), // アンダー
		  100.0f,   // 半径
		   0.0,    // フレーム
		},
	};

	Hit_capsule_data* now_hit_area = 0;

	int m_player_num = 0; // 1pか2pかを判断する用の変数
	COLOR_F m_color[2] = {0}; // このキャラの色
};