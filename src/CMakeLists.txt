cmake_minimum_required(VERSION 3.5)

set(SOURCES
    gui/mainwindow.cpp
)

set(HEADERS
    gui/mainwindow.h
)

set(UIS
    gui/mainwindow.ui
)

set(PROJECT_SOURCES
        ${SOURCES}
        ${HEADERS}
        ${UIS}
)

qt_add_executable(keyhook_test
        MANUAL_FINALIZATION
        main.cpp
        ${PROJECT_SOURCES}
    )

target_link_libraries(keyhook_test PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(keyhook_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/gui ${CMAKE_CURRENT_BINARY_DIR})

target_compile_options(keyhook_test PRIVATE /permissive- /utf-8 /MP $<$<CONFIG:Debug>:/Zf /fsanitize=address>)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(keyhook_test)
endif()
