#include "GameMain.h"
#include "GameSceneMain.h"
#include "Game2Scene.h"

//�O����`(GameMain.cpp�ɂĐ錾)
extern int Input, EdgeInput;

// �V�[���J�n�O�̏��������s��
BOOL initGame2Scene(void) {

	return TRUE;
}

//	�t���[������
void moveGame2Scene() {

	if ((EdgeInput & PAD_INPUT_1)) {
		changeScene(SCENE_MENU);
	}

}

//	�����_�����O����
void renderGame2Scene(void) {

	DrawString(30, 50, "�Q�[����ʂQ�ł�", GetColor(255, 255, 255));
	DrawString(30, 100, "�{�^���P�Ń^�C�g���ɖ߂�", GetColor(255, 255, 255));

}

//	�V�[���I�����̌㏈��
void releaseGame2Scene(void) {


}

// ���蔻��R�[���o�b�N �@�@�@�����ł͗v�f���폜���Ȃ����ƁI�I
void  Game2SceneCollideCallback(int nSrc, int nTarget, int nCollideID) {



}
