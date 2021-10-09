#include"DateSol.h"

//关键字列表，已经过字典序排序
std::vector<std::string> KeyWord =
{
	std::string("auto"),
		std::string("break"),
		std::string("case"),
		std::string("char"),
		std::string("const"),
		std::string("continue"),
		std::string("default"),
		std::string("do"),
		std::string("double"),
		std::string("else"),
		std::string("enum"),
		std::string("extern"),
		std::string("float"),
		std::string("for"),
		std::string("goto"),
		std::string("if"),
		std::string("int"),
		std::string("long"),
		std::string("register"),
		std::string("return"),
		std::string("short"),
		std::string("signed"),
		std::string("sizeof"),
		std::string("static"),
		std::string("struct"),
		std::string("switch"),
		std::string("typedef"),
		std::string("union"),
		std::string("unsigned"),
		std::string("void"),
		std::string("volatile"),
		std::string("while")
};

//Token类型表(类型码,类型字符串表示)
std::map<int, std::string> TokenType =
{
	{SIGN_WORD,std::string("SIGN_WORD")},
	{KEY_WORD,std::string("KEY_WORD")},
	{OP_WORD,std::string("OP_WORD")},
	{BOUND_WORD,std::string("BOUND_WORD")},
	{CONST_STR,std::string("CONST_STR")},
	{CONST_CH,std::string("CONST_CH")},
	{NUM_INT,std::string("NUM_INT")},
	{NUM_UINT,std::string("NUM_UINT")},
	{NUM_LLONG,std::string("NUM_LLONG")},
	{NUM_ULLONG,std::string("NUM_ULLONG")},
	{NUM_FLOAT,std::string("NUM_FLOAT")},
	{NUM_DOUBLE,std::string("NUM_DOUBLE")}
};

//分析出的word符号表管理
std::vector<GROUP> groups;

//各类标记总数
int Token_Times[TokenNum] = { 0 };

//错误信息管理
	//存储错误所在的行坐标
std::vector<int> Error_col;
	//错误字符串
std::vector<std::string> Error_word;
	//错误信息
std::vector<std::string> Error_mas;

//程序行数、字符总数
extern int File_lines;
extern int File_CharNums;
//储存分析的word
extern std::string word;

//二分查找word是否在关键词表内
bool MidSearch_KeyWord(std::string tar, std::vector<std::string>& KeyWordPool)
{
	auto left = KeyWordPool.begin();
	auto right = KeyWordPool.end() - 1;
	auto mid = left + (right - left) / 2;
	while ((right - left) >= 0)
	{
		if (mid->compare(tar) == 0)
		{
			return true;
		}
		else if (mid->compare(tar) > 0)
		{
			if (mid == left) return false;
			else right = mid - 1;
		}
		else
		{
			if (mid == right) return false;
			else left = mid + 1;
		}

		mid = left + (right - left) / 2;
	}
	return false;
}

//分析word，非法，则放入错误信息表，正确，放入word符号表
void Add_Word(int Type)
{
	switch (Type)
	{
	case  SIGN_WORD:
	{
		if (word.size() > MAX_LEN_SIGN_WORD)//标识符过长
		{
			Error_col.push_back(File_lines);
			Error_word.push_back(word);
			Error_mas.push_back(std::string("标识符过长"));
		}
		else
		{
			GROUP add;
			add.names = word;
			add.Types = SIGN_WORD;
			groups.push_back(add);
			Token_Times[Type] += 1;
		}
		break;
	}
	case KEY_WORD: case OP_WORD: case BOUND_WORD: case CONST_STR: case CONST_CH:
	{
		GROUP add;
		add.names = word;
		add.Types = Type;
		groups.push_back(add);
		Token_Times[Type] += 1;
		break;
	}
	case NUM_FLOAT:
	{
		float get = (float)atof(word.c_str());
		if (!_finite(get))//越界
		{
			Error_col.push_back(File_lines);
			Error_word.push_back(word);
			Error_mas.push_back(std::string("浮点数超出float范围"));
		}
		else
		{
			GROUP add;
			add.names = word;
			add.Types = NUM_FLOAT;
			groups.push_back(add);
			Token_Times[NUM_FLOAT] += 1;
			break;
		}
		break;
	}
	case NUM_DOUBLE:
	{
		double get = atof(word.c_str());
		if (!_finite(get))//越界
		{
			Error_col.push_back(File_lines);
			Error_word.push_back(word);
			Error_mas.push_back(std::string("浮点数超出double范围"));
		}
		else
		{
			GROUP add;
			add.names = word;
			add.Types = NUM_DOUBLE;
			groups.push_back(add);
			Token_Times[NUM_DOUBLE] += 1;
			break;
		}
		break;
	}
	case NUM_INT:
	{
		//对int进行检测
		int base = GetIntBase(word);
		switch (base)
		{
		case 2: case 8: case 16:
		{
			std::string valid;
			switch ((IsBaseInt(word, base, valid)))
			{
			case 0://数字过大，无法表示
			{
				Error_col.push_back(File_lines);
				Error_word.push_back(word);
				Error_mas.push_back(std::string("整数常量过大"));
				break;
			}
			case 1://用int
			{
				GROUP add;
				add.names = valid;
				add.Types = NUM_INT;
				groups.push_back(add);
				Token_Times[NUM_INT] += 1;
				break;
			}
			case 2://用long long
			{
				GROUP add;
				add.names = valid;
				add.Types = NUM_LLONG;
				groups.push_back(add);
				Token_Times[NUM_LLONG] += 1;
				break;
			}
			case 3:
			{
				GROUP add;
				add.names = valid;
				add.Types = NUM_ULLONG;
				groups.push_back(add);
				Token_Times[NUM_ULLONG] += 1;
				break;
			}
			default:
				break;
			}
			break;
		}
		case 10:
		{
			std::string valid;
			switch (Is10Int(word, valid))
			{
			case 0://数字过大，无法表示
			{
				Error_col.push_back(File_lines);
				Error_word.push_back(word);
				Error_mas.push_back(std::string("整数常量过大"));
				break;
			}
			case 1://用int
			{
				GROUP add;
				add.names = valid;
				add.Types = NUM_INT;
				groups.push_back(add);
				Token_Times[NUM_INT] += 1;
				break;
			}
			case 2://用long long
			{
				GROUP add;
				add.names = valid;
				add.Types = NUM_LLONG;
				groups.push_back(add);
				Token_Times[NUM_LLONG] += 1;
				break;
			}
			case 3:
			{
				GROUP add;
				add.names = valid;
				add.Types = NUM_ULLONG;
				groups.push_back(add);
				Token_Times[NUM_ULLONG] += 1;
				break;
			}
			default:
				break;
			}
			break;
		}
		default:
			break;
		}
		break;
	}
	case NUM_UINT:
	{
		//对Uint检测进制
		int base = GetUIntBase(word);
		switch (base)
		{
		case 2: case 8: case 16:
		{
			std::string valid;
			switch ((IsBaseUInt(word, base, valid)))
			{
			case 0://数字过大，无法表示
			{
				Error_col.push_back(File_lines);
				Error_word.push_back(word);
				Error_mas.push_back(std::string("整数常量过大"));
				break;
			}
			case 1://用Uint
			{
				GROUP add;
				add.names = valid;
				add.Types = NUM_UINT;
				groups.push_back(add);
				Token_Times[NUM_UINT] += 1;
				break;
			}
			case 2://ULL
			{
				GROUP add;
				add.names = valid;
				add.Types = NUM_ULLONG;
				groups.push_back(add);
				Token_Times[NUM_ULLONG] += 1;
				break;
			}
			default:
				break;
			}
			break;
		}
		case 10:
		{
			std::string valid;
			switch (Is10UInt(word, valid))
			{
			case 0://数字过大，无法表示
			{
				Error_col.push_back(File_lines);
				Error_word.push_back(word);
				Error_mas.push_back(std::string("整数常量过大"));
				break;
			}
			case 1://用Uint
			{
				GROUP add;
				add.names = valid;
				add.Types = NUM_UINT;
				groups.push_back(add);
				Token_Times[NUM_UINT] += 1;
				break;
			}
			case 2:
			{
				GROUP add;
				add.names = valid;
				add.Types = NUM_ULLONG;
				groups.push_back(add);
				Token_Times[NUM_ULLONG] += 1;
				break;
			}
			default:
				break;
			}
			break;
		}
		default:
			break;
		}
		break;
	}
	case NUM_LLONG:
	{
		//对LL检测进制
		int base = GetLLongBase(word);
		switch (base)
		{
		case 2: case 8: case 16:
		{
			std::string valid;
			switch ((IsBaseLLong(word, base, valid)))
			{
			case 0://数字过大，无法表示
			{
				Error_col.push_back(File_lines);
				Error_word.push_back(word);
				Error_mas.push_back(std::string("整数常量过大"));
				break;
			}
			case 1://用LL
			{
				GROUP add;
				add.names = valid;
				add.Types = NUM_LLONG;
				groups.push_back(add);
				Token_Times[NUM_LLONG] += 1;
				break;
			}
			case 2://ULL
			{
				GROUP add;
				add.names = valid;
				add.Types = NUM_ULLONG;
				groups.push_back(add);
				Token_Times[NUM_ULLONG] += 1;
				break;
			}
			default:
				break;
			}
			break;
		}
		case 10:
		{
			std::string valid;
			switch (Is10LLong(word, valid))
			{
			case 0://数字过大，无法表示
			{
				Error_col.push_back(File_lines);
				Error_word.push_back(word);
				Error_mas.push_back(std::string("整数常量过大"));
				break;
			}
			case 1://用LL
			{
				GROUP add;
				add.names = valid;
				add.Types = NUM_LLONG;
				groups.push_back(add);
				Token_Times[NUM_LLONG] += 1;
				break;
			}
			case 2:
			{
				GROUP add;
				add.names = valid;
				add.Types = NUM_ULLONG;
				groups.push_back(add);
				Token_Times[NUM_ULLONG] += 1;
				break;
			}
			default:
				break;
			}
			break;
		}
		default:
			break;
		}
		break;
	}
	case NUM_ULLONG:
	{
		//对ULL检测进制
		int base = GetULLongBase(word);
		switch (base)
		{
		case 2: case 8: case 16:
		{
			std::string valid;
			switch ((IsBaseULLong(word, base, valid)))
			{
			case 0://数字过大，无法表示
			{
				Error_col.push_back(File_lines);
				Error_word.push_back(word);
				Error_mas.push_back(std::string("整数常量过大"));
				break;
			}
			case 1://ULL
			{
				GROUP add;
				add.names = valid;
				add.Types = NUM_ULLONG;
				groups.push_back(add);
				Token_Times[NUM_ULLONG] += 1;
				break;
			}
			default:
				break;
			}
			break;
		}
		case 10:
		{
			std::string valid;
			switch (Is10ULLong(word, valid))
			{
			case 0://数字过大，无法表示
			{
				Error_col.push_back(File_lines);
				Error_word.push_back(word);
				Error_mas.push_back(std::string("整数常量过大"));
				break;
			}
			case 1:
			{
				GROUP add;
				add.names = valid;
				add.Types = NUM_ULLONG;
				groups.push_back(add);
				Token_Times[NUM_ULLONG] += 1;
				break;
			}
			default:
				break;
			}
			break;
		}
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
}

int GetIntBase(std::string num)
{
	//num末尾无后缀
	if (num.size() < 2)
	{
		return 10;
	}
	if (num[0] == '0')
	{
		if (num[1] == 'b' || num[1] == 'B') return 2;
		if (num[1] == 'x' || num[1] == 'X') return 16;
		else return 8;
	}
	else return 10;
}

int IsBaseInt(std::string num, int base, std::string& Valid)//不包含10进制判断
{
	//num末尾无后缀
	unsigned int numLen = 0;
	bool begin = false;
	if (base == 2)
	{
		for (unsigned int i = 2; i < num.size(); i++)
		{
			if (num[i] != '0') begin = true;
			if (begin) Valid.push_back(num[i]);
		}
		numLen = num.size();
		if (numLen == 0)
		{
			numLen = 1;
			Valid = std::string("0b0");
		}
		else
		{
			Valid = std::string("0b") + Valid;
		}
	}
	if (base == 8)
	{
		for (unsigned int i = 1; i < num.size(); i++)
		{
			if (num[i] != '0') begin = true;
			if (begin) Valid.push_back(num[i]);
		}
		numLen = num.size();
		if (numLen == 0)
		{
			numLen = 1;
			Valid = std::string("00");
		}
		else
		{
			Valid = std::string("0") + Valid;
		}
	}
	if (base == 16)
	{
		for (unsigned int i = 2; i < num.size(); i++)
		{
			if (num[i] != '0') begin = true;
			if (begin) Valid.push_back(num[i]);
		}
		numLen = num.size();
		if (numLen == 0)
		{
			numLen = 1;
			Valid = std::string("0x0");
		}
		else
		{
			Valid = std::string("0x") + Valid;
		}
	}
	int index = 0;
	while (base > 1)
	{
		base /= 2;
		index += 1;
	}
	if (((8 * sizeof(int) - 1) / index) >= numLen) return 1;//可以用int表示
	if (((8 * sizeof(long long) - 1) / index) >= numLen) return 2;//需要提升到long long表示
	if ((8 * sizeof(unsigned long long) / index) >= numLen) return 3;//需要提升到unsigned long long表示
	return 0;//数字过大，无法表示
}
int Is10Int(std::string num, std::string& Valid)
{
	//num末尾无后缀
	//先获取有效位
	bool real = false;
	for (unsigned int i = 0; i < num.size(); i++)
	{
		if (num[i] != '0') real = true;
		if (real) Valid.push_back(num[i]);
	}
	if (Valid.size() == 0) Valid.push_back('0');


	std::string StdInt = std::to_string(INT_MAX);
	if (Valid.size() < StdInt.size())
	{
		return 1;
	}
	else if (Valid.size() == StdInt.size())
	{
		if (Valid.compare(StdInt) < 0)
		{
			return 1;
		}
	}
	//无法用int表示
	std::string StdLL = std::to_string(LLONG_MAX);
	if (Valid.size() < StdLL.size())
	{
		return 2;
	}
	else if (Valid.size() == StdLL.size())
	{
		if (Valid.compare(StdLL) < 0)
		{
			return 2;
		}
	}
	//无法用long long表示
	std::string StdULL = std::to_string(ULLONG_MAX);
	if (Valid.size() < StdULL.size())
	{
		return 3;
	}
	else if (Valid.size() == StdULL.size())
	{
		if (Valid.compare(StdULL) < 0)
		{
			return 3;
		}
	}
	return 0;
	//无法用unsigned long long 表示

}

int GetUIntBase(std::string num)
{
	//num的末尾有U或u  形如xxu,num的2 8 16 位数大于2
	if (num.size() < 3)
	{
		return 10;
	}
	if (num[0] == '0')
	{
		if (num[1] == 'b' || num[1] == 'B') return 2;
		if (num[1] == 'x' || num[1] == 'X') return 16;
		return 8;
	}
	else
	{
		return 10;
	}
}
int IsBaseUInt(std::string num, int base, std::string& Valid)
{
	//有后缀U
	//先提取有效的位数
	unsigned int numLen = 0;
	bool begin = false;
	if (base == 2)
	{
		for (unsigned int i = 2; i < num.size() - 1; i++)
		{
			if (num[i] != '0') begin = true;
			if (begin) Valid.push_back(num[i]);
		}
		numLen = Valid.size();
		if (numLen == 0)
		{
			Valid = std::string("0b0U");
			numLen = 1;
		}
		else
		{
			Valid = std::string("0b") + Valid + std::string("U");
		}
	}
	if (base == 8)
	{
		for (unsigned int i = 1; i < num.size() - 1; i++)
		{
			if (num[i] != '0') begin = true;
			if (begin) Valid.push_back(num[i]);
		}
		numLen = Valid.size();
		if (numLen == 0)
		{
			Valid = std::string("00U");
			numLen = 1;
		}
		else
		{
			Valid = std::string("0") + Valid + std::string("U");
		}
	}

	if (base == 16)
	{
		for (unsigned int i = 2; i < num.size() - 1; i++)
		{
			if (num[i] != '0') begin = true;
			if (begin) Valid.push_back(num[i]);
		}
		numLen = Valid.size();
		if (numLen == 0)
		{
			Valid = std::string("0x0U");
			numLen = 1;
		}
		else
		{
			Valid = std::string("0x") + Valid + std::string("U");
		}
	}

	int index = 0;
	while (base > 1)
	{
		base /= 2;
		index += 1;
	}
	if (((8 * sizeof(unsigned int)) / index) >= numLen) return 1;//可以用Uint表示
	if ((8 * sizeof(unsigned long long) / index) >= numLen) return 2;//需要提升到unsigned long long表示
	return 0;//数字过大，无法表示
}

int Is10UInt(std::string num, std::string& Valid)
{
	//num末尾为u或者U
	//先获取有效位
	bool real = false;
	for (unsigned int i = 0; i < num.size() - 1; i++)
	{
		if (num[i] != '0') real = true;
		if (real) Valid.push_back(num[i]);
	}
	if (Valid.size() == 0) Valid.push_back('0');


	std::string StdUInt = std::to_string(UINT_MAX);
	if (Valid.size() < StdUInt.size())
	{
		Valid = Valid + std::string("U");
		return 1;
	}
	else if (Valid.size() == StdUInt.size())
	{
		if (Valid.compare(StdUInt) < 0)
		{
			Valid = Valid + std::string("U");
			return 1;
		}
	}
	//无法用Uint表示
	std::string StdULL = std::to_string(ULLONG_MAX);
	if (Valid.size() < StdULL.size())
	{
		Valid = Valid + std::string("U");
		return 2;
	}
	else if (Valid.size() == StdULL.size())
	{
		if (Valid.compare(StdULL) < 0)
		{
			Valid = Valid + std::string("U");
			return 2;
		}
	}
	return 0;
	//无法用unsigned long long 表示
}

int GetLLongBase(std::string num)
{
	//num的末尾有L或l  形如xxl,num的2 8 16 位数大于2
	if (num.size() < 2)
	{
		return 10;
	}
	if (num[0] == '0')
	{
		if (num[1] == 'b' || num[1] == 'B') return 2;
		if (num[1] == 'x' || num[1] == 'X') return 16;
		return 8;
	}
	else
	{
		return 10;
	}
}
int IsBaseLLong(std::string num, int base, std::string& Valid)//不包含10进制判断
{
	// 有后缀l
	//先提取有效的位数
	unsigned int numLen = 0;
	bool begin = false;
	if (base == 2)
	{
		for (unsigned int i = 2; i < num.size() - 1; i++)
		{
			if (num[i] != '0') begin = true;
			if (begin) Valid.push_back(num[i]);
		}
		numLen = Valid.size();
		if (numLen == 0)
		{
			Valid = std::string("0b0L");
			numLen = 1;
		}
		else
		{
			Valid = std::string("0b") + Valid + std::string("L");
		}
	}
	if (base == 8)
	{
		for (unsigned int i = 1; i < num.size() - 1; i++)
		{
			if (num[i] != '0') begin = true;
			if (begin) Valid.push_back(num[i]);
		}
		numLen = Valid.size();
		if (numLen == 0)
		{
			Valid = std::string("00L");
			numLen = 1;
		}
		else
		{
			Valid = std::string("0") + Valid + std::string("L");
		}
	}

	if (base == 16)
	{
		for (unsigned int i = 2; i < num.size() - 1; i++)
		{
			if (num[i] != '0') begin = true;
			if (begin) Valid.push_back(num[i]);
		}
		numLen = Valid.size();
		if (numLen == 0)
		{
			Valid = std::string("0x0L");
			numLen = 1;
		}
		else
		{
			Valid = std::string("0x") + Valid + std::string("L");
		}
	}

	int index = 0;
	while (base > 1)
	{
		base /= 2;
		index += 1;
	}
	if (((8 * sizeof(long long) - 1) / index) >= numLen) return 1;//可以用LLong表示
	if ((8 * sizeof(unsigned long long) / index) >= numLen) return 2;//需要提升到unsigned long long表示
	return 0;//数字过大，无法表示
}
int Is10LLong(std::string num, std::string& Valid)
{
	//num末尾为L
	//先获取有效位
	bool real = false;
	for (unsigned int i = 0; i < num.size() - 1; i++)
	{
		if (num[i] != '0') real = true;
		if (real) Valid.push_back(num[i]);
	}
	if (Valid.size() == 0) Valid.push_back('0');


	std::string StdLL = std::to_string(LLONG_MAX);
	if (Valid.size() < StdLL.size())
	{
		Valid = Valid + std::string("L");
		return 1;
	}
	else if (Valid.size() == StdLL.size())
	{
		if (Valid.compare(StdLL) < 0)
		{
			Valid = Valid + std::string("L");
			return 1;
		}
	}
	//无法用LL表示
	std::string StdULL = std::to_string(ULLONG_MAX);
	if (Valid.size() < StdULL.size())
	{
		Valid = Valid + std::string("L");
		return 2;
	}
	else if (Valid.size() == StdULL.size())
	{
		if (Valid.compare(StdULL) < 0)
		{
			Valid = Valid + std::string("L");
			return 2;
		}
	}
	return 0;
	//无法用unsigned long long 表示
}

int GetULLongBase(std::string num)
{
	//num的末尾有uL或ul  形如xxul,num的2 8 16 位数大于3
	if (num.size() < 3)
	{
		return 10;
	}
	if (num[0] == '0')
	{
		if (num[1] == 'b' || num[1] == 'B') return 2;
		if (num[1] == 'x' || num[1] == 'X') return 16;
		return 8;
	}
	else
	{
		return 10;
	}
}
int IsBaseULLong(std::string num, int base, std::string& Valid)//不包含10进制判断
{
	// 有后缀lu
	//先提取有效的位数
	unsigned int numLen = 0;
	bool begin = false;
	if (base == 2)
	{
		for (unsigned int i = 2; i < num.size() - 2; i++)
		{
			if (num[i] != '0') begin = true;
			if (begin) Valid.push_back(num[i]);
		}
		numLen = Valid.size();
		if (numLen == 0)
		{
			Valid = std::string("0b0UL");
			numLen = 1;
		}
		else
		{
			Valid = std::string("0b") + Valid + std::string("UL");
		}
	}
	if (base == 8)
	{
		for (unsigned int i = 1; i < num.size() - 2; i++)
		{
			if (num[i] != '0') begin = true;
			if (begin) Valid.push_back(num[i]);
		}
		numLen = Valid.size();
		if (numLen == 0)
		{
			Valid = std::string("00UL");
			numLen = 1;
		}
		else
		{
			Valid = std::string("0") + Valid + std::string("UL");
		}
	}

	if (base == 16)
	{
		for (unsigned int i = 2; i < num.size() - 2; i++)
		{
			if (num[i] != '0') begin = true;
			if (begin) Valid.push_back(num[i]);
		}
		numLen = Valid.size();
		if (numLen == 0)
		{
			Valid = std::string("0x0UL");
			numLen = 1;
		}
		else
		{
			Valid = std::string("0x") + Valid + std::string("UL");
		}
	}

	int index = 0;
	while (base > 1)
	{
		base /= 2;
		index += 1;
	}
	if ((8 * sizeof(unsigned long long) / index) >= numLen) return 1;//可以用unsigned long long表示
	return 0;//数字过大，无法表示
}
int Is10ULLong(std::string num, std::string& Valid)
{
	//num末尾为UL
	//先获取有效位
	bool real = false;
	for (unsigned int i = 0; i < num.size() - 2; i++)
	{
		if (num[i] != '0') real = true;
		if (real) Valid.push_back(num[i]);
	}
	if (Valid.size() == 0) Valid.push_back('0');

	std::string StdULL = std::to_string(ULLONG_MAX);
	if (Valid.size() < StdULL.size())
	{
		Valid = Valid + std::string("UL");
		return 1;
	}
	else if (Valid.size() == StdULL.size())
	{
		if (Valid.compare(StdULL) < 0)
		{
			Valid = Valid + std::string("UL");
			return 1;
		}
	}
	return 0;
	//无法用unsigned long long 表示
}
