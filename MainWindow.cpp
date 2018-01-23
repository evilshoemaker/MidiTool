#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>

#include "systemaudio/QSystemAudio.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	audioWatcher_(new QSystemAudioWatcher(this))
{
	ui->setupUi(this);
	setFixedSize(this->geometry().width(), this->geometry().height());

	init();
	fillDeviceList();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::onVolumeLevelChanged(int value)
{
	ui->volumeLevelLabel->setText(QString::number(value));
	if (running_) {
		sendControlChange(value);
	}
}

void MainWindow::start()
{
	QString outDeviceId = ui->midiDevicesComboBox->currentData().toString();
	if (outDeviceId.isEmpty())
		return;

	midi_.connect(outDeviceId);
	ui->stratButton->setText("Stop");
	ui->statusLabel->setText("Running");
	running_ = true;
	setEnableGui(false);
}

void MainWindow::stop()
{
	midi_.disconnect();
	running_ = false;
	setEnableGui(true);
	ui->stratButton->setText("Start");
	ui->statusLabel->setText("Stopped");
}

void MainWindow::fillDeviceList()
{
	ui->midiDevicesComboBox->clear();

	QMap<QString, QString> vals = QMidiOut::devices();
	for (const QString &key : vals.keys()) {
		ui->midiDevicesComboBox->addItem(vals[key], key);
	}
}

void MainWindow::sendControlChange(int value)
{
	midi_.controlChange(ui->channelSpinBox->value(),
					   ui->controlNumberSpinBox->value(),
						value);
}

void MainWindow::setEnableGui(bool flag)
{
	ui->channelSpinBox->setEnabled(flag);
	ui->controlNumberSpinBox->setEnabled(flag);
	ui->midiDevicesComboBox->setEnabled(flag);
}

void MainWindow::on_stratButton_clicked()
{
	if (running_) {
		stop();
	}
	else {
		start();
	}
}

void MainWindow::init()
{
	connect(audioWatcher_, &QSystemAudioWatcher::volumeLevelChanged, this, &MainWindow::onVolumeLevelChanged);
	audioWatcher_->start();
}
