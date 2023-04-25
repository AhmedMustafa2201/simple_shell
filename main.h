#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
/**
 * struct stringArray - array of strings
 * @arr: array of string
 * @length: length of the array
 */
typedef struct stringArray
{
	char **arr;
	int length;
} stringArray;
#endif

