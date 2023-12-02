#include "WinMain.h"
#include "GameMain.h"

#include "GameScene.h"
#include "TitleScene.h"

TiteleScene titel_scene;
GameScene play_scene; // �Q�[���v���C�V�[���̃I�u�W�F�N�g

int scene_num; // ���ǂ̃V�[�����̂�����p�̕ϐ�
// �e�V�[���ł̎g�����������邽�߂̃V�[���̗񋓑�
enum Scene
{
	Titele, // �^�C�g��
	Play,  // ���C���̃v���C�V�[��
	End,   // �G���h

	Scene_Max // �V�[���̍ő吔
};

// ��������(�e�V�[����)
void GameInit()
{
	titel_scene.Init();
	play_scene.Init(); 

	scene_num = Titele; // �ŏ��̓^�C�g���V�[������n�߂�
}

// �X�V����
void GameUpdate()
{
	switch (scene_num)
	{
	case Titele: // �^�C�g���V�[��
		
		titel_scene.Update();
		if (titel_scene.scene_change_judge) {    // �V�[���̐؂�ւ��̋���������
			Scene_Change_Judge(scene_num, Play); // �V�[���̐؂�ւ�
		}
		break;

	case Play:  // �v���C�V�[��
		play_scene.Update();
		break;
	case End:  // �G���h�V�[��
		break;
	}

	
}

// �`�揈��
void GameDraw()
{
	switch (scene_num)
	{
	case Titele: // �^�C�g���V�[��

		titel_scene.Draw();
		// titel_scene.Draw();
		break;

	case Play:  // �v���C�V�[��
		play_scene.Draw();
		break;
	case End:  // �G���h�V�[��
		break;
	}
	
}

// �I������
void GameExit()
{
	titel_scene.Exit();
	play_scene.Exit();
}


//----------------------------------------------
// ���̃V�[�����玟�̃V�[���ɐ؂�ւ���֐�
//----------------------------------------------
void Scene_Change_Judge(int& now_scene, const int& next_scene)
{
	// ���̃V�[���ԍ��Ɏ��s�������V�[���ԍ�������
	now_scene = next_scene;
}