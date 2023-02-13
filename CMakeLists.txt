cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(STRINGS "VERSION" version)
project(gpagent LANGUAGES CXX)

# Set the CMAKE_INSTALL_PREFIX to /usr if not specified
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "/usr" CACHE PATH "The default install prefix" FORCE)
endif()

message(STATUS "CMAKE_INSTALL_PREFIX was set to: ${CMAKE_INSTALL_PREFIX}")

configure_file(version.h.in version.h)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Widgets
    Network
    WebSockets
    WebEngine
    WebEngineWidgets
)

find_package(Qt5Keychain REQUIRED)

add_subdirectory(ThirdParty/inih)
add_subdirectory(ThirdParty/plog)
add_subdirectory(ThirdParty/qt-unix-signals)
set(QAPPLICATION_CLASS QApplication)
add_subdirectory(ThirdParty/SingleApplication)

configure_file(src/com.yuezk.qt.gpclient.desktop.in com.yuezk.qt.gpclient.desktop)
configure_file(src/com.yuezk.qt.gpclient.metainfo.xml.in com.yuezk.qt.gpclient.metainfo.xml)

file(GLOB ${PROJECT_NAME}_SRCS "include/*.h" "src/*.cpp")
add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRCS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${QTKEYCHAIN_INCLUDE_DIRS}/qt5keychain)

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::Network
    Qt5::WebSockets
    Qt5::WebEngine
    Qt5::WebEngineWidgets
    QtSignals
    inih
    plog
    SingleApplication
    ${QTKEYCHAIN_LIBRARIES}
)

file(GLOB ${PROJECT_NAME}_gui_SRCS "include/gui/*.h" "src/gui/*.cpp" "src/gui/*.qrc")
add_executable(${PROJECT_NAME}_gui ${${PROJECT_NAME}_gui_SRCS})
target_compile_definitions(${PROJECT_NAME}_gui PRIVATE ENV_CDP_PORT="QTWEBENGINE_REMOTE_DEBUGGING")
target_include_directories(${PROJECT_NAME}_gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/gui)
target_include_directories(${PROJECT_NAME}_gui PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(${PROJECT_NAME}_gui ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}_gui DESTINATION bin)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/com.yuezk.qt.gpclient.metainfo.xml" DESTINATION share/metainfo)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/com.yuezk.qt.gpclient.desktop" DESTINATION share/applications)
install(FILES "com.yuezk.qt.gpclient.svg" DESTINATION share/icons/hicolor/scalable/apps)
install(FILES "gp.conf" DESTINATION /etc/gpservice)

