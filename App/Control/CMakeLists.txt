add_library(Control INTERFACE)

target_sources(Control 
    INTERFACE Src/PID_controller.c
    INTERFACE
                FILE_SET HEADERS
                BASE_DIRS Inc
                FILES
                Inc/PID_controller.h
            )

            target_link_libraries(Control INTERFACE Error)

