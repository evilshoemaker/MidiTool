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
		startStopAction_->setText(tr("Stop"));
    }
    else {
        setIcon(QIcon(":/icons/main_d.png"));
		startStopAction_->setText(tr("Start"));
    }
}

QMenu *TrayIcon::createMenu()
{
    QMenu *menu = new QMenu();

	showMainWindowAction_ = new QAction(tr("Settings"), this);
	connect(showMainWindowAction_, &QAction::triggered, this, &TrayIcon::showMainWindow);
	menu->addAction(showMainWindowAction_);

	menu->addSeparator();

	startStopAction_ = new QAction(tr("Start"), this);
	connect(startStopAction_, &QAction::triggered, this, &TrayIcon::startStop);
	menu->addAction(startStopAction_);

	quitAction_ = new QAction(tr("Exit"), this);
	connect(quitAction_, &QAction::triggered, this, &TrayIcon::quit);
	menu->addAction(quitAction_);

    return menu;
}
