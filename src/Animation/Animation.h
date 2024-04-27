#pragma once
#include <iostream>
/**
* @fule Animation.h
* @brief アニメーション用のクラス
*/

/**
* アニメーション用のクラス
*/
class Animation final
{
public:




	//! コンストラクタ
	//! @param アニメーションの最大数
	Animation(int anim_max);


	//1 デストラクタ
	virtual ~Animation();

	//! 読み込み用関数
	//! @param ファイルのパス
	//! @param アニメーション番号
	void Load_Anim(const char file_path[256], int anim_no, int anim_index);



	//! アッタチ
	//! @param ベースのモデル
	//! @param アッタチしたいモデル番号
	void Attach_Anim(Model* model, int anim_num);

	//! デタッチ
	//! @param ベースのモデル
	//! @param デタッチしたいモデル番号
	void Detach_Anim(Model* model,int anim_num);

	//! アニメーションの切り替え用関数




private:

	int          m_anim_max = 0;          //!< アニメーションの最大数
public:


	//! 再生中のアニメーションの情報構造体
	struct Context
	{
		bool  is_playering = false;         //!< 再生中かどうか
		bool  is_loop = false;              //!< ループ再生かどうか
		int   animation_index = -1;         //!< 現在の再生中の番号
		int   animation_attach_index = -1;  //!< アタッチされたスロット番号
		float m_blend_ratio = 0.0f;         //!< ブレンド比(0.0f～1.0f)
		float animation_total_time = 0.0;   //!< 総再生時間
		float play_time = 0.0f;             //!< 現在再生中の時間
	};

	//! [0]現在のアニメーション
	//! [1]次のアニメーション
	Context m_contexts[2];           //!< 構造体はアニメーションブレンドのため2系統を持つ
	

	float   m_blend_time = 1.0f;    //!< ブレンドの補間時間
	struct Anim_
	{
		int handl = -1;     //! アニメーションの入れ物
		int index = -1;     //! アニメションのインデックス
	};
	Anim_* anim_handl;

	////---------------------------------------------------------------------------
	//// 普通アニメーション読み込み用の配列
	////---------------------------------------------------------------------------
	//
	//int*   m_anim_model = 0;    // アニメーションモデル
	//int*   m_anim_attach = 0;   // モデルにアニメーションをアタッチする用の配列（アタッチ番号を取得する）
	//float* m_anim_total = 0;  // アニメーションが何フレーム科を取得、それを保存する用の配列
	//float* m_anim_rate = 0;	// それぞれのアニメーションのブレンド率（0.0f ~ 1.0f）
	//float* m_anim_frame = 0;  // アニメーションが何フレーム進んでいるのか


	////---------------------------------------------------------------------------
	//// 攻撃アニメーション用変数
	////---------------------------------------------------------------------------
	//int* m_attack_anim_model = 0;    // 各攻撃アニメーションアニメーション読み込み用の配列
	//int* m_attack_anim_attach = 0;   // モデルに攻撃アニメーションをアタッチする用の配列（アタッチ番号を取得する）
	//float* m_attack_anim_total = 0;  // 攻撃アニメーションが何フレーム科を取得、それを保存する用の配列
	//float* m_attack_anim_rate = 0;   // それぞれの攻撃アニメーションのブレンド率（0.0f ~ 1.0f）
	//float* m_attack_anim_frame = 0;  // 攻撃アニメーションが何フレーム進んでいるのか


	////---------------------------------------------------------------------------
	//// ガードアニメーション用変数
	////---------------------------------------------------------------------------
	//int* m_block_anim_model = 0;         // アニメーションモデル
	//int* m_block_anim_attach = 0;        // モデルにアニメーションをアタッチする用の配列（アタッチ番号を取得する）
	//float* m_block_anim_total = 0;       // アニメーションが何フレーム科を取得、それを保存する用の配列
	//float* m_block_anim_rate = 0;	       // それぞれのアニメーションのブレンド率（0.0f ~ 1.0f）
	//float* m_block_anim_frame = 0;       // アニメーションが何フレーム進んでいるのか


	////---------------------------------------------------------------------------
	//// ダメージ（受けた時の）アニメーション用変数
	////---------------------------------------------------------------------------
	//int* m_damage_anim_model = 0;    // アニメーションモデル
	//int* m_damage_anim_attach = 0;   // モデルにアニメーションをアタッチする用の配列（アタッチ番号を取得する）
	//float* m_damage_anim_total = 0;  // アニメーションが何フレーム科を取得、それを保存する用の配列
	//float* m_damage_anim_rate = 0;   // それぞれのアニメーションがどのくらうのわりあいになるか（0.0f ~ 1.0f）
	//float* m_damage_anim_frame = 0;  // アニメーションが何フレーム進んでいるのか

};