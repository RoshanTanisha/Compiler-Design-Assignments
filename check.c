#include <string.h>
#include <stdlib.h>

int a[] = {2, 2, 8, 6, 6, 3, 4};
char * two[] =   {"do", "if"};
char * three[] = {"for", "int"};
char * four[] =  {"case", "char", "else", "enum", "goto", "long", "main", "void"};
char * five[] =  {"break", "const", "float", "short", "union", "while"};
char * six[] =   {"double", "extern", "return", "sizeof", "static", "struct"};
char * seven[] = {"default", "else if", "typedef"};
char * eight[] = {"continue", "register", "unsigned", "volatile"};

//return positive value for valid identifier, other 0 for keyword, negative value for a invalid identifier.

extern FILE * f1;

int check(char * c){
	int result = 1;
	int i;
	int l = strlen(c);
	fprintf(f1, "%s\n", c);
	if(c[0] == '_' || (c[0] >= 'A' && c[0] <= 'Z') || (c[0] >= 'a' && c[0] <= 'z')){
		if(l >= 2 && l <= 8){
			for(i = 0; i < a[l-2]; i ++){
				switch(l){
					case 2:	result = strcmp(c, two[i]);	
							break;
					case 3:	result = strcmp(c, three[i]);
							break;
					case 4:	result = strcmp(c, four[i]);
							break;
					case 5:	result = strcmp(c, five[i]);
							break;
					case 6:	result = strcmp(c, six[i]);
							break;
					case 7:	result = strcmp(c, seven[i]);
							break;
					case 8:	result = strcmp(c, eight[i]);
							break;
				}
				if(result == 0){
					return(result);
				}else{
					result = 1;
				}
			}
		}
		for(i = 1; i < l; i ++){
			if(c[i] == '_' || (c[i] >= 'a' && c[i] <= 'z') || (c[i] >= 'A' && c[i] <= 'Z')){
				continue;
			}else{
				result = -1;
			}
		}
	}else{
		result = -1;
	}
	return(result);
}