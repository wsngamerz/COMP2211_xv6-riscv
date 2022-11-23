#include "kernel/types.h"
#include "user/user.h"
#include "user/memory_management.h"


int main(int argc, char *argv[]) {
    printf("This is the testingo programo\n");

    // this does nothing right now
    void* ptr = _malloc(10);
    _free(ptr);

    exit(0);
}
