#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <conio.h>
#include <windows.h>



using namespace std;





class Boss
{
public:
	int maxhealth,health, killpoint, equipcost,bosstype;
	Boss(){InitBoss();}
	void InitBoss()
	{
		srand(time(NULL));
		maxhealth = health = (rand() % 2000 )+ 1000;
		killpoint = (rand()%50 )+ 10;
		equipcost = (rand() % 100 )+ 1;
		bosstype = (rand() % 3) + 1;
	}

	void summonboss() 
	{
		maxhealth = health = (rand() % 20000) + 10000;
		killpoint = (rand() % 5000) + 1000;
		equipcost = (rand() % 100) + 1;
		bosstype = 4;
	}


	int GetHealth() { return health; };
	int GetMaxHealth() { return maxhealth; };
	int GetKillpoint() { return killpoint; };
	int GetEquipcost() { return equipcost; };
	
};
void Score();
void GameStart();
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y);
void loadres();
void draw();
void mouse();
void Reinitboss();
void uptext();


int sc = 0;
IMAGE img[12];
IMAGE btn[3];
Boss monster;
LPCTSTR font = "華康行楷體W5";
char str[256];

int attack = 10, strikedamage = 0;
float strike = 0;
int Cattack = 100, Cstrikedamage = 200, Cstrike = 250;
int bossX = ((rand() % 224) + 0);
int bossY = ((rand() % 120) + 50);
int equip[3];
int upattack = 50,up[3];
int upstrikedamage = 50;
int upstrike = 50;
int gg=0;
int main()
{
	GameStart();
	
	BeginBatchDraw(); //雙緩衝繪圖
	while (1)
	{
		FlushBatchDraw(); //雙緩衝繪圖
		mouse();
		if (gg == 1) {
			break;
		}
		


	
	}
	EndBatchDraw(); //雙緩衝繪圖

	
	 system("pause");



	return 0;
}


void mouse()
{
	if (MouseHit())
	{
		settextcolor(RGB(255, 255, 255));
		MOUSEMSG data = GetMouseMsg();
		int row = data.y;
		int col = data.x;
		int damage;
		if (data.uMsg == WM_LBUTTONDOWN) {
			if (col > bossX && col < (bossX + 256) && row > bossY && row < (bossY + 256)) //BOSS點擊
			{
				int tempstrike = (rand() % 100 + 1);
				if (tempstrike <= strike) {

					damage = attack + strikedamage;
					drawAlpha(&img[10], bossX - 44, bossY - 44);
				}
				else {
					damage = attack;
				}

				if ((monster.health -= damage) <= 0 && monster.bosstype != 4) {
					Reinitboss();
					sc += monster.GetKillpoint();
				}
				else if((monster.health -= damage) <= 0 && monster.bosstype == 4) {
					drawAlpha(&img[11], 0, 0);
					gg = 1;

				}

			}

			if (col > 318 && col < (318 + 150) && row > 512 && row < (512 + 50)) //btn1
			{
				drawAlpha(&btn[1], 318, 512);
				uptext();
				if (sc >= upattack && up[0] < 20) {
					sc -= upattack;
					attack += (rand() % 5 + 2);
					upattack += (rand() % 10 + 5);
					up[0] += 1;
				}


			}
			if (col > 318 && col < (318 + 150) && row > 586 && row < (586 + 50)) //btn2
			{
				drawAlpha(&btn[1], 318, 586);
				uptext();
				if (sc >= upstrike && up[1] < 20) {
					sc -= upstrike;
					strike += (rand() % 2 + 0.1);
					upstrike += (rand() % 15 + 10);
					up[1] += 1;
				}


			}
			if (col > 318 && col < (318 + 150) && row > 663 && row < (663 + 50)) //btn3
			{
				drawAlpha(&btn[1], 318, 663);
				uptext();
				if (sc >= upstrikedamage && up[2] < 10) {
					sc -= upstrikedamage;
					strikedamage += (rand() % 10 + 5);
					upstrikedamage += (rand() % 20 + 10);
					up[2] += 1;
				}


			}
			if (col > 170 && col < (170 + 137) && row > 380 && row < (380 + 131) && equip[0] == 1 && equip[1] == 1 && equip[2] == 1) //btn4
			{
				monster.summonboss();
				for (int i = 0; i < 3; i++) {
					equip[i] = 0;
				}
				draw();


			}




		}



		if (data.uMsg == WM_LBUTTONUP) {
			if (col > bossX && col < (bossX + 256) && row > bossY && row < (bossY + 256)) //BOSS點擊
			{
				bossX = ((rand() % 224) + 0);
				bossY = ((rand() % 120) + 50);
				draw();
			}
		}
	



		if (col > 318 && col < (318 + 150) && row > 512 && row < (512 + 50)) //btn1
		{
			if (data.uMsg == WM_LBUTTONUP) {
				draw();
				drawAlpha(&btn[0], 318, 512);
				uptext();
			}
		}
		if (col > 318 && col < (318 + 150) && row > 586 && row < (586 + 50)) //btn2
		{
			if (data.uMsg == WM_LBUTTONUP) {
				draw();
				drawAlpha(&btn[0], 318, 586);
				uptext();
			}
		}
		if (col > 318 && col < (318 + 150) && row > 663 && row < (663 + 50)) //btn3
		{
			if (data.uMsg == WM_LBUTTONUP) {
				draw();
				drawAlpha(&btn[0], 318, 663);
				uptext();
			}
		}




		
	}
}

void uptext() 
{
	settextcolor(RGB(255, 255, 255));
	settextstyle(36, 18, font);

	
	
	

	if (up[0] >= 20) {
		sprintf(str, "MAX"); //攻擊力
		outtextxy(375, 520, str);
	}
	else {
		sprintf(str, "%d", upattack); //攻擊力
		outtextxy(375, 520, str);
	}
	if (up[1] >= 20) {
		sprintf(str, "MAX"); //爆擊率
		outtextxy(375, 594, str);
	}
	else {
		sprintf(str, "%d", upstrike); //爆擊率
		outtextxy(375, 594, str);
	}
	if (up[2] >= 10) {
		sprintf(str, "MAX"); //爆擊傷害
		outtextxy(375, 671, str);
	}
	else {
		sprintf(str, "%d", upstrikedamage); //爆擊傷害
		outtextxy(375, 671, str);
	}

}


void Reinitboss()
{
	int equipdrow = ((rand() % 1000) + 1);
	
	if (equipdrow <= monster.equipcost) {
		while (true)
		{
			int equipdrowtype = ((rand() % 3) + 1); //判斷種類
			if (equip[equipdrowtype-1] != 1) {
				equip[equipdrowtype-1] = 1;
				
				for (int i = 0; i < 3; i++) {
					if (equip[i] == 1) {
						if (equip[i] == 1 && i == 0) {
							drawAlpha(&img[7], 43, 397);
						}
						else if (equip[i] == 1 && i == 1) {
							drawAlpha(&img[8], 200, 397);
						}
						else if (equip[i] == 1 && i == 2) {
							drawAlpha(&img[9], 368, 397);
						}
					}
				}
				break;
			}
			else if(equip[0] == 1 && equip[1] == 1 && equip[2] == 1)
			{
				break;
			}
		}
	}
	monster.InitBoss();
	draw();
}

void draw()
{
	int barX = 440;
	float health = monster.GetHealth();
	float maxhealth = monster.GetMaxHealth();
	float barsc = (health / maxhealth) * 100;

	if (barsc == 100) {
		barX = 440;
	}
	else {
		barX = (barsc) * 5;
		if (barX < 43)
			barX = 43;
		
	}
	drawAlpha(&img[5], 43, 38); //血條(RED)
	putimage(barX, 38, &img[6]); //血條
	drawAlpha(&img[0], 0, 0); //背景
	
	for (int i = 0; i < 3; i++) {
		if (equip[i] == 1) {
			if (equip[i] == 1 && i == 0) {
				drawAlpha(&img[7], 43, 397);
			}
			else if (equip[i] == 1 && i == 1) {
				drawAlpha(&img[8], 200, 397);
			}
			else if (equip[i] == 1 && i == 2) {
				drawAlpha(&img[9], 368, 397);
			}
		}
	}
	drawAlpha(&img[monster.bosstype], bossX, bossY);

	if (equip[0] == 1 && equip[1] == 1 && equip[2] == 1)
	{
		drawAlpha(&btn[2], 170, 380);
	}

	
	

	drawAlpha(&btn[0], 318, 512);
	drawAlpha(&btn[0], 318, 586);
	drawAlpha(&btn[0], 318, 663);


	Score();
}

void GameStart()
{
	loadres(); //載入資源
	initgraph(480, 760);
	setbkcolor(RGB(153, 155, 159));
	clearcliprgn();

	int mode = TRANSPARENT;
	setbkmode(mode);

	for (int i = 0; i < 3; i++) {
		equip[i] = 0;
		up[i] = 0;
	}

	draw();

	
	

	
	
}

void Score()
{

	

	settextcolor(RGB(255, 255, 255));
	settextstyle(26, 13,font);

	sprintf(str, "%d", sc);  //分數
	outtextxy(391, 5, str);

	sprintf(str, "%d", monster.GetHealth()); //血量
	outtextxy(226, 39, str);

	settextcolor(RGB(0,0,0));
	sprintf(str, "%d", attack); //攻擊力
	outtextxy(202, 520, str);
	sprintf(str, "%.1f %%", strike); //爆擊率
	outtextxy(202, 597, str);
	sprintf(str, "%d", strikedamage); //爆擊傷害
	outtextxy(202, 676, str);


	uptext();

}

void loadres() {


	loadimage(&img[0], "./images/bg.png");
	loadimage(&img[1], "./images/1.png");
	loadimage(&img[2], "./images/2.png");
	loadimage(&img[3], "./images/3.png");
	loadimage(&img[4], "./images/4.png");
	loadimage(&img[5], "./images/bar.png");
	loadimage(&img[6], "./images/bar2.png");
	loadimage(&img[7], "./images/w1.png");
	loadimage(&img[8], "./images/w2.png");
	loadimage(&img[9], "./images/w3.png");
	loadimage(&img[10], "./images/hit.png");
	loadimage(&btn[0], "./images/b1.png");
	loadimage(&btn[1], "./images/b2.png");
	loadimage(&btn[2], "./images/b3.png");
	loadimage(&img[11], "./images/bg2.png");
	



}

void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //x为载入图片的X坐标，y为Y坐标
{


	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{

		for (int ix = 0; ix < picture_width; ix++)
		{

			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{

				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}