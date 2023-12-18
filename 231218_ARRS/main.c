
#include "repository.h"
#include "service.h"
#include "input_interface.h"

int main() {
    initRepository();
    initService();
    startCLI();
    return 0;
}

