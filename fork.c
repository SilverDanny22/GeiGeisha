#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
        pid_t procid, parentid, result;
        int a=0;
        result = fork();
        a=a+1;
        procid = getpid();
        parentid = getppid();

        printf("Id, next process: %d\n", procid);
        printf("Id, next parent process: %d\n", parentid);
        printf("Znachenie peremennoy a: %d\n", a);
        return 0;
}
