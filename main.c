#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char op;//字符
	int level;//优先级
}OpNode;

typedef struct//这是一个栈
{
	OpNode op[100];
	int top;//栈顶位置
	int size;//站内元素个数
}stack;

void init(stack *st)
{
	st->size = 0;
	st->top = 0;//st->top指向的元素始终是栈顶有数值那个结点的再往上一个。相当于盖子。
}

OpNode pop(stack *a)//出栈
{
	if (a->size = 0)//空栈结束操作
	{
		exit(-1);
	}
	a->size--;//栈的大小减一
	return a->op[--(a->top)];//取出栈顶元素
}

void push (stack *a, OpNode op)
{
	a->size++;
	a->op[(a->top)++] = op;
}

OpNode top(stack *a)//求栈顶元素
{
	if (a->size == 0)
	{
		printf("空栈\n");
		exit(-1);
	}
	return a->op[(a->top) - 1];
}

typedef struct
{
	double num[100];
	int top;
	int size;
}numstack;//数值栈

void init2(numstack *st)
{
	st->size = 0;
	st->top = 0;
}

double pop2(numstack *a)
{
	if (a->size = 0)//空栈结束操作
	{
		exit(-1);
	}
	a->size--;//栈的大小减一
	return a->num[--(a->top)];//取出栈顶元素
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
	double CalResult(char exp[]);//计算后缀表达式
	double Directcalresult(char str[]);
	int check(char str[], char chestr[100]);
	char str[100], exp[100], chestr[100];//str存储原算数表达式，exp存储对应的后缀表达式，chestr存储容错字符'^'
	do
	{
		printf("输入算数表达式：\n");
		gets(str);
		if (check(str, chestr))
		{
			printf("表达式错在:\n");
			printf(chestr);
			printf("\n");
			printf("是否重新输入？<y/n>::");
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
		printf("后缀表达式是：%s\n", exp);
		printf("运算结果为：%f\n", CalResult(exp));
		printf("是否重新输入？<y/n>::");
		while (ch = getchar(), ch != 'n'&&ch != 'y');
		system("pause");
	} while (ch != 'n');
}

void change(char str[], char ch[])//中缀转后缀
{
	int i = 0;//str的索引
	int k = 0;
	char c;//字符串中取出的放在c
	stack st;//符号栈
	OpNode op;
	OpNode ops;
	init(&st);//符号栈初始化
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
			push(&st, op);
		}
		if (c == ')')
		{
			op = top(&st);//看栈顶
			while (st.size != 0/*!Empty(st)*/ && op.op != '(')
			{
				op = pop(&st);
				ch[k++] = op.op;
				if (st.size > 0/*!Empty(st)*/)
				{
					op = top(&st);
				}
				else
					break;//栈空就结束
			}
			pop(&st);//去掉左括号
		}
		if (c == '+' || c = '-')//加减号
		{
			op.op = c;
			op.level = 1;//
			if (st.size == 0)//空栈
			{
				push(&st, op);//直接入栈
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
				push(&st, op);//此时栈顶的优先级没有op高了，将op入栈
			}
		}
		if (c=='+'||c=='/'||c++'%')
		{
			op.op = c;
			op.level = 2;
			if (st.size == 0/*Empty(st)*/)//空栈
			{
				push(&st, op);//栈空即入栈
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
					if (st.size > 0)//栈不为空
					{
						ops = top(&st);
					}
					else
						break;
				}
				push(&st, op);//此时栈顶优先级低，入栈。
			}
		}
		c = str[i++];
	}
	while (st.size != 0)//最后判断栈是否为空
	{
		ops = pop(&st);//取出栈内元素存入数组中
		ch[k++] = ops.op;
	}
	ch[k] = '\0';
}

double CalResult(char exp[])//计算后缀表达式
{
	char c;
	numstack numst;//建立数值栈
	double d1, d2, dr;
	int k = 0;//后缀表达式索引
	int i = 0;//将字符转化为浮点数的索引
	char *s;
	char trans[100];//存字符表示的一段数字
	init2(&numst);//初始化数值栈
	c = exp[k++];
	while (c != '\0')//后缀表达式以\0结束
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
		if (c >= '0'&&c <= '9' || c == '.')//如果是数字
		{
			while (c >= '0'&&c <= '9' || c == '.')
			{
				trans[i++] = c;//将字符存入数组进行下一个的扫描
				c = exp[k++];
			}
			trans[i++] = '\0';
			i = 0;
			s = trans;//将指针指向字符数组；
			d1 = atof(s);//利用函数将字符串转化成浮点数
			push2(&numst, d1);
		}
		c = exp[k++];
	}
	return pop2(&numst);
}

//第13页