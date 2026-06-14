idf_component_register(
    SRCS "src/fluidnc.c"
    INCLUDE_DIRS "include"
    REQUIRES pendant_config esp_timer
    PRIV_REQUIRES freertos
)
