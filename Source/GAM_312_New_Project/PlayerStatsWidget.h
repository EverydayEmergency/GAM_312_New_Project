// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatsWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAM_312_NEW_PROJECT_API UPlayerStatsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateBars(float Health, float Hunger, float Stamina);
};
