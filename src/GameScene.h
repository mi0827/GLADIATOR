#pragma once

#include "Snene_Base.h"
class GameScene :public Scene_Base
{
public:
	GameScene();
	// ~GameScene();
	// ��������
	void Init()override;

	// �X�V����
	void Update()override;

	// �`�揈��
	void Draw()override;

	// �I������
	void Exit()override;

	// �ړ����̂��݂��̂����蔻��v
	void Move_Hit();

	// �^�C�}�[�̍X�V����
	void Time_Update();
	// �^�C�}�[�̕`��
	void Time_Draw();

	// �U���̂����蔻����s���֐�
	void Attack_Hit(int player1, int player2);
	// �K�[�h�̓����蔻��
	void Block_Hit(int player1, int player2);
	// �L�����N�^�[�̃X�e�[�^�X�`�揈��
	void Draw_Status();

private:

};