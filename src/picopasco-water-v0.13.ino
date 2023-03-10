//................................................................................
//...',,;;........................;;....:,........''.......',,;;..................
//..;c'..'.......................'do...'o;.......'oo'.....;c'..,..'...............
//..l:..':;'ll;:c:::c;..'....'....lo'..,o, '::l,.;xo'.....o:..,c,,oc..:'.''.......
//..ol...:,.ld'.'.',lo''ol..c;....cd,..:l. .',dl.'xl......ol...c,'dc.:d;.:o,.;c...
//..,lc;:;..cd'..,:;ld,.,lcc:.....;d:.'lc..,;;xo.'xl''....;lc;:;.'oo;,lc..:l:c,...
//....',....co;..';':o:..,do......,l;..l:..',,lo,.coc:......',....',..,,...lx:....
//...................,:,.'l;...........,'......'...''...................,..cc.....
//...................,c:;:,............................................:c;;;......
//....................','...............................................''........
//................................................................................
//..........................................'''''''''',''''''''...................
//.........................''''',,,,,,,,'',,,,,,,,,,,,,,,,,;;;:;..................
//................''',,,,,,,;;,,,,,,,,,''''',,,,,,,;;;;;::::cc:;..................
//............',,,,,,,,,,,,,,,,,,,,,,,,;;;;;;;::::::cccccccccc:;..................
//...........,:::::::;;;;;;;;:::::::ccccccccccc::;:ccccccccccc:;..................
//...........,:ccccclllccccccllllccccc:::,';;''...':cccccccccc:;..................
//...........':cclllllllllllc:;;;'','...,...'''....;ccccccccccc;..................
//............,cccllllllllllc,'....'...,'.'..''''..;ccccccccccc;..................
//...........':cclllllllllll;'..'....,'.....'.';,.,ccccccccccc:'.................
// ............;cclllllllllll:'.',;'''....','..';;'':lccccccccc:'.................
// ............,ccllllllllllll;.',.''''...',,......':lcllcccccc:,.................
//  ...........':clllllllllllll,..''..,..''';;.....,;clllccccccc;.................
//.    ......:clllllllllllol,...;,.'....,,..,' ..':lclccccccc:'................
//         .....;clllllllllllll;...'.',',,..''...  .,:ccclccccccc;..... ..........
//        ......,cclllllllllllo:''....,,;;',,...'.,,,;clcccllcclodolc:,'..........
//        ......':cllllllllllloc''..'..,:::;,,,;:ccccccccclllloddxkkxkkkxoc;......
//       .....';cclllllllllllll:;::::ccclllllllllllllcccllloddddxxdllllodxxdc'...
//        ..,cxOxllllllllllllllllllllllllllllllllllllllllooddoddxxkdcccccllodd:...
//      ..:x0XXKOxdoollllllllllllllllooooollooooooooooddddddddddddxdlclclllll;....
//    ..cOKXK0kxkOOxxddddddddddddddddddddddddddddxdxxxxkkxxddddoooollllcc:,.......
//   .,xKK0OxddodOOkkkxxkxxxxxxxxxxxdddoooddooodxxxxkkkxxdooollllllcc:,....  .....
//  .,xK0kdoollldOOkkxxxkxxxxxxxxxxxxdddddddddxxxxxdddolllllllcc:;,'....   .......
//  .lkkdolllllloxOkkkxkkxdxxxxxxxxxxxxxxxddddooolllllllllcc:;,'........   .......
//  'ldolccccccllodddxxxxdddddddddddddddooooollllllllc:;;,'.............    ......
//...:olcc:::::cccccclllllooooooddooooooooooolcc:;,,'...................     .....
//...':lollccccccccccccllllooooodddoolcc:;;,,'..........................         .
//  ...,:llooooooooooddddddddoollc:;,...................................          
//   ...',;:codxolcdxxdooolcc::;;,''.....................................         
//   ...',,;cldxdlcoxxdoooooooll:;;,'....................................         
//   ...,,;:::ccllooooloooxkxodxdc:;,'...................................         
//  .......'',;;;::cccclloddodddlc:;,'..................................         
//     ........'',,;;;;:;;::::c:::;;,,'..................................         
//     .............''''',,,,,,,,,'''....................................         
//    ..................................................................          
//   ...................................................................          
//  
//  picopasco-water: moisture-irrigation-control closed/open loop
//
//  Firmware controls irrigation pumps using relays triggered from moisture scan. 
//  Irrigation control via manual time based or automatic PID closed loop control mechanism.
//
//   > User inputs:
//    -[soilUL] [soilLL] upper and lower moisture sensor limits 
//    -[ctlmode] fully AUTO closed loop = -1; TIMER open loop = 1 [default]; off = 0;
//    -[doseSP] target dispense dosage per pump trigger
//    -[waterIntSP] open loop trigger period for dispense check 
//
//   < Outputs:
//    - Automated closed loop control of irrigation pumps using a moisture sensor for feedback      
// 
// additional libraries required for a successfull build: https://github.com/Seeed-Studio/SGP30_Gas_Sensor https://www.arduinolibraries.info/libraries/sensirion-i2-c-sht4x  
//  #include "pins_arduino.h" 
//  mailto://GrayHatGuy@GrayHatGuy.com 


#include <Arduino.h>
#include "pins_arduino.h" //custom header for seeed grove pico breakout
#include <SoftwareSerial.h>

#define moisturePin A2                             //moisture sensor pin

int ctl = 16;              //relay GPIO control trigger pins
int trigger = LOW;                     //init state of relay
const int waterIntSP = 5000;                    //auto water interval [ms]
int doseSP = 1000;        //min dose water time for pump on [ms] *disable unused pump with 0
int df =  2 * doseSP ; // dwell (soak) time ms after dispense before reading
int t_loop = 100;                            //while wait interval for loop()
int last_loop = millis();      //last loop time
int waterprint = 13;                         //number of status lines to print during water dwell
int hydrateTotal;                      //cumulative pump time since boot         
int ctlmode = -1;                    //fully automatic closed loop = -1; time trigger open loop = 1 [default]; off = 0;
int soilUL = 1200;                   //upper limit for soil moisture 4-923
int soilLL = 200;                   //lower limit for soil moisture 4-923
int moisturePV;
int lastPV;
int ledPin = LED_BUILTIN;                    //led pin
int ledState = LOW;                      //init state of led
unsigned long previousMillis = millis(); //led do while last time stamp
float waterStart = waterIntSP + millis(); //start time for next auto water
int hydrocnt = 1;  //hydrates since boot
int olTrigger = 0;
int closeloopcnt = 0;


void setup() { 
  Serial.begin(115200);  
  pinMode(ctl, OUTPUT);  
  digitalWrite(ctl, LOW);  
} 

void loop() { 
  while ((millis() -last_loop) > t_loop) {
    scan(); blink(-1); 
    if (millis() > waterStart) {
        olTrigger = 1;
    }
    if ((ctlmode == 1) and (olTrigger ==1)){  //open loop timer
      if (moisturePV <= soilLL) {     
        lastPV = moisturePV; hydrate(ctlmode); delay(df); waterStart = waterIntSP + millis(); olTrigger = 0; scan(); Serial.println("INFO|Timer dispense complete|PV(now)|"+String(moisturePV)+"|PV(before)|"+String(lastPV));
      }
      if ((moisturePV > soilLL) or (moisturePV > soilUL)){
        waterStart = waterIntSP + millis(); olTrigger = 0; Serial.println(String("INFO|Moisture within limits|PV|"+moisturePV));
      }
    }
    if ((ctlmode == -1) and (moisturePV < 0.5*(soilLL+soilUL))) { //closed loop auto //SP targets centerline of ul and ll
      closeloopcnt = 0; lastPV = moisturePV;
      while ((moisturePV < (0.5*(soilLL+soilUL)))) {       
        hydrate(ctlmode); delay(df); blink(-1); closeloopcnt = closeloopcnt +1; scan();        
        Serial.println("|ClosedLoopCount|"+String(closeloopcnt)+"|PV(now)|"+String(moisturePV)+"|PV(before)|"+String(lastPV));       
      }
    }
    last_loop = millis();
  }
}

void blink(long led_int) { 
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  unsigned long currentMillis = millis(); 
  if ((currentMillis - previousMillis >= led_int) and (led_int > 0) ) {   //led_int input in ms -1 toggle rn
    previousMillis = currentMillis; 
    if (ledState == LOW) { 
      ledState = HIGH; 
      } else { 
        ledState = LOW; 
      } 
      digitalWrite(ledPin, ledState); 
    } 
  if (led_int == -1){             //bypass time interval with -1 toggle rn
    if (ledState == LOW) { 
      ledState = HIGH; 
    } else { 
      ledState = LOW; } ; 
    digitalWrite(ledPin, ledState);
  }
}

void scan() { 
  String printStr = ""; 
  moisturePV = analogRead(moisturePin); 
  String pctlmode =String("N/A");
  switch (ctlmode) {
    case -1:
      pctlmode = "AUTO";
      break;
    case  1:
      pctlmode = "TIMER";
      printStr = printStr + (waterStart-millis());
      break;
    case  0:
      pctlmode = "OFF";
      break;
  }
  Serial.println(String(millis()) + "> |PV-" + moisturePV + "|UL-"+ soilUL+ "|LL-"+soilLL+"|" + pctlmode + "|" + printStr);
} 
  
void hydrate(int mode){ //int mode = {0 - 0ff; -1 - Auto (ctlmode = -1); 1 - Timer (ctlmode = 1);}
  int pumpon;
  int cnt;
  switch (mode) {
    case -1:
    cnt = 0;
      pumpon = millis() + doseSP;            //capture pump end time
      digitalWrite(ctl, HIGH);                   //trigger relay high
      Serial.println (String(millis())+"> hydration: ON! for "+doseSP+" at "+millis()+" ms ends at "+pumpon+ " ms");
      while (pumpon >= millis()) {                  //while pumping print countdown to end at fixed interval
        blink(-1);                                  //blink toggle on demand (-1) else (n>=0 is blink interva)
        Serial.println(String(millis())+"> hydration: "+(pumpon - millis())+" ms of watering time remaining " + (waterprint-cnt) + "/" + waterprint ); cnt = cnt +1;
        delay(doseSP/waterprint);                  //report status of the remaining pump time setting print interval at 1/19 of the dwell time.
      } 
      digitalWrite(ctl, LOW);
      hydrateTotal = hydrateTotal + doseSP;
      waterStart =  waterIntSP + millis(); 
      Serial.println(String (millis())+"> hydration: done! - " + millis() +" ms ");
      Serial.println("|TotalCount|"+String(hydrocnt)); 
      Serial.println("|TotalTime|" + String(hydrateTotal)+" ms since boot");
      Serial.println("|NextTrigger|" + String(waterStart)+" ms"); 
      hydrocnt = hydrocnt +1;
      break;
    case 1:
      cnt = 0;
      pumpon = millis() + doseSP;            //capture pump end time
      digitalWrite(ctl, HIGH);                   //trigger relay high
      Serial.println (String(millis())+"> hydration: ON! for "+doseSP+" at "+millis()+" ms ends at "+pumpon+ " ms");

      while (pumpon >= millis()) {                  //while pumping print countdown to end at fixed interval
        blink(-1);                                  //blink toggle on demand (-1) else (n>=0 is blink interva)
        Serial.println(String(millis())+"> hydration: "+(pumpon - millis())+" ms of watering time remaining " + (waterprint-cnt) + "/" + waterprint ); cnt = cnt +1;
        delay(doseSP/waterprint);                  //report status of the remaining pump time setting print interval at 1/19 of the dwell time.
      } 
      digitalWrite(ctl, LOW);
      hydrateTotal = hydrateTotal + doseSP;
      waterStart =  waterIntSP + millis(); 
      Serial.println(String (millis())+"> |hydration complete and moisture within limits| " + millis() +" ms ");
      Serial.println("|TotalHydrations|"+String(hydrocnt)); 
      Serial.println("|TotalHydrationTime|" + String(hydrateTotal) +" ms since boot");
      Serial.println("|AutoCorrections|" + String(closeloopcnt)+" ms"); 
      break;
    case 0:
      Serial.println("Hydration DISABLED!");
      break;
    default:
      Serial.println("Invalid input: use form hydrate(int mode) where mode is {0 - 0ff, -1 - Auto (ctlmode = 1), 1 - Timer (ctlmode = 1)}");
      break;
  }

}
