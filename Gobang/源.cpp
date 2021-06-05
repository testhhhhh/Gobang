#include<graphics.h>//图形库头文件
#include<math.h>
#include<mmsystem.h>//倒入声音头文件
#pragma comment(lib,"winmm.lib")//播放音乐库头文件
#include<windows.h>;
int flag = 0;//表示下棋次数
int board[15][15] = { 0 };//初始化棋盘的状态
int score[15][15] = { 0 };//初始化棋盘的分数
int rrhuiqi[2];
int rjhuiqi[2][2];
int judge(int a, int b);
void Chess_ai_naive(int& x, int& y);//电脑获取最优解位置
void evaluate_naive();
void youxishuoming();
void manvsmanplayChess();
void manvsaiplayChess();
void ChessBorad();
//游戏大厅设计
void initGame()
{
	
	HWND hWnd = GetHWnd();//获取窗口句柄，即窗口的唯一标识符
	SetWindowText(hWnd, "五子棋游戏");//改变窗口标题
	IMAGE backgrand;//创建一个图像对象
	loadimage(&backgrand, "背景1.jpg", 700, 700);//装载光标，图标，位图，此为装载游戏大厅背景图
	putimage(0, 0, &backgrand);//在屏幕上输出一个位图
	MOUSEMSG m;		// 定义鼠标消息 

	while (true)
	{
		// 获取一条鼠标消息
		m = GetMouseMsg();

		//避免黑屏
		//putimage(0, 0, &backgrand);

		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:     //当在“客户区”按下鼠标的消息
			if (m.x >= 250 && m.x <= 450 && m.y >= 270 && m.y <= 340)  //玩家对战区域		
			{
				ChessBorad();   //棋盘界面初始化
				manvsmanplayChess();//人人对战
			}
			if (m.x >= 250 && m.x <= 450 && m.y >= 370 && m.y <= 440)  //人机对战区域	
			{
				ChessBorad();
				manvsaiplayChess();//人机对战
			}
			if (m.x >= 430 && m.x <= 620 && m.y >= 520 && m.y <= 575)  //音乐开区域		
			{
				mciSendString("open 音乐.mp3", 0, 0, 0);//设置背景音乐  多媒体控制接口
				mciSendString("play  音乐.mp3", 0, 0, 0);
			}
			if (m.x >= 430 && m.x <= 620 && m.y >= 590 && m.y <=650)  //音乐关区域		
			{
				mciSendString("pause 音乐.mp3", NULL, 0, NULL);
			}
			if (m.x >= 150 && m.x <= 350 && m.y >= 520 && m.y <= 580) {//游戏说明
				youxishuoming();
			}
			if (m.x >= 150 && m.x <= 350 && m.y >= 600 && m.y <= 700) {//退出游戏
				exit(0);
			}

		}

	}
}
//游戏说明函数
void youxishuoming() {
	IMAGE h2;
	loadimage(&h2, "背景3.jpg", 700, 700);
	putimage(0, 0, &h2);
	MOUSEMSG mg;
	while (true) {
		mg = GetMouseMsg();
		//避免黑屏
		putimage(0, 0, &h2);

		switch (mg.uMsg)
		{
		case WM_LBUTTONDOWN:     
			if (mg.x >= 400 && mg.x <= 660 && mg.y >= 450 && mg.y <= 600)//返回大厅界面区域
			{
				initGame();
			}

		}

	}
}
//初始化游戏棋盘界面
void ChessBorad() {
	loadimage(NULL, "背景2.jpg", 700, 700);
	setlinecolor(BLACK);//画线条为黑色
	for (int i = 175; i <550; i += 25)//循环画线
	{
		line(i, 175, i, 525);//画线函数，画竖线：第一个点（i，175），第二个点（i，525）
		line(175, i, 525, i);//画横线，第一个点（175，i），第二个点（525，i）
		setfillcolor(BLACK);
		solidcircle(350, 350, 3);
		solidcircle(250, 250, 3);
		solidcircle(450, 250, 3);
		solidcircle(250, 450, 3);
		solidcircle(450, 450, 3);
		
	}
	
}
//人人对决函数
void manvsmanplayChess()
{
	MOUSEMSG m;//保存鼠标消息
	int x, y;
	int a = 0, b = 0;
	while (1)
	{
		m = GetMouseMsg();

		for (int i = 0; i <=14; i++)//每行15个交点可以下，每格长宽25
		{
			for (int j = 0; j <=14; j++)
			{
				if (abs(m.x - (175 + (i * 25))) < 12 && abs(m.y - (175 + (j * 25))) < 12)//使得落子在交点上
				{                         
					x = 175 + i * 25;//第一条线在150，边边线不下，从第二条线开始即175
					y = 175 + j * 25;
					a = i;
					b = j;//用a,b记录鼠标点击位置方便后续判断
				}
			}

		}
		//下棋
		if (m.uMsg == WM_LBUTTONDOWN && (m.x > 162 && m.x <537 && m.y >162 && m.y <537))//鼠标消息为鼠标左键在棋盘区域内按下时
		{

			if (board[a][b] != 0)//不能重复下棋
			{
				MessageBox(NULL, "这里有棋子了请重新选择", "提示", MB_OK);//提示框，null为消息框没有拥有窗口
				continue;
			}
			if (flag % 2 == 0)//利用flag不断+1时奇偶性地不断变化来判断轮到哪个玩家下
			{
				setfillcolor(BLACK);//当flag为偶数则黑棋下
				solidcircle(x, y, 10);//获得鼠标x，y为画一个圆的圆心，半径10
				board[a][b] = 1;//玩家1在棋盘的（a,b）位置下了棋，则设置board为1，表示该位置玩家1有棋
			}
			else
			{
				setfillcolor(WHITE);
				solidcircle(x, y, 10);
				board[a][b] = 2;//玩家2下棋记录为2
			}

			flag++;//每次下一个棋，flag就加1
			rrhuiqi[0] = a;//利用一维数组来储存最近的一个落子点，rrhuiqi[0]记录落子点x值
			rrhuiqi[1] = b;//rrhuiqi[1]记录落子点y值

		}
		//悔棋
		else if (m.uMsg == WM_RBUTTONDOWN && (m.x > 162 && m.x <537  && m.y > 162 && m.y <537)) {//右键鼠标落在棋盘区域
			if (board[a][b] != 0 && (rrhuiqi[0] == a && rrhuiqi[1] == b)) {//棋盘有子处且是最近的落子点，即只能是悔最近的棋子，不能无限悔棋，不能跨步悔棋
				board[a][b] = 0;//悔棋后重置board数组该点处为空
				ChessBorad();//重绘棋盘上未落上一棋的局势
				for (int i = 0; i <=14; i++) {
					for (int j = 0; j <=14; j++) {
						if (board[i][j] == 1) {
							setfillcolor(BLACK);
							solidcircle(175 + (i * 25), 175 + (j * 25), 10);
						}
						if (board[i][j] == 2) {
							setfillcolor(WHITE);
							solidcircle(175 + (i * 25), 175 + (j * 25), 10);
						}

					}
				}
				flag--;//悔棋玩家再下一次
			}
			//无子或不在棋盘区域
			else {
				MessageBox(NULL, "悔棋失败", "提示", MB_OK);//提示框
				continue;
			}
		}
		if (judge(a, b))//每下一子判断是否产生赢家
		{
			if ((flag -1)% 2 == 1)//白棋落子后产生赢家
			{
				MessageBox(NULL, "白棋获胜", "游戏结束", MB_OK);
				memset(board, 0, sizeof(board));
				flag = 0;
				initGame();
			}
			else
			{
				MessageBox(NULL, "黑棋获胜", "游戏结束", MB_OK);
				memset(board, 0, sizeof(board));
				flag = 0;
				initGame();
			}
		}
		if(!judge(a,b)&&flag==225) {
			MessageBox(NULL, "平局", "游戏结束", MB_OK);
			memset(board, 0, sizeof(board));
			flag = 0;
			initGame();
		}
		if ((m.uMsg == WM_LBUTTONDOWN)&& m.x >= 450 && m.x <= 625 && m.y >= 50 && m.y <= 100)//点击返回大厅
		{
			memset(board, 0, sizeof(board));
			flag = 0;
			initGame();
		} 
	}
}
//判断输赢
int judge(int a, int b)
	{
		int i, j;
		int t = 2 - flag % 2;//玩家1时，board记录也为1，玩家2则board也为2
		for (i = a - 4, j = b; i <= a; i++)//判断横方向的5个棋子是否连成
		{
			if (i >= 0 && i <= 11 && t == board[i][j] && t == board[i + 1][j] && t == board[i + 2][j] && t == board[i + 3][j] && t == board[i + 4][j])
				return 1;
		}
		for (i = a, j = b - 4; j <= b; j++)//判断竖方向的5个棋子是否连成
		{
			if (j >= 0 && j <= 11 && t == board[i][j] && t == board[i][j + 1] && t == board[i][j + 2] && t == board[i][j + 3] && t == board[i][j + 4])
				return 1;
		}
		for (i = a - 4, j = b - 4; i<= a && j <= b; j++, i++)//判断斜左上方的5个棋子是否连成
		{
			if (j >= 0 && j <= 11 && i >= 0 && i <= 11 && t == board[i][j] && t == board[i + 1][j + 1] && t == board[i + 2][j + 2] && t == board[i + 3][j + 3] && t == board[i + 4][j + 4])
				return 1;
		}
		for (i = a +4, j = b -4; i>= a && j <= b; i--, j++)//判断斜右上方的5个棋子是否连成
		{
			if (j >= 0 && j <= 11 && i >= 0 && i <= 11 && t == board[i][j] && t == board[i - 1][j +1] && t == board[i - 2][j + 2] && t == board[i - 3][j + 3] && t == board[i - 4][j + 4])
				return 1;
		}

		return 0;
	}
//每个空子的评估函数 权值法
void evaluate_naive()	//需要对人落子和电脑已落子进行评价。人落子电脑要堵，电脑自己落子要做成5子 
	{
		memset(score, 0, sizeof(score));//清空score数组，即把sizeof(score)长度的score数组里的值全为0
		int number1, number2, empty;//number1为方向上人子数，number2为方向上电脑子数，empty为空子数
		for (int x = 0; x <=14; ++x)
			for (int y = 0; y <=14; ++y)
				if (board[x][y] == 0)//评估每个空子
					for (int i = -1; i <= 1; ++i)
						for (int j = -1; j <= 1; ++j)//每个空位的8个方向
							if (!(i == 0 && j == 0))//0,0不动不用算 
							{
								int k = 0;
								number1 = 0, number2 = 0, empty = 0;
								//对人落子评分（要对人所下的子进行围堵，玩家在这儿落子后的估分越高，电脑就越有必要下在这儿，来打破玩家的意图） 
								//每个方向上的正方向
								for (k = 1; k <= 5; ++k)
									if (x + i * k >= 0 && x + i * k <= 14 && y + j * k >= 0 && y + j * k <= 14 && board[x + i * k][y + j * k] == 1)	++number1;
									else if (x + i * k >= 0 && x + i * k <= 14 && y + j * k >= 0 && y + j * k <= 14 && board[x + i * k][y + j * k] == 0) { ++empty; break; }
									else	break;
								//每个方向上的反方向
								for (k = -1; k >= -5; --k)
									if (x + i * k >= 0 && x + i * k <= 14 && y + j * k >= 0 && y + j * k <= 14 && board[x + i * k][y + j * k] == 1)	++number1;
									else if (x + i * k >= 0 && x + i * k <= 14 && y + j * k >= 0 && y + j * k <= 14 && board[x + i * k][y + j * k] == 0) { ++empty; break; }
									else	break;
								if (number1 == 1)	score[x][y] += 1;	//人若下该空子，就两子了，那么不管死活都是+1
								else if (number1 == 2)
								{
									if (empty == 1)	score[x][y] += 5;	//三子，死，+5
									else if (empty == 2)	score[x][y] += 10;//三子，活，+10	 
								}
								else if (number1 == 3)
								{
									if (empty == 1)	score[x][y] += 20;//形成死四，+20
									else if (empty == 2)	score[x][y] += 100;//形成活四，+100 
								}
								else if (number1 == 4) score[x][y] += 1000;//五子，+1000
								//对电脑落子评分（我自己下了这个空子，会怎样）
								empty = 0;
								for (k = 1; k <= 5; ++k)
									if (x + i * k >= 0 && x + i * k <= 14 && y + j * k >= 0 && y + j * k <= 14 && board[x + i * k][y + j * k] == 2)	++number2;
									else if (x + i * k >= 0 && x + i * k <= 14 && y + j * k >= 0 && y + j * k <= 14 && board[x + i * k][y + j * k] == 0) { ++empty; break; }
									else	break;
								for (k = -1; k >= -5; --k)
									if (x + i * k >= 0 && x + i * k <= 14 && y + j * k >= 0 && y + j * k <= 14 && board[x + i * k][y + j * k] == 2)	++number2;
									else if (x + i * k >= 0 && x + i * k <= 14 && y + j * k >= 0 && y + j * k <= 14 && board[x + i * k][y + j * k] == 0) { ++empty; break; }
									else	break;//碰到边边
								if (number2 == 0)	score[x][y] += 1;	//电脑若下了该空子，就一子了，那么不管死活都是+1 
								else if (number2 == 1)	score[x][y] += 2;	//两子，+2 
								else if (number2 == 2)
								{
									if (empty == 1)	score[x][y] += 8;	//三子，死，+8
									else if (empty == 2)	score[x][y] += 30;//三子，活，+30	
								}
								else if (number2 == 3)
								{
									if (empty == 1)	score[x][y] += 50;//四子，死，+50 
									else if (empty == 2)	score[x][y] += 200;//四子，活，+200 
								}
								else if (number2 == 4) score[x][y] += 10000;	//五子，+10000 
							}
	}
//电脑获取最优解位置
void Chess_ai_naive(int& x, int& y)
	{//搜的是当前的第一个最优解 
		evaluate_naive();
		int maxpos = 0;
		for (int i = 0; i <=14; ++i)
			for (int j = 0; j <=14; ++j)
				if (score[i][j] > maxpos)
				{
					maxpos = score[i][j];
					x = i;
					y = j;//找出分数最高的点，记录并返回
				}
	}
//人机下棋
void manvsaiplayChess() {
		MOUSEMSG m;//保存鼠标消息
		int x, y;
		int a = 0, b = 0;
		while (1) {
			if (flag % 2 == 0) {
				m = GetMouseMsg();
				outtextxy(300, 600, "玩家下");
				for (int i = 0; i <=14; i++)
				{
					for (int j = 0; j <=14; j++)
					{
						if (abs(m.x - (175 + (i * 25))) < 12 && abs(m.y - (175 + (j * 25))) < 12)
						{
							x = 175 + i * 25;
							y = 175 + j * 25;
							a = i;
							b = j;
						}
					}
				}
				//人下棋
				if (m.uMsg == WM_LBUTTONDOWN&& (m.x > 160 && m.x < 537 && m.y >162 && m.y < 537))
				{
					if (board[a][b] != 0)//不能重复下棋
					{
						MessageBox(NULL, "这里有棋子了请重新选择", "提示", MB_OK);//提示框
						continue;
					 }
					
						setfillcolor(BLACK);
						solidcircle(x, y, 10);//获得鼠标x，y为画一个圆的圆心，半径10
						board[a][b] = 1;

						flag++;//每次下一个棋，flag就加1

						rjhuiqi[0][0] = a;
						rjhuiqi[0][1] = b;
						if (judge(a, b)) {
							MessageBox(NULL, "黑棋获胜", "游戏结束", MB_OK);
							memset(board, 0, sizeof(board));
							memset(score, 0, sizeof(score));
							flag = 0;
							initGame();
						}
						if (!judge(a, b) && flag == 225) {
							MessageBox(NULL, "平局", "游戏结束", MB_OK);
							memset(board, 0, sizeof(board));
							memset(score, 0, sizeof(score));
							flag = 0;
							initGame();
						}
					
				}
				//人悔棋
				if (m.uMsg == WM_RBUTTONDOWN && (m.x > 160 && m.x < 537 && m.y >162 && m.y < 537)) {

					if (board[a][b] != 0&&(rjhuiqi[0][0] == a&&rjhuiqi[0][1] == b)) {
						board[a][b] = 0;
						board[rjhuiqi[1][0]][rjhuiqi[1][1]] = 0;//电脑下的上一步也退回
						ChessBorad();
						for (int i = 0; i <=14; i++) {
							for (int j = 0; j <=14; j++) {
								if (board[i][j] == 1) {
									setfillcolor(BLACK);
									solidcircle(175 + (i * 25), 175 + (j * 25), 10);
								}
								if (board[i][j] == 2) {
									setfillcolor(WHITE);
									solidcircle(175 + (i * 25), 175 + (j * 25), 10);
								}

							}
						}
						flag-2;//人和电脑都退
					}
					else {
						MessageBox(NULL, "不可悔棋", "提示", MB_OK);//提示框
						continue;
					}
				}
				//人机返回大厅
				if ((m.uMsg == WM_LBUTTONDOWN) && m.x >= 450 && m.x <= 625 && m.y >= 50 && m.y <= 100)
				{   //全部重置
					memset(board, 0, sizeof(board));
					memset(score, 0, sizeof(score));
					flag = 0;
					initGame();
				}
			}

			if (flag % 2 == 1) {
				outtextxy(300, 600, "电脑下");
				Chess_ai_naive(a, b);//评估人下的每一个棋子
				setfillcolor(WHITE);
				solidcircle(175+ a * 25, 175 + b * 25, 10);
				board[a][b] = 2;
				flag++;
				rjhuiqi[1][0] = a;//人机悔棋记录坐标，rjhuiqi[1][0]记录x坐标，rjhuiqi[1][1] = b记录y坐标
				rjhuiqi[1][1] = b;
				if (judge(a, b)){
					MessageBox(NULL, "白棋获胜", "游戏结束", MB_OK);
					memset(board, 0, sizeof(board));
					memset(score, 0, sizeof(score));
					flag = 0;
					initGame();
				}
				if (!judge(a, b) && flag == 225) {
					MessageBox(NULL, "平局", "游戏结束", MB_OK);
					memset(board, 0, sizeof(board));
					memset(score, 0, sizeof(score));
					flag = 0;
					initGame();
				}
			}
		}
	}
int main()
	{

		initgraph(700, 700);//初始化图形系统
		initGame();
		while (1);//防止闪退
		return 0;

	}