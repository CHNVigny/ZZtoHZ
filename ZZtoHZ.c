#include <stdio.h>
#include <string.h>
#include <malloc.h>
//#include <VgStack.h>
#include <stdlib.h>
#define bool int
#define false 0
#define true 1
#define N 100

/*
typedef struct huozhui  ///��������ڵ�
{
int Member;
typedef struct huozhui *Next;
}
void CreateList()
*/
typedef struct    //������ջ�ڵ�
{
	char op;//�ַ�
	int level;//���ȼ�
	OpNode *Next;//ָ����
}OpNode, *pNode1;

typedef struct    //������ջ�ڵ�
{
	double num;
	NumNode *Next;
}NumNode, *pNode2;

//    ����һ��������ջ�ṹ
typedef struct     //������ջ
{
	OpNode *Top;            //ջ��
	OpNode *Bottom;        //ջ��
}Stack1, *pStack1;

typedef struct    //������ջ
{
	NumNode *Top;            //ջ��
	NumNode *Bottom;        //ջ��
}Stack2, *pStack2;

void InitStack1(pStack1 ps)//��ʼ��������ջ
{
	ps->Top = (pNode)malloc(sizeof(OpNode));        //    �����ڴ�ռ��ջ��
	if (NULL == ps->Top)
	{
		printf("��̬�����ڴ�ʧ��\n");
		exit(-1);
	}
	else
	{
		ps->Bottom = ps->Top;                    //    ʹջ��Ҳָ��ջ���ռ�
		ps->Top->Next = NULL;                    //    ջ��ָ����ΪNULL��
	}
	//return;
}

void InitStack2(pStack2 ps)//��ʼ����ֵջ
{
	ps->Top = (NumNode*)malloc(sizeof(NumNode));        //    �����ڴ�ռ��ջ��
	if (NULL == ps->Top)
	{
		printf("��̬�����ڴ�ʧ��\n");
		exit(-1);
	}
	else
	{
		ps->Bottom = ps->Top;                    //    ʹջ��Ҳָ��ջ���ռ�
		ps->Top->Next = NULL;                    //    ջ��ָ����ΪNULL��
	}
	//return;
}
bool Push1(pStack1 ps, char op, int level)//���ַ�ջ��ѹջ
{
	pNode1 pNew = (pNode1)malloc(sizeof(OpNode));    //    ����һ���½ڵ㣬�������ڴ�ռ�
	if (NULL == pNew)
	{
		return false;
	}
	pNew->op = op;
	pNew->level = level;
	pNew->Next = ps->Top;                        //    ʹ�½ڵ��ָ��ָ��ջ��
	ps->Top = pNew;                                //    ���½ڵ���Ϊ��ջ��

	return true;
}

bool Push2(pStack ps, double num)//���ַ�ջ��ѹջ
{
	pNode2 pNew = (pNode2)malloc(sizeof(NumNode));    //    ����һ���½ڵ㣬�������ڴ�ռ�
	if (NULL == pNew)
	{
		return false;
	}
	pNew->num = num;
	pNew->Next = ps->Top;                        //    ʹ�½ڵ��ָ��ָ��ջ��
	ps->Top = pNew;                                //    ���½ڵ���Ϊ��ջ��
	return true;
}
bool Empty1(pStack1 ps)
{
	if (ps->Top == ps->Bottom)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Empty2(pStack2 ps)
{
	if (ps->Top == ps->Bottom)
	{
		return true;
	}
	else
	{
		return false;
	}
}

char Pop1(pStack1 ps)
{
	char ret;
	pNode1 Swap = NULL;
	if (Empty(ps))
	{
		exit(0);
	}
	else
	{
		ret = ps->Top->op;
		Swap = ps->Top;
		ps->Top = ps->Top->Next;
		free(Swap);
		return ret;
	}
}

double Pop2(pStack2 ps)
{
	double ret;
	pNode2 Swap = NULL;
	if (Empty(ps))
	{
		exit(0);
	}
	else
	{
		ret = ps->Top->num;
		Swap = ps->Top;
		ps->Top = ps->Top->Next;
		free(Swap);
		return ret;
	}
}

char Top1(pStack1 ps)//����ջ��Ԫ��
{
	char ret;
	ret = ps->Top->op;
	return ret;
}

double Top2(pStack2 ps)//����ջ��Ԫ��
{
	double ret;
	ret = ps->Top->num;
	return ret;
}

int main()
{
	int n;//��������ĳ���
	int i, j;//����ѭ��
	int rOpd, lOpd, result;
	char b;
	char c;//�ӵ���Ԫ��
	char *d = (char*)malloc(N*sizeof(char));//100��Ԫ�ص����飬���ڴ�ź�׺���ʽ
	char *a = (char*)malloc(N*sizeof(char));
	SuanShi BDA[100];
	Stack s;
	Stack s2;
	InitStack(&s);
	InitStack(&s2);
	printf("��������׺���ʽ��\n");
	gets(a);
	n = strlen(a);
	a[n] = '\0';
	j = 0;
	for (i = 0;i < n;i++)
	{
		b = a[i];
		if (a[i] > 47 && a[i] < 58)
		{
			if (i == 0 || a[i - 1] == 37 || a[i - 1] == 40 || a[i - 1] == 41 || a[i - 1] == 42 || a[i - 1] == 43 || a[i - 1] == 45 || a[i - 1] == 47)
			{
				BDA[j].num = a[i];
				if (a[i + 1] == 37 || a[i + 1] == 40 || a[i + 1] == 41 || a[i + 1] == 42 || a[i + 1] == 43 || a[i + 1] == 45 || a[i + 1] == 47)
				{
					j = j + 1;
				}
			}
			else if (a[i - 1] > 47 && a[i - 1] < 58)
			{
				BDA[j].num = BDA[j].num * 10 + a[i];
				if (a[i + 1] == 37 || a[i + 1] == 40 || a[i + 1] == 41 || a[i + 1] == 42 || a[i + 1] == 43 || a[i + 1] == 45 || a[i + 1] == 47)
				{
					j = j + 1;
				}
			}
			else
			{
				BDA[j].op = a[i];
				j = j + 1;
			}
		}
	}
	printf("��׺���ʽΪ��\n");
	j = 0;
	for (i = 0;i < n;i++)
	{

		b = a[i];
		if (b > 47 && b < 58)
		{
			printf("%c", b);
			d[j] = b;
			j += 1;
		}
		else if (b == 37 || b == 40 || b == 41 || b == 42 || b == 43 || b == 45 || b == 47)
		{
			if (b != ')' && (Empty(&s) || Top(&s) == '('))
			{
				Push(&s, b);
			}
			else
			{
				switch (b)
				{
				case '(':
					Push(&s, b);
					break;
				case ')':
					while (Top(&s) != '(')
					{
						c = Pop(&s);
						d[j] = c;
						j += 1;
						printf("%c", c);

					}
					if (Top(&s) == '(')
					{
						Pop(&s);
					}
					break;
				case '%':
					if (Top(&s) == '+' || Top(&s) == '-' || Top(&s) == '(')
					{
						Push(&s, b);
					}
					else if (Top(&s) == '/' || Top(&s) == '*' || Top(&s) == '%')
					{
						c = Pop(&s);
						d[j] = c;
						j += 1;
						printf("%c", c);
						Push(&s, b);
					}
					break;
				case '*':

					if (Top(&s) == '+' || Top(&s) == '-' || Top(&s) == '(')
					{
						Push(&s, b);
					}
					else if (Top(&s) == '/' || Top(&s) == '*' || Top(&s) == '%')
					{
						c = Pop(&s);
						d[j] = c;
						j += 1;
						printf("%c", c);
						Push(&s, b);
					}
					else
					{
						d[j] = b;
						j += 1;
						printf("%c", b);
					}
					break;
				case '/':
					if (Top(&s) == '+' || Top(&s) == '-' || Top(&s) == '(')
					{
						Push(&s, b);
					}
					else if (Top(&s) == '/' || Top(&s) == '*' || Top(&s) == '%')
					{
						c = Pop(&s);
						d[j] = c;
						j += 1;
						printf("%c", c);
						Push(&s, b);
					}
					else
					{
						d[j] = b;
						j += 1;
						printf("%c", b);

					}
					break;
				case '+':
					if ('(' == Top(&s))
					{
						Push(&s, b);
					}
					else if (Top(&s) == '-' || Top(&s) == '+')
					{
						c = Pop(&s);
						d[j] = c;
						j += 1;
						printf("%c", c);
						Push(&s, b);
					}
					else
					{
						d[j] = b;
						j += 1;
						printf("%c", b);

					}
					break;
				case '-':
					if (Top(&s) == '(')
					{
						Push(&s, b);
					}
					else if (Top(&s) == '-' || Top(&s) == '+')
					{
						c = Pop(&s);
						d[j] = c;
						j += 1;
						printf("%c", c);
						Push(&s, b);
					}
					else
					{
						d[j] = b;
						j += 1;
						printf("%c", b);

					}
					break;
				}
			}
		}
	}
	while (!Empty(&s))
	{
		c = Pop(&s);
		d[j] = c;
		j += 1;
		printf("%c", c);

	}
	/*
	printf("\n");
	for (i=0;i<j;i++)
	{
	printf("%c",d[i]);
	}
	*/
	for (i = 0; i < j; i++)
	{
		b = d[i];
		if (b > 47 && b < 58)
		{
			n = b - 48;
			Push(&s2, n);
		}
		else if (b == 37 || b == 42 || b == 43 || b == 45 || b == 47)
		{
			switch (b)
			{
			case '+':
				rOpd = (int)Pop(&s2);
				lOpd = (int)Pop(&s2);
				result = lOpd + rOpd;
				Push(&s2, result);
				break;
			case '-':
				rOpd = (int)Pop(&s2);
				lOpd = (int)Pop(&s2);
				result = lOpd - rOpd;
				Push(&s2, result);
				break;
			case '*':
				rOpd = (int)Pop(&s2);
				lOpd = (int)Pop(&s2);
				result = lOpd*rOpd;
				Push(&s2, result);
				break;
			case '/':
				rOpd = (int)Pop(&s2);
				lOpd = (int)Pop(&s2);
				result = lOpd / rOpd;
				Push(&s2, result);
				break;
			case '%':
				rOpd = (int)Pop(&s2);
				lOpd = (int)Pop(&s2);
				result = lOpd%rOpd;
				Push(&s2, result);
				break;
			}
		}
	}
	printf("\n");
	printf("��׺���ʽ��ֵΪ��\n");
	result = (int)Pop(&s2);
	printf("%d", result);
	return 0;

}