#include "terminal.h"
#include "errors.h"

const char ARGUMENT_ERROR[] = ANSI_RED
    "Error: you must provide 2 arguments [timeout, command]; you can use -h for help.\n" ANSI_RESET;

const char NO_ARGUMENTS_ERROR[] = ANSI_RED
    "You need to pass arguments, use -h for help.\n" ANSI_RESET;

const char OOM_ERROR[] = ANSI_RED
    "Out of memory.\n" ANSI_RESET;

const char PARSING_TIMEOUT_ERROR[] = ANSI_RED
    "Error parsing the timeout; you must provide a valid number.\n" ANSI_RESET;

const char SIGACTION_ERROR[] = ANSI_RED
    "Error registering sigaction\n" ANSI_RESET;

const char TIMEOUT_ERROR[] = ANSI_RED "Timeout exceeded...\n" ANSI_RESET;
