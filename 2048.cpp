#include<iostream>
#include<time.h>
#include<conio.h>
#include<cassert>
#include<iomanip>
using namespace std;

constexpr int LENGTH = 4;
constexpr int SCORE_PER_TIME = 10;
enum Direction { UP, DOWN, LEFT, RIGHT };

class Game_2048 {
private:
	int table[LENGTH][LENGTH];
public:
	Game_2048();
	Direction Get_direction();
	Direction Int2Dir(int);
	int Move(Direction);
	void Print_table();
	bool is_survive();
	int Run_once();
	void Add_digit();
};

int main() {
	srand(time(NULL));
	Game_2048 game;
	int score = 0;
	game.Print_table();
	while (game.is_survive()) {
		score += game.Run_once();
		score -= 2;
	}
	cout << "Your Score is: " << score << endl;
	cout << "Input q to exit" << endl;
	while (getchar()!='q');
	return 0;
}
Game_2048::Game_2048() {
	for (int i = 0; i < LENGTH; ++i)
		for (int j = 0; j < LENGTH; ++j)
			table[i][j] = 0;
	int i, j;
	int cnt = 0;
	while (cnt != 2) {
		i = rand() % LENGTH;
		j = rand() % LENGTH;
		if (table[i][j] == 0) {
			table[i][j] = 2;
			cnt++;
		}
	}
}

Direction Game_2048::Int2Dir(int n) {
	switch (n)
	{
	case 72:
		return UP;
	case 75:
		return LEFT;
	case 77:
		return RIGHT;
	case 80:
		return DOWN;
	default:
		return UP;
	}
}
Direction Game_2048::Get_direction() {
	if (_getch()) {
		Direction dir = Int2Dir(_getch());
	}
	else
		return UP;
}
int Game_2048::Move(Direction dir) {
	int tmp;
	int cnt_combine = 0;
	switch (dir)
	{
	case UP:
		for (int j = 0; j < LENGTH; ++j)
			for (int i = 1; i < LENGTH; ++i)
				if (table[i][j]) {
					tmp = i;
					while (tmp > 0 && table[tmp - 1][j] == 0) {
						table[tmp - 1][j] = table[tmp][j];
						table[tmp][j] = 0;
						--tmp;
					}
					if (table[tmp - 1][j] == table[tmp][j]) {
						table[tmp - 1][j] *= 2;
						table[tmp][j] = 0;
						cnt_combine++;
					}
				}

		break;
	case DOWN:
		for (int j = 0; j < LENGTH; ++j)
			for (int i = LENGTH - 2; i >= 0; --i)
				if (table[i][j]) {
					tmp = i;
					while (tmp < LENGTH - 1 && table[tmp + 1][j] == 0) {
						table[tmp + 1][j] = table[tmp][j];
						table[tmp][j] = 0;
						++tmp;
					}
					if (table[tmp + 1][j] == table[tmp][j]) {
						table[tmp + 1][j] *= 2;
						table[tmp][j] = 0;
						cnt_combine++;
					}
				}
		break;
	case LEFT:
		for (int i = 0; i < LENGTH; ++i)
			for (int j = 1; j < LENGTH; ++j)
				if (table[i][j]) {
					tmp = j;
					while (tmp > 0 && table[i][tmp - 1] == 0) {
						table[i][tmp - 1] = table[i][tmp];
						table[i][tmp] = 0;
						--tmp;
					}
					if (table[i][tmp - 1] == table[i][tmp]) {
						table[i][tmp - 1] *= 2;
						table[i][tmp] = 0;
						cnt_combine++;
					}
				}
		break;
	case RIGHT:
		for (int i = 0; i < LENGTH; ++i)
			for (int j = LENGTH - 2; j >= 0; --j)
				if (table[i][j]) {
					tmp = j;
					while (tmp < LENGTH - 1 && table[i][tmp + 1] == 0) {
						table[i][tmp + 1] = table[i][tmp];
						table[i][tmp] = 0;
						++tmp;
					}
					if (table[i][tmp + 1] == table[i][tmp]) {
						table[i][tmp + 1] *= 2;
						table[i][tmp] = 0;
						cnt_combine++;
					}
				}
		break;
	default:
		break;
	}
	return cnt_combine * SCORE_PER_TIME;
}

void Game_2048::Print_table() {
	for (int i = 0; i < LENGTH; ++i) {
		for (int j = 0; j < LENGTH; ++j) {
			cout << setw(3) << table[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

int Game_2048::Run_once() {
	int score;
	Direction dir = Get_direction();
	score = Move(dir);
	Add_digit();
	system("cls");
	Print_table();
	return score;
}

void Game_2048::Add_digit() {

	bool isnot_full = false;
	for (int i = 0; i < LENGTH; ++i)
		for (int j = 0; j < LENGTH; ++j)
			if (!table[i][j])isnot_full = true;
	if (!isnot_full)
		return;

	int i, j, n;
	n = (rand() % 2 + 1) * 2;
	while (true) {
		i = rand() % LENGTH;
		j = rand() % LENGTH;
		if (!table[i][j]) {
			table[i][j] = n;
			break;
		}
	}
}

bool Game_2048::is_survive() {
	for (int i = 0; i < LENGTH; ++i)
		for (int j = 0; j < LENGTH; ++j)
			if (table[i][j] == 0)
				return true;

	for (int i = 0; i < LENGTH; ++i) {
		for (int j = 0; j < LENGTH - 1; ++j) {
			if (table[i][j] == table[i][j + 1])
				return true;
			if (table[j][i] == table[j + 1][i])
				return true;
		}
	}

	
	return false;
}