#include "WinMain.h"

#include "TitleScene.h"

//------------------------------------------
// ��������
//------------------------------------------
void TiteleScene::Init()
{
	background_image = LoadGraph("Data/Baclground/Title.jpg"); // �摜�̗p������
	image_pos.set(0.0f, 0.0f); // �`����W�̐ݒ�

	// �J�E���g�ނ͍ŏ��͂O�X�^�[�g
	count_flame = 0;
	count_time = 0;

	scene_change_judge = false; // �ŏ��̓V�[���̐؂�ւ������Ă͂����Ȃ�
}

//------------------------------------------
// �X�V����
//------------------------------------------
void TiteleScene::Update()
{
	Flame_Time_Update(&count_flame, &count_time);
	if (count_time >= 10) // �^�C�g����ʂ�10�b�o������
	{
		scene_change_judge = true; // �V�[���̐؂�ւ���������
	}
	
	
}

//------------------------------------------
// �`�揈��
//------------------------------------------
void TiteleScene::Draw()
{
	// �w�i�摜�̕`��
	DrawGraph(image_pos.x, image_pos.y, background_image, TRUE);
	DrawFormatString(16, 16, GetColor(0, 0, 0), "time:%2d", count_time);
}

//------------------------------------------
// �I������
//------------------------------------------
void TiteleScene::Exit()
{
	DeleteGraph(background_image); // �摜�f�[�^�̉��
}
