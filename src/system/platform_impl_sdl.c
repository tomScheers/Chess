#include <system/platform.h>
app_desc_t g_app_desc = {0};

int main() {
    g_app_desc = app_main();
    return 0;
}