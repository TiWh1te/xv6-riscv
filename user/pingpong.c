#include "../kernel/types.h"
#include "user.h"

int main() {
    int p2c[2]; 
    int c2p[2]; 
    char buf[5];


    if (pipe(p2c) < 0 || pipe(c2p) < 0) {
        printf("pingpong: ошибка создания pipe\n");
        exit(1);
    }

    if (fork() == 0) {
      
        close(p2c[1]);
        close(c2p[0]);


        read(p2c[0], buf, 4);
        buf[4] = '\0';
        printf("%d: получил %s\n", getpid(), buf);


        write(c2p[1], "pong", 4);

        close(p2c[0]);
        close(c2p[1]);
        exit(0);
    } else {

        close(p2c[0]); 
        close(c2p[1]); 


        write(p2c[1], "ping", 4);


        read(c2p[0], buf, 4);
        buf[4] = '\0';
        printf("%d: получил %s\n", getpid(), buf);

        close(p2c[1]);
        close(c2p[0]);
        wait(0);
        exit(0);
    }
}
