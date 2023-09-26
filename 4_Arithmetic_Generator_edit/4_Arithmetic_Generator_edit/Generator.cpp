#include "Header_File.h"


char* Generate_Operator() // 生成运算符
{
	char* Operator = new char[2];
	char S[4] = { '+','-','x','#' };
	switch (S[rand() % 4])
	{
	case '+': strcpy(Operator, "+"); break;
	case '-': strcpy(Operator, "-"); break;
	case '*': strcpy(Operator, "*"); break;
	case '#': strcpy(Operator, "#"); break;
	default:  strcpy(Operator, "+"); break;
	}
	return Operator;
}


char* Generate_Operand() // 生成运算数 
{
	srand((unsigned)time(NULL) + rand()); // 以（系统时间+一个伪随机数）作为伪随机数发生器的起始点，避免连续出现相同题目

	extern int n; // 生成题目数量
	extern int r; // 生成题目中数字的最大值（不包含）

	int judge = rand() % 10; // 用于判断生成整数或分数，此处70%的概率生成整数
	int integer = 0, numerator = 0, denominator = 0;
	char operand[MAXSIZE] = {};
	char temp[MAXSIZE] = {};

	if (judge <= 6) // 生成整数
	{
		integer = rand() % r;
		if (integer == 0) integer++; // 运算数当中不出现0
		sprintf(operand, "%d", integer);
	}
	else // 生成分数
	{
		numerator = rand() % (r - 1); // 生成分子

		if (numerator != 0)
		{
			sprintf(operand, "%d", numerator);
			strcat(operand, "/");
		}
		while (Fraction_Compliance_Check(numerator, denominator) == ERROR)
		{
			denominator = rand() % r;
		}
		sprintf(temp, "%d", denominator);
		strcat(operand, temp);
	}
	return operand;
}


char* Generate_Equation() // 生成单个算式
{
	srand((unsigned)time(NULL) + rand());

	int parenthesis = 0; // parenthesis用于标志算式是否存在未配对的左括号，1表示存在
	int quantity_operand = rand() % 3 + 2; // 操作数个数，取值范围2、3、4
	char string[MAXSIZE] = {}; // 用于存放算式

	// 算式超过两个操作数，算式最前方有几率出现括号
	if (quantity_operand > 2)
	{
		if (rand() % 2 == 1) // 生成概率为1/2
		{
			strcat(string, "(");
			parenthesis = 1;
		}
	}

	// 依次生成数字、算符、数字
	strcat(string, Generate_Operand());
	strcat(string, Generate_Operator());
	strcat(string, Generate_Operand());

	if (quantity_operand == 2) return string; // 若此次生成的算式仅有两个操作数，则生成完毕

	// 此次生成的算式操作数个数大于2，继续生成
	else
	{
		if (parenthesis == 1) // 若存在未配对的左括号
		{
			if (rand() % 2 == 1) // 1/2的概率生成对应右括号
			{
				strcat(string, ")");
				parenthesis = 0;
			}
		}

		// 生成一个算符
		strcat(string, Generate_Operator());

		// 若此次生成的为4个操作数的算式，且此时算式中无未配对的左括号，则仍可以插入左括号，概率为1/2
		if (quantity_operand == 4 && parenthesis == 0)
		{
			if (rand() % 2 == 1)
			{
				strcat(string, "(");
				parenthesis = 1;
			}
		}

		// 生成一个数字
		strcat(string, Generate_Operand());

		// 若此次生成的为3个操作数的算式，检查是否存在未配对左括号，并结束此次生成
		if (quantity_operand == 3)
		{
			if (parenthesis == 1)
			{
				strcat(string, ")");
				parenthesis = 0;
			}
			return string;
		}

		// 若此次生成的为4个操作数的算式，生成最后的算符与数字，随后检查是否存在未配对左括号，并结束此次生成
		if (quantity_operand == 4)
		{
			strcat(string, Generate_Operator());
			strcat(string, Generate_Operand());

			if (parenthesis == 1)
			{
				strcat(string, ")");
				parenthesis = 0;
			}
			return string;
		}
	}
}


Status Generate_Answer(char result[], int y) // 计算答案并写入文件
{
	extern int count; // 用于记录算式个数

	SqStack_Operand S_operand; // 运算数栈 
	SqStack_Operator S_operator; // 运算符栈 
	Linklist_Operand operand_x1, operand_x2; // 操作数
	Node_Operand outcome; // 存放结果或中间结果
	int i = 0, j = 0;
	int Operator;
	char answer[20] = {}; // 用于存放答案 
	FILE* fp;

	InitStack_Sq_Operand(S_operand);
	InitStack_Sq_Operator(S_operator);
	fp = fopen("Answer.txt", "a");

	while (result[i] != '\0' || StackEmpty_Sq(S_operator) != OK) // 按字符依次读取
	{
		if (result[i] >= '0' && result[i] <= '9') // 若读取到数字
		{
			j = j * 10 + (result[i] - '0'); // 还原数字
			i++;
			if (result[i] > '9' || result[i] < '0') // 若下一个字符为算符，则将读取到的数字压入操作数栈
			{
				Push_SqStack_Operand(S_operand, j, 1);
				j = 0;
			}
		}
		else // 若读取到运算符
		{
			if (result[i] == ')' && Get_Top(S_operator) == '(') // 若出现一个操作数前后均有括号的情况，则去除冗余的括号
			{
				Pop_SqStack_Operator(S_operator); // 移除左括号
				i++;
				continue;
			}
			if (Rear_First_Check(result[i], S_operator) == OK) // 满足能够让后方的式子先进行运算的条件
			{
				Push_SqStack_Operator(S_operator, result[i]); // 运算符入栈 
				i++;
				continue;
			}
			if (Front_First_Check(result[i], S_operator) == OK) // 之前已读入的算式能够先进行计算
			{
				operand_x1 = Pop_SqStack_Operand(S_operand);
				operand_x2 = Pop_SqStack_Operand(S_operand);
				Operator = Pop_SqStack_Operator(S_operator)->data;
				outcome = Calculator(*operand_x1, *operand_x2, Operator); // 计算中间值

				// 若除法运算中结果出现假分数，或减法运算中出现负数，则返回-1
				if (Division_Compliance_Check(outcome, Operator) == ERROR || Subtraction_Compliance_Check(outcome, Operator) == ERROR)
				{
					fclose(fp);
					return ERROR;
				}

				Push_SqStack_Operand(S_operand, outcome.numerator, outcome.denominator); // 算式符合规范，中间结果入栈 
				continue;
			}
		}
	}
	if (outcome.numerator < 0) // 结果出现负数，返回-1
	{
		fclose(fp);
		return ERROR;
	}
	Simplify(outcome.numerator, outcome.denominator, answer); // 分式化简，并将结果传入答案字符串 
	count++;
	fprintf(fp, "%d.  %s\n", y, answer); // 将答案写入文件
	fclose(fp);
	return OK;
}


Status Generate_Formula(int question_num) // 将生成的式子读入txt文件
{
	srand((unsigned)time(NULL) + rand());
	char string[MAXSIZE] = {};
	//char* string1 = string;
	FILE* fp;
	fp = fopen("Exercises.txt", "a");
	int i = 0;

	// 用于输入进文件时插入空格，以及乘除号的格式变换
	char lpa[3] = { "( " };
	char rpa[3] = { " )" };
	char add[4] = { " + " };
	char sub[4] = { " - " };
	char div[5] = { " ÷ " };
	char mul[5] = { " × " };

	strcpy(string, Generate_Equation());
	if (Generate_Answer(string, question_num) == ERROR) // 生成的算式不符合要求，向上层函数报错
	{
		fclose(fp);
		return ERROR;
	}
	else // 算式符合要求，将其写入文件
	{
		fprintf(fp, "%d.  ", question_num);
		while (string[i] != '\0')
		{
			if (string[i] == '(')
			{
				fprintf(fp, "%s", lpa);
				i++;
				continue;
			}
			if (string[i] == ')')
			{
				fprintf(fp, "%s", rpa);
				i++;
				continue;
			}
			if (string[i] == '+')
			{
				fprintf(fp, "%s", add);
				i++;
				continue;
			}
			if (string[i] == '-')
			{
				fprintf(fp, "%s", sub);
				i++;
				continue;
			}
			// 乘除号在写入文件时需要进行修改
			if (string[i] == '#')
			{
				fprintf(fp, "%s", div);
				i++;
				continue;
			}
			if (string[i] == '*')
			{
				fprintf(fp, "%s", mul);
				i++;
				continue;
			}
			fprintf(fp, "%c", string[i]);
			i++;
		}
		fprintf(fp, " = %c", '\n');
		fclose(fp);
		return OK;
	}
}