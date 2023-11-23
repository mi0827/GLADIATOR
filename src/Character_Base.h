#pragma once

#include "Base.h"

// キャラクタークラス
// Baseクラスを継承
class CharacterBase : public Base
{
public:

#define HP_MAX 350 // HPの最大値
#define PUNCH_MAX 2
	//---------------
	// 関数の定義
	//---------------
	//virtual と = 0 しておくことで派生クラスでオーバーロードできる
	CharacterBase();
	virtual void Init(int player_num) = 0; // 初期処理
	virtual void Animation_Init() = 0;     // アニメーション用の初期処理
	// カメラに対して前後左右に移動するため
	// カメラがどの方向にあるのかを情報として使う
	virtual void Update(Vector3* camera_rot) = 0;		// 更新処理
	virtual void Move_Hit_Update() = 0; // 壁擦り用の関数
	virtual void Attack_Update() = 0;   // 攻撃が行われた時に行う
	virtual void Damage_Update() = 0;   // ダメージを食らった時に行う
	virtual void Block_Update() = 0;    // ガードが行われた時に行う
	virtual void Draw() = 0;		    // 描画処理
	virtual void Exit() = 0;		    // 終了処理

	void Update_Status();   // ステータス更新処理
	void Draw_Status();     // ステータス描画用関数
	//---------------------------------------------------------------------------
	// プレイヤーの移動をする関数
	//---------------------------------------------------------------------------
	void Move_Player(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed);
	//---------------------------------------------------------------------------
	// 移動用関数
	// 引数
	// １：今動いていいのか
	// ２：いまは移動していいていいかの判断
	// ３：プレイヤーの向いている向き
	// ４：移動スピード
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
	// アクションにあったアニメーションつける関数（攻撃）
	void Attack_Action(int index);

	// ダメージアニメーション用の変数のNew用関数
	void Damage_Anim_New(int DAMAGE_ANIM_MAX);
	// ダメージアニメーションの初期設定
	void Damage_Anim_Init(int DAMAGE_ANIM_MAX, int index);
	// アクションにあったアニメーションつける関数（ダメージ）
	void Damage_Action(int index);

	// ガードアニメーション用の変数のNew用関数
	void Block_Anim_New(int DAMAGE_ANIM_MAX);
	// ガードアニメーションの初期設定
	void Block_Anim_Init(int DAMAGE_ANIM_MAX, int index);
	// アクションにあったアニメーションつける関数（ガード）
	void Block_Action(int index);

	// アニメーション変数をdeleteする用の関数
	void Anim_Delete();


	// 当たり判定のあったとき当たった相手の情報をとってくる関数
	void Get_other(float* hit_other_x, float* hit_other_z, float* hit_other_r); // カプセル、円

	void Get_other(Vector3* hit_other_1, Vector3* hit_other_2);                 // 立方体

	// 当たり判定を作る関数
	void Attack_Hit_New(Vector3* pot_pos, Vector3* under_pos);

	// 攻撃力を保存する用の関数
	void Set_Attack_Damage(int ATTACK_ANIM_MAX, const int* attack_damage);

	// delete用の関数
	void Delete();
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

	int pad_no = 0;				// 何番のパッドを使っているのか
	void SetPadNo(int no)
	{
		pad_no = no;
	}

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
	int* anim_attach;   // モデルにアニメーションをアタッチする用の配列（アタッチ番号を取得する）
	float* anim_total;  // アニメーションが何フレーム科を取得、それを保存する用の配列
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
	

	//---------------------------------------------------------------------------
	// ガードアニメーション用変数
	//---------------------------------------------------------------------------
	int* block_anim_model;    // アニメーションモデル
	int* block_anim_attach;   // モデルにアニメーションをアタッチする用の配列（アタッチ番号を取得する）
	float* block_anim_total;  // アニメーションが何フレーム科を取得、それを保存する用の配列
	float* block_anim_rate;	  // それぞれのアニメーションがどのくらうのわりあいになるか（0.0f ~ 1.0f）
	float* block_anim_frame;  // アニメーションが何フレーム進んでいるのか
	

	//---------------------------------------------------------------------------
	// ダメージ（受けた時の）アニメーション用変数
	//---------------------------------------------------------------------------
	int* damage_anim_model;    // アニメーションモデル
	int* damage_anim_attach;   // モデルにアニメーションをアタッチする用の配列（アタッチ番号を取得する）
	float* damage_anim_total;  // アニメーションが何フレーム科を取得、それを保存する用の配列
	float* damage_anim_rate;   // それぞれのアニメーションがどのくらうのわりあいになるか（0.0f ~ 1.0f）
	float* damage_anim_frame;  // アニメーションが何フレーム進んでいるのか
	
public:
	int attack_anim_pick;     // どのアニメーションをしているのかを判断する用
	int block_anim_pick;      // どのアニメーションをしているのかを判断する用
	int damage_anim_pick;     // どのアニメーションをしているかを判断する用の変数
	
public:
	//---------------------------------------------------------------------------
	// 各キャラの当たり判定用変数
	//---------------------------------------------------------------------------
	bool cd_hit_flag; //< あたり判定を行てよいかのフラグ


	//---------------------------------------------------------------------------
	// 各アクション判断用変数
	//---------------------------------------------------------------------------
	bool m_attack_judge;       // 今攻撃中なのかの判断 
	bool m_damage_judge;       // 今ダメージを受けているのか
	bool m_block_judge;        // 今ガード中なのか

	//---------------------------------------------------------------------------
	// 当たり判定があったときの各処理の判断用変数
	//---------------------------------------------------------------------------
	bool m_move_judge;         // いまは移動していいていいかの判断
	Vector3 m_hit_other_pos;   // 当たり判定があった相手の座標を入れる
	Vector3 m_hit_other_size;  // 当たり判定があった相手のサイズを入れる（立方体の場合）

	//---------------------------------------------------------------------------
	// キャラクターのカプセル型の当たり判定用変数
	//---------------------------------------------------------------------------
	Vector3 m_hit_body_pos_top;     // カプセルの上側 
	Vector3 m_hit_body_pos_under;   // 下側
	float   m_hit_body_r = 0;       // 半径

	//---------------------------------------------------------------------------
	// 移動用当たり判定（ボックス）
	//---------------------------------------------------------------------------
	Vector3 m_move_hit_box_pos;  // キャラの足の下にパネルのようにして使う
	Vector3 m_move_hit_box_size; // パネルサイズ
	Vector3 m_character_size;    // プレイヤーをボックスとしたときの大きさ(中心座標からPANEL_HAL)

	//---------------------------------------------------------------------------
	// アクション時の当たり判定用変数（カプセル）
	//---------------------------------------------------------------------------
	Vector3 m_hit_cd_pos_top;     // カプセルの上側 
	Vector3 m_hit_cd_pos_under;   // 下側
	float   m_hit_cd_r = 0;       // 半径
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
	Vector2 m_hp_pos;   // 描画座標
	Vector2 m_hp_count; // 計算用
	int* m_attack_damage; // 攻撃力

	//---------------------------------------------------------------------------
	// 攻撃時の当たり判定用変数
	//---------------------------------------------------------------------------
	Vector3 hit_pos_pot;
	Vector3 hit_pos_under;

};