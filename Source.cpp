#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <iostream>
#include <vector>
#include <random>
#include <conio.h>
#include <chrono>


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
				Clear(olc::CYAN);
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
						cout << endl << (int)(time / 60 * 1000) << "miliseconds | average: " << (float)(average/repetitions);
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
			<< "4. GameName\n\n\n\n\n\n\n\n\n";


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
				cout << "Eclipse";
				_getch();
				break;
			}

			case 4:
			{
				system("cls");
				cout << "Eclipse";
				_getch();
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
