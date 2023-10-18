#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sched.h>

int main()
{
    struct timeval start_time, end_time;
    pid_t child_pid;

    // Create a child process
    child_pid = fork();

    if (child_pid == -1)
    {
        perror("Fork failed");
        return 1;
    }
    gettimeofday(&start_time, NULL);
    if (child_pid == 0)
    {
        // This code runs in the child process

        // Set the FIFO scheduling policy for the child process
        struct sched_param param;
        param.sched_priority = 50;

        if (sched_setscheduler(getpid(), SCHED_RR, &param) == -1)
        {
            perror("Error setting FIFO scheduler");
            exit(1);
        }
        // Execute the program using execvp
        char *const args[] = {"./Counter", NULL};

        execvp("./Counter", args);

        // If execvp fails, report an error
        perror("Execvp failed");
        exit(1);
    }
    else
    {
        // This code runs in the parent process

        // Wait for the child process to finish
        wait(NULL);

        // Get the current time after the execution
        gettimeofday(&end_time, NULL);

        // Calculate the execution time in seconds
        double execution_time = (end_time.tv_sec - start_time.tv_sec) +
                                (end_time.tv_usec - start_time.tv_usec) / 1e6;

        printf("Execution time of RR: %.6f seconds\n", execution_time);
    }

    return 0;
}
