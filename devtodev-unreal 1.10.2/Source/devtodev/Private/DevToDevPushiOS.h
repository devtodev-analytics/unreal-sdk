#pragma once

#if PLATFORM_IOS

#include "DTDPushImpl.h"

class DevToDevPushiOS : public DTDPushImpl
{
public:
	explicit DevToDevPushiOS();	

	virtual void Initialize() override;
};

#endif
