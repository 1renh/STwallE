Team STWALL-E's Submission to Hackkosice 2023 BSH Challenge

STM32G0B1RET6 Nucleo-64 MCU with X-Nucleo-LED 12A1

Implemented 2 patterns of LED on the expansion board

1. Color Transition of the Whole Matrix of LEDs (Left 4x4)
 - 36 smooth color transitions with 5 seconds between transition.
2. Color Transition of Every Single Row of LEDs (Left 4x4)
 - b, s, h falling down in different colors

Existing implementation is based on NUCLEO-F401RE, NUCLEO-L073RZ, NUCLEO-L476RG.

To implement on other MCUs, create new project in STMCubeIDE. Follow the settings on existing iocs (specifically LED12A1.ioc) to initialize the main files.
Now inserting the sample codes from the examples in the Projects/Src/main.c will work. 
Relevant package: STM32CubeExpansion_LED12A1

To set individual LEDs
Each row is dev (variable name in sample code) with indexing from 0-3. To access each column in the row (channels in sample code), 0-3 are the indexes for the left-most LED with 0 corresponding to r, 1 corresponding g, 2 corresponding to b. 3-5 are the indexes for the 2nd LED from the left, 6-8 are 3rd and 9-11 are the last. 
Colors are changed using the Analogue dimming function.




