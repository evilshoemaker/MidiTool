#include "QSystemAudio.h"

#include <QDebug>

#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

#include "functiondiscoverykeys_devpkey.h"
//#include "Propvarutil.h"

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

int QSystemAudio::volumeLevel(const QString &id)
{
	float currentVolume = -1;
	HRESULT hr = CoInitialize(NULL);

	if (SUCCEEDED(hr))
	{
		IMMDeviceEnumerator *pEnum = NULL;
		hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void **)&pEnum);

		if (SUCCEEDED(hr)) {
			IMMDevice *device;
			LPCWSTR deviceId = (const wchar_t*) id.utf16();;

			hr = pEnum->GetDevice(deviceId, &device);
			if (SUCCEEDED(hr)) {
				IAudioEndpointVolume* endpointVolume = NULL;
				hr = device->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
				if (SUCCEEDED(hr)) {
					endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
					endpointVolume->Release();
				}

				device->Release();
			}

			pEnum->Release();
		}
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

QMap<QString, QString> QSystemAudio::devices()
{
    QMap<QString, QString> ret;
    /*HRESULT hr = CoInitialize(NULL);

	if (SUCCEEDED(hr))
	{
		IMMDeviceEnumerator *pEnum = NULL;
		hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void **)&pEnum);

		if (SUCCEEDED(hr))
		{
			LPWSTR defaultDeviceId = NULL;
			IMMDevice *pDefaultDevice;

			HRESULT hr = pEnum->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDefaultDevice);

			if (SUCCEEDED(hr))
			{
				hr = pDefaultDevice->GetId(&defaultDeviceId);

				if (!SUCCEEDED(hr))
				{
					defaultDeviceId = NULL;
				}

				pDefaultDevice->Release();
			}

			IMMDeviceCollection *pDevices;

			hr = pEnum->EnumAudioEndpoints(eRender, DEVICE_STATE_ACTIVE, &pDevices);

			if (SUCCEEDED(hr))
			{
				UINT count;

				pDevices->GetCount(&count);

				if (SUCCEEDED(hr))
				{
					for (UINT i = 0; i < count; ++i)
					{
						IMMDevice *pDevice;
						HRESULT hr = pDevices->Item(i, &pDevice);

						if (SUCCEEDED(hr))
						{
							LPWSTR wstrID = NULL;

							hr = pDevice->GetId(&wstrID);

							if (SUCCEEDED(hr))
							{
								IPropertyStore *pStore;
								hr = pDevice->OpenPropertyStore(STGM_READ, &pStore);

								if (SUCCEEDED(hr))
								{
									PROPVARIANT friendlyName;

									PropVariantInit(&friendlyName);
									hr = pStore->GetValue(PKEY_Device_FriendlyName, &friendlyName);

									if (SUCCEEDED(hr))
									{
										ret.insert(QString::fromWCharArray(wstrID),
												   QString::fromWCharArray(friendlyName.pwszVal));

										PropVariantClear(&friendlyName);
									}

									pStore->Release();
								}
							}

							pDevice->Release();
						}
					}
				}

				pDevices->Release();
			}

			pEnum->Release();
		}
    }*/

	return ret;
}

/*void QSystemAudio::devices()
{
	HRESULT hr = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		IMMDeviceEnumerator *pEnum = NULL;
		hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void **)&pEnum);

		if (SUCCEEDED(hr))
		{
			IMMDeviceCollection *pDevices;
			hr = pEnum->EnumAudioEndpoints(eRender, DEVICE_STATE_ACTIVE, &pDevices);

			if (SUCCEEDED(hr))
			{
				UINT count;

				pDevices->GetCount(&count);

				if (SUCCEEDED(hr))
				{
					for (unsigned int deviceIndex = 0; deviceIndex < count; deviceIndex++) {
						IMMDevice *pDevice;
						hr = pDevices->Item(deviceIndex, &pDevice);

						if (SUCCEEDED(hr))
						{
							LPWSTR wstrID = NULL;

							hr = pDevice->GetId(&wstrID);

							if (SUCCEEDED(hr))
							{
								IPropertyStore *pStore;
								hr = pDevice->OpenPropertyStore(STGM_READ, &pStore);

								if (SUCCEEDED(hr))
								{
									PROPVARIANT friendlyName;

									PropVariantInit(&friendlyName);
									hr = pStore->GetValue(PKEY_Device_FriendlyName, &friendlyName);

									if (SUCCEEDED(hr))
									{
										WCHAR szTitle[128];
										hr = PropVariantToString(friendlyName, szTitle, ARRAYSIZE(szTitle));

										if (SUCCEEDED(hr)) {
											QString title = QString::fromWCharArray(szTitle);
											qDebug() << title;
										}

										PropVariantClear(&friendlyName);
									}

									pStore->Release();
								}
							}

							pDevice->Release();
						}
					}
				}

				pDevices->Release();
			}

			pEnum->Release();
		}
	}

	//return result;
}*/
