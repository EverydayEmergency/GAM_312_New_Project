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

	// Name of the building part
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Part Information")
	FString BuildingPartName = "Null";

	// The ID number of a part
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Part Information")
	int partID = 0;

	// The amount of a resource used to make the building part
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources Used")
	TMap<TSubclassOf<AResourcePoint>, int32> resourcesUsed;
};
