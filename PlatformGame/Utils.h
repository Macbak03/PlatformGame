#pragma once
class Utils
{
public:
	template <typename T> static int sgn(T value);
};

template<typename T>
inline int Utils::sgn(T value)
{
	return (T(0) < value) - (value < T(0));
}
