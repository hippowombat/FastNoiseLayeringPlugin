Requirements:

Rockam's FastNoiseWrapper plugin, available here https://github.com/Rockam/FastNoise-UE4-Wrapper

A simple function library for mathematically blending layers of noise generated from Rockam's UE4 implementation of Auburn's Fast Noise library.

Before blending noises, call the Init Noise Wrappers function. The Noise Wrappers input pin (array of FastNoiseWrapper objects) should be a function-local variable, while Noise Layers can/should be an Actor/Class variable that you can edit via the Details panel.

Once the noise has been initialized, you can simply supply the noise wrappers & your noise layer array (array of NoiseLayerType structs) along with a location to get a mathematically blended noise value from your list of noise layers.

![NoiseFunctions](https://github.com/user-attachments/assets/802e81e1-f275-4241-b6e2-3e0e68fec7c9)

Blend Noises functions step through Noise Layers array in order, performing the Noise Blend Function (mathematical operation) of the current layer against the accumulated value of previous layers. 

For example, a Noise Layers array with entry 1 set to Subtract will subtract the noise value at the supplied position from the noise value at the supplied position from entry 0.

![NoiseLayering](https://github.com/user-attachments/assets/06de3310-5144-48d1-ab4f-ea5d03ab7876)

The same functions/FFN_NoiseLayerType struct type can be exposed to C++ by including FastNoiseLayeringFunctions.h in your class's header file.

![image](https://github.com/user-attachments/assets/f21bf13e-0ee7-4e56-8615-4b1d426d75d6)

![image](https://github.com/user-attachments/assets/8b4522dc-2a24-4c06-8bdd-50ec9d36fb72)

![image](https://github.com/user-attachments/assets/eb887907-93ed-4a2e-a72a-b75b0d29a9be)

![image](https://github.com/user-attachments/assets/1557d398-7e29-4be1-a2b1-cf1de91a6543)
