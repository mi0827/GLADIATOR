#pragma once
#include "src/System/Transform.h"
#include "src/Model/Model.h"
/**
* @fule Fighter.h
* @brief キャラクターファイターのクラス
*/


/**
* ファイターのクラス
*/
class Fighter : public CharacterBase
{
	//public:
	//	//コンストラクタ
	//	Fighter();
	//	// デストラクタ
	//	~Fighter();
	//
	//	/**
	//	* @fn
	//	* 初期処理用の関数
	//	* @param 何番目のキャラか
	//	* @detail コンストラクタでできない色々なものの初期化を行う関数
	//	*/
	//	void Init(int player_num)override;
	//
	//	/**
	//	* @fn
	//	* アニメーション用の初期処理用関数
	//	*/
	//	void Animation_Init()override;              // アニメーション用の初期処理
	//
	//	/**
	//	* @fn
	//	* 更新処理用の関数
	//	* @param １：カメラの向き
	//	* @param ２：SEのボリューム
	//	* @detail キャラの更新をまとめる関数
	//	* @detail 引数の説明
	//	* @detail カメラに対して前後左右に移動するためカメラの情報が必要
	//	* @detail SEのボリュームの変更を使うために必要
	//	*/
	//	void Update(Vector3* camera_rot, int SE_Volume)override;
	//
	//	/**
	//	* @fn
	//	* プレイヤーの移動用の当たり判定更新処理（壁擦り）
	//	*/
	//	void Move_Hit_Update()override;
	//
	//	/**
	//	* @fn
	//	* アクションに関するボタンの押し用の関数
	//	* @param カメラの向き
	//	*/
	//	void Attack_PressButton_Update(Vector3* camera_rot)override;
	//
	//	void Attack_Update()override;   // 攻撃が行われた時に行う
	//	// ダメージを食らった時に行う関数
	//	// 引数
	//	// くらったダメージ
	//	void Damage_Update(int* m_attack_damage)override;
	//
	//	void Block_Update()override;	// ガードが行われた時に行う
	//	void Draw() override;		// 描画処理
	//	void Exit() override;		// 終了処理
	//	void SE_Init()override;     // SEの初期化関数
	//
	//public:
	//	const float MOVE_SPEED = 1.5f; // 走る用のスピード
	//	 
	//	static const int anim_max = 2;
	//	
	// Playerクラス
	// CharacterBaseクラスを継承
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
	Fighter(); // コンストラクタ
	void Init(int player_num) override;         // 初期処理
	void Animation_Init()override;              // アニメーション用の初期処理

	// カメラに対して前後左右に移動するため
	// カメラがどの方向にあるのかを情報として使う
	// 更新処理
	// 引数
	// １：カメラの向き
	// ２：SEのボリューム
	void Update(Vector3* camera_rot, int SE_Volume/*, bool status_*/) override;  // 更新処理

	// プレイヤーの移動用当たり判定更新処理（壁擦り）
	void Move_Hit_Update()override;

	// アクションに関するボタン押し用の関数（見やすくするための関数）
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
	float m_lifespan_count = NULL;

public:
	//Transform transform;
	Model model;
};
