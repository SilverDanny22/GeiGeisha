#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
        int semid; //IPC-deskriptor dlya massiva cemafora
        char pathname[] = "for_ipc.ipc"; //Imya file, s pomochyu kotorogo generiruetsa ipc-kluch
        key_t key; //Peremennaya dlya hranenya ipc-klucha
        struct sembuf mybuf; //Structura dannyh, zadayuchaya operacii nad opredelennym cemaforom
        //Process generacii ipc-klucha
        if((key = ftok(pathname,0)) < 0) {
                printf("Ne udalos sgenerirovat kluch ipc\n");
                exit(-1);
        }
        //Process poluchenya dostupa k massivu cemaforov dlya konkretnogo ipc-klucha
        //Esli massiva cemaforov ne suchestvuet, to pytaemsya sozdat ego
        if((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
                printf("Ne udalos poluchit  deskriptor massiva cemafora\n");
                exit(-1);
        }
        mybuf.sem_op = -1; //Kodirovanye operacii D(semidi,1)
        mybuf.sem_flg = 0;
        mybuf.sem_num = 0;
        //Operacii budut osuchestvlyatsya nad cemaforom 0, kod operacii -1
        printf("Oshidanye raznlokirovki tekuchego processa\n");
        //Vypolnyaem operacii nad cemaforom
        if(semop(semid, &mybuf, 1) <0) {
                printf("Ne udalos vypolnit operaciy nad cemaforom\n");
                exit(-1);
        }
        printf("Tekuchi process razblokirovan\n");
        return 0;
}
