#include "WinMain.h"
#include "GameMain.h"
#include "Player.h"



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
	m_hit_attack_pos_top.set(m_pos.x + 8 * sinf(TO_RADIAN(m_rot.y)), m_pos.y + 13, m_pos.z + 8 * cosf(TO_RADIAN(m_rot.y)));
	m_hit_attack_pos_under.set(m_pos.x + 8 * sinf(TO_RADIAN(m_rot.y)), m_pos.y + 12.7, m_pos.z + 6 * cosf(TO_RADIAN(m_rot.y)));
	m_hit_attack_r = 1.0f;
	//======================
	// 移動用のボックス                                                   
	m_move_hit_box_size.set(PANEL_HALF - 0.1, PANEL_HALF - 0.1, PANEL_HALF - 0.1);    // パネルの大きさ

	// 判断用、フラグ変数
	m_move_judge = false;                              // 最初は動いてはいけない
	m_attack_judge = false;                            // 攻撃していない
	bead_hit_judg = false;                            // なににもあたってない

	m_hp_pos.set(10, 32);         // HPバーの描画位置初期化
	m_hp_count.set(HP_MAX, 32 + 30);   // HPの計算用の初期化
}

//---------------------------------------------------------------------------
// 初期処理
//---------------------------------------------------------------------------
void Player::Init(int player_num)
{
	m_model = MV1LoadModel("Data/Model/Player/Player.mv1");   // プレイヤーモデルの読み込み
	// 普通アニメーションの初期化
	// アニメーションの読み込み
	CharacterBase::Nomal_Anim_New(ANIM_MAX);  // 普通アニメーションに必要な変数の配列を作る
	anim_model[ANIM_IDLE] = MV1LoadModel("Data/Model/Player/Animation/Player_Idle.mv1"); // アイドル
	anim_model[ANIM_RUN] = MV1LoadModel("Data/Model/Player/Animation/Player_Run.mv1");   // 走る
	CharacterBase::Nomal_Anim_Init(ANIM_IDLE, ANIM_MAX, 1); // 普通アニメーションの初期設定

	// 攻撃アニメーションの初期化
	// アニメーションの読み込み
	CharacterBase::Attack_Anim_New(ATTACK_ANIM_MAX); // 攻撃アニメーションに必要な変数の配列を作る
	attack_anim_model[ATTACK_LONG_NORMAL_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/long_normal_attack.mv1");       // 遠距離普通攻撃
	attack_anim_model[ATTACK_SHORT_NORMAL_1_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/Punch.mv1");                 // 近距離攻撃１
	attack_anim_model[ATTACK_SHORT_NORMAL_2_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/short_normal_attack_2.mv1"); // 近距離攻撃２
	attack_anim_model[ATTACK_SLIDE_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/slide.mv1");                          // スライディング
	attack_anim_model[ATTACK_SPECIAL_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/special_attack.mv1");               // 必殺技
	CharacterBase::Attack_Anim_Init(ATTACK_ANIM_MAX, 1); // 攻撃アニメーションの初期設定

	// pad_input = GetJoypadInputState(DX_INPUT_PAD3);  // ゲームパッドの読み込み

	if (player_num == 0) {
		m_pos.set(0.0f, 0.0f, -50.0f);           // 初期座標の設定
		m_rot.set(0.0f, 0.0f, 0.0f);             // 向きの設定
	}
	else {
		m_pos.set(0.0f, 0.0f, 500.0f);            // 初期座標の設定
		m_rot.set(0.0f, 180.0f, 0.0f);			  // 向きの設定
	}
}

//---------------------------------------------------------------------------
// 更新処理
//---------------------------------------------------------------------------
void Player::Update(Vector3* camera_rot)
{
	before_mov = m_pos; // 移動される前に入れ替えとく

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

		//=================================
		// 近距離攻撃
		//=================================
		// マウスの左クリックまたはAボタンで近距離攻撃
		if (PushMouseInput(MOUSE_INPUT_LEFT) || GetJoypadInputState(pad_no) & PAD_INPUT_1) {
			action_mode = ATTACK_ACTION;                    // モデルのアクションを攻撃に変更
			attack_anim_pick = ATTACK_SHORT_NORMAL_1_ANIM;  // 近距離攻撃アクションを設定
			CharacterBase::Attack_Action(1);                 // 行いたい攻撃アニメーションをセット

			break;
		}

		//=================================
		// 遠距離攻撃
		//=================================
		// マウスの右クリック、または、Yボタンで遠距離攻撃
		if (PushMouseInput(MOUSE_INPUT_RIGHT) || GetJoypadInputState(pad_no) & PAD_INPUT_4) {
			action_mode = ATTACK_ACTION;                 // モデルのアクションを攻撃に変更
			attack_anim_pick = ATTACK_LONG_NORMAL_ANIM;  // 近距離攻撃アクションを設定
			CharacterBase::Attack_Action(1);              // 行いたい攻撃アニメーションをセット
			break;
		}

		//=================================
		// スライディング
		//=================================
		// スペースキークリック、または、Bボタンで遠距離攻撃
		if (PushHitKey(KEY_INPUT_SPACE) || GetJoypadInputState(pad_no) & PAD_INPUT_2) {
			action_mode = ATTACK_ACTION;           // モデルのアクションを攻撃に変更
			attack_anim_pick = ATTACK_SLIDE_ANIM;  // 近距離攻撃アクションを設定
			CharacterBase::Attack_Action(1);        // 行いたい攻撃アニメーションをセット
			break;
		}

		//=================================
		// 必殺技
		//=================================
		// 『 Eキー ＋ Qキー 』クリック、または、『 Rボタン + Lボタン 』で必殺技攻撃
		if (PushHitKey(KEY_INPUT_E) && PushHitKey(KEY_INPUT_Q) || GetJoypadInputState(pad_no) & PAD_INPUT_6 && GetJoypadInputState(pad_no) & PAD_INPUT_5) {
			action_mode = ATTACK_ACTION;             // モデルのアクションを攻撃に変更
			attack_anim_pick = ATTACK_SPECIAL_ANIM;  // 近距離攻撃アクションを設定
			CharacterBase::Attack_Action(1);   // 行いたい攻撃アニメーションをセット
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
			// 攻撃が終わったのでこうげきしていないようにする
			//m_attack_judge = false;
			attack_anim_pick = ATTACK_ANIM_MAX; // 攻撃アニメーションが終わったのでアニメーションが設定されていない値にしておく
		}
		MV1SetAttachAnimTime(m_model, attack_anim_attach[attack_anim_pick], attack_anim_frame[attack_anim_pick]); // アニメーションの再生
		break;
	}


	switch (attack_anim_pick)
	{
	case ATTACK_LONG_NORMAL_ANIM: // 遠距離攻撃（弾を出す）
		// カウントがからだったら
		if (lifespan_count == NULL) {
			lifespan_count = 120.0f; // カウントのセット
		}
		// 弾用の変数
		if (lifespan_count >= 120.0f) {
			bead_pos = new Vector3;
			*bead_pos = m_pos; // 一旦プレイヤーの位置にしておく（本来プレイヤーの手の位置に合わせる）
			bead_pos->y += 10.0f; // y座標をずらして空中に浮かべる
			bead_r = 2.0f;        // 半径の設定
		}
		// 一旦前に飛ばす
		bead_pos->x += 3 * sinf(TO_RADIAN(m_rot.y));
		bead_pos->z += 3 * cosf(TO_RADIAN(m_rot.y));
		lifespan_count--; // 弾が消えるまでのカウントを進める
		// カウントが一定にまで減るか、当たり判定があったら
		if (lifespan_count <= 0 || bead_hit_judg) {
			delete bead_pos; // 弾の解放
			bead_pos = NULL;
			lifespan_count = NULL; // 次のために空にしておく
			m_attack_judge = false; // 攻撃を終わらせておく
		}
		break;

	case ATTACK_SHORT_NORMAL_1_ANIM: // 近距離普通攻撃１ (当たり判定の作成)
		if (m_attack_judge) { // 攻撃フラグが上がっていたら
			now_hit_area = hit_areas[ATTACK_SHORT_NORMAL_1_ANIM];
			if (attack_anim_frame[ATTACK_SHORT_NORMAL_1_ANIM] == now_hit_area.fit_anim_frame) {
				// 当たり判定を見えるようにする物
				// 向いている方向に座標を設定（今はパンチに位置）
				m_hit_attack_pos_top.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * now_hit_area.hit_top.x, m_pos.y + now_hit_area.hit_top.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * now_hit_area.hit_top.z);
				m_hit_attack_pos_under.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * now_hit_area.hit_under.x, m_pos.y + now_hit_area.hit_under.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * now_hit_area.hit_under.z);
			}
			else {
				/*if (now_hit_area != NULL) {
					now_hit_area = NULL;
				}*/
			}
		}
		break;

	case ATTACK_SLIDE_ANIM: // スライディング（当たり判定の作成）
		if (m_attack_judge) { // 攻撃フラグが上がっていたら
			now_hit_area = hit_areas[ATTACK_SLIDE_ANIM]; // 構造体を触りやすくするために違う変数に入れておく
			// 当たり判定を見えるようにする物
			// 向いている方向に座標を設定（今はパンチに位置）
			if (attack_anim_frame[ATTACK_SLIDE_ANIM] == now_hit_area.fit_anim_frame) {
				m_hit_attack_pos_top.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * now_hit_area.hit_top.x, m_pos.y + now_hit_area.hit_top.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * now_hit_area.hit_top.z);
				m_hit_attack_pos_under.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * now_hit_area.hit_under.x, m_pos.y + now_hit_area.hit_under.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * now_hit_area.hit_under.z);
			}
		}
		break;
	case ATTACK_SPECIAL_ANIM: // 必殺技 (弾を出す)
		// カウントがからだったら
		if (lifespan_count == NULL) {
			lifespan_count = 240.0f; // カウントのセット
		}
		// 弾用の変数
		if (lifespan_count >= 240.0f) {
			bead_pos = new Vector3;
			*bead_pos = m_pos; // 一旦プレイヤーの位置にしておく（本来プレイヤーの手の位置に合わせる）

			// 座標の設定
			bead_pos->set(m_pos.x + 300 * sinf(TO_RADIAN(m_rot.y)), m_pos.y + 300, m_pos.z + 300 * cosf(TO_RADIAN(m_rot.y)));
			bead_r = 100.0f;        // 半径の設定
		}
		bead_pos->y--;
		lifespan_count--; // 弾が消えるまでのカウントを進める
		// カウントが一定にまで減るか、当たり判定があったら
		if (lifespan_count <= 0 || bead_hit_judg) {
			delete bead_pos; // 弾の解放
			bead_pos = NULL;
			lifespan_count = NULL; // 次のために空にしておく
			m_attack_judge = false; // 攻撃を終わらせておく
		}
	}


	// ステータスの更新処理
	CharacterBase::Update_Status();
}

//---------------------------------------------------------------------------
// プレイヤーの移動用当たり判定（壁擦り）
//---------------------------------------------------------------------------
void Player::Move_Hit_Update()
{
	CharacterBase::Move_Hit(&before_mov, &m_move_hit_box_size, &m_hit_other_pos, &m_hit_other_size);
}

//---------------------------------------------------------------------------
// ステータス描画処理
//---------------------------------------------------------------------------
// CharacterBase::Draw_Status(); //ステータス描画処理

//---------------------------------------------------------------------------
// 描画処理
//---------------------------------------------------------------------------
void Player::Draw()
{
	// 玉を描画する(今だけ)
	if (bead_pos != NULL) {
		DrawSphere3D(bead_pos->VGet(), bead_r, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	}
	// プレイヤー自身の当たり判定
	DrawCapsule3D(m_hit_body_pos_top.VGet(), m_hit_body_pos_under.VGet(), m_hit_body_r, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);

	// 当たり判定を見えるようにする物
	// 向いている方向に座標を設定（今はパンチに位置）
	//hit_areas[ATTACK_LONG_NORMAL_ANIM].hit_top = Vector3();
	DrawCapsule3D(m_hit_attack_pos_top.VGet(), m_hit_attack_pos_under.VGet(), m_hit_attack_r, 8, GetColor(0, 255, 0), GetColor(255, 0, 0), FALSE);


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

	// 弾が解放されていなかったら解放する
	if (bead_pos != NULL) {
		delete bead_pos;
	}

	// アニメーション用変数たちのdelete
	CharacterBase::Anim_Delete(ANIM_MAX, ATTACK_ANIM_MAX);
}