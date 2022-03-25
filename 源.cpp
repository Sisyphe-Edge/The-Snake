#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define BLOCK_SIZE 20
#define HEIGHT 30
#define WIDTH 40

bool start = 0;
int mode = 0;
int Blocks[HEIGHT][WIDTH] = { 0 };
int food_i, food_j;
int isFailure = 0;
char moveDirection;

void menu()
{
	initgraph(800, 600);
	setbkcolor(RGB(0, 0, 0));
	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 255, 255));
	settextstyle(100, 0, _T("����"));
	outtextxy(240, 40, _T("̰����"));
	settextstyle(30, 0, _T("����"));
	outtextxy(310, 160, _T("�ո��ѡģʽ"));
	settextstyle(60, 0, _T("����"));
	outtextxy(280, 250, _T("����ģʽ"));
	settextstyle(60, 0, _T("����"));
	outtextxy(280, 330, _T("����ģʽ"));
	settextstyle(60, 0, _T("����"));
	outtextxy(280, 410, _T("����ģʽ"));
}

void choose()
{
	int chs = 1;
	settextstyle(60, 0, _T("����"));
	outtextxy(220, 250, _T("��"));
	char judge = '0';
	while (judge != ' ')
	{
		judge = _getch();
		if (judge == 'w' && chs != 1)
		{
			system("cls");
			menu();
			chs--;
		}
		if (judge == 's' && chs != 3)
		{
			system("cls");
			menu();
			chs++;
		}
		if (chs == 1)
		{
			settextstyle(60, 0, _T("����"));
			outtextxy(220, 250, _T("��"));
		}
		if (chs == 2)
		{
			settextstyle(60, 0, _T("����"));
			outtextxy(220, 330, _T("��"));
		}
		if (chs == 3)
		{
			settextstyle(60, 0, _T("����"));
			outtextxy(220, 410, _T("��"));
		}
		if (judge == ' ')
		{
			if (chs == 1)
			{
				mode = 1;
			}
			if (chs == 2)
			{
				mode = 2;
			}
			if (chs == 3)
			{
				mode = 3;
			}
		}
	}
	FlushBatchDraw();
}

void moveSnake()
{
	//������ά���飬�����ּ�1����¼���ƶ�ǰ��λ��
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (Blocks[i][j] > 0)
				Blocks[i][j] += 1;
		}
	}
	int oldTail_i = 0, oldTail_j = 0, oldHead_i = 0, oldHead_j = 0;
	int max = 0;
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{

			if (max < Blocks[i][j])
			{
				max = Blocks[i][j];
				oldTail_i = i;
				oldTail_j = j;
			}
			if (Blocks[i][j] == 2)
			{
				oldHead_i = i;
				oldHead_j = j;
			}
		}
	}
	//�����ߵ�λ��
	int newHead_i = oldHead_i;
	int newHead_j = oldHead_j;
	if (moveDirection == 'w')
		newHead_i -= 1;
	else if (moveDirection == 's')
		newHead_i += 1;
	else if (moveDirection == 'a')
		newHead_j -= 1;
	else if (moveDirection == 'd')
		newHead_j += 1;


	//ʵ�ִ�ǽ����һ�˴��������������ߵ��ƶ�
	if (newHead_i >= HEIGHT)
	{
		newHead_i = 0;
	}
	else if (newHead_i < 0)
	{
		newHead_i = HEIGHT - 1;
	}
	else if (newHead_j >= WIDTH)
		newHead_j = 0;
	else if (newHead_j < 0)
		newHead_j = WIDTH - 1;

	if (Blocks[newHead_i][newHead_j] > 0)
	{
		isFailure = 1;
		return;
	}

	//������ͷ��λ�� Ҫ���ж���ͷλ���Ƿ���ȷ֮��
	Blocks[newHead_i][newHead_j] = 1;

	//�Է�
	if (newHead_i == food_i && newHead_j == food_j)
	{
		food_i = rand() % (HEIGHT - 5) + 2;
		food_j = rand() % (WIDTH - 5) + 2;
	}
	else
	{
		Blocks[oldTail_i][oldTail_j] = 0;
	}
}

void startup()
{
	int i;
	Blocks[HEIGHT / 2][WIDTH / 2] = 1;
	for (i = 1; i <= 4; i++)
		Blocks[HEIGHT / 2][WIDTH / 2 - i] = i + 1;
	moveDirection = 'd';
	food_i = rand() % (HEIGHT - 5) + 2;
	food_j = rand() % (WIDTH - 5) + 2;
	initgraph(WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE);
	setlinecolor(RGB(236, 236, 236));
	BeginBatchDraw();
}

void show()
{
	cleardevice();
	int i, j;
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			if (Blocks[i][j] > 0)
				setfillcolor(HSVtoRGB(Blocks[i][j] * 10, 0.9, 1));
			else setfillcolor(WHITE);
			fillrectangle(j * BLOCK_SIZE, i * BLOCK_SIZE, (j + 1) * BLOCK_SIZE, (i + 1) * BLOCK_SIZE);
		}
	}
	setfillcolor(RED);
	fillrectangle(food_j * BLOCK_SIZE, food_i * BLOCK_SIZE, (food_j + 1) * BLOCK_SIZE, (food_i + 1) * BLOCK_SIZE);
	if (isFailure)
	{
		setbkmode(TRANSPARENT);
		settextcolor(RGB(255, 0, 0));
		settextstyle(80, 0, _T("����"));
		outtextxy(240, 220, _T("��Ϸʧ��"));
	}
	FlushBatchDraw();
}

void updateWithoutInput()
{
	if (isFailure)
		return;
	static int waitIndex = 1;
	waitIndex++;
	if (waitIndex == 7)
	{
		moveSnake();
		waitIndex = 1;
	}
}

/*��ʵ�ϣ��ƶ��ߵĺ���ֻ��movewithoutinput��
movewithinput�������ǵõ��û������Ե���move�������������ߵ�λ��
*/

void updateWithInput()
{
	if (_kbhit() && isFailure == 0)
	{
		char input = _getch();
		char orimoveDirection = moveDirection;

		if (input == 'a' || input == 's' || input == 'd' || input == 'w')
		{
			moveDirection = input;
			if (orimoveDirection == 'a' && moveDirection == 'd')
				moveDirection = orimoveDirection;
			if (orimoveDirection == 'w' && moveDirection == 's')
				moveDirection = orimoveDirection;
			if (orimoveDirection == 'd' && moveDirection == 'a')
				moveDirection = orimoveDirection;
			if (orimoveDirection == 's' && moveDirection == 'w')
				moveDirection = orimoveDirection;
			if (moveDirection != orimoveDirection)
				moveSnake();

		}
	}
}

int main() //  ������
{
	menu();
	choose();
	if (mode == 1)
	{
		startup();  // ��ʼ����������ִ��һ��	
		while (1)   // һֱѭ��
		{
			show();  // ���л���
			updateWithoutInput(); // �������޹صĸ��� 
			updateWithInput();    // �������йصĸ���
		}
		return 0;
	}
}
