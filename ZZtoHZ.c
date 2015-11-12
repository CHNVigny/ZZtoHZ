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
	ps->Top = (pNode1)malloc(sizeof(OpNode));        //    �����ڴ�ռ��ջ��
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

bool Push2(pStack2 ps, double num)//���ַ�ջ��ѹջ
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

OpNode Pop1(pStack1 ps)
{
	OpNode ret;
	pNode1 Swap = NULL;
	if (Empty(ps))
	{
		exit(0);
	}
	else
	{
		ret.op = ps->Top->op;
		ret.level = ps->Top->level;
		Swap = ps->Top;
		ps->Top = ps->Top->Next;
		free(Swap);
		return ret;
	}
}

NumNode Pop2(pStack2 ps)
{
	NumNode ret;
	pNode2 Swap = NULL;
	if (Empty(ps))
	{
		exit(0);
	}
	else
	{
		ret.num = ps->Top->num;
		Swap = ps->Top;
		ps->Top = ps->Top->Next;
		free(Swap);
		return ret;
	}
}

OpNode Top1(pStack1 ps)//����ջ��Ԫ��
{
	OpNode ret;
	ret.op = ps->Top->op;
	ret.level = ps->Top->level;
	return ret;
}

NumNode Top2(pStack2 ps)//����ջ��Ԫ��
{
	NumNode ret;
	ret.num = ps->Top->num;
	return ret;
}

void change(char str[], char *ch)//��׺ת��׺
{
	int i = 0;//str������
	int k = 0;
	char c;//�ַ�����ȡ���ķ���c
	Stack1 st;//����ջ
	char opp;//op.op

	OpNode op;
	OpNode ops;
	InitStack1(&st);//����ջ��ʼ��
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
			Push1(&st, c, -1);
		}
		if (c == ')')
		{
			op = Top1(&st);//��ջ��
			while (!Empty1(&st) && op.op != '(')
			{
				op = Pop1(&st);
				ch[k++] = op.op;
				if (!Empty(&st))
				{
					op = Top1(&st);
				}
				else
					break;//ջ�վͽ���
			}
			Pop1(&st);//ȥ��������
		}
		if (c == '+' || c == '-')//�Ӽ���
		{
			op.op = c;
			op.level = 1;//
			if (Empty(&st))//��ջ
			{
				Push1(&st, c, 1);//ֱ����ջ
			}
			else
			{
				ops = Top1(&st);
				while (ops.level >= op.level)
				{
					ops = Pop1(&st);
					ch[k++] = ops.op;
					if (!Empty1(&st))
						ops = Top1(&st);
					else
						break;
				}
				Push1(&st, c, 1);//��ʱջ�������ȼ�û��op���ˣ���op��ջ
			}
		}
		if (c == '+' || c == '/' || c == '%')
		{
			op.op = c;
			op.level = 2;
			if (Empty1(&st))//��ջ
			{
				Push1(&st, c, 2);//ջ�ռ���ջ
			}
		}
		else
		{
			{
				ops = Top1(&st);
				while (ops.level >= op.level)
				{
					ops = Pop1(&st);
					ch[k++] = ops.op;
					if (!Empty1(&st))//ջ��Ϊ��
					{
						ops = Top1(&st);
					}
					else
						break;
				}
				Push1(&st, c, 2);//��ʱջ�����ȼ��ͣ���ջ��
			}
		}
		c = str[i++];
	}
	while (!Empty1(&st))//����ж�ջ�Ƿ�Ϊ��
	{
		ops = Pop1(&st);//ȡ��ջ��Ԫ�ش���������
		ch[k++] = ops.op;
	}
	ch[k] = '\0';
}

int main()
{
	int n;//��������ĳ���
	int i, j;//����ѭ��
	int rOpd, lOpd, result;
	char b;
	char c;//�ӵ���Ԫ��
	char a[100], b[100];//a(str)�洢ԭ�������ʽ��b(exp)�洢��Ӧ�ĺ�׺���ʽ
	Stack1 s1;//������ջ
	Stack2 s2;//��ջ
	InitStack1(&s1);
	InitStack2(&s2);
	printf("��������׺���ʽ��\n");
	gets(a);
	n = strlen(a);
	a[n] = '\0';
	
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