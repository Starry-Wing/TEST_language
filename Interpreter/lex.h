#pragma once

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class lex
{

public:

	//�ļ����������
	ifstream file;
	ofstream out;

	//���ڴ��txt�ļ����� 
	char letter[10001];

	//���ڼ�¼letter���±� 
	int index = 0;

	//��¼���� 
	int line = 1;

	int judge = 0;



	/*
	bool isAlpha(char ch);//�ж��ַ��Ƿ�Ϊ��ĸ
	bool isNum(char ch);//�ж��ַ��Ƿ�Ϊ����
	bool isNote(char ch);//�ж��ַ��Ƿ�Ϊע��
	bool isAO(char ch);//�ж��Ƿ�Ϊ���������
	bool isRO(char ch);//�ж��Ƿ�Ϊ��ϵ�����
	bool isMark(char ch);//�ж��Ƿ�Ϊ��
	bool isReserved(char ch);//�ж��Ƿ�Ϊ����ָ���
	bool isError(char ch);//�ж��Ƿ��ǷǷ��ַ�
	void Alpha();//ʶ�������ʶ�� 
	void Note();//ʶ�����ע�ͷ� 
	void Num();//ʶ������޷�������
	void Reserved();//ʶ������ֽ��
	void AO();//ʶ�������������� 
	void RO();//ʶ�������ϵ����� 
	void Mark();//ʶ�������̾�� 
	void Error();//ʶ������Ƿ��ַ� 

	void start();
	*/

	//�ж��ַ��Ƿ�Ϊ��ĸ
	bool isAlpha(char ch)
	{
		if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
			return true;
		else
			return false;
	}

	//�ж��ַ��Ƿ�Ϊ����
	bool isNum(char ch)
	{
		if ((ch >= '0' && ch <= '9'))
			return true;
		else
			return false;
	}

	//�ж��ַ��Ƿ�Ϊע��
	bool isNote(char ch)
	{
		if (ch == '/')
			return true;
		else
			return false;
	}

	//�ж��Ƿ�Ϊ���������
	bool isAO(char ch)
	{
		if (ch == '+' || ch == '-' || ch == '*' || ch == '%') {
			return true;
		}
		else
			return false;
	}

	//�ж��Ƿ�Ϊ��ϵ�����
	bool isRO(char ch)
	{
		if (ch == '<' || ch == '>' || ch == '=') {
			return true;
		}
		else
			return false;
	}

	//�ж��Ƿ�Ϊ��
	bool isMark(char ch)
	{
		if (ch == '!')
			return true;
		else
			return false;

	}

	//�ж��Ƿ�Ϊ����ָ���
	bool isReserved(char ch)
	{
		if (ch == '(' || ch == ')' || ch == ';'
			|| ch == '{' || ch == '}')
			return true;
		else
			return false;
	}

	//�ж��Ƿ��ǷǷ��ַ�
	bool isError(char ch)
	{
		if (!isMark(ch) && !isReserved(ch)
			&& !isAlpha(ch) && !isNum(ch)
			&& !isRO(ch) && !isAO(ch)
			&& !isNote(ch) && ch != ' '&& ch!='\t')
			return true;
		else
			return false;
	}

	//ʶ�������ʶ�� 
	void Alpha()
	{
		char str[50] = { 0 };
		int i = 0;
		str[i++] = letter[index];

		//��ɵ���
		while (isAlpha(letter[index + 1]) || isNum(letter[index + 1])) {
			index += 1;
			str[i++] = letter[index];
		}

		//�ж��Ƿ�Ϊ�ؼ��֣����������Ϊ��ʶ��
		if (strcmp(str, "if") == 0 || strcmp(str, "else") == 0 ||
			strcmp(str, "for") == 0 || strcmp(str, "while") == 0 ||
			strcmp(str, "do") == 0 || strcmp(str, "int") == 0 ||
			strcmp(str, "write") == 0 || strcmp(str, "read") == 0)
			out << str << "    " << str << endl;
		else
			out << "ID    " << str << endl;
	}

	//ʶ�����ע�ͷ� 
	void Note()
	{
		char str[500] = { 0 };
		int i = 0;
		str[i++] = letter[index];
		if (letter[index + 1] == '*') {
			index += 1;
			str[i++] = letter[index];
			while (1) {
				if (letter[index] == EOF) {
					cout << "����:" << line << "  " << str << " ע�ͷ�ʹ�ô���" << endl;
					judge = 1;
					break;
				}
				index += 1;
				str[i++] = letter[index];
				if (letter[index] == '*') {
					if (letter[index + 1] == '/') {
						index += 1;
						str[i++] = letter[index];
						break;
					}
					else {
						continue;
					}
				}
			}
		}
		else {
			out << str << "     " << str << endl;
		}
	}

	//ʶ������޷�������
	void Num()
	{
		char str[50] = { 0 };
		int i = 0;
		if (letter[index] == '0')
		{
			str[i++] = letter[index];
			out << "NUM    " << str << endl;
		}
		else
		{
			while (isNum(letter[index])) {
				str[i++] = letter[index];
				index += 1;
			}
			index -= 1;
			out << "NUM    " << str << endl;
		}
	}

	//ʶ������ֽ��
	void Reserved()
	{
		out << letter[index] << "    " << letter[index] << endl;
	}

	//ʶ�������������� 
	void AO()
	{
		out << letter[index] << "    " << letter[index] << endl;
	}

	//ʶ�������ϵ����� 
	void RO()
	{
		char str[500] = { 0 };
		int i = 0;
		str[i++] = letter[index];
		if (letter[index + 1] == '=') {
			str[i++] = letter[index + 1];
			index += 1;
			out << str << "    " << str << endl;
		}
		else {
			out << str << "    " << str << endl;
		}
	}

	//ʶ�������̾�� 
	void Mark()
	{
		char str[50] = { 0 };
		int i = 0;
		str[i++] = letter[index];
		if (letter[index + 1] == '=') {
			index += 1;
			str[i++] = letter[index];
			out << str << "    " << str << endl;
		}
		else {
			cout << "������" << line << "  " << letter[index] << " ���������ʹ�ô���" << endl;
			judge = 1;
		}
	}

	//ʶ������Ƿ��ַ� 
	void Error()
	{
		cout << "������" << line << "  " << letter[index] << " ���򣺷Ƿ��ַ�" << endl;
		judge = 1;
	}

	//������
	int start()
	{
		string txtname;
		//cout << "����Դ�����ļ���:";
		//cin >> txtname;
		txtname = "text.txt";
		file.open(txtname);
		out.open("lex.txt");

		//����txt�ļ��е����ַ� 
		char ch;

		//��ȡ�ļ�ʱ�����±� 
		int i = 0;

		//��ȡtxt�ļ���letter������ 
		while (1) {
			file.get(ch);
			if (file.eof()) {
				break;
			}
			letter[i++] = ch;
		}

		//����letter
		for (index = 0; index < strlen(letter); index++) {
			if (letter[index] == '\n') {
				line++;
			}
			else if (isRO(letter[index])) {
				RO();
			}
			else if (isAlpha(letter[index])) {
				Alpha();
			}
			else if (isNote(letter[index])) {
				Note();
			}
			else if (isNum(letter[index])) {
				Num();
			}
			else if (isMark(letter[index])) {
				Mark();
			}
			else if (isAO(letter[index])) {
				AO();
			}
			else if (isReserved(letter[index])) {
				Reserved();
			}
			else if (isError(letter[index])) {
				Error();
			}
		}
		out.close();

		cout << "�ʷ�������������ĵ��ʱ��ļ�����lex.txt" << endl;

		return judge;
	}


};

