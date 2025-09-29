#include "mainwindow.h"

#include <QApplication>

#include <QDebug>
#include <QAbstractNativeEventFilter>
#include <windows.h>

HHOOK g_hHook = nullptr;   // global hook handle

// Low-level keyboard callback
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT *kb = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);

        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            switch (kb->vkCode) {
            case VK_SPACE:
                qDebug() << "Space pressed!";
                break;
            case VK_LEFT:
                qDebug() << "Left Arrow pressed!";
                break;
            case VK_RIGHT:
                qDebug() << "Right Arrow pressed!";
                break;
            case VK_UP:
                qDebug() << "Up Arrow pressed!";
                break;
            case VK_DOWN:
                qDebug() << "Down Arrow pressed!";
                break;
            }
        }
    }
    // Pass to next hook in chain
    return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

// Helper class to keep hook alive in Qt
class KeyboardHook : public QAbstractNativeEventFilter {
public:
    KeyboardHook() {
        g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(nullptr), 0);
        if (!g_hHook) {
            qWarning() << "Failed to install hook!";
        }
    }
    ~KeyboardHook() {
        if (g_hHook) {
            UnhookWindowsHookEx(g_hHook);
            g_hHook = nullptr;
        }
    }

    bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result) override {
        // We don’t need to handle messages here, hook works via callback.
        return false;
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    KeyboardHook hook; // installs hook
    qDebug() << "App running, press Space or Arrow keys (even if app is not focused).";

    MainWindow w;
    w.setWindowFlags(w.windowFlags() | Qt::WindowStaysOnTopHint);
    w.show();
    return a.exec();
}
