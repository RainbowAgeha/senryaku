#include "GameMain.h"
#include "GameSceneMain.h"
#include "MenuScene.h"

//���j���[���ڂ̃V�[���ԍ��̔z��
#define MENU_MAX 3
SCENE_NO menu[MENU_MAX] = { SCENE_GAME1, SCENE_GAME2, SCENE_GAME3 };
char *menuList[3] = { "�Q�[���X�^�[�g","�I�v�V����","�I��" };
//�I�����ꂽ�Q�[����\�����j���[�ԍ��̏������imenu�̓Y�����j
static int selectedGame = 0;

int startfont;

//�O����`(GameMain.cpp�ɂĐ錾)
extern int Input, EdgeInput;


//�V�[���J�n�O�̏��������s��
BOOL initMenuScene(void) {

	SetFontSize(32);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	selectedGame = 0;

	return TRUE;
}

//�t���[������
void moveMenuScene() {

	//�V���j���[���ڂ̑I��
	//�V(1) �@�V���Ɂ��������ꂽ��A
	if ((EdgeInput & PAD_INPUT_UP)) {
		//�V(1) �A�P��̃��j���[���ڂ��I�����ꂽ�Ƃ���B
		//      �@�������A�������̃��j���[���ڂ��Ȃ��Ƃ��́A�ŉ��i�̃��j���[���ڂ��I�����ꂽ�Ƃ���
		if (--selectedGame < 0) {
			selectedGame = MENU_MAX - 1;
		}
	}


	//�V(2) �@�V���Ɂ��������ꂽ��A
	if ((EdgeInput & PAD_INPUT_DOWN)) {
		//�V(2) �A�P���̃��j���[���ڂ��I�����ꂽ�Ƃ���B�B
		//      �@�������A�����艺�̃��j���[���ڂ��Ȃ��Ƃ��́A�ŏ�i�̃��j���[���ڂ��I�����ꂽ�Ƃ���
		if (++selectedGame >= MENU_MAX) {
			selectedGame = 0;
		}
	}

	//�V(3) �V���Ƀ{�^���P�������ꂽ��I������Ă���V�[����
	if ((EdgeInput & PAD_INPUT_1)) {
		changeScene(menu[selectedGame]);
	}
}

//�����_�����O����
void renderMenuScene(void) {

	DrawString(30, 50, "���j���[���", GetColor(255, 255, 255));
	DrawString(30, 400, "�L�[�����őI���B�{�^���P�Ō���", GetColor(255, 255, 255));

	//�U(2) ���j���[���ڂ̕\��
	int x = 220, y = 140, gapY = 80;	//�ix,y)�F�\���J�n���W�@gapY�F�s�̍���
	for (int i = 0; i < MENU_MAX; i++, y += gapY) {

		//�U(2) �@�I�����ꂽ���ڂ̕\��
		if (i == selectedGame) {
			DrawString(x, y, menuList[i], GetColor(255, 0, 0));
			//�U(2) �A�I������Ă��Ȃ����ڂ̕\��
		}
		else {
			DrawString(x, y, menuList[i], GetColor(255, 255, 255));
		}

	}
}

//�V�[���I�����̌㏈��
void releaseMenuScene(void) {


}

//���蔻��R�[���o�b�N �@�@�@�����ł͗v�f���폜���Ȃ����ƁI�I
void  MenuSceneCollideCallback(int nSrc, int nTarget, int nCollideID) {
}
