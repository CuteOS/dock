#ifndef DOCKPLUGIN_H
#define DOCKPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include <interfaceplugin.h>
#include <dataObject.h>
#include <QFile>
#include <QGuiApplication>

class DockPlugin : public QObject, public InterfacePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID InterfacePlugin_iid FILE "dockplugin.json")
    Q_INTERFACES(InterfacePlugin)
public:
    explicit DockPlugin(QObject *parent = nullptr);
    virtual void recMsgfromManager(PluginMetaData) Q_DECL_OVERRIDE{};
    virtual void initialize() Q_DECL_OVERRIDE;
    virtual QList<QObject*> dataList() Q_DECL_OVERRIDE;
signals:
    void sendMsg2Manager(PluginMetaData) Q_DECL_OVERRIDE;

};

#endif // DOCKPLUGIN
