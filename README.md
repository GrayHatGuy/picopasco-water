# picopasco-water
automatically water plants based upon moisture sensor feedback
## requirements
see [picopasco-main](https://github.com/GrayHatGuy/picopasco#parts) for hardware (sensor, relay, pump, MCU) and wiring diagrams.
## how to:
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
  - **TIMER [ctlmode] = 1** - [_demo_]()
      * **control:** open loop no target correction
      * **timing:** _start -> sensor scan for [waterIntSP] ms -> irrigate for [doseSP] ms -> soak delay for [df] = 2 * [doseSP] ms -> repeat_
  - **AUTO [ctlmode] = -1** - [_demo_]()
      * **control:** closed loop continual correction to center of **[soilUL] [soilLL]**
      * **timing:** _start -> sensor scan for [waterIntSP] ms -> if sensor is out of target range -> repeat irigation with [doseSP] then dwell for [df] util target is reached_
  - **OFF [ctlmode] = 0** - [_demo_]()
      * **control:** none hydration off
      * **timing:** _start -> sensor scan_
