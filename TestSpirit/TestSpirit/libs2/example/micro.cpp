#include <spirit/Spirit.h>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////////////////
using std::cout;
using std::cin;
using std::endl;

using Spirit::Scanner;
using Spirit::space;
using Spirit::real_p;

/////////////////////////////////////////////////////////////////////////////////////////
int
main()
{
	cout << "/////////////////////////////////////////////////////////\n\n";
	cout << "\t\tMicro Parser Test For Spirit...\n\n";
	cout << "/////////////////////////////////////////////////////////\n\n";

	cout << "Give me a complex number of the form r or (r) or (r,i) \n";
	cout << "Type [q or Q] to quit\n\n";

	while (true)
	{
		char str[256];
		cin.getline(str, 256);
		if (str[0] == 'q' || str[0] == 'Q')
			break;

		Scanner<>	scan(str, space);
		double		r = 0;
		double		i = 0;
		
		bool	match = 
			(	real_p(r)
			| 	'(' >> real_p(r) >> !(',' >> real_p(i)) >> ')'
			).Parse(scan);
		
		if (match && !*scan)
		{
			cout << endl;
			cout << "\t\t" << str << " Parses OK\n";
			cout << "r = " << r << "\n";
			cout << "i = " << i << "\n\n";
		}
		else
		{
			cout << endl;
			cout << "\t\t" << str << " Fails Parsing\n";
			cout << "\t\t";
			for (int i = 0; i < (&*scan - str); i++)
				cout << " ";
			cout << "^--Here\n\n\n";
		}
	}
	
	cout << "Bye... :-) \n\n";

	return 0;
}


