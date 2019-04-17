#include <stdio.h>

#define N_BLACK   "\033[30m"
#define N_RED     "\033[31m"
#define N_GREEN   "\033[32m"
#define N_YELLOW  "\033[33m"
#define N_BLUE    "\033[34m"
#define N_MAGENTA "\033[35m"
#define N_CYAN    "\033[36m"
#define N_WHITE   "\033[37m"

#define NBG_BLACK   "\033[40m"
#define NBG_RED     "\033[41m"
#define NBG_GREEN   "\033[42m"
#define NBG_YELLOW  "\033[43m"
#define NBG_BLUE    "\033[44m"
#define NBG_MAGENTA "\033[45m"
#define NBG_CYAN    "\033[46m"
#define NBG_WHITE   "\033[47m"

#define S_BLACK   "\033[90m"
#define S_RED     "\033[91m"
#define S_GREEN   "\033[92m"
#define S_YELLOW  "\033[93m"
#define S_BLUE    "\033[94m"
#define S_MAGENTA "\033[95m"
#define S_CYAN    "\033[96m"
#define S_WHITE   "\033[97m"

#define SBG_BLACK   "\033[100m"
#define SBG_RED     "\033[101m"
#define SBG_GREEN   "\033[102m"
#define SBG_YELLOW  "\033[103m"
#define SBG_BLUE    "\033[104m"
#define SBG_MAGENTA "\033[105m"
#define SBG_CYAN    "\033[106m"
#define SBG_WHITE   "\033[107m"

#define RESET  "\033[0m"
#define BOLD  "\033[1m"
#define UNDERLINE "\033[4m"
#define INVERSE "\033[7m"

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