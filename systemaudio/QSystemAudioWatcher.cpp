#include "QSystemAudioWatcher.h"

QSystemAudioWatcher::QSystemAudioWatcher(QObject *parent)
	: QObject(parent),
	  volumeChangeTimer_(new QTimer(this))
{
	volumeChangeTimer_->setInterval(20);
	connect(volumeChangeTimer_, &QTimer::timeout, this, &QSystemAudioWatcher::onTimerTick);
}

void QSystemAudioWatcher::start()
{
	volumeChangeTimer_->start();
}

void QSystemAudioWatcher::stop()
{
	volumeChangeTimer_->stop();
}

void QSystemAudioWatcher::onTimerTick()
{
	int value = -100;
	if (currentDeviceId_.isEmpty()) {
		value = QSystemAudio::volumeLevel();
	}
	else {
		value = QSystemAudio::volumeLevel(currentDeviceId_);
	}

	if (value != currentVolumeLevel_) {
		currentVolumeLevel_ = value;
		emit volumeLevelChanged(currentVolumeLevel_);
	}
}

void QSystemAudioWatcher::setCurrentDeviceId(const QString &currentDeviceId)
{
	currentDeviceId_ = currentDeviceId;
}
