#include "WinMain.h"
#include "GameMain.h"
#include "Camera.h"


constexpr float CAMERA_LENGTH = 40.0f;          // プレイヤーからカメラまでの距離
// カメラの回転スピード
constexpr float MOUSE_CAMERA_ROT_SPEED = 0.2f;  // マウス用
constexpr float PAD_CAMERA_ROT_SPEED = 3.0f;    // パッド用
constexpr float UP_ANGLE_MAX = 30.0f;           // カメラの上アングルの最大
constexpr float LOWER_ANGLE = -10.0f;           // カメラの下アングルの最低（地面に埋まらない程度）



// コンストラクタ(初期化)
Camera::Camera()
{
	// カメラ座標の初期設定
	m_pos.set(0.0f, 0.0f, -20.0f);
	// カメラの向きは全部０度で開始
	m_rot.set(0.0f, 0.0f, 0.0f);
	// カメラが見る座標
	m_look.set(0.0f, 0.0f, 0.0f); // すべて０．０ｆで初期化

	// マウスの移動量の初期化最小は0.0fから
	m_mouse_move_x = 0.0f;
	m_mouse_move_y = 0.0f;
}

// 初期処理
void Camera::Init()
{



}

//---------------------------------------------------------------------------------
//	// プレイ画面の初期設定
//---------------------------------------------------------------------------------
void Camera::PlayField_Init()
{
	
		m_field_size.set(SCREEN_W / 2, SCREEN_H);                                                                     // 描画する画面のサイズの設定
		m_screen_field = MakeScreen(m_field_size.x, m_field_size.y);                                    // 描画画面を書き込むための初期設定
		SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 2.0f, -5.0f), VGet(0.0f, 0.0f, 1.0f));  // カメラの設定
	
}

//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Camera::Update(Vector3* player_pos)
{
	// プレイヤーの後ろに付いて動く
	m_look.set(player_pos->x, player_pos->y + 10.0f, player_pos->z);
	// マウスの移動量
	m_mouse_move_x = GetMouseMoveX();
	m_mouse_move_y = GetMouseMoveY();

	// カメラの向きを変える
	// （２Dのマウスの移動量をそのまま角度に渡すと大きいので少し小さくしています）
	m_rot.x += m_mouse_move_y * MOUSE_CAMERA_ROT_SPEED;
	m_rot.y += m_mouse_move_x * MOUSE_CAMERA_ROT_SPEED;

	// カメラが地面に埋まらないようにしている
	if (m_rot.x <= LOWER_ANGLE) {
		m_rot.x = LOWER_ANGLE;
	}

	// カメラが真上にいかないようにしている
	if (m_rot.x >= UP_ANGLE_MAX) {
		m_rot.x = UP_ANGLE_MAX;
	}

	//	ゲームパッドの右スティックの値を使って向き変数（ m_rot ）の値を変更
	// 左ステックでプレイヤーの向きや座標の更新
	// ゲームパッドの情報を取得（XINPUT の情報）
	XINPUT_STATE input;
	// ゲームパッドの情報を丸ごと取得
	GetJoypadXInputState(DX_INPUT_PAD1, &input);
	// 移動用ベクトル用変数
	Vector3 rot;
	// 左スティックの値を設定
	rot.y = input.ThumbRX;
	rot.x = input.ThumbRY;
	// -32768 ～ 32767 を-1.0f　～　1.0fにします
	rot /= 32768.0f;
	// この移動用ベクトルの大きさがある程度大きい時だけ移動させようと思います
	if (rot.GetLength() > 0.5f) {
		m_rot += rot * PAD_CAMERA_ROT_SPEED;  // その移動ベクトル分座標移動
	}

	// まずは回転前のベクトルを用意します
	// カメラが見るプレイヤー方向のベクトルを作成します
	VECTOR base_dir = VGet(0.0f, 0.0f, -CAMERA_LENGTH);

	// 行列を用意します
	// X軸回転行列
	MATRIX mat_x = MGetRotX(TO_RADIAN(m_rot.x));
	// Y軸回転行列
	MATRIX mat_y = MGetRotY(TO_RADIAN(m_rot.y));

	// X軸回転とY軸回転をさせたいので２つの行列を１個にまとめます
	MATRIX mat = MMult(mat_x, mat_y);
	// 元のベクトルをＸ軸回転とＹ軸回転させます
	// 簡単に言ったら一定の距離の棒を作っている
	VECTOR change_dir = VTransform(base_dir, mat);

	// カメラの位置を見ている座標から一定の位置に再設定
	m_pos = m_look + change_dir;
}

//---------------------------------------------------------------------------------
//	描画前のカメラのセット
//---------------------------------------------------------------------------------
void Camera::Draw_Set()
{
	// ２：今から描画するもの場所をテクスチャに変更します（レンダーターゲットの切り替え）
	SetDrawScreen(m_screen_field);
	// ２－１：その書き込む領域をクリアする
	ClearDrawScreen();
	//	カメラの設定
	SetCameraNearFar(0.1f, 3000.0f);
	SetupCamera_Perspective(TO_RADIAN(45.0f));
	// カメラ座標と見る座標を渡してカメラの設定
	SetCameraPositionAndTarget_UpVecY(m_pos.VGet(), m_look.VGet());
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Camera::Draw(int camera_No)
{
	// ４：描画先をいつもの場所にする
	SetDrawScreen(DX_SCREEN_BACK);

	// PLAYER１か２によってカメラの描画位置が変わる

	// プレイヤー１の場合
	if (camera_No == 0) {
		// ３Dが描画された画像を描画
		DrawGraphF(m_field_pos.x, m_field_pos.y, m_screen_field, TRUE);
		// どっちの画面が移っているのかがわかるように
		DrawString(16, 16, "PLAYER 1", GetColor(255, 255, 255));
		// 画像がわかりやすいように
		DrawLineBox(m_field_pos.x, m_field_pos.y, m_field_pos.x + m_field_size.x, m_field_pos.y + m_field_size.y, GetColor(255, 255, 255));

	}
	// プレイヤー２の場合
	else {
		// ３Dが描画された画像を描画
		DrawGraphF(m_field_pos.x + m_field_size.x, m_field_pos.y, m_screen_field, TRUE);
		// どっちの画面が移っているのかがわかるように
		DrawString(SCREEN_W / 2+ 16, 16, "PLAYER 2", GetColor(255, 255, 255));
		// 画像がわかりやすいように
		DrawLineBox(m_field_pos.x + m_field_size.x, m_field_pos.y, m_field_pos.x + m_field_size.x *2, m_field_pos.y + m_field_size.y, GetColor(0, 255, 255));
	}

}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Camera::Exit()
{
}
