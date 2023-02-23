cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME cute-dock)
project(${PROJECT_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 CONFIG REQUIRED Widgets DBus X11Extras Concurrent LinguistTools QuickControls2)
find_package(KF5WindowSystem REQUIRED)
find_package(PkgConfig REQUIRED)

file(GLOB TS_FILES translations/*.ts)
# 更新 .ts 翻译文件
execute_process(COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/translations/translate_update.sh WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/translations)

pkg_check_modules(XCB_LIBS REQUIRED xcb)

set(SRCS
    src/applicationitem.h
    src/applicationmodel.cpp
    src/docksettings.cpp
    src/iconthemeimageprovider.cpp
    src/main.cpp
    src/mainwindow.cpp
    src/systemappmonitor.cpp
    src/systemappitem.cpp
    src/processprovider.cpp
    src/trashmanager.cpp
    src/utils.cpp
    src/xwindowinterface.cpp
    src/activity.cpp
    src/notifications.cpp
    src/fakewindow.cpp
    src/battery.cpp
    src/brightness.cpp
    src/poweractions.cpp
    src/controlcenterdialog.cpp
    src/volume.cpp
    src/appearance.cpp

    src/systemtray/statusnotifieritemsource.cpp
    src/systemtray/systemtraytypes.cpp
    src/systemtray/systemtraytypedefs.h
    src/systemtray/systemtraymodel.cpp
    src/systemtray/statusnotifierwatcher.cpp
    src/systemtray/statusnotifieritemhost.cpp

    src/libdbusmenuqt/dbusmenuimporter.cpp
    src/libdbusmenuqt/dbusmenushortcut_p.cpp
    src/libdbusmenuqt/dbusmenutypes_p.cpp
    src/libdbusmenuqt/utils.cpp

    src/appmenu/kdbusimporter.h
    src/appmenu/appmenu.h
    src/appmenu/appmenu.cpp
    src/appmenu/appmenudbus.h
    src/appmenu/appmenudbus.cpp
    src/appmenu/verticalmenu.h
    src/appmenu/verticalmenu.cpp
    src/appmenu/menuimporter.h
    src/appmenu/menuimporter.cpp
    src/appmenu/appmenumodel.h
    src/appmenu/appmenumodel.cpp
    src/appmenu/appmenuapplet.h
    src/appmenu/appmenuapplet.cpp
    src/appmenu/dbusmenu_interface.cpp
    src/appmenu/dbusmenu_interface.h

    resources.qrc
)

set(statusnotifierwatcher_xml src/systemtray/org.kde.StatusNotifierWatcher.xml)
qt5_add_dbus_interface(SRCS ${statusnotifierwatcher_xml} statusnotifierwatcher_interface)
qt5_add_dbus_interface(SRCS src/systemtray/org.freedesktop.DBus.Properties.xml dbusproperties)

set(statusnotifieritem_xml src/systemtray/org.kde.StatusNotifierItem.xml)
set_source_files_properties(${statusnotifieritem_xml} PROPERTIES
   NO_NAMESPACE false
   INCLUDE "src/systemtray/systemtraytypes.h"
   CLASSNAME OrgKdeStatusNotifierItem
)
qt5_add_dbus_interface(SRCS ${statusnotifieritem_xml} statusnotifieritem_interface)

qt5_add_dbus_adaptor(SRCS src/systemtray/org.kde.StatusNotifierWatcher.xml
                     src/systemtray/statusnotifierwatcher.h StatusNotifierWatcher)

# libdbusmenuqt
set_source_files_properties(src/libdbusmenuqt/com.canonical.dbusmenu.xml PROPERTIES
   NO_NAMESPACE true
   INCLUDE "src/libdbusmenuqt/dbusmenutypes_p.h"
   CLASSNAME DBusMenuInterface
)

# The interface was added on Qt5.15
# qt_add_dbus_interface(libdbusmenu_SRCS src/libdbusmenuqt/com.canonical.dbusmenu.xml dbusmenu_interface)

## appmenu
qt5_add_dbus_adaptor(appmenu_SRCS src/appmenu/com.canonical.AppMenu.Registrar.xml
    src/appmenu/menuimporter.h MenuImporter menuimporteradaptor MenuImporterAdaptor)
qt5_add_dbus_adaptor(appmenu_SRCS src/appmenu/com.cute.cappmenu.xml
    src/appmenu/appmenudbus.h AppmenuDBus appmenuadaptor AppmenuAdaptor)


qt5_add_dbus_adaptor(DBUS_SOURCES
                     src/com.cute.Dock.xml
                     src/mainwindow.h MainWindow)

add_subdirectory(plugins/settings)
set_source_files_properties(${DBUS_SOURCES} PROPERTIES SKIP_AUTOGEN ON)
add_executable(${PROJECT_NAME} ${SRCS} ${appmenu_SRCS} ${DBUS_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${XCB_LIBS_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt5::Core
        Qt5::Widgets
        Qt5::Quick
        Qt5::QuickControls2
        Qt5::X11Extras
        Qt5::Concurrent
        Qt5::DBus
        KF5::WindowSystem
        ${XCB_LIBS_LIBRARIES}
)

qt5_create_translation(QM_FILES ${TS_FILES})
add_custom_target(translations DEPENDS ${QM_FILES} SOURCES ${TS_FILES})
add_dependencies(${PROJECT_NAME} translations)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${QM_FILES} DESTINATION /usr/share/${PROJECT_NAME}/translations)
install(FILES cute-dock-list.conf DESTINATION /etc)
