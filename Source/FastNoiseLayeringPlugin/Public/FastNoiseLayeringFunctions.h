

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FastNoiseWrapper.h"
#include "FastNoiseLayeringFunctions.generated.h"

/**
 * 
 */

UENUM(BlueprintType) enum EFN_BlendType
{
	// Enumerator to be used in switch behavior for mathematically blending noise layer values together
	Add			UMETA(DisplayName = "Add"),
	Subtract	UMETA(DisplayName = "Subtract"),
	Multiply	UMETA(DisplayName = "Multiply"),
	Divide		UMETA(DisplayName = "Divide"),
};

UENUM(BlueprintType) enum EFN_FalloffType
{
	// Enumerator to determine if any kind of height falloff management should be done to the terrain
	None		UMETA(DisplayName = "None"),
	Island		UMETA(DisplayName = "Island"),
	Mountains	UMETA(DisplayName = "Mountains")
};

USTRUCT(BlueprintType) struct FFN_NoiseLayerType
{
	// Struct to be used in array variable for defining noise layering behaviors for offsetting vertex Z positions

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LayerName = "LayerName";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFastNoise_NoiseType NoiseType = EFastNoise_NoiseType::Simplex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Seed = 1337;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Frequency = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFastNoise_Interp InterpType = EFastNoise_Interp::Quintic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFastNoise_FractalType FractalType = EFastNoise_FractalType::FBM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Octaves = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Lacunarity = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Gain = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CellularJitter = 0.45;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFastNoise_CellularDistanceFunction CellularDistanceFunction = EFastNoise_CellularDistanceFunction::Euclidean;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFastNoise_CellularReturnType CellularReturnType = EFastNoise_CellularReturnType::CellValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EFN_BlendType> NoiseBlendFunction = Add;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NoiseStrength = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D NoiseBiasScale = FVector2D(0.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D NoiseMinMax = FVector2D(-1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TerraceHeight = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool InvertNoise = false;

};

USTRUCT(BlueprintType) struct FFN_LayeredNoise
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FFN_NoiseLayerType> NoiseLayers;

	UPROPERTY(BlueprintReadOnly)
	TArray<UFastNoiseWrapper*> NoiseWrappers;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 NoiseLayerSeed = -1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float NoiseLayerScaleOffset = 1.0f;
};

UCLASS()
class FASTNOISELAYERINGPLUGIN_API UFastNoiseLayeringFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure, Category = "GSFNG Statics")
	static float BlendNoises(FVector Position, FVector CenterPosition, UPARAM(ref) TArray<UFastNoiseWrapper*>& NoiseWrappers, UPARAM(ref) TArray<FFN_NoiseLayerType>& NoiseLayers);

	UFUNCTION(BlueprintPure, Category = "GSFNG Statics")
	static float BlendNoises3D(FVector Position, UPARAM(ref) TArray<UFastNoiseWrapper*>& NoiseWrappers, UPARAM(ref) TArray<FFN_NoiseLayerType>& NoiseLayers);
	
	UFUNCTION(BlueprintCallable, Category = "GSFNG Statics", meta = (HidePin = "Outer", DefaultToSelf = "Outer"))
	static void InitNoiseWrappers(UObject* Outer, UPARAM(ref) TArray<UFastNoiseWrapper*>& NoiseWrappers, TArray<FFN_NoiseLayerType> NoiseLayers, int32 OverrideSeed = -1, float NoiseScaleOffset = 1.0f);

	
};
