// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAM_312_New_ProjectCharacter.h"
#include "GAM_312_New_ProjectProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


//////////////////////////////////////////////////////////////////////////
// AGAM_312_New_ProjectCharacter

AGAM_312_New_ProjectCharacter::AGAM_312_New_ProjectCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
	
}

void AGAM_312_New_ProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (ResourcesArray.Num() != 0)
	{
		for (int i = 0; i < ResourcesArray.Num(); i++)
		{
			FString resourceName = ResourcesArray[i].GetDefaultObject()->resourceName;
			ResourcesNameArray.Add(resourceName);
			ResourcesAmountArray.Add(0);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, resourceName);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(ResourcesAmountArray[i]));
		}
	}
	
}

//////////////////////////////////////////////////////////////////////////// Input

void AGAM_312_New_ProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGAM_312_New_ProjectCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGAM_312_New_ProjectCharacter::Look);

		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AGAM_312_New_ProjectCharacter::FindObject);
	}
}

void AGAM_312_New_ProjectCharacter::FindObject()
{
	// Makes a line trace
	FHitResult HitResult;
	FVector StartLocation = FirstPersonCameraComponent->GetComponentLocation(); // Location of camera
	FVector Direction = FirstPersonCameraComponent->GetForwardVector() * 800.0f; // Direction camera is looking in 800 units ahead of camera
	FVector EndLocation = StartLocation + Direction;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // Ignores player character
	QueryParams.bTraceComplex = true; // Traces complex collisions
	QueryParams.bReturnFaceIndex = true; // Returns face normals
	// Performs line trace
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams))
	{
		AResourcePoint* HitResource = Cast<AResourcePoint>(HitResult.GetActor()); // if the hitresult has a resource actor then it is assigned to hitresource

		if (Stamina > 5.0f)
		{
			if (HitResource)
			{
				FString hitName = HitResource->resourceName; // Gets the name of resource collected
				int resourceValue = HitResource->resourceAmount; // Gets the resource's value

				HitResource->totalResource = HitResource->totalResource - resourceValue; // Subtracts the value of the resource from the total resource value

				// If there is more in total resource then the resource value is added to the value of whatever resource it is
				if (HitResource->totalResource > resourceValue)
				{
					GiveResource(resourceValue, hitName); // Updates a specific resources value
					SetStamina(-5.0f);
				}
				else
				{
					HitResource->Destroy(); // If there are no resources left then destroy resource
					check(GEngine != nullptr);
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Depleted"));
				}
			}
		}
	}

}


void AGAM_312_New_ProjectCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AGAM_312_New_ProjectCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AGAM_312_New_ProjectCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AGAM_312_New_ProjectCharacter::GetHasRifle()
{
	return bHasRifle;
}

//////////////////////////////////////////////////////////////////////////// Additional Functions

void AGAM_312_New_ProjectCharacter::SetHealth(float amount)
{
	if (Health + amount < 100)
	{
		Health = Health + amount;
	}
	else if (Health + amount > 100)
	{
		Health = 100;
	}
}

void AGAM_312_New_ProjectCharacter::SetHunger(float amount)
{
	if (Hunger + amount < 100)
	{
		Hunger = Hunger + amount;
	}
	else if (Hunger + amount > 100)
	{
		Hunger = 100;
	}
}

void AGAM_312_New_ProjectCharacter::SetStamina(float amount)
{
	if (Stamina + amount < 100)
	{
		Stamina = Stamina + amount;
	}
	else if (Stamina + amount > 100)
	{
		Stamina = 100;
	}
}

void AGAM_312_New_ProjectCharacter::DecreaseStats()
{
	if (Hunger > 0)
	{
		SetHunger(-1.0f); //Increases player hunger everytime function is called

	}

	SetStamina(10.0f); // Regeneates stamina everytime function is called

	//If hunger is less than or equal to 0 then health starts to decrease instead
	if (Hunger <= 0)
	{
		SetHealth(-3.0f);
	}
}

void AGAM_312_New_ProjectCharacter::GiveResource(int amount, FString resource)
{
	for (int i = 0; i < ResourcesArray.Num(); i++)
	{
		if (resource == ResourcesNameArray[i])
		{
			ResourcesAmountArray[i] = ResourcesAmountArray[i] + amount;
			FString total = FString::FromInt(ResourcesAmountArray[i]);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Added ") + FString::FromInt(amount) + TEXT(" ") + resource);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Total ") + resource + TEXT(": ") + total);
		}
	}
}
