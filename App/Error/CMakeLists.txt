add_library(Error INTERFACE)
target_sources(Error 
            INTERFACE
                FILE_SET HEADERS
                BASE_DIRS Inc
                FILES
                    Inc/emc_error.h)
