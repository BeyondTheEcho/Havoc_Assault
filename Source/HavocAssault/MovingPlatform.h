// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class HAVOCASSAULT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void CheckReverseDirection();
	void MoveTowardsCurrentWaypoint(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="Platform Config")
	float m_Speed = 100.0f;
	UPROPERTY(EditAnywhere, Category = "Platform Config")
	AActor* m_WaypointStart;
	UPROPERTY(EditAnywhere, Category = "Platform Config")
	AActor* m_WaypointEnd;
	UPROPERTY(EditAnywhere, Category = "Platform Config")
	float m_TargetDistanceTolerance = 5.0f;

	FVector m_StartPosition;
	AActor* m_CurrentWaypoint;

};
