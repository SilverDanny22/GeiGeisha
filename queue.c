#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define LAST_MESSAGE 255
int main() {
        int msqid;
        char pathname[] = "for_ipc.c";
        key_t key;
        int i, len;
        struct mymsgbuf {
                long mtype;
                char mtext[81];
        } mybuf;

        if((key = ftok(pathname, 0)) <0) {
                printf("Ne udalos sgenerirovat kluch ipc\n");
                exit(-1);
        }
        if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
                printf("Ne udalos sozdat ochered ili poluchit k nei dostup\n");
                exit(-1);
        }
        for (i = 1; i <= 5; i++) {
                mybuf.mtype = 1;
                strcpy(mybuf.mtext, "Soobshenye ot programmy queue.out");
                len = strlen(mybuf.mtext) + 1;
                if (msgsnd(msqid, (struct msgbuf*) &mybuf, len, 0) <0) {
                        printf("Ne udalos otpravit soobshenye v ochered\n");
                        msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
                        exit(-1);
                }
         }
         mybuf.mtype = LAST_MESSAGE;
         len = 0;
         if (msgsnd(msqid, (struct msgbuf*) &mybuf, len, 0) <0) {
                        printf("Ne udalos otpravit soobshenye v ochered\n");
                        msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
                        exit(-1);
         }
         return 0;
} 
