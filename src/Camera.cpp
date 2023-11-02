#include "WinMain.h"
#include "GameMain.h"
#include "Camera.h"

// プレイヤーからカメラまでの距離
#define CAMERA_LENGTH 40.0f
// カメラの回転スピード
#define MOUSE_CAMERA_ROT_SPEED	0.2f // マウス用
#define PAD_CAMERA_ROT_SPEED 3.0f    // パッド用
// カメラの上アングルの最大
const float UP_ANGLE_MAX = 30.0f;
// カメラの下アングルの最低（地面に埋まらない程度）
const float LOWER_ANGLE = -10.0f;

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
//	描画処理
//---------------------------------------------------------------------------------
void Camera::Draw()
{
	// 座標と向きを渡してカメラの設定
	// SetCameraPositionAndAngle(m_pos.VGet(), m_rot.x, m_rot.y, m_rot.z);

	// カメラ座標と見る座標を渡してカメラの設定
	SetCameraPositionAndTarget_UpVecY(m_pos.VGet(), m_look.VGet());

}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Camera::Exit()
{
}
