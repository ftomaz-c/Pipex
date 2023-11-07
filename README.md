# Pipex

## Description

"This project is about handling pipes."

## Task List

 - [ ] Test all of the "new" external functions;
 - [ ] Understand the theory and all the external functions;
 - [ ] Write the pseudo code - parsing, execution, cleanup, etc;
 - [ ] Write the Program;
 - [ ] Debugging;


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

#### fork()
```
#include <unistd.h>

pid_t fork(void);
```
Creates a new process by duplicating the calling process.  The new process is referred to as the child process.  The calling process is referred to as the parent process.

#### pipe()
```
#include <unistd.h>

int pipe(int pipefd[2]);
```
Creates  a pipe, a unidirectional data channel that can be used for interprocess communication.  The array pipefd is used to return two file descriptors referring to the ends of the pipe.  pipefd[0] refers to the read end of the pipe.  pipefd[1] refers to the write end of the pipe.  Data written to the write end of the pipe is buffered by the kernel until it is read from the read end of the pipe.

#### unlink
```
unlink FILE
unlink OPTION
```
Remove the specified FILE.

* wait, waitpid
```
#include <sys/wait.h>

pid_t wait(int *wstatus);
pid_t waitpid(pid_t pid, int *wstatus, int options);
```
The wait() system call suspends execution of the calling thread until one of its children terminates.  The call wait(&wstatus) is equivalent to:

	waitpid(-1, &wstatus, 0);

The waitpid() system call suspends execution of the calling thread until a child specified by pid argument has changed state.  By default, waitpid() waits only for terminated children, but this behavior is modifiable via the options argument, as described below.

The value of pid can be:

	< -1	meaning wait for any child process whose process group ID is equal to the absolute value of pid.

	-1		meaning wait for any child process.

	0		meaning wait for any child process whose process group ID is equal to that of the calling process at the time of the call to waitpid().

	> 0		meaning wait for the child whose process ID is equal to the value of pid.