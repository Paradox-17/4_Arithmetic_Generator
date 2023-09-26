#include "Header_File.h"


int gcd(int x, int y) // ���������Լ��
{
	return y == 0 ? x : gcd(y, x % y);
}


Node_Operand Calculator(Node_Operand x1, Node_Operand x2, int Operator) // ʵ���������ļ���
{
	Node_Operand result;

	switch (Operator)
	{
	case'+':
		result.numerator = x2.numerator * x1.denominator + x2.denominator * x1.numerator;
		result.denominator = x1.denominator * x2.denominator;
		break;
	case'-':
		result.numerator = x2.numerator * x1.denominator - x2.denominator * x1.numerator;
		result.denominator = x1.denominator * x2.denominator;
		break;
	case'*':
		result.numerator = x2.numerator * x1.numerator;
		result.denominator = x1.denominator * x2.denominator;
		break;
	case'#':
		result.numerator = x2.numerator * x1.denominator;
		result.denominator = x2.denominator * x1.numerator;
		break;
	case'/':   // �ֺ���������������ͬ
		result.numerator = x2.numerator * x1.denominator;
		result.denominator = x2.denominator * x1.numerator;
		break;

	default:break;
	}
	return result;
}


void Simplify(int numerator, int denominator, char string[]) // �������򣬼ٷ���ת��Ϊ������
{
	int integer, remainder, great_commom_divisor;
	char temp_string[30] = {};

	// ����С�ڷ�ĸ������Լ��
	if (numerator < denominator)
	{
		// ���ӷ�ĸͬ�����Լ��
		great_commom_divisor = gcd(numerator, denominator);
		integer = numerator / great_commom_divisor;
		remainder = denominator / great_commom_divisor;

		// ���д��string
		itoa(integer, string, 10); // ��int���͵���ֵ��10���Ƶ���ʽת��Ϊ�ַ������������string��
		strcat(string, "/");
		itoa(remainder, temp_string, 10);
		strcat(string, temp_string);
	}

	// ���ӵ��ڷ�ĸ�����Ϊ1
	else if (numerator == denominator)
	{
		// integer = numerator / denominator;
		integer = 1;
		itoa(integer, string, 10);
	}

	// ���Ӵ��ڷ�ĸ����Ҫ����
	else
	{
		if (numerator % denominator == 0) // ������������ĸ
		{
			integer = numerator / denominator;
			itoa(integer, string, 10);
		}
		else // ���Ӳ���������ĸ
		{
			integer = numerator / denominator; // ���ӳ��Է�ĸ���̣����������������
			remainder = numerator - integer * denominator; // ���ӳ��Է�ĸ������
			great_commom_divisor = gcd(numerator, denominator); // ���ӷ�ĸ�����Լ��
			itoa(integer, string, 10);
			strcat(string, "'"); // �ٷ����Դ���������չʾ
			sprintf(temp_string, "%d", remainder / great_commom_divisor); // ����������С��Լ�����������ķ���
			strcat(string, temp_string);
			strcat(string, "/");
			sprintf(temp_string, "%d", denominator / great_commom_divisor); // ԭ��ĸ������С��Լ�����������ķ�ĸ
			strcat(string, temp_string);
		}
	}

}