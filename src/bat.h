#ifndef BAT_H
#define BAT_H

const uint8_t batFrameCount = 2;
const uint8_t batFrameWidth = 8;
const uint8_t batFrameHeight = 8;
const uint8_t PROGMEM batFrames[][8] = {
  /* Frame number 0
              
              
         #    
       ## ##  
      # # # # 
              
              
              
  */
  {0x10,0x08,0x18,0x04,0x18,0x08,0x10,0x00},
  /* Frame number 1
              
              
      #  #  # 
       ## ##  
              
              
              
              
  */
  {0x04,0x08,0x08,0x04,0x08,0x08,0x04,0x00}
};

#endif
