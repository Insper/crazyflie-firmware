# Bitcraze Crazyflie 2.0 Firmware  

This repository contains the source code for the [Bitcraze Crazyflie 2.0](https://www.bitcraze.io/crazyflie-2/) firmware utilizing [ARM Mbed OS](https://www.mbed.com/en/platform/mbed-os/).


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

## Fork

The first step is to fork this repository, which means to create a copy of this repository in your own account:

1. Click on ```Fork```

## Import

After you have forked the repository, you should import it to [Mbed Studio](https://os.mbed.com/studio/) (program):

1. Install and open [Mbed Studio](https://os.mbed.com/studio/)
2. Click on ```File```>```Import Program...```
3. Paste ```https://github.com/user_name/crazyflie-firmware/``` under ```URL``` and then click ```Add Program```

## Target

The microcontroller from [Bitcraze Crazyflie 2.0](https://www.bitcraze.io/crazyflie-2/) ([STM32F405RG](https://www.st.com/en/microcontrollers-microprocessors/stm32f405rg.html)) is not available for [ARM Mbed OS](https://www.mbed.com/en/platform/mbed-os/). However, the microcontroller from [Seeed Arch Max](https://os.mbed.com/platforms/Seeed-Arch-Max/) development board ([STM32F407VE](https://www.st.com/en/microcontrollers-microprocessors/stm32f407ve.html)) is very similar and can be utilized with little adjustments:

1. Click on ```Target``` and choose ```Seeed Arch Max (ARCH-MAX)```
2. Navigate to file ```mbed-os``` > ```targets``` > ```TARGET_STM``` > ```TARGET_STM32F4``` > ```TARGET_STM32F407xG``` > ```device``` > ```TOOLCHAIN_ARM_STD``` > ```STM32F407xx.sct``` and modify the code of line 9:

```  #define MBED_APP_START 0x08004000```

3. Navigate to file ```mbed-os``` > ```targets``` > ```TARGET_STM``` > ```TARGET_STM32F4``` > ```TARGET_STM32F446xE``` > ```TARGET_ARCH_MAX``` > ```PeripheralPins.c``` and add a line of code between lines 135 and 136: 

```{PB_11, PWM_2, STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 4, 0)},  // TIM2_CH4```

## Build

To build the program is very simple:

1. Click on ```Build program```


## Flash

To flash the firmware wirellesly you will need an [Bitcraze Crazyradio PA](https://www.bitcraze.io/crazyradio-pa/) (hardware) and the [crazyflie-clients-python](https://github.com/bitcraze/crazyflie-clients-python) (software):

1. Install [crazyflie-clients-python](https://github.com/bitcraze/crazyflie-clients-python)
2. Plug in the [Bitcraze Crazyradio PA](https://www.bitcraze.io/crazyradio-pa/)
3. Put the [Bitcraze Crazyflie 2.0](https://www.bitcraze.io/crazyflie-2/) in program mode
- Turn off
- Hold down the push button (on/off) for about 1 second until you the blue led starts blinking
- Release the push button button
4. Open console (```CRTL```+``` ` ```), change directory to where the project is located (```cd crazyflie-firmware```) and type ```make flash```
