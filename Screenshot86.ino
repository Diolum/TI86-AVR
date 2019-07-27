#include <TICL.h>
TICL ticl = TICL(9,8);

void setup() {
  Serial.begin(9600);
  ticl.resetLines();
    uint8_t screen[1024];
    int rlen = 0, rval = 0;
    
    // Request the screen image
    uint8_t msg[4] = {COMP86, SCR, 0x00, 0x00};
    rval = ticl.send(msg, NULL, 0);
    if (rval) {
      Serial.print("Failed to send SCR request: ");
      Serial.println(rval);
      return;}
    
    // Wait for ack
    ticl.resetLines();
    delay(100);
    rval = ticl.get(msg, NULL, &rlen, 0);
    if (rval) {
      Serial.print("Failed to get SCR ack: ");
      Serial.println(rval);
      return;}
    
    // Wait for screen image
    rval == ticl.get(msg, screen, &rlen, 1024);
    if (rval) {
      Serial.print("Failed to get SCR: ");
      Serial.println(rval);
      return;}
    
    // Send an ack
    rval = ticl.send(msg, NULL, 0);
    if (rval) {
      Serial.print("Failed to send ack: ");
      Serial.println(rval);
      return;}
    
    // Dump the screen to the serial console
    for (int i = 0; i < 1024; i++) {
      for (int j = 7; j >= 0; j--) {
        if (screen[i] & (1 << j)) {
          Serial.write('#');}
          else {
          Serial.write(' ');}}
      if (i % 16 == 15) {
        Serial.println();}}}

void loop() {
}
