#pragma once

#define SCREEN_W	800
#define SCREEN_H	450


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

// �U���̂����蔻����s���֐�
void Attack_Hit();
// �L�����N�^�[�̃X�e�[�^�X�`�揈��
void Draw_Status();