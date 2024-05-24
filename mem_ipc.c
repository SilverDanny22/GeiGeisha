#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main() {
        int *array;
        int shmid;
        int new = 1;
        char pathname[] = "for_ipc.ipc";
        key_t key;
        if((key = ftok(pathname, 0)) < 0) {
                printf("Ne udalos sgenerirovat kluch\n");
                exit(-1);
        }
        if((shmid = shmget(key, 3*sizeof(int), 0666 | IPC_CREAT | IPC_EXCL) <0)) {
                if (errno != EEXIST) {
                        printf("Ne udalos sozdat segment razdelyaemoi pamyati\n");
                        exit(-1);
                }
                else {
                        if((shmid = shmget(key, 3*sizeof(int), 0)) < 0) {
                                printf("Ne udalos naiti oblast razdelyaemoi pamyati\n");
                                exit(-1);
                        }
                        new  = 0;
                }
        }
        if((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
                printf("Ne udalos podsoedinit segment r adr.prostranstvu tekushego processa\n");
                exit(-1);
        }
        if (new) {
                array[0] = 1;
                array[1] = 0;
                array[2] = 1;
        }
        else {
                array[0] += 1;
                array[2] += 1;
        }
        printf("Programma 1 zapuskalas %d raz(a), programma 2 - %d raz(a), vsego zapuskalos - %d\n", array[0], array[1], array[2]);
        if(shmdt(array) <0) {
                printf("Ne udalos iscluchit segment iz adresnogo prostranstva tekushego processa\n");
                exit(-1);
        }
        return 0;
}
