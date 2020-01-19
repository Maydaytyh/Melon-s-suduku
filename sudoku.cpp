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
        bool Flag=get(argv[2],n);
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
        ifstream infile;
        infile.open(argv[2], ios::in);
        if (!infile.is_open())
        {
            puts("无法打开文件！请检查输入！");
            return 0;
        }
        while (!infile.eof())
        {
            num_of_problem++;
            for (int i = 1; i <= 9; ++i)
            {
                for (int j = 1; j <= 9; ++j)
                {
                    infile >> problem_sudoku[num_of_problem][i][j];
                    //cout << problem_sudoku[num_of_problem][i][j] << " ";
                }
                //puts("");
            }
        }
        infile.close();
        //解决问题
        puts("输入完成!");
        cout << "num=" << num_of_problem << endl;
        Sudoku sudoku_problem;
        for (int i = 1; i <= num_of_problem; ++i)
        {
            for (int j = 1; j <= 9; ++j)
                for (int k = 1; k <= 9; ++k)
                    sudoku_problem.sudoku[j - 1][k - 1] = problem_sudoku[i][j][k];
            sudoku_problem.DFS(0);
            sudoku_problem.print();
        }
        puts("问题已解决！");
        double t_end = clock();
        printf("解决问题用时为%fs\n", (t_end - t_start) * 1.0 / 1000);
        /*ofstream outfile;
        outfile.open("sudoku.txt", ios::out);*/
        freopen("sudoku.txt", "w", stdout);
        PrintAns();
        printf("输出答案总用时为%fs\n", (clock() - t_start) * 1.0 / 1000);
        fclose(stdout);
    }
    return 0;
}