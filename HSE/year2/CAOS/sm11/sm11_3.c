// Данная задача была решена на семе 
//https://github.com/freepvps/hseos/blob/master/src/bufread/main.c

#include <asm/unistd_32.h>
#include <unistd.h>
#include <stddef.h>

enum { BUF_SIZE = 4096 };

struct FileReadState
{
    int fd;              // "файловый дескриптор", для чтения со стандартного потока ввода - 0
    unsigned char *buf;  // указатель на буфер
    int bufsize;         // размер буфера
    int lc;              // последний считанный символ
    int offset;
    int size;
};


static char buffer[BUF_SIZE];

struct FileReadState beg_stin = {
    0,
    buffer,
    BUF_SIZE,
    -1,
    0,
    0
};

struct FileReadState *stin = &beg_stin;

int asm_read(int fd, char * buf, size_t bs) {
    volatile int ch = -1;
    asm volatile(
        "movl   $3, %%eax\n\t" 
        "movl   %[filed], %%ebx\n\t"
        "movl   %[ptr], %%ecx\n\t"
        "movl   %[bufsize], %%edx\n\t"
        "int     $0x80\n\t"
        "movl   %%eax, %[res]\n\t"
        : [res]"=g"(ch)
        : [filed]"g"(fd), [ptr]"g"(buf), [bufsize]"g"(bs)
        : "%eax", "%ebx", "%ecx", "%edx", "memory"
    );
    return ch;
}

int lastchar() {
    return  stin->lc;
}

int buf_nextchar(int fd) {
    int ch = -1;
    if (stin->offset < stin->size) {
        stin->lc = stin->buf[stin->offset];
        stin->offset += 1;
        ch = lastchar();
    }
    return ch;
}


int nextchar() {
    int ch = buf_nextchar(stin->fd);
    if (ch != -1) {
        return ch;
    }
    stin->offset = 0;
    stin->size = 0;
    int qty = asm_read(stin->fd, stin->buf, stin->bufsize);
    if (qty <= 0) {
        stin->lc = -1;
        ch = -1;
    } else {
        stin->size = qty;
        ch = buf_nextchar(stin->fd);
    }
    return ch;
}
