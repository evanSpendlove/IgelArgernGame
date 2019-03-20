#include <stdio.h>

#define N_BLACK   "\x1b[30m"
#define N_RED     "\x1b[31m"
#define N_GREEN   "\x1b[32m"
#define N_YELLOW  "\x1b[33m"
#define N_BLUE    "\x1b[34m"
#define N_MAGENTA "\x1b[35m"
#define N_CYAN    "\x1b[36m"
#define N_WHITE   "\x1b[37m"

#define NBG_BLACK   "\x1b[40m"
#define NBG_RED     "\x1b[41m"
#define NBG_GREEN   "\x1b[42m"
#define NBG_YELLOW  "\x1b[43m"
#define NBG_BLUE    "\x1b[44m"
#define NBG_MAGENTA "\x1b[45m"
#define NBG_CYAN    "\x1b[46m"
#define NBG_WHITE   "\x1b[47m"

#define S_BLACK   "\x1b[90m"
#define S_RED     "\x1b[91m"
#define S_GREEN   "\x1b[92m"
#define S_YELLOW  "\x1b[93m"
#define S_BLUE    "\x1b[94m"
#define S_MAGENTA "\x1b[95m"
#define S_CYAN    "\x1b[96m"
#define S_WHITE   "\x1b[97m"

#define SBG_BLACK   "\x1b[100m"
#define SBG_RED     "\x1b[101m"
#define SBG_GREEN   "\x1b[102m"
#define SBG_YELLOW  "\x1b[103m"
#define SBG_BLUE    "\x1b[104m"
#define SBG_MAGENTA "\x1b[105m"
#define SBG_CYAN    "\x1b[106m"
#define SBG_WHITE   "\x1b[107m"

#define RESET  "\x1b[0m"
#define BOLD  "\x1b[1m"
#define UNDERLINE "\x1b[4m"
#define INVERSE "\x1b[7m"

int main(void)
{
    printf(RESET);

    // REGULAR
    printf(N_BLACK "Hi" N_WHITE);
    printf(N_RED "\tHi" N_WHITE);
    printf(N_GREEN "\tHi" N_WHITE);
    printf(N_YELLOW "\tHi" N_WHITE);
    printf(N_BLUE "\tHi" N_WHITE);
    printf(N_MAGENTA "\tHi" N_WHITE);
    printf(N_CYAN "\tHi\n\n" N_WHITE);

    // NORMAL BG
    printf(NBG_WHITE "Hi" NBG_BLACK);
    printf(NBG_RED "\tHi" NBG_BLACK);
    printf(NBG_GREEN "\tHi" NBG_BLACK);
    printf(NBG_YELLOW "\tHi" NBG_BLACK);
    printf(NBG_BLUE "\tHi" NBG_BLACK);
    printf(NBG_MAGENTA "\tHi" NBG_BLACK);
    printf(NBG_CYAN "\tHi\n\n" RESET);

    // STRONG
    printf(S_BLACK "Hi" S_WHITE);
    printf(S_RED "\tHi" S_WHITE);
    printf(S_GREEN "\tHi" S_WHITE);
    printf(S_YELLOW "\tHi" S_WHITE);
    printf(S_BLUE "\tHi" S_WHITE);
    printf(S_MAGENTA "\tHi" S_WHITE);
    printf(S_CYAN "\tHi\n\n" S_WHITE);

    // STRRONG BG
    printf(SBG_WHITE "Hi" RESET);
    printf(SBG_RED "\tHi" RESET);
    printf(SBG_GREEN "\tHi" RESET);
    printf(SBG_YELLOW "\tHi" RESET);
    printf(SBG_BLUE "\tHi" RESET);
    printf(SBG_MAGENTA "\tHi" RESET);
    printf(SBG_CYAN "\tHi\n\n" RESET);

    printf(RESET);

    printf(BOLD "Bold text!\n" RESET);
    printf(UNDERLINE "Underlined!\n" RESET);
    printf(INVERSE "I don't know what this is\n" RESET);

    printf(BOLD N_BLUE "Blue!\n" RESET);
    printf(BOLD N_RED INVERSE "Weird..\n" RESET);

    return 0;
}