
//先实现数独终局
#include <bits/stdc++.h>
using namespace std;
/****                                   变量定义区                           ****/
const int FirstNum = 5;//(2+2)%9+1=5
int nn=1;
char sudodo[1000005][10][10];
int problem_sudoku[1000005][10][10];
class Sudoku {
public:
    int num[9] = { 1,2,3,4,6,7,8,9 };
    int num_use[9];
    int offset[8] = { 3,6,1,4,7,2,5,8 };
    int sudoku[10][10];
    bool ok = false;
    void print()
    {
        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
                sudodo[nn][i][j] = sudoku[i + 1][j + 1] + '0';
            sudodo[nn][i][9] = '\0';
        }
        nn++;
    }
    void generate_final(int num_of_sudoku)
    {
        sudoku[1][1] = 5;
        do
        {
            //构造第一行
            for (int i = 2; i <= 9; i++)
                sudoku[1][i] = num[i- 2];
            //构造剩余的行
            for (int i = 2; i <= 9; ++i)
            {
                for (int j = 1; j <= 9; ++j)
                {
                    int shifted = offset[i - 2] + j;
                    if (shifted > 9) shifted -= 9;
                    sudoku[i][shifted] = sudoku[1][j];
                }
            }
            print();
            if (nn >= num_of_sudoku) return;
            Sudoku tmpSudoku;
            int sudoku_1[10][10];
            //接着构造
            int num_2[3] = { 1,2,3 }, num_3[3] = { 1,2,3 };
            for (int i = 1; i <= 3; ++i)
                for (int j = 1; j <= 9; ++j)
                    tmpSudoku.sudoku[i][j] = sudoku[i][j];
            do
            {
                for (int i = 4; i <= 6; ++i)
                {
                    for (int j = 1; j <= 9; ++j)
                        tmpSudoku.sudoku[i][j] = sudoku[num_2[i - 4] + 4][j];
                }
                do
                {
                    for (int i = 7; i <= 9; ++i)
                    {
                        for (int j = 1; j <= 9; ++j)
                            tmpSudoku.sudoku[i][j] = sudoku[num_3[i - 7] + 7][j];
                    }
                    tmpSudoku.print();
                    if (nn >= num_of_sudoku) return;
                } while (next_permutation(num_3, num_3 + 3));
            } while (next_permutation(num_2, num_2 + 3));
        } while (next_permutation(num, num + 8));
    }
    bool check(int pos,int num)
    {
        int x = pos / 9 + 1;
        int y = pos % 9;
        if (!y) y += 9;
        for (int i = 1; i <= 9; ++i)
            if (sudoku[x][i] == num || sudoku[i][y] == num)
                return false;
        //检验九宫格
        if (x % 3 == 0) x = (x / 3 - 1) * 3 + 1;
        else x = x / 3 * 3 + 1;
        if (y % 3 == 0) y = (y / 3 - 1) * 3 + 1;
        else y = y / 3 * 3 + 1;
        for (int i = x; i <= x + 3; ++i)
            for (int j = y; j <= y + 3; ++j)
                if (sudoku[i][j] == num)
                    return false;
        return true;
    }
    void solve_dfs(int tmp)
    {
        int y = tmp % 9;
        int x = tmp / 9 + 1;
        if (!y) y += 9;
        if (tmp == 82 || ok)
        {
            ok = true;
            return;
        }
        if (sudoku[x][y])
            solve_dfs(tmp + 1);
        else
        {
            for (int i = 1; i <= 9; ++i)
            {
                if (check(tmp, i))
                {
                    sudoku[x][y] = i;
                    solve_dfs(tmp + 1);
                    if (ok) return;
                    sudoku[x][y] = 0;
                }
            }
        }
    }
};
int get(char* num)
{
    int len = strlen(num);
    int ans = 0;
    for (int i = 0; i < len; ++i)
        ans = ans * 10 + num[i] - '0';
    return ans;
}
void print_ans()
{
    for (int i = 1; i <= nn; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            printf("%s\n", sudodo[i][j]);
        }
        puts("");
    }
}
int main(int argc, char** argv)
{
    double t_start = clock();
    freopen("sudoku.txt", "w", stdout);
    //判断参数
    if (argc < 3 ||( strcmp(argv[1], "-c")&&strcmp(argv[1],"-s" )!= 0))
    {
        puts("参数错误！请重新输入！");
        exit(0);
    }
    if (strcmp(argv[1], "-c") == 0) {
        int n = get(argv[2]);
        Sudoku use_sudoku;
        use_sudoku.generate_final(n);
        print_ans();
        freopen("CON", "w", stdout);
        puts("打印完成！");
        double t_end = clock();
        printf("输出%d个终局用时为%fs\n", n, (t_end - t_start) * 1.0 / 1000);
        print_ans();
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
        int num_of_problem = 1;
        while (!infile.eof())
        {
            for (int i = 1; i <= 9; ++i)
                for (int j = 1; j <= 9; ++j)
                    infile >> problem_sudoku[num_of_problem][i][j];
            num_of_problem++;
        }
        infile.close();
        //解决问题
        Sudoku sudoku_problem;
        for (int i = 1; i <= num_of_problem; ++i)
        {
            for (int j = 1; j <= 9; ++j)
                for (int k = 1; k <= 9; ++k)
                    sudoku_problem.sudoku[j][k] = problem_sudoku[i][j][j];
            sudoku_problem.solve_dfs(1);
            sudoku_problem.print();
        }
        /*ofstream outfile;
        outfile.open("sudoku.txt", ios::out);*/
        print_ans();
    }
    return 0;
}