#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
        int semid;
        char pathname[] = "for_ipc.ipc";
        key_t key;
        struct sembuf mybuf;
        if((key = ftok(pathname, 0)) < 0) {
                printf("Ne udalos sgenerirovat kluch ipc\n");
                exit(-1);
        }
        if((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
                printf("Ne udalos poluchit  deskriptor massiva cemafora\n");
                exit(-1);
        }
        mybuf.sem_op = 1;
        mybuf.sem_flg = 0;
        mybuf.sem_num = 0;
        printf("Razblokirovka processa, zapushenogo ranee\n");
        if(semop(semid, &mybuf, 1) <0) {
                printf("Ne udalos vypolnit operaciy nad cemaforom\n");
                exit(-1);
        }
        printf("Znahenye cemafora ustanovleno v edinicu\n");
        return 0;
}
