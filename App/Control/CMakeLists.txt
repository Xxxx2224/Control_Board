add_library(Control STATIC)

target_sources(Control 
            PRIVATE Src/PID_controller.c
            PUBLIC
                FILE_SET HEADERS
                BASE_DIRS Inc
                FILES
                Inc/PID_controller.h
            )

target_link_libraries(Control PUBLIC Error)

