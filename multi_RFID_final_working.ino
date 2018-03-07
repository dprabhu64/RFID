/*******************************************
 * function:get the id of RFID key
 * RFID	                  SunFounder Uno
 * VCC	                      3.3V  
 * RST	                      6
 * GND	                      GND
 * MISO	                      7
 * MOSI	                      5
 * SCK	                      4
 * NSS	                      3
 * IRQ	                      2
 ****************************************/

#include"rfid1.h"
RFID1 rfid;//create a variable type of RFID1

uchar serNum[5];  // array to store your ID
int i=0,relay=13;
void setup()
{
  Serial.begin(9600); 
  Serial.println("Checking for card");
   pinMode(relay, OUTPUT);
  //initialize the serial
//  rfid.begin(2,4,5,7,3,6);  ////rfid.begin(2 IRQ_PIN,4 SCK_PIN,5 MOSI_PIN, 7 MISO_PIN,3 Nss,6 rst)
//                                           7 IRQ_PIN,  5 SCK_PIN,4 MOSI_PIN, MISO_PIN,3 NSS_PIN,2 RST_PIN) 
//  delay(100);//delay 1sSS_PIN,6 RST_PIN
//  rfid.init(); //initialize the RFID
}
void loop()
{
  static int count=0; 
  int card=0;
   //Serial.println("Checking for card");
  
  card=checkRFID(i);
   
  uchar status;
  uchar str[MAX_LEN];
  // Search card, return card types
  status = rfid.request(PICC_REQIDL, str);
  if (status != MI_OK)
  {
    //Serial.println(status);
    return;
  }
  // Show card type
  //rfid.showCardType(str);
  //Prevent conflict, return the 4 bytes Serial number of the card
  status = rfid.anticoll(str);

  if (status == MI_OK)
  {
     Serial.print("The card's number is: ");
     memcpy(serNum, str, 5);
     rfid.showCardID(serNum);//show the card ID
     Serial.println();
     uchar* id = serNum;
     switch(card){
        case 0:    
              if( id[0]==0xB0 && id[1]==0x73 && id[2]==0xF6 && id[3]==0xA2 ) 
              {
                 count++;
                 Serial.println("Card 1!");
               } 
              break;
        case 1:
              if( id[0]==0x20 && id[1]==0x23 && id[2]==0xE9 && id[3]==0xA2 ) 
              {
                 count++; 
                 Serial.println("card 2");
              } 
              break;   

        case 2:
              if( id[0]==0x26 && id[1]==0x2E && id[2]==0xBF && id[3]==0x29 ) 
              {
                 count++; 
                 Serial.println("card 3");
              } 
              break;    

        case 3:
              if( id[0]==0xA0 && id[1]==0x15 && id[2]==0xDF && id[3]==0xA4 ) 
              {
                 count++; 
                 Serial.println("card 4");
              } 
              break;    
        default:

              break;               
         }
  }
  delay(2000);

 // rfid.halt(); //command the card into sleep mode 
 

  i++;
  if(i>3){
    i=0;
  }
    
  if(count==4){
   Serial.println("Correct Order....Door Unlocked");
   count=0; 
   digitalWrite(relay, HIGH);  
   
  }
  else if(count>3){
      count=0;
      Serial.println("Door locked");  
  }
  else
       Serial.println("Door locked");   
}//End of void loop

int checkRFID(int i){
//  int card=0;
  if(i==0){
    rfid.begin(7,5,4,8,3,2);//(2,4,5,7,3,6);
    rfid.init();
   // card=0;
  }
  if(i==1){
    rfid.begin(7,5,4,9,3,2);//(2,4,5,8,3,6);
    rfid.init();
   // card=1;
  }
  if(i==2){
    rfid.begin(7,5,4,10,3,2);//(2,4,5,9,3,6);
    rfid.init();
   // card=2;
  }
  if(i==3){
    rfid.begin(7,5,4,11,3,2);
    rfid.init();
   // card=3;
  }

  delay(100);
 
  return i;

}
