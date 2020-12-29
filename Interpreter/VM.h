#pragma once

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <cstring>

class VM
{
public:
	int start()
	{
		int es = 0, i, k = 0;//���� 
		int codecount;//������ 
		int stack[1000];//������ջ 
		int stacktop = 0;//ջ�� 
		char code[1000][20];//�������� 
		int data[1000]; //��ŵ�ַ������ 
		int label[100];//��Ԫʽ�ı�� 
		char lno[4];
		FILE* fin; //����ָ����������ļ���ָ��

		if ((fin = fopen("assembly.txt", "r")) == NULL)
		{
			printf("\n���ļ�����!\n");
			es = 10;
			return(es);
		}
		codecount = 0;//��ʼ�� 
		fscanf(fin, "%s", &code[codecount]);
		while (!feof(fin))
		{
			i = strlen(code[codecount]) - 1;
			if (code[codecount][i] == ':')
			{
				i = i - 5;
				strncpy(lno, &code[codecount][5], i);
				lno[i] = '\0';
				label[atoi(lno)] = codecount;//��label�����סÿ����ŵĵ�ַ
				code[codecount][0] = ':';
				code[codecount][1] = '\0';
				strcat(code[codecount], lno);
				k++;
			}
			codecount++;
			fscanf(fin, "%s", &code[codecount]);
		}
		fclose(fin);

		for (i = 0; i < codecount; i++)
		{
			int l;
			l = strlen(code[i]);
			if ((l > 1) && (code[i][1] == 'A'))
			{
				lno[0] = code[i][l - 1];
				lno[1] = '\0';
				_itoa(label[atoi(lno)], code[i], 10);//����ת�� 
			}
		}

		i = 0;

		while (i < codecount)//ִ��ÿ��ָ��
		{

			if (strcmp(code[i], "LOAD") == 0)//LOAD D��D�е����ݼ��ص�������ջ��
			{
				i++;
				stack[stacktop] = data[atoi(code[i])];
				stacktop++;
			}
			if (strcmp(code[i], "LOADI") == 0)//LOADI a������aѹ�������ջ
			{
				i++;
				stack[stacktop] = atoi(code[i]);
				stacktop++;
			}
			//STO D ��������ջջ����Ԫ���ݴ���D
			//��ջ����Ԫ���ݱ��ֲ��䡣
			if (strcmp(code[i], "STO") == 0)
			{
				i++;
				data[atoi(code[i])] = stack[stacktop - 1];
			}
			//STI D ��������ջջ����Ԫ���ݴ���D
			//��ջ����Ԫ���ݳ�ջ��
			if (strcmp(code[i], "POP") == 0)
			{
				stacktop--;
			}
			//ADD����ջ����Ԫ��ջ����Ԫ���ݳ�ջ����ӣ�������ջ����
			if (strcmp(code[i], "ADD") == 0)
			{
				stack[stacktop - 2] = stack[stacktop - 2] + stack[stacktop - 1];
				stacktop--;
			}
			//SUB    ����ջ����Ԫ��ȥջ����Ԫ���ݲ���ջ��������ջ����
			if (strcmp(code[i], "SUB") == 0)
			{
				stack[stacktop - 2] = stack[stacktop - 2] - stack[stacktop - 1];
				stacktop--;
			}
			//MULT   ����ջ����Ԫ��ջ����Ԫ���ݳ�ջ����ˣ�������ջ����
			if (strcmp(code[i], "MULT") == 0)
			{
				stack[stacktop - 2] = stack[stacktop - 2] * stack[stacktop - 1];
				stacktop--;
			}
			//DIV    ����ջ����Ԫ��ջ����Ԫ���ݳ�ջ�������������ջ����
			if (strcmp(code[i], "DIV") == 0)
			{
				stack[stacktop - 2] = stack[stacktop - 2] / stack[stacktop - 1];
				stacktop--;
			}
			//BR    lab  ������ת�Ƶ�lab
			if (strcmp(code[i], "BR") == 0)
			{
				i++;
				i = atoi(code[i]);
			}
			//BRF  lab  ���ջ����Ԫ�߼�ֵ����Ϊ�٣�0����ת�Ƶ�lab
			if (strcmp(code[i], "BRF") == 0)
			{
				i++;
				if (stack[stacktop - 1] == 0) i = atoi(code[i]);
				stacktop--;
			}
			//EQ  ��ջ������Ԫ�����ڱȽϣ�����������٣�1��0������ջ��
			if (strcmp(code[i], "EQ") == 0)
			{
				stack[stacktop - 2] = stack[stacktop - 2] == stack[stacktop - 1];
				stacktop--;
			}
			//NOTEQ ��ջ������Ԫ�������ڱȽϣ�����������٣�1��0������ջ��
			if (strcmp(code[i], "NOTEQ") == 0)
			{
				stack[stacktop - 2] = stack[stacktop - 2] != stack[stacktop - 1];
				stacktop--;
			}
			//GT    ��ջ������ջ������������ջ����1��������0
			if (strcmp(code[i], "GT") == 0)
			{
				stack[stacktop - 2] = stack[stacktop - 2] > stack[stacktop - 1];
				stacktop--;
			}
			//LES  ��ջ��С��ջ������������ջ����1��������0
			if (strcmp(code[i], "LES") == 0)
			{
				stack[stacktop - 2] = stack[stacktop - 2] < stack[stacktop - 1];
				stacktop--;
			}
			//GE  ��ջ�����ڵ���ջ������������ջ����1��������0
			if (strcmp(code[i], "GE") == 0)
			{
				stack[stacktop - 2] = stack[stacktop - 2] >= stack[stacktop - 1];
				stacktop--;
			}
			//LE  ��ջ��С�ڵ���ջ������������ջ����1��������0
			if (strcmp(code[i], "LE") == 0)
			{
				stack[stacktop - 2] = stack[stacktop - 2] <= stack[stacktop - 1];
				stacktop--;
			}
			//AND ��ջ������Ԫ���߼������㣬����������٣�1��0������ջ��
			if (strcmp(code[i], "AND") == 0)
			{
				stack[stacktop - 2] = stack[stacktop - 2] && stack[stacktop - 1];
				stacktop--;
			}
			//OR  ��ջ������Ԫ���߼������㣬����������٣�1��0������ջ��
			if (strcmp(code[i], "OR") == 0)
			{
				stack[stacktop - 2] = stack[stacktop - 2] || stack[stacktop - 1];
				stacktop--;
			}
			//NOT  ��ջ�����߼�ֵȡ��
			if (strcmp(code[i], "NOT") == 0)
			{
				stack[stacktop - 1] = !stack[stacktop - 1];
			}
			//IN �ӱ�׼�����豸�����̣�����һ���������ݣ�����ջ��
			if (strcmp(code[i], "IN") == 0)
			{
				printf("Please input��");
				scanf("%d", &stack[stacktop]);
				stacktop++;
			}
			//OUT ��ջ����Ԫ���ݳ�ջ�����������׼����豸�ϣ���ʾ������
			if (strcmp(code[i], "OUT") == 0)
			{
				printf("Print:%d\n", stack[stacktop - 1]);
				stacktop--;
			}
			//STOP ִֹͣ��
			if (strcmp(code[i], "STOP") == 0)
			{
				stack[stacktop] = '\n';
				return 0;
			}
			i++;
		}
		return 0;
	}


};

