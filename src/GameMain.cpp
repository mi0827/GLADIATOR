#include "WinMain.h"
#include "GameMain.h"

#include "GameScene.h"

GameScene play_scene; // �Q�[���v���C�V�[���̃I�u�W�F�N�g


// ��������(�e�V�[����)
void GameInit()
{
	play_scene.GameInit(); 
}

// �X�V����
void GameUpdate()
{
	play_scene.GameUpdate();
	
}

// �`�揈��
void GameDraw()
{
	play_scene.GameDraw();
	
}

// �I������
void GameExit()
{
	play_scene.GameExit();

}
