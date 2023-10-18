#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <sys/time.h>

#define NUM_PROCESSES 3

FILE *fp;
void call_fifo()
{
    struct timeval start_time, end_time;
    pid_t child_pid;

    // Get the current time before starting the execution
    gettimeofday(&start_time, NULL);

    // Create a child process
    child_pid = fork();

    if (child_pid == -1)
    {
        perror("Fork failed");
    }

    if (child_pid == 0)
    {
        // This code runs in the child process

        // Set the FIFO scheduling policy for the child process with default parameter
        struct sched_param param;
        param.sched_priority = 99;
        if (sched_setscheduler(0, SCHED_FIFO, &param) == -1)
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

        printf("Execution time of FIFO: %.6f seconds\n", execution_time);
        fp = fopen("FIFO.txt", "w");
        fprintf(fp, "%.6f\n", execution_time);
        fclose(fp);
    }
}

void call_rr()
{
    struct timeval start_time, end_time;
    pid_t child_pid;

    // Get the current time before starting the execution
    gettimeofday(&start_time, NULL);

    // Create a child process
    child_pid = fork();

    if (child_pid == -1)
    {
        perror("Fork failed");
    }

    if (child_pid == 0)
    {
        // This code runs in the child process

        // Set the FIFO scheduling policy for the child process with default parameter
        struct sched_param param;
        param.sched_priority = 1;
        if (sched_setscheduler(0, SCHED_RR, &param) == -1)
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

        fp = fopen("RR.txt", "w");
        fprintf(fp, "%.6f \n", execution_time);
        fclose(fp);
    }
}

void call_other()
{
    struct timeval start_time, end_time;
    pid_t child_pid;

    // Get the current time before starting the execution
    gettimeofday(&start_time, NULL);

    // Create a child process
    child_pid = fork();

    if (child_pid == -1)
    {
        perror("Fork failed");
    }

    if (child_pid == 0)
    {
        // This code runs in the child process

        // Set the FIFO scheduling policy for the child process with default parameter
        struct sched_param param;
        param.sched_priority = 0;
        if (sched_setscheduler(0, SCHED_OTHER, &param) == -1)
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

        printf("Execution time of OTHER: %.6f seconds\n", execution_time);

        fp = fopen("OTHER.txt", "w");
        fprintf(fp, "%.6f \n", execution_time);
        fclose(fp);
    }
}

int main()
{
    long FIFO_time, RR_time, Other_time;
    int pid1 = fork();
    if (pid1 == 0)
    {
        call_fifo();
    }
    else
    {
        int pid2 = fork();
        if (pid2 == 0)
        {
            call_rr();
        }
        else
        {
            int pid3 = fork();
            if (pid3 == 0)
            {
                call_other();
            }
            else
            {
                wait(NULL);
                wait(NULL);
                wait(NULL);
            }
        }
    }
}
