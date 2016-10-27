#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void identifyComments(FILE * f, FILE * out);

int main(int argc, char ** argv){
	FILE * f, * g;
	if(argc == 1){
		printf("Enter the name of the file.\n");
		return(-1);
	}
	f = fopen(argv[1], "r");
	g = fopen("Comment2.txt", "w");
	identifyComments(f, g);
	fclose(g);
	g = fopen("Comment2.txt", "r");
	printf("Following are the comment lines from the file: %s\n", argv[1]);
	while(! feof(g)){
		printf("%c", fgetc(g));
	}
	fclose(f);
	fclose(g);
	// /printf("End");
	return(0);
}

void identifyComments(FILE * f, FILE * out){
	char c, d;
	while((c = fgetc(f)) != EOF){
		if(c == '/'){
			d = fgetc(f);
			if(d == '/' || d == '*'){
				fputc(c, out);
				fputc(d, out);
				if(d == '/'){
					while((d = fgetc(f)) != '\n'){
						fputc(d, out);
					}
					fputc(d, out);
				}else{
					L:
					while((d = fgetc(f)) != '*'){
						fputc(d, out);
					}
					fputc(d, out);
					if((d = fgetc(f)) == '/'){
						fputc(d, out);
					}else{
						goto L;
					}
				}
			}
		}
	}
}