#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_NONSTDC_NO_DEPRECATE


// �⺯����
#include <io.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// �궨��
#define OK 1
#define ERROR 0
#define MINSIZE 256
#define MAXSIZE 1024


// �Զ������ݽṹ
typedef int Status; // ״̬����

typedef  struct  Node_Operand {
	int  numerator;    // ����
	int  denominator;  // ��ĸ
	struct Node_Operand* next;
}Node_Operand, * Linklist_Operand; // ���������

typedef struct Node_Operator {
	int data;
	struct Node_Operator* next;
}Node_Operator, * Linklist_Operator; // ��������

typedef struct {
	Node_Operand* elem;
	int top;
	int length;
}SqStack_Operand; // ������ջ

typedef struct {
	Node_Operator* elem;
	int top;
	int length;
}SqStack_Operator; // �����ջ


// �ӿ��б�

// ˳��ջ�ӿ�
Status InitStack_Sq_Operand(SqStack_Operand& S); // ������ջ��ʼ��
Status InitStack_Sq_Operator(SqStack_Operator& S); // �����ջ��ʼ��
Status Push_SqStack_Operand(SqStack_Operand& S, int a, int b); // ��������ջ
Status Push_SqStack_Operator(SqStack_Operator& S, int a); // �������ջ
Linklist_Operand Pop_SqStack_Operand(SqStack_Operand& S); // ��������ջ
Linklist_Operator Pop_SqStack_Operator(SqStack_Operator& S); // �������ջ
Status Get_Top(SqStack_Operator S); // ȡջ�������
Status StackEmpty_Sq(SqStack_Operator S); // �����ջ�п�

// �������������ӿ�
int gcd(int x, int y); // ���������Լ��
Node_Operand Calculator(Node_Operand x1, Node_Operand x2, int Operator); // ʵ���������ļ���
void Simplify(int numerator, int denominator, char string[]); // �������򣬼ٷ���ת��Ϊ������

// �жϽӿ�
int Priority_Judgement(char Operator); // �жϲ��������ȼ�
Status Fraction_Compliance_Check(int numerator, int denominator); // ��������Ƿ�Ϲ�
Status Rear_First_Check(char a, SqStack_Operator S); // �����ж��ܷ��ú󷽵�ʽ���Ƚ�������
Status Front_First_Check(char a, SqStack_Operator S); // �����ж��ܷ���ǰ����ʽ���Ƚ��м���
Status Division_Compliance_Check(Node_Operand outcome, int Operator); // ��������Ϲ��Լ��
Status Subtraction_Compliance_Check(Node_Operand outcome, int Operator); // ��������Ϲ��Լ��

// ��Ҫ�����ӿ�
char* Generate_Operator(); // ���������
char* Generate_Operand(); // ���������� 
char* Generate_Equation(); // ���ɵ�����ʽ
Status Generate_Answer(char result[], int y); // ����𰸲�д���ļ�
Status Generate_Formula(int question_num); // �����ɵ�ʽ�Ӷ���txt�ļ�
