#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_NONSTDC_NO_DEPRECATE


// 库函数集
#include <io.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 宏定义
#define OK 1
#define ERROR 0
#define MINSIZE 256
#define MAXSIZE 1024


// 自定义数据结构
typedef int Status; // 状态函数

typedef  struct  Node_Operand {
	int  numerator;    // 分子
	int  denominator;  // 分母
	struct Node_Operand* next;
}Node_Operand, * Linklist_Operand; // 运算数结点

typedef struct Node_Operator {
	int data;
	struct Node_Operator* next;
}Node_Operator, * Linklist_Operator; // 运算符结点

typedef struct {
	Node_Operand* elem;
	int top;
	int length;
}SqStack_Operand; // 运算数栈

typedef struct {
	Node_Operator* elem;
	int top;
	int length;
}SqStack_Operator; // 运算符栈


// 接口列表

// 顺序栈接口
Status InitStack_Sq_Operand(SqStack_Operand& S); // 运算数栈初始化
Status InitStack_Sq_Operator(SqStack_Operator& S); // 运算符栈初始化
Status Push_SqStack_Operand(SqStack_Operand& S, int a, int b); // 运算数入栈
Status Push_SqStack_Operator(SqStack_Operator& S, int a); // 运算符入栈
Linklist_Operand Pop_SqStack_Operand(SqStack_Operand& S); // 运算数出栈
Linklist_Operator Pop_SqStack_Operator(SqStack_Operator& S); // 运算符出栈
Status Get_Top(SqStack_Operator S); // 取栈顶运算符
Status StackEmpty_Sq(SqStack_Operator S); // 运算符栈判空

// 基本算术操作接口
int gcd(int x, int y); // 求两数最大公约数
Node_Operand Calculator(Node_Operand x1, Node_Operand x2, int Operator); // 实现两个数的计算
void Simplify(int numerator, int denominator, char string[]); // 分数化简，假分数转化为带分数

// 判断接口
int Priority_Judgement(char Operator); // 判断操作符优先级
Status Fraction_Compliance_Check(int numerator, int denominator); // 检验分数是否合规
Status Rear_First_Check(char a, SqStack_Operator S); // 用于判断能否让后方的式子先进行运算
Status Front_First_Check(char a, SqStack_Operator S); // 用于判断能否让前方的式子先进行计算
Status Division_Compliance_Check(Node_Operand outcome, int Operator); // 除法计算合规性检查
Status Subtraction_Compliance_Check(Node_Operand outcome, int Operator); // 除法计算合规性检查

// 主要操作接口
char* Generate_Operator(); // 生成运算符
char* Generate_Operand(); // 生成运算数 
char* Generate_Equation(); // 生成单个算式
Status Generate_Answer(char result[], int y); // 计算答案并写入文件
Status Generate_Formula(int question_num); // 将生成的式子读入txt文件
