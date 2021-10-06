#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"State.h"
std::string path;
std::fstream code;

extern char ch;
extern std::vector<GROUP> groups;
//�����������ַ�����
extern int File_lines;
extern int File_CharNums;
//������Ϣ����
	//�洢�������ڵ���������
extern std::vector<int> Error_col;
//�����ַ���
extern std::vector<std::string> Error_word;
//������Ϣ
extern std::vector<std::string> Error_mas;

//Token���ͱ�
extern std::map<int, std::string> TokenType;
extern int Token_Times[TokenNum];


int main(void)
{
	std::cout << "�������ļ�·��:";
	std::cin >> path;
	code.open(path, std::fstream::in);
	if (!code)
	{
		std::cout << "�ļ���ʧ��" << std::endl;
		return 0;
	}
	//��ʼ�ʷ�����
	code >> std::noskipws;//�ܹ���ȡÿ���ַ�(�س��Ϳո�)������������ܲ��˻س���ո�
	while (code >> ch)
	{
		sol_ch();
	}
	ch = EOF;
	sol_ch();
	//�����Ϣ
	std::cout << "Token ���ͳ�� (����/����,����)" << std::endl;
	for (int i = 0; i < TokenNum; i++)
	{
		std::cout << "( " << i << "/" << TokenType[i] << "," << Token_Times[i] << " )" << std::endl;
	}
	std::cout << "*****Token: (�ַ��� , ����/����)*****" << std::endl;
	for (unsigned int i = 0; i < groups.size(); i++)
	{
		std::cout << "( " << groups[i].names << "," << groups[i].Types <<"/"<< TokenType[groups[i].Types]<< " )" << std::endl;
	}
	std::cout << "@@@@@@�ļ��ַ�����  �ļ�����@@@@@" << std::endl;
	std::cout << "File_charnum:" << File_CharNums << "  " << "File_lines:" << File_lines << std::endl;
	std::cout << "@@@@@@������Ϣ@@@@@" << std::endl;
	for (unsigned int i = 0; i < Error_col.size(); i++)
	{
		std::cout << "error line" << ":" << Error_col[i] + 1 << " �����ַ��� " <<Error_word[i] << " " << Error_mas[i] << std::endl;
	}
	return 0;
}
