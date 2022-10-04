#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include<time.h>
#include"void.h"

int main() {
	system("mode con cols=100 lines=30");  //設定控制檯的寬高
	welcometogame();
	Startup(); //初始化
	do {		//遊戲迴圈，畫面一張張更新並顯示
		timesup();
		scoreandtips();
		UpdateInput();
		if (n == 1) {//難度簡單
			difficult1();
			UpdateNormal1();
		}
		else if (n == 2) {//難度困難
			difficult2();
			UpdateNormal2();
		}
		Show();
		if (IsOver == 0) {
			endgame();
		}
	} while (IsOver == 1);

	return 0;
}
