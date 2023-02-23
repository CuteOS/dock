#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <QObject>
#include <QDBusInterface>
#include <QDBusPendingCall>

class Notifications : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool doNotDisturb READ doNotDisturb WRITE setDoNotDisturb NOTIFY doNotDisturbChanged)

public:
    explicit Notifications(QObject *parent = nullptr);

    bool doNotDisturb() const;
    void setDoNotDisturb(bool enabled);

private slots:
    void onDBusDoNotDisturbChanged();

signals:
    void doNotDisturbChanged();

private:
    QDBusInterface m_iface;
    bool m_doNotDisturb;
};

#endif // NOTIFICATIONS_H
