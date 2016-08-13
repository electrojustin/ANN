#ifndef ERROR_H
#define ERROR_H
enum ann_error_code
{
	err_invalid_op = 0
};

void error (enum ann_error_code error_code, int line_num, char* file_name, char* detail);
#endif
