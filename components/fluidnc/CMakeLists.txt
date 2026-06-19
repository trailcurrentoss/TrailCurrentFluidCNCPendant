# Both backends are in SRCS. Each gates itself on CONFIG_FLUIDNC_USE_MOCK at
# the top of its file, so `idf.py menuconfig` flips between them with a
# rebuild only — no CMake reconfigure needed.
idf_component_register(
    SRCS
        "src/fluidnc.c"
        "src/fluidnc_mock.c"
        "src/proto.c"
        "src/transport_ws.c"
        "src/transport_uart.c"
        "src/transport_telnet.c"
    INCLUDE_DIRS "include"
    PRIV_INCLUDE_DIRS "src"
    REQUIRES pendant_config esp_timer
    PRIV_REQUIRES
        freertos
        esp_event
        esp_driver_uart
        espressif__esp_websocket_client
)
