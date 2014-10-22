#include <spirit/Spirit.h>
#include <iostream>

using Spirit::Rule;
using Spirit::ChLit;
using Spirit::Range;
using Spirit::anychar;
using Spirit::alpha;
using Spirit::alnum;
using Spirit::digit;
using Spirit::xdigit;
using Spirit::StrLit;
using Spirit::nothing;

using std::cout;

static void
Parse(Rule<> const& rule, char const* expr)
{
	cout << "/////////////////////////////////////////////////////////\n\n";

	char const* scan = expr;
	if (rule.Parse(scan) && !*scan)
	{
		cout << "\t\t" << expr << " Parses OK\n\n\n";
	}
	else
	{
		cout << "\t\t" << expr << " Fails Parsing\n";
		cout << "\t\t";
		for (int i = 0; i < (&*scan - expr); i++)
			cout << " ";
		cout << "^--Here\n\n\n";
	}
}

int
main()
{

	// Start grammar definition
	Rule<>	prolog, element, Misc, Letter, Digit, CombiningChar, Extender, Reference, 
				CData, doctypedecl, XMLDecl, SDDecl, VersionInfo, EncodingDecl,
				VersionNum, Eq, EmptyElemTag, STag, content, ETag, Attribute, 
				AttValue, CharDataChar, CharData, Comment, CDSect,
				CharRef, EntityRef, EncName, BaseChar, document, Char, S, NameChar, Name;

	ChLit<>	Percent('%');
	ChLit<>	Ampersand('&');
	ChLit<>	DblQuote('"');
	ChLit<>	Quote('\'');
	ChLit<>	LessThan('<');

	ChLit<>	x9('\x9');
	ChLit<>	xA('\xA');
	ChLit<>	xD('\xD');
	Range<unsigned char>	x20xFF('\x20', '\xFF');
	ChLit<>	x20('\x20');

	// This is the start rule for XML
	document = 		prolog >> element >> *Misc;
	Char = 			x9 | xA | xD | x20xFF;

	S = 				+(x20 | x9 | xD | xA);

	NameChar = 		Letter | Digit | '.' | '-' | '_' | ':' | CombiningChar | Extender;
	Name = 			(Letter | '_' | ':') >> *(NameChar);

	AttValue = 		'"' >> *((anychar - (LessThan | Ampersand | DblQuote)) | Reference) 
							>> '"' 
						| '\'' >> *((anychar - (LessThan | Ampersand | Quote)) | Reference) 
							>> '\'';

	CharDataChar = anychar - (LessThan | Ampersand);
	CharData =		*(CharDataChar - "]]>");

	Comment =		"<!--" >> *((Char - '-') | ('-' >> (Char - '-'))) >> "-->";

	CDSect =			"<![CDATA[" >> CData >> "]]>";
	CData =			*(Char - "]]>");

	prolog =			!XMLDecl >> *Misc >> !(doctypedecl >> *Misc);
	XMLDecl =		"<?xml" >> VersionInfo >> !EncodingDecl >> !SDDecl >> !S >> "?>";
	VersionInfo =	S >> "version" >> Eq >> (Quote >> VersionNum >> Quote 
							| DblQuote >> VersionNum >> DblQuote);
	Eq =				!S >> '=' >> !S;
	VersionNum =	+(alnum | '_' | '.' | ':' | '-');
	Misc =			Comment | S;

	doctypedecl =	"<!DOCTYPE" >> *(Char - (ChLit<>('[') | '>')) >> !('[' >> *(Char - ']') >> ']') >> '>';

	SDDecl =			S >> "standalone" >> Eq >> ((Quote >> (StrLit<>("yes") | "no") >> Quote)
							| (DblQuote >> (StrLit<>("yes") | "no") >> DblQuote));

	element =		EmptyElemTag
						| STag >> content >> ETag;

	STag =			'<' >> Name >> *(S >> Attribute) >> !S >> '>';
	Attribute =		Name >> Eq >> AttValue;
	ETag =			"</" >> Name >> !S >> '>';
	content =		!CharData >> *((element | Reference | CDSect | Comment) >> !CharData);
	EmptyElemTag =	'<' >> Name >> *(S >> Attribute) >> !S >> "/>";

	CharRef =		"&#" >> +digit >> ';'
						| "&#x" >> +xdigit >> ';';

	Reference =		EntityRef | CharRef;
	EntityRef =		'&' >> Name >> ';';

	EncodingDecl =	S >> "encoding" >> Eq >> (DblQuote >> EncName >> DblQuote | 
							Quote >> EncName >> Quote);
	EncName =		alpha >> *(alnum | '.' | '_' | '-');


	Letter = 		BaseChar;// | Ideographic;
	BaseChar =		Range<unsigned char>('\x41', '\x5A') | Range<unsigned char>('\x61', '\x7A')
						| Range<unsigned char>('\xC0', '\xD6') | Range<unsigned char>('\xD8', '\xF6')
						| Range<unsigned char>('\xF8', '\xFF');

	// Ideographic =
	CombiningChar =	nothing;
	Digit =			digit;
	Extender =		ChLit<unsigned char>('\xB7');





	Parse(document, "<?xml version=\"1.0\" encoding=\"UTF-8\" ?><!DOCTYPE greeting [<!ELEMENT "
			"greeting (#PCDATA)>]><greeting>Hello, world!</greeting>");
	Parse(document, "<!-- declarations for <head> & <body> -->");
	Parse(document, "<?xml version=\"1.0\" encoding=\"UTF-8\" ?><!DOCTYPE greeting [<!ELEMENT "
			"greeting (#PCDATA)>]><greeting>Hello, world!</greeting><!-- declarations for <head> & "
			"<body> -->");
	Parse(document, "<?xml version=\"1.0\" encoding=\"UTF-8\" ?><!DOCTYPE greeting [<!ELEMENT "
			"greeting (#PCDATA)>]><greeting>Hello, world!</greeting><!-- B+, B, or B--->");
			
	Parse(CDSect, "<![CDATA[<greeting>Hello, world!</greeting>]]>");
	Parse(document, "<?xml version=\"1.0\" encoding=\"UTF-8\" ?><!DOCTYPE greeting [<!ELEMENT "
			"greeting (#PCDATA)>]><greeting>Hello, world!<![CDATA[<greeting>Hello, world!"
			"</greeting>]]></greeting>");
	
	Parse(document, "<?xml version=\"1.0\" encoding=\"UTF-8\" ?><!DOCTYPE greeting [<!ELEMENT "
			"greeting (#PCDATA)>]><![CDATA[<greeting>Hello, world!</greeting>]]>");
	Parse(document, "<?xml version=\"1.0\"?> <greeting>Hello, world!</greeting>");
	Parse(document, "<greeting>Hello, world!</greeting>");
	Parse(document, "<?xml version=\"1.0\"?> <!DOCTYPE greeting SYSTEM \"hello.dtd\"> <greeting>"
			"Hello, world!</greeting>");
	Parse(document, "<?xml version=\"1.0\" standalone='yes'?> <greeting>Hello, world!</greeting>");
	Parse(document, "<?xml version=\"1.0\" standalone='yes'?> <!DOCTYPE greeting SYSTEM \"hello.dtd\">"
		  " <greeting>Hello, world!</greeting>");
	Parse(document, 	"<?xml version=\"1.0\" encoding=\"ISO8859-1\" ?>"
							"<note>"
			  					"<to>Tove</to>"
								"<from>Jani</from>"
								"<heading>Reminder</heading>"
								"<body>Don't forget me this weekend!</body>"
							"</note>" );
	
	Parse(document, 	"<?xml version=\"1.0\"?>"
							"<!DOCTYPE note ["
								"<!ELEMENT note    (to,from,heading,body)>"
								"<!ELEMENT to      (#PCDATA)>"
								"<!ELEMENT from    (#PCDATA)>"
								"<!ELEMENT heading (#PCDATA)>"
								"<!ELEMENT body    (#PCDATA)>"
							"]>"
							"<note>"
								"<to>Tove</to>"
								"<from>Jani</from>"
								"<heading>Reminder</heading>"
						 		"<body>Don't forget me this weekend!</body>"
						 	"</note>");
	
}
