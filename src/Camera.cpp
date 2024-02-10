#include "WinMain.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Base.h"
#include "Camera.h"


constexpr float CAMERA_LENGTH = 50.0f;          // プレイヤーからカメラまでの距離
// カメラの回転スピード
constexpr float MOUSE_CAMERA_ROT_SPEED = 0.2f;  // マウス用
constexpr float PAD_CAMERA_ROT_SPEED = 3.0f;    // パッド用
constexpr float UP_ANGLE_MAX = 30.0f;           // カメラの上アングルの最大
constexpr float LOWER_ANGLE = -5.0f;           // カメラの下アングルの最低（地面に埋まらない程度）
constexpr float BOX_SIZE = 4.0f;                   // ボックスのサイズ
constexpr float BOX_SIZE_HALF = (BOX_SIZE / 2.0f); // 半数のサイズ

//---------------------------------------
// コンストラクタ(初期化)
//---------------------------------------
Camera::Camera(int num)
{
	//! カメラ座標の初期設定
	m_pos.set(0.0f, 0.0f, -20.0f);
	//! カメラの向きは全部０度で開始
	m_rot.set(0.0f, 0.0f, 0.0f);
	if (num == 1) 
	{
		m_rot.set(0.0f, 180.0f, 0.0f);
	}
	//! カメラが見る座標
	m_look.set(0.0f, 0.0f, 0.0f); // すべて０．０ｆで初期化

	//! マウスの移動量の初期化最小は0.0fから
	m_mouse_move_x = 0.0f;
	m_mouse_move_y = 0.0f;
	//! パネルの大きさ(カメラを中心として扱うため半分の大きさを使う)
	hit_box_size.set(BOX_SIZE_HALF - (float)0.1, BOX_SIZE_HALF - (float)0.1, BOX_SIZE_HALF - (float)0.1);
	before_pos.set(m_pos); //< 移動前の座標の設定
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
	m_field_size.set(SCREEN_W / 2, SCREEN_H);                                                                      // 描画する画面のサイズの設定
	m_screen_field = MakeScreen((int)m_field_size.x, (int)m_field_size.y);                                             // 描画画面を書き込むための初期設定
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 2.0f, -5.0f), VGet(0.0f, 0.0f, 1.0f));  // カメラの設定
}

//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Camera::Update(Vector3* player_pos)
{
	before_pos.set(m_pos); //< 移動前の座標の設定
	// プレイヤーの後ろに付いて動く
	m_look.set(player_pos->x, player_pos->y + 10.0f, player_pos->z);
	// マウスの移動量
	m_mouse_move_x = (float)GetMouseMoveX();
	m_mouse_move_y = (float)GetMouseMoveY();

	// カメラの向きを変える
	// （２Dのマウスの移動量をそのまま角度に渡すと大きいので少し小さくしています）
	m_rot.x += m_mouse_move_y * MOUSE_CAMERA_ROT_SPEED;
	m_rot.y += m_mouse_move_x * MOUSE_CAMERA_ROT_SPEED;

	// カメラが地面に埋まらないようにしている
	if (m_rot.x <= LOWER_ANGLE) 
	{
		m_rot.x = LOWER_ANGLE;
	}

	// カメラが真上にいかないようにしている
	if (m_rot.x >= UP_ANGLE_MAX) 
	{
		m_rot.x = UP_ANGLE_MAX;
	}

	//	ゲームパッドの右スティックの値を使って向き変数（ m_rot ）の値を変更
	// 左ステックでプレイヤーの向きや座標の更新
	// ゲームパッドの情報を取得（XINPUT の情報）
	XINPUT_STATE input;
	// ゲームパッドの情報を丸ごと取得
	GetJoypadXInputState(pad_no, &input);
	// 移動用ベクトル用変数
	Vector3 rot;
	// 左スティックの値を設定
	rot.y = input.ThumbRX;
	rot.x = input.ThumbRY;
	// -32768 ～ 32767 を-1.0f　～　1.0fにします
	rot /= 32768.0f;
	// この移動用ベクトルの大きさがある程度大きい時だけ移動させようと思います
	if (rot.GetLength() > 0.5f)
	{
		m_rot.y += rot.y * PAD_CAMERA_ROT_SPEED;
		m_rot.x -= rot.x * PAD_CAMERA_ROT_SPEED;
		// m_rot += rot * PAD_CAMERA_ROT_SPEED;  // その移動ベクトル分座標移動
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
// カメラが壁に埋まらないようにする(うまくいかない)
//---------------------------------------------------------------------------------
void Camera::Hit_Object(Vector3* obj_pos, Vector3* obj_size)
{
	if (before_pos.x + hit_box_size.x >= obj_pos->x - obj_size->x && before_pos.x - hit_box_size.x <= obj_pos->x + obj_size->x) 
	{
		m_pos.z = before_pos.z;
		m_pos.x = before_pos.x;
	}
	if (before_pos.z + hit_box_size.z >= obj_pos->z - obj_size->z && before_pos.z - hit_box_size.z <= obj_pos->z + obj_size->z)
	{
		m_pos.z = before_pos.z;
		m_pos.x = before_pos.x;
	}
}

//---------------------------------------------------------------------------------
//	描画前のカメラのセット
//---------------------------------------------------------------------------------
// めんどくさいけど頑張って工事しろ
void Camera::Draw_Set()
{
	// この下の二つを地番最後にしたい
	// ２：今から描画するもの場所をテクスチャに変更します（レンダーターゲットの切り替え）
	SetDrawScreen(m_screen_field);
	// ２－１：その書き込む領域をクリアする
	ClearDrawScreen();

	// この下のやつをアップデートの一番最初にする
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
	// 文字の最初の大きさをとっておく
	int original_font_size = GetFontSize();

	SetFontSize(SCREEN_H / (int)23.0);

	const char* player1 = "PLAYER 1 ";
	// 描画幅の取得
	float player1_w = (float)GetDrawStringWidth(player1, -1);
	
	const char* player2 = "PALYER 2 ";
	// 描画幅の取得
	float player2_w = (float)GetDrawStringWidth(player2, -1);

	// 文字列の高さ取得
	float players_h = (float)GetFontSize();

	// プレイヤー１の場合
	if (camera_No == 0) 
	{
		// ３Dが描画された画像を描画
		DrawGraphF(m_field_pos.x, m_field_pos.y, m_screen_field, TRUE);
		// どっちの画面が移っているのかがわかるように
		DrawString(SCREEN_W / (int)50, SCREEN_H / (int)20 - (int)players_h, player1, GetColor(255, 255, 255));
		// 画像がわかりやすいように
		DrawLineBox((int)m_field_pos.x, (int)m_field_pos.y, (int)m_field_pos.x + (int)m_field_size.x, (int)m_field_pos.y + (int)m_field_size.y, GetColor(255, 255, 255));

	}
	// プレイヤー２の場合
	else 
	{
		int player2_x = /*SCREEN_W / 50.0 +*/ SCREEN_W / (int)1.3 + (int)player2_w;
		// ３Dが描画された画像を描画
		DrawGraphF(m_field_pos.x + m_field_size.x, m_field_pos.y, m_screen_field, TRUE);
		// どっちの画面が移っているのかがわかるように
		DrawString(player2_x, SCREEN_H / (int)20.0 - (int)players_h, player2, GetColor(255, 255, 255));
		// 画像がわかりやすいように
		DrawLineBox((int)m_field_pos.x + (int)m_field_size.x, (int)m_field_pos.y, (int)m_field_pos.x + (int)m_field_size.x * (int)2, (int)m_field_pos.y + (int)m_field_size.y, GetColor(0, 255, 255));
	}
	
}

//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Camera::Exit()
{
}
