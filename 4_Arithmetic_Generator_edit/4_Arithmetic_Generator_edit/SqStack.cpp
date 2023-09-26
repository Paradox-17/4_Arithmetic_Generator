#include "Header_File.h"


Status InitStack_Sq_Operand(SqStack_Operand& S) // ������ջ��ʼ��
{
	S.elem = (Linklist_Operand)malloc(100 * sizeof(Node_Operand));
	S.top = 0;
	S.length = 0;
	return OK;
}

Status InitStack_Sq_Operator(SqStack_Operator& S) // �����ջ��ʼ��
{
	S.elem = (Linklist_Operator)malloc(100 * sizeof(Node_Operator));
	S.top = 0;
	S.length = 0;
	return OK;
}


Status Push_SqStack_Operand(SqStack_Operand& S, int a, int b) // ��������ջ
{

	Linklist_Operand p = (Linklist_Operand)malloc(sizeof(Node_Operand));
	p->numerator = a;
	p->denominator = b;

	if (S.length == 0) // ��ջ
	{
		p->next = NULL;
		S.elem[S.top] = *p;
	}
	else // ջ�ǿ�
	{
		p->next = &(S.elem[S.top++]);
		S.elem[S.top] = *p;
	}
	S.length++;

	return OK;
}

Status Push_SqStack_Operator(SqStack_Operator& S, int a) // �������ջ
{
	Linklist_Operator p = (Linklist_Operator)malloc(sizeof(Node_Operator));
	p->data = a;

	if (S.length == 0) // ��ջ
	{
		p->next = NULL;
		S.elem[S.top] = *p;
	}
	else // ջ�ǿ�
	{
		p->next = &(S.elem[S.top++]);
		S.elem[S.top] = *p;
	}
	S.length++;

	return OK;
}


Linklist_Operand Pop_SqStack_Operand(SqStack_Operand& S) // ��������ջ
{
	Linklist_Operand p;
	if (S.length != 1) p = &S.elem[S.top--];
	else  p = &S.elem[S.top];
	S.length--;
	return p;
}

Linklist_Operator Pop_SqStack_Operator(SqStack_Operator& S) // �������ջ
{
	Linklist_Operator p;
	if (S.length != 1) p = &S.elem[S.top--];
	else  p = &S.elem[S.top];
	S.length--;
	return p;
}


Status Get_Top(SqStack_Operator S) // ȡջ�������
{
	Linklist_Operator p;
	if (S.length == 0) return ERROR;
	p = &S.elem[S.top];
	return p->data;
}


Status StackEmpty_Sq(SqStack_Operator S) // �����ջ�п�
{
	if (S.length == 0) return OK;
	else return ERROR;
}