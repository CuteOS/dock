cmake_minimum_required(VERSION 3.14)

set(PLUGIN_NAME "DockSettingsPlugin")
project(${PLUGIN_NAME} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Gui Quick DBus REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui REQUIRED)
#载入设置开发库
#find_package(YoyoSettings REQUIRED)

set(SRCS
    ${CuteSettings_SRCS}
    dockplugin.qrc
    dockplugin.json
    dockplugin.cpp
    dockplugin.h
    dock.h
    dock.cpp
)

# 设置动态库的名称、类型,shared是动态库。
#add_library(${PLUGIN_NAME} SHARED ${SRCS})
# 设置项目需要的访问的头文件，这里是设置的插件头文件
#target_include_directories(${PLUGIN_NAME} PUBLIC ${CuteSettings_INCLUDE_DIR}/cute-settings)
#target_link_libraries(${PLUGIN_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::DBus)

#target_compile_definitions(${PLUGIN_NAME} PRIVATE ${PLUGIN_NAME}_LIBRARY)

#install(TARGETS ${PLUGIN_NAME} DESTINATION lib/cuteos/setting/plugins/)
