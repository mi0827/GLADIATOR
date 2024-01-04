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
	void Update()override;

	// �`�揈��
	void Draw()override;

	// �I������
	void Exit()override;

public:
	int background_image; // �w�i�摜�p��
	Vector2 image_pos;    // �摜�p�̕`����W
	int count_flame; // �t���[���J�E���g�p�̕ϐ� 
	int count_time;  // �t���[��������ۂ̊���o���ē����p�̎���

	// �t�H���g�f�[�^�p
	int GTA_font_data; // GTA�̃t�H���g�f�[�^�p�̕ϐ�
	LPCSTR GTA_font_path;

	enum Title_se
	{
		DECISION, // �^�C�g����ʂŎw��̃{�^���������ꂽ��

		SE_MAX,   // SE�̍ő吔
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
