// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ResourcePoint.h"
#include "BuildingPart.h"
#include "Kismet/GameplayStatics.h"
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

	/** Player Inventory **/

	// Tracks the number of materials collected by player
	UPROPERTY()
	float matsCollected;

	// Tracks the number of objects built in scene
	UPROPERTY()
	float objectsBuilt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	TArray<TSubclassOf<AResourcePoint>> ResourcesArray;

	UPROPERTY(VisibleDefaultsOnly, Category = "Resources")
	TArray<FString> ResourcesNameArray;

	UPROPERTY(VisibleDefaultsOnly, Category = "Resources")
	TArray<int> ResourcesAmountArray;

	UFUNCTION()
	void GiveResource(int amount, FString resource);

};

