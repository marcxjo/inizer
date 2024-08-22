add_executable(
        inizer main.c
        inizer-api.c
        inizer-str.c
        inizer-logging.c
)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GLIB REQUIRED glib-2.0)

include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})
add_definitions(${GLIB_CFLAGS_OTHER})
target_link_libraries(inizer ${GLIB_LIBRARIES})