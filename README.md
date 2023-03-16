# picopasco-water

automatically water plants based upon moisture sensor feedback

![image](https://github.com/GrayHatGuy/picopasco-water/blob/6bf44768abad50d30a800cb3156aeb3c3cee7acf/picopasco-water-layout2.jpeg)

## requirements

see [picopasco-main](https://github.com/GrayHatGuy/picopasco#parts) for hardware (sensor, relay, pump, MCU) with wiring and firmware details below.

## how to:

* wiring 

![image]((https://github.com/GrayHatGuy/picopasco-water/blob/a465415fa1193063989dae65d3e3b20d807e2f4e/picopasco-water-wiring.png)

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

![image](https://github.com/GrayHatGuy/picopasco-water/blob/a465415fa1193063989dae65d3e3b20d807e2f4e/picopasco-water-wiring.png)

### demos 
  - **TIMER [ctlmode] = 1** 
    * [_firmware output_](https://youtube.com/shorts/7hno1aNq0y4?feature=share) 

     
  - **AUTO [ctlmode] = -1**
    * [_firmware output_](https://youtu.be/WC2HDOqH6xY) 
      
  - **OFF [ctlmode] = 0** 
    * see scan examples above.

  [_operational demo_](https://youtu.be/i5UP44l4Cr4)

     
