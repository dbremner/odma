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
