#include "WinMain.h"
#include "Vector2.h"
#include "Scene_Base.h"
#include "TitleScene.h"

const int Title_Time_MAX = 10;  // �^�C�g���`�掞��(������3�b)

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
	//// DX���C�u�����̃J������ݒ肷��B
	//SetCameraPositionAndTarget_UpVecY(VGet(10, 10, -20), VGet(0, 0, 0));
	//SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	//SetCameraNearFar(1.0f, 150.0f);

	//// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	//Effekseer_Sync3DSetting();


	count_flame--; // �t���[���̃J�E���g�����炷
	if (count_flame <= 0) { // �t���[�����ݒ肳�ꂽ�l�ȏ�ɂȂ�����
		count_flame = FLAME_MAX; // �t���[���J�E���g�����Z�b�g
		count_time--;    // �^�C���J�E���g��i�߂�
	}
	//Flame_Time_Update(&count_flame, &count_time);
	if (count_time <= 0) // �^�C�g����ʂ�10�b�o������
	{
		scene_change_judge = true; // �V�[���̐؂�ւ���������
	}
}

//------------------------------------------
// �`�揈��
//------------------------------------------
void TiteleScene::Draw()
{
	// �����łƂ��Ă����������Z�b�g���Ă���
	// ������̕`��ƕ`�敝�̎擾��2��g���̂ł����Œ�`���Ƃ��܂�
	int original_font_size = GetFontSize();

	// �w�i�摜�̕`��
	SetFontSize(50); // �t�H���g�T�C�Y�̕ύX

	DrawGraph(image_pos.x, image_pos.y, background_image, TRUE);
	DrawFormatString(16 + 7, 16 + 7, GetColor(0, 128,128), "START:%02d", count_time); // ��
	DrawFormatString(16, 16, GetColor(0, 255, 255), "START:%02d", count_time); // ��
//	SetFontSize(18); // �t�H���g�T�C�Y��߂�


	
	
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
	DrawString(SCREEN_W / 2 - w / 2,     SCREEN_H / 2 + taile_h,     name, GetColor(255, 0, 0)); // ��
	SetFontSize(original_font_size); // �t�H���g�T�C�Y��߂�

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
	ChangeFont("MS �S�V�b�N", DX_CHARSET_DEFAULT);
}
