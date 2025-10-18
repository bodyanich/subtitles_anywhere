#ifndef WINUTILS_H
#define WINUTILS_H

#include <QAbstractNativeEventFilter>
#include <QPointer>
#include <QSharedPointer>
#include <QHash>

#include <windows.h>

#include "osutils/OSUtilsBase.h"

class WinUtils : public OSUtilsBase, QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    static WinUtils* instance();

    bool isLaunchAtStartupEnabled() const override;
    void setLaunchAtStartup(bool enable) override;

    void registerNativeEventFilter() override;

    bool registerGlobalShortcut(const QString& name,
                                Qt::Key key,
                                Qt::KeyboardModifiers modifiers,
                                QString* error = nullptr) override;
    bool unregisterGlobalShortcut(const QString& name) override;

    bool setLowLevelKeyboardHook() override;
    void unsetLowLevelKeyboardHook() override;
    static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

    WORD qtToNativeKeyCode(Qt::Key key);
    DWORD qtToNativeModifiers(Qt::KeyboardModifiers modifiers);

protected:
    explicit WinUtils(QObject* parent = nullptr);
    ~WinUtils() override = default;

    bool nativeEventFilter(const QByteArray& eventType, void* message, qintptr *) override;
    void triggerGlobalShortcut(int id);

private:
    static QPointer<WinUtils> m_instance;

    struct globalShortcut
    {
        int id;
        DWORD nativeKeyCode;
        DWORD nativeModifiers;
    };

    int m_nextShortcutId;
    QHash<QString, QSharedPointer<globalShortcut>> m_globalShortcuts;
    HHOOK m_hHook;

    Q_DISABLE_COPY(WinUtils)
};

inline WinUtils* winUtils()
{
    return WinUtils::instance();
}

#endif // WINUTILS_H
