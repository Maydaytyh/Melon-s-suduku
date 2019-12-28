
//先实现数独终局
#include <bits/stdc++.h>
using namespace std;
/****                                   变量定义区                           ****/
const int FirstNum = 5;//(2+2)%9+1=5
int nn=1;
char sudodo[1000005][10][10];
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
        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
                sudodo[nn][i][j] = sudoku[i ][j ] + '0';
            sudodo[nn][i][9] = '\0';
        }
        nn++;
        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
                printf("%d ", sudoku[i ][j]);
            puts("");
        }
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
            int num_2[3] = { 0,1,2 }, num_3[3] = { 0,1,2};
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
    ///判断行和列是否满足
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

    ///判断3*3的正方形是否满足
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
    for (int i = 1; i <= num_of_problem; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {

            //printf("%s\n", sudodo[i][j]);
            for (int k = 0; k < 8; ++k)
                printf("%c ", sudodo[i][j][k]);
            printf("%c\n", sudodo[i][j][8]);
        }
        puts("");
    }
}
int main(int argc, char** argv)
{
    double t_start = clock();
    
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
        freopen("sudoku.txt", "w", stdout);
        print_ans();
        freopen("CON", "w", stdout);
        puts("打印完成！");
        double t_end = clock();
        printf("输出%d个终局用时为%fs\n", n, (t_end - t_start) * 1.0 / 1000);
        //print_ans();
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
                    sudoku_problem.sudoku[j-1][k-1] = problem_sudoku[i][j][k];
           /* for (int j = 1; j <= 9; ++j)
            {
                for (int k = 1; k <= 9; ++k)
                    printf("%d ", sudoku_problem.sudoku[j][k]);
                puts("");
            }*/
            sudoku_problem.DFS(0);
            sudoku_problem.print();
        }
        puts("问题已解决！");
        /*ofstream outfile;
        outfile.open("sudoku.txt", ios::out);*/
        freopen("sudoku.txt", "w", stdout);
        print_ans();
    }
    return 0;
}