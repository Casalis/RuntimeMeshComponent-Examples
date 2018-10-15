// Fill out your copyright notice in the Description page of Project Settings.

#include "RuntimeMeshBasic.h"
#include "RuntimeMeshComponent.h"
#include "RuntimeMeshShapeGenerator.h"
#include "RuntimeMeshBuilder.h"
#include "RuntimeMeshLibrary.h"
#include "RuntimeMeshData.h"
#include "RuntimeMesh.h"


// Sets default values
ARuntimeMeshBasic::ARuntimeMeshBasic()
	: BoxSize(100.0f, 100.0f, 100.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bRunGenerateMeshesOnConstruction = false;
	bRunGenerateMeshesOnBeginPlay = true;
}



void ARuntimeMeshBasic::GenerateMeshes_Implementation()
{
/*	TSharedPtr<FRuntimeMeshBuilder> Builder = MakeRuntimeMeshBuilder<FRuntimeMeshTangentsHighPrecision, FRuntimeMeshDualUV, uint16>();*/

	URuntimeMesh* RuntimeMesh = GetRuntimeMeshComponent()->GetOrCreateRuntimeMesh();
	RuntimeMesh->SetCollisionUseAsyncCooking(true);

	FRuntimeMeshDataPtr Data = RuntimeMesh->GetRuntimeMeshData();
	Data->EnterSerializedMode();

	Data->CreateMeshSection(0, false, false, 1, false, true, EUpdateFrequency::Infrequent);

	auto Section = Data->BeginSectionUpdate(0, 0);
	URuntimeMeshShapeGenerator::CreateBoxMesh(BoxSize * 0.75f, *Section.Get());
	Section->Commit();

	Section = Data->BeginSectionUpdate(0, 1);
	URuntimeMeshShapeGenerator::CreateBoxMesh(BoxSize * 0.6f, *Section.Get());
	Section->Commit();

	Section = Data->BeginSectionUpdate(0, 2);
	URuntimeMeshShapeGenerator::CreateBoxMesh(BoxSize * 0.4f, *Section.Get());
	Section->Commit();

	Section = Data->BeginSectionUpdate(0, 3);
	URuntimeMeshShapeGenerator::CreateBoxMesh(BoxSize * 0.2f, *Section.Get());
	Section->Commit();

	Data->SetLODScreenSize(0, 1.0f);
	Data->SetLODScreenSize(1, 0.75f);
	Data->SetLODScreenSize(2, 0.25f);
	Data->SetLODScreenSize(3, 0.15f);
}

