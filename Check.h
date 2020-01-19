#pragma once
#include<string>
#include<cstdio>
#include<algorithm>
#include<sudoku.h>
using namespace std;
class Check {
private:
	int argc;
	char** argv;
	int NumOfPar;
	char OpType;
	char* FileName;
	bool InputError;
public:
	Check(int argc, char* argv[])
	{
		this->argc = argc;
		this->argv = argv;
		OpType = 0;
		NumOfPar = 0;
		FileName = nullptr;
		InputError = false;
	}
	int GetParNum()
	{
		return NumOfPar;
	}
	char GetOpType()
	{
		return OpType;
	}
	void GetInput()
	{
		if (argc != 3)
		{
			InputError = true;
			puts("输入参数的个数错误！请检查输入！");
		}
		else
		{
			if (strcmp(argv[1], "-c") == 0)
			{
				OpType = 'c';
				bool Flag = get(argv[2],NumOfPar);
				if (!Flag) //第三个参数输入类型错误
				{
					InputError = true;
					NumOfPar = 0;
					puts("Parameter error!You should input character in 0-9!");
				}
				else
				{
					if (NumOfPar <= 0 || NumOfPar > 1000000)
					{
						InputError = true;
						NumOfPar = 0;
						puts("Parameter error!You should input number in 1-1000000");
					}
				}
			}
			else if (strcmp(argv[1], "-s") == 0)
			{
				OpType = 's';
				FileName = argv[2];
				errno_t err;
				FILE* tryopen;
				err = fopen_s(&tryopen, FileName, "r");
				if (err)
				{
					InputError = true;
					puts("FileName error!Can't open the file you input!");
				}
			}
			else
			{
				InputError = true;
				puts("Parameter error!Can't get the meaning of the parameter!");
			}
		}
	}
	bool GetError()
	{
		return InputError;
	}
	char* GetFileName()
	{
		return FileName;
	}
};
