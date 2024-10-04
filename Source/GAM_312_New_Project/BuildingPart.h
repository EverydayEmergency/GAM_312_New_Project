// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "ResourcePoint.h"
#include "BuildingPart.generated.h"

UCLASS()
class GAM_312_NEW_PROJECT_API ABuildingPart : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingPart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	// Pivot point for all building components
	UPROPERTY(EditAnywhere)
	UArrowComponent* PivotArrow;

	UPROPERTY(EditAnywhere, Category = "Building Part Information")
	FString BuildingPartName = "Null";

	// The name of the part
	UPROPERTY(EditAnywhere, Category = "Building Part Information")
	FString partName = "Null";

	// The ID number of a part
	UPROPERTY(EditAnywhere, Category = "Building Part Information")
	int partID = 0;

	// The amount of wood used to make the building part
	UPROPERTY(EditAnywhere, Category = "Resources Used")
	TMap<TSubclassOf<AResourcePoint>, int32> resourcesUsed;
};