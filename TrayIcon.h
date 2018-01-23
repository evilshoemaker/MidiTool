#ifndef TRAYICON_H
#define TRAYICON_H

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit TrayIcon(QObject *parent = nullptr);

public slots:
    void setRunning(bool flag);

private:
    QMenu *createMenu();
};

#endif // TRAYICON_H
