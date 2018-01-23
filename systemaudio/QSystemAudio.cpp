#include "QSystemAudio.h"

#include <QDebug>

#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

QSystemAudio::QSystemAudio(QObject *parent) : QObject(parent)
{

}

//int QSystemAudio::getVolume()
//{
//	CoInitialize(NULL);

//	IMMDeviceEnumerator* deviceEnumerator = NULL;
//	if(CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator) == S_OK) {
//		IMMDevice* defaultDevice = NULL;
//		if(deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice) == S_OK) {
//			IAudioEndpointVolume* endpointVolume = NULL;
//			if(defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume) == S_OK) {
//				float val;
//				endpointVolume->GetMasterVolumeLevel(&val);
//				qDebug() << val;
//				endpointVolume->SetMasterVolumeLevelScalar((float)30 / 100, NULL);
//				endpointVolume->Release();
//			}
//			defaultDevice->Release();
//		}
//		deviceEnumerator->Release();
//	}

//	CoUninitialize();

//	CoInitialize(NULL);
//	IMMDeviceEnumerator *deviceEnumerator = NULL;
//	HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
//	IMMDevice *defaultDevice = NULL;

//	hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
//	deviceEnumerator->Release();
//	deviceEnumerator = NULL;

//	IAudioEndpointVolume *endpointVolume = NULL;
//	hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
//	defaultDevice->Release();
//	defaultDevice = NULL;

//	float currentVolume;

//	hr = endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);

//	endpointVolume->Release();

//	CoUninitialize();

//	return currentVolume * 100;
//}

void QSystemAudio::volumeMute(bool isEnable)
{
	CoInitialize(NULL);
	IMMDeviceEnumerator *deviceEnumerator = NULL;
	HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
	IMMDevice *defaultDevice = NULL;

	hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	deviceEnumerator->Release();
	deviceEnumerator = NULL;

	IAudioEndpointVolume *endpointVolume = NULL;
	hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
	defaultDevice->Release();
	defaultDevice = NULL;

	endpointVolume->SetMute(isEnable, NULL);

	endpointVolume->Release();

	CoUninitialize();
}

void QSystemAudio::setVolumeLevel(int value)
{
	CoInitialize(NULL);
	IMMDeviceEnumerator *deviceEnumerator = NULL;
	HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
	IMMDevice *defaultDevice = NULL;

	hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	deviceEnumerator->Release();
	deviceEnumerator = NULL;

	IAudioEndpointVolume *endpointVolume = NULL;
	hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
	defaultDevice->Release();
	defaultDevice = NULL;

	hr = endpointVolume->SetMasterVolumeLevelScalar((float)value / 100, NULL);

	endpointVolume->Release();

	CoUninitialize();
}

int QSystemAudio::volumeLevel()
{
	CoInitialize(NULL);

	float currentVolume = -1;

	IMMDeviceEnumerator* deviceEnumerator = NULL;
	if(CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator) == S_OK) {
		IMMDevice* defaultDevice = NULL;
		if(deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice) == S_OK) {
			IAudioEndpointVolume* endpointVolume = NULL;
			if(defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume) == S_OK) {
				endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
				endpointVolume->Release();
			}
			defaultDevice->Release();
		}
		deviceEnumerator->Release();
	}

	CoUninitialize();

	return currentVolume * 100;
}

int QSystemAudio::muteStatus()
{
	CoInitialize(NULL);
	IMMDeviceEnumerator *deviceEnumerator = NULL;
	HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
	IMMDevice *defaultDevice = NULL;

	hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	deviceEnumerator->Release();
	deviceEnumerator = NULL;

	IAudioEndpointVolume *endpointVolume = NULL;
	hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
	defaultDevice->Release();
	defaultDevice = NULL;

	BOOL muteStatus;

	hr = endpointVolume->GetMute(&muteStatus);

	endpointVolume->Release();

	CoUninitialize();

	return muteStatus;
}
