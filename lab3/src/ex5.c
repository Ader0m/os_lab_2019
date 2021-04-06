#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <getopt.h>

int main() {
    pid_t child_pid = fork();
    if (child_pid >= 0)
            printf("Fork: successfully\n");
    if (child_pid == 0) {
        execl("sequental_min_max", "sequental_min_max", "5", "4", NULL);
    }
    else
        exit(0);
}