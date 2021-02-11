#include <asm/unistd_32.h>
#include <unistd.h>
#include <stddef.h>

enum { BUF_SIZE = 4 };

struct FileWriteState
{
    int fd;              // "файловый дескриптор", для вывода на стандартный поток вывода - 1
    unsigned char *buf;  // указатель на буфер
    int bufsize;         // размер буфера
    size_t offset;          // смещение
};

static char buffer[BUF_SIZE];

static struct FileWriteState file_out = {
    1,
    buffer,
    BUF_SIZE,
    0,
};

struct FileWriteState *stout = &file_out;

int asm_write(int fd, char * buf, int bs) {
    volatile int written = 0;
    asm volatile(
        "movl   $4, %%eax\n\t"
        "movl   %[file_descriptor], %%ebx\n\t"
        "movl   %[ptr], %%ecx\n\t"
        "movl   %[size], %%edx\n\t"
        "int    $0x80\n\t"
        "movl   %%eax, %[qty]"
        : [qty]"=g"(written)
        : [file_descriptor]"g"(fd), [ptr]"g"(buf), [size]"g"(bs)
        : "%eax", "%ebx", "%ecx", "%edx", "memory"
    );
    return written;
}



__attribute__((fastcall)) void flush(struct FileWriteState *out){
    asm_write(out->fd, out->buf, out->offset);
    out->offset = 0;
};

__attribute__((fastcall)) void writechar(int c, struct FileWriteState *out) {
    if (out->offset == out->bufsize) {
        flush(out);
    }
    out->buf[out->offset++] = c;
    return;
}
