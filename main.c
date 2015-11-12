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
	int top;//ջ��λ��
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
			if (ch == 'y')
			{
				system("pause");
				continue;
			}
			if (ch == 'n')
			{
				system("pause");
				exit(-1);
			}
		}
		change(str, exp);
		printf("��׺���ʽ�ǣ�%s\n", exp);
		printf("������Ϊ��%f\n", CalResult(exp));
		printf("�Ƿ��������룿<y/n>::");
		while (ch = getchar(), ch != 'n'&&ch != 'y');
		system("pause");
	} while (ch != 'n');
}

void change(char str[], char ch[])//��׺ת��׺
{
	int i = 0;//str������
	int k = 0;
	char c;//�ַ�����ȡ���ķ���c
	stack st;//����ջ
	OpNode op;
	OpNode ops;
	init(&st);//����ջ��ʼ��
	c = str[i++];
	while (c != '\0')
	{
		if ((c >= '0'&&c <= '9') || c == '.')
		{
			while ((c >= '0'&&c <= '9') || c == '.')
			{
				ch[k++] = c;//���ַ�ֱ�ӷŵ�������
				c = str[i++];
			}
			ch[k++] = ' ';
		}
		if (c == '(')
		{
			op.op = '(';
			op.level = -1;//���ȼ�
			push(&st, op);
		}
		if (c == ')')
		{
			op = top(&st);//��ջ��
			while (st.size != 0/*!Empty(st)*/ && op.op != '(')
			{
				op = pop(&st);
				ch[k++] = op.op;
				if (st.size > 0/*!Empty(st)*/)
				{
					op = top(&st);
				}
				else
					break;//ջ�վͽ���
			}
			pop(&st);//ȥ��������
		}
		if (c == '+' || c = '-')//�Ӽ���
		{
			op.op = c;
			op.level = 1;//
			if (st.size == 0)//��ջ
			{
				push(&st, op);//ֱ����ջ
			}
			else
			{
				ops = top(&st);
				while (ops.level >= op.level)
				{
					ops = pop(&st);
					ch[k++] = ops.op;
					if (st.size > 0/*!Empty(st)*/)
						ops = top(&st);
					else
						break;
				}
				push(&st, op);//��ʱջ�������ȼ�û��op���ˣ���op��ջ
			}
		}
		if (c=='+'||c=='/'||c++'%')
		{
			op.op = c;
			op.level = 2;
			if (st.size == 0/*Empty(st)*/)//��ջ
			{
				push(&st, op);//ջ�ռ���ջ
			}
		}
		else
		{
			{
				ops = top(&st);
				while (ops.level >= op.level)
				{
					ops = pop(&st);
					ch[k++] = ops.op;
					if (st.size > 0)//ջ��Ϊ��
					{
						ops = top(&st);
					}
					else
						break;
				}
				push(&st, op);//��ʱջ�����ȼ��ͣ���ջ��
			}
		}
		c = str[i++];
	}
	while (st.size != 0)//����ж�ջ�Ƿ�Ϊ��
	{
		ops = pop(&st);//ȡ��ջ��Ԫ�ش���������
		ch[k++] = ops.op;
	}
	ch[k] = '\0';
}

double CalResult(char exp[])//�����׺���ʽ
{
	char c;
	numstack numst;//������ֵջ
	double d1, d2, dr;
	int k = 0;//��׺���ʽ����
	int i = 0;//���ַ�ת��Ϊ������������
	char *s;
	char trans[100];//���ַ���ʾ��һ������
	init2(&numst);//��ʼ����ֵջ
	c = exp[k++];
	while (c != '\0')//��׺���ʽ��\0����
	{
		if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
		{
			switch(c)
			{
			case '+':
				d2 = pop2(&numst);
				d1 = pop2(&numst);
				dr = d1 + d2;
				push2(&numst, dr);
				break;
			case '-':
				d2 = pop2(&numst);
				d1 = pop2(&numst);
				dr = d1 - d2;
				push2(&numst, dr);
				break;
			case '*':
				d2 = pop2(&numst);
				d1 = pop2(&numst);
				dr = d1 * d2;
				push2(&numst, dr);
				break;
			case '/':
				d2 = pop2(&numst);
				d1 = pop2(&numst);
				dr = d1 / d2;
				push2(&numst, dr);
				break;
			case '%':
				d2 = pop2(&numst);
				d1 = pop2(&numst);
				dr = (double)((int)d1 % (int)d2);
				push2(&numst, dr);
				break;
			}
		}
		if (c >= '0'&&c <= '9' || c == '.')//���������
		{
			while (c >= '0'&&c <= '9' || c == '.')
			{
				trans[i++] = c;//���ַ��������������һ����ɨ��
				c = exp[k++];
			}
			trans[i++] = '\0';
			i = 0;
			s = trans;//��ָ��ָ���ַ����飻
			d1 = atof(s);//���ú������ַ���ת���ɸ�����
			push2(&numst, d1);
		}
		c = exp[k++];
	}
	return pop2(&numst);
}

//��13ҳ