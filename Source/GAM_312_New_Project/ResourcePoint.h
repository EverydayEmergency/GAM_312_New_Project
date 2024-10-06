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
	UPROPERTY(EditAnywhere, Category = "Resource Information")
	FString resourceName = "None";

	// Description of the resource
	UPROPERTY(EditAnywhere, Category = "Resource Information")
	FString resourceDescription = "Nothing to see here.";

	// Everytime a resource is gathered it will raise by this amount
	UPROPERTY(EditAnywhere, Category = "Resource Information")
	int resourceAmount = 5;

	// The total amount before resource is depleted
	UPROPERTY(EditAnywhere, Category = "Resource Information")
	int totalResource = 100;

	// Sound effects used when gathering resource
	UPROPERTY(EditAnywhere, Category = "Resource Information")
	TArray<USoundWave*> soundEffects;


	// Checks to see if the resource is edible
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Information")
	bool isEdible = false;

	// The amount of health that is restored if the resource is food
	UPROPERTY(EditAnywhere, Category = "Resource Information|Food Stats", meta=(EditCondition="isEdible", EditConditionHides))
	int healthRestored = 0;

	// The amount of hunger that is restored if the resource is food
	UPROPERTY(EditAnywhere, Category = "Resource Information|Food Stats", meta = (EditCondition = "isEdible", EditConditionHides))
	int hungerRestored = 10;

	// The amount of stamina that is restored if the resource is food
	UPROPERTY(EditAnywhere, Category = "Resource Information|Food Stats", meta = (EditCondition = "isEdible", EditConditionHides))
	int staminaRestored = 0;

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
