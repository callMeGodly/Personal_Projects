
void serial_init();
void tx_helper(short int c);
void tx_char(char ch);

extern char receive_buffer[5]; //  to hold RX values
extern char begin;  // to start accepting
extern int placement;   // which spot in the array does the value go to
extern char is_complete;    // if complete then flag it so the main loop will update
