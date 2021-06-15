#include "GameSceneMain.h"

//�S�ẴV�[���̃w�b�_�t�@�C�����C���N���[�h����
#include "Game1Scene.h"
#include "Game2Scene.h"
#include "Game3Scene.h"
#include "MenuScene.h"


//���̃t�@�C���������Ŏg�p����֐��̃v���g�^�C�v�錾
//���݂̃V�[���̏���������
void initCurrentScene(void);
//���݂̃V�[���̃t���[������
void moveCurrentScene();
//���݂̃V�[���̃����_�����O����
void renderCurrentScene(void);
//���݂̃V�[���̍폜����
void releaseCurrentScene(void);

//���̃t�@�C���������Ŏg�p����ϐ��̐錾�istatic�����Đ錾����j
static SCENE_NO sceneNo = SCENE_NONE;	// ���݂̃V�[���ԍ��i�K�������l��SCENE_NONE�j
static SCENE_NO prevScene = SCENE_NONE;	// 1�O�̃V�[���ԍ��i�K�������l��SCENE_NONE�j
static SCENE_NO nextScene = SCENE_NONE;	// ���̃V�[���ԍ��i�K�������l��SCENE_NONE�j

//�R�Q�[���J�n�O�̏��������s��
BOOL InitGame(void){
	// �S�ẴV�[���ŋ��L���郂�m������������
	

	//�R(1) ���߂̃V�[���ԍ��̐ݒ�
	changeScene(SCENE_MENU);
	return TRUE;
}

//�t���[������
void FrameMove(){
	

	// ���̃V�[���ɕύX���邩�ǂ������f����
	if (sceneNo != nextScene){
		//���݂̃V�[���̍폜����
		releaseCurrentScene();
		//���݂̃V�[����V�K�V�[���ɕύX����
		sceneNo = nextScene;
		//�V�����V�[���̏���������
		initCurrentScene();
	}

	//���݂̃V�[���̃t���[������
	moveCurrentScene();
}

//�����_�����O����
void RenderScene(){
	//���݂̃V�[���̃����_�����O����
	renderCurrentScene();
}

//�Q�[���I�����̌㏈��
void GameRelease(void){
	//���݂̃V�[���̍폜����
	releaseCurrentScene();
	// �S�ẴV�[���ŋ��L���郂�m�̍폜����������

}

//�R(2) ���蔻��R�[���o�b�N �@�@�@�����ł͗v�f���폜���Ȃ����ƁI�I
void  CollideCallback(int nSrc, int nTarget, int nCollideID){
	switch (sceneNo){
	case SCENE_NONE:	break;
	case SCENE_MENU:	MenuSceneCollideCallback(nSrc, nTarget, nCollideID);		break;
	case SCENE_GAME1:	Game1SceneCollideCallback(nSrc, nTarget, nCollideID);		break;
	case SCENE_GAME2:	Game2SceneCollideCallback(nSrc, nTarget, nCollideID);		break;
	case SCENE_GAME3:	Game3SceneCollideCallback(nSrc, nTarget, nCollideID);		break;
	case SCENE_MAX:		break;
	default:
		MessageBox(NULL, "�܂����̃V�[���͂Ȃ�", "�쐬�r��", 0);
		changeScene(prevScene);
	}
}

//�V�[����ύX����֐�
void changeScene(SCENE_NO no){
	// ���݂̃V�[���Ɠ����Ƃ��͉������Ȃ�
	if (sceneNo == no)return;
	// �������Ȃ��V�[���ԍ��̎��͖�������
	if (no >= SCENE_MAX) return;
	if (no <= SCENE_NONE) return;
	// �V�[����ύX����
	prevScene = sceneNo;
	nextScene = no;
}

//�R(3) ���݂̃V�[���̏���������
void initCurrentScene(void){
	switch (sceneNo){
	case SCENE_NONE:	break;
	case SCENE_MENU:	initMenuScene();	break;
	case SCENE_GAME1:	initGame1Scene();	break;
	case SCENE_GAME2:	initGame2Scene();	break;
	case SCENE_GAME3:	initGame3Scene();	break;
	case SCENE_MAX:		break;
	default:
		MessageBox(NULL, "�܂����̃V�[���͂Ȃ�", "�쐬�r��", 0);
		changeScene(prevScene);
	}
}
//�R(4) ���݂̃V�[���̃t���[������
void moveCurrentScene(){
	switch (sceneNo){
	case SCENE_NONE:	break;
	case SCENE_MENU:	moveMenuScene();		break;
	case SCENE_GAME1:	moveGame1Scene();		break;
	case SCENE_GAME2:	moveGame2Scene();		break;
	case SCENE_GAME3:	moveGame3Scene();		break;
	case SCENE_MAX:		break;
	default:
		MessageBox(NULL, "�܂����̃V�[���͂Ȃ�", "�쐬�r��", 0);
		changeScene(prevScene);
	}
}
//�R(5) ���݂̃V�[���̃����_�����O����
void renderCurrentScene(void){
	switch (sceneNo){
	case SCENE_NONE:	break;
	case SCENE_MENU:	renderMenuScene();		break;
	case SCENE_GAME1:	renderGame1Scene();		break;
	case SCENE_GAME2:	renderGame2Scene();		break;
	case SCENE_GAME3:	renderGame3Scene();		break;
	case SCENE_MAX:		break;
	default:
		MessageBox(NULL, "�܂����̃V�[���͂Ȃ�", "�쐬�r��", 0);
		changeScene(prevScene);
	}
}
//�R(6) ���݂̃V�[���̍폜����
void releaseCurrentScene(void){
	switch (sceneNo){
	case SCENE_NONE:	break;
	case SCENE_MENU:	releaseMenuScene();		break;
	case SCENE_GAME1:	releaseGame1Scene();	break;
	case SCENE_GAME2:	releaseGame2Scene();	break;
	case SCENE_GAME3:	releaseGame3Scene();	break;
	case SCENE_MAX:		break;
	default:
		MessageBox(NULL, "�܂����̃V�[���͂Ȃ�", "�쐬�r��", 0);
		changeScene(prevScene);
	}
}
