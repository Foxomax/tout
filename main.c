#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include "utils.h"
#include "terminal.h"
#include "help.h"
#include "errors.h"

static volatile sig_atomic_t timeout_hit = 0;

struct task_config
{
    long timeout;
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
        fprintf(stderr, "%s", NO_ARGUMENTS_ERROR);
        exit(EXIT_FAILURE);
    }
    else if (argc == 2 && is_help_flag(argv[1]))
    {
        fputs(HELP_TEXT, stdout);
        exit(EXIT_SUCCESS);
    }
    else if (argc < 3)
    {
        fprintf(stderr, "%s", ARGUMENT_ERROR);
        exit(EXIT_FAILURE);
    }
    struct task_config cfg;

    if ((cfg.timeout = parsing_to_long(argv[1])) <= 0)
    {
        fprintf(stderr, "%s", PARSING_TIMEOUT_ERROR);
        exit(EXIT_FAILURE);
    }

    if (init_vector(&cfg.commands) != 0)
    {
        fprintf(stderr, "%s", OOM_ERROR);
        exit(EXIT_FAILURE);
    }

    struct sigaction wake_up = {0};
    wake_up.sa_handler = handle_alarm;

    sigemptyset(&wake_up.sa_mask);

    if (sigaction(SIGALRM, &wake_up, NULL) < 0)
    {
        free_vector(&cfg.commands);
        fprintf(stderr, "Error registering sigaction");
        exit(EXIT_FAILURE);
    }

    for (int i = 2; i < argc; i++)
    {
        if (add_element(&cfg.commands, argv[i]) == -1)
        {
            free_vector(&cfg.commands);
            fprintf(stderr, "%s", OOM_ERROR);
            exit(EXIT_FAILURE);
        }
    }

    if (add_element(&cfg.commands, NULL) == -1)
    {
        free_vector(&cfg.commands);
        fprintf(stderr, "%s", OOM_ERROR);
        exit(EXIT_FAILURE);
    }

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
        setpgid(0, 0);
        execvp(cfg.commands.items[0], cfg.commands.items);
        perror("execvp failed");
        free_vector(&cfg.commands);
        exit(EXIT_FAILURE);
    }
    else
    {
        setpgid(pid, pid);
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

        kill(-pid, SIGTERM);
        usleep(100000);

        if (waitpid(pid, &status, WNOHANG) == 0)
        {
            kill(-pid, SIGKILL);
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
