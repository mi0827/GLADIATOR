#include "WinMain.h"
#include "Vector2.h"
#include "Option.h"

// �T�E���h�̉��͈̔�
constexpr int Volume_MAX = 255; // �ő�
constexpr int Volume_LEAST = 0; // �ŏ�

constexpr int MENU_COUNT = 10; // ���j���[�{�^����������Ă������܂łɂ�����Œ᎞��

constexpr int BOX_SIZE_X = 280;               // �l�p�̔w�iX�����̃T�C�Y
constexpr int BOX_SIZE_Y = 350;               // �l�p�̔w�iY�����̃T�C�Y
constexpr int BOX_SIZE_HARF_X = BOX_SIZE_X / 2; // �w�iX�����̔����̃T�C�Y
constexpr int BOX_SIZE_HARF_Y = BOX_SIZE_Y / 2; // �w�iY�����̔����̃T�C�Y

constexpr int BAR_SIZE = 30;                // �o�[��X���W�̃T�C�Y
constexpr int BAR_SPACE_X = BOX_SIZE_HARF_X / 2;// ���S����ǂꂭ�炢���Ԃ��J���邩�̒l(X���W)
constexpr int BAR_Y = Volume_MAX / 2;// ���S����ǂꂭ�炢���Ԃ��J���邩�̒l(Y���W)



Option::Option()
{
	menu_count = 0; // �O����X�^�[�g

	// ���W�ݒ�
	option_box_pos.set(SCREEN_W / 2 - BOX_SIZE_HARF_X, SCREEN_H / 2 - BOX_SIZE_HARF_Y); // �w�i
	BGM_box_pos.set(SCREEN_W / 2 - BAR_SPACE_X, SCREEN_H / 2 + BAR_Y);
	SE_box_pos.set(SCREEN_W / 2 + BAR_SPACE_X - BAR_SIZE, SCREEN_H / 2 + BAR_Y);
	option_flag = false; // �ŏ��̓I�v�V�������j���[�͕��Ă���
	BGM_Volume = 100;
	SE_Volume = 255;
	select = 0; // BGM����X�^�[�g
}

Option::~Option()
{
}

//----------------------------------------------
// ��������
//----------------------------------------------
void Option::Init()
{
	image_box = LoadGraph("Data/Option/OptionMenu.png");
}

//----------------------------------------------
// �I�v�V�����̍X�V����
//----------------------------------------------
void Option::Update()
{

	// �I�v�V�������j���[���J���Ƃ�
	// �{�^���������ꂽ��
	if (IsPadOn(PAD_ID::PAD_START, PAD_NO::PAD_NO1))
	{
		// �I�v�V�������j���[���J��
		option_flag = true;
	}
	if (IsPadOn(PAD_ID::PAD_START, PAD_NO::PAD_NO2))
	{
		// �I�v�V�������j���[���J��
		option_flag = true;
	}
	// �I�v�V�������j���[���J���Ă���Ƃ�
	if (option_flag) {
		menu_count++; // �J�E���g�𑝂₷
		// ���E�̃{�^���ŕύX����������I��
		// �O�FBGM
		// �P�FSE
		// ���{�^��
		if (IsPadOn(PAD_ID::PAD_D_DOWN, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_D_DOWN, PAD_NO::PAD_NO2)) {
			select -= 1;
			if (select < 0) {
				select = 1;
			}
		}
		// �E�{�^��
		if (IsPadOn(PAD_ID::PAD_D_RIGHT, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_D_RIGHT, PAD_NO::PAD_NO2)) {
			select += 1;
			if (select >= 2) {
				select = 0;
			}
		}
		if (select == 0) {
			// BGM�̉��ʂ�������
			// ���{�^��
			if (IsPadOn(PAD_ID::PAD_D_LEFT, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_D_LEFT, PAD_NO::PAD_NO2)) {
				BGM_Volume -= 10;
			}
			// BGM�̉��ʂ��グ��
			// ��{�^��
			if (IsPadOn(PAD_ID::PAD_D_UP, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_D_UP, PAD_NO::PAD_NO2)) {
				BGM_Volume += 10;
			}
		}
		else {
			// SE�̉��ʂ�������
			// ���{�^��
			if (IsPadOn(PAD_ID::PAD_D_LEFT, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_D_LEFT, PAD_NO::PAD_NO2)) {
				SE_Volume -= 10;
			}
			// SE�̉��ʂ��グ��
			// ��{�^��
			if (IsPadOn(PAD_ID::PAD_D_UP, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_D_UP, PAD_NO::PAD_NO2)) {
				SE_Volume += 10;
			}
		}
	}
	// BGM�̍Œ�̒l�Ŏ~�߂�
	if (BGM_Volume <= Volume_LEAST) { BGM_Volume = Volume_LEAST; }
	// BGM�̍ő�l�Ŏ~�߂�
	if (BGM_Volume >= Volume_MAX) { BGM_Volume = Volume_MAX; }
	// SE�̍Œ�̒l�Ŏ~�߂�
	if (SE_Volume <= Volume_LEAST) { SE_Volume = Volume_LEAST; }
	// SE�̍ő�l�Ŏ~�߂�
	if (SE_Volume >= Volume_MAX) { SE_Volume = Volume_MAX; }

	// �J�E���g�����ȏ�ɂȂ�����
	if (menu_count >= MENU_COUNT) {
		// �I�v�V�������j���[���J���Ă���
		// �Ȃ��{�^���������ꂽ��
		if (IsPadOn(PAD_ID::PAD_START, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_START, PAD_NO::PAD_NO2))
		{
			// �I�v�V�������j���[�����
			option_flag = false;
			// �J�E���g�����Z�b�g
			menu_count = 0;
		}
	}
}

//----------------------------------------------
// �I�v�V�����̕`�揈��
//----------------------------------------------
void Option::Draw()
{
	// ChangeFont("�l�r ����");
	// �I�v�V�������j���[���J���Ă��鎞����
	// �`�悷��
	if (option_flag) {
		DrawExtendGraph(option_box_pos.x, option_box_pos.y, option_box_pos.x + BOX_SIZE_X, option_box_pos.y + BOX_SIZE_Y, image_box, TRUE);  // �I�v�V�������j���[�̔w�i
		// BGM�o�[�̕`��
		DrawBox(BGM_box_pos.x, BGM_box_pos.y, BGM_box_pos.x + BAR_SIZE, BGM_box_pos.y - BGM_Volume, GetColor(0, 0, 0), true);
		DrawLineBox(BGM_box_pos.x, BGM_box_pos.y, BGM_box_pos.x + BAR_SIZE, BGM_box_pos.y - BGM_Volume, GetColor(255, 255, 255));
		int original_font_size = GetFontSize();
		SetFontSize(28); // �t�H���g�T�C�Y�̕ύX
		const char* bgm = "BGM";
		Vector2 bgm_pos; // ������̍��W
		bgm_pos.x = GetDrawStringWidth(bgm, -1);
		bgm_pos.y = GetFontSize();
		DrawFormatStringF(BGM_box_pos.x + BAR_SIZE / 2 - bgm_pos.x / 2, BGM_box_pos.y, GetColor(0, 0, 0), bgm);// ������̕`��

		// SE�o�[�̕`��
		DrawBox(SE_box_pos.x, SE_box_pos.y, SE_box_pos.x + BAR_SIZE, SE_box_pos.y - SE_Volume, GetColor(0, 0, 0), true);
		DrawLineBox(SE_box_pos.x, SE_box_pos.y, SE_box_pos.x + BAR_SIZE, SE_box_pos.y - SE_Volume, GetColor(255, 255, 255));
		const char* se = "SE";
		Vector2 se_pos; // ������̍��W
		se_pos.x = GetDrawStringWidth(se, -1);
		se_pos.y = GetFontSize();
		DrawFormatStringF(SE_box_pos.x + BAR_SIZE / 2 - se_pos.x / 2, SE_box_pos.y, GetColor(0, 0, 0), se); // ������̕`��
	
	
		// �ǂ���̃o�[��I��ł��邩�킩��₷�����邽�߂̂���
		if (select == 0) {
			// BGM��
			DrawLineBox(BGM_box_pos.x, BGM_box_pos.y, BGM_box_pos.x + BAR_SIZE, BGM_box_pos.y - BGM_Volume, GetColor(255, 255, 0));
			DrawFormatStringF(BGM_box_pos.x + BAR_SIZE / 2 - bgm_pos.x / 2 - 2, BGM_box_pos.y - 2, GetColor(255, 255, 0), bgm);
		}
		else {
			// SE��
			DrawLineBox(SE_box_pos.x, SE_box_pos.y, SE_box_pos.x + BAR_SIZE, SE_box_pos.y - SE_Volume, GetColor(225, 255, 0));
			DrawFormatStringF(SE_box_pos.x + BAR_SIZE / 2 - se_pos.x / 2 -2, SE_box_pos.y-2, GetColor(255, 255, 0), se);
		}
		SetFontSize(original_font_size); // �t�H���g�T�C�Y��߂�
	}

}
