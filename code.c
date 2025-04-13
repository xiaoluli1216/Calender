#include<graphics.h>
#include<stdio.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define WIDTH 50
#define HEIGHT 50
int year, month, day;
char weekday[7][3] = { "一","二","三","四","五","六","日" };
int tempMap[6 * 7] = { 0 }; //暂时存储
int map[6][7] = { 0 };

//区分平年和闰年
bool isleapyear(int year)
{
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		return true;
	else
		return false;
}
//选择结构求每个月的天数
int GetDayByMonth(int year, int month)
{
	switch (month)
	{
	case 2:
		return isleapyear(year) ? 29 : 28;
		break;
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
		break;
	default:
		return 30;
		break;
	}
}

//用户输入的日期离1900.1.1有多少天
int GetSumDays(int year, int month)
{
	int sum = 0;
	for (int i = 1900;i < year;i++) {
		sum += isleapyear(i) ? 366 : 365;
	}
	for (int i = 0;i < month;i++)
	{
		sum += GetDayByMonth(year, i);
	}
	return sum;
}


IMAGE imgbk;
IMAGE img;
void GameInit()
{
	loadimage(&imgbk, "background.bmp");
	mciSendString("open 1.mp3", 0, 0, 0);
	mciSendString("play 1.mp3 repeat", 0, 0, 0);
}

//封装一个函数使其自动居中
void outtextMid(int x, int y, const char* str)
{
	settextstyle(35, 0, "楷体");
	settextcolor(BLACK);
	int textX = x + (WIDTH - textwidth(str)) / 2;
	int textY = y + (HEIGHT - textheight(str)) / 2;
	outtextxy(textX, textY, str);
}

void drawCalender()
{
	int x = 50;
	int y = 50;
	for (int i = 0;i < 7;i++) {
		outtextMid(x + i * WIDTH, y, weekday[i]);
	}
	for (int i = 0;i < 6;i++)
	{
		for (int j = 0;j < 7;j++)
		{
			int x = WIDTH * j + 50;
			int y = HEIGHT * i + 100;
			if (map[i][j]) {
				setlinecolor(BLACK);
				setfillcolor(map[i][j] == day ? LIGHTBLUE : WHITE);
				fillrectangle(x, y, x + WIDTH, y + HEIGHT);
				//图形化只能输出字符串  数字转换字符串
				char str[20] = { "" };
				sprintf_s(str, 20, "%d", map[i][j]);
				outtextMid(x, y, str);
			}
		}
	}
}

//获取地图
void GetMap(int sum, int year, int month)
{
	int result, temp, i;
	int count = 0;
	result = sum % 7;
	for (i = 0;i < result;i++)
	{
		tempMap[count++] = 0;
	}
	temp = 7 - result;
	for (int i = 1;i <= GetDayByMonth(year, month);i++)
	{
		tempMap[count++] = i;
	}
	//一维数组转换为二维数组
	int pos = 0;
	for (int i = 0;i < 6;i++)
	{
		for (int j = 0;j < 7;j++)
		{
			map[i][j] = tempMap[pos++];
		}
	}
}

void TextAction()
{
	const char* text[8] = { "好","好","学","习","天","天","向","上" };
	settextstyle(35, 0, "楷体");
	settextcolor(WHITE);
	int x = 500;
	int y = 50;
	for (int i = 0;i < 8;i++)
	{
		if (i < 4) {
			outtextxy(x, y + i * 50, text[i]);
		}
		else {
			outtextxy(x - 50, y + (i - 3) * 50, text[i]);
		}
		Sleep(500);
	}
}

void GameDraw()
{
	putimage(0, 0, &imgbk);
	//文字布局
	settextcolor(BLUE);
	settextstyle(30, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy(100, 10, "欢迎来看日历");

	drawCalender();

	char date[20] = { "" };
	sprintf_s(date, 20, "%d年%d月%d日", year, month, day);
	settextcolor(WHITE);
	settextstyle(18, 0, "楷体");
	outtextxy(430, 370, date);

	TextAction();
}


int main()
{
	printf("input year month day:");
	scanf_s("%d %d %d", &year, &month, &day);
	GetMap(GetDayByMonth(year,month),year,month);

	
	initgraph(561, 413);
	GameInit();
	GameDraw();
	while (1);

	closegraph();
	return 0;
}
