#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
int main() {
        int fd;
        size_t size;
        char string[] = "Gr. 3.124.2.23";
        if ((fd = open("wrfile.txt", O_WRONLY|O_CREAT, 0666))<0) {
                printf("Ne udalos otryt file\n");
                exit(-1); 
        }
        size = write(fd ,string, 14);
        if (size !=14) {
                printf("Ne udalos zapysat v file iz 14 byte\n");
                exit(-1);
        }
        printf("Stroka zapisanav file wrfile.txt\n");
        if (close(fd) <0) {
                printf("Ne udalos zakryt file\n");
                exit(-1);
        }
        return 0;
}
