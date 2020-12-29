#pragma once

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class lex
{

public:

	//文件的输入输出
	ifstream file;
	ofstream out;

	//用于存放txt文件内容 
	char letter[10001];

	//用于记录letter的下标 
	int index = 0;

	//记录行数 
	int line = 1;

	int judge = 0;



	/*
	bool isAlpha(char ch);//判断字符是否为字母
	bool isNum(char ch);//判断字符是否为数字
	bool isNote(char ch);//判断字符是否为注释
	bool isAO(char ch);//判断是否为代数运算符
	bool isRO(char ch);//判断是否为关系运算符
	bool isMark(char ch);//判断是否为！
	bool isReserved(char ch);//判断是否为特殊分隔符
	bool isError(char ch);//判断是否是非法字符
	void Alpha();//识别并输出标识符 
	void Note();//识别并输出注释符 
	void Num();//识别并输出无符号整数
	void Reserved();//识别并输出分界符
	void AO();//识别并输出代数运算符 
	void RO();//识别并输出关系运算符 
	void Mark();//识别并输出感叹号 
	void Error();//识别并输出非法字符 

	void start();
	*/

	//判断字符是否为字母
	bool isAlpha(char ch)
	{
		if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
			return true;
		else
			return false;
	}

	//判断字符是否为数字
	bool isNum(char ch)
	{
		if ((ch >= '0' && ch <= '9'))
			return true;
		else
			return false;
	}

	//判断字符是否为注释
	bool isNote(char ch)
	{
		if (ch == '/')
			return true;
		else
			return false;
	}

	//判断是否为代数运算符
	bool isAO(char ch)
	{
		if (ch == '+' || ch == '-' || ch == '*' || ch == '%') {
			return true;
		}
		else
			return false;
	}

	//判断是否为关系运算符
	bool isRO(char ch)
	{
		if (ch == '<' || ch == '>' || ch == '=') {
			return true;
		}
		else
			return false;
	}

	//判断是否为！
	bool isMark(char ch)
	{
		if (ch == '!')
			return true;
		else
			return false;

	}

	//判断是否为特殊分隔符
	bool isReserved(char ch)
	{
		if (ch == '(' || ch == ')' || ch == ';'
			|| ch == '{' || ch == '}')
			return true;
		else
			return false;
	}

	//判断是否是非法字符
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

	//识别并输出标识符 
	void Alpha()
	{
		char str[50] = { 0 };
		int i = 0;
		str[i++] = letter[index];

		//组成单词
		while (isAlpha(letter[index + 1]) || isNum(letter[index + 1])) {
			index += 1;
			str[i++] = letter[index];
		}

		//判断是否为关键字，如果不是则为标识符
		if (strcmp(str, "if") == 0 || strcmp(str, "else") == 0 ||
			strcmp(str, "for") == 0 || strcmp(str, "while") == 0 ||
			strcmp(str, "do") == 0 || strcmp(str, "int") == 0 ||
			strcmp(str, "write") == 0 || strcmp(str, "read") == 0)
			out << str << "    " << str << endl;
		else
			out << "ID    " << str << endl;
	}

	//识别并输出注释符 
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
					cout << "行数:" << line << "  " << str << " 注释符使用错误" << endl;
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

	//识别并输出无符号整数
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

	//识别并输出分界符
	void Reserved()
	{
		out << letter[index] << "    " << letter[index] << endl;
	}

	//识别并输出代数运算符 
	void AO()
	{
		out << letter[index] << "    " << letter[index] << endl;
	}

	//识别并输出关系运算符 
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

	//识别并输出感叹号 
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
			cout << "行数：" << line << "  " << letter[index] << " 错因：运算符使用错误" << endl;
			judge = 1;
		}
	}

	//识别并输出非法字符 
	void Error()
	{
		cout << "行数：" << line << "  " << letter[index] << " 错因：非法字符" << endl;
		judge = 1;
	}

	//主程序
	int start()
	{
		string txtname;
		//cout << "输入源程序文件名:";
		//cin >> txtname;
		txtname = "text.txt";
		file.open(txtname);
		out.open("lex.txt");

		//保存txt文件中单个字符 
		char ch;

		//读取文件时控制下标 
		int i = 0;

		//读取txt文件到letter数组中 
		while (1) {
			file.get(ch);
			if (file.eof()) {
				break;
			}
			letter[i++] = ch;
		}

		//遍历letter
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

		cout << "词法分析程序输出的单词表文件名：lex.txt" << endl;

		return judge;
	}


};

