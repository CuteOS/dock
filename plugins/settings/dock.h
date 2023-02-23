#ifndef DOCK_H
#define DOCK_H

#include <QObject>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDBusServiceWatcher>
#include <QDBusPendingCall>

#include <QStandardPaths>
#include <QString>
#include <QSettings>
class Dock : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int dockIconSize READ dockIconSize WRITE setDockIconSize NOTIFY dockIconSizeChanged)
    Q_PROPERTY(int dockDirection READ dockDirection WRITE setDockDirection NOTIFY dockDirectionChanged)
    Q_PROPERTY(int dockVisibility READ dockVisibility WRITE setDockVisibility NOTIFY dockVisibilityChanged)
    Q_PROPERTY(int dockStyle READ dockStyle WRITE setDockStyle NOTIFY dockStyleChanged)
    Q_PROPERTY(bool dockRoundedWindow READ dockRoundedWindow WRITE setDockRoundedWindow NOTIFY dockRoundedWindowChanged)

public:
    explicit Dock(QObject *parent = nullptr);
    int dockIconSize() const;
    Q_INVOKABLE void setDockIconSize(int dockIconSize);

    int dockDirection() const;
    Q_INVOKABLE void setDockDirection(int dockDirection);

    int dockVisibility() const;
    Q_INVOKABLE void setDockVisibility(int visibility);

    int dockRoundedWindow() const;
    Q_INVOKABLE void setDockRoundedWindow(bool enable);

    int dockStyle() const;
    Q_INVOKABLE void setDockStyle(int style);
signals:
    void dockIconSizeChanged();
    void dockDirectionChanged();
    void dockVisibilityChanged();
    void dockStyleChanged();
    void dockRoundedWindowChanged();
private:
    QSettings *m_dockSettings;
    bool m_dockRoundedWindow;

    int m_dockIconSize;
    int m_dockDirection;
    int m_dockVisibility;
    int m_dockStyle;
};

#endif // DOCK_H
