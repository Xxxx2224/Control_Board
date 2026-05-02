add_library(Control INTERFACE)

target_link_libraries(Control INTERFACE Error)

target_sources(Control
            PUBLIC
                FILE_SET HEADERS
                BASE_DIRS Inc
                FILES
                Inc/PID_controller.h
            )




