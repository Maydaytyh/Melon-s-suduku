#include "pch.h"
#include "CppUnitTest.h"
#include "../suduku/sudoku.h"
#include "../suduku//sudoku.cpp"
#include "../suduku/Check.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		int argc;
		char** argv_c, ** argv_s;//�ֱ��ʾ����Ϊ-c ��-s
		UnitTest()
		{
			argv_c = (char**)malloc(3 * sizeof(char*));
			argv_s= (char**)malloc(3 * sizeof(char*));
			argc = 3;
			for (int i = 0; i < 3; ++i)
			{
				argv_c[i] = (char*)malloc(100 * sizeof(char));
				argv_s[i] = (char*)malloc(100* sizeof(char));
			}
			cout << argv_c << " " << argv_s << endl;
			//���ַ������г�ʼ����ֵ
			strcpy_s(argv_c[0],100, "sudoku.exe");
			strcpy_s(argv_c[1], 100, "-c");
			strcpy_s(argv_c[2],100,  "100");
			strcpy_s(argv_s[0], 100, "sudoku.exe");
			strcpy_s(argv_s[1],100, "-s");
			strcpy_s(argv_s[2],  100,"C:\\Users\\GuguMelon\\source\\repos\\suduku\\problem.txt");
		}
		TEST_METHOD(TestMethod1)//���Բ��� ������������Ĳ���
		{
			argc = 2;
			Check Test(argc, argv_c);
			Test.GetInput();
			Assert::AreEqual(Test.GetError() == true, true);
		}
		TEST_METHOD(TestMethod2)//���Բ��� �������ʹ���Ĳ���
		{
			strcpy(argv_s[1], "t");
			strcpy(argv_s[2], "text");
			Check Test(argc, argv_s);
			Test.GetInput();
			Assert::AreEqual(Test.GetError() == true, true);
		}
		TEST_METHOD(TestMethod3)//���Բ��� -c N��ȷ����Ĳ���
		{
			strcpy(argv_c[1], "c");
			strcpy(argv_c[2], "1000");
			Check Test(argc, argv_c);
			Test.GetInput();
			Assert::AreEqual(Test.GetError() == true, true);
		}
		TEST_METHOD(TestMethod4)//���Բ��� -c N��������Ĳ��� <=0
		{
			strcpy(argv_c[1], "c");
			strcpy(argv_c[2], "-1000");
			Check Test(argc, argv_c);
			Test.GetInput();
			Assert::AreEqual(Test.GetError() == true, true);
		}
		TEST_METHOD(TestMethod5)//���Բ��� -c N��������Ĳ��� >1000000
		{
			strcpy(argv_c[1], "c");
			strcpy(argv_c[2], "10000000");
			Check Test(argc, argv_c);
			Test.GetInput();
			Assert::AreEqual(Test.GetError() == true, true);
		}
		TEST_METHOD(TestMethod8)//���Բ��� -c N��������Ĳ��� ������
		{
			strcpy(argv_c[1], "c");
			strcpy(argv_c[2], "cd78");
			Check Test(argc, argv_c);
			Test.GetInput();
			Assert::AreEqual(Test.GetError() == true, true);
		}
		TEST_METHOD(TestMethod6)//���Բ��� -s FilePath����ȷ����
		{
			strcpy(argv_s[1], "s");
			strcpy(argv_s[2], "C:\\Users\\GuguMelon\\source\\repos\\suduku\\problem.txt");
			Check Test(argc, argv_s);
			Test.GetInput();
			Assert::AreEqual(Test.GetError() == true, true);
		}
		TEST_METHOD(TestMethod7)//���Բ��� -s FilePath�Ĵ�������
		{
			strcpy(argv_s[1], "s");
			strcpy(argv_s[2], "C:\\Users\\GuguMelon\\source\\repos\\suduku\\error.txt");
			Check Test(argc, argv_s);
			Test.GetInput();
			Assert::AreEqual(Test.GetError() == true, true);
		}
		TEST_METHOD(TestMethod9)//�Ի�ȡ-cʱ��������������Get�������е���ȷ����
		{
			strcpy(argv_c[2], "10000000");
			int n;
			bool flag = get(argv_c[2], n);
			Assert::AreEqual(flag == true, true);
		}
		TEST_METHOD(TestMethod10)//�Ի�ȡ-cʱ��������������Get�������еĴ������
		{
			strcpy(argv_c[2], "dfss");
			int n;
			bool flag = get(argv_c[2], n);
			Assert::AreEqual(flag == false, true);
		}
		TEST_METHOD(TestMethod11)//���������Ƿ�������жϺ��� ��ȷ����
		{
			Sudoku sudoku_one;
			int Grid[9][9] = {
				{4 ,7 ,6 ,0, 1, 0, 3, 0, 5},
				{3 ,0 ,8, 5, 6, 7, 4, 9, 1},
				{9 ,1 ,5 ,8, 4, 3, 0, 2, 7,},
				{2 ,3 ,7, 0, 8, 1, 9, 5, 4,},
				{6 ,4 ,0 ,7 ,0 ,0 ,2 ,0, 0},
				{5 ,8 ,9 ,3, 2, 0, 7, 1, 6,},
				{1, 6, 3, 0, 5, 9, 0, 7, 2,},
				{7, 0, 4, 2, 3, 8, 1, 6, 9,},
				{8, 9, 2, 1, 0, 6, 5, 4, 3},
			};
			sudoku_one.GetSudoku(Grid);
			bool flag=sudoku_one.row_column(0,3,9);
			Assert::AreEqual(flag == true, true);
		}
		TEST_METHOD(TestMethod12)//���������Ƿ�������жϺ��� �д������
		{
			Sudoku sudoku_one;
			int Grid[9][9] = {
				{4 ,7 ,6 ,0, 1, 0, 3, 0, 5},
				{3 ,0 ,8, 5, 6, 7, 4, 9, 1},
				{9 ,1 ,5 ,8, 4, 3, 0, 2, 7,},
				{2 ,3 ,7, 0, 8, 1, 9, 5, 4,},
				{6 ,4 ,0 ,7 ,0 ,0 ,2 ,0, 0},
				{5 ,8 ,9 ,3, 2, 0, 7, 1, 6,},
				{1, 6, 3, 0, 5, 9, 0, 7, 2,},
				{7, 0, 4, 2, 3, 8, 1, 6, 9,},
				{8, 9, 2, 1, 0, 6, 5, 4, 3},
			};
			sudoku_one.GetSudoku(Grid);
			bool flag = sudoku_one.row_column(0, 3, 4);
			Assert::AreEqual(flag == false, true);
		}
		TEST_METHOD(TestMethod13)//���������Ƿ�������жϺ��� �д������
		{
			Sudoku sudoku_one;
			int Grid[9][9] = {
				{4 ,7 ,6 ,0, 1, 0, 3, 0, 5},
				{3 ,0 ,8, 5, 6, 7, 4, 9, 1},
				{9 ,1 ,5 ,8, 4, 3, 0, 2, 7,},
				{2 ,3 ,7, 0, 8, 1, 9, 5, 4,},
				{6 ,4 ,0 ,7 ,0 ,0 ,2 ,0, 0},
				{5 ,8 ,9 ,3, 2, 0, 7, 1, 6,},
				{1, 6, 3, 0, 5, 9, 0, 7, 2,},
				{7, 0, 4, 2, 3, 8, 1, 6, 9,},
				{8, 9, 2, 1, 0, 6, 5, 4, 3},
			};
			sudoku_one.GetSudoku(Grid);
			bool flag = sudoku_one.row_column(0, 3, 2);
			Assert::AreEqual(flag == false, true);
		}
		TEST_METHOD(TestMethod14)//���ԾŹ����Ƿ�������жϺ��� �Ź�����ȷ����
		{
			Sudoku sudoku_one;
			int Grid[9][9] = {
				{4 ,7 ,6 ,0, 1, 0, 3, 0, 5},
				{3 ,0 ,8, 5, 6, 7, 4, 9, 1},
				{9 ,1 ,5 ,8, 4, 3, 0, 2, 7,},
				{2 ,3 ,7, 0, 8, 1, 9, 5, 4,},
				{6 ,4 ,0 ,7 ,0 ,0 ,2 ,0, 0},
				{5 ,8 ,9 ,3, 2, 0, 7, 1, 6,},
				{1, 6, 3, 0, 5, 9, 0, 7, 2,},
				{7, 0, 4, 2, 3, 8, 1, 6, 9,},
				{8, 9, 2, 1, 0, 6, 5, 4, 3},
			};
			sudoku_one.GetSudoku(Grid);
			bool flag = sudoku_one.Judge(0, 3, 2);
			Assert::AreEqual(flag == true, true);
		}
		TEST_METHOD(TestMethod15)//���ԾŹ����Ƿ�������жϺ��� �Ź���������
		{
			Sudoku sudoku_one;
			int Grid[9][9] = {
				{4 ,7 ,6 ,0, 1, 0, 3, 0, 5},
				{3 ,0 ,8, 5, 6, 7, 4, 9, 1},
				{9 ,1 ,5 ,8, 4, 3, 0, 2, 7,},
				{2 ,3 ,7, 0, 8, 1, 9, 5, 4,},
				{6 ,4 ,0 ,7 ,0 ,0 ,2 ,0, 0},
				{5 ,8 ,9 ,3, 2, 0, 7, 1, 6,},
				{1, 6, 3, 0, 5, 9, 0, 7, 2,},
				{7, 0, 4, 2, 3, 8, 1, 6, 9,},
				{8, 9, 2, 1, 0, 6, 5, 4, 3},
			};
			sudoku_one.GetSudoku(Grid);
			bool flag = sudoku_one.Judge(0, 3, 8);
			Assert::AreEqual(flag == false, true);
		}
	};
}
/*
int Grid[10][10] = {
				{0,0,0,0,0,0,0,0,0,0,},
				{0,4 ,7 ,6 ,9, 1, 2, 3, 8, 5},
				{0,3 ,2 ,8, 5, 6, 7, 4, 9, 1},
				{0,9 ,1 ,5 ,8, 4, 3, 6, 2, 7,},
				{0,2 ,3 ,7, 6, 8, 1, 9, 5, 4,},
				{0,6 ,4 ,1 ,7 ,9 ,5 ,2 ,3, 8},
				{0,5 ,8 ,9 ,3, 2, 4, 7, 1, 6,},
				{0,1, 6, 3, 4, 5, 9, 8, 7, 2,},
				{0,7, 5, 4, 2, 3, 8, 1, 6, 9,},
				{0,8, 9, 2, 1, 7, 6, 5, 4, 3,},
			};

*/