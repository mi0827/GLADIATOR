#include "Snene_Base.h"
#include "WinMain.h"

const int Flame_MAX= 60; // 一秒何フレームか



//----------------------------------------------
// フレームから時間に置き換える関数
//----------------------------------------------
void Scene_Base::Flame_Time_Update(int* flame, int* time)
{
    flame++; // フレームのカウントを進める
    if (*flame >= Flame_MAX) { // フレームが設定された値以上になったら
        *flame = 0; // フレームカウントをリセット
       *time++;    // タイムカウントを進める
    }
}
