// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ResourcePoint.h"
#include "BuildingPart.h"
#include "ObjectiveWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerStatsWidget.h"
#include "InputActionValue.h"
#include "GAM_312_New_ProjectCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class AGAM_312_New_ProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	/** Rotate Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RotatePartAction;
	
public:
	AGAM_312_New_ProjectCharacter();

protected:
	virtual void BeginPlay();

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void FindObject();

	/** Player Stats **/

	// Player health variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Health = 100.0f;

	// Player hunger variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Hunger = 100.0f;

	// Player stamina variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Stamina = 100.0f;

	// Function to assign an amount to the health variable
	UFUNCTION(BlueprintCallable)
	void SetHealth(float amount);

	// Function to assign an amount to the hunger variable
	UFUNCTION(BlueprintCallable)
	void SetHunger(float amount);

	// Function to assign an amount to the stamina variable
	UFUNCTION(BlueprintCallable)
	void SetStamina(float amount);

	// Function to decrease a stat
	UFUNCTION()
	void DecreaseStats();

	// Variable playerUI is derived from the UPlayerWidget files
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPlayerStatsWidget* playerUI;

	/** Resources **/

	// Tracks the number of materials collected by player
	UPROPERTY()
	float matsCollected;

	// Array of all the resources that are being used in the game
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	TArray<TSubclassOf<AResourcePoint>> ResourcesArray;

	// Array of all the names of the resources being used in the game
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Resources")
	TArray<FString> ResourcesNameArray;

	// Array containing the amount of every resource that is gathered in the game
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Resources")
	TArray<int> ResourcesAmountArray;

	// Function to add to the total amount of a given resource
	UFUNCTION()
	void GiveResource(int amount, FString resource);

	UFUNCTION(BlueprintCallable)
	AResourcePoint* FindResourceByName(FString name);

	// Function that finds the index of a resource based off of the resource's name
	UFUNCTION(BlueprintCallable)
	int FindResourceIndex(FString resourceName);

	// Function to eat a food resource
	UFUNCTION(BlueprintCallable)
	void EatFood(AResourcePoint* resource);

	/** Building Parts **/
	
	// Array of all the building parts that are being used in the game
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Parts")
	TArray<TSubclassOf<ABuildingPart>> BuildingPartsArray;

	// Array of all the names of the building parts being used in the game
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Building Parts")
	TArray<FString> BuildingPartsNameArray;

	// Array containing the amount of every building part that is created in the game
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Building Parts")
	TArray<int> BuildingPartsAmountArray;

	// Function to create a building part
	UFUNCTION(BlueprintCallable)
	void CreateBuildingPart(TSubclassOf <ABuildingPart> buildingObject);

	// Function to create a building part
	UFUNCTION(BlueprintCallable)
	void CreateBuildingPartByName(FString partName);

	// Function that finds the index of a building part based off of the building part's name
	UFUNCTION(BlueprintCallable)
	int FindBuildingPartIndex(FString partName);

	// Function that finds the names of the resources used to create a building object
	UFUNCTION(BlueprintCallable)
	TArray<FString> FindBuildingPartResourcesNames(TSubclassOf<ABuildingPart> buildingObject);

	// Function to to find the amount of the resources used to create a building object
	UFUNCTION(BlueprintCallable)
	TArray<int> FindBuildingPartResourcesAmount(TSubclassOf<ABuildingPart> buildingObject);
	
	// Tracks the number of objects built in scene
	UPROPERTY()
	float objectsBuilt;

	UPROPERTY()
	bool isBuilding;

	UPROPERTY()
	ABuildingPart* spawnedPart;

	// Spawns building
	UFUNCTION(BlueprintCallable)
	void SpawnBuilding(FString buildingObject, bool& isSuccess);

	// Rotates building
	UFUNCTION()
	void RotateBuilding();	

	/** SFX **/
	// Function played when a resource is being gathered
	UFUNCTION()
	void playGatheringSFX(AResourcePoint* resource);

	// Sound effects played when creating a part
	UPROPERTY(EditAnywhere, Category = "SFX")
	USoundWave* buildingSFX;

	// Sound effects played when placing a part
	UPROPERTY(EditAnywhere, Category = "SFX")
	USoundWave* placingSFX;

	// Sound effects played when there is not enough of a resource or building part
	UPROPERTY(EditAnywhere, Category = "SFX")
	USoundWave* notEnoughSFX;

	// Sound effects played if there is an error
	UPROPERTY(EditAnywhere, Category = "SFX")
	USoundWave* errorSFX;

	// Function played when creating a part
	UFUNCTION()
	void playBuildingSFX();

	// Function played when placing a part
	UFUNCTION()
	void playPlacingSFX();

	// Function played when there is not enough of a resource or building part
	UFUNCTION()
	void playNotEnoughSFX();

	// Function played when there is a error
	UFUNCTION()
	void playErrorSFX();

	/** Miscellaneous **/
	// Variable objWidget is derived from the UObjectiveWidget files
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObjectiveWidget* objWidget;
};

