# Find the CUnit includes and library
#
# This module defines
# LIBCONFIG_INCLUDE_DIR, where to find cppunit include files, etc.
# LIBCONFIG_LIBRARIES, the libraries to link against to use libconfig++.
# LIBCONFIG_FOUND, If false, do not try to use libconfig++.

# also defined, but not for general use are
# LIBCONFIG_LIBRARY, where to find libconfig++.

FIND_PATH(LIBCONFIG_INCLUDE_DIR libconfig.h++
  /usr/local/include
  /usr/include
  ~/libs/include
  ~/include
)

FIND_LIBRARY(LIBCONFIG_LIBRARY config++
  /usr/local/lib
  /usr/lib
  ~/libs/lib
)

IF(LIBCONFIG_INCLUDE_DIR)
  IF(LIBCONFIG_LIBRARY)
    SET(LIBCONFIG_FOUND TRUE)
    SET(LIBCONFIG_LIBRARIES ${LIBCONFIG_LIBRARY})
  ENDIF(LIBCONFIG_LIBRARY)
ENDIF(LIBCONFIG_INCLUDE_DIR)

IF (LIBCONFIG_FOUND)
   IF (NOT LibConfig_FIND_QUIETLY)
      MESSAGE(STATUS "Found LibConfig++: ${LIBCONFIG_LIBRARIES}" )
   ENDIF (NOT LibConfig_FIND_QUIETLY)
ELSE (LIBCONFIG_FOUND)
   IF (LibConfig_FIND_REQUIRED)
      MESSAGE(SEND_ERROR "Could NOT find LibConfig")
   ENDIF (LibConfig_FIND_REQUIRED)
ENDIF (LIBCONFIG_FOUND)

MARK_AS_ADVANCED(LIBCONFIG_INCLUDE_DIR LIBCONFIG_LIBRARIES)
