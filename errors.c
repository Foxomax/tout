#include "terminal.h"

const char ARGUMENT_ERROR[] = ANSI_RED
    "Error, you need to pass 2 arguments [timeout, command]\n" ANSI_RESET;

const char NO_ARGUMENTS_ERROR[] = ANSI_RED
    "You need to pass arguments, use -h for help.\n" ANSI_RESET;

const char OOM_ERROR[] = ANSI_RED
    "Out of memory.\n" ANSI_RESET;

const char PARSING_TIMEOUT_ERROR[] = ANSI_RED
    "Error in parsing timeout\n" ANSI_RESET;
