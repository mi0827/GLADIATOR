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
	int BGM_Volume; // BGM�̉���
	int SE_Volume;  // SE�̉���
	bool option_flag;    // �I�v�V�������j���[���J�����߂̂���

private:
	Vector2 option_box_pos; // �I�v�V�������j���[��ʂ̎l�p���W
	Vector2 BGM_box_pos;    // BGM�o�[�̍��W
	Vector2 SE_box_pos;     // SE�o�[�̍��W

	int image_box; // �w�i�摜�p�̓��ꕨ
	int menu_count; // ���j���[�{�^����������Ă������܂łɂ�����Œ᎞�Ԃ��J�E���g���邽�߂̕�

};