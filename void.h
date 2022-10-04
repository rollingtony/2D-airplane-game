#pragma once
#define high 25 //畫布高
#define width 60 //畫布寬
#define border -1 //邊界
#define blank 0 //空白
#define plane 1 //飛機
#define bullet 2 //子彈
#define enemy 3 //敵機
#define destroy 4 //摧毀標記
#define b_bullet 5 //boss子彈
#define boss 100 //BOSS
#define difficulty1 5  //分數難度1
#define difficulty2 10 //分數難度2
#define difficulty3 20 //分數難度3
#define difficulty4 30 //分數難度4
#define difficulty5 80 //分數難度5

int canvas[high + 2][width + 2]; //遊戲場景的高和寬
int pos_h, pos_w; //飛機位置
int enemynum; //敵機數量
int interval; //同個計次來模擬時間間隔
int itv_move; //敵機移動的時間間隔
int itv_new; //敵機重新整理的時間間隔
int score; //簡單遊戲分數
int IsOver; //判斷遊戲是否結束
int highscore = 0;//最高紀錄
int att;//BOSS打擊次數
int boss1;//boss生成一次，防止boss重複生成
int boss_y_start;//bossY軸寬度
int boss_move; //boss移動的時間間隔
int bullet_move;//boss子彈生成速度
int bullet_new; //boss子彈移動速度
int n; //主畫面選擇關卡
int mode; //子彈模式
time_t start, end; //遊戲時間間隔
int times; //遊戲時間計時

void Startup(); //遊戲數值初始化
void Show(); //遊戲介面輸出
void UpdateInput(); //與輸入無關的遊戲狀態更新
void UpdateNormal1(); //因輸入導致的簡單遊戲狀態更新
void UpdateNormal2(); //因輸入導致的困難遊戲狀態更新
void welcometogame(); //開始介面

int color(int c) //更改文字顏色
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	return 0;
}
void gotoxy(int x, int y) { //回撥游標
	COORD pos;
	pos.X = x - 1;
	pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void HideCursor() { //隱藏游標函式
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor);
}
void explation() //遊戲提示 
{
	int i, j = 1;
	system("cls");
	color(10);
	gotoxy(40, 1);
	printf("遊戲說明");
	color(2);
	for (i = 3; i <= 28; i++)  //輸出上下邊框===
	{
		for (j = 6; j <= 80; j++) //輸出左右邊框||
		{
			gotoxy(j, i);
			if (i == 3 || i == 28) printf("=");
			else if (j == 6 || j == 80) printf("||");
		}
	}
	color(3);
	gotoxy(20, 5);
	printf("1. W,A,S,D 分別控制飛機的上下左右移動");
	color(10);
	gotoxy(20, 8);
	printf("2. 按空格發射子彈，打中敵機即可得到一分");
	color(14);
	gotoxy(20, 11);
	printf("3. 碰到敵機、BOSS或BOSS子彈死亡");
	color(11);
	gotoxy(20, 14);
	printf("4. 利用按鍵1 2 3 切換發射子彈模式");
	color(4);
	gotoxy(20, 17);
	printf("5. 在時間內獲取最高分!");
	gotoxy(20, 20);
	color(15);
	printf("6. 玩的愉快！！！");
	color(7);
	gotoxy(20, 23);
	printf("/*****按任意鍵返回主頁面*****/");
	_getch();        //按任意鍵返回主介面
	system("cls");
	welcometogame();
}
void scoreandtips()//遊戲側邊提示 
{
	gotoxy(70, 8);
	color(14);
	printf("遊戲得分：%d 倒數計時：%02d", score, times);
	gotoxy(70, 10);
	printf("在時間內獲取最高分!");
	gotoxy(70, 12);
	printf("用 W A S D 分別控制飛機的移動");
	gotoxy(70, 14);
	printf("按下空格鍵即為發射炮彈");
	gotoxy(70, 16);
	color(7);
	printf("@ 是敵機");
	gotoxy(70, 18);
	color(4);
	printf("# 是BOSS");
	gotoxy(70, 20);
	color(12);
	printf("* 是BOSS子彈");
	color(14);
	gotoxy(70, 22);
	printf("利用按鍵 ");
	printf("1 ");
	color(3);
	printf("2 ");
	color(5);
	printf("3 ");
	color(14);
	printf("切換子彈發射模式");
}
void welcometogame() //開始介面
{
	color(15);
	gotoxy(43, 10);
	printf("飛 機 大 戰");
	color(11);
	gotoxy(15, 22);
	printf("1.簡單模式");
	gotoxy(34, 22);
	printf("2.困難模式");
	gotoxy(54, 22);
	printf("3.遊戲說明");
	gotoxy(73, 22);
	printf("4.退出遊戲");
	color(3);
	gotoxy(36, 25);
	printf("請使用英文輸入法進行遊戲!");
	gotoxy(40, 27);
	printf("請選擇 1 2 3 4：");
	color(14);
	scanf("%d", &n);   //輸入選項
	switch (n)
	{
	case 1:
	case 2:
		system("cls");   //遊戲開始預備
		Show();
		break;
	case 3:
		explation();    //遊戲說明函式
		break;
	case 4:
		exit(0);    //退出遊戲
		break;
	default:
		color(12);
		gotoxy(40, 28);
		printf("請輸入1-4之間的數!");
		_getch();  //輸入任意鍵
		system("cls"); //清屏
		welcometogame();
	}
}
void Startup() { //遊戲數值初始化
	IsOver = 1;
	score = 0; //初始化分數
	for (int i = 0; i < high + 2; i++) { //初始化畫布
		for (int j = 0; j < width + 2; j++) {
			if (i == 0 || i == high + 1 || j == 0 || j == width + 1) {
				canvas[i][j] = border;
			}
			else canvas[i][j] = blank;
		}
	}
	pos_h = high - 1; //初始化飛機豎直座標
	pos_w = width / 2; //初始化飛機水平座標

	canvas[pos_h][pos_w] = plane; //初始化飛機位置

	enemynum = 6; //敵機數量

	srand(time(NULL));//改變隨機種子來改變產生的順序
	interval = 95; //初始化時間間隔計數
	itv_move = 20; //初始化敵機移動時間間隔
	itv_new = 100; //初始化敵機重新整理時間間隔
	att = 0;//初始化打擊boss次數
	boss1 = 0;//boss生成一次
	boss_move = 3;//初始化boss移動時間間隔
	boss_y_start = 25;//設定bossY軸寬度
	bullet_move = 2;//初始化boss子彈移動時間間隔
	bullet_new = 20;//初始化boss子彈重新整理時間間隔
	mode = 1;//初始化發射子彈模式
	start = time(NULL);

}
void Show() { //遊戲介面輸出
	HideCursor(); //隱藏游標
	gotoxy(1, 1); //回撥游標、重新整理畫面
	for (int i = 0; i < high + 2; i++) {
		for (int j = 0; j < width + 2; j++) {
			if (canvas[i][j] == plane) { //當前位置為飛機位置
				if (mode == 2) {   //飛機樣式隨模式改變
					color(3);
					printf("Y");
				}
				else if (mode == 3) {
					color(5);
					printf("w");
				}
				else
					printf("^");
				color(14);
			}
			else if (canvas[i][j] == bullet) { //當前位置為子彈位置
				if (mode == 2)   //飛機樣式隨模式改變
					color(3);
				else if (mode == 3)
					color(5);
				printf("|");
				color(14);
			}
			else if (canvas[i][j] == b_bullet) { //當前位置為子彈位置
				color(12);
				printf("*");
				color(14);
			}
			else if (canvas[i][j] == enemy) { //當前位置為敵機位置
				color(7);
				printf("@");
				color(14);
			}
			else if (canvas[i][j] == border) { //當前位置為邊界
				printf("-");
			}
			else if (canvas[i][j] == blank) { //當前位置無物，且在邊界內
				printf(" ");
			}
			else if (canvas[i][j] == destroy) { //墜毀位置
				printf("x");
			}
			else if (canvas[i][j] == boss) {//BOSS位置
				color(4);
				printf("#");
				color(14);
			}
		}
		printf("\n");
	}
}
void UpdateInput() { //因輸入導致的遊戲狀態更新
	if (_kbhit()) { //當有鍵按下時
		if (GetKeyState('W') < 0) { //當按下 W 鍵，上移
			if (pos_h > 1) {
				canvas[pos_h][pos_w] = blank;
				if (canvas[pos_h - 1][pos_w] == enemy) { //下個位置是敵機，撞毀
					canvas[pos_h - 1][pos_w] = destroy;
					IsOver = 0;
				}
				else canvas[--pos_h][pos_w] = plane;
			}
		}
		if (GetKeyState('S') < 0) { //當按下 S 鍵，下移
			if (pos_h < high) {
				canvas[pos_h][pos_w] = blank;
				if (canvas[pos_h + 1][pos_w] == enemy) { //下個位置是敵機，撞毀
					canvas[pos_h + 1][pos_w] = destroy;
					IsOver = 0;
				}
				else canvas[++pos_h][pos_w] = plane;
			}
		}
		if (GetKeyState('A') < 0) { //當按下 A 鍵，左移
			if (pos_w > 1) {
				canvas[pos_h][pos_w] = blank;
				if (canvas[pos_h][pos_w - 1] == enemy) { //下個位置是敵機，撞毀
					canvas[pos_h][pos_w - 1] = destroy;
					IsOver = 0;
				}
				else canvas[pos_h][--pos_w] = plane;
			}
		}
		if (GetKeyState('D') < 0) { //當按下 D 鍵，右移
			if (pos_w < width) {
				canvas[pos_h][pos_w] = blank;
				if (canvas[pos_h][pos_w + 1] == enemy) { //下個位置是敵機，撞毀
					canvas[pos_h][pos_w + 1] = destroy;
					IsOver = 0;
				}
				else canvas[pos_h][++pos_w] = plane;
			}
		}
		if (GetKeyState(' ') < 0) { //當按下空格鍵，發射子彈
			if (pos_h != 1) {
				if (mode == 3) {
					if (canvas[pos_h - 1][pos_w - 1] == border) { //飛機在邊界旁邊，子彈不會射出在邊界
						canvas[pos_h - 1][pos_w + 1] = bullet;
						canvas[pos_h - 1][pos_w] = bullet;
					}
					else if (canvas[pos_h - 1][pos_w + 1] == border) {
						canvas[pos_h - 1][pos_w - 1] = bullet;
						canvas[pos_h - 1][pos_w] = bullet;
					}
					else {
						canvas[pos_h - 1][pos_w - 1] = bullet;
						canvas[pos_h - 1][pos_w] = bullet;
						canvas[pos_h - 1][pos_w + 1] = bullet;
					}
				}
				else if (mode == 2) {
					if (canvas[pos_h - 1][pos_w - 1] == border) {//飛機在邊界旁邊，子彈不會射出在邊界
						canvas[pos_h - 1][pos_w + 1] = bullet;
					}
					else if (canvas[pos_h - 1][pos_w + 1] == border) {
						canvas[pos_h - 1][pos_w - 1] = bullet;
					}
					else {
						canvas[pos_h - 1][pos_w - 1] = bullet;
						canvas[pos_h - 1][pos_w + 1] = bullet;
					}
				}
				else  canvas[pos_h - 1][pos_w] = bullet;
			}
		}
		if (GetKeyState('1') < 0) {//當按下數字鍵1，子彈切到單發模式
			mode = 1;
		}
		if (GetKeyState('2') < 0) {//當按下數字鍵2，子彈切到雙發模式
			mode = 2;
		}
		if (GetKeyState('3') < 0) {//當按下數字鍵3，子彈切到三發模式
			mode = 3;
		}
	}
}

void UpdateNormal1() { //與輸入無關的簡單遊戲狀態更新
	int temp[high + 2][width + 2]; //用來判斷原位置的臨時陣列
	for (int i = 1; i <= high; i++) {
		for (int j = 1; j <= width; j++) {
			temp[i][j] = canvas[i][j];
		}
	}
	for (int i = 1; i <= high; i++) { //遍歷臨時陣列，修改畫布
		for (int j = 1; j <= width; j++) {
			if (temp[i][j] == enemy && interval % itv_move == 0) { //當前位置為敵機
				canvas[i][j] = blank;
				if (temp[i + 1][j] == bullet) { //下面為子彈，敵機被擊中
					canvas[i + 1][j] = blank;
					score++;
					printf("\a"); //擊中音效
				}
				else if (i < high) { //沒被擊中且前面不是邊界，敵機往前一格
					canvas[i + 1][j] = enemy;
				}
				if (i + 1 == pos_h && j == pos_w) { //下面為飛機，玩家飛機被撞毀
					canvas[i + 1][j] = destroy;
					IsOver = 0;
				}
			}
			if (temp[i][j] == bullet) { //當前位置為子彈
				canvas[i][j] = blank;
				if (temp[i - 1][j] == enemy) { //下個位置是敵機，敵機被擊毀
					canvas[i - 1][j] = blank;
					score++;
					printf("\a");
				}
				else if (i > 1) {//前面不是邊界，子彈往前一格
					canvas[i - 1][j] = bullet;
				}
			}
		}
	}
	if (interval % itv_new == 0) //到敵機生成時間間隔，生成敵機群
		for (int i = 0; i < enemynum; i++) { //新增敵機群
			canvas[rand() % 2 + 1][rand() % width + 1] = enemy;
		}
	if (interval < 200) { //時間間隔計次
		interval++;
	}
	else { //時間間隔計次重來
		interval = 1;
	}

}
void UpdateNormal2() { //與輸入無關的困難遊戲狀態更新
	int temp[high + 2][width + 2]; //用來判斷原位置的臨時陣列
	for (int i = 1; i <= high; i++) {
		for (int j = 1; j <= width; j++) {
			temp[i][j] = canvas[i][j];
		}
	}
	if (score >= difficulty4 && score < difficulty5) { //BOSS顯示與移動
		if (boss1 == 1 && interval % boss_move == 0) {
			for (int i = 1; i < 4; i++) {
				for (int j = 1; j <= width; j++) {
					canvas[i][j] = blank;
				}
			}
			if (temp[1][55] != boss && rand() % 2 == 0) {//BOSS隨機往右移動
				for (int i = 1; i < 4; i++) {
					for (int j = boss_y_start + i + 1; j <= boss_y_start + 10 - i + 1; j++) {
						canvas[i][j] = boss;
					}
				}
				boss_y_start++;
			}
			else if (temp[1][5] != boss) {//BOSS隨機往左移動
				for (int i = 1; i < 4; i++) {
					for (int j = boss_y_start + i - 1; j <= boss_y_start + 10 - i - 1; j++) {
						canvas[i][j] = boss;
					}
				}
				boss_y_start--;
			}
		}
		else if (interval % boss_move == 0) {//生成BOSS一次
			for (int i = 1; i < 4; i++) {
				for (int j = boss_y_start + i; j <= boss_y_start + 10 - i; j++) {
					canvas[i][j] = boss;
				}
			}
			boss1 = 1;
		}
	}
	for (int i = 1; i <= high; i++) { //遍歷臨時陣列，修改畫布
		for (int j = 1; j <= width; j++) {
			if (temp[i][j] == enemy && interval % itv_move == 0) { //當前位置為敵機
				canvas[i][j] = blank;
				if (temp[i + 1][j] == bullet) { //下面為子彈，敵機被擊中
					canvas[i + 1][j] = blank;
					score++;
					printf("\a"); //擊中音效
				}
				else if (i < high && rand() % 2 == 0) {//敵機隨機往右下移動
					if (canvas[i + 1][j + 1] == border)//如果旁邊是邊界就往下掉
						canvas[i + 1][j] = enemy;
					else
						canvas[i + 1][j + 1] = enemy;
				}
				else if (i < high) {//敵機隨機往左下移動
					if (canvas[i + 1][j - 1] == border)//如果旁邊是邊界就往下掉
						canvas[i + 1][j] = enemy;
					else
						canvas[i + 1][j - 1] = enemy;
				}
				if (i + 1 == pos_h && j == pos_w) { //下面為飛機，玩家飛機被撞毀
					canvas[i + 1][j] = destroy;
					IsOver = 0;
				}
			}
			if (temp[i][j] == boss) { //當前位置為BOSS
				if (temp[i + 1][j] == bullet) { //下面為子彈，BOSS被擊中
					att++;
					printf("\a"); //擊中音效
				}
				else if (i > 2 && temp[i + 1][j] == blank && interval % bullet_new == 0) {//BOSS前面為空且到子彈生成間隔，生成BOSS子彈
					canvas[i + 1][j] = b_bullet;
				}
				if (i + 1 == pos_h && j == pos_w) { //下面為飛機，玩家飛機被撞毀
					canvas[i + 1][j] = destroy;
					IsOver = 0;
				}
				else if (i == pos_h && j + 1 == pos_w) { //右邊為飛機，玩家飛機被撞毀
					canvas[i][j + 1] = destroy;
					IsOver = 0;
				}
				else if (i == pos_h && j - 1 == pos_w) { //左邊為飛機，玩家飛機被撞毀
					canvas[i][j - 1] = destroy;
					IsOver = 0;
				}
			}
			if (temp[i][j] == b_bullet && interval % bullet_move == 0) { //當前位置為BOSS子彈
				canvas[i][j] = blank;
				if (temp[i + 1][j] == bullet) { //下面為子彈，BOSS子彈被擊中
					canvas[i + 1][j] = blank;
				}
				else if (i < high) { //前面不是邊界，BOSS子彈往前一格
					canvas[i + 1][j] = b_bullet;
				}
				if (i + 1 == pos_h && j == pos_w) { //下面為飛機，玩家飛機被摧毀
					canvas[i + 1][j] = destroy;
					IsOver = 0;
				}
			}
			if (temp[i][j] == bullet) { //當前位置為子彈
				canvas[i][j] = blank;
				if (temp[i - 1][j] == enemy) { //下個位置是敵機，敵機被擊毀
					canvas[i - 1][j] = blank;
					score++;
					printf("\a");
				}
				else if (temp[i - 1][j] == boss) { //下個位置是BOSS，BOSS打擊數增加
					att++;
					printf("\a");
				}
				else if (temp[i - 1][j] == b_bullet) {//下個位置是BOSS子彈，BOSS子彈被擊毀
					canvas[i - 1][j] = blank;
				}
				else if (i > 1) {
					canvas[i - 1][j] = bullet;
				}
			}
		}
	}
	if (att >= 100) {//BOSS打擊數到100，BOSS消失
		for (int i = 1; i < 4; i++) {
			for (int j = 1; j <= width; j++) {
				canvas[i][j] = blank;
			}
		}
		att = 0;
		score += 50;
	}

	if (interval % itv_new == 0) //剛好到敵機生成時間間隔
		for (int i = 0; i < enemynum; i++) { //新增敵機群
			canvas[rand() % 2 + 1][rand() % width + 1] = enemy;
		}
	if (interval < 1000) { //時間間隔計次
		interval++;
	}
	else { //時間間隔計次清零
		interval = 1;
	}

}

void difficult1() { //用分數做難度區隔
	if (score >= difficulty1 && score < difficulty2) {
		itv_move = 10; //敵機移動速度加快
		itv_new = 20; //敵機生成速度加快
		enemynum = 3; //敵機一次生成數目減少
	}
	else if (score >= difficulty2 && score < difficulty3) {
		itv_move = 5; //敵機移動速度加快
	}
	else if (score >= difficulty3 && score < difficulty4) {
		itv_move = 2; //敵機移動速度加快
		itv_new = 10; //敵機生成速度加快
	}
	else if (score >= difficulty4 && score < difficulty5) {
		itv_move = 1; //敵機移動速度加快
		itv_new = 5; //敵機生成速度加快
	}
}
void difficult2() {//用分數做難度區隔
	if (score >= difficulty1 && score < difficulty2) {
		itv_move = 10; //敵機移動速度加快
		itv_new = 20; //敵機生成速度加快
		enemynum = 3; //敵機一次生成數目減少
	}
	else if (score >= difficulty2 && score < difficulty3) {
		itv_move = 5; //敵機移動速度加快
	}
	else if (score >= difficulty3 && score < difficulty4) {
		itv_move = 2; //敵機移動速度加快
		itv_new = 10; //敵機生成速度加快
	}
	else if (score >= difficulty4 && score < difficulty5) {
		itv_new = 1001; //敵機不再進行生成，BOSS出現
	}
	else if (score >= difficulty5) {
		itv_move = 2; //敵機移動速度加快
		itv_new = 8; //敵機生成速度加快
	}
}

void endgame() //結束畫面
{
	printf("GAME OVER !!!\t");
	Sleep(2000);
	int k;
	system("pause");
	system("cls");
	if (score > highscore) {
		highscore = score;
		printf("恭喜你突破最高紀錄!!!\n");
	}
	printf("最終分數:%d\n最高紀錄:%d\n", score, highscore);
	printf("輸入1再玩一次簡單模式\n輸入2再玩一次困難模式\n輸入3返回主選單\n輸入4退出遊戲\n請輸入：");
	scanf("%d", &k);
	system("cls");
	switch (k)
	{
	case 1:
		n = 1;
		printf("重新玩簡單模式");
		system("cls");
		Startup();   // 資料初始化
		Show();
		break;
	case 2:
		n = 2;
		printf("重新玩困難模式");
		system("cls");
		Startup();   // 資料初始化
		Show();
		break;
	case 3:
		printf("返回主選單");
		system("cls");
		welcometogame();
		Startup();
		break;
	case 4:printf("退出成功");
		exit(0);
		break;
	default:
		color(12);
		gotoxy(40, 28);
		system("cls");
		printf("輸入錯誤,輸入任意鍵回到主選單");
		_getch();  //輸入任意鍵
		welcometogame();
		Startup();
		system("cls");  //清屏
	}
}
void timesup() {  //倒數計時函數
	end = time(NULL) - start;
	times = 30 - (int)end;
	if (times == 0) {  //時間歸零遊戲結束
		IsOver = 0;
		canvas[pos_h][pos_w] = destroy;
	}
}





