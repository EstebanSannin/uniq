/*
 * NOME:      Stefano Viola
 * MATRICOLA: 863000253
 * LICENSE:   GPLv3
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF 1024

void usage(void){
	
	printf("Programmazione2: uniq\n"
		"USAGE\tuniq [option] [file]\n"
		"OPTION:\n"
		"-c\tOgni riga viene preceduta dal numero di occorrenze\n"
		"-d\tScarta le linee che non sono ripetute\n"
		"-u/tScarta completamente le linee ripetute\n\n"
		"EXAMPLE:\n"
		"uniq -c file\n");
		exit(0);
}
int main(int argc, char **argv)
{
	char line[BUF];
	char line2[BUF];
	int strcount;
	char **strarray = NULL;
	
	/* variabili per opzioni a linea di comando*/
	int c;
	int cflag = 0;
	int dflag = 0;
	int uflag = 0;

	FILE *fp;
	while((c = getopt(argc, argv, "cduh")) != -1){
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
				usage();
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
	while((fgets(line,BUF, fp)) != NULL)
	{
		strarray = (char **)realloc(strarray, (strcount + 1) * sizeof(char *));
		strarray[strcount++] = strdup(line);
	}
	int i;
	int j;
	int count = 0,flag = 0;
	int x = 0;
	char line3[BUF];
	for(i = 0; i<strcount; i++){
		strcpy(line2,strarray[i]);
		j=i+1;
		while(j<strcount){
			if(!strcmp(line2,strarray[j])){
				count++;
				j++;
				i=j-1;
				if(!flag){
					strcpy(line3,line2);
				}
				flag=1;
			}else{
				break;
			}
		}

		if(!flag){
			if(cflag && !dflag)
				printf("%6d %s",1,line2);
			else if(!dflag)
				printf("%s",line2);
		}else{
			if(cflag && !uflag)
				printf("%6d %s",count+1,line3);
			else if(!uflag)
				printf("%s",line3);
		}
		j=0;
		count = 0;
		flag = 0;
	}

}

