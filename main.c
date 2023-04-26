#include "main.h"

/**
 * get_string_array - description here...
 * @arr_size: number of the array list
 * Return: struct stringArray
 */
struct stringArray *get_string_array(int arr_size)
{
	struct stringArray *arr;

	arr = malloc(sizeof(stringArray));
	arr->length = 0;
	arr->arr = malloc(arr_size * sizeof(char *));
	return (arr);
}

/**
 * get_and_parse_line - description here...
 * @arr: pointer to the original struct
 * Return nothing
 */
void get_and_parse_line(struct stringArray *arr)
{
	char *portion, *tempStr;
	int tempSize = 0, tempIdx = 0;
	char *string = NULL;
	size_t size = 0;

	getline(&string, &size, stdin);

	/* parsing the string line from user into an array of strings*/
	portion = strtok(string, " \r\n");
	while (portion != NULL)
	{
		while (portion[tempIdx] != '\0')
		{
			tempSize++;
			tempIdx++;
		}
		tempStr = malloc(sizeof(char) * tempSize);
		strcpy(tempStr, portion);

		arr->length = arr->length + 1;
		arr->arr[arr->length - 1] = tempStr;
		tempIdx = 0;
		tempSize = 0;
		tempStr = NULL;
		portion = strtok(NULL, " \r\n");
	}
	arr->arr = realloc(arr->arr, arr->length);
	arr->arr[arr->length] = NULL;
}

/**
 * exec_line_command - execute the wroted cmd line.
 * @arr: struct stringArray
 * @st: struct stat
 * @tempIdx: number for the index
 * @status: passed status from main function
 * Return nothing
 */
void exec_line_command(struct stringArray *arr, struct stat *st,
		int *tempIdx, int *status)
{
	pid_t my_pid;

	/* Check whether the path is valid */
	if (stat(arr->arr[0], st) == 0)
	{
		/*FORK CHILD TO EXECUTE in case the path is valid */
		while (*tempIdx < arr->length)
		{
			if (arr->arr[*tempIdx] == NULL)
				printf("NULL\n");
			else
				printf("%s\n", arr->arr[*tempIdx]);

			*tempIdx = *tempIdx + 1;
		}

		my_pid = fork();
		if (my_pid == 0)
		{
			if (execve(arr->arr[0], arr->arr, NULL) == -1)
				perror("execve");

			sleep(3);
		}
		else
			wait(status);
	}
	else
		printf(" NOT FOUND\n");

}

/**
 * main - desc
 * Return: 0
 */
int main(void)
{
	struct stringArray *arr;
	int arr_size = 100, tempIdx = 0, status, j = 1;
	/* pid_t my_pid; */
	struct stat st;

	/* MAIN LOOP */
	while (j == 1)
	{
		printf("$ ");
		/* Intialize Array*/
		arr = get_string_array(arr_size);
		/*GET LINE AND PARSE IT FOR FUTURE USE*/
		get_and_parse_line(arr);
		if (strcmp(arr->arr[0], "exit") == 0)
			break;
		if (arr->arr[0][0] != '/')
		{
			int len = 0;
			char *temp = arr->arr[0];

			while (temp[len] != '\0')
				len++;

			arr->arr[0] = malloc(6 + len);
			strcat(arr->arr[0], "/bin/");
			strcat(arr->arr[0], temp);
		}

		exec_line_command(arr, &st, &tempIdx, &status);
	}

	return (0);
}
