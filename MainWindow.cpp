#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QCoreApplication>

#include "systemaudio/QSystemAudio.h"

#include "Util.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	audioWatcher_(new QSystemAudioWatcher(this)),
	trayIcon_(new TrayIcon(this)),
	settings_(new QSettings(configFilePath(), QSettings::IniFormat, this))
{
	ui->setupUi(this);
	setFixedSize(this->geometry().width(), this->geometry().height());

	init();
	fillDeviceList();
	loadSettings();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::onVolumeLevelChanged(int value)
{
	ui->volumeLevelLabel->setText(QString::number(value));

	if (running_) {
		if (value < 0)
			return;

		int v = (value * 127) / 100;
		sendControlChange(v);
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
	trayIcon_->setRunning(running_);
}

void MainWindow::stop()
{
	midi_.disconnect();
	running_ = false;
	setEnableGui(true);
	ui->stratButton->setText("Start");
	ui->statusLabel->setText("Stopped");
	trayIcon_->setRunning(running_);
}

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
	if (reason == QSystemTrayIcon::Trigger)
	{
		if (!this->isVisible()) {
			this->show();
			this->activateWindow();
		} else {
			this->showNormal();
			this->activateWindow();
		}
	}
}

void MainWindow::fillDeviceList()
{
	ui->midiDevicesComboBox->clear();

	QMap<QString, QString> vals = QMidiOut::devices();
	for (const QString &key : vals.keys()) {
		ui->midiDevicesComboBox->addItem(vals[key], key);
	}

	ui->audioDevicesComboBox->clear();

	QMap<QString, QString> audioDevList = QSystemAudio::devices();
	for (const QString &key : audioDevList.keys()) {
		ui->audioDevicesComboBox->addItem(audioDevList[key], key);
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
	ui->autorunCheckBox->setEnabled(flag);
	ui->audioDevicesComboBox->setEnabled(flag);
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
	ui->autorunCheckBox->setChecked(Util::isAutorun());

	connect(audioWatcher_, &QSystemAudioWatcher::volumeLevelChanged, this, &MainWindow::onVolumeLevelChanged);
	audioWatcher_->start();

	connect(trayIcon_, &TrayIcon::activated, this, &MainWindow::trayIconActivated);
	connect(trayIcon_, &TrayIcon::showMainWindow, this, [=]() {
		trayIconActivated(QSystemTrayIcon::Trigger);
	});
	connect(trayIcon_, &TrayIcon::quit, [=]() {
		stop();
		saveSettings();
		trayIcon_->hide();
		qApp->quit();
	});
	connect(trayIcon_, &TrayIcon::startStop, [=]() {
		on_stratButton_clicked();
	});

	trayIcon_->show();
}

void MainWindow::loadSettings()
{
	ui->channelSpinBox->setValue(settings_->value("midi/channel", 0).toInt());
	ui->controlNumberSpinBox->setValue(settings_->value("midi/controlNumber", 0).toInt());

	QString deviceId = settings_->value("midi/deviceId", "").toString();
	int index = ui->midiDevicesComboBox->findData(deviceId);
	if (index != -1) {
		ui->midiDevicesComboBox->setCurrentIndex(index);
	}

	deviceId = settings_->value("audio/deviceId", "").toString();
	index = ui->audioDevicesComboBox->findData(deviceId);
	if (index != -1) {
		ui->audioDevicesComboBox->setCurrentIndex(index);
	}
}

void MainWindow::saveSettings()
{
	settings_->setValue("midi/channel", ui->channelSpinBox->value());
	settings_->setValue("midi/controlNumber", ui->controlNumberSpinBox->value());
	settings_->setValue("midi/deviceId", ui->midiDevicesComboBox->currentData().toString());
	settings_->setValue("audio/deviceId", ui->audioDevicesComboBox->currentData().toString());
}

void MainWindow::on_autorunCheckBox_toggled(bool checked)
{
	Util::setAutorun(checked);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	this->hide();
	saveSettings();
	event->ignore();
}

QString MainWindow::configFilePath()
{
	QString path = QDir::toNativeSeparators(QCoreApplication::applicationDirPath() + "/config.ini");
	return path;
}

void MainWindow::on_audioDevicesComboBox_currentIndexChanged(int index)
{
	Q_UNUSED(index);
	audioWatcher_->setCurrentDeviceId(ui->audioDevicesComboBox->currentData().toString());
}
