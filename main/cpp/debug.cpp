#include <excentury/excentury.h>

int main() {
    debug("This message is only seen with DEBUG set to 2\n");
    trace("This message is only seen with DEBUG set to 3\n");
    printf("Hello world\n");
    exitif(true, NULL, "This is a test to check that DEBUG is on.\n");
    printf("Debug was turned off...\n");
}
