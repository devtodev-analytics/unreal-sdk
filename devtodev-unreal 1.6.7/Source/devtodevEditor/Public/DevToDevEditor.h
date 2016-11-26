// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ModuleManager.h"

/**
* The public interface to this module
*/
class FDevToDevEditor : public IModuleInterface
{   
public:
    /** IModuleInterface implementation */
    void StartupModule();
    void ShutdownModule();
};

