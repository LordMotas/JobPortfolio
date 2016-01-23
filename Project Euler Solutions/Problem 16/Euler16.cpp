/*
Project Euler #16
Problem Statement:

2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2^1000?

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string itostring(int a)
{
	std::ostringstream oss;
	oss << a;
	return oss.str();
}



class StrInt
{
public:
	// ctor... from string ...
	StrInt(const std::string& s = "0") : snum(s)
	{
		trim(snum); validate(snum); normalize();
	}

	// ctor from int ...
	StrInt(int s) : snum(itostring(s)) {}

	void showData()
	{
		int count = 0;
		int i = snum.size();
		while (i && snum[--i] == '0') ++count;
		std::cout << "size = " << snum.size()
			<< ", end zeros = " << count;
	}

	void total(){
		auto total = 0;
		for (int i = 0; i < snum.size(); i++){
			total += snum[i] - '0';
		}
		std::cout << "The answer is: " << total << std::endl;
	}

private:
	std::string snum;
	void normalize()
	{
		//now called in ctor ...
		//trim( snum ); // trim off all leading and trailing whitespaces ...

		/*  // now ... validate is done in ctor ...
		int len = snum.size();
		for( int i = 0; i < len; ++i ) // if not a valid integer ... set to "0"
		if( snum[i] < '0' || '9' < snum[i] )
		{ snum = "0"; len = 1; break; }
		*/

		// erase leading zeros ... but NOT last zero
		int i = 0, j = snum.size() - 1;
		while (i < j && snum[i] == '0') ++i;
		snum.erase(0, i);
	}

	// if not a valid integer ... set to "0"
	static bool validate(std::string& s)
	{
		int len = s.size();
		for (int i = 0; i < len; ++i)
			if (s[i] < '0' || '9' < s[i])
			{
				s = "0";  return false;
			}
		return true;
	}

	// trim leading and trailing whitespaces from 's' ... and return by 'ref.'
	static void trim(std::string& s, const std::string t = " \t") // default whitespace: "\t "
	{
		size_t p1 = s.find_first_not_of(t); // get index of 'first char' ...
		if (std::string::npos != p1) // ok ... not all ws ... nor empty ... so can safely
		{
			s.erase(0, p1);
			size_t p2 = s.find_last_not_of(t); // get index of 'last char' ...
			s.erase(p2 + 1);
		}
		else // ... all was whitespace ... or was empty
			s.clear();
	}

	friend std::ostream& operator << (std::ostream& os, const StrInt& s)
	{
		return os << s.snum;
	}

	friend char sumof(const StrInt& a, int len1, const StrInt& b, int len2, int& carry)
	{
		int sum = a.snum[len1] - '0' + b.snum[len2] - '0' + carry;
		if (sum > 9) { sum -= 10; carry = 1; }
		else carry = 0;
		return char('0' + sum);
	}
	friend char sumof(const StrInt& s, int len, int& carry)
	{
		int sum = s.snum[len] - '0' + carry;
		if (sum > 9) { sum -= 10; carry = 1; }
		else carry = 0;
		return char('0' + sum);
	}

	// uses both friend functions above ...
	friend StrInt operator + (const StrInt& a, const StrInt& b)
	{
		int len1 = a.snum.size();
		int len2 = b.snum.size();
		int ml = (len1 > len2 ? len1 : len2);
		StrInt s;
		s.snum.resize(ml);

		int carry = 0;

		while (len1 && len2)
			s.snum[--ml] = sumof(a, --len1, b, --len2, carry);

		if (len1)
			while (len1)
				s.snum[--ml] = sumof(a, --len1, carry);
		else if (len2)
			while (len2)
				s.snum[--ml] = sumof(b, --len2, carry);

		if (carry)
			s.snum = "1" + s.snum;

		return s;
	}

	friend char productof(int a, const StrInt& b, int len2, int& carry)
	{
		int sum = a * (b.snum[len2] - '0') + carry;
		if (sum > 9) { carry = sum / 10; sum = sum % 10; }
		else carry = 0;
		return char('0' + sum);
	}
	friend StrInt operator * (int a, const StrInt& b)
	{
		int len2 = b.snum.size();
		StrInt s;
		s.snum.resize(len2);

		int carry = 0;

		while (len2--)
			s.snum[len2] = productof(a, b, len2, carry);

		if (carry)
			s.snum = char('0' + carry) + s.snum;

		s.normalize();
		return s;
	}

	// uses both friend functions above ...
	friend StrInt operator * (const StrInt& a, const StrInt& b)
	{
		int len1 = a.snum.size();
		StrInt s;
		while (len1--)
		{
			StrInt n = (a.snum[len1] - '0') * b;
			n.normalize();
			if (n.snum != "0")
			{
				/*
				for( int i = a.snum.size()-1-len1; i > 0; --i )
				n = 10*n;
				*/
				int shiftLeft = a.snum.size() - 1 - len1;
				if (shiftLeft > 0)
					n.snum += std::string(shiftLeft, '0');
			}

			s = s + n;
		}

		return s;
	}
};




int main()
{
	StrInt s("1");

	for (int i = 0; i < 1000; i++){
		s = s * 2;
	}

	std::cout << s << std::endl << std::endl;

	s.total();
	


	system("Pause");
	return 0;

}