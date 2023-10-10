// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	m_StartPosition = GetActorLocation();

	if (m_WaypointStart)
	{
		m_CurrentWaypoint = m_WaypointEnd;
		SetActorLocation(m_WaypointStart->GetActorLocation());
	}
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckReverseDirection();

	MoveTowardsCurrentWaypoint(DeltaTime);
}

void AMovingPlatform::CheckReverseDirection()
{
	FVector locationDifference = GetActorLocation() - m_CurrentWaypoint->GetActorLocation();

	if (locationDifference.SizeSquared() <= (m_TargetDistanceTolerance * m_TargetDistanceTolerance))
	{
		if (m_CurrentWaypoint == m_WaypointStart)
		{
			m_CurrentWaypoint = m_WaypointEnd;
		}
		else
		{
			m_CurrentWaypoint = m_WaypointStart;
		}
	}
}

void AMovingPlatform::MoveTowardsCurrentWaypoint(float DeltaTime)
{
	FVector currentLocation = GetActorLocation();
	FVector targetLocation = m_CurrentWaypoint->GetActorLocation();

	FVector direction = targetLocation - currentLocation;
	direction.Normalize();

	currentLocation += direction * m_Speed * DeltaTime;

	SetActorLocation(currentLocation);
}



