#include "WinMain.h"
#include "GameMain.h"
#include "Scene_Base.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "EndScene.h"

Scene_Base* scene;

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
	// �ŏ��̓^�C�g���V�[������n�߂�
	scene = new TiteleScene;
	scene->Init(); // �^�C�g���V�[���̏�����

	scene_num = Titele; // �ŏ��̓^�C�g���V�[������n�߂�
}

// �X�V����
void GameUpdate()
{
	switch (scene_num)
	{
	case Titele: // �^�C�g���V�[��

		scene->Update();
		if (scene->scene_change_judge) {                             // �V�[���̐؂�ւ��̋���������
			Scene_Change_Judge(scene_num, Play); // �V�[���̐؂�ւ�
			scene->Exit();                                           // dekete�O�ɏI����������
			delete scene;                                            // �V�[���̐؂�ւ��̑O�Ƀ^�C�g���V�[����������
			scene = new GameScene;                                   // ���̃V�[����new���Ă���
			scene->Init();                                           // ���̃V�[���̏��������������ōς܂�
		}
		break;

	case Play:  // �v���C�V�[��
		scene->Update();
		if (scene->scene_change_judge) {                             // �V�[���̐؂�ւ��̋���������
			Scene_Change_Judge(scene_num, End);  // �V�[���̐؂�ւ�
			scene->Exit();                                           // dekete�O�ɏI����������
			delete scene;                                            // �V�[���̐؂�ւ��̑O�Ƀ^�C�g���V�[����������
			scene = new EndScene;                                    // ���̃V�[����new���Ă���
			scene->Init();                                           // ���̃V�[���̏��������������ōς܂�
		}
		break;
	case End:  // �G���h�V�[��
		scene->Update();
		if (scene->scene_change_judge) {                             // �V�[���̐؂�ւ��̋���������
			Scene_Change_Judge(scene_num, Titele);  // �V�[���̐؂�ւ�
			scene->Exit();                                           // dekete�O�ɏI����������
			delete scene;                                            // �V�[���̐؂�ւ��̑O�Ƀ^�C�g���V�[����������
			scene = new TiteleScene;                                 // ���̃V�[����new���Ă���
			scene->Init();                                           // ���̃V�[���̏��������������ōς܂�
		}
		break;
	}


}

// �`�揈��
void GameDraw()
{
	scene->Draw();
}

// �I������
void GameExit()
{
	
	scene->Exit();
}


//----------------------------------------------
// ���̃V�[�����玟�̃V�[���ɐ؂�ւ���֐�
//----------------------------------------------
void Scene_Change_Judge(int& now_scene, const int& next_scene)
{
	// ���̃V�[���ԍ��Ɏ��s�������V�[���ԍ�������
	now_scene = next_scene;
}