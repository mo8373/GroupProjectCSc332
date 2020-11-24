#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

#define COMMAND_LEN 4 //constant used as last 4 commands need to be printed
char listOfCommands[COMMAND_LEN][1024]; //array of size 4 to keep the commands

//this function takes in the user input and inserts into the array
//it will keep shifting the list to the left as more commands come in
//IT SHOULD BE CALLED RIGHT AFTER WE GET A NEW COMMAND FROM USER
void updateListOfCommands(char newCommand[]){
	for(int i = 1; i < COMMAND_LEN; i++){
		strcpy(listOfCommands[i-1], listOfCommands[i]);
	}
	strcpy(listOfCommands[COMMAND_LEN-1], newCommand);
}
//this function will be used right before exiting as it will print the commands
void printLastFourCommands() {
	printf("\nLast Four Commands: \n");
	for(int i = 0; i < COMMAND_LEN; i++){
		if (listOfCommands[i] != NULL)
			printf("%s\n", listOfCommands[i]);
	} 
    printf("\n");   
}
//printing a list of contents in the current directory
void listCurrentDir() {
    DIR * dir;
    struct dirent *sd; //pointer to read the dir
    dir = opendir("."); //this assumes the current directory

    if (dir == NULL) {
        printf("ERROR OPENING DIRECTORY. \n");
        exit(1);
    }
    while((sd = readdir(dir))!= NULL) {
        printf(">> %s\n", sd->d_name);
    }
    closedir(dir); 
}

void exit_Gurjit() {
    listCurrentDir();
    printLastFourCommands();

    printf("Hit Enter to exit the SHELL...");
    char input[1024]; // String To Take Input
	fgets(input,1024,stdin); // Obtain Input
    if (strcmp(input, "\0" ) == 0){
        exit(EXIT_SUCCESS); //CALL THE EXIT FUNCTION WHICH WILL PRINT THE LAST 4 COMMANDS AND CONTENT IN DIR
    }
}
/* 
**************************************
The following two functions/code will need the user input from shell. 
**************************************
1. 
updateListOfCommands(USERINPUT); 
^^this function should be to be placed right after we get the input from user so it can stay updated.
FOR EXAMPLE==
    //get input from user
    fgets(linebuffer,sizeof(linebuffer),stdin);
    
    //push most recent command into history
    updateListOfCommands(linebuffer);
----------------------------------------------------------
2. 
if (strcmp(inputArgs[0], "\0" ) == 0){
    exit(); //CALL THE EXIT FUNCTION WHICH WILL PRINT THE LAST 4 COMMANDS AND CONTENT IN DIR
break;
}
^^ if the user hits return, it will break out of the program and exit shell
*/
