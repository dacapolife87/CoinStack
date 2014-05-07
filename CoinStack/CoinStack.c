#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#define SLEEPTIME 100
#define DROPTIME 50
#define ENDINGTIME 2000
#define COL			GetStdHandle(STD_OUTPUT_HANDLE)				 // 콘솔창의 핸들정보 받기
#define BLACK       SetConsoleTextAttribute(COL, 0x0000);        // 검정색
#define DARK_BLUE   SetConsoleTextAttribute(COL, 0x0001);        // 파란색
#define GREEN       SetConsoleTextAttribute(COL, 0x0002);        // 녹색
#define BLUE_GREEN  SetConsoleTextAttribute(COL, 0x0003);        // 청녹색
#define BLOOD       SetConsoleTextAttribute(COL, 0x0004);        // 검붉은색
#define PURPLE      SetConsoleTextAttribute(COL, 0x0005);        // 보라색
#define GOLD        SetConsoleTextAttribute(COL, 0x0006);        // 금색
#define ORIGINAL    SetConsoleTextAttribute(COL, 0x0007);        // 밝은 회색 (ORIGINAL CONSOLE COLOR)
#define GRAY        SetConsoleTextAttribute(COL, 0x0008);        // 회색
#define BLUE        SetConsoleTextAttribute(COL, 0x0009);        // 파란색
#define HIGH_GREEN  SetConsoleTextAttribute(COL, 0x000a);        // 연두색
#define SKY_BLUE    SetConsoleTextAttribute(COL, 0x000b);        // 하늘색
#define RED         SetConsoleTextAttribute(COL, 0x000c);        // 빨간색
#define PLUM        SetConsoleTextAttribute(COL, 0x000d);        // 자주색
#define YELLOW      SetConsoleTextAttribute(COL, 0x000e);        // 노란색
#define WHITE       SetConsoleTextAttribute(COL, 0x000f);        // 흰색


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
void stackgame()
{
	int x=23;
	int y=1;
	setWindowSize();

	
	drawBackgroundFunc();
	printScore();
	gotoxy(x,y);
	coinMove(x,y);

	return;
}
void coinMove(int x,int y)
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
			printf("▥▥▥▥");
			Sleep(SLEEPTIME);
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
			printf("▥▥▥▥");
			Sleep(SLEEPTIME);
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
			clearLevel();
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
void clearLevel()
{
	int x,y;
	char yes;
	system("cls");
	x=35;
	y=15;
	gotoxy(x,y);
	printf("GameClear\n");
	Sleep(1000);
	system("cls");
	do
	{
		printf("다음 레벨로 넘어가시겠습니까? (Y/N)\n");
		scanf("%c",&yes);
		switch (yes)
		{
		case 'Y':case'y':
			stackgame();
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
void coinDownFunc(int x,int dropheight)// x:다운 위치 y 다운될높이
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
	printf("▥▥▥▥");

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
	x=35;
	y=16;
	gotoxy(x,y);
	do{
		scanf("%d",&menu);
		if(!(menu==1 || menu==2))
			printf("                          다시입력해주세요.(1 또는 2 입력)");
		switch (menu)
		{
		case 1:
			stackgame();
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
	printf("                             1. 게임시작    \n");
	printf("                             2. 게임종료   \n");
	printf("                          원하시는 메뉴를 선택하세요.   \n");
	
	return;
}
void printScore()
{
	int x,y;
	x=3;
	y=10;
	gotoxy(x,y);
	printf("CoinStack");

	x=65;
	y=10;
	gotoxy(x,y);
	printf("Level 01\n");
	x=65;
	y=12;
	gotoxy(x,y);
	printf("Difficulty hard");

	return;
}
void drawBackgroundFunc()
{
	
	int i,j;
	int x,y;
	GOLD;
	
	y=2;

	for(i=0;i<19;i++)
	{
		x=20;
		gotoxy(x,y);
		printf("▦");
		for(j=0;j<20;j++)
			printf("  ");
		printf("▦");
		printf("\n");
		y++;
	}
	x=20;
	gotoxy(x,y);
	printf("▦");
	for(i=0;i<20;i++)
	{
		if(i>7 && i<12)
		{
			GRAY;
			printf("▩");
		}
		else
		{
			GOLD;
			printf("▦");
		}		
	}
	printf("▦");
	printf("\n");
	printf("123456789012345678901234567890123456789012345678901234567890");
	return;
}
