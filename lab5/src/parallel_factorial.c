#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

int k = -1, mod = -1, pnum = -1;
int res = 1;


void factorial(int* this_pnum) {
    int start;
    int ans = 1;
    int end = k / pnum * (*this_pnum); 
    if (pnum != 1 && *this_pnum == pnum - 1 && (k + pnum) % 2 != 0)
        start = k / pnum * (*this_pnum + 1) + 1;
    else
        start = k / pnum * (*this_pnum + 1);
    printf("%d %d %d\n", start, end, *this_pnum);
    for (; start > end; start--) {
        ans = (ans * start) % mod;
        printf("%d\n", ans);
    }
    printf("%d\n", ans);
    pthread_mutex_lock(&mut);
    res = res * ans % mod;
    pthread_mutex_unlock(&mut);
}

int main(int argc, char *argv[]) {

    while (true) {
        int current_optind = optind ? optind : 1;

        static struct option options[] = {{"k", required_argument, 0, 0},
                                        {"pnum", required_argument, 0, 0},
                                        {"mod", required_argument, 0, 0},
                                        {0, 0, 0, 0}};

        int option_index = 0;
        int c = getopt_long(argc, argv, "f", options, &option_index);

        if (c == -1) break;

        switch (c) {
        case 0:
            switch (option_index) {
            case 0:
                k = atoi(optarg);
                if (k < 1) {
                    printf("Error: num must be positive number\n");
                    return(1);
                }
                // error handling
                break;
            case 1:
                pnum = atoi(optarg);
                if (pnum < 1) {
                    printf("Error: pnum must be positive number\n");
                    return(1);
                }
                // error handling
                break;
            case 2:
                mod = atoi(optarg);
                if (mod < 2) {
                    printf("Error: mod must be more than one");
                    return(1);
                }
                break;

            defalut:
                printf("Index %d is out of options\n", option_index);
            }
            break;

        case '?':
            break;

        default:
            printf("getopt returned character code 0%o?\n", c);
        }
    }

    if (optind < argc) {
        printf("Has at least one no option argument\n");
        return 1;
    }

    if (k == -1 || mod == -1 || pnum == -1) {
        printf("Usage: %s -k \"num\" --pnum \"num\" --mod \"num\" \n",
            argv[0]);
        return 1;
    }
    // закончено введение аргументов
    pthread_t thread[pnum];
    int this_pnum[pnum];

    for(int i = 0; i < pnum; i++) {
        this_pnum[i] = i;
        if (pthread_create(&thread[i], NULL, (void *)factorial, (void *)&this_pnum[i]) != 0){
            perror("pthread_create");
            exit(1);
        }
    }

    for (int i = 0; i < pnum; i++) {
        if (pthread_join(thread[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }

    printf("%d\n", res);
    return 0;
}