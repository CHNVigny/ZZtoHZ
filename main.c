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
	int top;//？？？？？？？（有可能是栈顶位置）
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
			if
		}
	}

}