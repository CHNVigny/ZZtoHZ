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
typedef struct node1    //操作符栈节点
{
	char op;//字符
	int level;//优先级
	struct node1 *Next;//指针域
}OpNode, *pNode1;

typedef struct node2    //浮点数栈节点
{
	double num;
	struct node2 *Next;
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
	ps->Top = (pNode1)malloc(sizeof(OpNode));        //    分配内存空间给栈顶
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

bool Push2(pStack2 ps, double num)//向字符栈里压栈
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

OpNode Pop1(pStack1 ps)
{
	OpNode ret;
	pNode1 Swap = NULL;
	if (Empty1(ps))
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
	if (Empty2(ps))
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

OpNode Top1(pStack1 ps)//返回栈顶元素
{
	OpNode ret;
	ret.op = ps->Top->op;
	ret.level = ps->Top->level;
	return ret;
}

NumNode Top2(pStack2 ps)//返回栈顶元素
{
	NumNode ret;
	ret.num = ps->Top->num;
	return ret;
}

int main()
{
	int n;//输入数组的长度
	char str[100];//中缀
	char ch[100];//后缀表达式
	Stack1 s1;//操作符栈
	Stack2 s2;//数栈
	InitStack1(&s1);
	InitStack2(&s2);
	int i = 0;//str的索引
	int k = 0;
	int a;
	char c;//字符串中取出的放在c
	Stack1 st;//符号栈
	OpNode op;
	OpNode ops;
	printf("请输入中缀表达式：\n");
	gets(str);
	n = strlen(str);
	str[n] = '\0';
	c = str[i++];
	while (c != '\0')
	{
		if ((c >= '0'&&c <= '9') || c == '.')
		{
			while ((c >= '0'&&c <= '9') || c == '.')
			{
				ch[k++] = c;//将字符直接放到数组中
				c = str[i++];
			}
			ch[k++] = ' ';
		}
		if (c == '(')
		{
			op.op = '(';
			op.level = -1;//优先级
			Push1(&st, c, -1);
		}
		if (c == ')')
		{
			op = Top1(&st);//看栈顶
			a = Empty1(&st);
			while (a != 1 && op.op != '(')
			{
				op = Pop1(&st);
				ch[k++] = op.op;
				if (!Empty1(&st))
				{
					op = Top1(&st);
				}
				else
					break;//栈空就结束
			}
			Pop1(&st);//去掉左括号
		}
		if (c == '+' || c == '-')//加减号
		{
			op.op = c;
			op.level = 1;//
			if (Empty1(&st))//空栈
			{
				Push1(&st, c, 1);//直接入栈
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
				Push1(&st, c, 1);//此时栈顶的优先级没有op高了，将op入栈
			}
		}
		if (c == '+' || c == '/' || c == '%')
		{
			op.op = c;
			op.level = 2;
			if (Empty1(&st))//空栈
			{
				Push1(&st, c, 2);//栈空即入栈
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
					a = Empty1(&st);
					if (a != 1)//栈不为空
					{
						ops = Top1(&st);
					}
					else
						break;
				}
				Push1(&st, c, 2);//此时栈顶优先级低，入栈。
			}
		}
		c = str[i++];
	}
	a = Empty1(&st);
	while (a != 1)//最后判断栈是否为空
	{
		ops = Pop1(&st);//取出栈内元素存入数组中
		ch[k++] = ops.op;
	}
	ch[k] = '\0';
	printf("后缀表达式为：%s\n",ch);
	system("pause");
	return 0;
}