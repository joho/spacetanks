#ifndef TANK_H
#define TANK_H

const uint8_t tankFrameCount = 3;
const uint8_t tankFrameWidth = 8;
const uint8_t tankFrameHeight = 8;
const uint8_t PROGMEM tankFrames[][8] = {
  /* Frame number 0
      ## ## # 
       #   #  
       # #    
       # #####
       # #    
       #   #  
      # ## ## 
              
  */
  {0x41,0x3f,0x40,0x5d,0x09,0x6a,0x49,0x08},
  /* Frame number 1
      # ## ## 
       #   #  
       # #    
       # #####
       # #    
       #   #  
       ## ### 
              
  */
  {0x01,0x7e,0x41,0x1d,0x48,0x6b,0x49,0x08},
  /* Frame number 2
       ## ### 
       #   #  
       # #    
       # #####
       # #    
       #   #  
      ## ###  
              
  */
  {0x40,0x7f,0x01,0x5c,0x49,0x6b,0x09,0x08}
};

#endif
