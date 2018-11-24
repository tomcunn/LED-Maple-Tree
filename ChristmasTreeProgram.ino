#include <Adafruit_NeoPixel.h>

#define PIN D3
#define TRUNK_LED 77
#define NUMBER_OF_LEDS 500

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_OF_LEDS, PIN, NEO_GRB + NEO_KHZ400);
enum TREE_STATE
{
  RED_TREE,
  BLUE_TREE,
  SNOW_TREE,
  MULTICOLOR_TREE,
  SPARKLE_TREE,
  CANDY_CANE
};

void setup() 
{
  //Init the strip with all zeros
  strip.begin();

  //Turn on the Board LED
  pinMode(D0,OUTPUT);
  digitalWrite(D0,HIGH);

  //Turn all of the LEDS off
  for(int i = 0; i<NUMBER_OF_LEDS ; i++)
   {
      strip.setPixelColor(i, 0, 0, 0);
   }

  //Put a delay in here so that pixels don't all turn white at start
  delay(1000);
  
  //Display the colors
  strip.show(); 
}

void loop() 
{
   static TREE_STATE CurrentTreeState = RED_TREE;
   static int timer = 0;
   
   switch(CurrentTreeState)
   {
      case(RED_TREE):
      { 
         for(int i = 0; i<(NUMBER_OF_LEDS-1) ; i=i+1)
         {
           strip.setPixelColor(i, 0, 50, 0);
           strip.setPixelColor(i+1, 50, 50, 0);
         }
         timer++;
         //10 seconds
         if(timer>10)
         {
            CurrentTreeState = BLUE_TREE;
            timer = 0;
         }
      }
      break;
      
      case(BLUE_TREE):
      {
         static int TurnBlueCounter = 0;

         if(TurnBlueCounter < 100)
         {
           TurnBlueCounter++;
         }
         else
         {
           TurnBlueCounter = 100;
         }
         timer++;
         for(int i = 0; i<NUMBER_OF_LEDS ; i++)
         {
           strip.setPixelColor(i, 0, 0, TurnBlueCounter);
         }
         timer++;
         //15 seconds
         if(timer>150)
         {
            CurrentTreeState = SNOW_TREE;
            TurnBlueCounter = 0;
            timer = 0;
         }
      }
      break;

      case(SNOW_TREE):
      {
         timer++;
         int white_snow;
         
         for(int i = 0; i<NUMBER_OF_LEDS ; i++)
         {
           white_snow = random(0, 2);
           if(white_snow == 1)
           {
             strip.setPixelColor(i, 20, 20, 20);
           }
           else
           {
             strip.setPixelColor(i, 0, 0, 0);
           }
           
         }
         timer++;
         //15 seconds
         if(timer>500)
         {
            CurrentTreeState = MULTICOLOR_TREE;
            timer = 0;
         }
      }
      break;

      case(MULTICOLOR_TREE):
      {
         for(int i = 0; i<(NUMBER_OF_LEDS-3) ; i=i+3)
         {
           strip.setPixelColor(i, 50, 0, 0);
           strip.setPixelColor(i+1, 0, 50, 0);
           strip.setPixelColor(i+2, 0, 0, 50);
         }
         timer++;
         //15 seconds
         if(timer>15)
         {
            CurrentTreeState = SPARKLE_TREE;
            timer = 0;
         }
      
      }
      break;

      case(SPARKLE_TREE):
      {
         static int FlowNumber = 0;
         timer++;
         FlowNumber++;
         
         if(FlowNumber > 2)
         {
           FlowNumber == 0;
         }
 
         for(int i = 0; i<(NUMBER_OF_LEDS-3) ; i=i+3)
         {
            if(FlowNumber == 0)
            {
              strip.setPixelColor(i, 50, 0, 0);
              strip.setPixelColor(i+1, 0, 50, 0);
              strip.setPixelColor(i+2, 0, 0, 50);
            }
            else if(FlowNumber == 1)
            {
              strip.setPixelColor(i, 0, 50, 0);
              strip.setPixelColor(i+1, 0, 0, 50);
              strip.setPixelColor(i+2, 50, 0, 0);
            }
            else if(FlowNumber ==2)
            {
              strip.setPixelColor(i, 0, 0, 50);
              strip.setPixelColor(i+1, 50, 0, 0);
              strip.setPixelColor(i+2, 0, 50, 0);              
            }
         }
         //15 seconds
         if(timer>15)
         {
            CurrentTreeState = CANDY_CANE;
            timer = 0;
         }
      }
      break;
      
      case(CANDY_CANE):
      {
         static int flop = 0;
         //15 seconds
         timer++;
         if(timer>15)
         {
            CurrentTreeState = RED_TREE;
            timer = 0;
         }
         for(int i = 0; i<(NUMBER_OF_LEDS) ; i++)
         {
            if(i%50 == 0)
            {
              flop ^= 1;
            }
            if(flop)
            {
               strip.setPixelColor(i, 0, 30, 0);
            }
            else
            {
               strip.setPixelColor(i, 20, 20, 20);
            }
         }
      }
      break;
      
      default:
         strip.setPixelColor(100, 100, 100, 100);
      break;
   }  
   //Show the strip
   strip.show();
   
   //Delay poor mans task rate
   
   if(CurrentTreeState == BLUE_TREE)
   {
     delay(100);  
   }
   else if(CurrentTreeState == SNOW_TREE)
   {
     delay(50); 
   }
   else
   {
      delay(1000);
   }
 
}
