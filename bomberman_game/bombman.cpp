#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <thread>
#include <ctime>
#include <wchar.h>
#include <map>
#include <math.h>
#include <string>
using namespace std;

#include <Windows.h>

#define ScreenEnable 1

int nScreenWidth = 121;
int nScreenHeight = 30;
int nFieldWidth = 15;
int nFieldHeight = 15;

struct Bomberman
{
	int x;
	int y;
};

struct Enemy
{
	int x;
	int y;
};

struct Block
{
	int x;
	int y;
	int treature;	
};

int CheckexplosionCount(map<int, int>& Checkexplosion) {
	int count = 0;
	for ( auto &p : Checkexplosion ) count += p.second == 1;
	return count;
}

int checkSamePositionBomb(map<int, int>& Checkexplosion, map<int, pair<chrono::time_point<chrono::system_clock>, pair<int,int>>>& bombclock, list<Bomberman>& bomberman) {
	for ( auto &bc : bombclock ) {
		int px = bc.second.second.first;
		int py = bc.second.second.second;
		if (px == bomberman.front().x && py == bomberman.front().y)
			return 0;
	}
	
	return 1;
}

int main()
{
	// wchar_t Oriscreen[nScreenWidth*nScreenHeight];
	wchar_t screen[nScreenWidth*nScreenHeight];
	HWND hwnd = GetConsoleWindow();
	if(hwnd != NULL){ SetWindowPos(hwnd, 0, 0, 0, (nScreenHeight+37)*nFieldHeight, (nScreenWidth)*nFieldWidth,SWP_SHOWWINDOW|SWP_NOMOVE); }
	
	for (int i = 0; i < nScreenWidth*nScreenHeight; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;
	
	bool bKeyUpLevel = false, bKeyDownLevel = false;
	bool bstartKey = false;
	bool choiceNumberOfPlayer = false;
	int choiceflop = 0;
	int choiceBottomFlop[6] = {0};
	
	int level = 1;
	int bombermanOriX;
	int bombermanOriY;
	char filename[64];
	
	swprintf(&screen[ 6 * nScreenWidth + 40], 30, L"   =======================   ");
	swprintf(&screen[ 7 * nScreenWidth + 40], 30, L" ||        Bombman        || ");
	swprintf(&screen[ 8 * nScreenWidth + 40], 30, L"   =======================   ");
	swprintf(&screen[12 * nScreenWidth + 40], 30, L"  PRESS SPACE TO START GAME  ");
	swprintf(&screen[18 * nScreenWidth + 40], 30, L"   1 Player easy mode          ");
	swprintf(&screen[20 * nScreenWidth + 40], 30, L"   2 Players easy mode         ");
	swprintf(&screen[22 * nScreenWidth + 40], 30, L"   1 Player medium mode          ");
	swprintf(&screen[24 * nScreenWidth + 40], 30, L"   2 Players medium mode         ");
	swprintf(&screen[26 * nScreenWidth + 40], 30, L"   1 Player hard mode          ");
	swprintf(&screen[28 * nScreenWidth + 40], 30, L"   2 Players hard mode         ");
				
	while (!bstartKey){
		auto t1 = chrono::system_clock::now();
		bstartKey = 0x8000 & GetAsyncKeyState((unsigned char)('\x20'));
		
		if (bstartKey)
			break;
			
		while (chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - t1).count() < 120 && !bstartKey)
		{
			bKeyUpLevel = (0x8000 & GetAsyncKeyState((unsigned char)('\x26'))) != 0;
			bKeyDownLevel = (0x8000 & GetAsyncKeyState((unsigned char)('\x28'))) != 0;
			choiceNumberOfPlayer = (0x8000 & GetAsyncKeyState((unsigned char)('\x5a'))) != 0;
			if (bstartKey)
				break;
		}
		
		if (bstartKey)
			break;
				
		if (bKeyUpLevel)
			if (level < 100)
				level += 1;
			else
				level = 100;
		if (bKeyDownLevel)
			if (level > 1)
				level -= 1;
			else
				level = 1;
		
		// swprintf(&screen[24 * nScreenWidth + 40], 30, L" choiceflop: %d           ", choiceflop);
		
		if (choiceNumberOfPlayer) {
			choiceflop %= 6;
			
			switch (choiceflop+1) {
				case 1:
					swprintf(&screen[18 * nScreenWidth + 40], 30, L" * 1 Player easy mode          ");
					swprintf(&screen[20 * nScreenWidth + 40], 30, L"   2 Players easy mode         ");
					swprintf(&screen[22 * nScreenWidth + 40], 30, L"   1 Player medium mode          ");
					swprintf(&screen[24 * nScreenWidth + 40], 30, L"   2 Players medium mode         ");
					swprintf(&screen[26 * nScreenWidth + 40], 30, L"   1 Player hard mode          ");
					swprintf(&screen[28 * nScreenWidth + 40], 30, L"   2 Players hard mode         ");
					break;
				case 2:
					swprintf(&screen[18 * nScreenWidth + 40], 30, L"   1 Player easy mode          ");
					swprintf(&screen[20 * nScreenWidth + 40], 30, L" * 2 Players easy mode         ");
					swprintf(&screen[22 * nScreenWidth + 40], 30, L"   1 Player medium mode          ");
					swprintf(&screen[24 * nScreenWidth + 40], 30, L"   2 Players medium mode         ");
					swprintf(&screen[26 * nScreenWidth + 40], 30, L"   1 Player hard mode          ");
					swprintf(&screen[28 * nScreenWidth + 40], 30, L"   2 Players hard mode         ");
					break;
				case 3:
					swprintf(&screen[18 * nScreenWidth + 40], 30, L"   1 Player easy mode          ");
					swprintf(&screen[20 * nScreenWidth + 40], 30, L"   2 Players easy mode         ");
					swprintf(&screen[22 * nScreenWidth + 40], 30, L" * 1 Player medium mode          ");
					swprintf(&screen[24 * nScreenWidth + 40], 30, L"   2 Players medium mode         ");
					swprintf(&screen[26 * nScreenWidth + 40], 30, L"   1 Player hard mode          ");
					swprintf(&screen[28 * nScreenWidth + 40], 30, L"   2 Players hard mode         ");
					break;
				case 4:
					swprintf(&screen[18 * nScreenWidth + 40], 30, L"   1 Player easy mode          ");
					swprintf(&screen[20 * nScreenWidth + 40], 30, L"   2 Players easy mode         ");
					swprintf(&screen[22 * nScreenWidth + 40], 30, L"   1 Player medium mode          ");
					swprintf(&screen[24 * nScreenWidth + 40], 30, L" * 2 Players medium mode         ");
					swprintf(&screen[26 * nScreenWidth + 40], 30, L"   1 Player hard mode          ");
					swprintf(&screen[28 * nScreenWidth + 40], 30, L"   2 Players hard mode         ");
					break;
				case 5:
					swprintf(&screen[18 * nScreenWidth + 40], 30, L"   1 Player easy mode          ");
					swprintf(&screen[20 * nScreenWidth + 40], 30, L"   2 Players easy mode         ");
					swprintf(&screen[22 * nScreenWidth + 40], 30, L"   1 Player medium mode          ");
					swprintf(&screen[24 * nScreenWidth + 40], 30, L"   2 Players medium mode         ");
					swprintf(&screen[26 * nScreenWidth + 40], 30, L" * 1 Player hard mode          ");
					swprintf(&screen[28 * nScreenWidth + 40], 30, L"   2 Players hard mode         ");
					break;
				case 6:
					swprintf(&screen[18 * nScreenWidth + 40], 30, L"   1 Player easy mode          ");
					swprintf(&screen[20 * nScreenWidth + 40], 30, L"   2 Players easy mode         ");
					swprintf(&screen[22 * nScreenWidth + 40], 30, L"   1 Player medium mode          ");
					swprintf(&screen[24 * nScreenWidth + 40], 30, L"   2 Players medium mode         ");
					swprintf(&screen[26 * nScreenWidth + 40], 30, L"   1 Player hard mode          ");
					swprintf(&screen[28 * nScreenWidth + 40], 30, L" * 2 Players hard mode         ");
					break;
				default:
					break;
			}
			choiceflop++;
		}
		
		swprintf(&screen[14 * nScreenWidth + 40], 30, L"  CHOOSE A LEVEL YOU WANT  ");
		swprintf(&screen[16 * nScreenWidth + 40], 30, L"        LEVEL %d           ", level);
		
		if (bstartKey)
			break;
			
		WriteConsoleOutputCharacterW(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}
    
	int lives = 3;
	int nScore = 0;
	int maximumbombNumber = 1;
	int temp_bombNumber = 0;
	int nScreenSpeed = 100;
	int BombPeriod = 5;
	int treature_tmp = 0;
	int tix = 0, tiy = 0;
	
	bool levelexitOpen = false;
		
	vector<vector<int>> dirs = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
	map<int, pair<chrono::time_point<chrono::system_clock>, pair<int,int>>> bombclock;
	map<int, int> Checkexplosion;
	for (int x=0; x<maximumbombNumber; x++){
		Checkexplosion.insert({x,0});
	}	
	
	while(lives)
	{
		//list<Bomberman> bomberman = {{14,16}};
		//list<Enemy> enemy1 = {{36,16}};
		//list<Enemy> enemy2 = {{40,14}};
		//map<int, pair<list<Enemy>, vector<int>>> enemy = {{1, {{{36,16}}, {}},
        //                         		  	   		 	  {2, {{{65,8}}, {}},
		//												  {3, {{{50,24}}, {}}};
		
		bool clearlevel = false;
		bool bDead = false;
		bool bKeyLeft = false, bKeyRight = false, bKeyUp = false, bKeyDown = false, bKeyPause = false;
		bool bKeyPutBomb = false;
		int nBombDirection = 4;
		int px, py;
		int firelength = 5;
		int flag1 = 0, flag2 = 0;
		int targetx = 0, targety = 0;
		
		for (int i = 0; i < nScreenWidth*nScreenHeight; i++) screen[i] = L' ';
		
		for (int second = 1; second >= 0; second--) {
			this_thread::sleep_for(chrono::seconds(1));
			swprintf(&screen[7 * nScreenWidth + 40], 22, L"  Level %d start  ", level);
			swprintf(&screen[9 * nScreenWidth + 40], 22, L" Remain Live:  %d ", lives);
			WriteConsoleOutputCharacterW(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
		}
		
		for (int i = 0; i < nScreenWidth*nScreenHeight; i++) screen[i] = L' ';
		
		clearlevel = false;
		
		// auto clock_start = chrono::system_clock::now();
		
		vector<vector<int>> bombposition;
		
		list<Bomberman> bomberman;
		map<int, pair<int, int>> Oriblockposition;
    	map<int, pair<list<Enemy>, vector<int>>> enemy;
    	string enemypattern;
    
		sprintf(filename, "bomberman_level_map/bomberman_level%d_map.txt", level);
    
    	fstream newfile;
	
    	newfile.open(filename, ios::in);  // open a file to perform write operation using file object
    
		if (newfile.is_open()) {   //checking whether the file is open
      		string tp;
      		// map<int, pair<int, int>> Oriblockposition;
      		int column = 3;
      		int block = 0;
      		int enemyNumber = 0;
      		while(getline(newfile, tp)){ //read data from file object and put it into string.
         		cout << tp << endl; //print the data of the string
         		int row = 0;
         		for (auto& t : tp) {
         			if (t == '@') {
         				bomberman.push_back({row, column});
        		 		// bombermanOriX = row;
       			  		// bombermanOriY = column;
					}
     		    	if (t == 'O') {
       			  		Oriblockposition.insert({block, {row, column}});
        		 		block++;
					}
					if (t == '$' || t == '&') {
						enemy.insert({enemyNumber, {{{row, column}}, {}}});
						enemypattern.push_back(t);
						enemyNumber++;
					}
					// Oriscreen[column * nScreenWidth + row] = t;
					row++;
				}
        		column++;
      		}
      		newfile.close(); //close the file object.
    	}
    		
		map<int, pair<int, int>> blockposition;
		for(auto& orib : Oriblockposition) {
			blockposition.insert({orib.first, {orib.second.first, orib.second.second}});
		}
		int blkexit = blockposition.size();
	
		map<int, pair<int, int>> treature;
		int pauseflop = 0;
		
		while (!bDead && !clearlevel)
		{
			
			auto t1 = chrono::system_clock::now();
			
			while (chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - t1).count() < nScreenSpeed)
			{
				// Get Input, 
				bKeyRight = (0x8000 & GetAsyncKeyState((unsigned char)('\x27'))) != 0;
				bKeyLeft = (0x8000 & GetAsyncKeyState((unsigned char)('\x25'))) != 0;
				bKeyUp = (0x8000 & GetAsyncKeyState((unsigned char)('\x26'))) != 0;
				bKeyDown = (0x8000 & GetAsyncKeyState((unsigned char)('\x28'))) != 0;
				bKeyPutBomb = (0x8000 & GetAsyncKeyState((unsigned char)('\x5a'))) != 0;
				bKeyPause = (0x8000 & GetAsyncKeyState((unsigned char)('\x50'))) != 0;
				
				if (bKeyUp)
					nBombDirection = 0;
				else if (bKeyRight)
					nBombDirection = 1;
				else if (bKeyDown)
					nBombDirection = 2;
				else if (bKeyLeft)
					nBombDirection = 3;
				else
					nBombDirection = 4;
			}
			
			if (bKeyPutBomb && CheckexplosionCount(Checkexplosion) < maximumbombNumber) {
				// clock_start = chrono::system_clock::now();
				//temp_bombNumber = bombclock.size();
				// bombindex++;
				/*
				if (bombclock.find(temp_bombNumber-1) != bombclock.end()) {
					bombclock[temp_bombNumber-1] = {chrono::system_clock::now(), {bomberman.front().x, bomberman.front().y}};
					Checkexplosion[temp_bombNumber-1] = 1;
				} else {
					bombclock.insert({temp_bombNumber-1, {chrono::system_clock::now(), {bomberman.front().x, bomberman.front().y}}});
					Checkexplosion.insert({temp_bombNumber-1, 1});
				}
				*/
				for (int x = 0; x < Checkexplosion.size(); x++) {
					if (Checkexplosion[x] == 0 && checkSamePositionBomb(Checkexplosion, bombclock, bomberman)) {
						Checkexplosion[x] = 1;
						if (bombclock.find(x) != bombclock.end()) {
						
							bombclock[x] = {chrono::system_clock::now(), {bomberman.front().x, bomberman.front().y}};
						
						} else {
						
							bombclock.insert({x, {chrono::system_clock::now(), {bomberman.front().x, bomberman.front().y}}});
						
						}
					}
				}
			}
				
			if (!enemy.empty()) {
				for (auto& e : enemy) {
				
				int de = -1;
				
				/*
				for (int d = 0; d < 4; d++) {
					int ex = e.second.first.front().x + dirs[d][0];
					int ey = e.second.first.front().y + dirs[d][1];
					if (screen[ey * nScreenWidth + ex] != L'*') {
						de = d;
						break;
					}
				}
				*/
				
				/*
				if (bomberman.front().x - e.second.first.front().x < 0) {
					if (bomberman.front().y - e.second.first.front().y < 0) {
						e.second.second.push_back(rand()%2 * 3);
					}
					else if (bomberman.front().y - e.second.first.front().y > 0) {
						e.second.second.push_back(rand()%2 + 2);
					}
					else {
						e.second.second.push_back(rand()%2 * 2 + 1);
					}
				}
				else if (bomberman.front().x - e.second.first.front().x > 0) {
					if (bomberman.front().y - e.second.first.front().y < 0) {
						e.second.second.push_back(rand() % 2);
					}
					else if (bomberman.front().y - e.second.first.front().y > 0) {
						e.second.second.push_back(rand() % 2 + 1);
					}
					else {
						e.second.second.push_back(rand()%2 * 2 + 1);
					}
				}
				else {
					e.second.second.push_back(rand()%2 * 2);
				}
				de = e.second.second.front();
				*/
				
				de = rand()%4;
				
				switch (de) {
					case 0:
						if (e.second.first.front().y - 1 < 4 
						|| screen[(e.second.first.front().y - 1) * nScreenWidth + e.second.first.front().x] == L'*' 
						|| screen[(e.second.first.front().y - 1) * nScreenWidth + e.second.first.front().x] == L'O' 
						|| screen[(e.second.first.front().y - 1) * nScreenWidth + e.second.first.front().x] == L'p' 
						|| screen[(e.second.first.front().y - 1) * nScreenWidth + e.second.first.front().x] == L'$')
							e.second.first.push_front({ e.second.first.front().x, e.second.first.front().y });
						else
							e.second.first.push_front({ e.second.first.front().x, e.second.first.front().y - 1 });
						break;
						
					case 1: // RIGHT
						if (e.second.first.front().x + 1 > nScreenWidth-2 
						|| screen[e.second.first.front().y * nScreenWidth + e.second.first.front().x + 1] == L'*' 
						|| screen[e.second.first.front().y * nScreenWidth + e.second.first.front().x + 1] == L'O' 
						|| screen[e.second.first.front().y * nScreenWidth + e.second.first.front().x + 1] == L'p' 
						|| screen[e.second.first.front().y * nScreenWidth + e.second.first.front().x + 1] == L'$')
							e.second.first.push_front({ e.second.first.front().x, e.second.first.front().y });
						else
							e.second.first.push_front({ e.second.first.front().x + 1, e.second.first.front().y });
						break;
					case 2: // DOWN
						if (e.second.first.front().y + 1 > nScreenHeight-2 
						|| screen[(e.second.first.front().y + 1) * nScreenWidth + e.second.first.front().x] == L'*' 
						|| screen[(e.second.first.front().y + 1) * nScreenWidth + e.second.first.front().x] == L'O' 
						|| screen[(e.second.first.front().y + 1) * nScreenWidth + e.second.first.front().x] == L'p' 
						|| screen[(e.second.first.front().y + 1) * nScreenWidth + e.second.first.front().x] == L'$')
							e.second.first.push_front({ e.second.first.front().x, e.second.first.front().y });
						else
							e.second.first.push_front({ e.second.first.front().x, e.second.first.front().y + 1 });
						break;
					case 3: // LEFT
						if (e.second.first.front().x - 1 < 1 
						|| screen[e.second.first.front().y * nScreenWidth + e.second.first.front().x - 1] == L'*' 
						|| screen[e.second.first.front().y * nScreenWidth + e.second.first.front().x - 1] == L'O' 
						|| screen[e.second.first.front().y * nScreenWidth + e.second.first.front().x - 1] == L'p' 
						|| screen[e.second.first.front().y * nScreenWidth + e.second.first.front().x - 1] == L'$')
							e.second.first.push_front({ e.second.first.front().x, e.second.first.front().y });
						else
							e.second.first.push_front({ e.second.first.front().x - 1, e.second.first.front().y });
						break;
					default:
						e.second.first.push_front({ e.second.first.front().x, e.second.first.front().y });
						break;	
				}
				if (!e.second.second.empty())
					e.second.second.pop_back();
				}
			}
			
			switch (nBombDirection)
			{
			case 0: // UP 
				if (bomberman.front().y - 1 < 4 
				|| screen[(bomberman.front().y - 1) * nScreenWidth + bomberman.front().x] == L'*' 
				|| screen[(bomberman.front().y - 1) * nScreenWidth + bomberman.front().x] == L'O'
				|| screen[(bomberman.front().y - 1) * nScreenWidth + bomberman.front().x] == L'p')
					bomberman.push_front({ bomberman.front().x, bomberman.front().y });
				else
					bomberman.push_front({ bomberman.front().x, bomberman.front().y - 1 });
				break;
			case 1: // RIGHT
				if (bomberman.front().x + 1 > nScreenWidth-2 
				|| screen[bomberman.front().y * nScreenWidth + bomberman.front().x + 1] == L'*' 
				|| screen[bomberman.front().y * nScreenWidth + bomberman.front().x + 1] == L'O'
				|| screen[bomberman.front().y * nScreenWidth + bomberman.front().x + 1] == L'p')
					bomberman.push_front({ bomberman.front().x, bomberman.front().y });
				else
					bomberman.push_front({ bomberman.front().x + 1, bomberman.front().y });
				break;
			case 2: // DOWN
				if (bomberman.front().y + 1 > nScreenHeight-2 
				|| screen[(bomberman.front().y + 1) * nScreenWidth + bomberman.front().x] == L'*' 
				|| screen[(bomberman.front().y + 1) * nScreenWidth + bomberman.front().x] == L'O'
				|| screen[(bomberman.front().y + 1) * nScreenWidth + bomberman.front().x] == L'p')
					bomberman.push_front({ bomberman.front().x, bomberman.front().y });
				else
					bomberman.push_front({ bomberman.front().x, bomberman.front().y + 1 });
				break;
			case 3: // LEFT
				if (bomberman.front().x - 1 < 1 
				|| screen[bomberman.front().y * nScreenWidth + bomberman.front().x - 1] == L'*' 
				|| screen[bomberman.front().y * nScreenWidth + bomberman.front().x - 1] == L'O'
				|| screen[bomberman.front().y * nScreenWidth + bomberman.front().x - 1] == L'p')
					bomberman.push_front({ bomberman.front().x, bomberman.front().y });
				else
					bomberman.push_front({ bomberman.front().x - 1, bomberman.front().y });
				break;
			default:
				bomberman.push_front({ bomberman.front().x, bomberman.front().y });
				break;
			}
			
			for (int i = 0; i < nScreenWidth*nScreenHeight; i++) screen[i] = L' ';
			
			for (int i = 0; i < nScreenWidth; i++)
			{
				screen[i] = L'=';
				screen[2 * nScreenWidth + i] = L'=';
			}
			
			/*
			for (int j = 3; j < nScreenHeight; j++){
				for (int k = 0; k < nScreenWidth; k++)
					screen[j * nScreenWidth + k] = Oriscreen[j * nScreenWidth + k];
			}
			*/
			
			for (int j = 0; j < nScreenWidth; j++)
				screen[3 * nScreenWidth + j] = L'*';
				
			for (int i = 4; i < nScreenHeight-1; i++) {
				screen[i * nScreenWidth] = L'*';
				screen[i * nScreenWidth + nScreenWidth - 1] = L'*';
			}
			
			for (int i = 5; i < nScreenHeight - 2; i+=2) {
				wcsncpy(screen +     i * nScreenWidth + 1, L" * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * ", nScreenWidth - 2);
				wcsncpy(screen + (i+1) * nScreenWidth + 1, L"                                                                                                                       ", nScreenWidth - 2);
			}
			
			for (int j = 0; j < nScreenWidth; j++)
				screen[(nScreenHeight-1) * nScreenWidth + j] = L'*';
			
			for (auto& blck : blockposition) {
				int bx = blck.second.first;
				int by = blck.second.second;
				screen[by * nScreenWidth + bx] = L'O';
			}
			
			if (!bombposition.empty()){
				// vector<int> blkindexes;
				for (auto bp : bombposition) {
					if (bomberman.front().x == bp[0] && bomberman.front().y == bp[1]) {
						bDead = true;
						break;
					}
					/*
					if (!blockposition.empty()) {
						for (auto& blck : blockposition) {
							treature_tmp = 1;
							int bx = blck.second.first;
							int by = blck.second.second;
							swprintf(&screen[5], L"%d == %d %d == %d", bx, bp[0], by, bp[1]);
			
							if (bx == bp[0] && by == bp[1]) {
								treature_tmp = 2;
								if (blck.first % 2 == 0) {
									treature_tmp += 1;
									treature.insert({treature_tmp, {bx, by}});
									screen[by * nScreenWidth + bx] = 65 + blck.first % 2;
								}
								else 
									screen[by * nScreenWidth + bx] = L' ';
							
								blkindexes.push_back(blck.first);
								break;
							}
						}
					}
					*/
				}
			}
			
			bomberman.pop_back();
			
			if (!enemy.empty()) {
				for (auto& e : enemy)
					e.second.first.pop_back();
			}
			
			if(!bombclock.empty()){
				
				for(auto& cp : Checkexplosion) {
					if (bombclock.find(cp.first) != bombclock.end()) {
						if (cp.second == 0) {
							bombclock.erase(cp.first);
							// temp_bombNumber--;
						}
					}
				}
					
				for(auto& bc : bombclock) {
					
					if (!Checkexplosion[bc.first]) continue;
					
					auto clock_now = chrono::system_clock::now();
					px = bc.second.second.first;
					py = bc.second.second.second;
					
					float currentTime = float(chrono::duration_cast <chrono::seconds> (clock_now - bc.second.first).count());
				
					if (currentTime < BombPeriod) {
						screen[py * nScreenWidth + px] = L'p';
						// Checkexplosion = true;
					} 
				}
				
				for(auto& bc : bombclock) {
					
					if (!Checkexplosion[bc.first]) continue;
					
					auto clock_now = chrono::system_clock::now();
					px = bc.second.second.first;
					py = bc.second.second.second;
					
					float currentTime = float(chrono::duration_cast <chrono::seconds> (clock_now - bc.second.first).count());
				
					if (currentTime >= BombPeriod && currentTime < BombPeriod+1) {
					
						// bombfireanimation(screen, px, py, firelength);
						screen[py * nScreenWidth + px] = L'x';
					
						int fireworkblock[4] = {0};
					
						for (int x = 0; x < firelength; x++) {
							if (px + x <= nScreenWidth-2) {
								if (screen[py * nScreenWidth + px + x] != L'*' && fireworkblock[0] == 0) {
									screen[py * nScreenWidth + px + x] = L'x';
									bombposition.push_back({px + x, py});
								} else {
									fireworkblock[0] = 1;
								}
							}
							if (px - x >= 1) {
							if (screen[py * nScreenWidth + px - x] != L'*' && fireworkblock[1] == 0) {
									screen[py * nScreenWidth + px - x] = L'x';
									bombposition.push_back({px - x, py});
								} else {
									fireworkblock[1] = 1;
								}
							}
							if (py + x <= nScreenHeight-2) {
								if (screen[(py + x) * nScreenWidth + px] != L'*' && fireworkblock[2] == 0) {
									screen[(py + x) * nScreenWidth + px] = L'x';
									bombposition.push_back({px, py + x});
								} else {
									fireworkblock[2] = 1;
								}
							}
							if (py - x >= 4) {
								if (screen[(py - x) * nScreenWidth + px] != L'*' && fireworkblock[3] == 0) {
									screen[(py - x)* nScreenWidth + px] = L'x';
									bombposition.push_back({px, py - x});
								} else {
									fireworkblock[3] = 1;
								}
							}
						}
						// Checkexplosion[bc.first] = 0;
					}
				}
				
				
				for(auto& bc : bombclock) {
					
					if (!Checkexplosion[bc.first]) continue;
					
					auto clock_now = chrono::system_clock::now();
					px = bc.second.second.first;
					py = bc.second.second.second;
					
					float currentTime = float(chrono::duration_cast <chrono::seconds> (clock_now - bc.second.first).count());
				
					// Checkexplosion = false;
					
					if (currentTime == BombPeriod+1) {
						// PutBomb = 0;
						
						if (!bombposition.empty()) {
							vector<int> blkindexes;
							
							for (auto& bp : bombposition) {
							if (!blockposition.empty()) {
								for (auto& blck : blockposition) {
									// treature_tmp = 1;
									int bx = blck.second.first;
									int by = blck.second.second;
									// swprintf(&screen[5], L"%d == %d %d == %d", bx, bp[0], by, bp[1]);
			
									if (bx == bp[0] && by == bp[1]) {
										// nScore += 10;
										/*
										if (blck.first % 5 == 0) {
											treature_tmp += 1;
											treature.insert({treature_tmp, {bx, by}});
											screen[by * nScreenWidth + bx] = 65 + blck.first % 10;
										}
										else 
											screen[by * nScreenWidth + bx] = L' ';
										*/
										int findrepeat = 0;
										for (auto& tr : treature) {
											if (tr.second.first == bx && tr.second.second == by) {
												findrepeat = 1;
												break;
											}
										}
										if (findrepeat) break;
										
										/*
										treature_tmp += 1;
										treature.insert({65 + treature_tmp, {bx, by}});
										screen[by * nScreenWidth + bx] = 65 + treature_tmp;
										blkindexes.push_back(blck.first);
										*/
										
										if (blck.first == blkexit-1) {
											targetx = bx;
											targety = by;
											levelexitOpen = true;
											screen[by * nScreenWidth + bx] = L']';
										}
											
										if (blck.first % 60 == 0) {
											treature_tmp = rand() % 4;
											treature.insert({65 + treature_tmp, {bx, by}});
											screen[by * nScreenWidth + bx] = 65 + treature_tmp;
										} else {
											screen[by * nScreenWidth + bx] = L' ';
										}
										blkindexes.push_back(blck.first);
										
										// screen[by * nScreenWidth + bx] = 65;
							
										//blkindexes.push_back(blck.first);
									}
								}
							}
							}
							// int Oriblksize = blockposition.size();
							for (auto& blkindex : blkindexes) {
					            blockposition.erase(blkindex);
					        }
					        // int Reduceblksize = blockposition.size();
						}
						Checkexplosion[bc.first] = 0;
						bombposition.clear();
						// bombclock.erase(bombclock.first);
					}
				}
			}
			
			if (levelexitOpen) {
				screen[targety * nScreenWidth + targetx] = L']';
			}
			
			// int index = 5;
			for (auto& tr : treature) {
				int tx = tr.second.first;
				int ty = tr.second.second;
					
				//swprintf(&screen[index * nScreenWidth + 25], L"treature position %d: (%d, %d) (%d, %d)", tr.first, tx, ty, bomberman.front().x, bomberman.front().y);
				//index++;
				// screen[ty * nScreenWidth + tx] = tr.first;
					
				if (bomberman.front().x == tx && bomberman.front().y == ty) {
					// swprintf(&screen[nScreenWidth + 30], L"clear treature");
					screen[ty * nScreenWidth + tx] = L' ';

					char c = tr.first;
						
					switch (c) {
							case 'A':
								maximumbombNumber += 1;
								// swprintf(&screen[9 * nScreenWidth + 25], L"flag triggered");
								Checkexplosion.insert({maximumbombNumber-1,0});
								nScore += 200;
								break;
							case 'B':
								firelength += 2;
								nScore += 300;
								break;
							case 'C':
								if (nScreenSpeed >= 40)
									nScreenSpeed -= 20;
								else
									nScreenSpeed = 40;
								nScore += 400;
								break;
							case 'D':
								if (BombPeriod >= 1)
									BombPeriod -= 1;
								else
									BombPeriod = 3;
								nScore += 350;
							default:
								break;
					}
					treature.erase(tr.first);
					break;
				} else {
					screen[ty * nScreenWidth + tx] = tr.first;
				}
			}
			
			//swprintf(&screen[nScreenWidth + 5], L"MaximumBombNumber: %d CheckexplosionCount(Checkexplosion)=%d", Checkexplosion.size(), CheckexplosionCount(Checkexplosion));
			//for (int x = 0; x < Checkexplosion.size(); x++)
			//	swprintf(&screen[2 * (x+1) * nScreenWidth + 5], L"Checkexplosion[%d]: %d", x, Checkexplosion[x]);
			
			swprintf(&screen[nScreenWidth + 5], L"	 				BombMan			 								 LEVEL: %d 		SCORE: %d 		LIVES: %d", level, nScore, lives);
			
			screen[bomberman.front().y * nScreenWidth + bomberman.front().x] = L'@';
			
			if (!enemy.empty()) {
				int enemykill = 0;
				for (auto &e : enemy) {
					
					screen[e.second.first.front().y * nScreenWidth + e.second.first.front().x] = enemypattern[e.first];
					
					for (auto& bp : bombposition) {
						if (e.second.first.front().x == bp[0] && e.second.first.front().y == bp[1]) {
							enemy.erase(e.first);
							nScore += 100;
							enemykill = 1;
							break;
						}
						if (enemykill)
							break;
					}
					
					if (enemykill)
						break;
				}
			}
			
			if (!enemy.empty())	{
				for (auto &e : enemy) {	
					if (bomberman.front().x == e.second.first.front().x && bomberman.front().y == e.second.first.front().y) {
						bDead = true;
						break;
					}
				}
			}
			
			if (bDead)
			    swprintf(&screen[15 * nScreenWidth + 40], L"    PRESS 'SPACE' TO PLAY AGAIN    ");
			
			if (bomberman.front().x == targetx && bomberman.front().y == targety)
				clearlevel = true;
			
			if (bKeyPause) {
				for (int x = 0; x < nScreenWidth*nScreenHeight; x++) screen[x] = 0;
				swprintf(&screen[15 * nScreenWidth + 40], L"    		PAUSE				   ");
				swprintf(&screen[17 * nScreenWidth + 40], L"    		%d				   ", (0x8000 & GetAsyncKeyState((unsigned char)('\x50'))));
				system("pause");
				/*
				while ((0x8000 & GetAsyncKeyState((unsigned char)('\x50'))) == 0) {
					swprintf(&screen[15 * nScreenWidth + 40], L"    		PAUSE				   ");
					swprintf(&screen[17 * nScreenWidth + 40], L"    		%d				   ", (0x8000 & GetAsyncKeyState((unsigned char)('\x50'))));
				};
				*/
			}
			
				
			// Display Frame
			WriteConsoleOutputCharacterW(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
		}	
		
		if (clearlevel) {
			for (int x = 0; x < nScreenWidth*nScreenHeight; x++) screen[x] = 0;
			
			swprintf(&screen[15 * nScreenWidth + 40], L"LEVEL COMPLETE");
			WriteConsoleOutputCharacterW(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
			
			for (int second = 5; second >= 0; second--) {
				this_thread::sleep_for(chrono::seconds(1));
				swprintf(&screen[7 * nScreenWidth + 40], 22, L"Next level will begin");
				swprintf(&screen[8 * nScreenWidth + 40], 20, L"in %d seconds...", second);
				WriteConsoleOutputCharacterW(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
			}	
			
			for (int x = 0; x < nScreenWidth*nScreenHeight; x++) {
				screen[x] = 0;
			}
			clearlevel = false;
			bombclock.clear();
			//temp_bombNumber = 0;
			treature.clear();
			blockposition.clear();
			for(auto& orib : Oriblockposition) {
				blockposition.insert({orib.first, {orib.second.first, orib.second.second}});
			}
			Checkexplosion.clear();
			for (int x=0; x<maximumbombNumber; x++){
				Checkexplosion.insert({x,0});
			}
			level++;
			targetx = 0;
			targety = 0;
			levelexitOpen = false;
			// bomberman.clear();
			// bomberman.push_back({bombermanOriX, bombermanOriY});
		} else {
			while ((0x8000 & GetAsyncKeyState((unsigned char)('\x20'))) == 0);
			bombclock.clear();
			//temp_bombNumber = 0;
			nScore = 0;
			firelength = 5;
			nScreenSpeed = 100;
			maximumbombNumber = 1;
			treature.clear();
			blockposition.clear();
			for(auto& orib : Oriblockposition) {
				blockposition.insert({orib.first, {orib.second.first, orib.second.second}});
			}
			Checkexplosion.clear();
			for (int x=0; x<maximumbombNumber; x++){
				Checkexplosion.insert({x,0});
			}
			lives--;
			targetx = 0;
			targety = 0;
			BombPeriod = 5;
			levelexitOpen = false;
			// bomberman.clear();
			// bomberman.push_back({bombermanOriX, bombermanOriY});
		}
	}
	return 0;
}
