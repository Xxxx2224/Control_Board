add_library(Drivers INTERFACE)

target_sources(Drivers 
    INTERFACE Src/emc_gpio.c
    INTERFACE
                FILE_SET HEADERS
                BASE_DIRS Inc
                FILES
                    Inc/emc_h755_gpio.h
            )
