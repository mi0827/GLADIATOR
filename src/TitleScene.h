#pragma once
#include "Scene_Base.h"
#include "Vector2.h"
// �^�C�g���V�[���̃N���X
class TiteleScene : public Scene_Base
{
	//int effeckt_h;
public:
	// ��������
	void Init()override;

	// �X�V����
	void Update(int bgm_volume, int se_volume)override;

	// �`�揈��
	void Draw()override;

	// �I������
	void Exit()override;

public:
	int background_image = 0; // �w�i�摜�p�̕ϐ�
	Vector2 image_pos = {0.0f,0.0f};    // �摜�p�̕`����W
	int count_flame = 0; // �t���[���J�E���g�p�̕ϐ� 
	int count_time = 0;  // �t���[��������ۂ̊���o���ē����p�̎���
	int movie = 0;       // ����p�̕ϐ�

	// �t�H���g�f�[�^�p
	int GTA_font_data = 0; // GTA�̃t�H���g�f�[�^�p�̕ϐ�
	LPCSTR GTA_font_path = 0;

	enum Title_se
	{
		DECISION, // �^�C�g����ʂŎw��̃{�^���������ꂽ��

		SE_MAX,   // SE�̍ő吔
	};

	enum BGM
	{
		TITLE_BGM,  // �^�C�g����ʂŗ���BGM

		BGM_MAX // BGM�̍ő吔
	};

private:

	// �^�C�g����ʂł̐؂�ւ��p
	enum Title_SCENES
	{
		TITLE, // �^�C�g�����
		MOVIE, // ������
	};

	// ��ʐ؂�ւ��p�̕ϐ�
	int title_scene = 0;

	bool start_flag = false; // �^�C�g����ʂŃ{�^���������ꂽ���ǂ����̃t���O

};
