#pragma once

template<class T, T InvalidValue = nullptr>
struct HandleTraitsBase
{
	using Type = T;
	inline static Type GetInvalidValue() noexcept
	{
		return InvalidValue;
	}
};

struct LSAHandleTraits : HandleTraitsBase<LSA_HANDLE>
{
	inline static bool Close(_In_ Type h) noexcept
	{
		return ::LsaClose(h) != FALSE;
	}
};

struct SCHandleTraits : HandleTraitsBase<SC_HANDLE>
{
	inline static bool Close(_In_ Type h) noexcept
	{
		return ::CloseServiceHandle(h) != FALSE;
	}
};

struct EventSourceTraits : HandleTraitsBase<HANDLE>
{
	inline static bool Close(_In_ Type h) noexcept
	{
		return ::DeregisterEventSource(h) != FALSE;
	}
};

struct HKeyTraits : HandleTraitsBase<HKEY>
{
	inline static bool Close(_In_ Type h) noexcept
	{
		return ::RegCloseKey(h) != FALSE;
	}
};

//typedefs
using file_handle = Microsoft::WRL::Wrappers::HandleT<Microsoft::WRL::Wrappers::HandleTraits::HANDLETraits>;
using proc_handle = Microsoft::WRL::Wrappers::HandleT<Microsoft::WRL::Wrappers::HandleTraits::HANDLENullTraits>;
using toolhelp_handle = Microsoft::WRL::Wrappers::HandleT<Microsoft::WRL::Wrappers::HandleTraits::HANDLETraits>;
using lsa_handle = Microsoft::WRL::Wrappers::HandleT<LSAHandleTraits>;
using sc_handle = Microsoft::WRL::Wrappers::HandleT<SCHandleTraits>;
using event_source_handle = Microsoft::WRL::Wrappers::HandleT<EventSourceTraits>;
using registry_handle = Microsoft::WRL::Wrappers::HandleT<HKeyTraits>;
