#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "systemaudio/QSystemAudioWatcher.h"

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

	void on_pushButton_clicked();

private:
	Ui::MainWindow *ui;

	QSystemAudioWatcher *audioWatcher_;

	void fillDeviceList();
};

#endif // MAINWINDOW_H
