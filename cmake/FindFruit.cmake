#
# Locate Google Fruit include paths and libraries
# Fruit can be found at https://github.com/google/fruit

# This module defines
# FRUIT_INCLUDE_DIR, where to find header file.
# FRUIT_LIBRARIES, the libraries to link against to use fruit.
# FRUIT_FOUND, If false, don't try to use fruit.

FIND_PATH(FRUIT_INCLUDE_DIR fruit/fruit.h
PATHS
"$ENV{FRUIT}/include"
/usr/local/include
/usr/local/include/fruit/include
/usr/include
/usr/include/fruit/include
)

FIND_LIBRARY(FRUIT_LIBRARIES fruit
PATHS
"$ENV{FRUIT}/lib"
/usr/local/lib
/usr/lib
)

SET(FRUIT_FOUND 0)
IF(FRUIT_INCLUDE_DIR)
    IF(FRUIT_LIBRARIES)
        SET(FRUIT_FOUND 1)
        MESSAGE(STATUS "Found Google Fruit")
    ENDIF(FRUIT_LIBRARIES)
ENDIF(FRUIT_INCLUDE_DIR)

MARK_AS_ADVANCED(
FRUIT_INCLUDE_DIR
FRUIT_INCLUDE_DIR
)