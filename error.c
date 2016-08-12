#include <stdio.h>
#include <stdlib.h>

#include "error.h"

const char* error_messages[1] = { "Invalid Operation" };

void error (enum ann_error_code error_code, int line_num, char* file_name, char* detail)
{
	printf("%s at %s:%d\n", error_messages[error_code], file_name, line_num);
	
	if (detail != NULL)
		printf("Details: %s\n", detail);
	
	exit(-1);
}
