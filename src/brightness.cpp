#include "brightness.h"
#include <QDBusPendingCall>

Brightness::Brightness(QObject *parent)
    : QObject(parent)
    , m_dbusConnection(QDBusConnection::sessionBus())
    , m_iface("com.cute.Settings",
              "/Brightness",
              "com.cute.Brightness", m_dbusConnection)
    , m_value(0)
    , m_enabled(false)
{
    if (!m_iface.isValid())
        return;

    m_value = m_iface.property("brightness").toInt();
    m_enabled = m_iface.property("brightnessEnabled").toBool();
}

void Brightness::setValue(int value)
{
    m_iface.asyncCall("setValue", value);
}

int Brightness::value() const
{
    return m_value;
}

bool Brightness::enabled() const
{
    return m_enabled;
}
