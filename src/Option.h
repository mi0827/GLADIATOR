#pragma once

class Option
{
public:
	// �R���X�g���N�^
	Option();
	// �f�X�g���N�^
	~Option();
	// ��������
	void Init();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();

public:
	int BGM_Volume = 0; // BGM�̉���
	int SE_Volume = 0;  // SE�̉���
	bool option_flag = false;    // �I�v�V�������j���[���J�����߂̂���

private:
	Vector2 option_box_pos = { 0.0f,0.0f }; // �I�v�V�������j���[��ʂ̎l�p���W
	Vector2 BGM_box_pos = { 0.0f,0.0f };    // BGM�o�[�̍��W
	Vector2 SE_box_pos = { 0.0f,0.0f };     // SE�o�[�̍��W

	int image_box = 0; // �w�i�摜�p�̓��ꕨ
	int menu_count = 0; // ���j���[�{�^����������Ă������܂łɂ�����Œ᎞�Ԃ��J�E���g���邽�߂̕�
	int select = 0; // SE��BGM����󂷂邽�߂̂���
};