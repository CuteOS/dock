#include "dock.h"

Dock::Dock(QObject *parent)
    : QObject{parent}
    , m_dockSettings(new QSettings(QSettings::UserScope, "cuteos", "dock"))
    , m_dockIconSize(0)
    , m_dockDirection(0)
    , m_dockVisibility(0)
{
    m_dockIconSize = m_dockSettings->value("IconSize").toInt();
    m_dockDirection = m_dockSettings->value("Direction").toInt();
    m_dockVisibility = m_dockSettings->value("Visibility").toInt();
    m_dockRoundedWindow = m_dockSettings->value("RoundedWindow").toBool();
    m_dockStyle = m_dockSettings->value("Style").toInt();
}

int Dock::dockIconSize() const
{
    return m_dockIconSize;
}

void Dock::setDockIconSize(int dockIconSize)
{
    if (m_dockIconSize != dockIconSize) {
        QDBusInterface iface("com.cute.Dock",
                             "/Dock",
                             "com.cute.Dock",
                             QDBusConnection::sessionBus());
        if (iface.isValid()) {
            iface.call("setIconSize", dockIconSize);
        }

        m_dockIconSize = dockIconSize;
        emit dockIconSizeChanged();
    }
}

int Dock::dockDirection() const
{
    return m_dockDirection;
}

void Dock::setDockDirection(int dockDirection)
{
    if (m_dockDirection != dockDirection) {
        QDBusInterface iface("com.cute.Dock",
                             "/Dock",
                             "com.cute.Dock",
                             QDBusConnection::sessionBus());
        if (iface.isValid()) {
            iface.call("setDirection", dockDirection);
        }

        m_dockDirection = dockDirection;
        emit dockDirectionChanged();
    }
}

int Dock::dockVisibility() const
{
    return m_dockVisibility;
}

void Dock::setDockVisibility(int visibility)
{
    if (m_dockVisibility != visibility) {
        m_dockVisibility = visibility;

        QDBusInterface iface("com.cute.Dock",
                             "/Dock",
                             "com.cute.Dock",
                             QDBusConnection::sessionBus());
        if (iface.isValid()) {
            iface.call("setVisibility", visibility);
        }

        emit dockVisibilityChanged();
    }
}

int Dock::dockRoundedWindow() const
{
    return m_dockRoundedWindow;
}

void Dock::setDockRoundedWindow(bool enable)
{
    if (m_dockRoundedWindow == enable)
        return;

    m_dockRoundedWindow = enable;
    m_dockSettings->setValue("RoundedWindow", m_dockRoundedWindow);
}

int Dock::dockStyle() const
{
    return m_dockStyle;
}

void Dock::setDockStyle(int style)
{
    if (m_dockStyle != style) {
        m_dockStyle = style;

        QDBusInterface iface("com.cute.Dock",
                             "/Dock",
                             "com.cute.Dock",
                             QDBusConnection::sessionBus());
        if (iface.isValid()) {
            iface.call("setStyle", style);
        }

        emit dockStyleChanged();
    }
}
