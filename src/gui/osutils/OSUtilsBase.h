#ifndef KEEPASSXC_OSUTILSBASE_H
#define KEEPASSXC_OSUTILSBASE_H

#include <QObject>

class OSUtilsBase : public QObject
{
    Q_OBJECT

public:

    virtual bool isLaunchAtStartupEnabled() const = 0;
    virtual void setLaunchAtStartup(bool enable) = 0;

    virtual void registerNativeEventFilter() = 0;

    virtual bool registerGlobalShortcut(const QString& name,
                                        Qt::Key key,
                                        Qt::KeyboardModifiers modifiers,
                                        QString* error = nullptr) = 0;
    virtual bool unregisterGlobalShortcut(const QString& name) = 0;

    virtual bool setLowLevelKeyboardHook() = 0;
    virtual void unsetLowLevelKeyboardHook() = 0;

signals:
    void globalShortcutTriggered(const QString& name, const QString& search = {});

protected:
    explicit OSUtilsBase(QObject* parent = nullptr);
    ~OSUtilsBase() override;
};

#endif // KEEPASSXC_OSUTILSBASE_H
