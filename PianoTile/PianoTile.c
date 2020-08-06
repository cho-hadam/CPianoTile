#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <windows.h>

//�Լ� ���� ����
int menu(void);
void start(void);
void manual(void);
void show_rectangle(void);
void show_ready(void);
int get_key(void);
void show_score(void);
void print_block(int x, int y);
void remove_block(int x, int y);
void game_over(void);
void rank(void);
void save_score(void);
void get_name(void);

void setConsole(void);
void setCursor(int v);
void gotoxy(int x, int y);
void right_left_move(char key, int* x, int x_min, int x_max);

//���� ����
int score;
int fail;
int step = 1;
char name[20];

int main(void) {
	setConsole();

	int m;
	while (m = menu()) {
		switch (m) {
		case 10: //����
			get_name();
			start();
			break;
		case 13: // ���� ���
			manual();
			break;
		case 16: //��ŷ
			rank();
			break;
		case 19: //����
			exit(1);
		}
	}

	return 0;
}

//�޴� ȭ��
int menu(void) {
	int x = 48, y = 5;
	char menu;

	system("cls");
	gotoxy(x, y);
	printf("  �ǾƳ� Ÿ�� ���� ");
	gotoxy(x, y += 5); int y_min = y;
	printf("        ����");
	gotoxy(x, y += 3);
	printf("     ���� ��� ");
	gotoxy(x, y += 3);
	printf("        ��ŷ ");
	gotoxy(x, y += 3);
	printf("        ���� ");
	int y_max = y;

	y = y_min;
	do {
		gotoxy(x, y);
		printf("��");
		menu = _getch();
		gotoxy(x, y);
		printf("  ");
		switch (menu) { //���� Ű
		case 72: //���� ���� Ű
			y -= 3;
			if (y < y_min) y = y_max;
			break;
		case 80: //�Ʒ��� ���� Ű
			y += 3;
			if (y > y_max) y = y_min;
			break;
		}
	} while (menu != 13);

	return y;
}
void get_name(void) {
	system("cls");
	gotoxy(48, 18);
	printf("�̸��� �Է��ϼ���.");
	gotoxy(48, 20);
	printf(">> ");
	scanf_s("%s", name, 20); fflush(stdin);
}
//����
void start(void) {
	system("cls");

	char c;
	int x = 10, y = 28;
	int rnd = 0, tile_y = 5, tile_x[4] = { x, x + 15, x + 30, x + 45 };
	srand(time(NULL));

	score = 0; fail = 0;
	int delay = 40; //�⺻ ����

	int x_min = x, x_max = x + (14 * 3 + 3);
	system("cls");
	show_rectangle();
	show_ready();
	while ((c = get_key()) != 27) {
		show_score();
		print_block(x, y);

		print_block(tile_x[rnd], tile_y);
		Sleep(delay);
		remove_block(tile_x[rnd], tile_y);
		if (tile_y < 24) {
			tile_y += 1;
		}
		else {
			if (tile_x[rnd] == x) {
				score += 100;
			}
			else {
				score -= 50;
				fail += 1;
				if (fail == 5) {
					game_over();
					break;
				}
			}
			if (score == 500) {
				delay = 30; //2�ܰ�
				step = 2;
			}
			else if (score == 1500) {
				delay = 20;
				step = 3;
			}
			else if (score == 3000) {
				delay = 10;
				step = 4;
			}
			else if (score == 5000) {
				delay = 5;
				step = 5;
			}
			tile_y = 5;
			rnd = rand() % 4;
		}

		remove_block(x, y);
		right_left_move(c, &x, x_min, x_max);
	}
	gotoxy(8, 35);
	printf(">> �ƹ� Ű�� ������ �޴��� ���ư��ϴ�. ");
	_getch();
	save_score();
}
int get_key(void) {
	if (_kbhit()) {
		return _getch();
	}
	return 1;
}
void right_left_move(char key, int* x, int x_min, int x_max) {
	switch (key) { //���� Ű
	case 75: //���� ���� Ű
		*x -= 15;
		if (*x < x_min) *x = x_min;
		break;
	case 77: //������ ���� Ű
		*x += 15;
		if (*x > x_max) *x = x_max;
		break;
	}
}
void print_block(int x, int y) {
	gotoxy(x, y);
	printf("��������");
	gotoxy(x, y + 1);
	printf("��������");
	gotoxy(x, y + 2);
	printf("��������");
}
void remove_block(int x, int y) {
	gotoxy(x, y);
	printf("              ");
	gotoxy(x, y + 1);
	printf("              ");
	gotoxy(x, y + 2);
	printf("              ");
}
//���簢�� �׸���
void show_rectangle(void) {
	int i, j, k;
	int x = 8, y = 4;
	int w = 30, h = 26;

	gotoxy(x, y);
	printf("��");
	for (i = 1; i <= w; i++) {
		printf("��");
	}
	printf("��");
	for (i = 1; i <= h; i++) {
		gotoxy(x, y + i);
		printf("��");
		for (j = 1; j <= w; j++) {
			printf("  ");
		}
		printf("\b��");
		if (i == h - 3) {
			gotoxy(x, y + i);
			printf("��");
			for (k = 1; k <= w; k++) {
				printf("��");
			}
			printf("��");
		}
	}
	gotoxy(x, y + i);
	printf("��");
	for (j = 1; j <= w; j++) {
		printf("��");
	}
	printf("��");
}
//�غ� ȭ��
void show_ready(void) {
	int x = 8, y = 35;
	gotoxy(x, y);
	printf(">> �ƹ� Ű�� ������ �����մϴ�. ");
	_getch();
	gotoxy(x, y);
	printf("                                  ");
}
void game_over(void) {
	system("cls");
	int x = 55, y = 20;
	gotoxy(x, y);
	printf("GAME OVER"); Sleep(2000);
}
void save_score(void) {
	FILE* fp;
	char* file = "score.txt";
	fopen_s(&fp, file, "a");
	fprintf(fp, "%s %d\n", name, score);
	fclose(fp);
}
//���� ���
void show_score(void) {
	int x = 80, y = 5;
	gotoxy(x, y);
	printf("%d�ܰ�", step);
	gotoxy(x, y + 3);
	printf("����   %5d", score);
	gotoxy(x, y + 5);
	printf("����   %5d", fail);
	gotoxy(x, y + 8);
	printf("�̵�   �� ��");
	gotoxy(x, y + 10);
	printf("����   Esc");
}
//���
void manual(void) {
	int x = 65, y = 5;

	system("cls");

	print_block(x-50, y);

	gotoxy(x, y);
	printf("   �� ĭ�� �������� Ÿ�ϰ� ���� ��ġ��");
	y += 2;

	gotoxy(x - 25, y);
	printf("%d�ܰ�", step);
	gotoxy(x - 25, y + 3);
	printf("����   %5d", score);
	gotoxy(x - 25, y + 5);
	printf("����   %5d", fail);
	gotoxy(x - 25, y + 8);
	printf("�̵�   �� ��");
	gotoxy(x - 25, y + 10);
	printf("����   Esc");

	gotoxy(x, y);
	printf("           ���� ������ ������");
	y += 2;
	gotoxy(x, y);
	printf("        ������ 100���� �ö󰩴ϴ�.");
	y += 2;

	gotoxy(x - 44, y - 1);
	printf("��");
	gotoxy(x - 44, y);
	printf("��");

	gotoxy(x, y);
	printf("        ������ ��� 50�� �����Ǹ�");
	y += 2;
	gotoxy(x, y);
	printf("     5�� ������ ��� ������ ����ǰ�");
	y += 2;
	gotoxy(x, y);
	printf("           ������ ��ϵ˴ϴ�.");
	y += 4;

	print_block(x - 50, y-1);
	gotoxy(x - 55, y); printf("��");
	gotoxy(x - 34, y); printf("��");

	gotoxy(x, y);
	printf("    ������ ���� ���� Ÿ���� ��������");
	y += 2;
	gotoxy(x, y);
	printf("          �ӵ��� �������ϴ�.");
	y += 5;
	gotoxy(x, y);
	printf("        ���� �ٷ� 1���Ϸ� GO GO!");
	gotoxy(x-25, 35);
	printf(">> �ƹ� Ű�� ������ �޴��� �̵��մϴ�. ");
	_getch();

	menu();
}

// ��ŷ
void rank(void) {
	FILE* fp;
	char* file = "score.txt";
	fopen_s(&fp, file, "r");
	char s_name[100][20], t_name[100][20];
	int s_score[100]; //100�� ���.. ���� �Ҵ� �˾ƺ���
	int x = 47, y = 5;
	int count = 0, i, j, temp;
	system("cls");
	gotoxy(x, y);
	printf("          ��ŷ");
	y += 2;
	gotoxy(x, y);
	printf("�̸�                ����");
	y += 4;

	if (fp == NULL) {
		gotoxy(40, 35);
		printf(">> �ƹ� Ű�� ������ �޴��� �̵��մϴ�.");
		_getch();

		menu();
	}
	else {
		while (!feof(fp)) {
			fscanf_s(fp, "%s %d\n", s_name[count], 20, &s_score[count]);
			count++;
		}
		fclose(fp);
		for (i = 0; i < count - 1; i++) {
			for (j = i + 1; j < count; j++) {
				if (s_score[i] < s_score[j]) {
					temp = s_score[i];
					s_score[i] = s_score[j];
					s_score[j] = temp;

					strcpy_s(t_name[i], 19, s_name[i]);
					strcpy_s(s_name[i], 19, s_name[j]);
					strcpy_s(s_name[j], 19, t_name[i]);
				}
			}
		}
		int p;
		if (count < 10) {
			p = count;
		}
		else {
			p = 10;
		}

		for (i = 0; i < p; i++) {
			gotoxy(x, y);
			printf("%s", s_name[i]);
			gotoxy(x + 20, y);
			printf("%5d", s_score[i]);
			y += 2;
		}

		gotoxy(40, 35);
		printf(">> �ƹ� Ű�� ������ �޴��� �̵��մϴ�. ");
		_getch();

		menu();
	}
}

//�ܼ� ����
void setConsole(void) {
	system("mode con:cols=120 lines=40");
	setCursor(0); //Ŀ�� �����
	system("title Piano Tiles Game");
	system("cls");
}
void setCursor(int v) {
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = v;
	cursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
//�ܼ� ��ǥ ����
void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}