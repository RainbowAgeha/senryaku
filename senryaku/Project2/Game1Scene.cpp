#include "GameMain.h"
#include "GameSceneMain.h"
#include "Game1Scene.h"
#include <math.h>

//外部定義(GameMain.cppにて宣言)
extern int Input, EdgeInput;

//マップ原点の位置
#define BaseX 20
#define BaseY 50

//色の定数宣言
int Cr_White = GetColor(255, 255, 255);
int Cr_Red = GetColor(255, 0, 0);
int Cr_Blue = GetColor(0, 0, 255);
int Cr_Green = GetColor(0, 255, 0);

//マップのサイズ
#define MapSizeX 15
#define MapSizeY 10

//マップイベント定数
enum {
	EventList_none = 0,	//イベント無し
	EventList_Enemy,	//戦闘イベント
	EventList_Item,		//アイテムを獲得する
	EventList_End		//番兵	
};

enum {
	Terrain_none = 0,	//地形なし
	Terrain_mounten

};

//カーソル画像IDと位置
int img_cursol;
int img_Arrrowcursol;
int cursol_x, cursol_y;

//メニューのうち、どれを選択しているかの変数　赤い矢印
int MenuChoice;

//選択肢メニューの初期位置
#define MenuBaseX 100
#define MenuBaseY 100

//ゲームモードイベントリスト
enum GameModeList {
	gamemode_init = 0,
	gamemode_playerturn,	//プレイヤーターン
	gamemode_playerUnitchoice,	//ユニットを選択している状態
	gamemode_playerMenuchoice,	//適当な場所を選択し、メニューを開いている状態
	gamemode_playerUnitmoveChoice,	//ユニットの移動先を選択している状態

	gamemode_enemyturn,		//エネミーターン

	gamemode_result
};

int GameMode;


//マップ配列　地形データ
int TerrainMapData[MapSizeX][MapSizeY];

//イベントマップ配列　
int EventMapData[MapSizeX][MapSizeY];

//移動できる範囲を保存する配列
int MoveCheckData[MapSizeX][MapSizeY];

#define UnitNum 10
//ユニット構造体配列
struct UnitStatus {
	int UnitID;		//ユニットID
	int EndFlag;	//1行動終了
	int posx;
	int posy;
	int isDead;		//死んでいるフラグ。1死んでいる
	int Hp;			//ステータスとか
	int atk;
	int def;
	int MovePower;		//移動出来る量
}unitdata[UnitNum];

enum {
	Unit_Null = 0,
	Unit_Player,
	Unit_Enemy
};

//プレイヤーの設定 マス目の位置
int playerX, playerY;

//画像変数ID
int Img_mapGrass;
int Img_mapMounten;
//画像の大きさ定数
#define ImgSize 40

//いろいろ使うよディレイ
int DelayTime = 0;

//-ユーザ関数群-------------------------------------

//指定した場所にコマが置かれているか検索する
//0 コマがなかった、1コマがあった
int PieceCheck(int _x, int _y);

//コマの移動範囲を検索、MoveCheckDataに移動出来る範囲を代入する
//
int PieceMoveCheck(int _x, int _y,int _movePower);


//--------------------------------------

// シーン開始前の初期化を行う
BOOL initGame1Scene(void) {

	//初期化
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

	//ユニットの初期化
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

	//プレイヤーの設定
	//プレイヤーは左下が初期位置
	unitdata[0].UnitID = Unit_Player;
	unitdata[0].EndFlag = 0;
	unitdata[0].posx = 0;
	unitdata[0].posy = MapSizeY - 1;
	unitdata[0].isDead = 0;
	unitdata[0].Hp = 10;
	unitdata[0].atk = 2;
	unitdata[0].def = 2;
	unitdata[0].MovePower = 5;

	//敵の設定
	//敵は右上が初期位置
	unitdata[1].UnitID = Unit_Enemy;
	unitdata[1].EndFlag = 0;
	unitdata[1].posx = MapSizeX - 1;
	unitdata[1].posy = 0;
	unitdata[1].isDead = 0;
	unitdata[1].Hp = 10;
	unitdata[1].atk = 2;
	unitdata[1].def = 2;

	//画像の読み込み
	Img_mapGrass = LoadGraph("res/map_grass.png");
	Img_mapMounten = LoadGraph("res/map_mounten.png");

	//カーソルの位置
	cursol_x = 0;
	cursol_y = 0;
	img_cursol = LoadGraph("res/cursol.png");

	img_Arrrowcursol = LoadGraph("res/ArrowCursol.png");
	MenuChoice = 0;

	//ゲームモード
	GameMode = gamemode_playerturn;
	
	return TRUE;
}

//	フレーム処理
void moveGame1Scene() {

	switch (GameMode) {

	case gamemode_playerturn:

		//カーソルを動かす
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

		//ボタン１を押したらメニューを開く
		if ((EdgeInput & PAD_INPUT_1)) {
			MenuChoice = 0;	

			//プレイヤーのユニットの選択したかどうかで判定を変える
			if (PieceCheck(cursol_x, cursol_y) == 1) {
				GameMode = gamemode_playerUnitchoice;
			}
			else {
				GameMode = gamemode_playerMenuchoice;
			}
			//敵だった場合は敵の移動範囲の表示が出来るといいね
		}

		break;

	case gamemode_playerUnitchoice:
		//選択肢を決める

		if ((EdgeInput & PAD_INPUT_UP)) {
			if (--MenuChoice < 0)MenuChoice = 3;
		}
		if ((EdgeInput & PAD_INPUT_DOWN)) {
			if (++MenuChoice > 3)MenuChoice = 0;
		}

		//選択肢に応じて決定
		if ((EdgeInput & PAD_INPUT_1)) {
			switch (MenuChoice) {
			case 0: //移動モード

				//探索範囲を全部初期化する
				for (int i = 0; i < MapSizeX; i++) {
					for (int j = 0; j < MapSizeY; j++) {
						MoveCheckData[i][j] = 0;
					}
				}
				//移動範囲を検索する処理を呼び出す
				PieceMoveCheck(unitdata[0].posx, unitdata[0].posy,unitdata[0].MovePower);
				//移動選択モードに切り替える
				GameMode = gamemode_playerUnitmoveChoice;
				break;
			case 1: //攻撃モード
				break;
			case 2: //待機モード
				break;
			case 3: //キャンセル
				GameMode = gamemode_playerturn;
				break;

			}
		}

		break;
	case gamemode_playerMenuchoice:
		//選択肢を決める

		if ((EdgeInput & PAD_INPUT_UP)) {
			if (--MenuChoice < 0)MenuChoice = 3;
		}
		if ((EdgeInput & PAD_INPUT_DOWN)) {
			if (++MenuChoice > 3)MenuChoice = 0;
		}

		//選択肢に応じて決定
		if ((EdgeInput & PAD_INPUT_1)) {
			switch (MenuChoice) {
			case 0: //ターンエンド
				GameMode = gamemode_enemyturn;
				DelayTime = 180;
				break;
			case 1: //戦績確認モード　まだ何もない
				break;
			case 2: //勝利条件確認モード　まだ何もない
				break;
			case 3: //キャンセル
				GameMode = gamemode_playerturn;
				break;

			}
		}

		break;

	case gamemode_playerUnitmoveChoice:

		//カーソルを動かす
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

		//移動できる範囲を選択した場所に瞬間移動する
		if ((EdgeInput & PAD_INPUT_1)) {
			if (MoveCheckData[cursol_x][cursol_y] == 1) {
				//押した場所が移動できる場所ならプレイヤーの位置をそこまで移動する
				unitdata[0].posx = cursol_x;
				unitdata[0].posy = cursol_y;

				//移動したので、このユニットは終了する
				unitdata[0].EndFlag = 1;

				//選択できるユニットがいなくてもとりあえずプレイヤーのターンへ。
				GameMode = gamemode_playerturn;
			}
		}

		break;

	case gamemode_enemyturn:
		
		//何もしないので、適当に時間がたったらプレイヤーのターン
		if (DelayTime-- < 0) {
			GameMode = gamemode_playerturn;

			//プレイヤーのユニット全部を行動可能にする
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


//	レンダリング処理
void renderGame1Scene(void){
	//DrawString(30, 50, "ゲーム画面１です", GetColor(255, 255, 255));
	//DrawString(30, 100, "ボタン１でタイトルに戻る", GetColor(255, 255, 255));

	//マップは常に表示
	for (int i = 0; i < MapSizeX; i++) {
		for (int j = 0; j < MapSizeY; j++) {
			switch (TerrainMapData[i][j]) {
			case Terrain_none:
				//DrawFormatString(BaseX + i * ImgSize, BaseY + j * ImgSize, Cr_White, "□");
				DrawGraph(BaseX + i * ImgSize, BaseY + j * ImgSize,Img_mapGrass,true);
				break;
			case Terrain_mounten:
				//DrawFormatString(BaseX + i * ImgSize, BaseY + j * ImgSize, Cr_White, "■");
				DrawGraph(BaseX + i * ImgSize, BaseY + j * ImgSize, Img_mapMounten, true);
				break;
			case 2:
				DrawFormatString(BaseX + i * ImgSize,  BaseY + j * ImgSize, Cr_Green, "□");
				break;
			}
		}
	}

	//ユニットの表示
	for (int i = 0; i < UnitNum; i++) {
		if (unitdata[i].isDead == 1)continue;

		if (unitdata[i].UnitID == Unit_Player) {
			//プレイヤーの描画処理
			//行動可能な場合明るく、行動出来ない場合灰色で表示する
			if (unitdata[i].EndFlag == 0) {
				DrawFormatString(BaseX + unitdata[i].posx * ImgSize, BaseY + unitdata[i].posy * ImgSize, Cr_Red, "◆");
			}
			else {
				//灰色に
				DrawFormatString(BaseX + unitdata[i].posx * ImgSize, BaseY + unitdata[i].posy * ImgSize, GetColor(128, 128, 128), "◆");
			}
		}

		if (unitdata[i].UnitID == Unit_Enemy) {
			//敵の描画処理
			DrawFormatString(BaseX + unitdata[i].posx * ImgSize, BaseY + unitdata[i].posy * ImgSize, Cr_Blue, "◆");
		}
	}

	//カーソルの表示
	DrawGraph(BaseX + cursol_x * ImgSize, BaseY + cursol_y * ImgSize, img_cursol,true);

	//操作の表示
	switch (GameMode) {
	case gamemode_playerturn:
		DrawFormatString(0, 0, Cr_White, "プレイヤーのターンです。ユニットを選択してください。");
		break;
	case gamemode_playerUnitchoice:
		DrawFormatString(MenuBaseX, MenuBaseY, Cr_White, "移動");
		DrawFormatString(MenuBaseX, MenuBaseY + 50 * 1, Cr_White, "攻撃");
		DrawFormatString(MenuBaseX, MenuBaseY + 50 * 2, Cr_White, "待機");

		DrawFormatString(MenuBaseX, MenuBaseY + 50 * 3, Cr_White, "キャンセル");

		//カーソルの表示
		DrawGraph(MenuBaseX - 40, MenuBaseY + MenuChoice * 50, img_Arrrowcursol, true);

		break;
	case gamemode_playerMenuchoice:
		DrawFormatString(MenuBaseX, MenuBaseY, Cr_White, "ターンエンド");
		DrawFormatString(MenuBaseX, MenuBaseY + 50 * 1, Cr_White, "戦績");
		DrawFormatString(MenuBaseX, MenuBaseY + 50 * 2, Cr_White, "勝利条件確認");

		DrawFormatString(MenuBaseX, MenuBaseY + 50 * 3, Cr_White, "キャンセル");

		//カーソルの表示
		DrawGraph(MenuBaseX - 40, MenuBaseY + MenuChoice * 50, img_Arrrowcursol, true);

		break;

	case gamemode_playerUnitmoveChoice:
		//移動できるマップを表示する
		for (int i = 0; i < MapSizeX; i++) {
			for (int j = 0; j < MapSizeY; j++) {
				if(MoveCheckData[i][j] == 1){
					DrawFormatString(BaseX + i * ImgSize, BaseY + j * ImgSize, Cr_Green, "□");
				}
			}
		}

		//カーソルの表示
		DrawGraph(MenuBaseX - 40, MenuBaseY + MenuChoice * 50, img_Arrrowcursol, true);

		break;
	case gamemode_enemyturn:
		DrawFormatString(0, 0, Cr_White, "敵のターンです。"); 

		DrawFormatString(MenuBaseX, MenuBaseY, Cr_White, "まだ何も作っていないよ");
		DrawFormatString(MenuBaseX, MenuBaseY+50, Cr_White, "ターンが切り替わるまで%d",DelayTime);

		break;

	}


}

//	シーン終了時の後処理
void releaseGame1Scene(void) {


}

// 当り判定コールバック 　　　ここでは要素を削除しないこと！！
void  Game1SceneCollideCallback(int nSrc, int nTarget, int nCollideID) {

}


int PieceCheck(int _x, int _y) {
	//生きているユニット分だけ検索を回す
	for (int i = 0; i < UnitNum; i++) {
		if (unitdata[i].isDead == 1)continue;
		//指定されている場所にコマがあるかどうか
		if (unitdata[i].posx == _x && unitdata[i].posy == _y){
			//指定したマスにいるユニットが終了している場合選択できない
			if (unitdata[i].EndFlag == 0) {
				//なおかつ、プレイヤーかどうか
				if (unitdata[i].UnitID == Unit_Player) {
					return 1;
				}
			}
		}
	}
	
	//検索しても当たらなかったので0を返す
	return 0;
}

int PieceMoveCheck(int _x, int _y, int _movePower){
	//フィールド外は無視
	if (_x < 0 || _x >= MapSizeX || _y < 0 || _y >= MapSizeY)return 0;
	//チェック済みは無視
	if(MoveCheckData[_x][_y] == 1) return 0;
	//移動できないブロックだった場合も無視
	if (TerrainMapData[_x][_y] != 0)return 0;
	//移動歩数が0だった場合も無視
	if (_movePower <= 0)return 0;

	//ここまで来たという事は今参照しているマスは移動できるマスであることがわかる
	MoveCheckData[_x][_y] = 1;

	//現在のマスから上下左右にチェックする
	return 1 +
		PieceMoveCheck(_x + 1, _y, _movePower - 1) +
		PieceMoveCheck(_x - 1, _y, _movePower - 1) +
		PieceMoveCheck(_x, _y + 1, _movePower - 1) +
		PieceMoveCheck(_x, _y - 1, _movePower - 1);

}
