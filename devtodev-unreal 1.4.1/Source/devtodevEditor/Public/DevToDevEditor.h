// Copyright 2018-2019 devtodev. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

/**
 * The public interface to this module
 */
class FDevToDevEditor : public IModuleInterface {
  public:
    /** IModuleInterface implementation */
    void StartupModule();
    void ShutdownModule();
};