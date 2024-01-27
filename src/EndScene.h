#pragma once

class EndScene : public Scene_Base
{
public:
	// ��������
	void Init()override;

	// �X�V����
	void Update(int bgm_volume, int se_volume)override;

	// �`�揈��
	void Draw()override;

	// �I������
	void Exit()override;

	// BGM�̏�������
	void BGM_Init();

public:
	int background_image; // �w�i�摜�p��
	Vector2 image_pos;    // �摜�p�̕`����W

	int count_flame; // �t���[���J�E���g�p�̕ϐ� 
	int count_time;  // �t���[��������ۂ̊���o���ē����p�̎���

	// �t�H���g�f�[�^�p
	int GTA_font_data; // GTA�̃t�H���g�f�[�^�p�̕ϐ�
	LPCSTR GTA_font_path;


	enum BGM
	{

		BGM_1, // ��ڂ�bgm

		BGM_MAX // bgm�̍ő吔
	};
};