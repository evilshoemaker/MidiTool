#ifndef QSYSTEMAUDIO_H
#define QSYSTEMAUDIO_H

#include <QObject>

class QSystemAudio : public QObject
{
	Q_OBJECT
public:
	explicit QSystemAudio(QObject *parent = 0);

	void volumeMute(bool isEnable);
	void setVolumeLevel(int value);
	int static volumeLevel();
	int muteStatus();

signals:

public slots:
};

#endif // QSYSTEMAUDIO_H
