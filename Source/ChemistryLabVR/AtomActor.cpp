// Fill out your copyright notice in the Description page of Project Settings.


#include "AtomActor.h"

// Sets default values
AAtomActor::AAtomActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/LevelOne/Atoms/Carbon/SM_Carbon.SM_Carbon'"));

	if(MeshAsset.Object != nullptr)
	{
		Mesh->SetStaticMesh(MeshAsset.Object);
	}

	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(false);
	Mesh->SetNotifyRigidBodyCollision(true);

	//Mesh->BodyInstance.bLockRotation = true;
	Mesh->BodyInstance.bLockXRotation = true;
	Mesh->BodyInstance.bLockYRotation = true;
	Mesh->BodyInstance.bLockZRotation = true;
}

// Called when the game starts or when spawned
void AAtomActor::BeginPlay()
{
	Super::BeginPlay();

	const FVector velocity = FVector(FMath::RandRange(-500,500),FMath::RandRange(-500,500),FMath::RandRange(-500,500));
	Mesh->SetPhysicsLinearVelocity(velocity,true);

	Mesh->OnComponentHit.AddDynamic(this, &AAtomActor::OnHit);

	for (int i = 0; i < 10; i++)
	{
		SpawnObject(AtomsStack[0]);
		SpawnObject(AtomsStack[1]);
		SpawnObject(AtomsStack[2]);
		SpawnObject(AtomsStack[3]);
		SpawnObject(AtomsStack[4]);
		SpawnObject(AtomsStack[5]);
	}
}

// Called every frame
void AAtomActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAtomActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		const FVector velocity = FVector(FMath::RandRange(-500,500),FMath::RandRange(-500,500),FMath::RandRange(-500,500));
		Mesh->SetPhysicsLinearVelocity(velocity,true);
	}
}

void AAtomActor::SpawnObject(UClass* Atom)
{
	FActorSpawnParameters SpawnParams;
	if(GetWorld())
	{
		GetWorld()->SpawnActor<AActor>(Atom,FVector(-30,190,240),FRotator(0,0,0), SpawnParams);
		//if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("SpawnParams"));}

	}
}

