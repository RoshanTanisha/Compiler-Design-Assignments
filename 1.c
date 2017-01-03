/*Identify whether the line is comment or not*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "check.c"
#define LENGTH 32

void removeComments(FILE * f, FILE * out);
void removeWhites(FILE * f, FILE * out);
int checkLength(FILE * out);
int analyze(char * s);

FILE * f1;

int main(int argc, char ** args){
	if(argc == 1){
		printf("Enter the file to analyze\n");
		return(12);
	}
	char Whites[] = {'\n', '\t'};
	FILE * f = fopen(args[1], "r");
	FILE * inter = fopen("Intermediate.c", "w");
	FILE * out = fopen("AnalyzedFile.c", "w");
	if(f == NULL || inter == NULL || out == NULL){
		printf("There is no such file\n");
		return(11);
	}
	removeComments(f, inter);
	
	fclose(inter);
	
	inter = fopen("Intermediate.c", "r");
	
	removeWhites(inter, out);
	fclose(f);
	fclose(inter);
	fclose(out);
	out = fopen("AnalyzedFile.c", "r");
	
	f1 = fopen("Identifier.txt", "w");
	if(checkLength(out) > 0){
		printf("The identifiers are to the rules of language\n");
	}else{
		printf("The length of the identifier is greater than permissible length which is %d\n", LENGTH);
	}
	fclose(out);
	system("AnalyzedFile.c");
	system("Intermediate.c");
	fclose(f1);

	return(0);
}

void removeComments(FILE * f, FILE * out){
	char c, d;
	while((c = fgetc(f)) != EOF){
		if(c == '/'){
			d = fgetc(f);
			if(d == '/'){
				while(fgetc(f) != '\n'){
				}
			}else if(d == '*'){
				L:
				while(fgetc(f) != '*'){
				}
				if(fgetc(f) != '/'){
					goto L;
				}
			}else{
				fputc(c, out);
				fputc(d, out);
			}
		}else{
			fputc(c, out);
		}
	}
}

void removeWhites(FILE * f, FILE * out){
	char c;
	while((c = fgetc(f)) != EOF){
		if(c == ' ' || c == '\n' || c == '\t'){
			fputc(c, out);
			do{
				c = fgetc(f);
			}while(c == ' ' || c == '\n' || c == '\t' && c != EOF);
			fputc(c, out);
		}else{
			fputc(c, out);
		}
	}
}

int checkLength(FILE * out){
	int l, i, j;
    char c;
	char * s = calloc(1024, sizeof(char));
	while(! feof(out)){
		fgets(s, 1024, out);
		l = analyze(s);
		strset(s, '\0');
		if(l == 2 || l == 3){
			return(-l);
		}
	}
	return(1);
}

//return value 0 - no identifier in line; 1 - identifier and okay; 2 - identifier but not okay; 3 - length gretaer than permissible

int analyze(char * s){
	int i, l = strlen(s), j, k = 0, m = 0, r = 0, len = 0;
	char * token[] = {"int", "char", "enum", "long", "void", "float", "union", "double", "struct", "#define", "typedef", "unsigned"};
	char * c = (char *)calloc(LENGTH, sizeof(char));
	char * p;
	printf("length = %d\n", l);
	for(i = 0; i < l; i ++){
		for(j = 0; j < 10; j ++){
			if(strncmp(&s[k], token[j], strlen(token[j])) == 0){
				k = strlen(token[j]) + 1;
				L:
					while(s[k] == ' ' || s[k] == '*'){
						k ++;
					}
					while(s[k] != ',' && s[k] != ' ' && s[k] != '(' && s[k] != '[' && s[k] != ';'){
						len ++;
						c[m ++] = s[k ++];
					}
					c[m] = '\0';
					len++;
					if(len > LENGTH){
						return(3);
					}
					p = (char *)calloc(len, sizeof(char));
					strncpy(p, c, len);
					if(check(p) == -1){
						r = 2;
						return(2);
					}
					
					r = 1;
					strset(p, '\0');
					free(p);
					p = NULL;
					len = 0;
					m = 0;
					strset(c, '\0');
					if(s[k] == ','){
						k ++;
						goto L;
					}
			}
		}
	}
	return(r);
}
