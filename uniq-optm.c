/*
 * NOME:      Stefano Viola
 * MATRICOLA: 863000253
 *
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF 1024
int main(int argc, char **argv)
{
	char line[BUF];
	char line2[BUF];
	int strcount;
	char **strarray = NULL;
	int c;
	int cflag = 0;
	int dflag = 0;
	int uflag = 0;
	FILE *fp;
	while((c = getopt(argc, argv, "cdu")) != -1){
		switch(c){
			case 'c':
				cflag = 1;
				break;
			case 'd':
				dflag = 1;
				break;
			case 'u':
				uflag = 1;
				break;
			case 'h':
				break;
			case '?':
				if(isprint(optopt))
					fprintf(stderr, "Unknown option `-%c'.\nTry 'uniq -h' for usage message.\n", optopt);
			default: 
				exit(1);
		}
	}
	if(argv[optind] == NULL)
		fp = stdin;
	else{
		if((fp = fopen(argv[optind], "r")) == NULL)
			exit(-1);
	}


	int flag = 0;
	int count = 0;
	int fine = 0;
	char *result;
	while(1){
		result = fgets(line,BUF, fp);
		if(result == NULL){
			if(fine)
				break;
			strcpy(line,"");
			fine = 1;
		}

		if(!flag)
			strcpy(line2,line);
		else{
			if(!strcmp(line,line2)){
				count++;
			}else{
				if(count>0){
					if(cflag && !uflag)
						printf("--%6d %s",count+1, line2);
					else if(!uflag)
						printf("%s",line2);
				}
				else
					if(cflag && !dflag)
						printf("%6d %s",count+1, line2);
					else if(!dflag)
						printf("%s",line2);
				strcpy(line2,line);
				count = 0;
			}
		}
		flag=1;
	}
}

