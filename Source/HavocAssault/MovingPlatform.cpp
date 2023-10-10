// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create root component (if needed)
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Initialize properties
	m_StartWaypoint = CreateDefaultSubobject<USceneComponent>(TEXT("StartPoint"));
	m_StartWaypoint->SetupAttachment(RootComponent);

	m_EndWaypoint = CreateDefaultSubobject<USceneComponent>(TEXT("EndPoint"));
	m_EndWaypoint->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	m_StartPoint = m_StartWaypoint->GetComponentLocation();
	m_EndPoint = m_EndWaypoint->GetComponentLocation();

	m_HeadingToEndPoint = true;
	m_CurrentWaypoint = m_EndPoint;
	SetActorLocation(m_StartPoint);
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
	FVector locationDifference = GetActorLocation() - m_CurrentWaypoint;

	if (locationDifference.SizeSquared() <= (m_TargetDistanceTolerance * m_TargetDistanceTolerance))
	{
		if (m_HeadingToEndPoint)
		{
			m_HeadingToEndPoint = !m_HeadingToEndPoint;
			m_CurrentWaypoint = m_StartPoint;
		}
		else
		{
			m_HeadingToEndPoint = !m_HeadingToEndPoint;
			m_CurrentWaypoint = m_EndPoint;
		}
	}
}

void AMovingPlatform::MoveTowardsCurrentWaypoint(float DeltaTime)
{
	FVector currentLocation = GetActorLocation();

	FVector direction = m_CurrentWaypoint - currentLocation;
	direction.Normalize();

	currentLocation += direction * m_Speed * DeltaTime;

	SetActorLocation(currentLocation);
}



