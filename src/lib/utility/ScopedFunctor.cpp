#include "ScopedFunctor.h"

ScopedFunctor::ScopedFunctor(std::function<void(void)> onDestroy)
	: m_onDestroy(onDestroy)
{
}

ScopedFunctor::~ScopedFunctor()
{
	m_onDestroy();
}
