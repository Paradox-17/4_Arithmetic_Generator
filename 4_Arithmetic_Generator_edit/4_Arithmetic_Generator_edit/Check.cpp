#include "Header_File.h"


int Priority_Judgement(char Operator) // �жϲ��������ȼ�
{
	switch (Operator)
	{
	case '(':       // ����
		return 4;
	case '/':       // �ֺ�
		return 3;
	case '*':       // �˺�
	case '#':       // ���� 
		return 2;
	case '+':       // �Ӻ�
	case '-':       // ����
		return 1;
	default:
		return 0;
	}
}


Status Fraction_Compliance_Check(int numerator, int denominator) // ��������Ƿ�Ϲ�
{
	if (numerator >= denominator || denominator == 0) return ERROR;
	else return OK;
}


Status Rear_First_Check(char a, SqStack_Operator S) // �����ж��ܷ��ú󷽵�ʽ���Ƚ�������
{
	if ((Get_Top(S) == '(' && a != ')') || (StackEmpty_Sq(S) == OK) || (Priority_Judgement(a) > Priority_Judgement(Get_Top(S)))) return OK;
	else return ERROR;
}


Status Front_First_Check(char a, SqStack_Operator S) // �����ж��ܷ���ǰ����ʽ���Ƚ��м���
{
	if ((a == '\0' && StackEmpty_Sq(S) != OK) || (Priority_Judgement(a) <= Priority_Judgement(Get_Top(S))) || a == ')') return OK;
	else return ERROR;
}


Status Division_Compliance_Check(Node_Operand outcome, int Operator) // ��������Ϲ��Լ��
{
	if (((double)outcome.numerator / (double)outcome.denominator > 1) && (Operator == '#')) return ERROR;
	else return OK;
}


Status Subtraction_Compliance_Check(Node_Operand outcome, int Operator) // ��������Ϲ��Լ��
{
	if (outcome.numerator < 0 && Operator == '-') return ERROR;
	else return OK;
}