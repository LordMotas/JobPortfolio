/*

Project Euler #48
Problem Statement:
The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.

Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.

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

int main(){

	std::string lastTenDigits;
	StrInt runningTotal("368199144695177095375011227646795567793680622934654583760988100234910747716194381428659099527845945869942643191290894720342979906407679647259860434238468038326040809691037615370376237713648510063115732951461774246705584266865759601815843666442832284556880313114548151539190975398485496645576513465858582712336401166221956188173449531674102688908321764663020306699770408625340766091595022791379368098369306375602813856646358773751558775213460225796579846583334007349358624342339332981334571237888809283103348760261360175950815609179464026871005243652109980863552142014242903434068560936573231079342194031864413918101238151056509267393515760392842472501391594073463001521843811073767021711026307504695733467897821866906648469828346607412967395801797791683609834722432241952845352564681868240369569566192825555323558078061997527689983848863374786789331581565252059172614339424600986143259233167583371070362625554531852054166117148858229508581589614337594463277554380518380921301218836327102231407332201109740102580216469298331766920619646083790732807627360614428085171565006289728508688964226799647192582924058589530750674578385365561878559589685756225692348914746922810913915619834754117648358035814128670294158565669942087736286390942241547226015004471330630113072042704288905042142628193771918594574302202147201188486345913190833752307476966010547423928871063118783026036381319039052008252072057933666712918946233312793697094074224187872045970976444309242782187738320257490080824330074991698698239561125811127607863900355221737846690567707344074494145266662103839812840216303448476913957072355732716627098372245223046792919747259113157425824064858331415400943278213042954635053574045209984512221264241903550178416824551412548637590007779082539288247751653566899882749594405895102587985539527709493510049546445427265617478399107188238681771215904234119392247489751079085948055945098805617963722928469554263782217625160428008228845552540344494860195267115187092227766195753907211126646150140614744233974765273475619964311852858614167819668340124730487710162006793529985758820653677274379563313495454526632718723482339494825759821076401694316043456512117937935456463521463021197726694983558929132357576188594977516630734212863869456164205525536767311298137182511494649463663073759219213056823561667776093739425742883930712609962163464088038826569132032160692637206183085942987973684584276491784843115472077900401692595694119273553511025991265446039366288921743581333200083717105241171504606883543418862024047552177055263424469501298905901938158245938633694105024815166679813689156668341197713475094389904887126794468901893850475050011205225742455555625750560213230387910337983950333245020653238989115507013882956277763880795687210857196493893142656713105966275422144605988058939600603604226921401402096519294250488670297983396353279460453142375542267881989197481789780678955093763193658603690898474826976906544473978017455720367929981796023041785852626797271283465789498383642350667978127819110846700");
	/*for (int i = 980; i < 1000; i++){
 		StrInt exponentTotal("1");
		for (int j = 1; j <= i; j++){
			exponentTotal = exponentTotal * i;
		}
		runningTotal = runningTotal + exponentTotal;
	}*/
	std::cout << "The answer is: " << runningTotal << std::endl;
	system("Pause");
	return 0;
}