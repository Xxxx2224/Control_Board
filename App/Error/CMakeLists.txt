add_library(Error INTERFACE)
target_sources(Error INTERFACE Inc/emc_assert.h
            INTERFACE
                FILE_SET HEADERS
                BASE_DIRS Inc
                FILES
                    Inc/emc_assert.h
                    Inc/emc_error.h)
