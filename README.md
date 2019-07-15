# Bitcraze Crazyflie 2.0 Firmware  

This repository contains the source code for the [Bitcraze Crazyflie 2.0](https://www.bitcraze.io/crazyflie-2/) firmware utilizing [ARM Mbed OS](https://www.mbed.com/en/platform/mbed-os/).

## Programming

Below are step by step instructions to program the [Bitcraze Crazyflie 2.0](https://www.bitcraze.io/crazyflie-2/).

### A) Fork

The first step is to fork this repository, which means to create a copy of this repository in your own GitHub account:

1. Click on ```Fork```

### B) Import

After you have forked the repository, you should import it to [Mbed Studio](https://os.mbed.com/studio/), an IDE designed specific for Mbed OS (Windows/Mac):

1. Install and open [Mbed Studio](https://os.mbed.com/studio/)
2. Click on ```File```>```Import Program...```
3. Paste ```https://github.com/user_name/crazyflie-firmware/``` under ```URL``` and then click ```Add Program```

### C) Target

Next step is to set the target you'll be utilizing, that's it, the microcontroller you will be developing for. The microcontroller from [Bitcraze Crazyflie 2.0](https://www.bitcraze.io/crazyflie-2/) ([STM32F405RG](https://www.st.com/en/microcontrollers-microprocessors/stm32f405rg.html)) is not available for [ARM Mbed OS](https://www.mbed.com/en/platform/mbed-os/). However, the microcontroller from [Seeed Arch Max](https://os.mbed.com/platforms/Seeed-Arch-Max/) development board ([STM32F407VE](https://www.st.com/en/microcontrollers-microprocessors/stm32f407ve.html)) is very similar and can be utilized with little adjustments:

1. Click on ```Target``` and choose ```Seeed Arch Max (ARCH-MAX)```
2. Navigate to file ```mbed-os``` > ```targets``` > ```TARGET_STM``` > ```TARGET_STM32F4``` > ```TARGET_STM32F407xG``` > ```device``` > ```TOOLCHAIN_ARM_STD``` > ```STM32F407xx.sct``` and modify the code of line 9:

```  #define MBED_APP_START 0x08004000```

3. Navigate to file ```mbed-os``` > ```targets``` > ```TARGET_STM``` > ```TARGET_STM32F4``` > ```TARGET_STM32F407xG``` > ```TARGET_ARCH_MAX``` > ```PeripheralPins.c``` and add a line of code between lines 135 and 136: 

```{PB_11, PWM_2, STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 4, 0)},  // TIM2_CH4```

### D) Build

Now you're ready to build your program, in other words, to create an binary file from your source code:

1. Click on ```Build program```


### E) Flash

Last step is to send this binary file to your microcontroller, which is called flash. This can be done wirellesly with the [Bitcraze Crazyradio PA](https://www.bitcraze.io/crazyradio-pa/), an USB radio dongle, and the [crazyflie-clients-python](https://github.com/bitcraze/crazyflie-clients-python), an PC client:

1. Install [crazyflie-clients-python](https://github.com/bitcraze/crazyflie-clients-python)
2. Plug in the [Bitcraze Crazyradio PA](https://www.bitcraze.io/crazyradio-pa/)
3. Put the [Bitcraze Crazyflie 2.0](https://www.bitcraze.io/crazyflie-2/) in program mode
- Turn off the drone
- Hold down the push button for about 1 second until you the blue led starts blinking
- Release the push button button
4. Open console (```CRTL```+``` ` ```)
5. Change directory to where the project is located (type ```cd crazyflie-firmware``` in the console) 
6. Send the binary file to the drone (type ```make flash``` in the console)

## Source code

The source code is organized as follows:

```
./                                | Root
 main.cpp                         | Main program
 + programs                       | Program files
 |  + examples                    | Examples
 |  + labs                        | Labs
 + src                            | Source files
 |  + drivers                     | Sensor drivers
 |  + modules                     | Controller modules
 |  + utils                       | Utility files
 + mbed-os                        | ARM Mbed OS library (automatically imported)
 + USBDevice                      | USB Device library (automatically imported)
```
