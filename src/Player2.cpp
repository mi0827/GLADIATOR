#include "WinMain.h"
#include "GameMain.h"
#include "Player2.h"

// コンストラクタ（初期化）
Player2::Player2()
{
	m_pos.set(0.0f, 0.0f, 10.0f);            // 初期座標の設定
	m_rot.set(0.0f, 180.0f, 0.0f);			  // 向きの設定


	// アニメーションが何フレーム進んでいるか用の変数
	// 最初は０から開始
	for (int i = 0; i < ANIM_MAX; i++)
	{
		anim_frame[i] = 0.0f;
	}
	anim_num = 0;                                     // 最初は０ばんのアニメーションをする
	action_mode = 0;                                  // 最初は普通アニメーションモードにしておく
	attack_anim_pick = -1;                            // 最初はなんのアニメーションも入っていない
	m_check_move = false;                             // 最初は走っていいない

	// 当たり判定用変数
	m_hit_body_pos_top.clear();                       // カプセルの上側
	m_hit_body_pos_under.clear();                     // 下側
	m_hit_body_r = 2.0f;                              // 半径
	m_move_judge = false;                              // 最初は動いてはいけない
	m_attack_judge = false;                            // 攻撃していない
	bead_hit_judg = false;                            // なににもあたってない
}

// 初期処理
void Player2::Init()
{

	m_model = MV1LoadModel("Data/Model/Player/Player.mv1");   // プレイヤーモデルの読み込み
	// 普通アニメーションの初期化
	// アニメーションの読み込み
	anim_model[ANIM_IDLE] = MV1LoadModel("Data/Model/Player/Animation/Player_Idle.mv1"); // アイドル
	anim_model[ANIM_RUN] = MV1LoadModel("Data/Model/Player/Animation/Player_Run.mv1");   // 走る
	for (int i = 0; i < ANIM_MAX; i++)
	{

		anim_attach[i] = MV1AttachAnim(m_model, 1, anim_model[i]);             // モデルにアニメーションをアタッチ（つける）する
		anim_total[i] = MV1GetAttachAnimTotalTime(m_model, anim_attach[i]);               // 取得したアタッチ番号からそのアニメーションが何フレームかを取得
		// 不必要なものにはブレンド率を0.0fにしておく（最初はアイドルにしておく）
		if (i != ANIM_IDLE)  // アイドル以外のアニメーションをモデルから外す
		{
			anim_rate[i] = 0.0f;
		}
		else {
			anim_rate[i] = 1.0f;
		}
	}

	// 攻撃アニメーションの初期化
	// アニメーションの読み込み
	attack_anim_model[ATTACK_LONG_NORMAL_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/long_normal_attack.mv1"); // 遠距離普通攻撃
	for (int i = 0; i < ATTACK_ANIM_MAX; i++)
	{

		attack_anim_attach[i] = MV1AttachAnim(m_model, 1, attack_anim_model[i]);  // モデルにアニメーションをアタッチ（つける）する
		attack_anim_total[i] = MV1GetAttachAnimTotalTime(m_model, attack_anim_attach[i]);    // 取得したアタッチ番号からそのアニメーションが何フレームかを取得
		attack_anim_attach[i] = MV1DetachAnim(m_model, attack_anim_attach[i]);               // 最初は攻撃アニメーションはしないのでディタッチしておく（使いたいときにまたアタッチする）
	}
}

// 更新処理
void Player2::Update(Vector3* camera_rot)
{
	// アクションモードの判断してそれに合った操作をするようにする
	switch (action_mode)
	{
	case NORMAL_ACTION:        // 普通アクション 
		m_check_move = false;  // 常にリセット
		// WASDキーでプレイヤーの移動
		// 移動中はダッシュする
		if (CheckHitKey(KEY_INPUT_UP)) // 上移動
		{
			CharacterBase::Move_Front(&m_move_judge, &m_check_move, camera_rot, &m_rot, &DASH_SPEED);
		}
		if (CheckHitKey(KEY_INPUT_DOWN)) // 下移動
		{
			CharacterBase::Move_Dehind(&m_move_judge, &m_check_move, camera_rot, &m_rot, &DASH_SPEED);
		}
		if (CheckHitKey(KEY_INPUT_LEFT)) // 左移動
		{
			CharacterBase::Move_Left(&m_move_judge, &m_check_move, camera_rot, &m_rot, &DASH_SPEED);
		}
		if (CheckHitKey(KEY_INPUT_RIGHT)) // 右移動
		{
			CharacterBase::Move_Right(&m_move_judge, &m_check_move, camera_rot, &m_rot, &DASH_SPEED);
		}

		// 十字キーのどれかが押されていたら動いてもよい
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

		// マウスの左クリックで攻撃
		if (PushMouseInput(MOUSE_INPUT_LEFT)) {
			anim_attach[anim_num] = MV1DetachAnim(m_model, anim_attach[anim_num]);  // 攻撃アニメーションに入る前に普通アニメを外す（直近のアニメーション） 
			attack_anim_attach[ATTACK_LONG_NORMAL_ANIM] = MV1AttachAnim(m_model, 1, attack_anim_model[ATTACK_LONG_NORMAL_ANIM]);      	// 使いたいアニメーションをモデルにつけなおす
			action_mode = ATTACK_ACTION;                 // 攻撃アクションに変更
			attack_anim_pick = ATTACK_LONG_NORMAL_ANIM;  // 玉投げアクションに設定 
			m_attack_judge = true;                        // 攻撃が始まるので攻撃中にしておく
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
			// m_attack_judg = false;
		}
		MV1SetAttachAnimTime(m_model, attack_anim_attach[attack_anim_pick], attack_anim_frame[attack_anim_pick]); // アニメーションの再生
		break;
	}


	if (m_attack_judge) {

		// 弾用の変数
		if (lifespan_count >= 120.0f) {
			bead_pos = new Vector3;
			*bead_pos = m_pos; // 一旦プレイヤーの位置にしておく（本来プレイヤーの手の位置に合わせる）
			bead_pos->y += 10.0f; // y座標をずらして空中に浮かべる
		}
		// 一旦前に飛ばす
		bead_pos->x += 3 * sinf(TO_RADIAN(m_rot.y));
		bead_pos->z += 3 * cosf(TO_RADIAN(m_rot.y));
		lifespan_count--; // 弾が消えるまでのカウントを進める

		// カウントが一定にまで減るか、当たり判定があったら
		if (lifespan_count <= 0 || bead_hit_judg) {
			delete bead_pos; // 弾の解放
			lifespan_count = 120.0f; // カウントのリセット
			m_attack_judge = false; // 攻撃を終わらせておく
		}
	}

	/*if (m_attack_judg) {
		switch (attack_anim_pick)
		{
		case ATTACK_LONG_NORMAL_ANIM:

			break;
		}

	}*/
}

void Player2::Move_Hit_Update()
{
}


// 描画処理
void Player2::Draw()
{
	// 玉を描画する(今だけ)
	if (bead_pos != NULL) {
		DrawSphere3D(bead_pos->VGet(), 2.0f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	}
	DrawCapsule3D(m_hit_body_pos_top.VGet(), m_hit_body_pos_under.VGet(), m_hit_body_r, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);

	MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));                                                                // 描画するプレイヤーモデルの座標の設定
	MV1SetRotationXYZ(m_model, VGet(TO_RADIAN(m_rot.x), TO_RADIAN(m_rot.y + 180), TO_RADIAN(m_rot.z)));   // モデルの回転
	MV1SetScale(m_model, VGet(0.1f, 0.1f, 0.1f));                                                                     // モデルの大きさ(10分の１のサイズ)
	MV1DrawModel(m_model);
}


// 終了処理
void Player2::Exit()
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
}