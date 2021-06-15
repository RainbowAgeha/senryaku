#include "GameMain.h"
#include "GameSceneMain.h"
#include "Game1Scene.h"
#include <math.h>

//�O����`(GameMain.cpp�ɂĐ錾)
extern int Input, EdgeInput;

//�}�b�v���_�̈ʒu
#define BaseX 20
#define BaseY 50

//�F�̒萔�錾
int Cr_White = GetColor(255, 255, 255);
int Cr_Red = GetColor(255, 0, 0);
int Cr_Blue = GetColor(0, 0, 255);
int Cr_Green = GetColor(0, 255, 0);

//�}�b�v�̃T�C�Y
#define MapSizeX 15
#define MapSizeY 10

//�}�b�v�C�x���g�萔
enum {
	EventList_none = 0,	//�C�x���g����
	EventList_Enemy,	//�퓬�C�x���g
	EventList_Item,		//�A�C�e�����l������
	EventList_End		//�ԕ�	
};

enum {
	Terrain_none = 0,	//�n�`�Ȃ�
	Terrain_mounten

};

//�J�[�\���摜ID�ƈʒu
int img_cursol;
int img_Arrrowcursol;
int cursol_x, cursol_y;

//���j���[�̂����A�ǂ��I�����Ă��邩�̕ϐ��@�Ԃ����
int MenuChoice;

//�I�������j���[�̏����ʒu
#define MenuBaseX 100
#define MenuBaseY 100

//�Q�[�����[�h�C�x���g���X�g
enum GameModeList {
	gamemode_init = 0,
	gamemode_playerturn,	//�v���C���[�^�[��
	gamemode_playerUnitchoice,	//���j�b�g��I�����Ă�����
	gamemode_playerMenuchoice,	//�K���ȏꏊ��I�����A���j���[���J���Ă�����
	gamemode_playerUnitmoveChoice,	//���j�b�g�̈ړ����I�����Ă�����

	gamemode_enemyturn,		//�G�l�~�[�^�[��

	gamemode_result
};

int GameMode;


//�}�b�v�z��@�n�`�f�[�^
int TerrainMapData[MapSizeX][MapSizeY];

//�C�x���g�}�b�v�z��@
int EventMapData[MapSizeX][MapSizeY];

//�ړ��ł���͈͂�ۑ�����z��
int MoveCheckData[MapSizeX][MapSizeY];

#define UnitNum 10
//���j�b�g�\���̔z��
struct UnitStatus {
	int UnitID;		//���j�b�gID
	int EndFlag;	//1�s���I��
	int posx;
	int posy;
	int isDead;		//����ł���t���O�B1����ł���
	int Hp;			//�X�e�[�^�X�Ƃ�
	int atk;
	int def;
	int MovePower;		//�ړ��o�����
}unitdata[UnitNum];

enum {
	Unit_Null = 0,
	Unit_Player,
	Unit_Enemy
};

//�v���C���[�̐ݒ� �}�X�ڂ̈ʒu
int playerX, playerY;

//�摜�ϐ�ID
int Img_mapGrass;
int Img_mapMounten;
//�摜�̑傫���萔
#define ImgSize 40

//���낢��g����f�B���C
int DelayTime = 0;

//-���[�U�֐��Q-------------------------------------

//�w�肵���ꏊ�ɃR�}���u����Ă��邩��������
//0 �R�}���Ȃ������A1�R�}��������
int PieceCheck(int _x, int _y);

//�R�}�̈ړ��͈͂������AMoveCheckData�Ɉړ��o����͈͂�������
//
int PieceMoveCheck(int _x, int _y,int _movePower);


//--------------------------------------

// �V�[���J�n�O�̏��������s��
BOOL initGame1Scene(void) {

	//������
	for (int i = 0; i < MapSizeX; i++) {
		for (int j = 0; j < MapSizeY; j++) {
			TerrainMapData[i][j] = Terrain_none;
			EventMapData[i][j] = 0;
			MoveCheckData[i][j] = 0;
		}
	}

	TerrainMapData[1][1] = Terrain_mounten;
	TerrainMapData[1][2] = Terrain_mounten;
	TerrainMapData[1][3] = Terrain_mounten;
	TerrainMapData[1][4] = Terrain_mounten;
	TerrainMapData[1][5] = Terrain_mounten;

	//���j�b�g�̏�����
	for (int i = 0; i < UnitNum; i++) {
		unitdata[i].UnitID = 0;
		unitdata[i].EndFlag = 0;
		unitdata[i].posx = 0;
		unitdata[i].posy = 0;
		unitdata[i].isDead = 1;
		unitdata[i].Hp = 0;
		unitdata[i].atk = 0;
		unitdata[i].def = 0;
		unitdata[i].MovePower = 0;
	}

	//�v���C���[�̐ݒ�
	//�v���C���[�͍����������ʒu
	unitdata[0].UnitID = Unit_Player;
	unitdata[0].EndFlag = 0;
	unitdata[0].posx = 0;
	unitdata[0].posy = MapSizeY - 1;
	unitdata[0].isDead = 0;
	unitdata[0].Hp = 10;
	unitdata[0].atk = 2;
	unitdata[0].def = 2;
	unitdata[0].MovePower = 5;

	//�G�̐ݒ�
	//�G�͉E�オ�����ʒu
	unitdata[1].UnitID = Unit_Enemy;
	unitdata[1].EndFlag = 0;
	unitdata[1].posx = MapSizeX - 1;
	unitdata[1].posy = 0;
	unitdata[1].isDead = 0;
	unitdata[1].Hp = 10;
	unitdata[1].atk = 2;
	unitdata[1].def = 2;

	//�摜�̓ǂݍ���
	Img_mapGrass = LoadGraph("res/map_grass.png");
	Img_mapMounten = LoadGraph("res/map_mounten.png");

	//�J�[�\���̈ʒu
	cursol_x = 0;
	cursol_y = 0;
	img_cursol = LoadGraph("res/cursol.png");

	img_Arrrowcursol = LoadGraph("res/ArrowCursol.png");
	MenuChoice = 0;

	//�Q�[�����[�h
	GameMode = gamemode_playerturn;
	
	return TRUE;
}

//	�t���[������
void moveGame1Scene() {

	switch (GameMode) {

	case gamemode_playerturn:

		//�J�[�\���𓮂���
		if ((EdgeInput & PAD_INPUT_UP)) {
			if (cursol_y > 0)cursol_y -= 1;
		}
		if ((EdgeInput & PAD_INPUT_DOWN)) {
			if (cursol_y < MapSizeY - 1)cursol_y += 1;
		}
		if ((EdgeInput & PAD_INPUT_RIGHT)) {
			if (cursol_x < MapSizeX - 1)cursol_x += 1;
		}
		if ((EdgeInput & PAD_INPUT_LEFT)) {
			if (cursol_x > 0)cursol_x -= 1;
		}

		//�{�^���P���������烁�j���[���J��
		if ((EdgeInput & PAD_INPUT_1)) {
			MenuChoice = 0;	

			//�v���C���[�̃��j�b�g�̑I���������ǂ����Ŕ����ς���
			if (PieceCheck(cursol_x, cursol_y) == 1) {
				GameMode = gamemode_playerUnitchoice;
			}
			else {
				GameMode = gamemode_playerMenuchoice;
			}
			//�G�������ꍇ�͓G�̈ړ��͈͂̕\�����o����Ƃ�����
		}

		break;

	case gamemode_playerUnitchoice:
		//�I���������߂�

		if ((EdgeInput & PAD_INPUT_UP)) {
			if (--MenuChoice < 0)MenuChoice = 3;
		}
		if ((EdgeInput & PAD_INPUT_DOWN)) {
			if (++MenuChoice > 3)MenuChoice = 0;
		}

		//�I�����ɉ����Č���
		if ((EdgeInput & PAD_INPUT_1)) {
			switch (MenuChoice) {
			case 0: //�ړ����[�h

				//�T���͈͂�S������������
				for (int i = 0; i < MapSizeX; i++) {
					for (int j = 0; j < MapSizeY; j++) {
						MoveCheckData[i][j] = 0;
					}
				}
				//�ړ��͈͂��������鏈�����Ăяo��
				PieceMoveCheck(unitdata[0].posx, unitdata[0].posy,unitdata[0].MovePower);
				//�ړ��I�����[�h�ɐ؂�ւ���
				GameMode = gamemode_playerUnitmoveChoice;
				break;
			case 1: //�U�����[�h
				break;
			case 2: //�ҋ@���[�h
				break;
			case 3: //�L�����Z��
				GameMode = gamemode_playerturn;
				break;

			}
		}

		break;
	case gamemode_playerMenuchoice:
		//�I���������߂�

		if ((EdgeInput & PAD_INPUT_UP)) {
			if (--MenuChoice < 0)MenuChoice = 3;
		}
		if ((EdgeInput & PAD_INPUT_DOWN)) {
			if (++MenuChoice > 3)MenuChoice = 0;
		}

		//�I�����ɉ����Č���
		if ((EdgeInput & PAD_INPUT_1)) {
			switch (MenuChoice) {
			case 0: //�^�[���G���h
				GameMode = gamemode_enemyturn;
				DelayTime = 180;
				break;
			case 1: //��ъm�F���[�h�@�܂������Ȃ�
				break;
			case 2: //���������m�F���[�h�@�܂������Ȃ�
				break;
			case 3: //�L�����Z��
				GameMode = gamemode_playerturn;
				break;

			}
		}

		break;

	case gamemode_playerUnitmoveChoice:

		//�J�[�\���𓮂���
		if ((EdgeInput & PAD_INPUT_UP)) {
			if (cursol_y > 0)cursol_y -= 1;
		}
		if ((EdgeInput & PAD_INPUT_DOWN)) {
			if (cursol_y < MapSizeY - 1)cursol_y += 1;
		}
		if ((EdgeInput & PAD_INPUT_RIGHT)) {
			if (cursol_x < MapSizeX - 1)cursol_x += 1;
		}
		if ((EdgeInput & PAD_INPUT_LEFT)) {
			if (cursol_x > 0)cursol_x -= 1;
		}

		//�ړ��ł���͈͂�I�������ꏊ�ɏu�Ԉړ�����
		if ((EdgeInput & PAD_INPUT_1)) {
			if (MoveCheckData[cursol_x][cursol_y] == 1) {
				//�������ꏊ���ړ��ł���ꏊ�Ȃ�v���C���[�̈ʒu�������܂ňړ�����
				unitdata[0].posx = cursol_x;
				unitdata[0].posy = cursol_y;

				//�ړ������̂ŁA���̃��j�b�g�͏I������
				unitdata[0].EndFlag = 1;

				//�I���ł��郆�j�b�g�����Ȃ��Ă��Ƃ肠�����v���C���[�̃^�[���ցB
				GameMode = gamemode_playerturn;
			}
		}

		break;

	case gamemode_enemyturn:
		
		//�������Ȃ��̂ŁA�K���Ɏ��Ԃ���������v���C���[�̃^�[��
		if (DelayTime-- < 0) {
			GameMode = gamemode_playerturn;

			//�v���C���[�̃��j�b�g�S�����s���\�ɂ���
			for (int i = 0; i < UnitNum; i++) {
				if (unitdata[i].isDead == 1)continue;
				if (unitdata[i].UnitID == Unit_Player) {
					unitdata[i].EndFlag = 0;
				}
			}


		}

		break;

	}

}


//	�����_�����O����
void renderGame1Scene(void){
	//DrawString(30, 50, "�Q�[����ʂP�ł�", GetColor(255, 255, 255));
	//DrawString(30, 100, "�{�^���P�Ń^�C�g���ɖ߂�", GetColor(255, 255, 255));

	//�}�b�v�͏�ɕ\��
	for (int i = 0; i < MapSizeX; i++) {
		for (int j = 0; j < MapSizeY; j++) {
			switch (TerrainMapData[i][j]) {
			case Terrain_none:
				//DrawFormatString(BaseX + i * ImgSize, BaseY + j * ImgSize, Cr_White, "��");
				DrawGraph(BaseX + i * ImgSize, BaseY + j * ImgSize,Img_mapGrass,true);
				break;
			case Terrain_mounten:
				//DrawFormatString(BaseX + i * ImgSize, BaseY + j * ImgSize, Cr_White, "��");
				DrawGraph(BaseX + i * ImgSize, BaseY + j * ImgSize, Img_mapMounten, true);
				break;
			case 2:
				DrawFormatString(BaseX + i * ImgSize,  BaseY + j * ImgSize, Cr_Green, "��");
				break;
			}
		}
	}

	//���j�b�g�̕\��
	for (int i = 0; i < UnitNum; i++) {
		if (unitdata[i].isDead == 1)continue;

		if (unitdata[i].UnitID == Unit_Player) {
			//�v���C���[�̕`�揈��
			//�s���\�ȏꍇ���邭�A�s���o���Ȃ��ꍇ�D�F�ŕ\������
			if (unitdata[i].EndFlag == 0) {
				DrawFormatString(BaseX + unitdata[i].posx * ImgSize, BaseY + unitdata[i].posy * ImgSize, Cr_Red, "��");
			}
			else {
				//�D�F��
				DrawFormatString(BaseX + unitdata[i].posx * ImgSize, BaseY + unitdata[i].posy * ImgSize, GetColor(128, 128, 128), "��");
			}
		}

		if (unitdata[i].UnitID == Unit_Enemy) {
			//�G�̕`�揈��
			DrawFormatString(BaseX + unitdata[i].posx * ImgSize, BaseY + unitdata[i].posy * ImgSize, Cr_Blue, "��");
		}
	}

	//�J�[�\���̕\��
	DrawGraph(BaseX + cursol_x * ImgSize, BaseY + cursol_y * ImgSize, img_cursol,true);

	//����̕\��
	switch (GameMode) {
	case gamemode_playerturn:
		DrawFormatString(0, 0, Cr_White, "�v���C���[�̃^�[���ł��B���j�b�g��I�����Ă��������B");
		break;
	case gamemode_playerUnitchoice:
		DrawFormatString(MenuBaseX, MenuBaseY, Cr_White, "�ړ�");
		DrawFormatString(MenuBaseX, MenuBaseY + 50 * 1, Cr_White, "�U��");
		DrawFormatString(MenuBaseX, MenuBaseY + 50 * 2, Cr_White, "�ҋ@");

		DrawFormatString(MenuBaseX, MenuBaseY + 50 * 3, Cr_White, "�L�����Z��");

		//�J�[�\���̕\��
		DrawGraph(MenuBaseX - 40, MenuBaseY + MenuChoice * 50, img_Arrrowcursol, true);

		break;
	case gamemode_playerMenuchoice:
		DrawFormatString(MenuBaseX, MenuBaseY, Cr_White, "�^�[���G���h");
		DrawFormatString(MenuBaseX, MenuBaseY + 50 * 1, Cr_White, "���");
		DrawFormatString(MenuBaseX, MenuBaseY + 50 * 2, Cr_White, "���������m�F");

		DrawFormatString(MenuBaseX, MenuBaseY + 50 * 3, Cr_White, "�L�����Z��");

		//�J�[�\���̕\��
		DrawGraph(MenuBaseX - 40, MenuBaseY + MenuChoice * 50, img_Arrrowcursol, true);

		break;

	case gamemode_playerUnitmoveChoice:
		//�ړ��ł���}�b�v��\������
		for (int i = 0; i < MapSizeX; i++) {
			for (int j = 0; j < MapSizeY; j++) {
				if(MoveCheckData[i][j] == 1){
					DrawFormatString(BaseX + i * ImgSize, BaseY + j * ImgSize, Cr_Green, "��");
				}
			}
		}

		//�J�[�\���̕\��
		DrawGraph(MenuBaseX - 40, MenuBaseY + MenuChoice * 50, img_Arrrowcursol, true);

		break;
	case gamemode_enemyturn:
		DrawFormatString(0, 0, Cr_White, "�G�̃^�[���ł��B"); 

		DrawFormatString(MenuBaseX, MenuBaseY, Cr_White, "�܂���������Ă��Ȃ���");
		DrawFormatString(MenuBaseX, MenuBaseY+50, Cr_White, "�^�[�����؂�ւ��܂�%d",DelayTime);

		break;

	}


}

//	�V�[���I�����̌㏈��
void releaseGame1Scene(void) {


}

// ���蔻��R�[���o�b�N �@�@�@�����ł͗v�f���폜���Ȃ����ƁI�I
void  Game1SceneCollideCallback(int nSrc, int nTarget, int nCollideID) {

}


int PieceCheck(int _x, int _y) {
	//�����Ă��郆�j�b�g��������������
	for (int i = 0; i < UnitNum; i++) {
		if (unitdata[i].isDead == 1)continue;
		//�w�肳��Ă���ꏊ�ɃR�}�����邩�ǂ���
		if (unitdata[i].posx == _x && unitdata[i].posy == _y){
			//�w�肵���}�X�ɂ��郆�j�b�g���I�����Ă���ꍇ�I���ł��Ȃ�
			if (unitdata[i].EndFlag == 0) {
				//�Ȃ����A�v���C���[���ǂ���
				if (unitdata[i].UnitID == Unit_Player) {
					return 1;
				}
			}
		}
	}
	
	//�������Ă�������Ȃ������̂�0��Ԃ�
	return 0;
}

int PieceMoveCheck(int _x, int _y, int _movePower){
	//�t�B�[���h�O�͖���
	if (_x < 0 || _x >= MapSizeX || _y < 0 || _y >= MapSizeY)return 0;
	//�`�F�b�N�ς݂͖���
	if(MoveCheckData[_x][_y] == 1) return 0;
	//�ړ��ł��Ȃ��u���b�N�������ꍇ������
	if (TerrainMapData[_x][_y] != 0)return 0;
	//�ړ�������0�������ꍇ������
	if (_movePower <= 0)return 0;

	//�����܂ŗ����Ƃ������͍��Q�Ƃ��Ă���}�X�͈ړ��ł���}�X�ł��邱�Ƃ��킩��
	MoveCheckData[_x][_y] = 1;

	//���݂̃}�X����㉺���E�Ƀ`�F�b�N����
	return 1 +
		PieceMoveCheck(_x + 1, _y, _movePower - 1) +
		PieceMoveCheck(_x - 1, _y, _movePower - 1) +
		PieceMoveCheck(_x, _y + 1, _movePower - 1) +
		PieceMoveCheck(_x, _y - 1, _movePower - 1);

}
