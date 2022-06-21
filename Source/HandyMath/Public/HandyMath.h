// Created by Jeremie Boga in 2020

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FHandyMathModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
