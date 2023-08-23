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

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUFFER_F -1
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define get_all \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

extern char **environ;

/**
 * struct lststr - This is a singly linked list
 * @num: The numbers in the list
 * @str: Stands for string
 * @next: It points to the next node
 */
typedef struct lststr
{
	int num;
	char *str;
	struct lststr *next;
} lst_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	lst_t *env;
	lst_t *history;
	lst_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} get_t;

typedef struct builtin
{
	char *type;
	int (*func)(get_t *);
} builtin_table;
int big(get_t *, char **);
int _symbol(get_t *);
void find_cmd(get_t *);
void fork_cmd(get_t *);
int exe_c(get_t *, char *);
char *cp(char *, int, int);
char *serch(get_t*, char *, char *);
int loophsh(char **);
void type(char *);
int type_char(char);
int put_fd(char c, int file_des);
int _put_fd(char *str, int file_des);
int str_len(char *);
int str_cmp(char *, char *);
char *begins(const char *, const char *);
char *str_cat(char *, char *);
char *str_cpy(char *, char *);
char *str_dup(const char *);
void _types(char *);
int _types_char(char);
char *_strncpy(char *, char *, int);
char *strn_cat(char *, char *, int);
char *_strchr(char *, char);
char **str_tow(char *, char *);
char **str_tow2(char *, char);
char *ceed(char *, char, unsigned int);
void release(char **);
void *move(void *, unsigned int, unsigned int);
int re(void **);
int is_interactive(get_t *);
int bound(char, char *);
int alpha(int);
int vert(char *);
int _vert(char *);
void _error(get_t *, char *);
int decimal(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _myexit(get_t *);
int _mycd(get_t *);
int _myhelp(get_t *);
int _myhistory(get_t *);
int _myalias(get_t *);
ssize_t get_input(get_t *);
int _getline(get_t *, char **, size_t *);
void sigintHandler(int);
void clean(get_t *);
void set_get(get_t*, char **);
void free_get(get_t *, int);
char *_getenv(get_t *, const char *);
int _myenv(get_t *);
int _mysetenv(get_t *);
int _myunsetenv(get_t *);
int populate_env_list(get_t *);
char **get_environ(get_t *);
int _unsetenv(get_t *, char *);
int _setenv(get_t *, char *, char *);
char *get_history_file(get_t *get);
int write_history(get_t *get);
int read_history(get_t *get);
int build_history_lst(get_t *, char *, int);
int renumber_history(get_t *get);
lst_t *add_node(lst_t **, const char *, int);
lst_t *add_node_end(lst_t **, const char *, int);
size_t print_list_str(const lst_t *);
int delete_node_at_index(lst_t **, unsigned int);
void free_lst(lst_t **);
size_t length(const lst_t *);
char **string(lst_t *);
size_t display(const lst_t *);
lst_t *first_node(lst_t *, char *, char);
ssize_t index_node(lst_t *, lst_t *);
int is_chain(get_t *, char *, size_t *);
void check_chain(get_t *, char *, size_t *, size_t, size_t);
int replace_alias(get_t *);
int replace_vars(get_t *);
int replace_string(char **, char *);

#endif

