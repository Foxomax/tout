#include "help.h"
#include "terminal.h"

const char HELP_TEXT[] =
    ANSI_BOLD "USAGE:\n" ANSI_RESET
              "    tout [TIMEOUT] [COMMAND...]\n\n" ANSI_BOLD "DESCRIPTION:\n" ANSI_RESET
              "    Executes the specified COMMAND with a TIMEOUT in seconds.\n"
              "    If the command exceeds the timeout, it will be forcefully terminated.\n\n" ANSI_BOLD "OPTIONS:\n" ANSI_RESET
              "    -h, --help    Show this help message and exit.\n\n" ANSI_BOLD "EXAMPLES:\n" ANSI_RESET
              "    tout 5 sleep 10\n"
              "    tout 3 ls -la\n";