#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int pipefd[2];
    pid_t pid1, pid2;

    pipe(pipefd); //create pipe
    pid1 = fork(); //create fork child1
  
    if (pid1 < 0){
        fprintf(stderr, "Fork Failed");
        exit(1);
    }else if(pid1 == 0){
        //child 1
        close(pipefd[0]); //close read end 
        dup2(pipefd[1], 1); // redirects stdout to write to the pipe
        chdir("./Dir0"); //go to Dir0 directory
        execlp("ls", "ls", "-F", NULL); 
        printf ("EXECLP Failed\n");
    }else{
        pid2 = fork();
        if (pid2 < 0){
            fprintf(stderr, "Fork Failed");
            exit(1);
        }else if(pid2 == 0){
            printf("Show all file in Dir0 below: \n");
            // child 2
            close(pipefd[1]); // close write end 
            dup2(pipefd[0], 0); // redirects stdin to read from the pipe 
            execlp("nl", "nl", NULL); 
            printf ("EXECLP Failed\n");
        } else {
            // Parent Code, close read and writw end in parent
            close(pipefd[0]);
            close(pipefd[1]);
            // wait for two child
            wait(NULL);
            wait(NULL);
        }
    }
    return 0;
}