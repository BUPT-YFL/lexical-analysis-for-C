#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"State.h"
std::string path;
std::fstream code;

extern char ch;
extern std::vector<GROUP> groups;
//程序行数、字符总数
extern int File_lines;
extern int File_CharNums;
//错误信息管理
	//存储错误所在的行列坐标
extern std::vector<int> Error_col;
//错误字符串
extern std::vector<std::string> Error_word;
//错误信息
extern std::vector<std::string> Error_mas;

//Token类型表
extern std::map<int, std::string> TokenType;
extern int Token_Times[TokenNum];


int main(void)
{
	std::cout << "请输入文件路径:";
	std::cin >> path;
	code.open(path, std::fstream::in);
	if (!code)
	{
		std::cout << "文件打开失败" << std::endl;
		return 0;
	}
	//开始词法分析
	code >> std::noskipws;//能够获取每个字符(回车和空格)，不设置则接受不了回车与空格
	while (code >> ch)
	{
		sol_ch();
	}
	ch = EOF;
	sol_ch();
	//输出信息
	std::cout << "Token 类别统计 (类码/类名,次数)" << std::endl;
	for (int i = 0; i < TokenNum; i++)
	{
		std::cout << "( " << i << "/" << TokenType[i] << "," << Token_Times[i] << " )" << std::endl;
	}
	std::cout << "*****Token: (字符串 , 类码/类名)*****" << std::endl;
	for (unsigned int i = 0; i < groups.size(); i++)
	{
		std::cout << "( " << groups[i].names << "," << groups[i].Types <<"/"<< TokenType[groups[i].Types]<< " )" << std::endl;
	}
	std::cout << "@@@@@@文件字符个数  文件行数@@@@@" << std::endl;
	std::cout << "File_charnum:" << File_CharNums << "  " << "File_lines:" << File_lines << std::endl;
	std::cout << "@@@@@@错误信息@@@@@" << std::endl;
	for (unsigned int i = 0; i < Error_col.size(); i++)
	{
		std::cout << "error line" << ":" << Error_col[i] + 1 << " 错误字符串 " <<Error_word[i] << " " << Error_mas[i] << std::endl;
	}
	return 0;
}
