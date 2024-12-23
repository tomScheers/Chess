#include <game/user_config.h>
#include <system/util.h>

#include <cJSON.h>

#include <unistd.h>

void set_user_config_defaults(user_config_t *config) {
    config->vsync_disabled = false;
}

user_config_t load_or_create_user_config(const char* filename) {
    user_config_t user_config = {0};
    cJSON *root = NULL;
    bool config_needs_update = false;

    if (access(filename, F_OK) != -1) {
        char* config_content = read_file_to_string(filename);
        if (config_content) {
            root = cJSON_Parse(config_content);
            free(config_content);

            if (!root) {
                printf("Error parsing JSON from config file\n");
                config_needs_update = true;
            } else {

                cJSON *system = cJSON_GetObjectItem(root, "system");
                cJSON *vsync_disabled_item = cJSON_GetObjectItem(system, "vsync_disabled");

                if (vsync_disabled_item) {
                    if (cJSON_IsBool(vsync_disabled_item)) {
                        user_config.vsync_disabled = vsync_disabled_item->valueint;
                    } else {
                        config_needs_update = true;
                    }
                } else {
                    config_needs_update = true;
                }
                
                cJSON_Delete(root);
            }
        } else {
            // File content does not exist
            config_needs_update = true;
        }
    } else {
        // File does not exist
        config_needs_update = true;
    }

    if (config_needs_update) {
        set_user_config_defaults(&user_config);
        root = cJSON_CreateObject();

        // Create system category
        cJSON *system = cJSON_AddObjectToObject(root, "system");
        cJSON_AddBoolToObject(system, "vsync_disabled", user_config.vsync_disabled);

        char *json_string = cJSON_PrintUnformatted(root);
        if (json_string) {
            write_string_to_file(filename, json_string);
            free(json_string);
        }

        cJSON_Delete(root);
    }

    return user_config;
}