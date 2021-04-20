#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child process... ID = %d\n", pid);
        exit(0);
    }
    else if (pid > 0) {
        printf("Parent process... ID = %d\n", pid);
        sleep(30);
    }
    else {
        printf("Fork failed...");
    }
    return 0;
}