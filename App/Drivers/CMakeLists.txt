add_library(Drivers STATIC)

target_sources(Drivers 
            PRIVATE Gpio/Src/gpio.c
            PUBLIC
                FILE_SET HEADERS
                BASE_DIRS Gpio/Inc
                FILES
                    Gpio/Inc/h755_gpio.h
            )
