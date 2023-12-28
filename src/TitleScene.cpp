#include "WinMain.h"
#include "Vector2.h"
#include "Scene_Base.h"
#include "TitleScene.h"

const int Title_Time_MAX = 5;  // �^�C�g���`�掞��(������3�b)

//------------------------------------------
// ��������
//------------------------------------------
void TiteleScene::Init()
{
	background_image = LoadGraph("Data/Background/Title.jpg"); // �摜�̗p������
	image_pos.set(0.0f, 0.0f); // �`����W�̐ݒ�

	// �J�E���g�ނ͍ŏ��̓}�b�N�X�X�^�[�g
	count_flame = FLAME_MAX;
	count_time = Title_Time_MAX;

	scene_change_judge = false; // �ŏ��̓V�[���̐؂�ւ������Ă͂����Ȃ�

	// �t�H���g�f�[�^�̓ǂݍ���
	//GTA_font_data = LoadFontDataToHandle("Data/Font/Gta/GTA.dft", 1.0f);
	GTA_font_path = "Data/Font/Gta/pricedown bl.ttf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	if (AddFontResourceEx(GTA_font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}
	ChangeFont("Pricedown Bl", DX_CHARSET_DEFAULT);

}

//------------------------------------------
// �X�V����
//------------------------------------------
void TiteleScene::Update()
{
	switch (title_scene)
	{
	case TITLE:

		// �Q�[���p�b�h�̏����ۂ��Ǝ擾
		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A) {
			// A�{�^���������ꂽ�玟�̃V�[���Ɉړ�
			start_flag = true;
		}
		else if (GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_A) {
			// A�{�^���������ꂽ�玟�̃V�[���Ɉړ�
			start_flag = true;
		}
		else
		{
			// �{�^����������Ă��Ȃ��Ƃ��̓t���O��������
			start_flag = false;
		}


		// �X�^�[�g�t���O�������Ă����玟�̃V�[���ɐi��
		if (start_flag) {
			scene_change_judge = true; // �V�[���̐؂�ւ���������
		}
		else {
			// �t���O���������Ă�����
			count_flame--; // �t���[���̃J�E���g�����炷
			if (count_flame <= 0) { // �t���[�����ݒ肳�ꂽ�l�ȏ�ɂȂ�����
				count_flame = FLAME_MAX; // �t���[���J�E���g�����Z�b�g
				count_time--;    // �^�C���J�E���g��i�߂�
			}
			if (count_time <= 0) // �^�C�g����ʂň�莞�Ԏ~�܂��Ă�����
			{
				title_scene = MOVIE; // ����̃V�[���̐؂�ւ���
			}
		}

		break;

	case MOVIE:

		// �Q�[���p�b�h�̏����ۂ��Ǝ擾
		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A) {
			// A�{�^���������ꂽ��^�C�g���`��ɖ߂�
			title_scene = TITLE;
		}
		// �Q�[���p�b�h�̏����ۂ��Ǝ擾
		if (GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_A) {
			// A�{�^���������ꂽ��^�C�g���`��ɖ߂�
			title_scene = TITLE;
		}

		break;

	}
}

//------------------------------------------
// �`�揈��
//------------------------------------------
void TiteleScene::Draw()
{

	// �w�i�摜�̕`��
	DrawGraph(image_pos.x, image_pos.y, background_image, TRUE);
	// �����łƂ��Ă����������Z�b�g���Ă���
	// ������̕`��ƕ`�敝�̎擾��2��g���̂ł����Œ�`���Ƃ��܂�
	int original_font_size = GetFontSize();


	switch (title_scene)
	{
	case TITLE:
	{
		SetFontSize(120); // �t�H���g�T�C�Y�̕ύX
		const char* name = "GLADIATOR";
		// �`�敝�̎擾
		float w = GetDrawStringWidth(name, -1);
		// ������̍����擾
		float h = GetFontSize();
		// �`��
		//DrawStringFToHandle(SCREEN_W / 2 - w -80, SCREEN_H / 2 +5, name, GetColor(128, 0, 0), GTA_font_data, TRUE); 
		//DrawStringFToHandle(SCREEN_W / 2 - w - 85, SCREEN_H / 2 , name, GetColor(255, 0, 0), GTA_font_data, TRUE); 
		int taile_h = -50;
		DrawString(SCREEN_W / 2 - w / 2 + 7, SCREEN_H / 2 + taile_h + 7, name, GetColor(128, 0, 0)); // ��
		DrawString(SCREEN_W / 2 - w / 2, SCREEN_H / 2 + taile_h, name, GetColor(255, 0, 0)); // ��
		

	}
	break;

	case MOVIE:

	{
		SetFontSize(120); // �t�H���g�T�C�Y�̕ύX
		const char* name = "�ق�Ƃ͓�6����悹��\��";
		// �`�敝�̎擾
		float w = GetDrawStringWidth(name, -1);
		// ������̍����擾
		float h = GetFontSize();
		// �`��
		//DrawStringFToHandle(SCREEN_W / 2 - w -80, SCREEN_H / 2 +5, name, GetColor(128, 0, 0), GTA_font_data, TRUE); 
		//DrawStringFToHandle(SCREEN_W / 2 - w - 85, SCREEN_H / 2 , name, GetColor(255, 0, 0), GTA_font_data, TRUE); 
		int taile_h = -50;
		DrawString(SCREEN_W / 2 - w / 2 + 7, SCREEN_H / 2 + taile_h + 7, name, GetColor(128, 0, 0)); // ��
		DrawString(SCREEN_W / 2 - w / 2, SCREEN_H / 2 + taile_h, name, GetColor(255, 0, 0)); // ��
		

	}
	break;
	}


	SetFontSize(50); // �t�H���g�T�C�Y�̕ύX


	//DrawFormatString(16 + 7, 16 + 7, GetColor(0, 128, 128), "START:%02d", count_time); // ��
	//DrawFormatString(16, 16, GetColor(0, 255, 255), "START:%02d", count_time); // ��
	DrawString(16 + 5, 16 + 5, "START: A ", GetColor(0, 128, 128)); // ��
	DrawString(16, 16, "START: A ", GetColor(0, 255, 255)); // ��
	SetFontSize(original_font_size); // �t�H���g�T�C�Y��

}



//------------------------------------------
// �I������
//------------------------------------------
void TiteleScene::Exit()
{
	DeleteGraph(background_image); // �摜�f�[�^�̉��

	// ********** �t�H���g�̃A�����[�h **********
	if (RemoveFontResourceEx(GTA_font_path, FR_PRIVATE, NULL)) {
	}
	else {
		MessageBox(NULL, "remove failure", "", MB_OK);
	}
	ChangeFont("�l�r ����", DX_CHARSET_DEFAULT);
}
