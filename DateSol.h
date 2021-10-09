#pragma once
#include<string>
#include<vector>
#include<limits>
#include<map>
//分析出的一个word符号的结构体
typedef struct group
{
	std::string names;
	int Types;
} GROUP;


bool MidSearch_KeyWord(std::string tar, std::vector<std::string>& KeyWordPool);
void Add_Word(int Type);
int GetIntBase(std::string num);//获取该数的进制表示
int IsBaseInt(std::string num, int base, std::string& Valid);//2 8 16进制判断
int Is10Int(std::string num, std::string& Valid);//10进制判断
int GetUIntBase(std::string num);//获取该数的进制表示
int IsBaseUInt(std::string num, int base, std::string& Valid);
int Is10UInt(std::string num, std::string& Valid);
int GetLLongBase(std::string num);//获取该数的进制表示
int IsBaseLLong(std::string num, int base, std::string& Valid);//不包含10进制判断
int Is10LLong(std::string num, std::string& Valid);
int GetULLongBase(std::string num);//获取该数的进制表示
int IsBaseULLong(std::string num, int base, std::string& Valid);//不包含10进制判断
int Is10ULLong(std::string num, std::string& Valid);

#define MAX_LEN_SIGN_WORD 247
#define TokenNum 12
//记号属性
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


