# picopasco-water
closed and open loop irrigation control using relays to activate pumps based upon moisture sensor feedback and user input control limits..
## Requirements
see [picopasco](https://github.com/GrayHatGuy/picopasco#parts) for wiring diagram and hardware (relays, pumps, MCU)
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
  - **AUTO** mode **[ctlmode] = -1**
  - **OFF** mode **[ctlmode] = 0**
  
