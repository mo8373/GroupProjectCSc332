#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include <string.h>
#include<sys/wait.h>


int tree_Radensky(){
  int status;
  pid_t pid[4]; //create process id for child
  pid[0] = fork(); // create child process and return Process id
  if(pid[0] < 0 ){
    perror("fork"); //there was a problem forking
  }
  if(pid[0] == 0){ //then the child is running
    execl("/bin/mkdir","mkdir", "Dir0", NULL); //creates directory Dir0
  }
    else{
    printf("PID of terminated child 0: %d\n", waitpid(pid[0], &status, 0)); //[prints if child was terminated]
    char *path = "Dir0";
    chdir(path);
    pid[1] = fork(); // create child process and return Process id
    if(pid[1] < 0 ){
      perror("fork"); //there was a problem forking
    }
    if(pid[1] == 0){ //then the child is running
      execl("/bin/touch","touch", "t1.txt","t2.txt", "t3.txt", NULL); // creates t1 t2 t3 text files
    }
    else{
      printf("PID of terminated child 1: %d\n", waitpid(pid[1], &status, 0)); //[prints if child was terminated
      pid[2] = fork(); // create child process and return Process id
      if(pid[2] < 0 ){
        perror("fork"); //there was a problem forking
      }
      if(pid[2] == 0){ //then the child is running
        execl("/bin/mkdir","mkdir", "Dir1", NULL); //creates directory Dir0
      }
      else{
        printf("PID of terminated child 2: %d\n", waitpid(pid[2], &status, 0)); //[prints if child was terminated
        printf("tree* finished executing\n");//print to show program is doen running
        return 0;
      }
    }
  }
}
