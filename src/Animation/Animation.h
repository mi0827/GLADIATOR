#pragma once

/**
* @fule Animation.h
* @brief アニメーション用のクラス
*/

/**
* アニメーション用のクラス
*/
class Animation
{
public:
	
	//!@brief コンストラクタ
	//!@param アニメーションの最大数
	Animation();

	
	//!@brief デストラクタ
	virtual ~Animation();

	//! アニメーションのデータ用の構造体
	struct AnimData
	{
		int handle = -1;     //! アニメーションの入れ物
		int index = -1;     //! アニメションのインデックス
	};
	std::vector<AnimData*> anim_handle;

	//! 再生中のアニメーションの情報構造体
	struct Information
	{
		bool  is_playering = false;         //!< 再生中かどうか
		bool  is_loop = false;              //!< ループ再生かどうか
		int   animation_index = -1;         //!< 現在の再生中の番号
		int   animation_attach_index = -1;  //!< アタッチされたスロット番号
		float m_blend_ratio = 0.0f;         //!< ブレンド比(0.0f～1.0f)
		float animation_total_time = 0.0;   //!< 総再生時間
		float play_time = 0.0f;             //!< 現在再生中の時間
	};
	//! 構造体はアニメーションブレンドのため2系統を持つ
	//! [0]現在のアニメーション
	//! [1]前のアニメーション
	Information m_contexts[2];          

	//! @brief アニメーションの情報の初期化関数
	//! @param どちらの構造体を初期化するかの番号
	void Information_Init(int num);

	//! @brief アニメーションの初期設定
	//! @param アニメーションの数
	//! @param デフォルト設定したいアニメーションの番号
	//! @detail デフォルトアニメーションのセット、アニメーションの入れ物の確保
	void Init_Animation(int anim_max, int default_anim);

	
	//! @brief読み込み用関数
	//! @param ファイルのパス
	//! @param アニメーション番号
	void Load_Animation(const char file_path[256], int anim_no, int anim_index);


	//! @briefアニメーションをセットする関数
	//! @param ベースのモデル
	//! @param アッタチしたいモデル番号
	//! @param ループ再生させるかどうか
	void Attach_Animation(Model* model, int anim_num, bool loop);


	//! @briefついているアニメーションを取り外すようの関数
	//! @param ベースのモデル
	//! @param デタッチしたいモデル番号
	void Detach_Animation(Model* model);


	//! @briefアニメーションの切り替え用関数
	//! @param ベースのモデル
	//! @param 次にセットしたいアニメーション番号
	//! @param アニメーションをループさせるかどうか
	void Change_Animation(Model* model, int anim_num, bool loop);

	//! @brief アニメーションの切り替え用関数
	//! @param ベースのモデル
	//! @param 次にセットしたいアニメーション番号
	//! @param アニメーションをループさせるかどう
	//! @detail アニメーションが終わるタイミングで切り替えるでChange_Animationを呼びたい時用の関数
	void Action_Change_Animation(Model* model, int anim_num, bool loop);

	//! @briefアニメーションの再生
	//! @param ベースのモデル
	void Play_Animation(Model* model);


	//! @briefアニメーションをループさせる
	void Loop_Animation();

	//! @briefループさせない場合
    //! @param ベースのモデル
	void Not_Loop(Model* model);



private:

	int m_anim_max = 0;          //!< アニメーションの最大数
	int m_default_anim = -1;     //!< デフォルトでセットしたアニメーション番号用の変数

};