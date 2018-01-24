#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

#include "systemaudio/QSystemAudioWatcher.h"
#include "qmidi/QMidiOut.h"

#include "TrayIcon.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void onVolumeLevelChanged(int value);
	void start();
	void stop();

	void trayIconActivated(QSystemTrayIcon::ActivationReason reason);

	void on_stratButton_clicked();
    void on_autorunCheckBox_toggled(bool checked);

private:
	void closeEvent(QCloseEvent *event);

private:
	Ui::MainWindow *ui;

    QSystemAudioWatcher *audioWatcher_ = nullptr;
    TrayIcon *trayIcon_ = nullptr;

	QMidiOut midi_;

	void init();
	void fillDeviceList();
	void sendControlChange(int value);
	void setEnableGui(bool flag);
	bool running_ = false;
};

#endif // MAINWINDOW_H
