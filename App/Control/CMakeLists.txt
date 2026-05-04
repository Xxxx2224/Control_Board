add_library(Control)

target_link_libraries(Control PUBLIC Error)

target_sources(Control 
            PUBLIC Src/PID_controller.c
            PUBLIC
                FILE_SET HEADERS
                BASE_DIRS Inc
                FILES
                Inc/PID_controller.h
            )




