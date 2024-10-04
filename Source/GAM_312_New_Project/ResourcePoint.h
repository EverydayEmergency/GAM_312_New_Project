// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ResourcePoint.generated.h"

UCLASS()
class GAM_312_NEW_PROJECT_API AResourcePoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourcePoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Name of the resource
	UPROPERTY(EditAnywhere)
	FString resourceName = "None";

	// Everytime a resource is gathered it will raise by this amount
	UPROPERTY(EditAnywhere)
	int resourceAmount = 5;

	// The total amount before resource is depleted
	UPROPERTY(EditAnywhere)
	int totalResource = 100;

	// Text for text render to set
	UPROPERTY()
	FText tempText;

	// Text for UI
	UPROPERTY(EditAnywhere)
	UTextRenderComponent* ResourceNameTxt;

	// Resource static mesh component
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	// Resource static mesh
	UPROPERTY(EditAnywhere)
	UStaticMesh* resourceMesh;
};
