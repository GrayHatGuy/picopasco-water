# picopasco-water

automatically water plants based upon moisture sensor feedback

## requirements

see [picopasco-main](https://github.com/GrayHatGuy/picopasco#parts) for hardware links (sensor, relay, pump, MCU).

## how to:

* wiring 

![image](https://github.com/GrayHatGuy/picopasco-water/blob/93da9541c35fa700cd6ab06cf1b844db552e3922/picopasco-water-wiring.png)

* update inputs

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

 ![image](https://github.com/GrayHatGuy/picopasco-water/blob/6387f54660eea0ac7d279fe3ec2b2359eec4048d/picopasco-water-controls.png)

### demos 
  - **TIMER [ctlmode] = 1** - setup: [_demo_]() [_terminal ouptput_]() 
     
  - **AUTO [ctlmode] = -1** - setup: [_demo_]() [_terminal ouptput_]() 
      
  - **OFF [ctlmode] = 0** - See scan output above.

     
