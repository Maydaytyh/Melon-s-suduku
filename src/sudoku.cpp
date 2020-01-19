//先实现数独终局
#include <sudoku.h>
using namespace std;

int main(int argc, char** argv)
{
	double t_start = clock();

	//判断参数

	if (!InputCheck(argc, argv))
	{
		exit(0);
	}
	if (strcmp(argv[1], "-c") == 0) {
		int n;
		bool Flag = get(argv[2], n);
		num_of_problem = n;
		Sudoku use_sudoku;
		use_sudoku.generate_final(n);
		//PrintAns();
		freopen("sudoku.txt", "w", stdout);
		PrintAns();
		freopen("CON", "w", stdout);
		puts("打印完成！");
		double t_end = clock();
		printf("输出%d个终局用时为%fs\n", n, (t_end - t_start) * 1.0 / 1000);
		//PrintAns();
		fclose(stdout);
	}
	else if (strcmp(argv[1], "-s") == 0)
	{
		//读入问题，存到数组中
		//freopen(argv[2], "r", stdin);
		t_start = clock();
		ifstream fin(argv[2], std::ios::binary);
		vector<char> buf(fin.seekg(0, std::ios::end).tellg());
		fin.seekg(0, std::ios::beg).read(&buf[0], static_cast<std::streamsize>(buf.size()));
		fin.close();
		num_of_problem = 0;
		int pointer = 0;
		int NumOfPro = 0;
		int NumOfNumber = 0;
		while (pointer < buf.size())
		{
			if (buf[pointer] < '0' || buf[pointer]>'9')
			{
				pointer++;
				continue;
			}
			else
			{
				problem_sudoku[num_of_problem][NumOfNumber / 9][NumOfNumber % 9] = buf[pointer] - '0';
				NumOfNumber++;
				if (NumOfNumber >= 81)
				{
					num_of_problem++;
					NumOfNumber = 0;
				}
				pointer++;
			}
		}
		puts("输入完成!");
		cout << "num=" << num_of_problem << endl;
		cout << "读入题目用时为" << (clock() - t_start) * 1.0 / 1000<<"s" << endl;
		double TStart = clock();
		Sudoku sudoku_problem;
		for (int i = 0; i < num_of_problem; ++i)
		{
		    for (int j = 0; j < 9; ++j)
		        for (int k = 0; k < 9; ++k)
		            sudoku_problem.sudoku[j] [k] = problem_sudoku[i][j][k];
		    sudoku_problem.DFS(0);
		    sudoku_problem.print();
		}
		puts("问题已解决！");
		double t_end = clock();
		printf("解决问题用时为%fs\n", (t_end - TStart) * 1.0 / 1000);
		///*ofstream outfile;
		//outfile.open("sudoku.txt", ios::out);*/
		TStart = clock();
		freopen("sudoku.txt", "w", stdout);
		PrintAns();
		freopen("CON", "w", stdout);
		printf("输出答案总用时为%fs\n", (clock() - TStart) * 1.0 / 1000);
		printf("程序运行总时长为%fs\n", (clock() - t_start) * 1.0 / 1000);
		fclose(stdout);
	}
	return 0;
}