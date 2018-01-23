#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "systemaudio/QSystemAudioWatcher.h"
#include "qmidi/QMidiOut.h"

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

	void on_stratButton_clicked();

private:
	Ui::MainWindow *ui;

	QSystemAudioWatcher *audioWatcher_;

	QMidiOut midi_;

	void init();
	void fillDeviceList();
	void sendControlChange(int value);
	void setEnableGui(bool flag);
	bool running_ = false;
};

#endif // MAINWINDOW_H
