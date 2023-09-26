#include "Header_File.h"


int Priority_Judgement(char Operator) // 判断操作符优先级
{
	switch (Operator)
	{
	case '(':       // 括号
		return 4;
	case '/':       // 分号
		return 3;
	case '*':       // 乘号
	case '#':       // 除号 
		return 2;
	case '+':       // 加号
	case '-':       // 减号
		return 1;
	default:
		return 0;
	}
}


Status Fraction_Compliance_Check(int numerator, int denominator) // 检验分数是否合规
{
	if (numerator >= denominator || denominator == 0) return ERROR;
	else return OK;
}


Status Rear_First_Check(char a, SqStack_Operator S) // 用于判断能否让后方的式子先进行运算
{
	if ((Get_Top(S) == '(' && a != ')') || (StackEmpty_Sq(S) == OK) || (Priority_Judgement(a) > Priority_Judgement(Get_Top(S)))) return OK;
	else return ERROR;
}


Status Front_First_Check(char a, SqStack_Operator S) // 用于判断能否让前方的式子先进行计算
{
	if ((a == '\0' && StackEmpty_Sq(S) != OK) || (Priority_Judgement(a) <= Priority_Judgement(Get_Top(S))) || a == ')') return OK;
	else return ERROR;
}


Status Division_Compliance_Check(Node_Operand outcome, int Operator) // 除法计算合规性检查
{
	if (((double)outcome.numerator / (double)outcome.denominator > 1) && (Operator == '#')) return ERROR;
	else return OK;
}


Status Subtraction_Compliance_Check(Node_Operand outcome, int Operator) // 除法计算合规性检查
{
	if (outcome.numerator < 0 && Operator == '-') return ERROR;
	else return OK;
}