#include "mainwindow.h"
#include "osutils/OSUtils.h"

#include <QApplication>
#include <QDebug>
#include <QAbstractNativeEventFilter>
#include <windows.h>

#include <QScreen>
#include <QRect>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    osUtils->registerNativeEventFilter();
    osUtils->registerGlobalShortcut("space", Qt::Key_Space, Qt::ControlModifier);
    osUtils->setLowLevelKeyboardHook();

    MainWindow mainWindow;

    QObject::connect(osUtils, &OSUtilsBase::globalShortcutTriggered, [&mainWindow](const QString& hotkey_name) {
        qDebug() << hotkey_name <<  " pressed!";
        qDebug() << "Width:" << mainWindow.geometry().width();
        qDebug() << "Height:" << mainWindow.geometry().height();
    });


    mainWindow.show();
    mainWindow.moveToDefaultPos();

    return app.exec();
}
