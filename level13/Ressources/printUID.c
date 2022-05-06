# include <unistd.h>
# include <stdio.h>

int main(void)
{
    uid_t uid = 0;

    uid = getuid();
    dprintf(STDOUT_FILENO, "My UID is (%u)\n", uid);
    return 0;
}