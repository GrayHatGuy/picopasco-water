# picopasco-water

automatically water plants based upon moisture sensor feedback

## requirements

see [picopasco-main](https://github.com/GrayHatGuy/picopasco#parts) for hardware (sensor, relay, pump, MCU) with wiring and firmware details below.

## how to:

* wiring 

![image](https://github.com/GrayHatGuy/picopasco-water/blob/93da9541c35fa700cd6ab06cf1b844db552e3922/picopasco-water-wiring.png)

* firmware inputs

  - **[soilUL] [soilLL]** - upper and lower moisture sensor limits 
  - **[ctlmode]** - fully AUTO closed loop = -1; TIMER open loop = 1 [default]; OFF = 0
  - **[doseSP]** - target dispense dosage per pump trigger
  - **[waterIntSP]** - open loop trigger period for dispense check 
  
* tuning

  - Set **[ctlmode] = 0** this will turn off hydration  
  - Monitor the current min and max measurents obtained by the sensors
  - Update **[soilUL] [soilLL]** limits outside of the measurement variation 
  
## details/demos:

### controls

 ![image]([https://github.com/GrayHatGuy/picopasco-water/blob/c13cb4fbaa6a2ea24d01a6d176c772c543ddec8f/picopasco-water-controls.png](https://github.com/GrayHatGuy/picopasco-water/blob/47aa70fdd3693d7fd8305aa7a06bb26d520f305f/picopasco-water-wiring.png))

### demos 
  - **TIMER [ctlmode] = 1** 
    * [_firmware output_](https://youtube.com/shorts/7hno1aNq0y4?feature=share) 
     
  - **AUTO [ctlmode] = -1**
    * [_firmware output_](https://youtu.be/WC2HDOqH6xY) 
      
  - **OFF [ctlmode] = 0** 
    * see scan examples above.

     
