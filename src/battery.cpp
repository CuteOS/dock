#include "battery.h"
#include <QSettings>
#include <QDBusPendingCall>

static const QString s_sServer = "com.cute.Settings";
static const QString s_sPath = "/PrimaryBattery";
static const QString s_sInterface = "com.cute.PrimaryBattery";

static Battery *SELF = nullptr;

Battery *Battery::self()
{
    if (!SELF)
        SELF = new Battery;

    return SELF;
}

Battery::Battery(QObject *parent)
    : QObject(parent)
    , m_upowerInterface("org.freedesktop.UPower",
                        "/org/freedesktop/UPower",
                        "org.freedesktop.UPower",
                        QDBusConnection::systemBus())
    , m_interface("com.cute.Settings",
                  "/PrimaryBattery",
                  "com.cute.PrimaryBattery",
                  QDBusConnection::sessionBus())
    , m_available(false)
    , m_onBattery(false)
    , m_showPercentage(false)
{
    m_available = m_interface.isValid() && !m_interface.lastError().isValid();

    if (m_available) {
        QSettings settings("cuteos", "statusbar");
        settings.setDefaultFormat(QSettings::IniFormat);
        m_showPercentage = settings.value("BatteryPercentage", false).toBool();

        QDBusConnection::sessionBus().connect(s_sServer, s_sPath, s_sInterface, "chargeStateChanged", this, SLOT(chargeStateChanged(int)));
        QDBusConnection::sessionBus().connect(s_sServer, s_sPath, s_sInterface, "chargePercentChanged", this, SLOT(chargePercentChanged(int)));
        QDBusConnection::sessionBus().connect(s_sServer, s_sPath, s_sInterface, "lastChargedPercentChanged", this, SLOT(lastChargedPercentChanged()));
        QDBusConnection::sessionBus().connect(s_sServer, s_sPath, s_sInterface, "capacityChanged", this, SLOT(capacityChanged(int)));
        QDBusConnection::sessionBus().connect(s_sServer, s_sPath, s_sInterface, "remainingTimeChanged", this, SLOT(remainingTimeChanged(qlonglong)));

        // Update Icon
        QDBusConnection::sessionBus().connect(s_sServer, s_sPath, s_sInterface, "chargePercentChanged", this, SLOT(iconSourceChanged()));

        QDBusInterface interface("org.freedesktop.UPower", "/org/freedesktop/UPower",
                                 "org.freedesktop.UPower", QDBusConnection::systemBus());

        QDBusConnection::systemBus().connect("org.freedesktop.UPower", "/org/freedesktop/UPower",
                                             "org.freedesktop.DBus.Properties",
                                             "PropertiesChanged", this,
                                             SLOT(onPropertiesChanged(QString, QVariantMap, QStringList)));

        if (interface.isValid()) {
            m_onBattery = interface.property("OnBattery").toBool();
        }

        emit validChanged();
    }
}

bool Battery::available() const
{
    return m_available;
}

bool Battery::onBattery() const
{
    return m_onBattery;
}

bool Battery::showPercentage() const
{
    return m_showPercentage;
}

void Battery::setShowPercentage(bool enabled)
{
    if (enabled == m_showPercentage)
        return;

    m_showPercentage = enabled;

    QSettings settings("cuteos", "statusbar");
    settings.setDefaultFormat(QSettings::IniFormat);
    settings.setValue("BatteryPercentage", m_showPercentage);

    emit showPercentageChanged();
}

int Battery::chargeState() const
{
    return m_interface.property("chargeState").toInt();
}

int Battery::chargePercent() const
{
    return m_interface.property("chargePercent").toInt();
}

int Battery::lastChargedPercent() const
{
    return m_interface.property("lastChargedPercent").toInt();
}

int Battery::capacity() const
{
    return m_interface.property("capacity").toInt();
}

QString Battery::statusString() const
{
    return m_interface.property("statusString").toString();
}

QString Battery::iconSource() const
{
    int percent = this->chargePercent();
    QString range;

    if (percent >= 95)
        range = "\ue144";
    else if (percent >= 85)
        range = "\uf1ce";
    else if (percent>= 75)
        range = "\uf1cc";
    else if (percent >= 65)
        range = "\uf1ca";
    else if (percent >= 55)
        range = "\uf1c8";
    else if (percent >= 45)
        range = "\uf1c6";
    else if (percent >= 35)
        range = "\uf1c4";
    else if (percent >= 25)
        range = "\uf1c2";
    else if (percent >= 15)
        range = "\uf1c0";
    else if (percent >= 5)
        range = "\uf1be";
    else
        range = "\uf1bc";

    if (m_onBattery)
        return range;

    return "\uf1d0";
}

void Battery::onPropertiesChanged(const QString &ifaceName, const QVariantMap &changedProps, const QStringList &invalidatedProps)
{
    Q_UNUSED(ifaceName);
    Q_UNUSED(changedProps);
    Q_UNUSED(invalidatedProps);

    bool onBattery = m_upowerInterface.property("OnBattery").toBool();
    if (onBattery != m_onBattery) {
        m_onBattery = onBattery;
        m_interface.call("refresh");
        emit onBatteryChanged();
        emit iconSourceChanged();
    }
}
