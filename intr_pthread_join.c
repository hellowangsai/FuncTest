#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

int stop = 0;
void* f(void* aaa) {
    printf("in f, pid: %d\n", pthread_self());
    while (stop == 0) {
       sleep(6);
       printf("f() errno: %d\n", errno);
       fflush(stdout);
    }
    sleep(10);
    return NULL;
}

void handle_signal(int signal) {
    stop = 1;
    printf("in signal, pid: %d\n", pthread_self()); // in my test, pid is same as main.
    fflush(stdout);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = &handle_signal;
    sa.sa_flags = SA_RESTART;
    sigfillset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    pthread_t thread;
    int ret;
    ret = pthread_create(&thread, NULL, f, NULL);
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ret = -1;
    printf("in main, pid: %d\n", pthread_self());
    fflush(stdout);
    while (ret != 0) {
        ts.tv_sec += 5;
        ret = pthread_timedjoin_np(thread, NULL, &ts);
        printf("ret code: %d, errno: %d\n", ret, errno);
        // sleep(5); // sleep can be interrupted, and set errno to EINTR.
    }
}
