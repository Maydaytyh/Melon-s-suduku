
//先实现数独终局
#include <bits/stdc++.h>
using namespace std;
/****                                   变量定义区                           ****/
const int FirstNum = 5;//(2+2)%9+1=5
int sudoku[10][10];
int num[9] = { 1,2,3,4,6,7,8,9 };
int offset[8] = { 3, 6, 1, 4, 7, 2, 5, 8 };
int get(char* num)
{
    int len = strlen(num);
    int ans = 0;
    for (int i = 0; i < len; ++i)
        ans = ans * 10 + num[i] - '0';
    return ans;
}
void print(int ans[10][10])
{
    for (int i = 1; i <= 9; ++i)
    {
        for (int j = 1; j <= 8; ++j)
            printf("%d ", ans[i][j]);
        printf("%d\n", ans[i][9]);
    }
    puts("");
}

int main(int argc, char** argv)
{
    double t_start = clock();
    freopen("sudoku.txt", "w", stdout);
    //判断参数
    if (argc < 3 || strcmp(argv[1], "-c") != 0)
    {
        puts("参数错误！请重新输入！");
        exit(0);
    }
    int n = get(argv[2]);
    sudoku[1][1] = 5;

    int nn = 0;
    do
    {
        //构造第一行
        for (int i = 2; i <= 9; i++)
            sudoku[1][i] = num[i - 2];
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
        print(sudoku);
        nn++;
        if (nn > n) goto out;
        int sudoku_1[10][10];
        //接着构造
        int num_2[3] = { 1,2,3 }, num_3[3] = { 1,2,3 };
        for (int i = 1; i <= 3; ++i)
            for (int j = 1; j <= 9; ++j)
                sudoku_1[i][j] = sudoku[i][j];
        do
        {
            for (int i = 4; i <= 6; ++i)
            {
                for (int j = 1; j <= 9; ++j)
                    sudoku_1[i][j] = sudoku[num_2[i - 4] + 4][j];
            }
            do
            {
                for (int i = 7; i <= 9; ++i)
                {
                    for (int j = 1; j <= 9; ++j)
                        sudoku_1[i][j] = sudoku[num_3[i - 7] + 7][j];
                }
                print(sudoku_1);
                nn++;
                if (nn > n) goto out;
            } while (next_permutation(num_3, num_3 + 3));
        } while (next_permutation(num_2, num_2 + 3));
    } while (next_permutation(num, num + 8));
out:

    // fclose(stdout);
    freopen("CON", "w", stdout);
    puts("打印完成！");

    double t_end = clock();
    printf("输出%d个终局用时为%fms\n", n, (t_end - t_start) * 1.0 / 1000);
    fclose(stdout);
    return 0;
}
