#pragma once
#pragma once
#include "Mmdeviceapi.h"

#define SAFE_RELEASE(punk)  \
              if ((punk) != NULL)  \
                { (punk)->Release(); (punk) = NULL; }

#define SAFE_DELETE(punk)  \
              if ((punk) != NULL)  \
                { delete (punk); (punk) = NULL; }

static PROPERTYKEY key;

class CMMNotificationClient : IMMNotificationClient
{
	LONG _cRef;
	IMMDeviceEnumerator* _pEnumerator;

	// Private function to print device-friendly name
	HRESULT _PrintDeviceName(LPCWSTR  pwstrId);

public:
	CMMNotificationClient() :
		_cRef(1),
		_pEnumerator(NULL)
	{
	}
	~CMMNotificationClient()
	{
		SAFE_RELEASE(_pEnumerator)
	}

	// IUnknown methods -- AddRef, Release, and QueryInterface
	ULONG STDMETHODCALLTYPE AddRef()
	{
		return InterlockedIncrement(&_cRef);
	}

	ULONG STDMETHODCALLTYPE Release()
	{
		ULONG ulRef = InterlockedDecrement(&_cRef);
		if (0 == ulRef)
		{
			delete this;
		}
		return ulRef;
	}

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, VOID** ppvInterface)
	{
		if (IID_IUnknown == riid)
		{
			AddRef();
			*ppvInterface = (IUnknown*)this;
		}
		else if (__uuidof(IMMNotificationClient) == riid)
		{
			AddRef();
			*ppvInterface = (IMMNotificationClient*)this;
		}
		else
		{
			*ppvInterface = NULL;
			return E_NOINTERFACE;
		}
		return S_OK;
	}

	// Callback methods for device-event notifications.

	HRESULT STDMETHODCALLTYPE OnDefaultDeviceChanged(EDataFlow flow, ERole role, LPCWSTR pwstrDeviceId)
	{
		
		if (flow == eRender && role == eConsole) {
			_PrintDeviceName(pwstrDeviceId);
			g_bsWin32Audio->isInitDone = 0;
			g_bsWin32Audio->CreateAudioListener((*g_osGlobals)->window);

		}
		
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE OnDeviceAdded(LPCWSTR pwstrDeviceId)
	{
		return S_OK;
	};

	HRESULT STDMETHODCALLTYPE OnDeviceRemoved(LPCWSTR pwstrDeviceId)
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE OnDeviceStateChanged(LPCWSTR pwstrDeviceId, DWORD dwNewState)
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE OnPropertyValueChanged(LPCWSTR pwstrDeviceId, const PROPERTYKEY key)
	{
		return S_OK;
	}
};

	// Given an endpoint ID string, print the friendly device name.
	HRESULT CMMNotificationClient::_PrintDeviceName(LPCWSTR pwstrId)
	{
		HRESULT hr = S_OK;
		IMMDevice* pDevice = NULL;
		IPropertyStore* pProps = NULL;
		PROPVARIANT varString;
		CoInitialize(NULL);
		PropVariantInit(&varString);
		GUID IDevice_FriendlyName = { 0xa45c254e, 0xdf1c, 0x4efd, { 0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8, 0x50, 0xe0 } };
		key.pid = 14;
		key.fmtid = IDevice_FriendlyName;
		if (_pEnumerator == NULL)
		{
			// Get enumerator for audio endpoint devices.
			hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),
				NULL, CLSCTX_INPROC_SERVER,
				__uuidof(IMMDeviceEnumerator),
				(void**)&_pEnumerator);
		}
		if (hr == S_OK)
		{
			hr = _pEnumerator->GetDevice(pwstrId, &pDevice);
		}
		if (hr == S_OK)
		{
			hr = pDevice->OpenPropertyStore(STGM_READ, &pProps);
		}
		if (hr == S_OK)
		{
			// Get the endpoint device's friendly-name property.
			hr = pProps->GetValue(key, &varString);
		}
		Console_Print("----------------------\nDevice name: \"%S\"\n"
			"  Endpoint ID string: \"%S\"\n",
			(hr == S_OK) ? varString.pwszVal : L"null device",
			(pwstrId != NULL) ? pwstrId : L"null ID");

		PropVariantClear(&varString);

		SAFE_RELEASE(pProps)
			SAFE_RELEASE(pDevice)
			CoUninitialize();
		return hr;
	}

CMMNotificationClient* pNotifyClient = NULL;

bool RegisterForNotification() {
	HRESULT hr = S_OK;//CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		IMMDeviceEnumerator* pEnum = NULL;
		// Create a multimedia device enumerator.
		hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL,
			CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pEnum);
		if (SUCCEEDED(hr))
		{
			pNotifyClient = new CMMNotificationClient();
			IMMNotificationClient* pNotify = (IMMNotificationClient*)(pNotifyClient);
			hr = pEnum->RegisterEndpointNotificationCallback(pNotify);
			if (SUCCEEDED(hr)) {
				PrintLog("Notification register success");
			}
			if (!SUCCEEDED(hr)) {
				PrintLog("Notification register error:");
				PrintLog("%s", (hr == E_POINTER ? "E_POINTER" :
					(hr == E_OUTOFMEMORY ? "E_OUTOFMEMORY" :
						(hr == E_NOTFOUND ? "E_NOTFOUND" : "NOT_DEFINED"))), "Error");
			}
		}
		pEnum->Release();
	}
	return SUCCEEDED(hr);
}
