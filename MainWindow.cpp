#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>

#include "qmidi/QMidiOut.h"
#include "qmidi/QMidiFile.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	audioWatcher_(new QSystemAudioWatcher(this))
{
	ui->setupUi(this);
	setFixedSize(this->geometry().width(), this->geometry().height());

	connect(audioWatcher_, &QSystemAudioWatcher::volumeLevelChanged, this, &MainWindow::onVolumeLevelChanged);
	audioWatcher_->start();

	fillDeviceList();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::onVolumeLevelChanged(int value)
{
	ui->volumeLevelLabel->setText(QString::number(value));
}

void MainWindow::on_pushButton_clicked()
{
	QMidiOut midi;
	midi.connect("1");

	midi.controlChange(12, 13, 120);

	midi.disconnect();
}

void MainWindow::fillDeviceList()
{
	ui->midiDevicesComboBox->clear();

	QMap<QString, QString> vals = QMidiOut::devices();
	for (const QString &key : vals.keys()) {
		ui->midiDevicesComboBox->addItem(vals[key], key);
	}
}
