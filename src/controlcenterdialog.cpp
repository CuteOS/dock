#include "controlcenterdialog.h"
#include <KWindowSystem>

ControlCenterDialog::ControlCenterDialog(QQuickWindow *parent)
    : QQuickWindow(parent)
{
    setFlags(Qt::Popup);
    setColor(Qt::transparent);
    installEventFilter(this);
}

void ControlCenterDialog::open()
{
    setVisible(true);
    setMouseGrabEnabled(true);
    setKeyboardGrabEnabled(true);
}

bool ControlCenterDialog::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        if (QWindow *w = qobject_cast<QWindow*>(object)) {
            if (!w->geometry().contains(static_cast<QMouseEvent*>(event)->globalPos())) {
                ControlCenterDialog::setVisible(false);
            }
        }
    } else if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Escape) {
            ControlCenterDialog::setVisible(false);
        }
    } else if (event->type() == QEvent::Show) {
        KWindowSystem::setState(winId(), NET::SkipTaskbar | NET::SkipPager | NET::SkipSwitcher);
    } else if (event->type() == QEvent::Hide) {
        setMouseGrabEnabled(false);
        setKeyboardGrabEnabled(false);
    }

    return QObject::eventFilter(object, event);
}
