
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
		cout << "�ʷ��д�,�������" << endl;
	}
	else
	{
		cout << "�ʷ�û�д��󣬽����﷨�����׶�" << endl;
		judge=syn1.start();
		if (judge != 0)
		{
			cout << "�﷨�д��������" << endl;
		}
		else 
		{
			cout << "�﷨û�д��󣬽�������������׶�" << endl;
			judge=sem1.start();
			if (judge != 0)
			{
				cout << "�����д��������" << endl;

			}
			else
			{
				cout << "�ɹ������м���룬�����������......" << endl;

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
				cout << "-----------------------------------------------------------" << endl;

				vm.start();
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);

			}
		}
	}


}