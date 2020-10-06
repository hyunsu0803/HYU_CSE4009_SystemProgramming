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

// 조교님 연락처 근데 성함이...?
// yellowjigi@gmail.com
//010 2087 6411
//나무가 점점 빨라지기
//닿으면 죽기
//점수 표시하기

int main(int argc, char* argv[]) {

	InitConsoleConfig(); //콘솔창 크기

	bool jumping = false; //jump중인지
	bool walking = true; //걷고있는지
	int dinosaurY = DINOSAUR_DISTANCE_FROM_TOP_Y; //공룡 높이
	int treeX = TREE_DISTANCE_FROM_LEFT_X; //나무의 좌표

	const int gravity = 3;
	int speed = 3; //트리가 다가오는 속도
	int score = 0; //점수 
	bool alive = true;

	while (true) {
		if (GetKeyDown() == ' ' && walking) { // 스페이스바가 눌렸다면 && 땅에 붙어있다면
			jumping = true; //점프해라
			walking = false;
		}

		if (jumping) { //점프중이면 3씩 올라감
			dinosaurY = dinosaurY - 3;
		}
		else { //하강중이면 3씩 내려옴
			dinosaurY = dinosaurY + 3;
		}

		if (dinosaurY <= 0) { // 하늘 위로 솟지 않게 꼭대기에서는 
			dinosaurY = 0;
			jumping = false; //그만 점프
		}

		if (dinosaurY >= DINOSAUR_DISTANCE_FROM_TOP_Y) { //땅밑으로 꺼지지 않게 
			dinosaurY = DINOSAUR_DISTANCE_FROM_TOP_Y;
			walking = true; //그만 하강
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
		Sleep(60); // 60에 한번씩 움직임

		if (alive) {
			system("cls");
		}
		else {
			return 0;
		}

		treeX = treeX - speed; //트리는 왼쪽으로 speed칸씩 옴

		if (treeX <= 0) { //트리가 사라지면 다시 트리 나타나게
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
	if (_kbhit()) { // 사용자가 key값을 누르면 입력 스트림에 사용자가 누른 key값을 저장 (버퍼)
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