#include "mainwindow.h"
#include "osutils/OSUtils.h"

#include <QApplication>
#include <QDebug>
#include <QAbstractNativeEventFilter>
#include <windows.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    osUtils->registerNativeEventFilter();
    osUtils->registerGlobalShortcut("space", Qt::Key_Space, Qt::ControlModifier);
    osUtils->setLowLevelKeyboardHook();

    QObject::connect(osUtils, &OSUtilsBase::globalShortcutTriggered, [](const QString& hotkey_name) {
        qDebug() << hotkey_name <<  " pressed!";
    });

    MainWindow w;
    w.setWindowFlags(w.windowFlags() | Qt::WindowStaysOnTopHint);
    w.show();
    return app.exec();
}
