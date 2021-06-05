#include<graphics.h>//ͼ�ο�ͷ�ļ�
#include<math.h>
#include<mmsystem.h>//��������ͷ�ļ�
#pragma comment(lib,"winmm.lib")//�������ֿ�ͷ�ļ�
#include<windows.h>;
int flag = 0;//��ʾ�������
int board[15][15] = { 0 };//��ʼ�����̵�״̬
int score[15][15] = { 0 };//��ʼ�����̵ķ���
int rrhuiqi[2];
int rjhuiqi[2][2];
int judge(int a, int b);
void Chess_ai_naive(int& x, int& y);//���Ի�ȡ���Ž�λ��
void evaluate_naive();
void youxishuoming();
void manvsmanplayChess();
void manvsaiplayChess();
void ChessBorad();
//��Ϸ�������
void initGame()
{
	
	HWND hWnd = GetHWnd();//��ȡ���ھ���������ڵ�Ψһ��ʶ��
	SetWindowText(hWnd, "��������Ϸ");//�ı䴰�ڱ���
	IMAGE backgrand;//����һ��ͼ�����
	loadimage(&backgrand, "����1.jpg", 700, 700);//װ�ع�꣬ͼ�꣬λͼ����Ϊװ����Ϸ��������ͼ
	putimage(0, 0, &backgrand);//����Ļ�����һ��λͼ
	MOUSEMSG m;		// ���������Ϣ 

	while (true)
	{
		// ��ȡһ�������Ϣ
		m = GetMouseMsg();

		//�������
		//putimage(0, 0, &backgrand);

		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:     //���ڡ��ͻ���������������Ϣ
			if (m.x >= 250 && m.x <= 450 && m.y >= 270 && m.y <= 340)  //��Ҷ�ս����		
			{
				ChessBorad();   //���̽����ʼ��
				manvsmanplayChess();//���˶�ս
			}
			if (m.x >= 250 && m.x <= 450 && m.y >= 370 && m.y <= 440)  //�˻���ս����	
			{
				ChessBorad();
				manvsaiplayChess();//�˻���ս
			}
			if (m.x >= 430 && m.x <= 620 && m.y >= 520 && m.y <= 575)  //���ֿ�����		
			{
				mciSendString("open ����.mp3", 0, 0, 0);//���ñ�������  ��ý����ƽӿ�
				mciSendString("play  ����.mp3", 0, 0, 0);
			}
			if (m.x >= 430 && m.x <= 620 && m.y >= 590 && m.y <=650)  //���ֹ�����		
			{
				mciSendString("pause ����.mp3", NULL, 0, NULL);
			}
			if (m.x >= 150 && m.x <= 350 && m.y >= 520 && m.y <= 580) {//��Ϸ˵��
				youxishuoming();
			}
			if (m.x >= 150 && m.x <= 350 && m.y >= 600 && m.y <= 700) {//�˳���Ϸ
				exit(0);
			}

		}

	}
}
//��Ϸ˵������
void youxishuoming() {
	IMAGE h2;
	loadimage(&h2, "����3.jpg", 700, 700);
	putimage(0, 0, &h2);
	MOUSEMSG mg;
	while (true) {
		mg = GetMouseMsg();
		//�������
		putimage(0, 0, &h2);

		switch (mg.uMsg)
		{
		case WM_LBUTTONDOWN:     
			if (mg.x >= 400 && mg.x <= 660 && mg.y >= 450 && mg.y <= 600)//���ش�����������
			{
				initGame();
			}

		}

	}
}
//��ʼ����Ϸ���̽���
void ChessBorad() {
	loadimage(NULL, "����2.jpg", 700, 700);
	setlinecolor(BLACK);//������Ϊ��ɫ
	for (int i = 175; i <550; i += 25)//ѭ������
	{
		line(i, 175, i, 525);//���ߺ����������ߣ���һ���㣨i��175�����ڶ����㣨i��525��
		line(175, i, 525, i);//�����ߣ���һ���㣨175��i�����ڶ����㣨525��i��
		setfillcolor(BLACK);
		solidcircle(350, 350, 3);
		solidcircle(250, 250, 3);
		solidcircle(450, 250, 3);
		solidcircle(250, 450, 3);
		solidcircle(450, 450, 3);
		
	}
	
}
//���˶Ծ�����
void manvsmanplayChess()
{
	MOUSEMSG m;//���������Ϣ
	int x, y;
	int a = 0, b = 0;
	while (1)
	{
		m = GetMouseMsg();

		for (int i = 0; i <=14; i++)//ÿ��15����������£�ÿ�񳤿�25
		{
			for (int j = 0; j <=14; j++)
			{
				if (abs(m.x - (175 + (i * 25))) < 12 && abs(m.y - (175 + (j * 25))) < 12)//ʹ�������ڽ�����
				{                         
					x = 175 + i * 25;//��һ������150���߱��߲��£��ӵڶ����߿�ʼ��175
					y = 175 + j * 25;
					a = i;
					b = j;//��a,b��¼�����λ�÷�������ж�
				}
			}

		}
		//����
		if (m.uMsg == WM_LBUTTONDOWN && (m.x > 162 && m.x <537 && m.y >162 && m.y <537))//�����ϢΪ�����������������ڰ���ʱ
		{

			if (board[a][b] != 0)//�����ظ�����
			{
				MessageBox(NULL, "������������������ѡ��", "��ʾ", MB_OK);//��ʾ��nullΪ��Ϣ��û��ӵ�д���
				continue;
			}
			if (flag % 2 == 0)//����flag����+1ʱ��ż�Եز��ϱ仯���ж��ֵ��ĸ������
			{
				setfillcolor(BLACK);//��flagΪż���������
				solidcircle(x, y, 10);//������x��yΪ��һ��Բ��Բ�ģ��뾶10
				board[a][b] = 1;//���1�����̵ģ�a,b��λ�������壬������boardΪ1����ʾ��λ�����1����
			}
			else
			{
				setfillcolor(WHITE);
				solidcircle(x, y, 10);
				board[a][b] = 2;//���2�����¼Ϊ2
			}

			flag++;//ÿ����һ���壬flag�ͼ�1
			rrhuiqi[0] = a;//����һά���������������һ�����ӵ㣬rrhuiqi[0]��¼���ӵ�xֵ
			rrhuiqi[1] = b;//rrhuiqi[1]��¼���ӵ�yֵ

		}
		//����
		else if (m.uMsg == WM_RBUTTONDOWN && (m.x > 162 && m.x <537  && m.y > 162 && m.y <537)) {//�Ҽ����������������
			if (board[a][b] != 0 && (rrhuiqi[0] == a && rrhuiqi[1] == b)) {//�������Ӵ�������������ӵ㣬��ֻ���ǻ���������ӣ��������޻��壬���ܿ粽����
				board[a][b] = 0;//���������board����õ㴦Ϊ��
				ChessBorad();//�ػ�������δ����һ��ľ���
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
				flag--;//�����������һ��
			}
			//���ӻ�����������
			else {
				MessageBox(NULL, "����ʧ��", "��ʾ", MB_OK);//��ʾ��
				continue;
			}
		}
		if (judge(a, b))//ÿ��һ���ж��Ƿ����Ӯ��
		{
			if ((flag -1)% 2 == 1)//�������Ӻ����Ӯ��
			{
				MessageBox(NULL, "�����ʤ", "��Ϸ����", MB_OK);
				memset(board, 0, sizeof(board));
				flag = 0;
				initGame();
			}
			else
			{
				MessageBox(NULL, "�����ʤ", "��Ϸ����", MB_OK);
				memset(board, 0, sizeof(board));
				flag = 0;
				initGame();
			}
		}
		if(!judge(a,b)&&flag==225) {
			MessageBox(NULL, "ƽ��", "��Ϸ����", MB_OK);
			memset(board, 0, sizeof(board));
			flag = 0;
			initGame();
		}
		if ((m.uMsg == WM_LBUTTONDOWN)&& m.x >= 450 && m.x <= 625 && m.y >= 50 && m.y <= 100)//������ش���
		{
			memset(board, 0, sizeof(board));
			flag = 0;
			initGame();
		} 
	}
}
//�ж���Ӯ
int judge(int a, int b)
	{
		int i, j;
		int t = 2 - flag % 2;//���1ʱ��board��¼ҲΪ1�����2��boardҲΪ2
		for (i = a - 4, j = b; i <= a; i++)//�жϺ᷽���5�������Ƿ�����
		{
			if (i >= 0 && i <= 11 && t == board[i][j] && t == board[i + 1][j] && t == board[i + 2][j] && t == board[i + 3][j] && t == board[i + 4][j])
				return 1;
		}
		for (i = a, j = b - 4; j <= b; j++)//�ж��������5�������Ƿ�����
		{
			if (j >= 0 && j <= 11 && t == board[i][j] && t == board[i][j + 1] && t == board[i][j + 2] && t == board[i][j + 3] && t == board[i][j + 4])
				return 1;
		}
		for (i = a - 4, j = b - 4; i<= a && j <= b; j++, i++)//�ж�б���Ϸ���5�������Ƿ�����
		{
			if (j >= 0 && j <= 11 && i >= 0 && i <= 11 && t == board[i][j] && t == board[i + 1][j + 1] && t == board[i + 2][j + 2] && t == board[i + 3][j + 3] && t == board[i + 4][j + 4])
				return 1;
		}
		for (i = a +4, j = b -4; i>= a && j <= b; i--, j++)//�ж�б���Ϸ���5�������Ƿ�����
		{
			if (j >= 0 && j <= 11 && i >= 0 && i <= 11 && t == board[i][j] && t == board[i - 1][j +1] && t == board[i - 2][j + 2] && t == board[i - 3][j + 3] && t == board[i - 4][j + 4])
				return 1;
		}

		return 0;
	}
//ÿ�����ӵ��������� Ȩֵ��
void evaluate_naive()	//��Ҫ�������Ӻ͵��������ӽ������ۡ������ӵ���Ҫ�£������Լ�����Ҫ����5�� 
	{
		memset(score, 0, sizeof(score));//���score���飬����sizeof(score)���ȵ�score�������ֵȫΪ0
		int number1, number2, empty;//number1Ϊ��������������number2Ϊ�����ϵ���������emptyΪ������
		for (int x = 0; x <=14; ++x)
			for (int y = 0; y <=14; ++y)
				if (board[x][y] == 0)//����ÿ������
					for (int i = -1; i <= 1; ++i)
						for (int j = -1; j <= 1; ++j)//ÿ����λ��8������
							if (!(i == 0 && j == 0))//0,0���������� 
							{
								int k = 0;
								number1 = 0, number2 = 0, empty = 0;
								//�����������֣�Ҫ�������µ��ӽ���Χ�£������������Ӻ�Ĺ���Խ�ߣ����Ծ�Խ�б�Ҫ�����������������ҵ���ͼ�� 
								//ÿ�������ϵ�������
								for (k = 1; k <= 5; ++k)
									if (x + i * k >= 0 && x + i * k <= 14 && y + j * k >= 0 && y + j * k <= 14 && board[x + i * k][y + j * k] == 1)	++number1;
									else if (x + i * k >= 0 && x + i * k <= 14 && y + j * k >= 0 && y + j * k <= 14 && board[x + i * k][y + j * k] == 0) { ++empty; break; }
									else	break;
								//ÿ�������ϵķ�����
								for (k = -1; k >= -5; --k)
									if (x + i * k >= 0 && x + i * k <= 14 && y + j * k >= 0 && y + j * k <= 14 && board[x + i * k][y + j * k] == 1)	++number1;
									else if (x + i * k >= 0 && x + i * k <= 14 && y + j * k >= 0 && y + j * k <= 14 && board[x + i * k][y + j * k] == 0) { ++empty; break; }
									else	break;
								if (number1 == 1)	score[x][y] += 1;	//�����¸ÿ��ӣ��������ˣ���ô���������+1
								else if (number1 == 2)
								{
									if (empty == 1)	score[x][y] += 5;	//���ӣ�����+5
									else if (empty == 2)	score[x][y] += 10;//���ӣ��+10	 
								}
								else if (number1 == 3)
								{
									if (empty == 1)	score[x][y] += 20;//�γ����ģ�+20
									else if (empty == 2)	score[x][y] += 100;//�γɻ��ģ�+100 
								}
								else if (number1 == 4) score[x][y] += 1000;//���ӣ�+1000
								//�Ե����������֣����Լ�����������ӣ���������
								empty = 0;
								for (k = 1; k <= 5; ++k)
									if (x + i * k >= 0 && x + i * k <= 14 && y + j * k >= 0 && y + j * k <= 14 && board[x + i * k][y + j * k] == 2)	++number2;
									else if (x + i * k >= 0 && x + i * k <= 14 && y + j * k >= 0 && y + j * k <= 14 && board[x + i * k][y + j * k] == 0) { ++empty; break; }
									else	break;
								for (k = -1; k >= -5; --k)
									if (x + i * k >= 0 && x + i * k <= 14 && y + j * k >= 0 && y + j * k <= 14 && board[x + i * k][y + j * k] == 2)	++number2;
									else if (x + i * k >= 0 && x + i * k <= 14 && y + j * k >= 0 && y + j * k <= 14 && board[x + i * k][y + j * k] == 0) { ++empty; break; }
									else	break;//�����߱�
								if (number2 == 0)	score[x][y] += 1;	//���������˸ÿ��ӣ���һ���ˣ���ô���������+1 
								else if (number2 == 1)	score[x][y] += 2;	//���ӣ�+2 
								else if (number2 == 2)
								{
									if (empty == 1)	score[x][y] += 8;	//���ӣ�����+8
									else if (empty == 2)	score[x][y] += 30;//���ӣ��+30	
								}
								else if (number2 == 3)
								{
									if (empty == 1)	score[x][y] += 50;//���ӣ�����+50 
									else if (empty == 2)	score[x][y] += 200;//���ӣ��+200 
								}
								else if (number2 == 4) score[x][y] += 10000;	//���ӣ�+10000 
							}
	}
//���Ի�ȡ���Ž�λ��
void Chess_ai_naive(int& x, int& y)
	{//�ѵ��ǵ�ǰ�ĵ�һ�����Ž� 
		evaluate_naive();
		int maxpos = 0;
		for (int i = 0; i <=14; ++i)
			for (int j = 0; j <=14; ++j)
				if (score[i][j] > maxpos)
				{
					maxpos = score[i][j];
					x = i;
					y = j;//�ҳ�������ߵĵ㣬��¼������
				}
	}
//�˻�����
void manvsaiplayChess() {
		MOUSEMSG m;//���������Ϣ
		int x, y;
		int a = 0, b = 0;
		while (1) {
			if (flag % 2 == 0) {
				m = GetMouseMsg();
				outtextxy(300, 600, "�����");
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
				//������
				if (m.uMsg == WM_LBUTTONDOWN&& (m.x > 160 && m.x < 537 && m.y >162 && m.y < 537))
				{
					if (board[a][b] != 0)//�����ظ�����
					{
						MessageBox(NULL, "������������������ѡ��", "��ʾ", MB_OK);//��ʾ��
						continue;
					 }
					
						setfillcolor(BLACK);
						solidcircle(x, y, 10);//������x��yΪ��һ��Բ��Բ�ģ��뾶10
						board[a][b] = 1;

						flag++;//ÿ����һ���壬flag�ͼ�1

						rjhuiqi[0][0] = a;
						rjhuiqi[0][1] = b;
						if (judge(a, b)) {
							MessageBox(NULL, "�����ʤ", "��Ϸ����", MB_OK);
							memset(board, 0, sizeof(board));
							memset(score, 0, sizeof(score));
							flag = 0;
							initGame();
						}
						if (!judge(a, b) && flag == 225) {
							MessageBox(NULL, "ƽ��", "��Ϸ����", MB_OK);
							memset(board, 0, sizeof(board));
							memset(score, 0, sizeof(score));
							flag = 0;
							initGame();
						}
					
				}
				//�˻���
				if (m.uMsg == WM_RBUTTONDOWN && (m.x > 160 && m.x < 537 && m.y >162 && m.y < 537)) {

					if (board[a][b] != 0&&(rjhuiqi[0][0] == a&&rjhuiqi[0][1] == b)) {
						board[a][b] = 0;
						board[rjhuiqi[1][0]][rjhuiqi[1][1]] = 0;//�����µ���һ��Ҳ�˻�
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
						flag-2;//�˺͵��Զ���
					}
					else {
						MessageBox(NULL, "���ɻ���", "��ʾ", MB_OK);//��ʾ��
						continue;
					}
				}
				//�˻����ش���
				if ((m.uMsg == WM_LBUTTONDOWN) && m.x >= 450 && m.x <= 625 && m.y >= 50 && m.y <= 100)
				{   //ȫ������
					memset(board, 0, sizeof(board));
					memset(score, 0, sizeof(score));
					flag = 0;
					initGame();
				}
			}

			if (flag % 2 == 1) {
				outtextxy(300, 600, "������");
				Chess_ai_naive(a, b);//�������µ�ÿһ������
				setfillcolor(WHITE);
				solidcircle(175+ a * 25, 175 + b * 25, 10);
				board[a][b] = 2;
				flag++;
				rjhuiqi[1][0] = a;//�˻������¼���꣬rjhuiqi[1][0]��¼x���꣬rjhuiqi[1][1] = b��¼y����
				rjhuiqi[1][1] = b;
				if (judge(a, b)){
					MessageBox(NULL, "�����ʤ", "��Ϸ����", MB_OK);
					memset(board, 0, sizeof(board));
					memset(score, 0, sizeof(score));
					flag = 0;
					initGame();
				}
				if (!judge(a, b) && flag == 225) {
					MessageBox(NULL, "ƽ��", "��Ϸ����", MB_OK);
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

		initgraph(700, 700);//��ʼ��ͼ��ϵͳ
		initGame();
		while (1);//��ֹ����
		return 0;

	}