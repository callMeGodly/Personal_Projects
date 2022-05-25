void encoder_init(void);

extern unsigned char new_state, old_state; // states for the rotary encoder
extern unsigned char a, b; // flags for the rotary encoder
extern unsigned int threshold;   // Threshold for the temperature, default at 75 but eeprom will overide eventually, used to debug when I want flash memory off
extern unsigned char changed;  // Flag for state change