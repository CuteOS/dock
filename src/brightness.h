#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

#include <QObject>
#include <QDBusInterface>

class Brightness : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int value READ value NOTIFY valueChanged)
    Q_PROPERTY(bool enabled READ enabled CONSTANT)

public:
    explicit Brightness(QObject *parent = nullptr);

    Q_INVOKABLE void setValue(int value);

    int value() const;
    bool enabled() const;

signals:
    void valueChanged();

private:
    QDBusConnection m_dbusConnection;
    QDBusInterface m_iface;
    int m_value;
    bool m_enabled;
};

#endif // BRIGHTNESS_H
