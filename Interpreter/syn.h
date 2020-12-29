#pragma once

#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include<string.h>
#include <iostream> 
using namespace std;

class syn
{
public:

	/*

	//��ȡ�ʷ���������ļ�
	void getnextandprint();

	//��һ���ֺ����Ƕ�ÿ������ĵݹ��½�����
	int program();
	int compound_stat();
	int statement();
	int assignment_stat();
	int expression();
	int bool_expression();
	int ari_expression();
	int ari_expression_1();
	int term();
	int term_1();
	int factor();
	int if_stat();
	int while_stat();
	int for_stat();
	int write_stat();
	int read_stat();
	int declaration_stat();
	int declaration_list();
	int statement_list();
	int compound_stat();
	
	void start();

	*/

	char token[100], token1[100];

	FILE* fp;

	int l = 0;;


	void getnextandprint()
	{
		l++;
		if (l > 192)
			return;
		fscanf(fp, "%s %s\n", &token, &token1);
		//printf("%s %s\n", token, token1);
	}

	int start()
	{
		int es = 0;
		if ((fp = fopen("lex.txt", "r")) == NULL)
		{
			printf("\n�򿪴���\n");
			es = 8;
		}
		if (es == 0)
		{
			es = program();
		}


		switch (es)
		{
		case 0:cout << "�﷨�����ɹ�!" << endl; break;
		case 1:cout << "������" << l << "   ȱ�ٷֽ�� {" << endl; break;
		case 2:cout << "������" << l << "   ȱ�ٷֽ�� }" << endl; break;
		case 3:cout << "������" << l << "   ȱ�ٱ�ʶ��" << endl; break;
		case 4:cout << "������" << l << "   ȱ�ٷֽ�� ;" << endl; break;
		case 5:cout << "������" << l << "   ȱ�ٷֽ�� (" << endl; break;
		case 6:cout << "������" << l << "   ȱ�ٷֽ�� )" << endl; break;
		case 7:cout << "������" << l << "   ȱ�ٲ�����" << endl; break;
		case 8:cout << "������" << l << "   ȱ�������" << endl; break;
		}
		fclose(fp);
		return es;
	}

	//program::={<declration_list><statement_list>}
	int program()
	{
		int es = 0;
		getnextandprint();
		if (strcmp(token, "{"))
		{
			es = 1;
			return(es);
		}
		getnextandprint();
		es = declaration_list();
		if (es > 0)
			return (es);
		es = statement_list();
		if (es > 0)
			return(es);
		if (strcmp(token, "}"))
		{
			es = 2;
			return(es);
		}
		return(es);
	}

	//<declaration_list>::=<declaration_list><declaration_stat>|yipucilong ��Ϊ <declaration_list>::={<declaration_stat>}
	int declaration_list()
	{
		int es = 0;
		while (strcmp(token, "int") == 0)
		{
			es = declaration_stat();
			if (es > 0) return(es);
		}
		return(es);
	}

	//<declaration_stat>::=int ID;
	int declaration_stat()
	{
		int es = 0;
		getnextandprint();
		if (strcmp(token, "ID"))
			return(es = 3);   //���Ǳ�ʶ��
		getnextandprint();
		if (strcmp(token, ";"))
			return(es = 4);   //���Ƿֺ�
		getnextandprint();
		return(es);
	}

	//<statement_list>::=<statement_list><statement>|yipucilong ��Ϊ  <statement_list>::={<statement>}
	int statement_list()
	{
		int es = 0;
		while (strcmp(token, "}"))
		{
			es = statement();
			if (es > 0)
				return(es);
			getnextandprint();
		}
		return(es);
	}

	//<statement::=<if_stat>|<while_stat>|<for_stat>|<compound_stat>|<assignment_stat>
	int statement()
	{
		int es = 0;
		if (es == 0 && strcmp(token, "if") == 0)
			es = if_stat();          //if���
		if (es == 0 && strcmp(token, "while") == 0)
			es = while_stat();          //while���
		if (es == 0 && strcmp(token, "for") == 0)
			es = for_stat();          //for���
		if (es == 0 && strcmp(token, "read") == 0)
			es = read_stat();          //read���
		if (es == 0 && strcmp(token, "write") == 0)
			es = write_stat();          //write���
		if (es == 0 && strcmp(token, "{") == 0)
			es = compound_stat();          //�������
		if (es == 0 && (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0 || strcmp(token, "(") == 0))
			es = assignment_stat();          //���ʽ���
		return(es);
	}

	//<if_stat>=if(<bool_expression>)<statement>[else<statement>]
	int if_stat()
	{
		int es = 0;
		getnextandprint();
		if (strcmp(token, "("))                      //�������� 
			return (es = 5);
		getnextandprint();
		es = bool_expression();
		if (es > 0)
			return(es);
		if (strcmp(token, ")"))                       //�������� 
			return(es = 6);
		getnextandprint();
		es = statement();
		if (es > 0)
			return(es);
		if (strcmp(token, "else") == 0)                    //else���� 
		{
			getnextandprint();
			es = statement();
			if (es > 0)
				return(es);
		}
		return(es);
	}

	//<while_stat>::=while(<bool_expression>)<statement>
	int while_stat()
	{
		int es = 0;
		getnextandprint();
		if (strcmp(token, "("))
			return(es = 5);                           //�������� 
		getnextandprint();
		es = bool_expression();
		if (es > 0)
			return(es);
		if (strcmp(token, ")"))
			return(es = 6);                         //��������
		getnextandprint();
		es = statement();
		return(es);
	}

	//  <for_stat>::=for(<expression>;<bool_expression>;<expression>)<statement>
	int for_stat()
	{
		int es = 0;
		getnextandprint();
		if (strcmp(token, "("))
			return(es = 5);                           //ȱ��������
		getnextandprint();
		es = expression();
		if (es > 0)
			return(es);
		if (strcmp(token, ";"))
			return(es = 4);                  //�ٷֺ�
		getnextandprint();
		es = bool_expression();
		if (es > 0)
			return(es);
		if (strcmp(token, ";"))
			return(es = 4);                  //�ٷֺ�
		getnextandprint();
		es = expression();
		if (es > 0)
			return(es);
		if (strcmp(token, ")"))
			return(es = 6);                  //��������
		getnextandprint();
		es = statement();
		return(es);
	}

	// <write_stat::=write<ari_expression>
	int write_stat()
	{
		int es = 0;
		getnextandprint();
		es = ari_expression();
		if (es > 0)
			return(es);
		if (strcmp(token, ";"))
			return(es = 4);								//ȱ�ٷֺ� 
		getnextandprint();
		return(es);
	}

	// <read_stat>::=read ID;
	int read_stat()
	{
		int es = 0;
		getnextandprint();
		if (strcmp(token, "ID"))
			return(es = 3);								//ȱ�ٱ�ʶ�� 
		getnextandprint();
		if (strcmp(token, ";"))
			return(es = 4);								//ȱ�ٷֺ� 
		getnextandprint();
		return(es);
	}

	//<compound_stat>::={<statement_list>}
	int compound_stat()
	{
		int es = 0;
		getnextandprint();
		es = statement_list();
		return(es);
	}

	//<assignment_stat>::=<expression>;
	int assignment_stat()
	{
		int es = 0;
		es = expression();
		if (es > 0)
			return(es);
		if (es == 0 && strcmp(token, ";") == 0)
		{
			return(es);
		}
		else
		{
			return(es = 4);
		}
	}

	//<expression>::=ID=<ari_expression>
	int expression()
	{
		int es = 0;
		if (strcmp(token, "ID") == 0)
		{
			getnextandprint();
			if (strcmp(token, "=") == 0)
			{
				getnextandprint();
				es = ari_expression();
				if (es > 0)
					return(es);
			}
			else
			{
				return (es);
			}
		}
		return (es);
	}

	//<bool_expression>::=<ari_expression>(>|<|>=|<=|==|!=)<ari_expression>
	int bool_expression()
	{
		int es = 0;
		es = ari_expression();
		if (es > 0)
			return (es);
		if (strcmp(token, ">") == 0 || strcmp(token, ">=") == 0 || strcmp(token, "<") == 0 || strcmp(token, "<=") == 0
			|| strcmp(token, "==") == 0 || strcmp(token, "!=") == 0)
		{
			getnextandprint();
			es = ari_expression();
			if (es > 0)
				return(es);
		}
		return (es);
	}
	//<arithmetic_expression> -> <term><arithmetic_expression_1>
	int ari_expression()
	{
		int es = 0;
		es = term();
		if (es > 0)
			return (es);
		es = ari_expression_1();
		if (es > 0)
			return(es);
		return(es);
	}
	//<arithmetic_expression_1> -> +<term> <arithmetic_expression_1> | -<term> <arithmetic_expression_1> | ��

	int ari_expression_1()
	{
		int es = 0;
		if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0)
		{
			getnextandprint();
			es = term();
			if (es > 0)
				return es;
			es = ari_expression_1();
			if (es > 0)
				return es;
		}
		return es;
	}
	// <term> -> <factor><term_1>
	int term()
	{
		int es = 0;
		es = factor();
		if (es > 0)
			return (es);
		es = term_1();
		return(es);
	}
	// <term_1> -> *<factor><term_1> | /<factor><term_1> | ��
	int term_1()
	{
		int es = 0;
		if (strcmp(token, "*") == 0 || strcmp(token, "/") == 0)
		{
			getnextandprint();
			es = factor();
			if (es > 0)
				return(es);
			es = term_1();
			if (es > 0)
				return(es);
		}
		return es;
	}
	//<factor>::=(<ari_expression>)|ID|NUM
	int factor()
	{
		int es = 0;
		if (strcmp(token, "(") == 0)
		{
			getnextandprint();
			es = ari_expression();
			if (es > 0)
				return (es);
			if (strcmp(token, ")"))
			{
				return(es = 6);
			}
			getnextandprint();
		}
		else
		{
			if (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0)
			{
				getnextandprint();
				return(es);
			}
			else
			{
				return(es = 7);
			}
		}
		return(es);
	}

};

