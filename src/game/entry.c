#include <system/platform.h>

typedef struct {
    bool vsync_disabled;
} user_config_t;

app_desc_t app_main() {
    user_config_t user_config;
    user_config.vsync_disabled = false;

    return (app_desc_t){
        .title = "Chess GUI",
        .vsync_disabled = user_config.vsync_disabled
    };
}