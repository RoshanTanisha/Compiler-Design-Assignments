#include <stdio.h>
#include <stdlib.h>

void filter(FILE * source, FILE * code, FILE * comments);
void printFile(FILE * f);

int main(int arg, char * argv[]){
	FILE * f1, * f2, * f3;
	int i;
	if(arg != 4){
		printf("Provide three file names: Source File, file which is to be produced without comments and file with comments\n");
		printf("Exiting...\n");
		getch();
		exit(2);
	}else{
		f1 = fopen(argv[1], "r");	
		f2 = fopen(argv[2], "w");	
		f3 = fopen(argv[3], "w");	
		filter(f1, f2, f3);
		
		for(i = 0; i < arg; i++)
		printf("argv[%d] = %s\n", i, argv[i]);
		printf("Source file filtered and written to %s : without comments and %s : only comments\n", argv[2], argv[3]);
		fclose(f1);
		fclose(f2);
		fclose(f3);
		getch();
		return(0);
	}
}


void filter(FILE * source, FILE * code, FILE * comments){
	char c, d;
	while(1){
		c = getc(source);
		if(c == EOF){
			break;
		}
		if(c != '/'){
			putc(c, code);
			printf("Writing '%c' to code file\n", c);
		}else{
			d = getc(source);
			if(d == '/' || d == '*'){
				putc(c, comments);
				putc(d, comments);
				printf("Writing '%c' to comments file\n", d);
				if(d == '/'){
					d = getc(source);
					while(d != 10){
						putc(d, comments);
						d = getc(source);
					}
					putc(d, comments);
					putc(d, code);
				}else{
					d = getc(source);
					do{
						putc(d, comments);
						d = getc(source);
					}while(d != 47);
					putc(d, comments);
				}
			}else{
				putc(c, code);
				putc(d, code);
			}
		}
	}
}
