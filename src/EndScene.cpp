#include "WinMain.h"
#include "Vector2.h"
#include "BGM.h"
#include "SE.h"
#include "Scene_Base.h"
#include "EndScene.h"

BGM end_bgm;

const int End_Time_MAX = 3;  // �G���h�`�掞��(������3�b)
//------------------------------------------
// ��������
//------------------------------------------
void EndScene::Init()
{
	background_image = LoadGraph("Data/background/End.jpg"); // �w�i�摜�̓ǂݍ���
	image_pos.set(0.0f, 0.0f); // �`����W�̐ݒ�

	// �J�E���g�ނ͍ŏ��̓}�b�N�X�X�^�[�g
	count_flame = FLAME_MAX;
	count_time  = End_Time_MAX;

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

	// BGM�̐ݒ�
	BGM_Init();

}

//------------------------------------------
// �X�V����
//------------------------------------------
void EndScene::Update(int bgm_volume, int se_volume)
{
	// BGM�̉��ʂ̒���
	end_bgm.BGM_ChangeVolume(bgm_volume, BGM_MAX);

	count_flame--; // �t���[���̃J�E���g�����炷
	if (count_flame <= 0) { // �t���[�����ݒ肳�ꂽ�l�ȏ�ɂȂ�����
		count_flame = FLAME_MAX; // �t���[���J�E���g�����Z�b�g
		count_time--;    // �^�C���J�E���g��i�߂�
	}
	//Flame_Time_Update(&count_flame, &count_time);
	if (count_time <= 0) // �^�C�g����ʂ�10�b�o������
	{
		scene_change_judge = true; // �V�[���̐؂�ւ���������
		// BGM�̍Đ����~�߂�
		end_bgm.Stop_BGM(BGM_1);
	}
}

//------------------------------------------
// �`�揈��
//------------------------------------------
void EndScene::Draw()
{
	// ������̕`��ƕ`�敝�̎擾��2��g���̂ł����Œ�`���Ƃ��܂�
	int original_font_size = GetFontSize();
	// �w�i�摜�̕`��

	DrawExtendGraph(image_pos.x, image_pos.y, SCREEN_W,SCREEN_H, background_image, TRUE);
	SetFontSize(100); // �t�H���g�T�C�Y�̕ύX
	DrawFormatString(16, 16, GetColor(0, 0, 0), "RESTART:%2d", count_time);
	//SetFontSize(40); // �t�H���g�T�C�Y�̕ύX
	//DrawFormatString(16, 16, GetColor(255, 255, 255), "RESTART:%2d", count_time);
	

	SetFontSize(200); // �t�H���g�T�C�Y�̕ύX
	// ������̕`��ƕ`�敝�̎擾��2��g���̂ł����Œ�`���Ƃ��܂�
	const char* name = "GLADIATOR";
	// �`�敝�̎擾
	float w = GetDrawStringWidth(name, -1);
	// ������̍����擾
	float h = GetFontSize();
	// �`��
	DrawStringF(SCREEN_W / 2 - w / 2  - 3, SCREEN_H / 2- 3, name, GetColor(255, 255, 255), TRUE);
	DrawStringF(SCREEN_W / 2 - w / 2, SCREEN_H / 2, name, GetColor(0, 0, 0), TRUE);
	
	SetFontSize(80); // �t�H���g�T�C�Y�̕ύX
	ChangeFont("�l�r ����", DX_CHARSET_DEFAULT); // �t�H���g�𖾒��̂ɂ���
	DrawStringF(16, 800, "  SE�F������", GetColor(0, 0, 0));
	DrawStringF(16, 900, " BGM�F�n�쓰������g�t", GetColor(0, 0, 0));
    DrawStringF(16, 1000, "BGM�FMusMus", GetColor(0, 0, 0));

	SetFontSize(original_font_size); // �t�H���g�T�C�Y��߂�
}

//------------------------------------------
// �I������
//------------------------------------------
void EndScene::Exit()
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

//------------------------------------------
// BGM�̏�������
//------------------------------------------
void EndScene::BGM_Init()
{
	// BGM�p�̔z��̗p��
	end_bgm.BGM_ContainerNew(BGM_MAX);
	// BGM�̓ǂݍ���
	end_bgm.Load_BGM("Data/BGM/End/end.mp3", BGM_1);

	// ��������BGM���Đ�����
	end_bgm.Play_BGM(DX_PLAYTYPE_BACK, true, BGM_1);
}
