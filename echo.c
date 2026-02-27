#define SYS_WRITE 4

#define STD_OUT 1

long syscall3(long syscall_num, long arg0, long arg1, long arg2) {
    long ret;

    asm volatile(
        "mov x16, %1\n"
        "mov x0, %2\n"
        "mov x1, %3\n"
        "mov x2, %4\n"
        "svc #0\n"
        "mov %0, x0\n"
        : "=r" (ret)
        : "r" (syscall_num), "r" (arg0), "r" (arg1), "r" (arg2)
    );

    return ret;
}

long len(char *s) {
    char *cursor = s;
    while (*cursor) {
        cursor++;
    }
    return (long)(cursor - s);
}

int puts(char *s) {
    long out = (long)s;
    long length = len(s);

    syscall3(SYS_WRITE, STD_OUT, out, length);
    return 0;
}

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        puts(argv[i]);
        puts(" ");
    }
    puts("\n");
}

void start() {
    long argc;
    long argv;

    asm volatile(
        "mov %0, x0\n"
        "mov %1, x1\n"
        : "=r" (argc), "=r" (argv)
    );
    
    main((int)argc, (char **)argv);   
}