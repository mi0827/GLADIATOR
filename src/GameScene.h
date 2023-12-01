#pragma once

class GameScene
{
public:
	GameScene();
	~GameScene();
	// ��������
	void GameInit();

	// �X�V����
	void GameUpdate();

	// �`�揈��
	void GameDraw();

	// �I������
	void GameExit();

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