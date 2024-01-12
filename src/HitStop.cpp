#include "WinMain.h"
#include "HitStop.h"

// --------------------------------------------------
// ヒットストップしてほしいか動いてほしいかを返す関数
// --------------------------------------------------
bool HitStop::Hit_Stop()
{
	stop_frame_count--; // カウントを減らす

	// ストップカウントが一定の値以上あると
	if (stop_frame_count > 0) {
		return  true; // ヒットストップしてほしい
	}
	else {
		return false; // してほしくない
	}

}

// --------------------------------------------------
// stop_frame_countをリセットするための関数
// --------------------------------------------------
void HitStop::Stop_Count_Reset()
{
	// カウントのリセット
	stop_frame_count = hit_stop_count_max;
}
