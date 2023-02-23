/*
 * Copyright (C) 2021 CuteOS Team.
 *
 * Author:     rekols <revenmartin@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QTranslator>
#include <QLocale>
#include <QDBusConnection>
#include "systemtray/systemtraymodel.h"
#include "applicationmodel.h"
#include "notifications.h"
#include "mainwindow.h"
#include "brightness.h"
#include "battery.h"
#include "poweractions.h"
#include "controlcenterdialog.h"
#include "appearance.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
    QApplication app(argc, argv);

    if (!QDBusConnection::sessionBus().registerService("com.cute.Dock")) {
        return -1;
    }

    const char *uri = "Cute.Dock";
    qmlRegisterType<DockSettings>(uri, 1, 0, "DockSettings");
    qmlRegisterType<SystemTrayModel>(uri, 1, 0, "SystemTrayModel");
    qmlRegisterType<ControlCenterDialog>(uri, 1, 0, "ControlCenterDialog");
    qmlRegisterType<Appearance>(uri, 1, 0, "Appearance");
    qmlRegisterType<Notifications>(uri, 1, 0, "Notifications");
    qmlRegisterType<Brightness>(uri, 1, 0, "Brightness");
    qmlRegisterType<Battery>(uri, 1, 0, "Battery");
    qmlRegisterType<PowerActions>(uri, 1, 0, "PowerActions");
    QString qmFilePath = QString("%1/%2.qm").arg("/usr/share/cute-dock/translations/").arg(QLocale::system().name());
    if (QFile::exists(qmFilePath)) {
        QTranslator *translator = new QTranslator(QApplication::instance());
        if (translator->load(qmFilePath)) {
            QGuiApplication::installTranslator(translator);
        } else {
            translator->deleteLater();
        }
    }

    MainWindow w;

    if (!QDBusConnection::sessionBus().registerObject("/Dock", &w)) {
        return -1;
    }

    return app.exec();
}
