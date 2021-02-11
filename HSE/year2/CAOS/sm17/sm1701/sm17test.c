

extern char **environ;

int main() 
{
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork: %s\n", strerror(errno));
        exit(1);
    }

    if (!pid) {
        char * envs[] = {"A=1", "B=2", NULL};
        char * args[] = {"/usr/bin/ls", "-l", "/", NULL};
        execve("/usr/sbin/busybox", args, environ);
        fprintf(stderr, "execve() : %s\n", strerror(errno));
        _exit(1);
    }
    wait(NULL);
}