#include "Header_File.h"


Status InitStack_Sq_Operand(SqStack_Operand& S) // 运算数栈初始化
{
	S.elem = (Linklist_Operand)malloc(100 * sizeof(Node_Operand));
	S.top = 0;
	S.length = 0;
	return OK;
}

Status InitStack_Sq_Operator(SqStack_Operator& S) // 运算符栈初始化
{
	S.elem = (Linklist_Operator)malloc(100 * sizeof(Node_Operator));
	S.top = 0;
	S.length = 0;
	return OK;
}


Status Push_SqStack_Operand(SqStack_Operand& S, int a, int b) // 运算数入栈
{

	Linklist_Operand p = (Linklist_Operand)malloc(sizeof(Node_Operand));
	p->numerator = a;
	p->denominator = b;

	if (S.length == 0) // 空栈
	{
		p->next = NULL;
		S.elem[S.top] = *p;
	}
	else // 栈非空
	{
		p->next = &(S.elem[S.top++]);
		S.elem[S.top] = *p;
	}
	S.length++;

	return OK;
}

Status Push_SqStack_Operator(SqStack_Operator& S, int a) // 运算符入栈
{
	Linklist_Operator p = (Linklist_Operator)malloc(sizeof(Node_Operator));
	p->data = a;

	if (S.length == 0) // 空栈
	{
		p->next = NULL;
		S.elem[S.top] = *p;
	}
	else // 栈非空
	{
		p->next = &(S.elem[S.top++]);
		S.elem[S.top] = *p;
	}
	S.length++;

	return OK;
}


Linklist_Operand Pop_SqStack_Operand(SqStack_Operand& S) // 运算数出栈
{
	Linklist_Operand p;
	if (S.length != 1) p = &S.elem[S.top--];
	else  p = &S.elem[S.top];
	S.length--;
	return p;
}

Linklist_Operator Pop_SqStack_Operator(SqStack_Operator& S) // 运算符出栈
{
	Linklist_Operator p;
	if (S.length != 1) p = &S.elem[S.top--];
	else  p = &S.elem[S.top];
	S.length--;
	return p;
}


Status Get_Top(SqStack_Operator S) // 取栈顶运算符
{
	Linklist_Operator p;
	if (S.length == 0) return ERROR;
	p = &S.elem[S.top];
	return p->data;
}


Status StackEmpty_Sq(SqStack_Operator S) // 运算符栈判空
{
	if (S.length == 0) return OK;
	else return ERROR;
}