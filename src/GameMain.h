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

// �V�[���؂�ւ��p�̊֐�
void Scene_Change_Judge(int& now_scene, const int& next_scene);

