#pragma once



// Playerクラス
// CharacterBaseクラスを継承
class Ninja : public CharacterBase
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
	Ninja(); // コンストラクタ
	void Init(int player_num)override;        //　初期処理
	void Animation_Init()override;              // アニメーション用の初期処理
	// カメラに対して前後左右に移動するため
	// カメラがどの方向にあるのかを情報として使う
	void Update(Vector3* camera_rot/*,bool status_flag*/) override;		//	更新処理
	void Move_Hit_Update()override;           // プレイヤーの移動用当たり判定更新処理（壁擦り）
	void Attack_PressButton_Update(Vector3* camera_rot)override; // アクションに関するボタン押し用の関数（見やすくするための関数）
	void Attack_Update()override;   // 攻撃が行われた時に行う
	void Damage_Update()override;	// ダメージを食らった時に行う
	void Block_Update()override;	// ガードが行われた時に行う
	void Draw()override;		//	描画処理
	void Exit()override;		//	終了処理
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
		ATTACK_SLIDE_ANIM,          // スライディング
		ATTACK_SPECIAL_ANIM,        // スペシャル

		ATTACK_ANIM_MAX // 攻撃アニメーションの数
	};


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