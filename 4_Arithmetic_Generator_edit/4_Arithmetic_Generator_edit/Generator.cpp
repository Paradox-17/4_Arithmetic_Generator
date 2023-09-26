#include "Header_File.h"


char* Generate_Operator() // ���������
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


char* Generate_Operand() // ���������� 
{
	srand((unsigned)time(NULL) + rand()); // �ԣ�ϵͳʱ��+һ��α���������Ϊα���������������ʼ�㣬��������������ͬ��Ŀ

	extern int n; // ������Ŀ����
	extern int r; // ������Ŀ�����ֵ����ֵ����������

	int judge = rand() % 10; // �����ж�����������������˴�70%�ĸ�����������
	int integer = 0, numerator = 0, denominator = 0;
	char operand[MAXSIZE] = {};
	char temp[MAXSIZE] = {};

	if (judge <= 6) // ��������
	{
		integer = rand() % r;
		if (integer == 0) integer++; // ���������в�����0
		sprintf(operand, "%d", integer);
	}
	else // ���ɷ���
	{
		numerator = rand() % (r - 1); // ���ɷ���

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


char* Generate_Equation() // ���ɵ�����ʽ
{
	srand((unsigned)time(NULL) + rand());

	int parenthesis = 0; // parenthesis���ڱ�־��ʽ�Ƿ����δ��Ե������ţ�1��ʾ����
	int quantity_operand = rand() % 3 + 2; // ������������ȡֵ��Χ2��3��4
	char string[MAXSIZE] = {}; // ���ڴ����ʽ

	// ��ʽ������������������ʽ��ǰ���м��ʳ�������
	if (quantity_operand > 2)
	{
		if (rand() % 2 == 1) // ���ɸ���Ϊ1/2
		{
			strcat(string, "(");
			parenthesis = 1;
		}
	}

	// �����������֡����������
	strcat(string, Generate_Operand());
	strcat(string, Generate_Operator());
	strcat(string, Generate_Operand());

	if (quantity_operand == 2) return string; // ���˴����ɵ���ʽ�������������������������

	// �˴����ɵ���ʽ��������������2����������
	else
	{
		if (parenthesis == 1) // ������δ��Ե�������
		{
			if (rand() % 2 == 1) // 1/2�ĸ������ɶ�Ӧ������
			{
				strcat(string, ")");
				parenthesis = 0;
			}
		}

		// ����һ�����
		strcat(string, Generate_Operator());

		// ���˴����ɵ�Ϊ4������������ʽ���Ҵ�ʱ��ʽ����δ��Ե������ţ����Կ��Բ��������ţ�����Ϊ1/2
		if (quantity_operand == 4 && parenthesis == 0)
		{
			if (rand() % 2 == 1)
			{
				strcat(string, "(");
				parenthesis = 1;
			}
		}

		// ����һ������
		strcat(string, Generate_Operand());

		// ���˴����ɵ�Ϊ3������������ʽ������Ƿ����δ��������ţ��������˴�����
		if (quantity_operand == 3)
		{
			if (parenthesis == 1)
			{
				strcat(string, ")");
				parenthesis = 0;
			}
			return string;
		}

		// ���˴����ɵ�Ϊ4������������ʽ������������������֣�������Ƿ����δ��������ţ��������˴�����
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


Status Generate_Answer(char result[], int y) // ����𰸲�д���ļ�
{
	extern int count; // ���ڼ�¼��ʽ����

	SqStack_Operand S_operand; // ������ջ 
	SqStack_Operator S_operator; // �����ջ 
	Linklist_Operand operand_x1, operand_x2; // ������
	Node_Operand outcome; // ��Ž�����м���
	int i = 0, j = 0;
	int Operator;
	char answer[20] = {}; // ���ڴ�Ŵ� 
	FILE* fp;

	InitStack_Sq_Operand(S_operand);
	InitStack_Sq_Operator(S_operator);
	fp = fopen("Answer.txt", "a");

	while (result[i] != '\0' || StackEmpty_Sq(S_operator) != OK) // ���ַ����ζ�ȡ
	{
		if (result[i] >= '0' && result[i] <= '9') // ����ȡ������
		{
			j = j * 10 + (result[i] - '0'); // ��ԭ����
			i++;
			if (result[i] > '9' || result[i] < '0') // ����һ���ַ�Ϊ������򽫶�ȡ��������ѹ�������ջ
			{
				Push_SqStack_Operand(S_operand, j, 1);
				j = 0;
			}
		}
		else // ����ȡ�������
		{
			if (result[i] == ')' && Get_Top(S_operator) == '(') // ������һ��������ǰ��������ŵ��������ȥ�����������
			{
				Pop_SqStack_Operator(S_operator); // �Ƴ�������
				i++;
				continue;
			}
			if (Rear_First_Check(result[i], S_operator) == OK) // �����ܹ��ú󷽵�ʽ���Ƚ������������
			{
				Push_SqStack_Operator(S_operator, result[i]); // �������ջ 
				i++;
				continue;
			}
			if (Front_First_Check(result[i], S_operator) == OK) // ֮ǰ�Ѷ������ʽ�ܹ��Ƚ��м���
			{
				operand_x1 = Pop_SqStack_Operand(S_operand);
				operand_x2 = Pop_SqStack_Operand(S_operand);
				Operator = Pop_SqStack_Operator(S_operator)->data;
				outcome = Calculator(*operand_x1, *operand_x2, Operator); // �����м�ֵ

				// �����������н�����ּٷ���������������г��ָ������򷵻�-1
				if (Division_Compliance_Check(outcome, Operator) == ERROR || Subtraction_Compliance_Check(outcome, Operator) == ERROR)
				{
					fclose(fp);
					return ERROR;
				}

				Push_SqStack_Operand(S_operand, outcome.numerator, outcome.denominator); // ��ʽ���Ϲ淶���м�����ջ 
				continue;
			}
		}
	}
	if (outcome.numerator < 0) // ������ָ���������-1
	{
		fclose(fp);
		return ERROR;
	}
	Simplify(outcome.numerator, outcome.denominator, answer); // ��ʽ���򣬲������������ַ��� 
	count++;
	fprintf(fp, "%d.  %s\n", y, answer); // ����д���ļ�
	fclose(fp);
	return OK;
}


Status Generate_Formula(int question_num) // �����ɵ�ʽ�Ӷ���txt�ļ�
{
	srand((unsigned)time(NULL) + rand());
	char string[MAXSIZE] = {};
	//char* string1 = string;
	FILE* fp;
	fp = fopen("Exercises.txt", "a");
	int i = 0;

	// ����������ļ�ʱ����ո��Լ��˳��ŵĸ�ʽ�任
	char lpa[3] = { "( " };
	char rpa[3] = { " )" };
	char add[4] = { " + " };
	char sub[4] = { " - " };
	char div[5] = { " �� " };
	char mul[5] = { " �� " };

	strcpy(string, Generate_Equation());
	if (Generate_Answer(string, question_num) == ERROR) // ���ɵ���ʽ������Ҫ�����ϲ㺯������
	{
		fclose(fp);
		return ERROR;
	}
	else // ��ʽ����Ҫ�󣬽���д���ļ�
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
			// �˳�����д���ļ�ʱ��Ҫ�����޸�
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