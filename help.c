#include "help.h"
#include "terminal.h"
#include "utils.h"

const char HELP_TEXT[] =
    ANSI_BOLD "USAGE:\n" ANSI_RESET
              "    tout [TIMEOUT] [COMMAND...]\n\n" ANSI_BOLD "DESCRIPTION:\n" ANSI_RESET
              "    Executes the specified COMMAND with a TIMEOUT in seconds.\n"
              "    If the command exceeds the timeout, it will be forcefully terminated.\n\n" ANSI_BOLD "OPTIONS:\n" ANSI_RESET
              "    -h, --help    Show this help message and exit.\n\n" ANSI_BOLD "EXAMPLES:\n" ANSI_RESET
              "    tout 5 sleep 10\n"
              "    tout 3 ls -la\n";

void generate_help_flags(StringVector *vec)
{
    init_vector(vec);
    add_element(vec, "-h");
    add_element(vec, "--help");
}

int is_help_flag(char *flag)
{
    int flag_match = 0;
    StringVector allowed_flags;
    generate_help_flags(&allowed_flags);
    for (int i = 0; i < allowed_flags.count; i++)
    {
        if (strcmp(allowed_flags.items[i], flag))
        {
            flag_match = 1;
            break;
        }
    }
    free_vector(&allowed_flags);
    return flag_match;
}
