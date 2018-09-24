%token INTEGER VARIABLE PRINT SEMI VALEQ NEWLINE
%left '+'
%left '*'
%right VALEQ
%start S
%{
    #include <stdio.h>
    #include <stdlib.h>
	void yyerror(char *);
	
	int yylex(void);
	int vars[26];
	int varsSet[26];
	int lineNumber;
%}

%%

S:
	C SEMI S
	|;

C:
	PRINT '(' VARIABLE ')' {
	 	if(varsSet[$3] == 0) {
			printf("linha %d: variavel %c nao inicializada!\n", lineNumber, $3+'a');
			exit(0);
		} else {
			printf("%d\n",vars[$3]); 
		}
	}|
	VARIABLE VALEQ E { 
		if ($3 < 0 || $3 > 32767) {
			printf("programa invalido!\n");
			exit(0);
		}
		vars[$1] = $3; varsSet[$1] = 1;
	} |
	
	;

E:
	INTEGER |
	VARIABLE { 
		if(varsSet[$1] == 0) {
			printf("linha %d: variavel %c nao inicializada!\n", lineNumber, $1+'a');
			exit(0);
		} else {
			$$ = vars[$1]; 
		}
	} |
	E '+' E { $$ = $1 + $3;} |
	E '*' E { $$ = $1 * $3;} |
	'(' E ')' { $$ = $2; };

%%

linenumber_increase(){
	lineNumber++;
}
void yyerror(char *s) {
    printf("programa invalido!\n");
}

int main() {
	
	int i;

	for(i = 0; i < 26; i++){
		vars[i] = 0;
		varsSet[i] = 0;
	}
	lineNumber = 1;
    yyparse();
    return 0;
}
