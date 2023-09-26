#include "Header_File.h"


int gcd(int x, int y) // 求两数最大公约数
{
	return y == 0 ? x : gcd(y, x % y);
}


Node_Operand Calculator(Node_Operand x1, Node_Operand x2, int Operator) // 实现两个数的计算
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
	case'/':   // 分号与除号运算规则相同
		result.numerator = x2.numerator * x1.denominator;
		result.denominator = x2.denominator * x1.numerator;
		break;

	default:break;
	}
	return result;
}


void Simplify(int numerator, int denominator, char string[]) // 分数化简，假分数转化为带分数
{
	int integer, remainder, great_commom_divisor;
	char temp_string[30] = {};

	// 分子小于分母，进行约分
	if (numerator < denominator)
	{
		// 分子分母同除最大公约数
		great_commom_divisor = gcd(numerator, denominator);
		integer = numerator / great_commom_divisor;
		remainder = denominator / great_commom_divisor;

		// 结果写入string
		itoa(integer, string, 10); // 将int类型的数值以10进制的形式转化为字符串，并存放在string中
		strcat(string, "/");
		itoa(remainder, temp_string, 10);
		strcat(string, temp_string);
	}

	// 分子等于分母，结果为1
	else if (numerator == denominator)
	{
		// integer = numerator / denominator;
		integer = 1;
		itoa(integer, string, 10);
	}

	// 分子大于分母，需要化简
	else
	{
		if (numerator % denominator == 0) // 分子能整除分母
		{
			integer = numerator / denominator;
			itoa(integer, string, 10);
		}
		else // 分子不能整除分母
		{
			integer = numerator / denominator; // 分子除以分母的商，即结果的整数部分
			remainder = numerator - integer * denominator; // 分子除以分母的余数
			great_commom_divisor = gcd(numerator, denominator); // 分子分母的最大公约数
			itoa(integer, string, 10);
			strcat(string, "'"); // 假分数以带分数进行展示
			sprintf(temp_string, "%d", remainder / great_commom_divisor); // 余数除以最小公约数，即化简后的分子
			strcat(string, temp_string);
			strcat(string, "/");
			sprintf(temp_string, "%d", denominator / great_commom_divisor); // 原分母除以最小公约数，即化简后的分母
			strcat(string, temp_string);
		}
	}

}