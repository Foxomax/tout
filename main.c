#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include "utils.h"
#include "terminal.h"
#include <signal.h>

static volatile sig_atomic_t timeout_hit = 0;

struct task_config
{
    int timeout;
    StringVector commands;
};

void handle_alarm(int sig)
{
    (void)sig;
    timeout_hit = 1;
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        fprintf(stderr, ANSI_RED "You need to pass arguments, use -h for help.\n" ANSI_RESET);
        exit(EXIT_FAILURE);
    }
    else if (argc < 3)
    {
        fprintf(stderr, ANSI_RED "Error, you need to pass 2 arguments [timeout, command]\n" ANSI_RESET);
        exit(EXIT_FAILURE);
    }

    struct sigaction wake_up;
    wake_up.sa_handler = handle_alarm;

    sigemptyset(&wake_up.sa_mask);

    sigaction(SIGALRM, &wake_up, NULL);

    struct task_config cfg;
    cfg.timeout = atoi(argv[1]);
    init_vector(&cfg.commands);

    for (int i = 2; i < argc; i++)
    {
        add_element(&cfg.commands, argv[i]);
    }

    add_element(&cfg.commands, NULL);

    pid_t pid;
    pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        free_vector(&cfg.commands);
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        execvp(cfg.commands.items[0], cfg.commands.items);

        perror("execvp failed");
        free_vector(&cfg.commands);
        exit(EXIT_FAILURE);
    }

    alarm(cfg.timeout);

    int status;
    pid_t result;

    while ((result = waitpid(pid, &status, 0)) == -1 && errno == EINTR)
    {
        if (timeout_hit)
        {
            break;
        }
    }

    if (timeout_hit)
    {
        fprintf(stderr, ANSI_RED "Timeout exceeded...\n" ANSI_RESET);

        kill(pid, SIGTERM);
        usleep(100000);

        if (waitpid(pid, &status, WNOHANG) == 0)
        {
            kill(pid, SIGKILL);
            waitpid(pid, &status, 0);
        }

        printf(ANSI_CURSOR_SHOW);
        fflush(stdout);
    }
    else if (result > 0)
    {
        alarm(0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
            fprintf(stderr, ANSI_RED "Command failed with exit code: %d\n" ANSI_RESET, WEXITSTATUS(status));
        }
    }

    free_vector(&cfg.commands);

    return WIFEXITED(status) ? WEXITSTATUS(status) : EXIT_SUCCESS;
}