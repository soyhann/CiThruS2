#pragma once

#include "CoreMinimal.h"

struct FTrafficCollisionResult
{
    bool bWillCollide = false;
    double TimeToImpact = 0.0f;
    double ClosestDistance = 0.0f;
};

/**
 * Static helper for predicting collision risk between two moving objects
 */
class FTrafficCollisionHelper
{
public:

    /**
     * Predict collision between two moving actors
     */
    static bool CheckCollisionRisk(
        const FVector& EgoPos,
        const FVector& EgoVel,
        float EgoRadius,
        const FVector& OtherPos,
        const FVector& OtherVel,
        float OtherRadius,
        float MaxPredictionTime,
        FTrafficCollisionResult& OutResult)
    {
        const double EgoSpeedSq = EgoVel.SizeSquared();

        // no ego motion -> no warning
        if (EgoSpeedSq < FMath::Square(5.0f))
        {
            return false;
        }

        FVector RelPos = OtherPos - EgoPos;
        FVector RelVel = OtherVel - EgoVel;

        double VelSq = RelVel.SizeSquared();

        if (VelSq < KINDA_SMALL_NUMBER)
        {
            return false;
        }

        // Not approaching -> ignore
       /* if (FVector::DotProduct(RelPos, RelVel) >= 0.0f)
        {
            return false;
        }*/

        double t = -FVector::DotProduct(RelPos, RelVel) / VelSq;
        t = FMath::Clamp(t, 0.0f, MaxPredictionTime);

        FVector ClosestRelPos = RelPos + RelVel * t;
        double DistSq = ClosestRelPos.SizeSquared();

        double CombinedRadius = EgoRadius + OtherRadius;

        if (DistSq <= CombinedRadius * CombinedRadius)
        {
            OutResult.bWillCollide = true;
            OutResult.TimeToImpact = t;
            OutResult.ClosestDistance = FMath::Sqrt(DistSq);
            return true;
        }

        return false;
    }
};
