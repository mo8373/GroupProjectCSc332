#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>



int path_Raul() {

   //print path to terminal and file t2.txt
   char cwd[PATH_MAX];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
   printf("Current working dir: %s\n",cwd );
   }
   FILE *t2 =fopen("t2.txt", "w");

   if (t2 == NULL) {
       perror("Error opening t2 \n");
       exit(0);
   }

   fprintf(t2, "%s", cwd);
   fclose(t2);
  


   // rename t2 -> path-info
   char old[] = "t2.txt";
   char new[] = "path-info.txt";
   int renaming = rename(old,new);
   if(renaming == 0) {
       printf("File t2 successfully renamed path-info.\n");
   } else {
       perror("There was an issue, renaming file t2 failed.\n");
   }

   //concat files tree and path -> t3
   FILE *tree = fopen("tree.txt", "r");
   FILE *path = fopen("path-info.txt", "r");

   FILE *t3 = fopen("t3.txt", "w");
   char c;

   if (tree == NULL || path == NULL || t3 == NULL){
   perror("Error opening files \n");
   exit(0);
   }

   // Copy contents of first file to file3.txt
   while ((c = fgetc(tree)) != EOF)
   fputc(c, t3);

   // Copy contents of second file to file3.txt
   while ((c = fgetc(path)) != EOF)
       fputc(c, t3);

   printf("Merged tree and path-info into t3 \n");
   fclose(tree);
   fclose(path);
   fclose(t3);



   // rename t3 -> log
   char old2[] = "t3.txt";
   char new2[] = "log.txt";
   int renaming2 = rename(old2,new2);
   if(renaming2 == 0) {
       printf("File t3 was successfully renamed log.\n");
   } else {
       perror("There was an issue, renaming file t3 failed.\n");
   }


   // delete file tree and path
   if (remove("tree.txt") == 0){
       printf("Deleted tree file successfully\n");}
   else {
       printf("Unable to delete the tree file\n");
   }

   if (remove("path-info.txt") == 0) {
       printf("Deleted path-info successfully\n");
   }
   else {
       printf("Unable to delete the path-info file\n");
   }


  
   //exit(EXIT_SUCCESS);
  
}




