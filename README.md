# Pipex

## Description

"This project is about handling pipes."

### External Functions (DESCRIPTIONS)

#### perror()
```
#include <errno.h>

void perror(const char *s);
```
Prints a system error message on the standard error describing the error encountered during a call to a system or library function.

#### strerror()
```
#include <string.h>

char *strerror(int errnum);
```
Returns a pointer to a string that describes the error code passed in the argument errnum.

#### access()
```
#include <unistd.h>

int access(const char *pathname, int mode);
```
Checks whether the calling process can access the file pathname. The  mode  specifies the accessibility check(s) to be performed. F_OK tests for the existence of the file. R_OK, W_OK, and X_OK test whether the file exists and grants read, write, and execute permissions, respectively.

#### dup, dup2
```
#include <unistd.h>

int dup(int oldfd);
int dup2(int oldfd, int newfd);
```
The <strong>dup()</strong> system call allocates a new file descriptor that refers to the same open file description as the descriptor oldfd. The new file descriptor number is guaranteed to be the lowest-numbered file descriptor that was unused in the calling process.

The <strong>dup2()</strong> system  call  performs the same task as dup(), but instead of using the lowest-numbered unused file descriptor, it uses the file descriptor number specified in newfd.  In other words, the file descriptor newfd is adjusted so that it now refers to the same open file description as oldfd.

#### execve()
```
#include <unistd.h>

int execve(const char *pathname, char *const argv[], char *const envp[]);
```
Executes the program referred to by <strong>pathname</strong>.  This causes the program that is currently being run by the calling process to be replaced with a new program, with newly initialized stack, heap, and (initialized and uninitialized) data segments.

<strong>argv</strong> is an array of pointers to strings passed to the new program as its command-line arguments.  By convention, the first of these strings (i.e., argv[0]) should contain the filename associated with the  file  being executed.  The argv array must be terminated by a NULL pointer.  (Thus, in the new program, argv[argc] will be NULL.)

<strong>envp</strong> is an array of pointers to strings, conventionally of the form key=value, which are passed as the environment of the new program.  The envp array must be terminated by a NULL pointer.

#### fork
```
#include <unistd.h>

pid_t fork(void);
```
Creates a new process by duplicating the calling process.  The new process is referred to as the child process.  The calling process is referred to as the parent process.


* pipe
* unlink
* wait
* waitpid
