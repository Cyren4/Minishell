#include <sys/types.h>
#include <signal.h>

int main(void)
{
    // kill(0, SIGTERM);
    // kill(0, SIGSEGV);
    // kill(0, SIGBUS);
    kill(0, SIGABRT);
    return (0);   
}