#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char op;//�ַ�
	int level;//���ȼ�
}OpNode;

typedef struct//����һ��ջ
{
	OpNode op[100];
	int top;//�����������������п�����ջ��λ�ã�
	int size;//վ��Ԫ�ظ���
}stack;

void init(stack *st)
{
	st->size = 0;
	st->top = 0;//st->topָ���Ԫ��ʼ����ջ������ֵ�Ǹ�����������һ�����൱�ڸ��ӡ�
}

OpNode pop(stack *a)//��ջ
{
	if (a->size = 0)//��ջ��������
	{
		exit(-1);
	}
	a->size--;//ջ�Ĵ�С��һ
	return a->op[--(a->top)];//ȡ��ջ��Ԫ��
}

void push (stack *a, OpNode op)
{
	a->size++;
	a->op[(a->top)++] = op;
}

OpNode top(stack *a)//��ջ��Ԫ��
{
	if (a->size == 0)
	{
		printf("��ջ\n");
		exit(-1);
	}
	return a->op[(a->top) - 1];
}

typedef struct
{
	double num[100];
	int top;
	int size;
}numstack;//��ֵջ

void init2(numstack *st)
{
	st->size = 0;
	st->top = 0;
}

double pop2(numstack *a)
{
	if (a->size = 0)//��ջ��������
	{
		exit(-1);
	}
	a->size--;//ջ�Ĵ�С��һ
	return a->num[--(a->top)];//ȡ��ջ��Ԫ��
}

void push2(numstack *a, double num)
{
	a->size++;
	a->num[(a->top)++] = num;
}

void main()
{
	char ch = 'y';
	void change(char str[], char exp[]);
	double CalResult(char exp[]);//�����׺���ʽ
	double Directcalresult(char str[]);
	int check(char str[], char chestr[100]);
	char str[100], exp[100], chestr[100];//str�洢ԭ�������ʽ��exp�洢��Ӧ�ĺ�׺���ʽ��chestr�洢�ݴ��ַ�'^'
	do
	{
		printf("�����������ʽ��\n");
		gets(str);
		if (check(str, chestr))
		{
			printf("���ʽ����:\n");
			printf(chestr);
			printf("\n");
			printf("�Ƿ��������룿<y/n>::");
			while (ch = getchar(), ch != 'n'&&ch != 'y');
			if
		}
	}

}