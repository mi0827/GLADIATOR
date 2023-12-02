#include "WinMain.h"
#include "GameMain.h"

#include "GameScene.h"
#include "TitleScene.h"
#include "EndScene.h"

// �e�V�[���̃I�u�W�F�N�g
TiteleScene titel_scene; // �^�C�g��
GameScene play_scene;    // �Q�[���v���C�V�[��
EndScene end_scene;      // �G���h

int scene_num; // ���ǂ̃V�[�����̂�����p�̕ϐ�
// �e�V�[���ł̎g�����������邽�߂̃V�[���̗񋓑�
enum Scene
{
	Titele, // �^�C�g��
	Play,  // ���C���̃v���C�V�[��
	End,   // �G���h

	Scene_Max // �V�[���̍ő吔
};

// ��������
void GameInit()
{
	// �e�V�[���̏�����
	titel_scene.Init();
	play_scene.Init();
	end_scene.Init();

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
		if (play_scene.scene_change_judge) {     // �V�[���̐؂�ւ��̋���������
			Scene_Change_Judge(scene_num, End);  // �V�[���̐؂�ւ�
		}
		break;
	case End:  // �G���h�V�[��
		end_scene.Update();
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
		end_scene.Draw();
		break;
	}

}

// �I������
void GameExit()
{
	titel_scene.Exit();
	play_scene.Exit();
	end_scene.Exit();
}


//----------------------------------------------
// ���̃V�[�����玟�̃V�[���ɐ؂�ւ���֐�
//----------------------------------------------
void Scene_Change_Judge(int& now_scene, const int& next_scene)
{
	// ���̃V�[���ԍ��Ɏ��s�������V�[���ԍ�������
	now_scene = next_scene;
}