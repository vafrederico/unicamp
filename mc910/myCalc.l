%{
    #include <stdlib.h>
    #include "y.tab.h"    
    #ifndef YYSTYPE
    typedef int YYSTYPE;
    #endif
    extern YYSTYPE yylval;   
%}

%%

print { return PRINT; }

; { return SEMI; }

:= { return VALEQ; }

\n { linenumber_increase(); }

[a-z] {
	yylval = *yytext - 'a';
	return VARIABLE;
}

[0-9]+ {
	yylval = atoi(yytext);
	return INTEGER;
}

[+*()] { 
	return *yytext;
}

[ \t]+ {}

. {
	yyerror("programa invalido!\n");  exit(0);
}
%%

int yywrap(void) {
    return 1;
}