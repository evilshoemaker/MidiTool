#include "TrayIcon.h"

TrayIcon::TrayIcon(QObject *parent)
    : QSystemTrayIcon(parent)
{
    setIcon(QIcon(":/icons/main_d.png"));
    setContextMenu(createMenu());
}

void TrayIcon::setRunning(bool flag)
{
    if (flag) {
        setIcon(QIcon(":/icons/main.png"));
    }
    else {
        setIcon(QIcon(":/icons/main_d.png"));
    }
}

QMenu *TrayIcon::createMenu()
{
    QMenu *menu = new QMenu();
    //menu->addAction(createQuitAction());
    return menu;
}
