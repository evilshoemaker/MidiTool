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

signals:
	void showMainWindow();
	void quit();
	void startStop();

public slots:
    void setRunning(bool flag);

private:
    QMenu *createMenu();
	QAction *showMainWindowAction_ = nullptr;
	QAction *quitAction_ = nullptr;
	QAction *startStopAction_ = nullptr;
};

#endif // TRAYICON_H
