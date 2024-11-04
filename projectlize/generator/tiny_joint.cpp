#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include<vector>
#include<string>
#include<set>
using namespace std;

bool match__if(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	'i':
						state = 2;
						break;
					default:
						state = 4;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					case	'f':
						state = 3;
						break;
					default:
						state = 4;
						break;
				}
				break;
			case	3:
				switch (s[idx])
				{
					default:
						state = 4;
						break;
				}
				break;
			default:
				state = 4;
				break;
		}
		idx++;
	}
	if (state == 3)
	{
		return true;
	}
	return false;
}


bool match__then(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	't':
						state = 2;
						break;
					default:
						state = 6;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					case	'h':
						state = 3;
						break;
					default:
						state = 6;
						break;
				}
				break;
			case	3:
				switch (s[idx])
				{
					case	'e':
						state = 4;
						break;
					default:
						state = 6;
						break;
				}
				break;
			case	4:
				switch (s[idx])
				{
					case	'n':
						state = 5;
						break;
					default:
						state = 6;
						break;
				}
				break;
			case	5:
				switch (s[idx])
				{
					default:
						state = 6;
						break;
				}
				break;
			default:
				state = 6;
				break;
		}
		idx++;
	}
	if (state == 5)
	{
		return true;
	}
	return false;
}


bool match__else(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	'e':
						state = 2;
						break;
					default:
						state = 6;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					case	'l':
						state = 3;
						break;
					default:
						state = 6;
						break;
				}
				break;
			case	3:
				switch (s[idx])
				{
					case	's':
						state = 4;
						break;
					default:
						state = 6;
						break;
				}
				break;
			case	4:
				switch (s[idx])
				{
					case	'e':
						state = 5;
						break;
					default:
						state = 6;
						break;
				}
				break;
			case	5:
				switch (s[idx])
				{
					default:
						state = 6;
						break;
				}
				break;
			default:
				state = 6;
				break;
		}
		idx++;
	}
	if (state == 5)
	{
		return true;
	}
	return false;
}


bool match__end(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	'e':
						state = 2;
						break;
					default:
						state = 5;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					case	'n':
						state = 3;
						break;
					default:
						state = 5;
						break;
				}
				break;
			case	3:
				switch (s[idx])
				{
					case	'd':
						state = 4;
						break;
					default:
						state = 5;
						break;
				}
				break;
			case	4:
				switch (s[idx])
				{
					default:
						state = 5;
						break;
				}
				break;
			default:
				state = 5;
				break;
		}
		idx++;
	}
	if (state == 4)
	{
		return true;
	}
	return false;
}


bool match__repeat(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	'r':
						state = 4;
						break;
					default:
						state = 8;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					case	't':
						state = 3;
						break;
					default:
						state = 8;
						break;
				}
				break;
			case	3:
				switch (s[idx])
				{
					default:
						state = 8;
						break;
				}
				break;
			case	4:
				switch (s[idx])
				{
					case	'e':
						state = 5;
						break;
					default:
						state = 8;
						break;
				}
				break;
			case	5:
				switch (s[idx])
				{
					case	'p':
						state = 6;
						break;
					default:
						state = 8;
						break;
				}
				break;
			case	6:
				switch (s[idx])
				{
					case	'e':
						state = 7;
						break;
					default:
						state = 8;
						break;
				}
				break;
			case	7:
				switch (s[idx])
				{
					case	'a':
						state = 2;
						break;
					default:
						state = 8;
						break;
				}
				break;
			default:
				state = 8;
				break;
		}
		idx++;
	}
	if (state == 3)
	{
		return true;
	}
	return false;
}


bool match__until(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	'u':
						state = 3;
						break;
					default:
						state = 7;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					default:
						state = 7;
						break;
				}
				break;
			case	3:
				switch (s[idx])
				{
					case	'n':
						state = 4;
						break;
					default:
						state = 7;
						break;
				}
				break;
			case	4:
				switch (s[idx])
				{
					case	't':
						state = 5;
						break;
					default:
						state = 7;
						break;
				}
				break;
			case	5:
				switch (s[idx])
				{
					case	'i':
						state = 6;
						break;
					default:
						state = 7;
						break;
				}
				break;
			case	6:
				switch (s[idx])
				{
					case	'l':
						state = 2;
						break;
					default:
						state = 7;
						break;
				}
				break;
			default:
				state = 7;
				break;
		}
		idx++;
	}
	if (state == 2)
	{
		return true;
	}
	return false;
}


bool match__read(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	'r':
						state = 2;
						break;
					default:
						state = 6;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					case	'e':
						state = 3;
						break;
					default:
						state = 6;
						break;
				}
				break;
			case	3:
				switch (s[idx])
				{
					case	'a':
						state = 4;
						break;
					default:
						state = 6;
						break;
				}
				break;
			case	4:
				switch (s[idx])
				{
					case	'd':
						state = 5;
						break;
					default:
						state = 6;
						break;
				}
				break;
			case	5:
				switch (s[idx])
				{
					default:
						state = 6;
						break;
				}
				break;
			default:
				state = 6;
				break;
		}
		idx++;
	}
	if (state == 5)
	{
		return true;
	}
	return false;
}


bool match__write(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	'w':
						state = 3;
						break;
					default:
						state = 7;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					default:
						state = 7;
						break;
				}
				break;
			case	3:
				switch (s[idx])
				{
					case	'r':
						state = 4;
						break;
					default:
						state = 7;
						break;
				}
				break;
			case	4:
				switch (s[idx])
				{
					case	'i':
						state = 5;
						break;
					default:
						state = 7;
						break;
				}
				break;
			case	5:
				switch (s[idx])
				{
					case	't':
						state = 6;
						break;
					default:
						state = 7;
						break;
				}
				break;
			case	6:
				switch (s[idx])
				{
					case	'e':
						state = 2;
						break;
					default:
						state = 7;
						break;
				}
				break;
			default:
				state = 7;
				break;
		}
		idx++;
	}
	if (state == 2)
	{
		return true;
	}
	return false;
}


bool match__NUM(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	'0':
						state = 1;
						break;
					case	'1':
						state = 1;
						break;
					case	'2':
						state = 1;
						break;
					case	'3':
						state = 1;
						break;
					case	'4':
						state = 1;
						break;
					case	'5':
						state = 1;
						break;
					case	'6':
						state = 1;
						break;
					case	'7':
						state = 1;
						break;
					case	'8':
						state = 1;
						break;
					case	'9':
						state = 1;
						break;
					default:
						state = 2;
						break;
				}
				break;
			default:
				state = 2;
				break;
		}
		idx++;
	}
	if (state == 1)
	{
		return true;
	}
	return false;
}


bool match__add(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	'+':
						state = 2;
						break;
					default:
						state = 3;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					default:
						state = 3;
						break;
				}
				break;
			default:
				state = 3;
				break;
		}
		idx++;
	}
	if (state == 2)
	{
		return true;
	}
	return false;
}


bool match__minus(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	'-':
						state = 2;
						break;
					default:
						state = 3;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					default:
						state = 3;
						break;
				}
				break;
			default:
				state = 3;
				break;
		}
		idx++;
	}
	if (state == 2)
	{
		return true;
	}
	return false;
}


bool match__mul(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	'*':
						state = 2;
						break;
					default:
						state = 3;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					default:
						state = 3;
						break;
				}
				break;
			default:
				state = 3;
				break;
		}
		idx++;
	}
	if (state == 2)
	{
		return true;
	}
	return false;
}


bool match__div(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	'/':
						state = 2;
						break;
					default:
						state = 3;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					default:
						state = 3;
						break;
				}
				break;
			default:
				state = 3;
				break;
		}
		idx++;
	}
	if (state == 2)
	{
		return true;
	}
	return false;
}


bool match__mod(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	'%':
						state = 2;
						break;
					default:
						state = 3;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					default:
						state = 3;
						break;
				}
				break;
			default:
				state = 3;
				break;
		}
		idx++;
	}
	if (state == 2)
	{
		return true;
	}
	return false;
}


bool match__power(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	'^':
						state = 2;
						break;
					default:
						state = 3;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					default:
						state = 3;
						break;
				}
				break;
			default:
				state = 3;
				break;
		}
		idx++;
	}
	if (state == 2)
	{
		return true;
	}
	return false;
}


bool match__LP(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	'<':
						state = 2;
						break;
					default:
						state = 3;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					default:
						state = 3;
						break;
				}
				break;
			default:
				state = 3;
				break;
		}
		idx++;
	}
	if (state == 2)
	{
		return true;
	}
	return false;
}


bool match__NEQ(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	'<':
						state = 2;
						break;
					default:
						state = 4;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					case	'>':
						state = 3;
						break;
					default:
						state = 4;
						break;
				}
				break;
			case	3:
				switch (s[idx])
				{
					default:
						state = 4;
						break;
				}
				break;
			default:
				state = 4;
				break;
		}
		idx++;
	}
	if (state == 3)
	{
		return true;
	}
	return false;
}


bool match__LPE(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	'<':
						state = 2;
						break;
					default:
						state = 4;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					case	'=':
						state = 3;
						break;
					default:
						state = 4;
						break;
				}
				break;
			case	3:
				switch (s[idx])
				{
					default:
						state = 4;
						break;
				}
				break;
			default:
				state = 4;
				break;
		}
		idx++;
	}
	if (state == 3)
	{
		return true;
	}
	return false;
}


bool match__RPE(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	'>':
						state = 2;
						break;
					default:
						state = 4;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					case	'=':
						state = 3;
						break;
					default:
						state = 4;
						break;
				}
				break;
			case	3:
				switch (s[idx])
				{
					default:
						state = 4;
						break;
				}
				break;
			default:
				state = 4;
				break;
		}
		idx++;
	}
	if (state == 3)
	{
		return true;
	}
	return false;
}


bool match__RP(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	'>':
						state = 2;
						break;
					default:
						state = 3;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					default:
						state = 3;
						break;
				}
				break;
			default:
				state = 3;
				break;
		}
		idx++;
	}
	if (state == 2)
	{
		return true;
	}
	return false;
}


bool match__BEQ(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	'=':
						state = 2;
						break;
					default:
						state = 4;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					case	'=':
						state = 3;
						break;
					default:
						state = 4;
						break;
				}
				break;
			case	3:
				switch (s[idx])
				{
					default:
						state = 4;
						break;
				}
				break;
			default:
				state = 4;
				break;
		}
		idx++;
	}
	if (state == 3)
	{
		return true;
	}
	return false;
}


bool match__seg(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	';':
						state = 2;
						break;
					default:
						state = 3;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					default:
						state = 3;
						break;
				}
				break;
			default:
				state = 3;
				break;
		}
		idx++;
	}
	if (state == 2)
	{
		return true;
	}
	return false;
}


bool match__assign(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	':':
						state = 2;
						break;
					default:
						state = 4;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					case	'=':
						state = 3;
						break;
					default:
						state = 4;
						break;
				}
				break;
			case	3:
				switch (s[idx])
				{
					default:
						state = 4;
						break;
				}
				break;
			default:
				state = 4;
				break;
		}
		idx++;
	}
	if (state == 3)
	{
		return true;
	}
	return false;
}


bool match__ID(string s) 
{
	int idx = 0;
	int state = 2;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	'0':
						state = 1;
						break;
					case	'1':
						state = 1;
						break;
					case	'2':
						state = 1;
						break;
					case	'3':
						state = 1;
						break;
					case	'4':
						state = 1;
						break;
					case	'5':
						state = 1;
						break;
					case	'6':
						state = 1;
						break;
					case	'7':
						state = 1;
						break;
					case	'8':
						state = 1;
						break;
					case	'9':
						state = 1;
						break;
					case	'A':
						state = 1;
						break;
					case	'B':
						state = 1;
						break;
					case	'C':
						state = 1;
						break;
					case	'D':
						state = 1;
						break;
					case	'E':
						state = 1;
						break;
					case	'F':
						state = 1;
						break;
					case	'G':
						state = 1;
						break;
					case	'H':
						state = 1;
						break;
					case	'I':
						state = 1;
						break;
					case	'J':
						state = 1;
						break;
					case	'K':
						state = 1;
						break;
					case	'L':
						state = 1;
						break;
					case	'M':
						state = 1;
						break;
					case	'N':
						state = 1;
						break;
					case	'O':
						state = 1;
						break;
					case	'P':
						state = 1;
						break;
					case	'Q':
						state = 1;
						break;
					case	'R':
						state = 1;
						break;
					case	'S':
						state = 1;
						break;
					case	'T':
						state = 1;
						break;
					case	'U':
						state = 1;
						break;
					case	'V':
						state = 1;
						break;
					case	'W':
						state = 1;
						break;
					case	'X':
						state = 1;
						break;
					case	'Y':
						state = 1;
						break;
					case	'Z':
						state = 1;
						break;
					case	'a':
						state = 1;
						break;
					case	'b':
						state = 1;
						break;
					case	'c':
						state = 1;
						break;
					case	'd':
						state = 1;
						break;
					case	'e':
						state = 1;
						break;
					case	'f':
						state = 1;
						break;
					case	'g':
						state = 1;
						break;
					case	'h':
						state = 1;
						break;
					case	'i':
						state = 1;
						break;
					case	'j':
						state = 1;
						break;
					case	'k':
						state = 1;
						break;
					case	'l':
						state = 1;
						break;
					case	'm':
						state = 1;
						break;
					case	'n':
						state = 1;
						break;
					case	'o':
						state = 1;
						break;
					case	'p':
						state = 1;
						break;
					case	'q':
						state = 1;
						break;
					case	'r':
						state = 1;
						break;
					case	's':
						state = 1;
						break;
					case	't':
						state = 1;
						break;
					case	'u':
						state = 1;
						break;
					case	'v':
						state = 1;
						break;
					case	'w':
						state = 1;
						break;
					case	'x':
						state = 1;
						break;
					case	'y':
						state = 1;
						break;
					case	'z':
						state = 1;
						break;
					default:
						state = 3;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					case	'A':
						state = 1;
						break;
					case	'B':
						state = 1;
						break;
					case	'C':
						state = 1;
						break;
					case	'D':
						state = 1;
						break;
					case	'E':
						state = 1;
						break;
					case	'F':
						state = 1;
						break;
					case	'G':
						state = 1;
						break;
					case	'H':
						state = 1;
						break;
					case	'I':
						state = 1;
						break;
					case	'J':
						state = 1;
						break;
					case	'K':
						state = 1;
						break;
					case	'L':
						state = 1;
						break;
					case	'M':
						state = 1;
						break;
					case	'N':
						state = 1;
						break;
					case	'O':
						state = 1;
						break;
					case	'P':
						state = 1;
						break;
					case	'Q':
						state = 1;
						break;
					case	'R':
						state = 1;
						break;
					case	'S':
						state = 1;
						break;
					case	'T':
						state = 1;
						break;
					case	'U':
						state = 1;
						break;
					case	'V':
						state = 1;
						break;
					case	'W':
						state = 1;
						break;
					case	'X':
						state = 1;
						break;
					case	'Y':
						state = 1;
						break;
					case	'Z':
						state = 1;
						break;
					case	'a':
						state = 1;
						break;
					case	'b':
						state = 1;
						break;
					case	'c':
						state = 1;
						break;
					case	'd':
						state = 1;
						break;
					case	'e':
						state = 1;
						break;
					case	'f':
						state = 1;
						break;
					case	'g':
						state = 1;
						break;
					case	'h':
						state = 1;
						break;
					case	'i':
						state = 1;
						break;
					case	'j':
						state = 1;
						break;
					case	'k':
						state = 1;
						break;
					case	'l':
						state = 1;
						break;
					case	'm':
						state = 1;
						break;
					case	'n':
						state = 1;
						break;
					case	'o':
						state = 1;
						break;
					case	'p':
						state = 1;
						break;
					case	'q':
						state = 1;
						break;
					case	'r':
						state = 1;
						break;
					case	's':
						state = 1;
						break;
					case	't':
						state = 1;
						break;
					case	'u':
						state = 1;
						break;
					case	'v':
						state = 1;
						break;
					case	'w':
						state = 1;
						break;
					case	'x':
						state = 1;
						break;
					case	'y':
						state = 1;
						break;
					case	'z':
						state = 1;
						break;
					default:
						state = 3;
						break;
				}
				break;
			default:
				state = 3;
				break;
		}
		idx++;
	}
	if (state == 1)
	{
		return true;
	}
	return false;
}


bool match__doc(string s) 
{
	int idx = 0;
	int state = 1;
	while (idx < s.length())
	{
		switch (state)
		{
			case	1:
				switch (s[idx])
				{
					case	'{':
						state = 2;
						break;
					default:
						state = 4;
						break;
				}
				break;
			case	2:
				switch (s[idx])
				{
					case	' ':
						state = 2;
						break;
					case	'/':
						state = 2;
						break;
					case	'1':
						state = 2;
						break;
					case	'2':
						state = 2;
						break;
					case	'3':
						state = 2;
						break;
					case	'4':
						state = 2;
						break;
					case	'5':
						state = 2;
						break;
					case	'6':
						state = 2;
						break;
					case	'7':
						state = 2;
						break;
					case	'8':
						state = 2;
						break;
					case	'9':
						state = 2;
						break;
					case	'A':
						state = 2;
						break;
					case	'B':
						state = 2;
						break;
					case	'C':
						state = 2;
						break;
					case	'D':
						state = 2;
						break;
					case	'E':
						state = 2;
						break;
					case	'F':
						state = 2;
						break;
					case	'G':
						state = 2;
						break;
					case	'H':
						state = 2;
						break;
					case	'I':
						state = 2;
						break;
					case	'J':
						state = 2;
						break;
					case	'K':
						state = 2;
						break;
					case	'L':
						state = 2;
						break;
					case	'M':
						state = 2;
						break;
					case	'N':
						state = 2;
						break;
					case	'O':
						state = 2;
						break;
					case	'P':
						state = 2;
						break;
					case	'Q':
						state = 2;
						break;
					case	'R':
						state = 2;
						break;
					case	'S':
						state = 2;
						break;
					case	'T':
						state = 2;
						break;
					case	'U':
						state = 2;
						break;
					case	'V':
						state = 2;
						break;
					case	'W':
						state = 2;
						break;
					case	'X':
						state = 2;
						break;
					case	'Y':
						state = 2;
						break;
					case	'Z':
						state = 2;
						break;
					case	'a':
						state = 2;
						break;
					case	'b':
						state = 2;
						break;
					case	'c':
						state = 2;
						break;
					case	'd':
						state = 2;
						break;
					case	'e':
						state = 2;
						break;
					case	'f':
						state = 2;
						break;
					case	'g':
						state = 2;
						break;
					case	'h':
						state = 2;
						break;
					case	'i':
						state = 2;
						break;
					case	'j':
						state = 2;
						break;
					case	'k':
						state = 2;
						break;
					case	'l':
						state = 2;
						break;
					case	'm':
						state = 2;
						break;
					case	'n':
						state = 2;
						break;
					case	'o':
						state = 2;
						break;
					case	'p':
						state = 2;
						break;
					case	'q':
						state = 2;
						break;
					case	'r':
						state = 2;
						break;
					case	's':
						state = 2;
						break;
					case	't':
						state = 2;
						break;
					case	'u':
						state = 2;
						break;
					case	'v':
						state = 2;
						break;
					case	'w':
						state = 2;
						break;
					case	'x':
						state = 2;
						break;
					case	'y':
						state = 2;
						break;
					case	'z':
						state = 2;
						break;
					case	'}':
						state = 3;
						break;
					default:
						state = 4;
						break;
				}
				break;
			case	3:
				switch (s[idx])
				{
					default:
						state = 4;
						break;
				}
				break;
			default:
				state = 4;
				break;
		}
		idx++;
	}
	if (state == 3)
	{
		return true;
	}
	return false;
}

unordered_map<string, int> tokenTypeMap;
vector<string> tokenTypes;
vector<string> tokenStrings;
vector<char> readChars;
set<char> ignoreChar = {'\n', ' '};
set<string> ignoreOutputTokenType = {"_doc"};
int idx;
string readFilePath = "./joint_test.txt";
string outPutPath = "./output.txt";
bool couldBeMoreLonger(string s){
		return 
			match__if(s)||

			match__then(s)||

			match__else(s)||

			match__end(s)||

			match__repeat(s)||

			match__until(s)||

			match__read(s)||

			match__write(s)||

			match__NUM(s)||

			match__add(s)||

			match__minus(s)||

			match__mul(s)||

			match__div(s)||

			match__mod(s)||

			match__power(s)||

			match__LP(s)||

			match__NEQ(s)||

			match__LPE(s)||

			match__RPE(s)||

			match__RP(s)||

			match__BEQ(s)||

			match__seg(s)||

			match__assign(s)||

			match__ID(s)||

			match__doc(s);
}
void readFileFull(string filePath)
{
    string data;
    ifstream ifs(filePath);
    while (std::getline(ifs, data)) // ifs，进行getLine的读取方式会省略换行符
    {
        for(int i=0;i<data.size();i++)
        {
            readChars.push_back(data[i]);
        }
    }
    ifs.close();
}
void outPutFile()
{
	try
	{
		ofstream ofs(outPutPath);
		for (int i = 0; i < tokenTypes.size(); i++)
		{
			if (ignoreOutputTokenType.find(tokenTypes[i]) == ignoreOutputTokenType.end())
			{
				ofs << tokenTypes[i] << '\n';
			}
// 			ofs << tokenStrings[i] << "\n";
		}
		ofs.close();
	}
	catch (const std::exception &e)
	{
	std::cerr << e.what() << endl;
	}
}

char getOneLetter()
{
    if (idx >= readChars.size())
    {
        return -1; // 阅读结束
    }
    char retChar = readChars[idx];
    idx = idx + 1;
    return retChar;
}

void backOneLetter()
{
    // 拒绝回退
    if (idx == 0)
    {
        return;
    }
    else
    {
        idx = idx - 1;
    }
}

int getTokenType()
{
	// 初始化
	readFileFull(readFilePath);
	char c;
	string s;
	string currTokenType = "NONE";
	while ((c = getOneLetter()) != -1)
	{
		// 不进行读入
		if (ignoreChar.find(c) != ignoreChar.end())
		{
			continue;
		}

		s.push_back(c);

		if(match__if(s))
		{
			currTokenType = "_if";
		}
		else if (match__then(s))
		{
			currTokenType ="_then";
		}
		else if (match__else(s))
		{
			currTokenType ="_else";
		}
		else if (match__end(s))
		{
			currTokenType ="_end";
		}
		else if (match__repeat(s))
		{
			currTokenType ="_repeat";
		}
		else if (match__until(s))
		{
			currTokenType ="_until";
		}
		else if (match__read(s))
		{
			currTokenType ="_read";
		}
		else if (match__write(s))
		{
			currTokenType ="_write";
		}
		else if (match__NUM(s))
		{
			currTokenType ="_NUM";
		}
		else if (match__add(s))
		{
			currTokenType ="_add";
		}
		else if (match__minus(s))
		{
			currTokenType ="_minus";
		}
		else if (match__mul(s))
		{
			currTokenType ="_mul";
		}
		else if (match__div(s))
		{
			currTokenType ="_div";
		}
		else if (match__mod(s))
		{
			currTokenType ="_mod";
		}
		else if (match__power(s))
		{
			currTokenType ="_power";
		}
		else if (match__LP(s))
		{
			currTokenType ="_LP";
		}
		else if (match__NEQ(s))
		{
			currTokenType ="_NEQ";
		}
		else if (match__LPE(s))
		{
			currTokenType ="_LPE";
		}
		else if (match__RPE(s))
		{
			currTokenType ="_RPE";
		}
		else if (match__RP(s))
		{
			currTokenType ="_RP";
		}
		else if (match__BEQ(s))
		{
			currTokenType ="_BEQ";
		}
		else if (match__seg(s))
		{
			currTokenType ="_seg";
		}
		else if (match__assign(s))
		{
			currTokenType ="_assign";
		}
		else if (match__ID(s))
		{
			currTokenType ="_ID";
		}
		else if (match__doc(s))
		{
			currTokenType ="_doc";
		}
		// 检测能否更多的字符
		if (currTokenType != "NONE")
		{
			c = getOneLetter();// 其实这里的c保留分隔符，就是完成了空格截断
			if (c != -1) // 不为-1时刻加入，检测回退
			{
				s.push_back(c);
				bool couldMore = couldBeMoreLonger(s);
				// 不为-1时刻回退
				// 回退
				s.pop_back();
				backOneLetter();
				if(couldMore)
				{
					continue;
				}
			}
			tokenTypes.push_back(currTokenType);
			tokenStrings.push_back(s);
			currTokenType="NONE";
			s.clear();
		}
	}
		if(!s.empty()){
			tokenTypes.push_back("NONE");
			tokenStrings.push_back("NONE");
		}
	return 0;
}
int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		readFilePath = string(argv[1]);
		outPutPath = string(argv[2]);
	}
	getTokenType();
	outPutFile();
}
