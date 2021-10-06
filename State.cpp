#include"State.h"
//程序行数、字符总数、当前字符、当前识别字符串、当前状态
int File_lines = 0;
int File_CharNums = 0;
char ch;
std::string word;
int state = 0;


//错误信息管理
	//存储错误所在的行列坐标
extern std::vector<int> Error_col;
//错误字符串
extern std::vector<std::string> Error_word;
//错误信息
extern std::vector<std::string> Error_mas;
//符号表
extern std::vector<std::string> KeyWord;


void sol_ch(void)
{
	switch (state)
	{

	case 0://初始状态
	{
		state0();
		break;
	}
	case 1:
	{
		state1();
		break;
	}
	case 2:
	{
		state2();
		break;
	}
	case 3:
	{
		state3();
		break;
	}
	case 4:
	{
		state4();
		break;
	}
	case 5:
	{
		state5();
		break;
	}
	case 6:
	{
		state6();
		break;
	}
	case 7:
	{
		state7();
		break;
	}
	case 8:
	{
		state8();
		break;
	}
	case 9:
	{
		state9();
		break;
	}
	case 10:
	{
		state10();
		break;
	}
	case 11:
	{
		state11();
		break;
	}
	case 12:
	{
		state12();
		break;
	}
	case 13:
	{
		state13();
		break;
	}
	case 14:
	{
		state14();
		break;
	}
	case 15:
	{
		state15();
		break;
	}
	case 16:
	{
		state16();
		break;
	}
	case 17:
	{
		state17();
		break;
	}
	case 18:
	{
		state18();
		break;
	}
	case 19:
	{
		state19();
		break;
	}
	case 20:
	{
		state20();
		break;
	}
	case 21:
	{
		state21();
		break;
	}
	case 22:
	{
		state22();
		break;
	}
	case 23:
	{
		state23();
		break;
	}
	case 24:
	{
		state24();
		break;
	}
	case 25:
	{
		state25();
		break;
	}
	case 26:
	{
		state26();
		break;
	}
	case 27:
	{
		state27();
		break;
	}
	case 28:
	{
		state28();
		break;
	}
	case 29:
	{
		state29();
		break;
	}
	case 30:
	{
		state30();
		break;
	}
	case 31:
	{
		state31();
		break;
	}
	case 32:
	{
		state32();
		break;
	}
	case 33:
	{
		state33();
		break;
	}
	case 34:
	{
		state34();
		break;
	}
	case 35:
	{
		state35();
		break;
	}
	case 36:
	{
		state36();
		break;
	}
	case 37:
	{
		state37();
		break;
	}
	case 38:
	{
		state38();
		break;
	}
	case 39:
	{
		state39();
		break;
	}
	case 40:
	{
		state40();
		break;
	}
	case 41:
	{
		state41();
		break;
	}
	default:
	{
		std::cout << "@@@词法分析异常@@@" << std::endl;
		state = 0;
		word.clear();
		state0();
		break;
	}
	}
}


void state0()
{
	switch (ch)
	{
		//标识符类型
	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h':
	case 'i': case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p':
	case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H':
	case 'I': case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P':
	case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
	case '_':
	{
		state = 1;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	//字符串常量
	case '"':
	{
		state = 6;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case'1': case'2': case'3': case'4': case'5': case'6': case'7': case'8': case'9':
	{
		state = 2;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case'0':
	{
		state = 34;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	//case //运算符状态未规划
	case '+':
	{
		state = 8;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}

	case '-':
	{
		state = 9;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}

	case '*':
	{
		state = 10;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}

	case '/':
	{
		state = 11;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}

	case '%':
	{
		state = 12;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}

	case '!':
	{
		state = 13;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}

	case '|':
	{
		state = 14;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}

	case '^':
	{
		state = 15;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}

	case '=':
	{
		state = 16;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}

	case '&':
	{
		state = 17;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}

	case '>':
	{
		state = 18;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}

	case '<':
	{
		state = 20;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}

	case '?':
	{
		state = 22;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}

	case '~':
	{
		word.push_back(ch);
		File_CharNums += 1;
		Add_Word(OP_WORD);
		//清理word
		word.clear();
		//结束
		break;
	}

	case ',': case '(': case ')': case '[': case  ']':
	case '.': case ';': case ':': case '{': case '}':
	{
		word.push_back(ch);
		File_CharNums += 1;
		Add_Word(BOUND_WORD);
		//清理word
		word.clear();
		//结束
		break;
	}

	case ' ': case '\t':
	{
		File_CharNums += 1;
		break;
	}
	case '\n':
	{
		File_CharNums += 1;
		File_lines += 1;
		break;
	}
	case '\'':
	{
		state = 26;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case EOF:
	{
		break;
	}
	default:
	{
		//出现错误
		File_CharNums += 1;
		Error_col.push_back(File_lines);
		Error_word.push_back(word);
		Error_mas.push_back(std::string("非法字符"));
		state = 0;
		word.clear();
		break;
	}
	}
	//读完文件后
}

void state1()
{
	switch (ch)
	{
	case'a': case'b': case'c': case'd': case'e': case'f': case'g': case'h':
	case'i': case'j': case'k': case'l': case'm': case'n': case'o': case'p':
	case'q': case'r': case's': case't': case'u': case'v': case'w': case'x': case'y': case'z':
	case'A': case'B': case'C': case'D': case'E': case'F': case'G': case'H':
	case'I': case'J': case'K': case'L': case'M': case'N': case'O': case'P':
	case'Q': case'R': case'S': case'T': case'U': case'V': case'W': case'X': case'Y': case'Z':
	case'_':
	case'0': case'1': case'2': case'3': case'4': case'5': case'6': case'7': case'8': case'9':
	{
		state = 1;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	default:
	{
		//记下num标识符
		int Type;
		if (MidSearch_KeyWord(word, KeyWord)) Type = KEY_WORD;
		else Type = SIGN_WORD;
		Add_Word(Type);
		//清理word
		word.clear();
		//结束，回归state0
		state = 0;
		state0();
		break;
	}
	}
}

void state2()
{
	switch (ch)
	{
	case'0': case'1': case'2': case'3': case'4': case'5': case'6': case'7': case'8': case'9':
	{
		state = 2;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case 'E':case 'e':
	{
		state = 3;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case '.':
	{
		state = 4;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case 'l': case 'L':
	{
		state = 40;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case 'u': case 'U':
	{
		word.push_back(ch);
		File_CharNums += 1;
		state = 41;
		break;
	}
	default://结束
	{
		Add_Word(NUM_INT);
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}

void state3()
{
	switch (ch)
	{
	case'0': case'1': case'2': case'3': case'4': case'5': case'6': case'7': case'8': case'9':
	{
		state = 5;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case '+': case '-':
	{
		state = 33;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	default:
	{
		//出现错误
		Error_col.push_back(File_lines);
		Error_word.push_back(word);
		Error_mas.push_back(std::string("浮点数不合法"));
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}



void state4()
{
	switch (ch)
	{
	case'0': case'1': case'2': case'3': case'4': case'5': case'6': case'7': case'8': case'9':
	{
		state = 4;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case 'E':case 'e':
	{
		state = 3;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case 'l': case 'L': case 'f': case 'F':
	{
		word.push_back(ch);
		File_CharNums += 1;
		if (ch == 'l' || ch == 'L') Add_Word(NUM_DOUBLE);
		else Add_Word(NUM_FLOAT);
		//清理word
		word.clear();
		state = 0;
		//结束
		break;
	}
	default:
	{
		Add_Word(NUM_DOUBLE);
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}

void state5()
{
	switch (ch)
	{
	case'0': case'1': case'2': case'3': case'4': case'5': case'6': case'7': case'8': case'9':
	{
		state = 5;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case 'l': case 'L': case 'f': case 'F':
	{
		word.push_back(ch);
		File_CharNums += 1;
		if (ch == 'l' || ch == 'L') Add_Word(NUM_DOUBLE);
		else Add_Word(NUM_FLOAT);
		//清理word
		word.clear();
		state = 0;
		//结束
		break;
	}
	default:
	{
		Add_Word(NUM_DOUBLE);
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}

void state6()
{
	switch (ch)
	{
	case '"':
	{
		File_CharNums += 1;
		word.push_back(ch);
		Add_Word(CONST_STR);
		word.clear();
		state = 0;
		break;
	}
	case '\\':
	{
		state = 7;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case '\n':
	{//error
		Error_col.push_back(File_lines);
		Error_word.push_back(word);
		Error_mas.push_back(std::string("字符串常量非法"));
		state = 0;
		word.clear();
		state = 0;
		state0();
		break;
	}
	case EOF:
	{//error
		Error_col.push_back(File_lines);
		Error_word.push_back(word);
		Error_mas.push_back(std::string("字符串常量非法"));
		state = 0;
		word.clear();
		state = 0;
		state0();
		break;
	}
	default:
	{
		state = 6;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	}
}

void state7()
{
	switch (ch)
	{
	case '\\':
	{
		state = 7;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	default:
	{
		if (ch == '\n') File_lines += 1;
		state = 6;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	}
}

void state8()
{
	switch (ch)
	{
	case '=': case '+':
	{
		File_CharNums += 1;
		word.push_back(ch);
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		break;
	}
	default:
	{
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}

void state9()
{
	switch (ch)
	{
	case '=': case '>': case '-':
	{
		File_CharNums += 1;
		word.push_back(ch);
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		break;
	}
	default:
	{
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}

void state10()
{
	switch (ch)
	{
	case '=':
	{
		File_CharNums += 1;
		word.push_back(ch);
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		break;
	}
	default:
	{
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}

void state11()
{
	switch (ch)
	{
	case '=':
	{
		File_CharNums += 1;
		word.push_back(ch);
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		break;
	}
	case '/':
	{
		File_CharNums += 1;
		word.clear();
		state = 25;
		break;
	}
	case '*':
	{
		File_CharNums += 1;
		word.clear();
		state = 23;
		break;
	}
	default:
	{
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}

void state12()
{
	switch (ch)
	{
	case '=':
	{
		File_CharNums += 1;
		word.push_back(ch);
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		break;
	}
	default:
	{
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}

void state13()
{
	switch (ch)
	{
	case '=':
	{
		File_CharNums += 1;
		word.push_back(ch);
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		break;
	}
	default:
	{
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}

void state14()
{
	switch (ch)
	{
	case '=': case '|':
	{
		File_CharNums += 1;
		word.push_back(ch);
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		break;
	}
	default:
	{
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}

void state15()
{
	switch (ch)
	{
	case '=':
	{
		File_CharNums += 1;
		word.push_back(ch);
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		break;
	}
	default:
	{
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}

void state16()
{
	switch (ch)
	{
	case '=':
	{
		File_CharNums += 1;
		word.push_back(ch);
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		break;
	}
	default:
	{
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}

void state17()
{
	switch (ch)
	{
	case '=': case '&':
	{
		File_CharNums += 1;
		word.push_back(ch);
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		break;
	}
	default:
	{
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}

void state18()
{
	switch (ch)
	{
	case '=':
	{
		File_CharNums += 1;
		word.push_back(ch);
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		break;
	}
	case '>':
	{
		state = 19;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	default:
	{
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}

void state19()
{
	switch (ch)
	{
	case '=':
	{
		File_CharNums += 1;
		word.push_back(ch);
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		break;
	}
	default:
	{
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}

void state20()
{
	switch (ch)
	{
	case '=':
	{
		File_CharNums += 1;
		word.push_back(ch);
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		break;
	}
	case '<':
	{
		state = 19;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	default:
	{
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}

void state21()
{
	switch (ch)
	{
	case '=':
	{
		File_CharNums += 1;
		word.push_back(ch);
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		break;
	}
	default:
	{
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}

void state22()
{
	switch (ch)
	{
	case ':':
	{
		File_CharNums += 1;
		word.push_back(ch);
		Add_Word(OP_WORD);
		word.clear();
		state = 0;
		break;
	}
	default:
	{
		//error
		Error_col.push_back(File_lines);
		Error_word.push_back(word);
		Error_mas.push_back(std::string("非法字符"));
		state = 0;
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}


void state23()
{
	switch (ch)
	{
	case '*':
	{
		state = 24;
		File_CharNums += 1;
		break;
	}
	case EOF:
	{
		state = 0;
		state0();
	}
	default:
	{
		File_CharNums += 1;
		if (ch == '\n')
		{
			File_lines += 1;
		}
		break;
	}
	}
}

void state24()
{
	switch (ch)
	{
	case '*':
	{
		File_CharNums += 1;
		break;
	}
	case '/':
	{
		state = 0;
		File_CharNums += 1;
		break;
	}
	case EOF:
	{
		state = 0;
		state0();
	}
	default:
	{
		state = 23;
		File_CharNums += 1;
		if (ch == '\n')
		{
			File_lines += 1;
		}
		break;
	}
	}
}

void state25()
{
	switch (ch)
	{
	case '\n':
	{
		state = 0;
		File_CharNums += 1;
		File_lines += 1;
		break;
	}
	case EOF:
	{
		state = 0;
		state0();
	}
	default:
	{
		File_CharNums += 1;
		break;
	}
	}
}

void state26()
{
	switch (ch)
	{
	case '\\':
	{
		state = 28;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case EOF:
	{
		//error
		Error_col.push_back(File_lines);
		Error_word.push_back(word);
		Error_mas.push_back(std::string("非法word"));
		state = 0;
		word.clear();
		state = 0;
		state0();
		break;
	}
	default:
	{
		state = 27;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	}
}
void state27()
{
	switch (ch)
	{
	case '\'':
	{
		File_CharNums += 1;
		word.push_back(ch);
		Add_Word(CONST_CH);
		word.clear();
		state = 0;
		break;
	}
	default:
	{
		//error
		Error_col.push_back(File_lines);
		Error_word.push_back(word);
		Error_mas.push_back(std::string("非法word"));
		state = 0;
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}
void state28()
{
	switch (ch)
	{
	case 'n': case 'r': case 't': case 'v': case 'a': case 'b': case 'f':
	case '\'': case '"': case '\\': case '?':
	{
		state = 27;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case '0': case'1': case'2': case'3': case'4': case'5': case'6': case'7':
	{
		state = 29;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case 'x':
	{
		state = 31;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	default:
	{
		//error
		Error_col.push_back(File_lines);
		Error_word.push_back(word);
		Error_mas.push_back(std::string("非法word"));
		state = 0;
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}
void state29()
{
	switch (ch)
	{
	case '0': case'1': case'2': case'3': case'4': case'5': case'6': case'7':
	{
		state = 30;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case '\'':
	{
		File_CharNums += 1;
		word.push_back(ch);
		Add_Word(CONST_CH);
		word.clear();
		state = 0;
		break;
	}
	default:
	{
		//error
		Error_col.push_back(File_lines);
		Error_word.push_back(word);
		Error_mas.push_back(std::string("非法word"));
		state = 0;
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}
void state30()
{
	switch (ch)
	{
	case '0': case'1': case'2': case'3': case'4': case'5': case'6': case'7':
	{
		state = 27;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case '\'':
	{
		File_CharNums += 1;
		word.push_back(ch);
		Add_Word(CONST_CH);
		word.clear();
		state = 0;
		break;
	}
	default:
	{
		//error
		Error_col.push_back(File_lines);
		Error_word.push_back(word);
		Error_mas.push_back(std::string("非法word"));
		state = 0;
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}
void state31()
{
	switch (ch)
	{
	case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8':
	case '9': case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'A': case 'B':
	case 'C': case 'D': case 'E': case 'F':
	{
		state = 32;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	default:
	{
		//error
		Error_col.push_back(File_lines);
		Error_word.push_back(word);
		Error_mas.push_back(std::string("非法word"));
		state = 0;
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}
void state32()
{
	switch (ch)
	{
	case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8':
	case '9': case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'A': case 'B':
	case 'C': case 'D': case 'E': case 'F':
	{
		state = 27;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case '\'':
	{
		File_CharNums += 1;
		word.push_back(ch);
		Add_Word(CONST_CH);
		word.clear();
		state = 0;
		break;
	}
	default:
	{
		//error
		Error_col.push_back(File_lines);
		Error_word.push_back(word);
		Error_mas.push_back(std::string("非法word"));
		state = 0;
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}

void state33()
{
	switch (ch)
	{
	case'0': case'1': case'2': case'3': case'4': case'5': case'6': case'7': case'8': case'9':
	{
		state = 5;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	default:
	{
		//出现错误
		Error_col.push_back(File_lines);
		Error_word.push_back(word);
		Error_mas.push_back(std::string("非法浮点数"));
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}

void state34()
{
	switch (ch)
	{
	case 'b': case 'B':
	{
		state = 35;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case 'x': case 'X':
	{
		state = 37;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case'0': case'1': case'2': case'3': case'4': case'5': case'6': case'7':
	{
		state = 39;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case 'l': case 'L':
	{
		state = 40;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case 'u': case 'U':
	{
		word.push_back(ch);
		File_CharNums += 1;
		state = 41;
		break;
	}
	default:
	{
		Add_Word(NUM_INT);
		//清理word
		word.clear();
		//结束，回归state0
		state = 0;
		state0();
		break;
	}
	}
}

void state35()
{
	switch (ch)
	{
	case '0': case '1':
	{
		state = 36;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	default:
	{
		//出现错误
		Error_col.push_back(File_lines);
		Error_word.push_back(word);
		Error_mas.push_back(std::string("非法二进制整数"));
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}

void state36()
{
	switch (ch)
	{
	case '0': case '1':
	{
		state = 36;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case 'l': case 'L':
	{
		state = 40;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case 'u': case 'U':
	{
		word.push_back(ch);
		File_CharNums += 1;
		state = 41;
		break;
	}
	default:
	{
		Add_Word(NUM_INT);
		//清理word
		word.clear();
		//结束，回归state0
		state = 0;
		state0();
		break;
	}
	}
}

void state37()
{
	switch (ch)
	{
	case'0': case'1': case'2': case'3': case'4': case'5': case'6': case'7':
	case'8': case'9': case'a': case'b': case'c': case'd': case'e': case'f':
	case'A': case'B': case'C': case'D': case'E': case'F':
	{
		state = 38;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	default:
	{
		//出现错误
		Error_col.push_back(File_lines);
		Error_word.push_back(word);
		Error_mas.push_back(std::string("非法八进制整数"));
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}

void state38()
{
	switch (ch)
	{
	case'0': case'1': case'2': case'3': case'4': case'5': case'6': case'7':
	case'8': case'9': case'a': case'b': case'c': case'd': case'e': case'f':
	case'A': case'B': case'C': case'D': case'E': case'F':
	{
		state = 38;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case 'l': case 'L':
	{
		state = 40;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case 'u': case 'U':
	{
		word.push_back(ch);
		File_CharNums += 1;
		state = 41;
		break;
	}
	default:
	{
		Add_Word(NUM_INT);
		//清理word
		word.clear();
		//结束，回归state0
		state = 0;
		state0();
		break;
	}
	}
}

void state39()
{
	switch (ch)
	{
	case'0': case'1': case'2': case'3': case'4': case'5': case'6': case'7':
	{
		state = 39;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case 'l': case 'L':
	{
		state = 40;
		word.push_back(ch);
		File_CharNums += 1;
		break;
	}
	case 'u': case 'U':
	{
		word.push_back(ch);
		File_CharNums += 1;
		state = 41;
		break;
	}
	default:
	{
		Add_Word(NUM_INT);
		//清理word
		word.clear();
		//结束，回归state0
		state = 0;
		state0();
		break;
	}
	}
}

void state40()
{
	switch (ch)
	{
	case 'u': case 'U':
	{
		word.push_back(ch);
		File_CharNums += 1;
		Add_Word(NUM_ULLONG);
		word.clear();
		state = 0;
		break;
	}
	default:
	{
		Add_Word(NUM_LLONG);
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}

void state41()
{
	switch (ch)
	{
	case 'l': case 'L':
	{
		word.push_back(ch);
		File_CharNums += 1;
		Add_Word(NUM_ULLONG);
		word.clear();
		state = 0;
		break;
	}
	default:
	{
		Add_Word(NUM_UINT);
		word.clear();
		state = 0;
		state0();
		break;
	}
	}
}