#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <iostream>
#include <vector>
#include <random>
#include <conio.h>
#include <chrono>
#include <Windows.h>
#include <Mmsystem.h>
#include <mciapi.h>
#pragma comment(lib, "Winmm.lib")




using namespace std;
using namespace std::chrono;


int speed;
int pxSize;
char keyPress;
bool paused = 0;
bool movement = false;
int tick = 0;
int repetitions = 0;
int average;
int lastTime;
int constexpr
FREE = 0, PAWN = 1, ROOK = 2, KNIGHT = 3, BISHOP = 4, QUEEN = 5, KING = 6;
int constexpr
BLACK = -1, WHITE = 1;



class Chess : public olc::PixelGameEngine {
public:
	~Chess() {
		delete sprWhite_king;
		delete sprWhite_queen;
		delete sprWhite_rook;
		delete sprWhite_knight;
		delete sprWhite_bishop;
		delete sprWhite_pawn;
		delete sprBlack_king;
		delete sprBlack_queen;
		delete sprBlack_rook;
		delete sprBlack_knight;
		delete sprBlack_bishop;
		delete sprBlack_pawn;
		delete sprBackground;
		delete decWhite_king;
		delete decWhite_queen;
		delete decWhite_rook;
		delete decWhite_knight;
		delete decWhite_bishop;
		delete decWhite_pawn;
		delete decBlack_king;
		delete decBlack_queen;
		delete decBlack_rook;
		delete decBlack_knight;
		delete decBlack_bishop;
		delete decBlack_pawn;
		delete decBackground;
	}
	Chess() {
		sAppName = "Chess";
	}
	void loadChessDecals() {
		sprBlack_rook = new olc::Sprite("./chessSources/br.png");
		sprBlack_king = new olc::Sprite("./chessSources/bk.png");
		sprBlack_queen = new olc::Sprite("./chessSources/bq.png");
		sprBlack_pawn = new olc::Sprite("./chessSources/bp.png");
		sprBlack_bishop = new olc::Sprite("./chessSources/bb.png");
		sprBlack_knight = new olc::Sprite("./chessSources/bn.png");
		sprWhite_rook = new olc::Sprite("./chessSources/wr.png");
		sprWhite_king = new olc::Sprite("./chessSources/wk.png");
		sprWhite_queen = new olc::Sprite("./chessSources/wq.png");
		sprWhite_pawn = new olc::Sprite("./chessSources/wp.png");
		sprWhite_bishop = new olc::Sprite("./chessSources/wb.png");
		sprWhite_knight = new olc::Sprite("./chessSources/wn.png");
		sprBackground = new olc::Sprite("./chessSources/background.png");
		sprPawnPromote = new olc::Sprite("./chessSources/pawnPromote.png");
		sprMoveBlack = new olc::Sprite("./chessSources/moveBlack.png");
		sprMoveWhite = new olc::Sprite("./chessSources/moveWhite.png");
		sprAttBlack = new olc::Sprite("./chessSources/attackBlack.png");
		sprAttWhite = new olc::Sprite("./chessSources/attackWhite.png");
		decWhite_king = new olc::Decal(sprWhite_king);
		decWhite_queen = new olc::Decal(sprWhite_queen);
		decWhite_rook = new olc::Decal(sprWhite_rook);
		decWhite_knight = new olc::Decal(sprWhite_knight);
		decWhite_bishop = new olc::Decal(sprWhite_bishop);
		decWhite_pawn = new olc::Decal(sprWhite_pawn);
		decBlack_king = new olc::Decal(sprBlack_king);
		decBlack_queen = new olc::Decal(sprBlack_queen);
		decBlack_rook = new olc::Decal(sprBlack_rook);
		decBlack_knight = new olc::Decal(sprBlack_knight);
		decBlack_bishop = new olc::Decal(sprBlack_bishop);
		decBlack_pawn = new olc::Decal(sprBlack_pawn);
		decBackground = new olc::Decal(sprBackground);
		decPawnPromote = new olc::Decal(sprPawnPromote);
		decAttBlack = new olc::Decal(sprAttBlack);
		decAttWhite = new olc::Decal(sprAttWhite);
		decMoveBlack = new olc::Decal(sprMoveBlack);
		decMoveWhite = new olc::Decal(sprMoveWhite);
	}
	olc::Sprite* sprWhite_king = nullptr;
	olc::Sprite* sprWhite_queen = nullptr;
	olc::Sprite* sprWhite_rook = nullptr;
	olc::Sprite* sprWhite_knight = nullptr;
	olc::Sprite* sprWhite_bishop = nullptr;
	olc::Sprite* sprWhite_pawn = nullptr;
	olc::Sprite* sprBlack_king = nullptr;
	olc::Sprite* sprBlack_queen = nullptr;
	olc::Sprite* sprBlack_rook = nullptr;
	olc::Sprite* sprBlack_knight = nullptr;
	olc::Sprite* sprBlack_bishop = nullptr;
	olc::Sprite* sprBlack_pawn = nullptr;
	olc::Sprite* sprBackground = nullptr;
	olc::Sprite* sprPawnPromote = nullptr;
	olc::Sprite* sprMoveWhite = nullptr;
	olc::Sprite* sprMoveBlack = nullptr;
	olc::Sprite* sprAttWhite = nullptr;
	olc::Sprite* sprAttBlack = nullptr;
	olc::Decal* decWhite_king = nullptr;
	olc::Decal* decWhite_queen = nullptr;
	olc::Decal* decWhite_rook = nullptr;
	olc::Decal* decWhite_knight = nullptr;
	olc::Decal* decWhite_bishop = nullptr;
	olc::Decal* decWhite_pawn = nullptr;
	olc::Decal* decBlack_king = nullptr;
	olc::Decal* decBlack_queen = nullptr;
	olc::Decal* decBlack_rook = nullptr;
	olc::Decal* decBlack_knight = nullptr;
	olc::Decal* decBlack_bishop = nullptr;
	olc::Decal* decBlack_pawn = nullptr;
	olc::Decal* decBackground = nullptr;
	olc::Decal* decPawnPromote = nullptr;
	olc::Decal* decMoveWhite = nullptr;
	olc::Decal* decMoveBlack = nullptr;
	olc::Decal* decAttWhite = nullptr;
	olc::Decal* decAttBlack = nullptr;
	int di[8] = { -2, -1, +1, +2, +2, +1, -1, -2 };
	int dj[8] = { +1, +2, +2, +1, -1, -2, -2, -1 };
	int tempI, tempJ, pawnJ, pawnColor;
	bool whiteKingMoved = false, blackKingMoved = false,
		blackLongRookMoved = false, blackShortRookMoved = false,
		whiteLongRookMoved = false, whiteShortRookMoved = false;
	bool playing, Selected;
	olc::vi2d drawPos;
	class Piece {
	public:
		int type;
		int color;
		int i;
		int j;
		bool highlighted;
	public:
		Piece(int Type, int Color, int I, int J) {
			this->type = Type;
			this->color = Color;
			this->i = I;
			this->j = J;
			this->highlighted = false;
		}
	};
	Piece* Field[9][9];
	Piece* tempPiece = new Piece(FREE, FREE, 0, 0);
	void setField() {
		playing = true;
		whiteKingMoved = false;
		blackKingMoved = false;
		blackLongRookMoved = false;
		blackShortRookMoved = false;
		whiteLongRookMoved = false;
		whiteShortRookMoved = false;
		Selected = false;
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				switch (i) {
				case 1:
				{
					switch (j) {
					case 1:
						Field[i][j] = new Piece(ROOK, BLACK, i, j);
						break;
					case 8:
						Field[i][j] = new Piece(ROOK, BLACK, i, j);
						break;
					case 2:
						Field[i][j] = new Piece(KNIGHT, BLACK, i, j);
						break;
					case 7:
						Field[i][j] = new Piece(KNIGHT, BLACK, i, j);
						break;
					case 3:
						Field[i][j] = new Piece(BISHOP, BLACK, i, j);
						break;
					case 6:
						Field[i][j] = new Piece(BISHOP, BLACK, i, j);
						break;
					case 4:
						Field[i][j] = new Piece(QUEEN, BLACK, i, j);
						break;
					case 5:
						Field[i][j] = new Piece(KING, BLACK, i, j);
						break;
					}
				}
				break;
				case 2:
					Field[i][j] = new Piece(PAWN, BLACK, i, j);
					break;
				case 7:
					Field[i][j] = new Piece(PAWN, WHITE, i, j);
					break;
				case 8:
				{
					switch (j) {
					case 1:
						Field[i][j] = new Piece(ROOK, WHITE, i, j);
						break;
					case 8:
						Field[i][j] = new Piece(ROOK, WHITE, i, j);
						break;
					case 2:
						Field[i][j] = new Piece(KNIGHT, WHITE, i, j);
						break;
					case 7:
						Field[i][j] = new Piece(KNIGHT, WHITE, i, j);
						break;
					case 3:
						Field[i][j] = new Piece(BISHOP, WHITE, i, j);
						break;
					case 6:
						Field[i][j] = new Piece(BISHOP, WHITE, i, j);
						break;
					case 4:
						Field[i][j] = new Piece(QUEEN, WHITE, i, j);
						break;
					case 5:
						Field[i][j] = new Piece(KING, WHITE, i, j);
						break;
					}
				}
				break;
				default:
					Field[i][j] = new Piece(FREE, FREE, i, j);
				}
			}
		}
	}
	void drawBoard() {
		if (Field[1][1]->color != BLACK) blackLongRookMoved = true;
		if (Field[1][8]->color != BLACK) blackShortRookMoved = true;
		if (Field[8][1]->color != WHITE) whiteLongRookMoved = true;
		if (Field[8][8]->color != WHITE) whiteShortRookMoved = true;
		DrawDecal({ 0,0 }, decBackground);
		for (int i = 1; i < 9; i++) {
			for (int j = 1; j < 9; j++) {
				drawPos = { int((j - 1) * 100 + 4), int((i - 1) * 100 + 4) };
				if (Field[i][j]->highlighted) {

					if (Field[i][j]->color * Field[tempI][tempJ]->color < 0) {
						if (i % 2 == j % 2) {
							DrawDecal(drawPos, decAttWhite, { 1.0f,1.0f }, olc::Pixel(255, 255, 255, 200));
						}
						else {
							DrawDecal(drawPos, decAttBlack, { 1.0f,1.0f }, olc::Pixel(255, 255, 255, 160));
						}
					}
					else {
						if (i % 2 == j % 2) {
							DrawDecal(drawPos, decMoveWhite, { 1.0f,1.0f }, olc::Pixel(255, 255, 255, 127));
						}
						else {
							DrawDecal(drawPos, decMoveBlack, { 1.0f,1.0f }, olc::Pixel(255, 255, 255, 127));
						}
					}
				}
				drawPos = { (j - 1) * 100, (i - 1) * 100 };
				if (Field[i][j]->color == WHITE) {
					switch (Field[i][j]->type) {
					case PAWN:
						DrawDecal(drawPos, decWhite_pawn);
						break;
					case ROOK:
						DrawDecal(drawPos, decWhite_rook);
						break;
					case KNIGHT:
						DrawDecal(drawPos, decWhite_knight);
						break;
					case BISHOP:
						DrawDecal(drawPos, decWhite_bishop);
						break;
					case QUEEN:
						DrawDecal(drawPos, decWhite_queen);
						break;
					case KING:
						DrawDecal(drawPos, decWhite_king);
						break;
					}
				}
				else {
					switch (Field[i][j]->type) {
					case PAWN:
						DrawDecal(drawPos, decBlack_pawn);
						break;
					case ROOK:
						DrawDecal(drawPos, decBlack_rook);
						break;
					case KNIGHT:
						DrawDecal(drawPos, decBlack_knight);
						break;
					case BISHOP:
						DrawDecal(drawPos, decBlack_bishop);
						break;
					case QUEEN:
						DrawDecal(drawPos, decBlack_queen);
						break;
					case KING:
						DrawDecal(drawPos, decBlack_king);
						break;
					}
				}
			}
		}
	}
	void resetHighlight() {
		for (int i = 1; i < 9; i++) {
			for (int j = 1; j < 9; j++) {
				Field[i][j]->highlighted = false;
			}
		}
	}
	void pawnValid(int i, int j) {

		if (Field[i][j]->color == WHITE) {
			if (j > 1 && i > 1) {
				if (Field[i - 1][j - 1]->color == BLACK && Field[i - 1][j - 1]->type != KING)
					Field[i - 1][j - 1]->highlighted = true;
			}
			if (j < 8 && i>1) {
				if (Field[i - 1][j + 1]->color == BLACK && Field[i - 1][j + 1]->type != KING)
					Field[i - 1][j + 1]->highlighted = true;
			}
			if (i == 7) {
				if (Field[i - 1][j]->type == FREE) {
					Field[i - 1][j]->highlighted = true;
					if (Field[i - 2][j]->type == FREE)
						Field[i - 2][j]->highlighted = true;
				}
			}
			else {
				if (i > 1)
					if (Field[i - 1][j]->type == FREE) {
						Field[i - 1][j]->highlighted = true;
					}
			}
		}
		else {
			if (j < 8 && i < 8) {
				if (Field[i + 1][j + 1]->color == WHITE && Field[i + 1][j + 1]->type != KING)
					Field[i + 1][j + 1]->highlighted = true;
			}
			if (i < 8 && j>1) {
				if (Field[i + 1][j - 1]->color == WHITE && Field[i + 1][j - 1]->type != KING)
					Field[i + 1][j - 1]->highlighted = true;
			}
			if (i == 2) {
				if (Field[i + 1][j]->type == FREE) {
					Field[i + 1][j]->highlighted = true;
					if (Field[i + 2][j]->type == FREE)
						Field[i + 2][j]->highlighted = true;
				}
			}
			else {
				if (i < 8)
					if (Field[i + 1][j]->type == FREE) {
						Field[i + 1][j]->highlighted = true;
					}
			}
		}
	}
	void rookValid(int i, int j) {
		int m = 1;
		while (i + m <= 8) {
			if (Field[i + m][j]->type == FREE) {
				Field[i + m][j]->highlighted = true;
			}
			else {
				if (Field[i + m][j]->color * Field[i][j]->color < 0 && Field[i + m][j]->type != KING) {
					Field[i + m][j]->highlighted = true;
					break;
				}
				else break;
			}
			m++;
		}
		m = -1;
		while (i + m >= 1) {
			if (Field[i + m][j]->type == FREE) {
				Field[i + m][j]->highlighted = true;
			}
			else {
				if (Field[i + m][j]->color * Field[i][j]->color < 0 && Field[i + m][j]->type != KING) {
					Field[i + m][j]->highlighted = true;
					break;
				}
				else break;
			}
			m--;
		}
		m = 1;
		while (j + m <= 8) {
			if (Field[i][j + m]->type == FREE) {
				Field[i][j + m]->highlighted = true;
			}
			else {
				if (Field[i][j + m]->color * Field[i][j]->color < 0 && Field[i][j + m]->type != KING) {
					Field[i][j + m]->highlighted = true;
					break;
				}
				else break;
			}
			m++;
		}
		m = -1;
		while (j + m >= 1) {
			if (Field[i][j + m]->type == FREE) {
				Field[i][j + m]->highlighted = true;
			}
			else {
				if (Field[i][j + m]->color * Field[i][j]->color < 0 && Field[i][j + m]->type != KING) {
					Field[i][j + m]->highlighted = true;
					break;
				}
				else break;
			}
			m--;
		}
	}
	void knightValid(int i, int j) {
		for (int m = 0; m < 8; m++) {
			int y = i + di[m];
			int x = j + dj[m];
			if (y >= 1 && y <= 8 && x >= 1 && x <= 8) {
				if (Field[y][x]->color != Field[i][j]->color && Field[y][x]->type != KING) {
					Field[y][x]->highlighted = true;
				}
			}
		}
	}
	void queenValid(int i, int j) {
		bishopValid(i, j);
		rookValid(i, j);
	}
	void bishopValid(int i, int j) {
		int m = 1, n = 1;
		while (i + m <= 8 && j + n <= 8) {
			if (Field[i][j]->color * Field[i + m][j + n]->color > 0) {
				break;
			}
			if (Field[i][j]->color * Field[i + m][j + n]->color < 0 && Field[i + m][j + n]->type != KING) {
				Field[i + m][j + n]->highlighted = true;
				break;
			}
			if (Field[i][j]->color * Field[i + m][j + n]->color == 0) {
				Field[i + m][j + n]->highlighted = true;
			}
			m++;
			n++;
		}
		m = 1;
		n = -1;
		while (i + m <= 8 && j + n >= 1) {
			if (Field[i][j]->color * Field[i + m][j + n]->color > 0) {
				break;
			}
			if (Field[i][j]->color * Field[i + m][j + n]->color < 0 && Field[i + m][j + n]->type != KING) {
				Field[i + m][j + n]->highlighted = true;
				break;
			}
			if (Field[i][j]->color * Field[i + m][j + n]->color == 0) {
				Field[i + m][j + n]->highlighted = true;
			}
			m++;
			n--;
		}
		m = -1;
		n = -1;
		while (i + m >= 1 && j + n >= 1) {
			if (Field[i][j]->color * Field[i + m][j + n]->color > 0) {
				break;
			}
			if (Field[i][j]->color * Field[i + m][j + n]->color < 0 && Field[i + m][j + n]->type != KING) {
				Field[i + m][j + n]->highlighted = true;
				break;
			}
			if (Field[i][j]->color * Field[i + m][j + n]->color == 0) {
				Field[i + m][j + n]->highlighted = true;
			}
			m--;
			n--;
		}
		m = -1;
		n = 1;
		while (i + m >= 1 && j + n <= 8) {
			if (Field[i][j]->color * Field[i + m][j + n]->color > 0) {
				break;
			}
			if (Field[i][j]->color * Field[i + m][j + n]->color < 0 && Field[i + m][j + n]->type != KING) {
				Field[i + m][j + n]->highlighted = true;
				break;
			}
			if (Field[i][j]->color * Field[i + m][j + n]->color == 0) {
				Field[i + m][j + n]->highlighted = true;
			}
			m--;
			n++;
		}
	}
	void kingValid(int i, int j) {
		if (i > 1) {
			if (Field[i - 1][j]->type == FREE || Field[i - 1][j]->color * Field[i][j]->color < 0) {
				Field[i - 1][j]->highlighted = true;
			}
		}
		if (j > 1) {
			if (Field[i][j - 1]->type == FREE || Field[i][j - 1]->color * Field[i][j]->color < 0) {
				Field[i][j - 1]->highlighted = true;
			}
		}
		if (i > 1 && j > 1) {
			if (Field[i - 1][j - 1]->type == FREE || Field[i - 1][j - 1]->color * Field[i][j]->color < 0) {
				Field[i - 1][j - 1]->highlighted = true;
			}
		}
		if (i < 8) {
			if (Field[i + 1][j]->type == FREE || Field[i + 1][j]->color * Field[i][j]->color < 0) {
				Field[i + 1][j]->highlighted = true;
			}
		}
		if (j < 8) {
			if (Field[i][j + 1]->type == FREE || Field[i][j + 1]->color * Field[i][j]->color < 0) {
				Field[i][j + 1]->highlighted = true;
			}
		}
		if (i < 8 && j < 8) {
			if (Field[i + 1][j + 1]->type == FREE || Field[i + 1][j + 1]->color * Field[i][j]->color < 0) {
				Field[i + 1][j + 1]->highlighted = true;
			}
		}
		if (i > 1 && j < 8) {
			if (Field[i - 1][j + 1]->type == FREE || Field[i - 1][j + 1]->color * Field[i][j]->color < 0) {
				Field[i - 1][j + 1]->highlighted = true;
			}
		}
		if (j > 1 && i < 8) {
			if (Field[i + 1][j - 1]->type == FREE || Field[i + 1][j - 1]->color * Field[i][j]->color < 0) {
				Field[i + 1][j - 1]->highlighted = true;
			}
		}
		if (Field[i][j]->color == WHITE) {
			if (!whiteKingMoved) {
				if (!whiteShortRookMoved) {
					if (Field[i][j + 1]->type == FREE && Field[i][j + 2]->type == FREE) {
						Field[i][j + 2]->highlighted = true;
					}
				}
				if (!whiteLongRookMoved) {
					if (Field[i][j - 1]->type == FREE && Field[i][j - 2]->type == FREE && Field[i][j - 3]->type == FREE) {
						Field[i][j - 3]->highlighted = true;
					}
				}
			}
		}
		else {
			if (!blackKingMoved) {
				if (!blackShortRookMoved) {
					if (Field[i][j + 1]->type == FREE && Field[i][j + 2]->type == FREE) {
						Field[i][j + 2]->highlighted = true;
					}
				}
				if (!blackLongRookMoved) {
					if (Field[i][j - 1]->type == FREE && Field[i][j - 2]->type == FREE && Field[i][j - 3]->type == FREE) {
						Field[i][j - 3]->highlighted = true;
					}
				}
			}
		}
	}
	void valid(int i, int j) {
		Field[i][j]->highlighted = true;
		switch (Field[i][j]->type) {
		case PAWN:
			pawnValid(i, j);
			break;
		case ROOK:
			rookValid(i, j);
			break;
		case KNIGHT:
			knightValid(i, j);
			break;
		case BISHOP:
			bishopValid(i, j);
			break;
		case QUEEN:
			queenValid(i, j);
			break;
		case KING:
			kingValid(i, j);
			break;
		}
	}
	void checkMouseClick() {
		int mouseX = GetMouseX() / 100 + 1;
		int mouseY = GetMouseY() / 100 + 1;
		if (playing) {
			if (GetMouse(0).bPressed) {
				if (!Selected) {
					if (Field[mouseY][mouseX]->type != FREE) {
						valid(mouseY, mouseX);
						tempPiece->type = Field[mouseY][mouseX]->type;
						tempPiece->color = Field[mouseY][mouseX]->color;
						tempI = mouseY;
						tempJ = mouseX;
						Selected = !Selected;
					}
				}
				else {
					if (Field[mouseY][mouseX]->highlighted) {
						if (Field[tempI][tempJ]->type == PAWN) {
							if (Field[tempI][tempJ]->color == WHITE) {
								if (tempI == 2 && mouseY == 1) {
									playing = false;
									pawnJ = mouseX;
									pawnColor = Field[tempI][tempJ]->color;
								}
							}
							else {
								if (tempI == 7 && mouseY == 8) {
									playing = false;
									pawnJ = mouseX;
									pawnColor = Field[tempI][tempJ]->color;
								}
							}
						}
						if (Field[tempI][tempJ]->type == KING) {
							if (Field[tempI][tempJ]->color == WHITE) {
								if (mouseY != tempI || mouseX != tempJ) {
									whiteKingMoved = true;
								}
							}
							else {
								if (mouseY != tempI || mouseX != tempJ) {
									blackKingMoved = true;
								}
							}
							if (tempJ + 2 == mouseX) {
								Field[mouseY][8]->type = FREE;
								Field[mouseY][8]->color = FREE;
								Field[mouseY][6]->type = ROOK;
								Field[mouseY][6]->color = Field[tempI][tempJ]->color;
							}
							if (tempJ - 3 == mouseX) {
								Field[mouseY][1]->type = FREE;
								Field[mouseY][1]->color = FREE;
								Field[mouseY][3]->type = ROOK;
								Field[mouseY][3]->color = Field[tempI][tempJ]->color;
							}
						}
						if (Field[tempI][tempJ]->type == ROOK) {
							if (Field[tempI][tempJ]->color == WHITE) {
								if (mouseY != tempI || mouseX != tempJ) {
									if (tempJ == 1) {
										whiteLongRookMoved = true;
									}
									else if (tempJ == 8) {
										whiteShortRookMoved = true;
									}
								}
							}
							else {
								if (mouseY != tempI || mouseX != tempJ) {
									if (tempJ == 1) {
										blackLongRookMoved = true;
									}
									else if (tempJ == 8) {
										blackShortRookMoved = true;
									}
								}
							}
						}
						Field[tempI][tempJ]->type = FREE;
						Field[tempI][tempJ]->color = FREE;
						Field[mouseY][mouseX]->type = tempPiece->type;
						Field[mouseY][mouseX]->color = tempPiece->color;
						Selected = !Selected;
						resetHighlight();
					}
				}
			}
		}
		else {
			if (GetMouse(0).bPressed) {
				if (mouseY == 4) {
					if (pawnColor == WHITE) {
						switch (mouseX) {
						case 3:
							Field[1][pawnJ]->type = QUEEN;
							break;
						case 4:
							Field[1][pawnJ]->type = ROOK;
							break;
						case 5:
							Field[1][pawnJ]->type = KNIGHT;
							break;
						case 6:
							Field[1][pawnJ]->type = BISHOP;
							break;
						}
					}
					else {
						switch (mouseX) {
						case 3:
							Field[8][pawnJ]->type = QUEEN;
							break;
						case 4:
							Field[8][pawnJ]->type = ROOK;
							break;
						case 5:
							Field[8][pawnJ]->type = KNIGHT;
							break;
						case 6:
							Field[8][pawnJ]->type = BISHOP;
							break;
						}
					}
					playing = true;
				}
			}
		}
	}
	void checkPawnPromote() {
		for (int i = 1; i < 9; i++) {
			if (Field[1][i]->type == PAWN || Field[8][i]->type == PAWN) {
				playing = false;
				pawnJ = i;
				if (Field[1][i]->type == PAWN) pawnColor = WHITE;
				if (Field[8][i]->type == PAWN) pawnColor = BLACK;
				drawPawnPromote();
				break;
			}
		}
	}
	void drawPawnPromote() {
		DrawDecal({ 0,0 }, decPawnPromote, { 1.0f,1.0f }, olc::Pixel(127, 127, 127, 127));
		if (pawnColor == WHITE) {
			DrawDecal({ 200,300 }, decWhite_queen);
			DrawDecal({ 300,300 }, decWhite_rook);
			DrawDecal({ 400,300 }, decWhite_knight);
			DrawDecal({ 500,300 }, decWhite_bishop);
		}
		else {
			DrawDecal({ 200,300 }, decBlack_queen);
			DrawDecal({ 300,300 }, decBlack_rook);
			DrawDecal({ 400,300 }, decBlack_knight);
			DrawDecal({ 500,300 }, decBlack_bishop);
		}
	}
public:
	bool OnUserCreate() override {
		loadChessDecals();
		setField();
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override {
		Clear(olc::BLACK);
		drawBoard();
		checkMouseClick();
		checkPawnPromote();
		if (GetKey(olc::Key::R).bHeld) {
			setField();
		}
		return true;
	}
};





class HBM : public olc::PixelGameEngine
{

public:
	HBM()
	{
		sAppName = "Reaction time test";
	}

public:
	float fTargetFrameTime = 1.0f / (100.0f / 1);
	float fAccumulatedTime = 0.0f;
	bool page1 = 0, startGame = 0, tryAgain = 0, guessingTime = 0;
	int page2 = 0;
	typedef std::chrono::high_resolution_clock Clock;
	float time = 0.0f;

	struct KeyCharMap
	{
		olc::Key key;
		char lower;
		char upper;
	};

	std::vector<KeyCharMap> valueInputKeys =
	{
					{olc::A, 'a', 'A'},
					{olc::B, 'b', 'B'},
					{olc::C, 'c', 'C'},
					{olc::D, 'd', 'D'},
					{olc::E, 'e', 'E'},
					{olc::F, 'f', 'F'},
					{olc::G, 'g', 'G'},
					{olc::H, 'h', 'H'},
					{olc::I, 'i', 'I'},
					{olc::J, 'j', 'J'},
					{olc::K, 'k', 'K'},
					{olc::L, 'l', 'L'},
					{olc::M, 'm', 'M'},
					{olc::N, 'n', 'N'},
					{olc::O, 'o', 'O'},
					{olc::P, 'p', 'P'},
					{olc::Q, 'q', 'Q'},
					{olc::R, 'r', 'R'},
					{olc::S, 's', 'S'},
					{olc::T, 't', 'T'},
					{olc::U, 'u', 'U'},
					{olc::V, 'v', 'V'},
					{olc::W, 'w', 'W'},
					{olc::X, 'x', 'X'},
					{olc::Y, 'y', 'Y'},
					{olc::Z, 'z', 'Z'},
					{olc::K0, '0', ')'},
					{olc::K1, '1', '!'},
					{olc::K2, '2', '@'},
					{olc::K3, '3', '#'},
					{olc::K4, '4', '$'},
					{olc::K5, '5', '%'},
					{olc::K6, '6', '^'},
					{olc::K7, '7', '&'},
					{olc::K8, '8', '*'},
					{olc::K9, '9', '('},
					{olc::NP0, '0', '0'},
					{olc::NP1, '1', '1'},
					{olc::NP2, '2', '2'},
					{olc::NP3, '3', '3'},
					{olc::NP4, '4', '4'},
					{olc::NP5, '5', '5'},
					{olc::NP6, '6', '6'},
					{olc::NP7, '7', '7'},
					{olc::NP8, '8', '8'},
					{olc::NP9, '9', '9'},
					{olc::NP_MUL, '*', '*'},
					{olc::NP_DIV, '/', '/'},
					{olc::NP_ADD, '+', '+'},
					{olc::NP_SUB, '-', '-'},
					{olc::NP_DECIMAL, '.', '.'},
					{olc::PERIOD, '.', '>'},
					{olc::SPACE, ' ', ' '},
					{olc::OEM_1, ';', ':'},
					{olc::OEM_2, '/', '?'},
					{olc::OEM_3, '`', '~'},
					{olc::OEM_4, '[', '{'},
					{olc::OEM_5, '\\', '|'},
					{olc::OEM_6, ']', '}'},
					{olc::OEM_7, '\'', '"'},
					{olc::OEM_8, '-', '-'},
					{olc::EQUALS, '=', '+'},
					{olc::COMMA, ',', '<'},
					{olc::MINUS, '-', '_'}
	};



	bool OnUserCreate() override
	{
		repetitions = 0;
		average = 0;
		lastTime = 0;
		return true;

	}

	bool OnUserUpdate(float fElapsedTime) override
	{


		if (page1 == 0)
		{
			Clear(olc::CYAN);
			DrawString(olc::vf2d(ScreenWidth() / 2 - 30, 7.5), "Hey!", olc::WHITE, 2);
			DrawString(olc::vf2d(45, 45), "Today, your reaction time", olc::WHITE, 1.25);
			DrawString(olc::vf2d(85, 55), "will be tested", olc::WHITE, 1.25);
			DrawString(olc::vf2d(25, 125), "Info: Since keyboard inputs are", olc::WHITE, 1);
			DrawString(olc::vf2d(31, 135), "faster, only keyboard presses", olc::WHITE, 1);
			DrawString(olc::vf2d(80, 145), "will be counted.", olc::WHITE, 1);
			DrawString(olc::vf2d(ScreenWidth() / 2 - 110, ScreenHeight() - 45), "Press any key to continue", olc::WHITE, 1);
			DrawString(olc::vf2d(ScreenWidth() - 65, ScreenHeight() - 10), "Page 1/2", olc::WHITE, 1);
			page1 = 1;
			return true;

		}

		if (page1 == 1 && page2 == 0)
		{
			for (auto& m : valueInputKeys)
				if (GetKey(m.key).bPressed)
				{
					page2 = 1;
					return true;
				}
		}

		if (page2 == 1)
		{
			Clear(olc::CYAN);
			DrawString(olc::vf2d(35, 45), "Basically, you have to press", olc::WHITE, 1.25);
			DrawString(olc::vf2d(35, 55), "any button once the screen", olc::WHITE, 1.25);
			DrawString(olc::vf2d(110, 65), "turns red", olc::WHITE, 1);
			DrawString(olc::vf2d(31, 135), "Additionally, your avg time", olc::WHITE, 1);
			DrawString(olc::vf2d(65, 145), "will be memorized.", olc::WHITE, 1);
			DrawString(olc::vf2d(ScreenWidth() / 2 - 100, ScreenHeight() - 45), "Press any key to start", olc::WHITE, 1);
			DrawString(olc::vf2d(ScreenWidth() - 65, ScreenHeight() - 10), "Page 2/2", olc::WHITE, 1);
			page2 = 2;
			return true;
		}


		if (page2 == 2)
		{
			for (auto& m : valueInputKeys)
				if (GetKey(m.key).bPressed)
				{
					startGame = 1;
					page2 = 3;
					return true;
				}
		}


		if (startGame == 1)
		{
			Clear(olc::CYAN);
			if (repetitions > 0)
			{
				DrawString(olc::vf2d(0, ScreenHeight() - 35), "Last time: " + to_string(lastTime) + " ms ", olc::WHITE, 1);
				DrawString(olc::vf2d(0, ScreenHeight() - 15), "Average time : " + to_string(average / repetitions) + " ms", olc::WHITE, 1);
			}


			fAccumulatedTime += fElapsedTime;
			if (fAccumulatedTime >= fTargetFrameTime)
			{
				fAccumulatedTime -= fTargetFrameTime;
				fElapsedTime = fTargetFrameTime;
			}
			else
				return true;

			if (rand() % 200 < 1)
			{
				Clear(olc::RED);
				if (repetitions > 0)
				{
					DrawString(olc::vf2d(0, ScreenHeight() - 35), "Last time: " + to_string(lastTime) + " ms ", olc::WHITE, 1);
					DrawString(olc::vf2d(0, ScreenHeight() - 15), "Average time : " + to_string(average / repetitions) + " ms", olc::WHITE, 1);
				}
				startGame = 0;
				guessingTime = 1;
				time = 0.0f;


				return true;
			}

			else
				return true;
		}



		else
		{

			if (guessingTime)
			{
				//auto t1 = Clock::now();
						//auto st = high_resolution_clock::now();


				for (auto& m : valueInputKeys)

				{
					time += fElapsedTime;

					if (GetKey(m.key).bPressed)
					{

						//auto t2 = Clock::now();

								//auto ft = high_resolution_clock::now();
						guessingTime = 0;
						startGame = 1;
						//auto d = duration_cast<microseconds>(ft - st);
		/*
				printf("%d.", (t2 - t1) / 1000000000);
				printf("%d seconds", ((t2 - t1) % 1000000000) / 100000);
		*/

		//cout << fixed << d.count() / 1000000.0 << "s";
						repetitions++;
						average = average + (int)(time / 60 * 1000);
						/*cout << endl << (int)(time / 60 * 1000) << "miliseconds | average: " << (float)(average/repetitions);*/
						lastTime = (int)(time / 60 * 1000);
						return true;
					}
				}

			}
		}

	}

};


class snek : public olc::PixelGameEngine
{

public:
	snek()
	{
		sAppName = "Snek - ESC = Pause | SPACE = Resume";
	}


public:
	float fTargetFrameTime = 1.0f / (100.0f / speed);
	float fAccumulatedTime = 0.0f;
	int posX = 0, posY = 0, dirX = 0, dirY = 0, snekLen = 0, posFoodX, posFoodY;
	vector<vector<int>> snekBody;
	void snekPositionUpdater(int dirX, int dirY)
	{
		posX = posX + dirX;
		posY = posY + dirY;
	}

public:

	bool dist(int x1, int y1, int x2, int y2)
	{
		double dist;
		dist = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
		if (dist < pxSize)
			return 1;
		else
			return 0;
	}

	void movementUpdater()
	{
		tick++;

		if (GetKey(olc::Key::W).bHeld && !(dirY == pxSize) && !movement)
		{
			dirY = pxSize * -1;
			dirX = 0;
			movement = true;
		}

		if (GetKey(olc::Key::A).bHeld && !(dirX == pxSize) && !movement)
		{
			dirX = pxSize * -1;
			dirY = 0;
			movement = true;
		}

		if (GetKey(olc::Key::S).bHeld && !(dirY == (pxSize * -1)) && !movement)
		{
			dirY = pxSize;
			dirX = 0;
			movement = true;
		}

		if (GetKey(olc::Key::D).bHeld && !(dirX == (pxSize * -1)) && !movement)
		{
			dirX = pxSize;
			dirY = 0;
			movement = true;
		}

		if (tick == 2)
		{
			tick = 0;
			movement = false;
		}
	}


	void pauseChecker()
	{
		if (GetKey(olc::Key::ESCAPE).bHeld)
		{
			paused = 1;
		}

		if (GetKey(olc::Key::SPACE).bHeld && (paused == 1))
		{
			paused = 0;
		}
	}

	void edgeHitCheck()
	{
		if (posX >= ScreenWidth())
			posX = 0;
		if (posX < 0)
			posX = ScreenWidth();
		if (posY >= ScreenHeight())
			posY = 0;
		if (posY < 0)
			posY = ScreenHeight();
	}


	bool OnUserCreate() override
	{
		Clear(olc::VERY_DARK_GREY);
		FillRect(posX, posY, pxSize, pxSize, olc::Pixel(0, 255, 0));
		int tempX, tempY;
		tempX = rand() % ScreenWidth();
		tempY = rand() % ScreenHeight();
		posFoodX = (tempX - (tempX % pxSize)) % ScreenWidth();
		posFoodY = (tempY - (tempY % pxSize)) % ScreenHeight();
		FillRect(posFoodX, posFoodY, pxSize, pxSize, olc::Pixel(255, 255, 255));



		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		pauseChecker();
		movementUpdater();


		// VVVVV --- Lower the virtual FPS --- VVVVV

		fAccumulatedTime += fElapsedTime;
		if (fAccumulatedTime >= fTargetFrameTime)
		{
			fAccumulatedTime -= fTargetFrameTime;
			fElapsedTime = fTargetFrameTime;
		}
		else
			return true;





		if (paused == 0)
		{

			//cout << ScreenWidth() << " "<<posX << " | " << ScreenHeight() << " " << posY << endl;



			if (snekBody.begin() != snekBody.end())
			{
				for (int i = 0; i < snekBody.size() - 1; i++)
				{
					if (snekBody[i][0] == posX && snekBody[i][1] == posY)
						return true;
					snekBody[i] = snekBody[i + 1];
				}
				snekBody[snekLen - 1] = { posX,posY };
			}


			// VVVVV --- Eating "food" and spawning a new one upon it being eaten --- VVVVV

			if (dist(posX, posY, posFoodX, posFoodY))
			{
				sAppName = (string)"Snake game | Highschore : " + to_string(snekLen + 1);
				int tempX, tempY;
				tempX = rand() % ScreenWidth();
				tempY = rand() % ScreenHeight();
				posFoodX = (tempX - (tempX % pxSize)) % ScreenWidth();
				posFoodY = (tempY - (tempY % pxSize)) % ScreenHeight();
				snekLen = snekLen + 1;
				vector<int> temp = { posX,posY }; // increases size by adding a temp vector into the main snek body
				snekBody.push_back(temp);
			}


			/*
			OLD KEYPRESS DETECTION
			if (_kbhit())
				keyPress = _getch();
			switch (keyPress)
			{
				case 'w':
				{
					if (dirY == pxSize)
						break;
					dirY = pxSize * -1;
					dirX = 0;
					break;
				}
				case 'a':
				{
					if (dirX == pxSize)
						break;
					dirX = pxSize * -1;
					dirY = 0;
					break;
				}
				case 's':
				{
					if (dirY == (pxSize * -1))
						break;
					dirY = pxSize;
					dirX = 0;
					break;
				}
				case 'd':
				{
					if (dirX == (pxSize*-1))
						break;
					dirX = pxSize;
					dirY = 0;
					break;
				}
			}
			*/


			snekPositionUpdater(dirX, dirY);

			edgeHitCheck();

			Clear(olc::BLACK);

			// VVVVV --- Drawing snek body --- VVVVV

			for (int i = 0; i < snekBody.size(); i++)
			{
				/*if (snekBody[i][0] == posX && snekBody[i][1] == posY) {
					while (!GetKey(olc::Key::SPACE).bHeld) {
						return true;
					}
				}*/

				FillRect(snekBody[i][0], snekBody[i][1], pxSize, pxSize, olc::DARK_GREEN);
			}

			// VVVVV --- Drawing snek head and food --- VVVVV

			FillRect(posX, posY, pxSize, pxSize, olc::GREEN);
			FillRect(posFoodX, posFoodY, pxSize, pxSize, olc::RED);
			//Sleep(speed);


			return true;
		}
		else
		{
			return true;
		}
	}
};


int main()
{

	int choice;

	while (true)
	{
		system("cls");
		cout << "What game would you like to play?\n"
			<< "1. Snake\n"
			<< "2. Reaction Test\n"
			<< "3. Chess\n"
			<< "4. Surprise\n\n\n\n\n\n\n\n\n";


		for (;;)
			if (_kbhit())
			{
				choice = _getch();
				break;
			}
		choice = (int)choice - 48;


		switch (choice)
		{
		case 1:
		{
			system("cls");



			cout << "Warning: Values too high may break the game\nInsert difficulty of the game: (The higher the harder, suggested is 8)\n";
			cin >> pxSize;

			cout << "\nWhat about the speed of the game? (The higher the harder, suggested is 75) \n";
			cin >> speed;

			speed = 500 / speed;
			system("cls");


			cout << "Controls:\n"
				<< "W A S D - Movement\n"
				<< "ESC - Pause\n"
				<< "SPACE - Resume\n\n\n";

			Sleep(3000);

			cout << "Game Starting in: \n";

			Sleep(1000);

			cout << "3...\n";

			Sleep(1000);

			cout << "2..\n";

			Sleep(1000);

			cout << "1.\n";

			Sleep(1000);

			snek game;

			if (game.Construct(200, 200, 3, 3, false, false))
				game.Start();

			cout << "\n\nHighschore:" << game.snekLen + 1 << "\n\n";

			break;
		}


		case 2:
		{
			system("cls");
			typedef std::chrono::high_resolution_clock Clock;
			HBM game;

			if (game.Construct(300, 250, 3, 3, false, false))
				game.Start();

			break;
		}


		case 3:
		{
			system("cls");
			Chess chess;
			if (chess.Construct(800, 800, 1, 1))
				chess.Start();
			break;
		}

		case 4:
		{
			system("cls");
			PlaySound(TEXT("Surprise.wav"), GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
			break;
		}

		default:
		{
			system("cls");
			cout << "Invalid choice";
			_getch();
		}

		}

	}
}
