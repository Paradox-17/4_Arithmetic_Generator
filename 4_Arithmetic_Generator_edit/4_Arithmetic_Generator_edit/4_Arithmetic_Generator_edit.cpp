#include "Header_File.h"

// 全局变量
int n;		              // 生成题目数量
int r;		              // 生成题目中数字的最大值（不包含）
int count = 0;            // 用于记录算式个数

// 主函数
int main(int argc, char* argv[])
{
	char* line;
	int question_num = 1; // 题号，初值为1 

	if (argc < 3) // 参数输入异常
	{
		printf("需要使用cmd运行，格式示例：main.exe -n 10 -r 10\n");
		return 0;
	}

	remove("Exercise.txt");
	remove("Answer.txt");
	srand((unsigned)time(NULL) + rand());

	// 辨别两种命令行参数输入格式
	if (strcmp(argv[1], "-n") == 0 && strcmp(argv[3], "-r") == 0)
	{
		n = atoi(argv[2]); // 将字符串转换为整型变量
		r = atoi(argv[4]);
	}
	if (strcmp(argv[1], "-r") == 0 && strcmp(argv[3], "-n") == 0)
	{
		n = atoi(argv[4]);
		r = atoi(argv[2]);
	}

	while (n > 0)
	{
		//line = Generate_Formula(question_num);
		//if (atoi(line) < 0) continue;
		if (Generate_Formula(question_num) == ERROR) continue;
		question_num++;
		n--;
	}

	return 0;
}
