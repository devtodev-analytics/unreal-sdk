#include "DevToDevPrivatePCH.h"

#include "DTDPushImpl.h"

DTDPushImpl::DTDPushImpl() : isInitialized(false)
{

}

void DTDPushImpl::Initialize()
{
	isInitialized = true;
}