#include "WinMain.h"
#include "GameMain.h"
#include "Player.h"
#include "InputPad.h"

#define PANEL_SIZE	5.0f              // パネルの大きさ
#define PANEL_HALF	(PANEL_SIZE/2.0f) // パネルの半分の大きさ

//---------------------------------------------------------------------------
// コンストラクタ（初期化）
//---------------------------------------------------------------------------
Player::Player()
{
	m_pos.set(0.0f, 0.0f, 0.0f);             // 初期座標の設定
	m_rot.set(0.0f, 0.0f, 0.0f);             // 向きの設定
	before_mov.set(m_pos);                       // 最初は最初の座標を入れとく

	anim_num = 0;                                     // 最初は０ばんのアニメーションをする
	action_mode = 0;                                  // 最初は普通アニメーションモードにしておく
	attack_anim_pick = -1;                            // 最初はなんのアニメーションも入っていない
	m_check_move = false;                             // 最初は走っていいない

	//------------------------------
	// 当たり判定用変数
	//=============
	// カプセル
	m_hit_body_pos_top.clear();                       // 上側
	m_hit_body_pos_under.clear();                     // 下側
	m_hit_body_r = 2.0f;                              // 半径

	// あたり判定用
	m_hit_cd_pos_top.set(m_pos.x + 8 * sinf(TO_RADIAN(m_rot.y)), m_pos.y + 13, m_pos.z + 8 * cosf(TO_RADIAN(m_rot.y)));
	m_hit_cd_pos_under.set(m_pos.x + 8 * sinf(TO_RADIAN(m_rot.y)), m_pos.y + 12.7, m_pos.z + 6 * cosf(TO_RADIAN(m_rot.y)));
	m_hit_cd_r = 1.0f;
	//======================
	// 移動用のボックス                                                   
	m_move_hit_box_size.set(PANEL_HALF - 0.1, PANEL_HALF - 0.1, PANEL_HALF - 0.1);    // パネルの大きさ

	// 判断用、フラグ変数
	m_move_judge = false;                              // 最初は動いてはいけない
	attack_flag = false;                            // 攻撃していない
	bead_hit_flag = false;                             // なににもあたってない

	// HP
	m_hp_pos.set(10, 32);           // HPバーの描画位置初期化
	m_hp_count.set(HP_MAX, 32 + 30);   // HPの計算用の初期化
	// スキル
	m_skill_pos.set(10, 72);			    // スキルのクールダウンバーの描画位置初期化
	m_skill_count.set(0, m_skill_pos.y + 30);// スキルのクールダウンバーの計算用の初期化
	// SP
	m_sp_pos.set(10, 112);		   	 // SPのクールダウンバーの描画位置初期化
	m_sp_count.set(0, m_sp_pos.y + 30); // SPのクールダウンバーの計算用の初期化
}

//---------------------------------------------------------------------------
// 初期処理
//---------------------------------------------------------------------------
void Player::Init(int player_num)
{
	m_model = MV1LoadModel("Data/Model/Player/Player.mv1");   // プレイヤーモデルの読み込み
	Animation_Init(); //< アニメーションの設定

	// pad_input = GetJoypadInputState(DX_INPUT_PAD3);  // ゲームパッドの読み込み

	if (player_num == 0) {
		m_pos.set(0.0f, 0.0f, -50.0f);           // 初期座標の設定
		m_rot.set(0.0f, 0.0f, 0.0f);             // 向きの設定
	}
	else {
		m_pos.set(0.0f, 0.0f, 500.0f);            // 初期座標の設定
		m_rot.set(0.0f, 180.0f, 0.0f);			  // 向きの設定
	}

	// 攻撃力の設定
	CharacterBase::Set_Attack_Damage(ATTACK_ANIM_MAX, m_damage);
}

//---------------------------------------------------------------------------
// アニメーション用の初期処理
//---------------------------------------------------------------------------
void Player::Animation_Init()
{
	// 普通アニメーションの初期化
	CharacterBase::Nomal_Anim_New(ANIM_MAX);  // 普通アニメーションに必要な変数の配列を作る
	anim_model[ANIM_IDLE] = MV1LoadModel("Data/Model/Player/Animation/Idle.mv1"); // アイドル
	anim_model[ANIM_RUN] = MV1LoadModel("Data/Model/Player/Animation/Player_Run.mv1");   // 走る
	CharacterBase::Nomal_Anim_Init(ANIM_IDLE, ANIM_MAX, 1); // 普通アニメーションの初期設定

	// 攻撃アニメーションの初期化
	CharacterBase::Attack_Anim_New(ATTACK_ANIM_MAX); //< 攻撃アニメーションに必要な変数の配列を作る
	attack_anim_model[ATTACK_LONG_NORMAL_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/long_normal_attack.mv1");       // 遠距離普通攻撃
	attack_anim_model[ATTACK_SHORT_NORMAL_1_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/Punch.mv1");                 // 近距離攻撃１
	attack_anim_model[ATTACK_SHORT_NORMAL_2_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/short_normal_attack_2.mv1"); // 近距離攻撃２
	attack_anim_model[ATTACK_SLIDE_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/slide.mv1");                          // スライディング
	attack_anim_model[ATTACK_SPECIAL_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/special_attack.mv1");               // 必殺技
	CharacterBase::Attack_Anim_Init(ATTACK_ANIM_MAX, 1); //< 攻撃アニメーションの初期設定

	// ダメージアニメーションの初期化
	CharacterBase::Damage_Anim_New(DAMAGE_ANIM_MAX); //< ダメージアニメーションに必要な変数の配列を作る
	damage_anim_model[DAMAGE_ANIM] = MV1LoadModel("Data/Model/Player/Animation/TakeDamage/damage1.mv1");     //< ダメージ食らった時
	damage_anim_model[DAMAGE_ANIM_1] = MV1LoadModel("Data/Model/Player/Animation/TakeDamage/damage2.mv1");   //< ダメージ食らった時２
	damage_anim_model[DAMAGE_ANIM_2] = MV1LoadModel("Data/Model/Player/Animation/TakeDamage/SweepFall.mv1"); //< 吹き飛ぶアニメーション
	damage_anim_model[DAMAGE_ANIM_3] = MV1LoadModel("Data/Model/Player/Animation/TakeDamage/GettingUp.mv1"); //< 起き上がるアニメーション
	damage_anim_model[DAMAGE_ANIM_END] = MV1LoadModel("Data/Model/Player/Animation/TakeDamage/die.mv1");
	CharacterBase::Damage_Anim_Init(DAMAGE_ANIM_MAX, 1); //< ダメージアニメーションの初期化

	// ガードアニメーションの設定
	CharacterBase::Block_Anim_New(BLOCK_ANIM_MAX);
	block_anim_model[BLOCK_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Block/block.mv1");
	CharacterBase::Block_Anim_Init(BLOCK_ANIM_MAX, 1);
}

//---------------------------------------------------------------------------
// 更新処理
//---------------------------------------------------------------------------
void Player::Update(Vector3* camera_rot, bool status_flag)
{

	before_mov = m_pos; // 移動される前に入れ替えとく
	action_flag = false; // アクションフラグを下す
	// アクションモードの判断してそれに合った操作をするようにする
	switch (action_mode)
	{
	case NORMAL_ACTION:        // 普通アクション 
		m_check_move = false;  // 常にリセット

		// 移動処理
		CharacterBase::Move_Player(&m_check_move, camera_rot, &m_rot, &MOVE_SPEED);

		// 移動中ならアニメーションの変更と当たり判定の移動
		if (m_check_move) {
			anim_num = ANIM_RUN;  // 移動中なので走るアニメーションに
			{                     // プレイヤー座標に当たり判定用のカプセルの位置を合わせる
				m_hit_body_pos_top = m_pos;
				m_hit_body_pos_top.y += 17.0f; // 高さを出す
				m_hit_body_pos_under = m_pos;
				m_hit_body_pos_under.y += 3.0f;
			}
		}
		else {                           // どの移動キーも押されてなかったら
			anim_num = ANIM_IDLE;        // アイドル状態にする
			{                            // プレイヤー座標に当たり判定用のカプセルの位置を合わせる
				m_hit_body_pos_top = m_pos;
				m_hit_body_pos_top.y += 17.0f; // 高さを出す
				m_hit_body_pos_under = m_pos;
				m_hit_body_pos_under.y += 3.0f;
			}
		}

		Attack_PressButton_Update(camera_rot); // アクションに関するボタン押し用の関数（見やすくするための関数）
		if (action_flag) { // アクションフラグが上がっていたら
			break;         // 後の処理を飛ばす
		}


		//=================================
		// ダメージのを食らったら
		//=================================
		if (damage_flag) {
			action_mode = DAMAGE_ACTION;           // モデルのアクションをダメージに変更
			damage_anim_pick = DAMAGE_ANIM;        // ダメージアクションを設定
			CharacterBase::Damage_Action(1); // 行いたいダメージアニメーションをセット
			break;
		}

		// アニメーション用のフレームカウントを進める
		for (int i = 0; i < ANIM_MAX; ++i) {
			anim_frame[i] += 1.0f;
			if (anim_frame[i] >= anim_total[i]) {
				anim_frame[i] = 0.0f;
			}
			// アニメーションの再生
			// 使いたくないアニメーション
			if (i != anim_num) {

				anim_rate[i] -= 0.1f; // 割合を減らす
			}
			else {// 使いたいアニメーション		
				anim_rate[i] += 0.1f; // 割合を増やす
			}

			anim_rate[i] = max(0.0f, min(anim_rate[i], 1.0f));                                    // 割合を0.0f ～ 1.0fにする（これをしないと踊り狂う） 
			MV1SetAttachAnimTime(m_model, anim_attach[i], anim_frame[i]);  // そのフレームのアニメーションにする
			MV1SetAttachAnimBlendRate(m_model, anim_attach[i], anim_rate[i]);   // それぞれにアニメーションの割合分再生します
		}
		break;
	case ATTACK_ACTION: // 攻撃アクション

		// アニメーションの再生
		// 攻撃アニメーション用のフレームカウントを進める
		attack_anim_frame[attack_anim_pick]++;
		if (attack_anim_frame[attack_anim_pick] >= attack_anim_total[attack_anim_pick]) { // アニメーションが一周したら
			attack_anim_frame[attack_anim_pick] = 0.0f;
			attack_anim_attach[attack_anim_pick] = MV1DetachAnim(m_model, attack_anim_attach[attack_anim_pick]);  // 攻撃アニメーションをディタッチしておく
			anim_attach[anim_num] = MV1AttachAnim(m_model, 1, anim_model[anim_num]);                   // モデルに元のアニメーションをアタッチしなおす（直近のアニメーション）
			action_mode = NORMAL_ACTION; 	// アニメーションが１ループしたかrATTACK_ACTIONから出る
			attack_flag = false; // 攻撃が終わったのでこうげきしていないようにする
			attack_anim_pick = ATTACK_ANIM_MAX; // 攻撃アニメーションが終わったのでアニメーションが設定されていない値にしておく
		}
		MV1SetAttachAnimTime(m_model, attack_anim_attach[attack_anim_pick], attack_anim_frame[attack_anim_pick]); // アニメーションの再生

		if (attack_flag) { // 攻撃フラグが上がっていたら
			Attack_Update();  // 攻撃用のアップデート
		}
		break;

	case BLOCK_ACTION:

		// アニメーションの再生
		// ガードアニメーション用のフレームカウントを進める
		block_anim_frame[block_anim_pick]++;
		if (block_anim_frame[block_anim_pick] >= block_anim_total[block_anim_pick]) { // アニメーションが一周したら
			block_anim_frame[block_anim_pick] = 0.0f;
			block_anim_attach[block_anim_pick] = MV1DetachAnim(m_model, block_anim_attach[block_anim_pick]);  // 攻撃アニメーションをディタッチしておく
			anim_attach[anim_num] = MV1AttachAnim(m_model, 1, anim_model[anim_num]);                   // モデルに元のアニメーションをアタッチしなおす（直近のアニメーション）
			action_mode = NORMAL_ACTION; 	// アニメーションが１ループしたかrATTACK_ACTIONから出る
			block_flag = false;
			block_anim_pick = BLOCK_ANIM_MAX; // 攻撃アニメーションが終わったのでアニメーションが設定されていない値にしておく
		}
		MV1SetAttachAnimTime(m_model, block_anim_attach[block_anim_pick], block_anim_frame[block_anim_pick]); // アニメーションの再生
		if (block_flag) {  // ガードフラグが上がったら
			Block_Update();   // ガード用のアップデート
		}
		break;

	case DAMAGE_ACTION:

		damage_anim_frame[damage_anim_pick]++;
		if (damage_anim_frame[damage_anim_pick] >= damage_anim_total[damage_anim_pick]) { // アニメーションが一周したら
			damage_anim_frame[damage_anim_pick] = 0.0f;
			damage_anim_frame[damage_anim_pick] = MV1DetachAnim(m_model, damage_anim_attach[damage_anim_pick]);  // 攻撃アニメーションをディタッチしておく
			anim_attach[anim_num] = MV1AttachAnim(m_model, 1, anim_model[anim_num]);                   // モデルに元のアニメーションをアタッチしなおす（直近のアニメーション）
			action_mode = NORMAL_ACTION; 	// アニメーションが１ループしたからダメージアニメーションから出る
			damage_flag = false;         // ダメージアニメーションフラグを下す
			damage_anim_pick = DAMAGE_ANIM_MAX; // 攻撃アニメーションが終わったのでアニメーションが設定されていない値にしておく
		}
		MV1SetAttachAnimTime(m_model, damage_anim_attach[damage_anim_pick], damage_anim_frame[damage_anim_pick]);
		if (damage_flag) { // ダメージを食らったフラグが上がっていたら
			Damage_Update();  // ダメージ用のアップデート
		}

		break;
	}

	// ステータスの更新のフラグが上がっていたら
	if (status_flag) {
		// ステータスの更新処理
		CharacterBase::Update_Status();
	}
}

//---------------------------------------------------------------------------
// 描画処理
//---------------------------------------------------------------------------
void Player::Draw()
{
	// 玉を描画する(今だけ)
	if (!bead_hit_flag) {
		DrawSphere3D(bead_pos.VGet(), bead_r, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	}
	// プレイヤー自身の当たり判定
	DrawCapsule3D(m_hit_body_pos_top.VGet(), m_hit_body_pos_under.VGet(), m_hit_body_r, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);

	// 当たり判定を見えるようにする物
	// 向いている方向に座標を設定（今はパンチに位置）
	//hit_areas[ATTACK_LONG_NORMAL_ANIM].hit_top = Vector3();
	if (cd_hit_flag && attack_flag) {
		DrawCapsule3D(m_hit_cd_pos_top.VGet(), m_hit_cd_pos_under.VGet(), m_hit_cd_r, 8, GetColor(0, 255, 0), GetColor(255, 0, 0), FALSE);
	}
	if (cd_hit_flag && block_flag) {
		DrawCapsule3D(m_block_top.VGet(), m_block_under.VGet(), m_block_r, 8, GetColor(0, 255, 0), GetColor(255, 0, 0), FALSE);
	}
	// プレイヤーの描画設定
	MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z)); // 描画するプレイヤーモデルの座標の設定
	MV1SetRotationXYZ(m_model, VGet(TO_RADIAN(m_rot.x), TO_RADIAN(m_rot.y + 180), TO_RADIAN(m_rot.z))); // モデルの回転
	MV1SetScale(m_model, VGet(0.1f, 0.1f, 0.1f)); // モデルの大きさ(10分の１のサイズ)
	MV1DrawModel(m_model); // モデルの描画
}

//---------------------------------------------------------------------------
// 終了処理
//---------------------------------------------------------------------------
void Player::Exit()
{
	MV1DeleteModel(m_model);       // モデルの削除
	for (int i = 0; i < ANIM_MAX; i++) {  // アニメーションの削除
		MV1DeleteModel(anim_model[i]);
	}

	// 攻撃アニメーションの削除
	for (int i = 0; i < ATTACK_ANIM_MAX; i++) {
		MV1DeleteModel(attack_anim_model[i]);
	}

	// 攻撃用あたり判定が解放されていなかったら
	if (!now_hit_area) {
		now_hit_area = nullptr;
	}
	// baseでnewした変数たちのdelete
	CharacterBase::Delete();
}

//---------------------------------------------------------------------------
// プレイヤーの移動用当たり判定（壁擦り）
//---------------------------------------------------------------------------
void Player::Move_Hit_Update()
{
	CharacterBase::Move_Hit(&before_mov, &m_move_hit_box_size, &m_hit_other_pos, &m_hit_other_size);
}

//---------------------------------------------------------------------------
// アクションに関するボタン押し用の関数（見やすくするための関数）
//---------------------------------------------------------------------------
void Player::Attack_PressButton_Update(Vector3* camera_rot)
{
	//=================================
	// 近距離攻撃
	//=================================
	// マウスの左クリックまたはAボタンで近距離攻撃
	if (PushMouseInput(MOUSE_INPUT_LEFT) || IsPadOn(PAD_ID::PAD_A, pad_no) ){
		action_mode = ATTACK_ACTION;                    // モデルのアクションを攻撃に変更
		attack_anim_pick = ATTACK_SHORT_NORMAL_1_ANIM;  // 近距離攻撃アクションを設定
		CharacterBase::Attack_Action(1);          // 行いたい攻撃アニメーションをセット	
		action_flag = true;                             // アクションフラグを上げる
	}

	//=================================
	// 遠距離攻撃
	//=================================
	// マウスの右クリック、または、Yボタンで遠距離攻撃
	if (PushMouseInput(MOUSE_INPUT_RIGHT) || IsPadOn(PAD_ID::PAD_Y, pad_no)) {
		action_mode = ATTACK_ACTION;                 // モデルのアクションを攻撃に変更
		attack_anim_pick = ATTACK_LONG_NORMAL_ANIM;  // 近距離攻撃アクションを設定
		bead_hit_flag = false;
		CharacterBase::Attack_Action(1);       // 行いたい攻撃アニメーションをセット	
		action_flag = true;                          // アクションフラグを上げる
	}

	//=================================
	// スライディング
	//=================================
	if (skill_flag) { // スキルが使用できるなら
		// スペースキークリック、または、Bボタンで遠距離攻撃
		if (PushHitKey(KEY_INPUT_SPACE) || IsPadOn(PAD_ID::PAD_B, pad_no)) {
			m_skill_count.x = 0; // スキルの使用なのでカウントをリセット
			action_mode = ATTACK_ACTION;           // モデルのアクションを攻撃に変更
			attack_anim_pick = ATTACK_SLIDE_ANIM;  // 近距離攻撃アクションを設定
			CharacterBase::Attack_Action(1);        // 行いたい攻撃アニメーションをセット
			CharacterBase::Move_Front(&m_check_move, camera_rot, &m_rot, &WARP);
			action_flag = true;                          // アクションフラグを上げる
			skill_flag = false;                          // skillを使用済みにしておく
		}
	}
	//=================================
	// 必殺技
	//=================================
	// 『 Eキー ＋ Qキー 』クリック、または、『 Rボタン + Lボタン 』で必殺技攻撃
	if (sp_flag) { // 必殺技が使用可能なら
		if (PushHitKey(KEY_INPUT_E) && PushHitKey(KEY_INPUT_Q) || IsPadOn(PAD_ID::PAD_L, pad_no) && IsPadOn(PAD_ID::PAD_R, pad_no)) {
			m_sp_count.x = 0; // SPの使用なのでカウントをリセット
			action_mode = ATTACK_ACTION;             // モデルのアクションを攻撃に変更
			attack_anim_pick = ATTACK_SPECIAL_ANIM;  // 必殺攻撃アクションを設定
			CharacterBase::Attack_Action(1);   // 行いたい攻撃アニメーションをセット
			action_flag = true;                      // アクションフラグを上げる
			sp_flag = false;                         // SPを使用済みにしておく
		}
	}

	//=================================
	// ガード
	//=================================
	// または、Xボタンで遠距離攻撃
	if (PushHitKey(KEY_INPUT_LSHIFT) || IsPadOn(PAD_ID::PAD_X, pad_no)) {
		action_mode = BLOCK_ACTION;           // モデルのアクションをガードに変更
		block_anim_pick = BLOCK_ANIM;         // ガードアクションを設定
		CharacterBase::Block_Action(1); // 行いたい攻撃アニメーションをセット
		action_flag = true;                   // アクションフラグを上げる
	}

}

//---------------------------------------------------------------------------
// 攻撃用アップデート
//---------------------------------------------------------------------------
void Player::Attack_Update()
{
	switch (attack_anim_pick)
	{
	case ATTACK_LONG_NORMAL_ANIM: // 遠距離攻撃（弾を出す）
		// カウントがからだったら

		if (lifespan_count == NULL) {
			lifespan_count = 120.0f; // カウントのセット
		}
		// 弾用の変数
		if (lifespan_count >= 120.0f) {

			bead_pos = m_pos; // 一旦プレイヤーの位置にしておく（本来プレイヤーの手の位置に合わせる）
			bead_pos.y += 10.0f; // y座標をずらして空中に浮かべる
			bead_r = 2.0f;        // 半径の設定
		}
		// 一旦前に飛ばす
		bead_pos.x += 3 * sinf(TO_RADIAN(m_rot.y));
		bead_pos.z += 3 * cosf(TO_RADIAN(m_rot.y));
		lifespan_count--; // 弾が消えるまでのカウントを進める

		now_hit_area = &hit_areas[THROW_ATTACK_1_HIT];
		if (attack_anim_frame[THROW_ATTACK_1_HIT] == now_hit_area->hit_anim_frame) {
			cd_hit_flag = true; //< 当たり判定を行っていい用にフラグを立てる

			// 当たり判定を見えるようにする物
			// 向いている方向に座標を設定（今はパンチに位置）
			m_hit_cd_pos_top.set(bead_pos);
			m_hit_cd_pos_under.set(bead_pos);
			m_hit_cd_r = now_hit_area->hit_r;
		}

		// カウントが一定にまで減るか、当たり判定があったら
		if (lifespan_count <= 0 || bead_hit_flag) {
			lifespan_count = NULL;  // 次のために空にしておく
			bead_hit_flag = true;   // 弾が何かに当たったか消えたので判定をリセット
			attack_flag = false;    // 攻撃を終わらせておく
			cd_hit_flag = false;    //< 当たり判定をしてほしくないのでフラグを下す
		}
		break;

	case ATTACK_SHORT_NORMAL_1_ANIM: // 近距離普通攻撃１ (当たり判定の作成)
		now_hit_area = &hit_areas[ATTACK_SHORT_NORMAL_1_HIT];
		if (attack_anim_frame[ATTACK_SHORT_NORMAL_1_ANIM] == now_hit_area->hit_anim_frame) {
			cd_hit_flag = true; //< 当たり判定を行っていい用にフラグを立てる

			// 当たり判定を見えるようにする物
			// 向いている方向に座標を設定（今はパンチに位置）
			m_hit_cd_pos_top.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * now_hit_area->hit_top.x, m_pos.y + now_hit_area->hit_top.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * now_hit_area->hit_top.z);
			m_hit_cd_pos_under.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * now_hit_area->hit_under.x, m_pos.y + now_hit_area->hit_under.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * now_hit_area->hit_under.z);
			m_hit_cd_r = now_hit_area->hit_r;
		}
		else {
			cd_hit_flag = false; //< 当たり判定をしてほしくないのでフラグを下す
		}
		break;


	case ATTACK_SLIDE_ANIM: // スライディング（当たり判定の作成）
		now_hit_area = &hit_areas[ATTACK_SLIDE_ANIM]; // 構造体を触りやすくするために違う変数に入れておく
		cd_hit_flag = true; //< 当たり判定を行っていい用にフラグを立てる

		// 当たり判定を見えるようにする物
		// 向いている方向に座標を設定（今はパンチに位置）
		if (attack_anim_frame[ATTACK_SLIDE_ANIM] == now_hit_area->hit_anim_frame) {
			m_hit_cd_pos_top.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * now_hit_area->hit_top.x, m_pos.y + now_hit_area->hit_top.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * now_hit_area->hit_top.z);
			m_hit_cd_pos_under.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * now_hit_area->hit_under.x, m_pos.y + now_hit_area->hit_under.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * now_hit_area->hit_under.z);
		}
		else {
			cd_hit_flag = false; //< 当たり判定をしてほしくないのでフラグを下す
		}
		break;
	case ATTACK_SPECIAL_ANIM: // 必殺技 (弾を出す)
		// カウントがからだったら
		if (lifespan_count == NULL) {
			lifespan_count = 240.0f; // カウントのセット
		}
		// 弾用の変数
		if (lifespan_count >= 240.0f) {

			bead_pos = m_pos; // 一旦プレイヤーの位置にしておく（本来プレイヤーの手の位置に合わせる）

			// 座標の設定
			bead_pos.set(m_pos.x + 300 * sinf(TO_RADIAN(m_rot.y)), m_pos.y + 300, m_pos.z + 300 * cosf(TO_RADIAN(m_rot.y)));
			bead_r = 100.0f;        // 半径の設定
		}
		bead_pos.y--;
		lifespan_count--; // 弾が消えるまでのカウントを進める
		// カウントが一定にまで減るか、当たり判定があったら
		if (lifespan_count <= 0 || bead_hit_flag) {
			lifespan_count = NULL;  // 次のために空にしておく
			bead_hit_flag = true;  // 弾が何かに当たったか消えたので判定をリセット
			attack_flag = false;    // 攻撃を終わらせておく
			cd_hit_flag = false;    //< 当たり判定をしてほしくないのでフラグを下す
		}
	}
}

//---------------------------------------------------------------------------
// ダメージを食らった時用の関数
//---------------------------------------------------------------------------
void Player::Damage_Update()
{
}

//---------------------------------------------------------------------------
// 
// ガードをした時用の関数
//---------------------------------------------------------------------------
void Player::Block_Update()
{
	switch (block_anim_pick)
	{
	case BLOCK_ANIM:
		now_hit_area = &hit_areas[BLOCK_HIT];
		if (attack_anim_frame[BLOCK_HIT] <= now_hit_area->hit_anim_frame) {
			cd_hit_flag = true; //< 当たり判定を行っていい用にフラグを立てる

			// 当たり判定を見えるようにする物
			// 向いている方向に座標を設定（今はパンチに位置）
			m_block_top.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * now_hit_area->hit_top.x, m_pos.y + now_hit_area->hit_top.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * now_hit_area->hit_top.z);
			m_block_under.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * now_hit_area->hit_under.x, m_pos.y + now_hit_area->hit_under.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * now_hit_area->hit_under.z);
			m_block_r = now_hit_area->hit_r;
		}
		else {
			cd_hit_flag = false; //< 当たり判定をしてほしくないのでフラグを下す
		}

		break;
	}
}