#include <stdio.h>
#include <stdlib.h> //system()
#include <Windows.h> //_kbhit()
#include <conio.h>

#define	DINOSAUR_DISTANCE_FROM_TOP_Y	12
#define TREE_DISTANCE_FROM_LEFT_X		90
#define TREE_DISTANCE_FROM_TOP_Y		20

void InitConsoleConfig();
int GetKeyDown();
void DrawDinosaur(int);
void DrawTree(int);
void GotoXY(int, int);
void viewScore(int);
void setSpeed(int, int&);

// ������ ����ó �ٵ� ������...?
// yellowjigi@gmail.com
//010 2087 6411
//������ ���� ��������
//������ �ױ�
//���� ǥ���ϱ�

int main(int argc, char* argv[]) {

	InitConsoleConfig(); //�ܼ�â ũ��

	bool jumping = false; //jump������
	bool walking = true; //�Ȱ��ִ���
	int dinosaurY = DINOSAUR_DISTANCE_FROM_TOP_Y; //���� ����
	int treeX = TREE_DISTANCE_FROM_LEFT_X; //������ ��ǥ

	const int gravity = 3;
	int speed = 3; //Ʈ���� �ٰ����� �ӵ�
	int score = 0; //���� 
	bool alive = true;

	while (true) {
		if (GetKeyDown() == ' ' && walking) { // �����̽��ٰ� ���ȴٸ� && ���� �پ��ִٸ�
			jumping = true; //�����ض�
			walking = false;
		}

		if (jumping) { //�������̸� 3�� �ö�
			dinosaurY = dinosaurY - 3;
		}
		else { //�ϰ����̸� 3�� ������
			dinosaurY = dinosaurY + 3;
		}

		if (dinosaurY <= 0) { // �ϴ� ���� ���� �ʰ� ����⿡���� 
			dinosaurY = 0;
			jumping = false; //�׸� ����
		}

		if (dinosaurY >= DINOSAUR_DISTANCE_FROM_TOP_Y) { //�������� ������ �ʰ� 
			dinosaurY = DINOSAUR_DISTANCE_FROM_TOP_Y;
			walking = true; //�׸� �ϰ�
		}

		if (treeX < 3) {
			if (DINOSAUR_DISTANCE_FROM_TOP_Y - dinosaurY < 2) {
				alive = false;
			}
		}
		if (3 <= treeX && treeX <= 12) {
			if (DINOSAUR_DISTANCE_FROM_TOP_Y - dinosaurY < 6) {
				alive = false;
			}
		}

		DrawDinosaur(dinosaurY);
		DrawTree(treeX);
		viewScore(score);
		Sleep(60); // 60�� �ѹ��� ������

		if (alive) {
			system("cls");
		}
		else {
			return 0;
		}

		treeX = treeX - speed; //Ʈ���� �������� speedĭ�� ��

		if (treeX <= 0) { //Ʈ���� ������� �ٽ� Ʈ�� ��Ÿ����
			treeX = TREE_DISTANCE_FROM_LEFT_X;
			score++;
			setSpeed(score, speed);
		}
	}
}

void viewScore(int score) {
	GotoXY(80, 3);
	printf("score : %d\n", score);
}

void setSpeed(int score, int& speed) {
	if (score > 0 && score % 3 == 0) {
		speed++;
	}
}

void InitConsoleConfig() {
	system("mode con:cols=100 lines=25");
}

int GetKeyDown() {
	if (_kbhit()) { // ����ڰ� key���� ������ �Է� ��Ʈ���� ����ڰ� ���� key���� ���� (����)
		return _getch(); // get character
	}

	return 0;
}

void DrawDinosaur(int dinosaurY) {
	static bool legDraw = true;
	GotoXY(0, dinosaurY);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	//system("color 2D");
	printf("        &&&&&&& \n");
	printf("       && &&&&&&\n");
	printf("       &&&&&&&&&\n");
	//system("color 6C");
	printf("&      &&&      \n");
	printf("&&     &&&&&&&  \n");
	printf("&&&   &&&&&     \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
	printf(" &&  &&&&&&&&&& \n");
	printf(" &&&&&&&&&&&    \n");
	printf("  &&&&&&&&&&    \n");
	printf("    &&&&&&&&    \n");
	printf("     &&&&&&     \n");

	if (legDraw) {
		printf("     &    &&&     \n");
		printf("     &&           ");
		legDraw = false;
	}

	else {
		printf("     &&&  &       \n");
		printf("          &&      ");
		legDraw = true;
	}
}

void DrawTree(int treeX) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	GotoXY(treeX, TREE_DISTANCE_FROM_TOP_Y);
	printf("$$$$");
	GotoXY(treeX, TREE_DISTANCE_FROM_TOP_Y + 1);
	printf(" $$");
	GotoXY(treeX, TREE_DISTANCE_FROM_TOP_Y + 2);
	printf(" $$");
	GotoXY(treeX, TREE_DISTANCE_FROM_TOP_Y + 3);
	printf(" $$");
	GotoXY(treeX, TREE_DISTANCE_FROM_TOP_Y + 4);
	printf(" $$");
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}