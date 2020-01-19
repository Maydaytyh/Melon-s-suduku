#ifndef _sudoku_H
#define _sudoku_H
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<string>
#include<random>
#include<time.h>
#include <fstream>
using namespace std;
/****                                   ����������                           ****/
const int FirstNum = 5;//(2+2)%9+1=5
int nn = 1;
char sudodo[1000005][10][20];
int problem_sudoku[1000005][10][10];
int num_of_problem = 0;
class Sudoku {
public:
	int num[9] = { 1,2,3,4,6,7,8,9 };
	int num_use[9];
	int offset[8] = { 3,6,1,4,7,2,5,8 };
	int sudoku[10][10];
	bool ok = false;
	void print()
	{	
		//0 1 2 
		for (int i = 0; i < 9; ++i)
		{	
			//012345
			for (int j = 0; j <16; j+=2)
			{
				sudodo[nn][i][j] = sudoku[i][j/2] + '0';
				sudodo[nn][i][j+1] = ' ';
			}
			sudodo[nn][i][16] = sudoku[i][8]+'0';
			sudodo[nn][i][17] = '\n';
			sudodo[nn][i][18] = '\0';
		}
		strcpy(sudodo[nn][9], "\n");
		nn++;
		/*for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
				printf("%d ", sudoku[i][j]);
			puts("");
		}*/
	}
	void GetSudoku(int Num[9][9])
	{
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j)
			{
				sudoku[i][j] = Num[i][j];
			}
	}
	void generate_final(int num_of_sudoku)
	{
		//cout << "��ʼ��!" << endl;
		sudoku[0][0] = 5;
		do
		{
			//int offset[8] = { 3,6,1,4,7,2,5,8 };
			//�����һ��
			for (int i = 1; i < 9; i++)
				sudoku[0][i] = num[i - 1];
			//����ʣ�����
			for (int i = 1; i < 9; ++i)
			{
				for (int j = 0; j < 9; ++j)
				{
					int shifted = offset[i - 1] + j;//
					if (shifted >= 9) shifted -= 9;
					sudoku[i][shifted] = sudoku[0][j];
				}
			}
			print();
			if (nn > num_of_sudoku) return;
			Sudoku tmpSudoku;
			int sudoku_1[9][9];
			//���Ź���
			int num_2[3] = { 0,1,2 }, num_3[3] = { 0,1,2 };
			for (int i = 0; i < 3; ++i)
				for (int j = 0; j < 9; ++j)
					tmpSudoku.sudoku[i][j] = sudoku[i][j];
			do
			{
				for (int i = 3; i < 6; ++i)
				{
					for (int j = 0; j < 9; ++j)
						tmpSudoku.sudoku[i][j] = sudoku[num_2[i - 3] + 3][j];
				}
				do
				{
					for (int i = 6; i < 9; ++i)
					{
						for (int j = 0; j < 9; ++j)
							tmpSudoku.sudoku[i][j] = sudoku[num_3[i - 6] + 6][j];
					}
					tmpSudoku.print();

					if (nn > num_of_sudoku) return;
				} while (next_permutation(num_3, num_3 + 3));
			} while (next_permutation(num_2, num_2 + 3));
		} while (next_permutation(num, num + 8));
	}
	///�ж��к����Ƿ�����
	bool row_column(int x, int y, int num)
	{
		for (int i = 0; i < 9; i++)
		{
			if (sudoku[x][i] == num && i != y)
				return false;
			if (sudoku[i][y] == num && i != x)
				return false;
		}
		return true;
	}
	//void GenerateProblem(int n)
	//{
	//    int NumOfEmpty = rand() % 31+30;//���г����ɿ�λ����Ŀ
	//    while (NumOfEmpty)
	//    {

	//    }
	//}
	///�ж�3*3���������Ƿ�����
	bool Judge(int x, int y, int num)
	{
		int xx = x / 3;
		int yy = y / 3;
		for (int i = xx * 3; i < xx * 3 + 3; i++)
			for (int j = yy * 3; j < yy * 3 + 3; j++)
			{
				if (sudoku[i][j] == num)
				{
					if (i == x && j == y)
						continue;
					else
						return false;
				}
			}
		return true;
	}
	bool DFS(int sum)
	{
		if (sum >= 81)
		{
			return true;
		}
		int x = sum / 9;
		int y = sum % 9;
		if (!sudoku[x][y])
		{
			for (int i = 1; i <= 9; i++)
			{
				sudoku[x][y] = i;
				if (row_column(x, y, i) && Judge(x, y, i))
					if (DFS(sum + 1))
						return true;
				sudoku[x][y] = 0;
			}
		}
		else
			return DFS(sum + 1);
		return false;
	}
};

bool get(char* num, int& n)
{
	int len = strlen(num);
	int ans = 0;
	int f = 1;
	for (int i = 0; i < len; ++i)
	{
		if (num[i] >= '0' && num[i] <= '9')
			ans = ans * 10 + num[i] - '0';
		else if (num[i] == '-')
		{
			f = -1;
		}
		else return false;
	}
	n = ans * f;
	return true;
}
void PrintAns()
{
	for (int i = 1; i < nn; ++i)
	{
		//cout << "ID=" << i << endl;
		for (int j = 0; j < 9; ++j)
		{

			//printf("%s\n", sudodo[i][j]);
		/*	for (int k = 0; k < 18; ++k)
		{*/
				printf("%s", sudodo[i][j]);
				//putchar(sudodo[i][j][k]);
				//putchar(' ');
		//	}
			//putchar('\n');
			/*putchar(sudodo[i][j][8]);
			putchar('\n');*/
			/*printf("%c\n", sudodo[i][j][8]);*/
		}
		putchar('\n');
		//puts("");
	}
}
bool InputCheck(int argc, char** argv)
{
	if (argc < 3 || (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-s") != 0))
	{
		puts("------------------����-----------");
		puts("���������ʹ������������룡");
		puts("��������淶����");
		puts("-s Ҫ���ɵ������վֵĸ���n(n>0&&n<=1000000");
		puts("-c Ҫ�����������Ŀ���ļ�·��");
		return false;
	}
	else if ((strcmp(argv[1], "-c") == 0))
	{
		int n;
		bool flag = get(argv[2], n);
		if (n <= 0 || n > 1000000)
		{
			puts("------------------����-----------");
			puts("�������Ҫ���ɵ������վָ����������������룡");
			puts("��������淶����");
			puts("-s Ҫ���ɵ������վֵĸ���n(n>0&&n<=1000000");
			puts("-c Ҫ�����������Ŀ���ļ�·��");
			return false;
		}
	}
	else if (strcmp(argv[1], "-s") == 0)
	{
		ifstream infile;
		infile.open(argv[2], ios::in);
		if (!infile.is_open())
		{
			puts("------------------����-----------");
			puts("��������ļ�·���޷��򿪣����������룡");
			puts("��������淶����");
			puts("-s Ҫ���ɵ������վֵĸ���n(n>0&&n<=1000000");
			puts("-c Ҫ�����������Ŀ���ļ�·��");
			return false;
		}
	}
	return true;
}
#endif