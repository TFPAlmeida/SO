#include <stdio.h>
#include "process.h"
#include "pipes.h"

int main(int argc, char * argv[]) {
    main_process(argc, argv);
    main_pipes(argc, argv);
    return 0;
}
