#include "GameMain.h"
#include "GameSceneMain.h"
#include "Game3Scene.h"

//�O����`(GameMain.cpp�ɂĐ錾)
extern int Input, EdgeInput;

// �V�[���J�n�O�̏��������s��
BOOL initGame3Scene(void){


	return TRUE;
}

//	�t���[������
void moveGame3Scene(){

	//�V(3) �V���Ƀ{�^���P�������ꂽ��I������Ă���V�[����
	if ((EdgeInput & PAD_INPUT_1)) {
		changeScene(SCENE_MENU);
	}

}

//	�����_�����O����
void renderGame3Scene(void){

	DrawString(30, 50, "�Q�[����ʂP�ł�", GetColor(255, 255, 255));
	DrawString(30, 100, "�{�^���P�Ń^�C�g���ɖ߂�", GetColor(255, 255, 255));

}

//	�V�[���I�����̌㏈��
void releaseGame3Scene(void){


}

// ���蔻��R�[���o�b�N �@�@�@�����ł͗v�f���폜���Ȃ����ƁI�I
void  Game3SceneCollideCallback( int nSrc, int nTarget, int nCollideID ){



}
