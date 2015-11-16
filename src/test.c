#include <stdio.h>
#include <string.h>
#include <regex.h>  
#include <stdlib.h>      

int main(void){

	regex_t preg;
	int rc;
	size_t nmatch = 4;
	regmatch_t pmatch[4];

	char *parse_string = "14;13;{1,2,3,4,5,9,12}";
	//char *parse_string = "a very simple simple simple string";
	//char *pattern1 = "([0-9]+)(?=;)";
	//char *pattern1 = "\\([0-9]*\\)";
	char *pattern1 = "\\(([0-9]*;)[0-9])\\";
	//char *pattern1 = "\\(sim[a-z]le\\) \\1";
	char *pattern2 = "([0-9]+)(?=,)|([0-9]+)(?=})";


	if (0 != (rc = regcomp(&preg, pattern1, 0))) {
		printf("regcomp() failed, returning nonzero (%d)\n", rc);
		exit(EXIT_FAILURE);
	}
	if (0 != (rc = regexec(&preg, parse_string, nmatch, pmatch, REG_NOTBOL))) {
		printf("Failed to match '%s' with '%s',returning %d.\n",
			parse_string, pattern1, rc);
	}
	else {

		printf("With the whole expression, a matched substring \"%.*s\" is found at position %d to %d. with '%s' \n",
			pmatch[0].rm_eo - pmatch[0].rm_so, &parse_string[pmatch[0].rm_so],
			pmatch[0].rm_so, pmatch[0].rm_eo - 1, pattern1);
		printf("With the sub-expression, a matched substring \"%.*s\" is found at position %d to %d.\n",
			pmatch[1].rm_eo - pmatch[1].rm_so, &parse_string[pmatch[1].rm_so],
			pmatch[1].rm_so, pmatch[1].rm_eo - 1);

		printf("With the sub-expression, a matched substring \"%.*s\" is found at position %d to %d.\n",
			pmatch[1].rm_eo - pmatch[1].rm_so, &parse_string[pmatch[1].rm_so],
			pmatch[1].rm_so, pmatch[1].rm_eo - 1);
		int i = 0;
		for ( i = 0; i < nmatch; ++i)
		{
			printf("%d\n", pmatch[i].rm_so);
		}

	}
	regfree(&preg);
	return 0;
	
	/*

	char* item;
	item = strtok(parse_string,";{,}");
	long chunk_number=atol(item);


	item = strtok(NULL,";{,}");
	long level_number=atol(item);
	
	long columns[level_number];

	printf("%ld, %ld\n",chunk_number,level_number);


	int j = 0;



	while(j<level_number){

		printf("%dbanana\n", j);

		item=strtok(NULL,";{,}");
		columns[j]=atol(item);

		j++;
	}

	printf("banana\n");
	*/

	printf("\n");


}