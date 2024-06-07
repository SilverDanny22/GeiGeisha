#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[], char *envp[]) {
        if(argc>1) {
                printf("Kolichestvo parametrov programmy %d\n", argc);
                for (int i=0; i<argc; i++) {
                        printf("Parametr %d: %s\n", i, argv[i]);
                }
        }
        else {
                int j=0;
                while (envp[j]!=NULL) {
                        printf("Znachenye parametra %d: %s\n", j,  envp[j]);
                        j++;
                }
        }
        return 0;
}
