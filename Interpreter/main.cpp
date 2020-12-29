
#include "lex.h"
#include "sem.h"
#include "syn.h"
#include "VM.h"
#include"windows.h"

int main()
{
	lex lex1;
	syn syn1;
	sem sem1;
	VM vm;
	int judge;
	judge=lex1.start();
	if (judge==1)
	{
		cout << "词法有错,程序结束" << endl;
	}
	else
	{
		cout << "词法没有错误，进入语法分析阶段" << endl;
		judge=syn1.start();
		if (judge != 0)
		{
			cout << "语法有错，程序结束" << endl;
		}
		else 
		{
			cout << "语法没有错误，将进入语义分析阶段" << endl;
			judge=sem1.start();
			if (judge != 0)
			{
				cout << "语义有错，程序结束" << endl;

			}
			else
			{
				cout << "成功生成中间代码，将启动虚拟机......" << endl;

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
				cout << "-----------------------------------------------------------" << endl;

				vm.start();
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);

			}
		}
	}


}