// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourcePoint.h"

// Sets default values
AResourcePoint::AResourcePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates a text render that appears on the resource
	ResourceNameTxt = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Render"));
	// Creates a mesh for the resource
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	// Assigns the mesh to be the root component of the resource
	RootComponent = Mesh;
	// Attaches text render component to the mesh
	ResourceNameTxt->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AResourcePoint::BeginPlay()
{
	Super::BeginPlay();
	
	// Set tempText to the resource name
	tempText = tempText.FromString(resourceName);

	//Set the resource name text to temp text
	ResourceNameTxt->SetText(tempText);
}

// Called every frame
void AResourcePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

