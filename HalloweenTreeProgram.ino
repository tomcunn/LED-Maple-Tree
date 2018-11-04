#include <Adafruit_NeoPixel.h>

#define PIN D3
#define TRUNK_LED 77
#define NUMBER_OF_LEDS 500

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_OF_LEDS, PIN, NEO_GRB + NEO_KHZ400);
enum TREE_STATE
{
  GREEN_TREE,
  FALL_TREE,
  DEAD_TREE,
  ORANGE_TREE,
  PURPLE_TREE,
  PURPLE_SPARK,
  PURPLE_GLOW
};

void setup() 
{
  //Init the strip with all zeros
  strip.begin();

  pinMode(D0,OUTPUT);
  digitalWrite(D0,HIGH);
  for(int i = 0; i<NUMBER_OF_LEDS ; i++)
   {
      strip.setPixelColor(i, 0, 0, 0);
   }
  strip.show(); // Initialize all pixels to 'off'
}

void loop() 
{
   static TREE_STATE CurrentTreeState = GREEN_TREE;
   static int timer = 0;
   
   switch(CurrentTreeState)
   {
      case(GREEN_TREE):
         for(int i = 0; i<NUMBER_OF_LEDS ; i++)
         {
           //This colors the trunk of the tree brown
           if(i<TRUNK_LED)
           {
              strip.setPixelColor(i, 10, 40, 0);
           }
           //Color the rest of the tree green
           else
           {
              strip.setPixelColor(i, 100, 0, 0);
           }
         }
         timer++;
         //15 seconds
         if(timer>300)
         {
            CurrentTreeState = FALL_TREE;
            timer = 0;
         }
      break;
      
      case(FALL_TREE):
        timer++;
        static int red_color = 0;
        static int green_color = 100;

        if(timer > 500)
        {
           timer = 0;
           CurrentTreeState = DEAD_TREE;
        }
        else if(timer > 99)
        {
          //no nothing
        }

        else
        {
          for(int i = TRUNK_LED; i<NUMBER_OF_LEDS ; i=i+3)
          {
             strip.setPixelColor(i, green_color - timer, red_color+timer,0);
             strip.setPixelColor(i+1, green_color - timer/2, red_color+timer/2,0);  
             strip.setPixelColor(i+2, green_color - timer/1.5, red_color+timer/1.5,0);
            //Fad to red
            //strip.setPixelColor(i, 0, 100, 0);
            //Fad to yellow
            //strip.setPixelColor(i+1, 50, 50, 0);
            //Fad to orange
            //strip.setPixelColor(i+2, 30, 70, 0);
          }
        }
      break;

      case(DEAD_TREE):
        int dead_leaf;
        for(int i = TRUNK_LED; i<NUMBER_OF_LEDS ; i++)
        {
          dead_leaf = random(0, 20);
          if(dead_leaf == 1)
          {
            strip.setPixelColor(i, 0, 0,0);
          }
        }
        timer ++;
        if(timer > 200)
        {
          timer = 0;

           for(int i = TRUNK_LED; i<NUMBER_OF_LEDS ; i++)
           {
              strip.setPixelColor(i, 0, 0,0);
           }
          CurrentTreeState = PURPLE_TREE;
        }

      break;

      case(PURPLE_TREE):
        int purple_light;
        timer ++;
        for(int i = TRUNK_LED; i<NUMBER_OF_LEDS ; i++)
        {
           purple_light = random(0, 10);  
           if(purple_light == 1)
           {
             strip.setPixelColor(i, 0, 30,60);
           }
           
        }
        if(timer > 200)
        {
          timer = 0;
          CurrentTreeState = PURPLE_SPARK;
        }
      break;

      case(PURPLE_SPARK):
        timer ++;
        for(int i = TRUNK_LED; i<NUMBER_OF_LEDS ; i++)
        {
           purple_light = random(0, 10);  
           if(purple_light == 1)
           {
             strip.setPixelColor(i, 0, 30,60);
           }
           else
           {
             strip.setPixelColor(i, 0, 0, 0);
           }
        }
        if(timer > 400)
        {
          for(int i = 0; i<NUMBER_OF_LEDS ; i++)
          {
             strip.setPixelColor(i, 0, 10,20);
          }
             timer = 0;
             CurrentTreeState = PURPLE_GLOW;
        }
      break;

      case(PURPLE_GLOW):
      {
         static int chase =0;
         chase ++;

         if(chase>500)
         {
            chase = 0;
         }
         timer ++;
         for(int i = 0; i<NUMBER_OF_LEDS ; i++)
         { 
            if(i<chase && i>(chase-10) && chase > 10)
            {
              strip.setPixelColor(i, 250, 0, 0);
            }
            else
            {
              strip.setPixelColor(i, 0, 10,20);
            }
         }

         if(timer > 800)
         {
            timer = 0;
            CurrentTreeState = GREEN_TREE;
         }
         
      }
      break;
      
      default:
         strip.setPixelColor(100, 100, 100, 100);
      break;
   }  
   //Show the strip
   strip.show();
   
   //Delay 50ms, poor mans task rate
   if(CurrentTreeState != PURPLE_GLOW)
   {
      delay(50);
   }
   else
   {
      delay(5);
   }
}
