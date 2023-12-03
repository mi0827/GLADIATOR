#pragma once
#include "Scene_Base.h"
#include "Vector2.h"
// �^�C�g���V�[���̃N���X
class TiteleScene : public Scene_Base 
{
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

};
