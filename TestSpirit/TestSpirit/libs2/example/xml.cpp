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
	Rule<>	prolog, element, Misc, Letter, Digit, CombiningChar, Extender, PEReference, Reference, 
				PubidChar, PITarget, CData, doctypedecl, XMLDecl, SDDecl, VersionInfo, EncodingDecl,
				VersionNum, Eq, DeclSep, ExternalID, markupdecl, NotationDecl, EntityDecl, AttlistDecl,
				elementdecl, TextDecl, extSubsetDecl, conditionalSect, EmptyElemTag, STag, content, ETag,
				Attribute, contentspec, Mixed, children, choice, seq, cp, AttDef, AttType, DefaultDecl,
				StringType, TokenizedType, EnumeratedType, NotationType, Enumeration, EntityValue,
				AttValue, SystemLiteral, PubidLiteral, CharDataChar, CharData, Comment, PI, CDSect,
				extSubset, includeSect, ignoreSect, ignoreSectContents, Ignore, CharRef, EntityRef,
				GEDecl, PEDecl, EntityDef, PEDef, NDataDecl, extParsedEnt, EncName, PublicID, BaseChar;

	Rule<>	document = 		prolog >> element >> *Misc;
	ChLit<>	x9('\x9');
	ChLit<>	xA('\xA');
	ChLit<>	xD('\xD');
	Range<unsigned char>	x20xFF('\x20', '\xFF');
	Rule<>	Char = 			x9 | xA | xD | x20xFF;

	ChLit<>	x20('\x20');
	Rule<>	S = 				+(x20 | x9 | xD | xA);

	Rule<>	NameChar = 		Letter | Digit | '.' | '-' | '_' | ':' | CombiningChar | Extender;
	Rule<>	Name = 			(Letter | '_' | ':') >> *(NameChar);
	Rule<>	Names =			Name >> *(S >> Name);
	Rule<>	Nmtoken =		+NameChar;
	Rule<>	Nmtokens =		Nmtoken >> *(S >> Nmtoken);
	ChLit<>	Percent('%');
	ChLit<>	Ampersand('&');
	ChLit<>	DblQuote('"');
	ChLit<>	Quote('\'');
	ChLit<>	LessThan('<');

	EntityValue =	'"' >> *((anychar - (Percent | Ampersand | DblQuote)) | PEReference 
							| Reference) >> '"' 
						| '\'' >> *((anychar - (Percent | Ampersand | Quote)) | PEReference 
							| Reference) >> '\'';

	AttValue = 		'"' >> *((anychar - (LessThan | Ampersand | DblQuote)) | Reference) 
							>> '"' 
						| '\'' >> *((anychar - (LessThan | Ampersand | Quote)) | Reference) 
							>> '\'';

	SystemLiteral=	(DblQuote >> *(anychar - DblQuote) >> DblQuote) 
							| (Quote >> *(anychar - Quote) >> Quote);

	PubidLiteral =	DblQuote >> *PubidChar >> DblQuote | Quote >> *(PubidChar - Quote) 
							>> Quote;
	PubidChar =		x20 | xD | xA | alnum | '-' | '\'' | '(' | ')' | '+' | ',' | '.' | '/' 
							| ':' | '=' | '?' | ';' | '!' | '*' | '#' | '@' | '$' | '_' | '%';

	CharDataChar = anychar - (LessThan | Ampersand);
	CharData =		*(CharDataChar - "]]>");

	Comment =		"<!--" >> *((Char - '-') | ('-' >> (Char - '-'))) >> "-->";

	PI =				"<?" >> PITarget >> !(S >> (*Char - (*Char >> "?>" >> *Char))) >> "?>";
	PITarget =		Name - ((ChLit<>('X') | 'x') >> (ChLit<>('M') | 'm') 
							>> (ChLit<>('L') | 'l'));

	CDSect =			"<![CDATA[" >> CData >> "]]>";
	CData =			*(Char - "]]>");

	prolog =			!XMLDecl >> *Misc >> !(doctypedecl >> *Misc);
	XMLDecl =		"<?xml" >> VersionInfo >> !EncodingDecl >> !SDDecl >> !S >> "?>";
	VersionInfo =	S >> "version" >> Eq >> (Quote >> VersionNum >> Quote 
							| DblQuote >> VersionNum >> DblQuote);
	Eq =				!S >> '=' >> !S;
	VersionNum =	+(alnum | '_' | '.' | ':' | '-');
	Misc =			Comment | PI | S;

	doctypedecl =	"<!DOCTYPE" >> S >> Name >> !(S >> ExternalID) >> !S >> !('[' 
							>> *(markupdecl | DeclSep) >> ']' >> !S) >> '>';
	DeclSep =		PEReference | S;
	markupdecl =	elementdecl | AttlistDecl | EntityDecl | NotationDecl | PI | Comment;

	extSubset =		!TextDecl >> extSubsetDecl;
	extSubsetDecl=	*(markupdecl | conditionalSect | DeclSep);
	SDDecl =			S >> "standalone" >> Eq >> ((Quote >> (StrLit<>("yes") | "no") >> Quote)
							| (DblQuote >> (StrLit<>("yes") | "no") >> DblQuote));

	element =		EmptyElemTag
						| STag >> content >> ETag;

	STag =			'<' >> Name >> *(S >> Attribute) >> !S >> '>';
	Attribute =		Name >> Eq >> AttValue;
	ETag =			"</" >> Name >> !S >> '>';
	content =		!CharData >> *((element | Reference | CDSect | PI | Comment) >> !CharData);
	EmptyElemTag =	'<' >> Name >> *(S >> Attribute) >> !S >> "/>";
	elementdecl =	"<!ELEMENT" >> S >> Name >> S >> contentspec >> !S >> '>';
	contentspec =	StrLit<>("EMPTY") | "ANY" | Mixed | children;
	children =		(choice | seq) >> !(ChLit<>('?') | '*' | '+');
	cp =				(Name | choice | seq) >> !(ChLit<>('?') | '*' | '+');
	choice =			'(' >> !S >> cp >> +(!S >> '|' >> !S >> cp) >> !S >> ')';
	seq =				'(' >> !S >> cp >> *(!S >> ',' >> !S >> cp) >> !S >> ')';
	Mixed =			'(' >> !S >> "#PCDATA" >> *(!S >> '|' >> !S >> Name) >> !S >> ")*"
						| '(' >> !S >> "#PCDATA" >> !S >> ')';
	AttlistDecl =	"<!ATTLIST" >> S >> Name >> *AttDef >> !S >> '>';
	AttDef =			S >> Name >> S >> AttType >> S >> DefaultDecl;
	AttType =		StringType | TokenizedType | EnumeratedType;
	StringType =	StrLit<>("CDATA");
	TokenizedType=	StrLit<>("ID") | "IDREF" | "IDREFS" | "ENTITY" | "ENTITIES" | "NMTOKEN" 
							| "NMTOKENS";
	EnumeratedType=NotationType | Enumeration;
	NotationType =	"NOTATION" >> S >> '(' >> !S >> Name >> *(!S >> '|' >> !S >> Name) >> !S 
							>> ')';
	Enumeration =	'(' >> !S >> Nmtoken >> *(!S >> '|' >> !S >> Nmtoken) >> !S >> ')';
	DefaultDecl =	StrLit<>("#REQUIRED") | "#IMPLIED" | !("#FIXED" >> S) >> AttValue;
	conditionalSect=	includeSect | ignoreSect;
	includeSect =	"<![" >> !S >> "INCLUDE" >> !S >> '[' >> extSubsetDecl >> "]]>";
	ignoreSect =	"<![" >> !S >> "IGNORE"  >> !S >> '[' >> *ignoreSectContents >> "]]>";
	ignoreSectContents =	Ignore >> *("<![" >> ignoreSectContents >> "]]>" >> Ignore);
	Ignore =			*(Char - (StrLit<>("<![") | "]]>"));

	CharRef =		"&#" >> +digit >> ';'
						| "&#x" >> +xdigit >> ';';

	Reference =		EntityRef | CharRef;
	EntityRef =		'&' >> Name >> ';';
	PEReference =	'%' >> Name >> ';';
	EntityDecl =	GEDecl | PEDecl;
	GEDecl =			"<!ENTITY" >> S >> Name >> S >> EntityDef >> !S >> '>';
	PEDecl =			"<!ENTITY" >> S >> '%' >> S >> Name >> S >> PEDef >> !S >> '>';
	EntityDef =		EntityValue
						| ExternalID >> !NDataDecl;
	PEDef =			EntityValue | ExternalID;

	ExternalID =	"SYSTEM" >> S >> SystemLiteral
						| "PUBLIC" >> S >> PubidLiteral >> S >> SystemLiteral;
	NDataDecl =		S >> "NDATA" >> S >> Name;
	TextDecl =		"<?xml" >> !VersionInfo >> EncodingDecl >> !S >> "?>";
	extParsedEnt =	!TextDecl >> content;
	EncodingDecl =	S >> "encoding" >> Eq >> (DblQuote >> EncName >> DblQuote | 
							Quote >> EncName >> Quote);
	EncName =		alpha >> *(alnum | '.' | '_' | '-');
	NotationDecl =	"<!NOTATION" >> S >> Name >> S >> (ExternalID | PublicID) >> !S >> '>';
	PublicID =		"PUBLIC" >> S >> PubidLiteral;


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
