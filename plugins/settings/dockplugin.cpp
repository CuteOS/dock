#include "dockplugin.h"
#include "dock.h"
DockPlugin::DockPlugin(QObject *parent)
    : QObject{parent}
{

}

QList<QObject*> DockPlugin::dataList()
{
    QList<QObject*> dataList;
    DataObject *data1 = new DataObject(this);
    data1->setName("dock");
    data1->setTitle(tr("Dock"));
    data1->setIconId("\uf4c4");
    data1->setPage("qrc:/dock/qml/main.qml");
    data1->setCategory(DISPLAYANDAPPEARANCE);
    dataList.append(data1);
    return dataList;
}

void DockPlugin::initialize()
{
    QString qmFilePath = QString("%1/%2.qm").arg("/usr/share/cute-dock/translations/").arg(QLocale::system().name());
    if (QFile::exists(qmFilePath)) {
        QTranslator *translator = new QTranslator(this);
        if (translator->load(qmFilePath)) {
            QGuiApplication::installTranslator(translator);
        } else {
            translator->deleteLater();
        }
    }
    // QML
    const char *uri = "Cute.Settings";
    qmlRegisterType<Dock>(uri, 1, 0, "Dock");
}
