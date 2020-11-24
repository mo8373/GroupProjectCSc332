#include <stdio.h>   
#include <stdlib.h>   
#include <unistd.h>  
#include <sys/wait.h> 
 
void proc1(int pipe[]) { 
  int close1 = close(pipe[0]);
   if (close1 == -1) {
    perror("Failed to close.");
    exit(EXIT_FAILURE);
  }
  int dupc1 = dup2(pipe[1], STDOUT_FILENO );
  if (dupc1 < 0) {
    perror("The Dup2 function failed for Process 1.");
    exit(EXIT_FAILURE);
  }
      char * command[3];
      command[0] = "ls";
      command[1] = "-l";
      command[2] = NULL;
      int exc = execvp(command[0],command);
          if(exc == -1){
          fprintf(stderr, "There was an error executing ls -l\n");
      }
}
void proc2(int pipe[]) {   
  int close2 = close(pipe[1]);
   if (close2 == -1) {
    perror("Failed to close.");
    exit(EXIT_FAILURE);
  }
  int dupc2 = dup2(pipe[0], STDIN_FILENO); 
  if (dupc2 < 0) {
    perror("The Dup2 function failed for Process 2.");
    exit(EXIT_FAILURE);
  }
  char * command[3];
  command[0] = "tee";
  command[1] = "t1.txt";
  command[2] = NULL;
  int exc = execvp(command[0],command);
      if(exc == -1){
        fprintf(stderr, "There was an error executing tee\n");
      }
}
 
int main () {
  int pipe_fd[2];
  int lpipe = pipe(pipe_fd);
 
  if (lpipe == -1) {
    perror("Pipe creation failure");
    exit(EXIT_FAILURE);
  }
  // clear screen first
  system("clear");
  int pid1, pid2;
  switch (pid1 = fork()) {
     case -1:
       perror("Fork failure for 1st child\n");
       exit(EXIT_FAILURE);
     case 0:
       proc1(pipe_fd);
       exit(EXIT_SUCCESS);
     default:
       break;
  }
    switch (pid2 = fork()) {
     case -1:
       perror("Fork failure for 2nd child \n");
       exit(EXIT_FAILURE);
     case 0:
       proc2(pipe_fd);
       exit(EXIT_SUCCESS);
     default:
       break;
    }
    int close_read = close(pipe_fd[0]);
    if (close_read == -1) {
    perror("Failed to close.");
    exit(EXIT_FAILURE);
    }
    int close_write = close(pipe_fd[1]);  
    if (close_write == -1) {
      perror("Failed to close.");
      exit(EXIT_FAILURE);
    }
    // wait for both children
    int wait1 = wait(NULL); 
    if (wait1 == -1) {
      perror("Wait Failure.");
      exit(EXIT_FAILURE);
    }
   int wait2 = wait(NULL); 
    if (wait2 == -1) {
      perror("Wait Failure");
      exit(EXIT_FAILURE);
    }  
    char old[] = "t1.txt";
    char new[] = "tree.txt";
    int ret = rename(old,new);
   if(ret == 0) {
      printf("File was successfully renamed.\n");
   } else {
      perror("There was an issue and we could not rename the file for you.");
   }
    exit(EXIT_SUCCESS);
}
