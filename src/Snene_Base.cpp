#include "Snene_Base.h"
#include "WinMain.h"

const int Flame_MAX= 60; // ��b���t���[����



//----------------------------------------------
// �t���[�����玞�Ԃɒu��������֐�
//----------------------------------------------
void Scene_Base::Flame_Time_Update(int* flame, int* time)
{
    flame++; // �t���[���̃J�E���g��i�߂�
    if (*flame >= Flame_MAX) { // �t���[�����ݒ肳�ꂽ�l�ȏ�ɂȂ�����
        *flame = 0; // �t���[���J�E���g�����Z�b�g
       *time++;    // �^�C���J�E���g��i�߂�
    }
}
