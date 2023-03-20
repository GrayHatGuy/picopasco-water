# picopasco-water

automatically water plants based upon moisture sensor feedback

![image](https://github.com/GrayHatGuy/picopasco-water/blob/f9d186949b299253bf801533ec1c9ac6cd0e35dd/picts/IMG_6668.JPG)

## requirements

see wiring and firmware details below.

### parts: 
  #### minimum _(by firmware design)_
   *  $6.00  [rp2040 pico  - (pico w optional)](https://www.raspberrypi.com/products/raspberry-pi-pico/)
   *  $3.70  [relays 5 volt spst](https://www.amazon.com/gp/product/B00LW15A4W)
   *  $10.76 [5 volt pump](https://www.amazon.com/gp/product/B07T6GDNT3/)
      -alternate pump $3.25 [low cost ](https://www.amazon.com/Gikfun-2-5V-6V-Submersible-Silicone-EK1374/dp/B0957BS936/)
      
  #### $12.95 - $20.46 Total cost of materials
## how to:

* wiring 

![image](https://github.com/GrayHatGuy/picopasco-water/blob/a465415fa1193063989dae65d3e3b20d807e2f4e/picopasco-water-wiring.png)

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

![image](https://github.com/GrayHatGuy/picopasco-water/blob/97006d53bb0eb49c545befab1ab0ec83e83e623e/picopasco-water-controls.png)

### demos 
  - **TIMER [ctlmode] = 1** 
    * [_firmware output_](https://youtube.com/shorts/7hno1aNq0y4?feature=share) 

     
  - **AUTO [ctlmode] = -1**
    * [_firmware output_](https://youtu.be/WC2HDOqH6xY) 
      
  - **OFF [ctlmode] = 0** 
    * see scan examples above.

## [_operational demo_](https://youtu.be/xHYEaHfb-Q8)

     
