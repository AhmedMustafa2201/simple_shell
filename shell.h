#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024

#define CMD_NORM	0
#define CMD_CHAIN	3
#define CMD_OR		1
#define CMD_AND		2

#define CONVERT_UNSIGNED	2
#define CONVERT_LOWERCASE	1

#define USE_STRTOK 0
#define USE_GETLINE 0

#define HIST_MAX	4096
#define HIST_FILE	".simple_shell_history"

extern char **environ;


/**
 * struct liststr - linked list
 * @num: the number
 * @str: a string
 * @next: points
 */
typedef struct liststr
{
	char *str;
	int num;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements,
 * @arg: a string generated
 * @argv:an array of strings
 * @path: a string path
 * @argc: count
 * @line_count: count
 * @err_num: the error code
 * @linecount_flag: if on count
 * @fname: filename
 * @env: local copy of environ
 * @environ: copy of environ from LL env
 * @history: history node
 * @alias: alias node
 * @env_changed: environ
 * @status: return status
 * @cmd_buf: cmd_buf
 * @cmd_buf_type: CMD_type
 * @readfd: the fd
 * @histcount: the history
 */
typedef struct passinfo
{
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	char *arg;
	int env_changed;
	int status;
	char **argv;
	char *path;
	int argc;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - builtin string
 * @type: builtin command
 * @func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

void find_cmd(info_t *);
void fork_cmd(info_t *);
int hsh(info_t *, char **);
int find_builtin(info_t *);

char *dup_chars(char *, int, int);
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);

int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
void _eputs(char *);
int _eputchar(char);

int loophsh(char **);

int bfree(void **);

int _strlen(char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
int _strcmp(char *, char *);

void _puts(char *);
int _putchar(char);
char *_strcpy(char *, char *);
char *_strdup(const char *);

char *_strncpy(char *, char *, int);
char *_strchr(char *, char);
char *_strncat(char *, char *, int);

char **strtow(char *, char *);
char **strtow2(char *, char);

void ffree(char **);
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);

int _isalpha(int);
int _atoi(char *);
int interactive(info_t *);
int is_delim(char, char *);

int _erratoi(char *);
int print_d(int, int);
void print_error(info_t *, char *);
char *convert_number(long int, int, int);
void remove_comments(char *);

int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);


ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

int _myhistory(info_t *);
int _myalias(info_t *);

char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int renumber_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);

void free_list(list_t **);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);

size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
ssize_t get_node_index(list_t *, list_t *);
list_t *node_starts_with(list_t *, char *, char);

int replace_alias(info_t *);
int replace_vars(info_t *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_string(char **, char *);

#endif

