#ifndef PEW_H
#define PEW_H

const uint8_t pewFrameCount = 3;
const uint8_t pewFrameWidth = 8;
const uint8_t pewFrameHeight = 8;
const uint8_t PROGMEM pewFrames[][8] = {
  /* Frame number 0
              
       #      
      # #     
      # #     
      # #     
       #      
              
              
  */
  {0x1c,0x22,0x1c,0x00,0x00,0x00,0x00,0x00},
  /* Frame number 1
              
         #    
        # #   
        # #   
        # #   
         #    
              
              
  */
  {0x00,0x00,0x1c,0x22,0x1c,0x00,0x00,0x00},
  /* Frame number 2
       #      
      # #   # 
      # #  # #
      # #  # #
      # #  # #
      # #   # 
       #      
              
  */
  {0x3e,0x41,0x3e,0x00,0x00,0x1c,0x22,0x1c}
};

#endif
