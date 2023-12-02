#include "EndScene.h"
#include "WinMain.h"


//------------------------------------------
// ��������
//------------------------------------------
void EndScene::Init()
{
	background_image = LoadGraph("Data/baclground/End.jpg"); // �w�i�摜�̓ǂݍ���
	image_pos.set(0.0f, 0.0f); // �`����W�̐ݒ�

	// �J�E���g�ނ͍ŏ��͂O�X�^�[�g
	count_flame = 0;
	count_time = 0;

	scene_change_judge = false; // �ŏ��̓V�[���̐؂�ւ������Ă͂����Ȃ�
}

//------------------------------------------
// �X�V����
//------------------------------------------
void EndScene::Update()
{
	count_flame++; // �t���[���̃J�E���g��i�߂�
	if (count_flame >= Flame_MAX) { // �t���[�����ݒ肳�ꂽ�l�ȏ�ɂȂ�����
		count_flame = 0; // �t���[���J�E���g�����Z�b�g
		count_time++;    // �^�C���J�E���g��i�߂�
	}
	//Flame_Time_Update(&count_flame, &count_time);
	if (count_time >= 10) // �^�C�g����ʂ�10�b�o������
	{
		scene_change_judge = true; // �V�[���̐؂�ւ���������
	}
}

//------------------------------------------
// �`�揈��
//------------------------------------------
void EndScene::Draw()
{
	// �w�i�摜�̕`��
	DrawGraph(image_pos.x, image_pos.y, background_image, TRUE);
	DrawFormatString(16, 16, GetColor(0, 0, 0), "time:%2d", count_time);
}

//------------------------------------------
// �I������
//------------------------------------------
void EndScene::Exit()
{
	DeleteGraph(background_image); // �摜�f�[�^�̉��
}
