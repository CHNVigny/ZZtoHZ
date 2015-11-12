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
typedef struct huozhui  ///这是链表节点
{
int Member;
typedef struct huozhui *Next;
}
void CreateList()
*/
typedef struct    //操作符栈节点
{
	char op;//字符
	int level;//优先级
	OpNode *Next;//指针域
}OpNode, *pNode1;

typedef struct    //浮点数栈节点
{
	double num;
	NumNode *Next;
}NumNode, *pNode2;

//    定义一个操作符栈结构
typedef struct     //操作符栈
{
	OpNode *Top;            //栈顶
	OpNode *Bottom;        //栈底
}Stack1, *pStack1;

typedef struct    //浮点数栈
{
	NumNode *Top;            //栈顶
	NumNode *Bottom;        //栈底
}Stack2, *pStack2;

void InitStack1(pStack1 ps)//初始化操作符栈
{
	ps->Top = (pNode)malloc(sizeof(OpNode));        //    分配内存空间给栈顶
	if (NULL == ps->Top)
	{
		printf("动态分配内存失败\n");
		exit(-1);
	}
	else
	{
		ps->Bottom = ps->Top;                    //    使栈底也指向栈顶空间
		ps->Top->Next = NULL;                    //    栈顶指针置为NULL；
	}
	//return;
}

void InitStack2(pStack2 ps)//初始化数值栈
{
	ps->Top = (NumNode*)malloc(sizeof(NumNode));        //    分配内存空间给栈顶
	if (NULL == ps->Top)
	{
		printf("动态分配内存失败\n");
		exit(-1);
	}
	else
	{
		ps->Bottom = ps->Top;                    //    使栈底也指向栈顶空间
		ps->Top->Next = NULL;                    //    栈顶指针置为NULL；
	}
	//return;
}
bool Push1(pStack1 ps, char op, int level)//向字符栈里压栈
{
	pNode1 pNew = (pNode1)malloc(sizeof(OpNode));    //    定义一个新节点，并分配内存空间
	if (NULL == pNew)
	{
		return false;
	}
	pNew->op = op;
	pNew->level = level;
	pNew->Next = ps->Top;                        //    使新节点的指针指向栈顶
	ps->Top = pNew;                                //    把新节点作为新栈顶

	return true;
}

bool Push2(pStack ps, double num)//向字符栈里压栈
{
	pNode2 pNew = (pNode2)malloc(sizeof(NumNode));    //    定义一个新节点，并分配内存空间
	if (NULL == pNew)
	{
		return false;
	}
	pNew->num = num;
	pNew->Next = ps->Top;                        //    使新节点的指针指向栈顶
	ps->Top = pNew;                                //    把新节点作为新栈顶
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

char Top1(pStack1 ps)//返回栈顶元素
{
	char ret;
	ret = ps->Top->op;
	return ret;
}

double Top2(pStack2 ps)//返回栈顶元素
{
	double ret;
	ret = ps->Top->num;
	return ret;
}

int main()
{
	int n;//输入数组的长度
	int i, j;//用于循环
	int rOpd, lOpd, result;
	char b;
	char c;//接弹出元素
	char *d = (char*)malloc(N*sizeof(char));//100个元素的数组，用于存放后缀表达式
	char *a = (char*)malloc(N*sizeof(char));
	SuanShi BDA[100];
	Stack s;
	Stack s2;
	InitStack(&s);
	InitStack(&s2);
	printf("请输入中缀表达式：\n");
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
	printf("后缀表达式为：\n");
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
	printf("后缀表达式的值为：\n");
	result = (int)Pop(&s2);
	printf("%d", result);
	return 0;

}