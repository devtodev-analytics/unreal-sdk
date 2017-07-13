#pragma once

class DTDPushImpl
{
public:
	DTDPushImpl();

	virtual ~DTDPushImpl() {};

	virtual void Initialize();

	inline bool IsInitialized() { return isInitialized; }

private:
	bool isInitialized;
};
