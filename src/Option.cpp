#include "WinMain.h"
#include "Vector2.h"
#include "Option.h"

// �T�E���h�̉��͈̔�
constexpr int Volume_MAX = 255; // �ő�
constexpr int Volume_LEAST = 0; // �ŏ�

constexpr int MENU_COUNT = 10; // ���j���[�{�^����������Ă������܂łɂ�����Œ᎞��

constexpr int BOX_SIZE = 300;               // �l�p�̔w�i�̃T�C�Y
constexpr int BOX_SIZE_HARF = BOX_SIZE / 2; // �w�i�̔����̃T�C�Y

constexpr int BAR_SIZE = 20;                // �o�[��X���W�̃T�C�Y
constexpr int BAR_SPACE_X= BOX_SIZE_HARF / 2;// ���S����ǂꂭ�炢���Ԃ��J���邩�̒l(X���W)
constexpr int BAR_Y = Volume_MAX / 2;// ���S����ǂꂭ�炢���Ԃ��J���邩�̒l(Y���W)



Option::Option()
{
	menu_count = 0; // �O����X�^�[�g

	// ���W�ݒ�
	option_box_pos.set(SCREEN_W / 2 - BOX_SIZE_HARF, SCREEN_H / 2 - BOX_SIZE_HARF); // �w�i
	BGM_box_pos.set(SCREEN_W / 2 - BAR_SPACE_X, SCREEN_H / 2 + BAR_Y);
	option_flag = false; // �ŏ��̓I�v�V�������j���[�͕��Ă���
	BGM_Volume = 255;
	SE_Volume = 255;
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
	// �I�v�V�������j���[���J���Ă���Ƃ�
	if (option_flag) {
		menu_count++; // �J�E���g�𑝂₷

		if (IsPadOn(PAD_ID::PAD_D_LEFT, PAD_NO::PAD_NO1)) {
			BGM_Volume-= 10;
		}


		
	}

	// �J�E���g�����ȏ�ɂȂ�����
	if (menu_count >= MENU_COUNT) {
		// �I�v�V�������j���[���J���Ă���
		// �Ȃ��{�^���������ꂽ��
		if (IsPadOn(PAD_ID::PAD_START, PAD_NO::PAD_NO1))
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
	// �I�v�V�������j���[���J���Ă��鎞����
	// �`�悷��
	if (option_flag) {
		DrawExtendGraph(option_box_pos.x, option_box_pos.y, option_box_pos.x + BOX_SIZE, option_box_pos.y + BOX_SIZE, image_box, TRUE);
		DrawBox(BGM_box_pos.x, BGM_box_pos.y, BGM_box_pos.x + BAR_SIZE, BGM_box_pos.y - BGM_Volume, GetColor(255, 255, 255),true);
	
	}

}
