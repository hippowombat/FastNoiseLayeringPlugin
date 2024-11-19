


#include "FastNoiseLayeringFunctions.h"
#include "Math/UnrealMathUtility.h"

float UFastNoiseLayeringFunctions::BlendNoises(FVector Position, TArray<UFastNoiseWrapper*>& NoiseWrappers,
	TArray<FFN_NoiseLayerType>& NoiseLayers)
{
	float NoiseBlendOutput = 0.0f;
	int32 i = -1;

	for (const UFastNoiseWrapper* NoiseWrapper : NoiseWrappers)
	{
		i++;
		
		// Get -1 : 1 normalized noise value at XY position for each layer
		float Noise2D = NoiseWrapper->GetNoise2D(Position.X, Position.Y);
		
		// Constant Bias Scale Noise
		Noise2D = Noise2D + NoiseLayers[i].NoiseBiasScale.X;
		Noise2D = Noise2D * NoiseLayers[i].NoiseBiasScale.Y;
		
		// Clamp Noise
		Noise2D = FMath::Clamp(Noise2D, NoiseLayers[i].NoiseMinMax.X, NoiseLayers[i].NoiseMinMax.Y);
		
		// Optionally invert noise values
		if (NoiseLayers[i].InvertNoise)
		{
			Noise2D = Noise2D * -1;
		}
		
		// Get noise strength for noise layer
		const float NoiseStrength = NoiseLayers[i].NoiseStrength;
		
		// Get noise blend mathematical function
		const EFN_BlendType BlendFunction = NoiseLayers[i].NoiseBlendFunction;
		
		// Get noise layer value from mult of Noise2D value & noise layer strength value
		float CurrentNoiseLayerValue = Noise2D * NoiseStrength;
		
		// Apply terracing per layer
		CurrentNoiseLayerValue = FMath::GridSnap(CurrentNoiseLayerValue, NoiseLayers[i].TerraceHeight);
		
		// Mathematically mix/blend noise layers in order based on Blend Function
		switch (BlendFunction)
		{
		case Add:
			NoiseBlendOutput = NoiseBlendOutput + CurrentNoiseLayerValue;
			break;

		case Subtract:
			NoiseBlendOutput = NoiseBlendOutput - CurrentNoiseLayerValue;
			break;

		case Multiply:
			NoiseBlendOutput = NoiseBlendOutput * CurrentNoiseLayerValue;
			break;

		case Divide:
			NoiseBlendOutput = NoiseBlendOutput / CurrentNoiseLayerValue;
			break;
		}
	}
	return NoiseBlendOutput;
}

float UFastNoiseLayeringFunctions::BlendNoises3D(FVector Position, TArray<UFastNoiseWrapper*>& NoiseWrappers,
	TArray<FFN_NoiseLayerType>& NoiseLayers)
{
	float NoiseBlendOutput = 0.0f;
	int32 i = -1;

	for (const UFastNoiseWrapper* NoiseWrapper : NoiseWrappers)
	{
		i++;
		
		// Get -1 : 1 normalized noise value at XY position for each layer
		float Noise3D = NoiseWrapper->GetNoise3D(Position.X, Position.Y, Position.Z);
		
		// Constant Bias Scale Noise
		Noise3D = Noise3D + NoiseLayers[i].NoiseBiasScale.X;
		Noise3D = Noise3D * NoiseLayers[i].NoiseBiasScale.Y;
		
		// Clamp Noise
		Noise3D = FMath::Clamp(Noise3D, NoiseLayers[i].NoiseMinMax.X, NoiseLayers[i].NoiseMinMax.Y);
		
		// Optionally invert noise values
		if (NoiseLayers[i].InvertNoise)
		{
			Noise3D = Noise3D * -1;
		}
		
		// Get noise strength for noise layer
		const float NoiseStrength = NoiseLayers[i].NoiseStrength;
		
		// Get noise blend mathematical function
		const EFN_BlendType BlendFunction = NoiseLayers[i].NoiseBlendFunction;
		
		// Get noise layer value from mult of Noise2D value & noise layer strength value
		float CurrentNoiseLayerValue = Noise3D * NoiseStrength;
		
		// Apply terracing per layer
		CurrentNoiseLayerValue = FMath::GridSnap(CurrentNoiseLayerValue, NoiseLayers[i].TerraceHeight);
		
		// Mathematically mix/blend noise layers in order based on Blend Function
		switch (BlendFunction)
		{
		case Add:
			NoiseBlendOutput = NoiseBlendOutput + CurrentNoiseLayerValue;
			break;

		case Subtract:
			NoiseBlendOutput = NoiseBlendOutput - CurrentNoiseLayerValue;
			break;

		case Multiply:
			NoiseBlendOutput = NoiseBlendOutput * CurrentNoiseLayerValue;
			break;

		case Divide:
			NoiseBlendOutput = NoiseBlendOutput / CurrentNoiseLayerValue;
			break;
		}
	}
	return NoiseBlendOutput;
}

void UFastNoiseLayeringFunctions::InitNoiseWrappers(UObject* Outer, TArray<UFastNoiseWrapper*>& NoiseWrappers, TArray<FFN_NoiseLayerType> NoiseLayers, int32 OverrideSeed, float NoiseScaleOffset)
{
	for (const FFN_NoiseLayerType NoiseLayer : NoiseLayers)
	{
		// Construct a new FastNoiseWrapper object
		UFastNoiseWrapper* FNW = NewObject<UFastNoiseWrapper>(Outer, UFastNoiseWrapper::StaticClass());
		int32 TSeed = NoiseLayer.Seed;
		if (OverrideSeed != -1)
		{
			TSeed = OverrideSeed;
		}
		// Run setup on FastNoiseWrapper, applying FNoiseLayer struct values to the Wrapper object
		FNW->SetupFastNoise
		(
			NoiseLayer.NoiseType,							//NoiseType
			TSeed,											//Seed
			NoiseLayer.Frequency / NoiseScaleOffset,		//Frequency
			NoiseLayer.InterpType,							//InterpType
			NoiseLayer.FractalType,							//FractalType
			NoiseLayer.Octaves,								//Octaves
			NoiseLayer.Lacunarity,							//Lacunarity
			NoiseLayer.Gain,								//Gain
			NoiseLayer.CellularJitter,						//CellularJitter
			NoiseLayer.CellularDistanceFunction,			//CellularDistanceFunction
			NoiseLayer.CellularReturnType					//CellularReturnType
		);
		// Add the constructed, setup Noise
		NoiseWrappers.Add(FNW);
	}
}




