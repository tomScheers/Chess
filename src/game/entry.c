#include <system/platform.h>
#include <game/config.h>
#include <stdio.h>

app_desc_t app_main() {
    user_config_t user_config = {0};
#ifdef __EMSCRIPTEN__
    set_user_config_defaults(&user_config);
#else
    user_config = load_or_create_user_config("config.json");
#endif

    printf("%i\n", user_config.vsync_disabled);
    fflush(stdout);

    return (app_desc_t){
        .title = "Chess GUI",
        .vsync_disabled = user_config.vsync_disabled
    };
}