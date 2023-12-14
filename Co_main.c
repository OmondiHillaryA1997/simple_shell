#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main(void)
{
	char **cmds = NULL, *tkn, *lnptr = NULL, *dupstr;
	size_t num_tkns = 0, n = 0, index = 0;
	ssize_t num_charR;

	while (1)
	{
		printf("Co-shell$ ");
		num_charR = getline(&lnptr, &n, stdin);

		if (num_charR == -1) 
		{
			free(lnptr);
			lnptr = NULL;
			printf("\n");
			exit(EXIT_FAILURE);
		}
		lnptr[num_charR - 1] = '\0';

		dupstr = custom_strdup(lnptr);
		tkn = strtok(dupstr, " ");

		/*Reset the token count for each input line*/

		while (tkn != NULL)
		{
			++num_tkns;
			tkn = strtok(NULL, " ");
		}
		if (num_tkns > 0) 
		{
			cmds = malloc(sizeof(char *) * (num_tkns + 1)); /*Allocate one more for the NULL pointer*/

			if (cmds == NULL) 
			{
				exit(EXIT_FAILURE);
			}

			tkn = strtok(lnptr, " ");

			index = 0; /*Reset index for new command tokens*/

			while (tkn != NULL)
			{
				cmds[index] = custom_strdup(tkn);

				tkn = strtok(NULL, " ");
				index++;
			}

			cmds[index] = NULL; /* Set the last pointer to NULL to mark the end*/
			index = 0;
			while (cmds[index] != NULL)
			{
				printf("%s\n", cmds[index]);
				index++;
			}
		}
		index = 0;
		while (cmds[index] != NULL) 
		{
			free(cmds[index]);
			index++;
		}
		free(cmds);
		/*Reset pointers and counters*/
		num_tkns = 0;

		free(lnptr);
		lnptr = NULL;
	}
	return 0;
}
