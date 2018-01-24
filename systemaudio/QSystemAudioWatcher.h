#ifndef QSYSTEMAUDIOWATCHER_H
#define QSYSTEMAUDIOWATCHER_H

#include <QObject>
#include <QTimer>

#include "systemaudio/QSystemAudio.h"

class QSystemAudioWatcher : public QObject
{
	Q_OBJECT
public:
	explicit QSystemAudioWatcher(QObject *parent = 0);

	void setCurrentDeviceId(const QString &currentDeviceId);

signals:
	void volumeLevelChanged(int value);

public slots:
	void start();
	void stop();

private slots:
	void onTimerTick();

private:
	int currentVolumeLevel_ = 0;
	QString currentDeviceId_ = "";

	QTimer *volumeChangeTimer_;
	//QSystemAudio systemAudio;
};

#endif // QSYSTEMAUDIOWATCHER_H
