#ifndef CONTROLCENTERDIALOG_H
#define CONTROLCENTERDIALOG_H

#include <QQuickWindow>
#include <QTimer>

class ControlCenterDialog : public QQuickWindow
{
    Q_OBJECT

public:
    ControlCenterDialog(QQuickWindow *view = nullptr);

    Q_INVOKABLE void open();

protected:
    bool eventFilter(QObject *object, QEvent *event);
};

#endif // CONTROLCENTERDIALOG_H
