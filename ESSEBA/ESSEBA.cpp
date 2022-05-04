// CODICE SVILUPPATO DA RICCARDO TRONCONI
﻿
#include <windows.h>
#include <ctime>
#include <iostream>
using namespace std;

constexpr auto W = 20;
constexpr auto H = 20;
constexpr auto bordi = 0;
constexpr auto V = 3;

char mappa[H][W] = { '.' };
char vita[V] = { '@' };

//riempire le vite
int full() {
	for (int i = 0; i < V; i++) {
		vita[i] = '@';
		cout << " ";
	}
	return 0;
}


//funzione per ripristinare la console
void clear() {
	COORD topLeft = { 0,0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

//stampare la mappa senza entità
void print_mappa() {
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			mappa[i][j] = '.';
			cout << mappa[i][j];
		}
		cout << endl;
	}
}

//stampare robottino + mappa
void print_robottino(int y, int x, char robottino) {
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			mappa[i][j] = '.';
			if (i == x && j == y) {
				mappa[i][j] = robottino;
			}
			cout << mappa[i][j];
		}
		cout << endl;
	}
}

// controllo dei muri per robottino
void controllo(int& robottino_x, int& robottino_y) {
	if (robottino_y == H) {
		robottino_y = H - 1;
	}
	else if (robottino_y == bordi - 1) {
		robottino_y = bordi;
	}

	if (robottino_x == W) {
		robottino_x = bordi;
	}
	else if (robottino_x == bordi - 1) {
		robottino_x = W - 1;
	}
}

//controllo nemico
void controllo_enemy(int& x1, int& y1, int& x2, int& y2, int& x3, int& y3) {
	if (y1 == H || y2 == H || y3 == H) {
		y1 = H - 1;
		y2 = H - 1;
		y3 = H - 1;
	}
	else if (y1 == bordi - 1 || y2 == bordi - 1 || y3 == bordi - 1) {
		y1 = bordi;
		y2 = bordi;
		y3 = bordi;
	}

	if (x1 == W || x2 == W || x3 == W) {
		x1 = bordi;
		x2 = bordi;
		x3 = bordi;
	}
	else if (x1 == bordi - 1 || x2 == bordi - 1 || x3 == bordi - 1) {
		x1 = W - 1;
		x2 = W - 1;
		x3 = W - 1;
	}
}

//stampare un nemico + mappa + robottino
void spawn_entity(char enemy, int& robottino_y, int& robottino_x, char robottino, int x1, int y1, int x2, int y2, int x3, int y3) {
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			mappa[i][j] = '.';
			if (i == x1 && j == y1 || i == x2 && j == y2 || i == x3 && j == y3) {
				mappa[i][j] = enemy;
			}
			else if (i == robottino_x && j == robottino_y) {
				mappa[i][j] = robottino;
			}
			cout << mappa[i][j];
		}
		cout << endl;
	}
}

//movimento casusale nemico
void move_enemy(int& x1, int& y1, int& x2, int& y2, int& x3, int& y3) {
	int siOno = rand() % 2 + 1;
	int check = rand() % 4 + 1;

	controllo_enemy(x1, y1, x2, y2, x3, y3);
	if (siOno == 1) {
		if (check == 1) {
			x1++;
			y2--;
			y3++;
		}
		else if (check == 2) {
			y1++;
			x2--;
			x1++;
		}
		else if (check == 3) {
			x1--;
			y2++;
			y3--;
		}
		else if (check == 4) {
			y1--;
			x2++;
			x3--;
		}
	}
}

//controllo vittoria
bool win(int& robottino_x, int& robottino_y) {
	if (robottino_y == H - 1) {
		cout << endl << "YOU WIN !!";
		return true;
	}
	else {
		return false;
	}
}

//controllo delle vite del personaggio
int vite(int& x1, int& y1, int& x2, int& y2, int& x3, int& y3, int& robottino_x, int& robottino_y, int& contatore_vite) {
	if (x1 == robottino_y && y1 == robottino_x || x2 == robottino_y && y2 == robottino_x) {
		vita[contatore_vite] = '#';
		contatore_vite++;
		cout << endl << "-1 vite rimanenti !" << endl;
		return true;
	}
	else {
		return false;
	}
}

//stampo delle vite
int check_vite() {
	cout << endl << "vite rimanenti = ";
	for (int i = 0; i < 3; i++) {
		cout << vita[i];
	}
	return 0;
}

//controllo sconfitta
bool game_over(int& contatore_vite) {
	if (contatore_vite == 3) {
		cout << endl << "GAME OVER" << endl;
		return true;
	}
	else {
		return false;
	}
}

int main() {

	srand(time(NULL));
	char commando;
	char robottino = '@';
	char enemy = '#';
	int contatore_vite = 0;
	int siOno;
	full();

	do {
		int robottino_y = 0, robottino_x = 9;
		int x1 = rand() % 20 + 1, y1 = rand() % 20 + 1;
		int x2 = rand() % 20 + 1, y2 = rand() % 20 + 1;
		int x3 = rand() % 20 + 1, y3 = rand() % 20 + 1;
		bool running = true;

		clear();
		spawn_entity(enemy, robottino_x, robottino_y, robottino, x1, y1, x2, y2, x3, y3);
		game_over(contatore_vite);


		do {
			cout << endl;
			vite(x1, y1, x2, y2, x3, y3, robottino_x, robottino_y, contatore_vite);
			game_over(contatore_vite);

			cout << endl << endl << "INSERISCI COMANDO: ";
			cin >> commando;

			if (commando == 'w') {
				clear();
				robottino_y--;
				controllo(robottino_x, robottino_y);
				move_enemy(x1, y1, x2, y2, x3, y3);
				spawn_entity(enemy, robottino_x, robottino_y, robottino, x1, y1, x2, y2, x3, y3);
			}
			else if (commando == 's') {
				clear();
				robottino_y++;
				controllo(robottino_x, robottino_y);
				move_enemy(x1, y1, x2, y2, x3, y3);
				spawn_entity(enemy, robottino_x, robottino_y, robottino, x1, y1, x2, y2, x3, y3);
			}
			else if (commando == 'd') {
				clear();
				robottino_x++;
				controllo(robottino_x, robottino_y);
				move_enemy(x1, y1, x2, y2, x3, y3);
				spawn_entity(enemy, robottino_x, robottino_y, robottino, x1, y1, x2, y2, x3, y3);
			}
			else if (commando == 'a') {
				clear();
				robottino_x--;
				controllo(robottino_x, robottino_y);
				move_enemy(x1, y1, x2, y2, x3, y3);
				spawn_entity(enemy, robottino_x, robottino_y, robottino, x1, y1, x2, y2, x3, y3);
			}
			else if (commando == '0') {
				running = false;
			}
			if (game_over(contatore_vite) != false) {
				running = false;
			}
			if (win(robottino_x, robottino_y) == true) {
				running = false;
			}
			check_vite();

		} while (running == true);
		clear();
		win(robottino_x, robottino_y);
		cout << endl << endl << "THE END!";
		cout << endl << endl << "VUOI GIOCARE DI NUOVO?" << endl << endl
			<< "1) SI" << endl << "2) NO" << endl << "seleziona opzione: ";
		cin >> siOno;
		if (siOno != 1 && siOno != 2) {
			do {
				cout << endl << "ERRORE ! " << endl << "E' PREGATO DI INSERIRE UN NUMERO TRA 1 E 2" << endl;
				cout << endl << endl << "VUOI GIOCARE DI NUOVO?" << endl << endl
					<< "1) SI" << endl << "2) NO" << endl << "seleziona opzione: ";
				cin >> siOno;
			} while (siOno != 1 && siOno != 2);
		}
	} while (siOno == 1);
	return 0;
}
