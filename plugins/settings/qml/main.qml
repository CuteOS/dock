import QtQuick 2.4
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import Cute.Settings 1.0
import CuteUI 1.0 as CuteUI
import "../../"

ItemPage {
    headerTitle: qsTr("Dock")

    Dock {
        id: dock
    }

    Scrollable {
        anchors.fill: parent
        contentHeight: layout.implicitHeight

        ColumnLayout {
            id: layout
            anchors.fill: parent
            spacing: CuteUI.Units.largeSpacing * 2

            RoundedItem {
                Label {
                    text: qsTr("Style")
                    color: CuteUI.Theme.disabledTextColor
                }

                RowLayout {
                    spacing: CuteUI.Units.largeSpacing * 2

                    IconCheckBox {
                        source: CuteUI.Theme.darkMode? "qrc:/dock/images/darkdock.png" : "qrc:/dock/images/lightdock.png"
                        text: qsTr("Center")
                        iconSize: 140
                        checked: dock.dockStyle === 0
                        onClicked: dock.setDockStyle(0)
                    }

                    IconCheckBox {
                        source: CuteUI.Theme.darkMode? "qrc:/dock/images/darkfill.png" : "qrc:/dock/images/lightfill.png"
                        text: qsTr("Full")
                        iconSize: 140
                        checked: dock.dockStyle === 1
                        onClicked: dock.setDockStyle(1)
                    }
                }
            }

//            // position
//            RoundedItem {
//                Label {
//                    text: qsTr("Position on screen")
//                    color: CuteUI.Theme.disabledTextColor
//                }

//                RowLayout {
//                    spacing: CuteUI.Units.largeSpacing * 2

//                    IconCheckBox {
//                        source: "qrc:/images/dock_left.svg"
//                        text: qsTr("Left")
//                        checked: dock.dockDirection === 0
//                        onClicked: dock.setDockDirection(0)
//                    }

//                    IconCheckBox {
//                        source: "qrc:/images/dock_bottom.svg"
//                        text: qsTr("Bottom")
//                        checked: dock.dockDirection === 1
//                        onClicked: dock.setDockDirection(1)
//                    }

//                    IconCheckBox {
//                        source: "qrc:/images/dock_right.svg"
//                        text: qsTr("Right")
//                        checked: dock.dockDirection === 2
//                        onClicked: dock.setDockDirection(2)
//                    }
//                }
//            }

            // Dock Size
            RoundedItem {
                Label {
                    text: qsTr("Size")
                    color: CuteUI.Theme.disabledTextColor
                }

                TabBar {
                    id: dockSizeTabbar
                    Layout.fillWidth: true
                    bottomPadding: CuteUI.Units.smallSpacing

                    TabButton {
                        text: qsTr("Small")
                    }

                    TabButton {
                        text: qsTr("Medium")
                    }

                    TabButton {
                        text: qsTr("Large")
                    }

                    TabButton {
                        text: qsTr("Huge")
                    }

                    currentIndex: {
                        var index = 0

                        if (dock.dockIconSize <= 45)
                            index = 0
                        else if (dock.dockIconSize <= 53)
                            index = 1
                        else if (dock.dockIconSize <= 63)
                            index = 2
                        else if (dock.dockIconSize <= 72)
                            index = 3

                        return index
                    }

                    onCurrentIndexChanged: {
                        var iconSize = 0

                        switch (currentIndex) {
                        case 0:
                            iconSize = 45
                            break;
                        case 1:
                            iconSize = 53
                            break;
                        case 2:
                            iconSize = 63
                            break;
                        case 3:
                            iconSize = 72
                            break;
                        }

                        dock.setDockIconSize(iconSize)
                    }
                }
            }

            // Visibility
            RoundedItem {
                Label {
                    text: qsTr("Display mode")
                    color: CuteUI.Theme.disabledTextColor
                }

                TabBar {
                    Layout.fillWidth: true
                    currentIndex: dock.dockVisibility
                    onCurrentIndexChanged: dock.setDockVisibility(currentIndex)

                    TabButton {
                        text: qsTr("Always show")
                    }

                    TabButton {
                        text: qsTr("Always hide")
                    }

                    TabButton {
                        text: qsTr("Smart hide")
                    }
                }
            }

            Item {
                Layout.fillHeight: true
            }
        }
    }
}
