#include <fcntl.h>
#include <minos/sysstd.h>
#include <minos/fsdefs.h>
#include <minos/status.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define O_EXCL 0200

const char* shift_args(int *argc, const char ***argv) {
    if((*argc) <= 0) return NULL;
    const char* arg = **argv;
    (*argc)--;
    (*argv)++;
    return arg;
}
void usage(FILE* sink, const char* exe) {
    fprintf(sink, "%s [file to create...]\n", exe);
}

intptr_t touch(const char* filename) {
    Stats stats;

    if (stat(filename, &stats) >= 0) {
        fprintf(stderr, "File already exists.\n");
        return 0;
    }

    intptr_t fd = open(filename, 0644, O_CREAT | O_EXCL);
    if (fd == -1) {
        fprintf(stderr, "Error: File could not be created.\n");
        return -1;
    }

    return 0;
}

int main(int argc, const char** argv) {
    const char* arg;
    const char* exe = shift_args(&argc, &argv);
    assert(exe && "Expected exe. Found nothing");

    if(argc <= 0) {
        usage(stderr, exe);
    }

    arg=shift_args(&argc, &argv);
    touch(arg);

    return 0;
}
