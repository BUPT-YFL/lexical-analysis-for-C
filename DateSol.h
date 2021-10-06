#pragma once
#include<string>
#include<vector>
#include<limits>
#include<map>
//��������һ��word���ŵĽṹ��
typedef struct group
{
	std::string names;
	int Types;
} GROUP;


bool MidSearch_KeyWord(std::string tar, std::vector<std::string>& KeyWordPool);
void Add_Word(int Type);
int GetIntBase(std::string num);//��ȡ�����Ľ��Ʊ�ʾ
int IsBaseInt(std::string num, int base, std::string& Valid);//2 8 16�����ж�
int Is10Int(std::string num, std::string& Valid);//10�����ж�
int GetUIntBase(std::string num);//��ȡ�����Ľ��Ʊ�ʾ
int IsBaseUInt(std::string num, int base, std::string& Valid);
int Is10UInt(std::string num, std::string& Valid);
int GetLLongBase(std::string num);//��ȡ�����Ľ��Ʊ�ʾ
int IsBaseLLong(std::string num, int base, std::string& Valid);//������10�����ж�
int Is10LLong(std::string num, std::string& Valid);
int GetULLongBase(std::string num);//��ȡ�����Ľ��Ʊ�ʾ
int IsBaseULLong(std::string num, int base, std::string& Valid);//������10�����ж�
int Is10ULLong(std::string num, std::string& Valid);

#define TokenNum 12
//�Ǻ�����
#define SIGN_WORD 0
#define KEY_WORD 1
#define OP_WORD 2
#define BOUND_WORD 3
#define CONST_STR 4

#define CONST_CH 5
#define NUM_INT 6
#define NUM_UINT 7
#define NUM_LLONG 8
#define NUM_ULLONG 9
#define NUM_FLOAT 10
#define NUM_DOUBLE 11


