#include"DateSol.h"

//�ؼ����б��Ѿ����ֵ�������
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

//Token���ͱ�(������,�����ַ�����ʾ)
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

//��������word���ű����
std::vector<GROUP> groups;

//����������
int Token_Times[TokenNum] = { 0 };

//������Ϣ����
	//�洢�������ڵ�������
std::vector<int> Error_col;
	//�����ַ���
std::vector<std::string> Error_word;
	//������Ϣ
std::vector<std::string> Error_mas;

//�����������ַ�����
extern int File_lines;
extern int File_CharNums;
//���������word
extern std::string word;

//���ֲ���word�Ƿ��ڹؼ��ʱ���
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

//����word���Ƿ�������������Ϣ����ȷ������word���ű�
void Add_Word(int Type)
{
	switch (Type)
	{
	case SIGN_WORD: case KEY_WORD: case OP_WORD: case BOUND_WORD: case CONST_STR: case CONST_CH:
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
		if (!_finite(get))//Խ��
		{
			Error_col.push_back(File_lines);
			Error_word.push_back(word);
			Error_mas.push_back(std::string("����������float��Χ"));
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
		if (!_finite(get))//Խ��
		{
			Error_col.push_back(File_lines);
			Error_word.push_back(word);
			Error_mas.push_back(std::string("����������double��Χ"));
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
		//��int���м��
		int base = GetIntBase(word);
		switch (base)
		{
		case 2: case 8: case 16:
		{
			std::string valid;
			switch ((IsBaseInt(word, base, valid)))
			{
			case 0://���ֹ����޷���ʾ
			{
				Error_col.push_back(File_lines);
				Error_word.push_back(word);
				Error_mas.push_back(std::string("������������"));
				break;
			}
			case 1://��int
			{
				GROUP add;
				add.names = valid;
				add.Types = NUM_INT;
				groups.push_back(add);
				Token_Times[NUM_INT] += 1;
				break;
			}
			case 2://��long long
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
			case 0://���ֹ����޷���ʾ
			{
				Error_col.push_back(File_lines);
				Error_word.push_back(word);
				Error_mas.push_back(std::string("������������"));
				break;
			}
			case 1://��int
			{
				GROUP add;
				add.names = valid;
				add.Types = NUM_INT;
				groups.push_back(add);
				Token_Times[NUM_INT] += 1;
				break;
			}
			case 2://��long long
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
		//��Uint������
		int base = GetUIntBase(word);
		switch (base)
		{
		case 2: case 8: case 16:
		{
			std::string valid;
			switch ((IsBaseUInt(word, base, valid)))
			{
			case 0://���ֹ����޷���ʾ
			{
				Error_col.push_back(File_lines);
				Error_word.push_back(word);
				Error_mas.push_back(std::string("������������"));
				break;
			}
			case 1://��Uint
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
			case 0://���ֹ����޷���ʾ
			{
				Error_col.push_back(File_lines);
				Error_word.push_back(word);
				Error_mas.push_back(std::string("������������"));
				break;
			}
			case 1://��Uint
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
		//��LL������
		int base = GetLLongBase(word);
		switch (base)
		{
		case 2: case 8: case 16:
		{
			std::string valid;
			switch ((IsBaseLLong(word, base, valid)))
			{
			case 0://���ֹ����޷���ʾ
			{
				Error_col.push_back(File_lines);
				Error_word.push_back(word);
				Error_mas.push_back(std::string("������������"));
				break;
			}
			case 1://��LL
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
			case 0://���ֹ����޷���ʾ
			{
				Error_col.push_back(File_lines);
				Error_word.push_back(word);
				Error_mas.push_back(std::string("������������"));
				break;
			}
			case 1://��LL
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
		//��ULL������
		int base = GetULLongBase(word);
		switch (base)
		{
		case 2: case 8: case 16:
		{
			std::string valid;
			switch ((IsBaseULLong(word, base, valid)))
			{
			case 0://���ֹ����޷���ʾ
			{
				Error_col.push_back(File_lines);
				Error_word.push_back(word);
				Error_mas.push_back(std::string("������������"));
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
			case 0://���ֹ����޷���ʾ
			{
				Error_col.push_back(File_lines);
				Error_word.push_back(word);
				Error_mas.push_back(std::string("������������"));
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
	//numĩβ�޺�׺
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

int IsBaseInt(std::string num, int base, std::string& Valid)//������10�����ж�
{
	//numĩβ�޺�׺
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
	if (((8 * sizeof(int) - 1) / index) >= numLen) return 1;//������int��ʾ
	if (((8 * sizeof(long long) - 1) / index) >= numLen) return 2;//��Ҫ������long long��ʾ
	if ((8 * sizeof(unsigned long long) / index) >= numLen) return 3;//��Ҫ������unsigned long long��ʾ
	return 0;//���ֹ����޷���ʾ
}
int Is10Int(std::string num, std::string& Valid)
{
	//numĩβ�޺�׺
	//�Ȼ�ȡ��Чλ
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
	//�޷���int��ʾ
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
	//�޷���long long��ʾ
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
	//�޷���unsigned long long ��ʾ

}

int GetUIntBase(std::string num)
{
	//num��ĩβ��U��u  ����xxu,num��2 8 16 λ������2
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
	//�к�׺U
	//����ȡ��Ч��λ��
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
	if (((8 * sizeof(unsigned int)) / index) >= numLen) return 1;//������Uint��ʾ
	if ((8 * sizeof(unsigned long long) / index) >= numLen) return 2;//��Ҫ������unsigned long long��ʾ
	return 0;//���ֹ����޷���ʾ
}

int Is10UInt(std::string num, std::string& Valid)
{
	//numĩβΪu����U
	//�Ȼ�ȡ��Чλ
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
	//�޷���Uint��ʾ
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
	//�޷���unsigned long long ��ʾ
}

int GetLLongBase(std::string num)
{
	//num��ĩβ��L��l  ����xxl,num��2 8 16 λ������2
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
int IsBaseLLong(std::string num, int base, std::string& Valid)//������10�����ж�
{
	// �к�׺l
	//����ȡ��Ч��λ��
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
	if (((8 * sizeof(long long) - 1) / index) >= numLen) return 1;//������LLong��ʾ
	if ((8 * sizeof(unsigned long long) / index) >= numLen) return 2;//��Ҫ������unsigned long long��ʾ
	return 0;//���ֹ����޷���ʾ
}
int Is10LLong(std::string num, std::string& Valid)
{
	//numĩβΪL
	//�Ȼ�ȡ��Чλ
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
	//�޷���LL��ʾ
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
	//�޷���unsigned long long ��ʾ
}

int GetULLongBase(std::string num)
{
	//num��ĩβ��uL��ul  ����xxul,num��2 8 16 λ������3
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
int IsBaseULLong(std::string num, int base, std::string& Valid)//������10�����ж�
{
	// �к�׺lu
	//����ȡ��Ч��λ��
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
	if ((8 * sizeof(unsigned long long) / index) >= numLen) return 1;//������unsigned long long��ʾ
	return 0;//���ֹ����޷���ʾ
}
int Is10ULLong(std::string num, std::string& Valid)
{
	//numĩβΪUL
	//�Ȼ�ȡ��Чλ
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
	//�޷���unsigned long long ��ʾ
}