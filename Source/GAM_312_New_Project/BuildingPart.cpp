// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingPart.h"

// Sets default values
ABuildingPart::ABuildingPart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates a mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	// Creates an arrow component 
	PivotArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Pivot Arrow"));

	// Makes the root component the pivot arrow and attaches the mesh to the arrow
	RootComponent = PivotArrow;
	Mesh->SetupAttachment(PivotArrow);
}

// Called when the game starts or when spawned
void ABuildingPart::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildingPart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

