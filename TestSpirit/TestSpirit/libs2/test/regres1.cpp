#include <spirit/Spirit.h>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////////////////
using std::cout;
using std::cin;
using std::endl;

using Spirit::Scanner;
using Spirit::space;
using Spirit::Rule;
using Spirit::str_p;
using Spirit::ncstr_p;
using Spirit::range_p;
using Spirit::ncrange_p;
using Spirit::ch_p;
using Spirit::ncch_p;
using Spirit::anychar;
using Spirit::xdigit;
using Spirit::digit;
using Spirit::alpha;
using Spirit::more;
using Spirit::Longest;

/////////////////////////////////////////////////////////////////////////////////////////
static void
Parse(Rule<> const& rule, char const* expr)
{
	Scanner<>	scan(expr, space);
	if (rule.Parse(scan) && !*scan)
	{
		cout << "\t\t" << expr << "\tPass\n";
	}
	else
	{
		cout << "\t\t" << expr << "\tFail\n";
		cout << "\t\t";
		for (int i = 0; i < (&*scan - expr); i++)
			cout << " ";
		cout << "^\n";
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
int
main()
{
	cout << "/////////////////////////////////////////////////////////\n\n";
	cout << "\t\tPattern Test For Spirit...\n\n";
	cout << "/////////////////////////////////////////////////////////\n\n";

	cout << "strings\n\n";
	Rule<>	str = str_p("joel");
	Parse(str, "joel");
	Parse(str, "joelo");
	Parse(str, "joal");
	Parse(str, "joe");
	cout << "\n";

	cout << "no case strings\n\n";
	Rule<>	ncstr = ncstr_p("joel");
	Parse(ncstr, "joel");
	Parse(ncstr, "JOEL");
	Parse(ncstr, "joAl");
	Parse(ncstr, "JoEl");
	cout << "\n";

	cout << "any >> string\n\n";
	Rule<>	any = anychar >> str_p("art");
	Parse(any, "dart");
	Parse(any, "cart");
	Parse(any, "tart");
	Parse(any, "art");
	Parse(any, "hurt");
	Parse(any, "dark");
	cout << "\n";

	cout << "one or more\n\n";
	Rule<>	onem = +ch_p('a') >> 'b';
	Parse(onem, "ab");
	Parse(onem, "aaab");
	Parse(onem, "b");
	Parse(onem, "baaa");
	cout << "\n";

	cout << "zero or more\n";
	Rule<>	zerom = *ch_p('a') >> 'b';
	Parse(zerom, "b");
	Parse(zerom, "ab");
	Parse(zerom, "aaab");
	Parse(zerom, "baaa");
	cout << "\n";

	cout << "repeat\n";
	Rule<>	rep1 = +(ncrange_p('a','z') | range_p('0','9'));
	Rule<>	rep2 = +(str_p("abc"));
	Parse(rep1, "aaaaaa");
	Parse(rep2, "abcabcabcabc");
	Parse(rep2, "abcabcabcabcc");
	cout << "\n";

	cout << "any and repeat\n";
	Rule<>	anyrep = *str_p("fo") >> *ch_p('o') >> *(anychar - '\0');
	Parse(anyrep, "fo");
	Parse(anyrep, "foo");
	Parse(anyrep, "fooo");
	Parse(anyrep, "foobar");
	Parse(anyrep, "foox");
	cout << "\n";

	cout << "sequence\n";
	Rule<>	seq = *ncstr_p("0x") >> +xdigit;
	Parse(seq, "0x3FFF");
	Parse(seq, "0x3GFF");
	cout << "\n";

	cout << "optional\n";
	Rule<>	opt = +digit >> '.' >> +digit >> !(ncch_p('e') >> +digit);
	Parse(opt, "3.666");
	Parse(opt, "3.666e25");
	Parse(opt, "3.6A6");
	cout << "\n";

	cout << "or\n";
	Rule<>	alt = str_p("joel") | str_p("mariel");
	Parse(alt, "joel");
	Parse(alt, "mariel");
	Parse(alt, "tenji");
	cout << "\n";

	cout << "and\n";
	Rule<>	and_ = +((anychar - '\0') & 'x');
	Parse(and_, "xxxxxxxxxx");
	Parse(and_, "xxxxxaxxxx");
	Parse(and_, "aaaaaaa");
	cout << "\n";

	cout << "diff\n";
	Rule<>	diff = +(alpha - 'a');
	Parse(diff, "abcdefg");
	Parse(diff, "bcdefgh");
	cout << "\n";

	cout << "xor\n";
	Rule<>	xor_ = alpha ^ xdigit;
	Parse(xor_, "0");
	Parse(xor_, "1");
	Parse(xor_, "2");
	Parse(xor_, "3");
	Parse(xor_, "4");
	Parse(xor_, "5");
	Parse(xor_, "6");
	Parse(xor_, "7");
	Parse(xor_, "8");
	Parse(xor_, "9");
	Parse(xor_, "a");
	Parse(xor_, "b");
	Parse(xor_, "c");
	Parse(xor_, "d");
	Parse(xor_, "e");
	Parse(xor_, "f");
	Parse(xor_, "g");
	Parse(xor_, "h");
	Parse(xor_, "i");
	cout << "\n";
	
	cout << "repeat exact 8\n";
	Rule<>	rep8 = alpha.Repeat(8);
	Parse(rep8, "abcdefg");
	Parse(rep8, "abcdefgh");
	Parse(rep8, "abcdefghi");
	Parse(rep8, "abcdefg");
	Parse(rep8, "a");

	cout << "repeat 2 to 8\n";
	Rule<>	rep28 = alpha.Repeat(2, 8);
	Parse(rep28, "abcdefg");
	Parse(rep28, "abcdefgh");
	Parse(rep28, "abcdefghi");
	Parse(rep28, "abcdefg");
	Parse(rep28, "a");

	cout << "repeat 2 or more\n";
	Rule<>	rep2_ = alpha.Repeat(2, more);
	Parse(rep2_, "abcdefg");
	Parse(rep2_, "abcdefgh");
	Parse(rep2_, "abcdefghi");
	Parse(rep2_, "abcdefg");
	Parse(rep2_, "a");

	cout << "longest parse\n";
	Rule<>	real = +digit >> '.' >> +digit;
	Rule<>	integ = +digit;
	Rule<>	num = Longest[ integ | real ];
	Parse(num, "123456");
	Parse(num, "456.1245");
	Parse(num, "123456A");


	cout << "Back Tracking\n";
	Rule<>	b = ch_p('B');
	Rule<>	a = ch_p('A') >> ( ch_p('B') | 'D' ) >> 'E' >> 'F' >> 'H' 
			| 'A' >> b >> 'E' >> 'G' >> 'H';


	cout << "\tShould parse OK...\n";
	Parse(a, "ABEFH");
	Parse(a, "ADEFH");
	Parse(a, "ABEGH");
	cout << "\n";

	cout << "\tShould fail parsing...\n";
	Parse(a, "AEFH");
	Parse(a, "ADEGH");

	return 0;
}


