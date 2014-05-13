////////////////////////////////////////////////////////////////////////////////////////////////// 
/* �� �ٲ� ���� */

/*************************************
* Coin Stack
* VisualStudio 2012
* 2014.04.16~
*************************************/

#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#define SLEEPTIME 100
#define DROPTIME 50
#define ENDINGTIME 2000
#define COL			GetStdHandle(STD_OUTPUT_HANDLE)			// �ܼ�â�� �ڵ����� �ޱ�
#define BLACK       SetConsoleTextAttribute(COL, 0x0000);   // ������
#define DARK_BLUE   SetConsoleTextAttribute(COL, 0x0001);   // �Ķ���
#define GREEN       SetConsoleTextAttribute(COL, 0x0002);   // ���
#define BLUE_GREEN  SetConsoleTextAttribute(COL, 0x0003);   // û���
#define BLOOD       SetConsoleTextAttribute(COL, 0x0004);   // �˺�����
#define PURPLE      SetConsoleTextAttribute(COL, 0x0005);   // �����
#define GOLD        SetConsoleTextAttribute(COL, 0x0006);   // �ݻ�
#define ORIGINAL    SetConsoleTextAttribute(COL, 0x0007);   // ���� ȸ�� (ORIGINAL CONSOLE COLOR)
#define GRAY        SetConsoleTextAttribute(COL, 0x0008);   // ȸ��
#define BLUE        SetConsoleTextAttribute(COL, 0x0009);   // �Ķ���
#define HIGH_GREEN  SetConsoleTextAttribute(COL, 0x000a);   // ���λ�
#define SKY_BLUE    SetConsoleTextAttribute(COL, 0x000b);   // �ϴû�
#define RED         SetConsoleTextAttribute(COL, 0x000c);   // ������
#define PLUM        SetConsoleTextAttribute(COL, 0x000d);   // ���ֻ�
#define YELLOW      SetConsoleTextAttribute(COL, 0x000e);   // �����
#define WHITE       SetConsoleTextAttribute(COL, 0x000f);   // ���


void setWindowSize();
void coinDownFunc(int,int);
void coinMove(int,int);
void gotoxy(int,int);
void clearpoint(int,int);
void stackcoin(int,int);
void drawBackgroundFunc();
void printScore();
void clearLevel();
void printImage();
void stackgame();
void selectMenu();
void startMenu();
void showStack(int);
void gameOver();

int main(void)
{
	startMenu();
	return 0;
}
void startMenu()
{
	system("cls");
	printImage();
	selectMenu();

	return;
}
int selectLevel()
{
	int selectedLevel=1;
	
	do
	{
		system("cls");
		printf("1. Level 1\n");
		printf("2. Level 2\n");
		printf("3. Level 3\n");
		printf("4. Level 4\n");
		printf("5. Level 5\n");

		printf("0. Back\n");

		scanf("%d",&selectedLevel);

		switch (selectedLevel)
		{
		case 1:
			return 1;
		case 2:
			return 2;
		case 3:
			return 3;
		case 4:
			return 4;
		case 5:
			return 5;
		case 0:
			startMenu();
			return 0;

		default:
			printf("�ٽ� �Է��� �ּ���.\n");
			continue;
		}
	}while(1);
}
void stackgame(int level)
{
	int x=23;
	int y=1;
	int speed=100;
	setWindowSize();

	
	drawBackgroundFunc();
	printScore(level);
	gotoxy(x,y);
	speed = speedForLevel(level);
	coinMove(x,y,speed,level);

	return;
}
int speedForLevel(int level)
{
	int movingSpeed=SLEEPTIME;
	int i;
	for(i=1;i<level;i++)
	{
		movingSpeed = (movingSpeed * 9)/10;
	}
	return movingSpeed;
}
void coinMove(int x,int y,int speed,int level)
{
	int rightmove = 1;
	int leftmove = 0;
	int downline = 0;
	int dropheight =20;
	double balance=41.5;
	double stackBalance=41.5;
	YELLOW;
	while(1){
		if(rightmove==1)
		{
			gotoxy(x,y);
			printf("�ȢȢȢ�");
			Sleep(speed);
			x++;
			if(x==53)
			{
				rightmove=0;
				leftmove=1;
			}
			
		}
		if(leftmove==1)
		{
			gotoxy(x,y);
			printf("�ȢȢȢ�");
			Sleep(speed);
			x--;
			if(x==23)
			{
				leftmove=0;
				rightmove=1;
			}
		}
		if(kbhit())	
		{
			getch();
			clearpoint((x-8),y);
			coinDownFunc(x,dropheight);
			/*
			if(rightmove==1)
				stackBalance=x+3.5;
			else
				stackBalance=x-3.5;
			*/
			leftmove=0;
			rightmove=1;
			stackBalance=(float)x+3.5;
			if(balance<stackBalance-3.5)
			{
				showStack(stackBalance);
				gameOver();
				return;
			}else if(balance>stackBalance+3.5)
			{
				//printf("%f / %f",stackBalance,balance);
				showStack(stackBalance);
				gameOver();
				return;
			}
			balance=(balance+stackBalance)/2;
			//showStack(balance);
			stackcoin(x,dropheight);
			
			dropheight--;
			x=23;

		}
		if(dropheight==15)
		{
			clearLevel(level);
			return;
		}
	}
}
void showStack(double balance)
{
	int x,y;
	x=65;
	y=14;
	gotoxy(x,y);
	printf("Stack balance : %f",balance);
}
void gameOver()
{
	int x,y;
	system("cls");
	x=35;
	y=15;
	gotoxy(x,y);
	printf("GameOver\n");
	Sleep(1000);
	startMenu();
	return;
}
void clearLevel(int level)
{
	int x,y;
	char yes;
	system("cls");
	x=35;
	y=15;
	gotoxy(x,y);
	printf("GameClear\n");
	Sleep(1000);
	level++;
	system("cls");
	do
	{
		printf("���� ������ �Ѿ�ðڽ��ϱ�? (Y/N)\n");
		scanf("%c",&yes);
		switch (yes)
		{
		case 'Y':case'y':
			stackgame(level);
			return;
		case 'N':case'n':
			startMenu();
			return;
		default:
			break;
		}
		system("cls");
	} while (1);
	
	return;
}
void coinDownFunc(int x,int dropheight)// x:�ٿ� ��ġ y �ٿ�ɳ���
{
	int i;
	for(i=1;i<=dropheight;i++)
	{
		stackcoin(x,i);
		clearpoint(x,i-1);
		Sleep(DROPTIME);
	}
	return;
}
void clearpoint(int x,int y)
{
	gotoxy(x,y);
	printf("       ");

	return;
}
void stackcoin(int x,int dropheight)
{
	gotoxy(x,dropheight);
	printf("�ȢȢȢ�");

	return;
}
void gotoxy(int x, int y)
{
	COORD Pos ={x-1,y-1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);

	return;
}
void setWindowSize()
{
	system("mode con:lines=30 cols=100");

	return;
}
void selectMenu()
{
	int x,y;
	int menu=0;
	int levelNum=0;
	x=35;
	y=16;
	gotoxy(x,y);
	do{
		scanf("%d",&menu);
		if(!(menu==1 || menu==2))
			printf("                          �ٽ��Է����ּ���.(1 �Ǵ� 2 �Է�)");
		switch (menu)
		{
		case 1:
			levelNum = selectLevel();

			printf("%d",levelNum);
			
			stackgame(levelNum);
		case 2:
			return;
		default:
			continue;
		}
	}while(!(menu==1 || menu==2));

	return;
}
void printImage()
{
	ORIGINAL;
	printf("   ###      ####     #####    #     #\n");
	printf("  #   #    #    #      #      ##    #\n");
	printf("  #        #    #      #      # ### #\n");
	printf("  #   #    #    #      #      #    ##\n");
	printf("   ###	    ####     #####    #     #\n");
	printf("\n");
	printf("                                 ####   #######    #       ###    #   #\n");
	printf("                                 #         #      #  #    #   #   #  #\n");
	printf("                                 ####      #     ######   #       ###\n");
	printf("                                    #      #     #    #   #   #   #  #\n");
	printf("                                 ####      #     #    #    ###    #   #\n");
	printf("\n");
	printf("                             1. ���ӽ���    \n");
	printf("                             2. ��������   \n");
	printf("                          ���Ͻô� �޴��� �����ϼ���.   \n");
	
	return;
}
void printScore(int level)
{
	int x,y;
	x=3;
	y=10;
	gotoxy(x,y);
	printf("CoinStack");

	x=65;
	y=10;
	gotoxy(x,y);
	printf("Level %d\n",level);
	x=65;
	y=12;
	gotoxy(x,y);
	printf("Difficulty hard");

	return;
}
void drawBackgroundFunc()  // ���� ���� ��׶���
{
	
	int i,j;
	int x,y;
	GOLD;
	
	y=2;

	for(i=0;i<19;i++)
	{
		x=20;
		gotoxy(x,y);
		printf("��");
		for(j=0;j<20;j++)
			printf("  ");
		printf("��");
		printf("\n");
		y++;
	}
	x=20;
	gotoxy(x,y);
	printf("��");
	for(i=0;i<20;i++)
	{
		if(i>7 && i<12)
		{
			GRAY;
			printf("��");
		}
		else
		{
			GOLD;
			printf("��");
		}		
	}
	printf("��");
	printf("\n");
	printf("1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"); // �ܼ�â Ŀ����ǥ Ȯ���ϱ� ���� �ӽ� ����
	return;
}