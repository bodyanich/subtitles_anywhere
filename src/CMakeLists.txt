cmake_minimum_required(VERSION 3.5)

set(SOURCES
    gui/mainwindow.cpp
    gui/osutils/OSUtilsBase.cpp
    gui/osutils/winutils/WinUtils.cpp
)

set(HEADERS
    gui/mainwindow.h
    gui/osutils/OSUtilsBase.h
    gui/osutils/winutils/WinUtils.h
    gui/osutils/OSUtils.h
)

set(UIS
    gui/mainwindow.ui
)

set(PROJECT_SOURCES
        ${SOURCES}
        ${HEADERS}
        ${UIS}
)

qt_add_executable(SubtitlesAnywhere
        MANUAL_FINALIZATION
        main.cpp
        ${PROJECT_SOURCES}
    )

target_link_libraries(SubtitlesAnywhere PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(SubtitlesAnywhere PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/gui)

target_compile_options(SubtitlesAnywhere PRIVATE /permissive- /utf-8 /MP $<$<CONFIG:Debug>:/Zf /fsanitize=address>)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SubtitlesAnywhere)
endif()
