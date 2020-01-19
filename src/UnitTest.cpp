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
		char** argv_c, ** argv_s;//分别表示参数为-c 和-s
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
			//对字符串进行初始化赋值
			strcpy_s(argv_c[0],100, "sudoku.exe");
			strcpy_s(argv_c[1], 100, "-c");
			strcpy_s(argv_c[2],100,  "100");
			strcpy_s(argv_s[0], 100, "sudoku.exe");
			strcpy_s(argv_s[1],100, "-s");
			strcpy_s(argv_s[2],  100,"C:\\Users\\GuguMelon\\source\\repos\\suduku\\problem.txt");
		}
		TEST_METHOD(TestMethod1)//测试参数 参数个数错误的测试
		{
			argc = 2;
			Check Test(argc, argv_c);
			Test.GetInput();
			Assert::AreEqual(Test.GetError() == true, true);
		}
		TEST_METHOD(TestMethod2)//测试参数 参数类型错误的测试
		{
			strcpy(argv_s[1], "t");
			strcpy(argv_s[2], "text");
			Check Test(argc, argv_s);
			Test.GetInput();
			Assert::AreEqual(Test.GetError() == true, true);
		}
		TEST_METHOD(TestMethod3)//测试参数 -c N正确输入的测试
		{
			strcpy(argv_c[1], "c");
			strcpy(argv_c[2], "1000");
			Check Test(argc, argv_c);
			Test.GetInput();
			Assert::AreEqual(Test.GetError() == true, true);
		}
		TEST_METHOD(TestMethod4)//测试参数 -c N错误输入的测试 <=0
		{
			strcpy(argv_c[1], "c");
			strcpy(argv_c[2], "-1000");
			Check Test(argc, argv_c);
			Test.GetInput();
			Assert::AreEqual(Test.GetError() == true, true);
		}
		TEST_METHOD(TestMethod5)//测试参数 -c N错误输入的测试 >1000000
		{
			strcpy(argv_c[1], "c");
			strcpy(argv_c[2], "10000000");
			Check Test(argc, argv_c);
			Test.GetInput();
			Assert::AreEqual(Test.GetError() == true, true);
		}
		TEST_METHOD(TestMethod8)//测试参数 -c N错误输入的测试 非整数
		{
			strcpy(argv_c[1], "c");
			strcpy(argv_c[2], "cd78");
			Check Test(argc, argv_c);
			Test.GetInput();
			Assert::AreEqual(Test.GetError() == true, true);
		}
		TEST_METHOD(TestMethod6)//测试参数 -s FilePath的正确输入
		{
			strcpy(argv_s[1], "s");
			strcpy(argv_s[2], "C:\\Users\\GuguMelon\\source\\repos\\suduku\\problem.txt");
			Check Test(argc, argv_s);
			Test.GetInput();
			Assert::AreEqual(Test.GetError() == true, true);
		}
		TEST_METHOD(TestMethod7)//测试参数 -s FilePath的错误输入
		{
			strcpy(argv_s[1], "s");
			strcpy(argv_s[2], "C:\\Users\\GuguMelon\\source\\repos\\suduku\\error.txt");
			Check Test(argc, argv_s);
			Test.GetInput();
			Assert::AreEqual(Test.GetError() == true, true);
		}
		TEST_METHOD(TestMethod9)//对获取-c时数独个数参数的Get函数进行的正确测试
		{
			strcpy(argv_c[2], "10000000");
			int n;
			bool flag = get(argv_c[2], n);
			Assert::AreEqual(flag == true, true);
		}
		TEST_METHOD(TestMethod10)//对获取-c时数独个数参数的Get函数进行的错误测试
		{
			strcpy(argv_c[2], "dfss");
			int n;
			bool flag = get(argv_c[2], n);
			Assert::AreEqual(flag == false, true);
		}
		TEST_METHOD(TestMethod11)//测试行列是否满足的判断函数 正确测试
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
		TEST_METHOD(TestMethod12)//测试行列是否满足的判断函数 行错误测试
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
		TEST_METHOD(TestMethod13)//测试行列是否满足的判断函数 列错误测试
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
		TEST_METHOD(TestMethod14)//测试九宫格是否满足的判断函数 九宫格正确测试
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
		TEST_METHOD(TestMethod15)//测试九宫格是否满足的判断函数 九宫格错误测试
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