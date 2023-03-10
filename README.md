# picopasco-water
automatically water plants based on moisture sensor feedback
## requirements
see [picopasco-main](https://github.com/GrayHatGuy/picopasco#parts) for hardware (sensor, relay, pump, MCU) and wiring diagrams.
## how to:
* update inputs
  - **[soilUL] [soilLL]** upper and lower moisture sensor limits 
  - **[ctlmode]** fully AUTO closed loop = -1; TIMER open loop = 1 [default]; off = 0
  - **[doseSP]** target dispense dosage per pump trigger
  - **[waterIntSP]** open loop trigger period for dispense check 
* tuning
  - Set **[ctlmode] = 0** this will turn off hydration  
  - Monitor the current min and max measurents obtained by the sensors
  - Update **[soilUL] [soilLL]** limits outside of the measurement variation 
## demos:
  - **TIMER** mode **[ctlmode] = 1**
    -timing diagram
    -vid
  - **AUTO** mode **[ctlmode] = -1**
    -timing diagram
    -vid
  - **OFF** mode **[ctlmode] = 0**
    -timing diagram
    -vid
