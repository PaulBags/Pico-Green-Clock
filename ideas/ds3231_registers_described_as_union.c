/* ABANDONED/REJECTED
The idea behind this was to create a type which describes all the various ways in which a byte register of DS3231 can be expressed.

Ultimately I rejected this idea as far too convoluted and probably not useful programatically.
I probably wouldn't be able to iterate over them in an array, 
and I suspect the arrangement of bits in such a structure may not be guarenteed.
At the very least there's too much I don't know about the implications of going down this road,
and it's unnessicary to do so.

Kept for the bit descriptions, and as a warning to other programmers of my competance level: in design, code, and practicality.
*/

/* Add descriptive selectors into bytes, modelling the DS3231 registers */
union ds3231_register {
  
  /* .byte   generic access as byte   */
  unsigned char byte;
  
  /* .bits.   generic access as bits   */
  struct {
    unsigned b0:1; // BIT 0 LSB
    unsigned b1:1; // BIT 1
    unsigned b2:1; // BIT 2
    unsigned b3:1; // BIT 3
    unsigned b4:1; // BIT 4
    unsigned b5:1; // BIT 5
    unsigned b6:1; // BIT 6
    unsigned b7:1; // BIT 7 MSB
  } bits;
  
  /* .sec., .min.   for registers:
    [rtc] seconds (0x00)
    [rtc] minutes (0x01)
    [A1] seconds  (0x07) [alarm type config bit: A1M1]
    [A1] minutes  (0x08) [alarm type config bit: A1M2]
    [A2] minutes  (0x0B) [alarm type config bit: A2M2]   */
  struct {
    unsigned lower:4; // lower digit BCD:  0..9
    unsigned upper:3; // upper digit BCD:  0..5 (combined 0..59)
    unsigned alarm:1; // [rtc] must be 0; [A*] alarm type config:  0..1
  } sec, min;
  
  /***
  hours registers have two definitions to cover both 24 hour format and 12 hour format.
  This is due to bit 5 being either part of the upper digit BCD (24hr) or AM/PM flag (12hr).
  ***/
  /* .hour24., .hour12.   for registers:
    [rtc] hours (0x02)
    [A1] hours  (0x09) [alarm type config bit A1M3]
    [A2] hours  (0x0C) [alarm type config bit A2M3]   */
  struct {
    unsigned lower:4;  // lower digit BCD  0..9
    unsigned upper:2;  // upper digit BCD  0..2 (combined 0..23))
    unsigned select:1; // THIS MODE: 0 = 24 hour mode
    unsigned alarm:1;  // [rtc] must be 0; [A*] alarm type config  0..1
  } hour24;
  struct {
    unsigned lower:4;  // lower digit BCD  0..9
    unsigned upper:1;  // upper digit BCD  0..1 (combined 1..12)
    unsigned am_pm:1;  // 12HR MODE: 0 = AM, 1 = PM
    unsigned select:1; // THIS MODE: 1 = 12 hour mode
    unsigned alarm:1;  // [rtc] must be 0; [A*] alarm type config  0..1
  } hour12;
  
  /* .day_of_week.   for registers:
    [rtc] day (0x03)   */
  struct {
    unsigned day:3;  // day of week (order indeterminate but must be consistant)  1..7, 
    unsigned zero:5; // [rtc] must be 0
  } day_of_week;
  
  /* .date.   for registers:
    [rtc] date (0x04)
    [A1]  date (0x0A) [alarm type config bit A1M4]
    [A2]  date (0x0D) [alarm type config bit A2M4]   */
  struct {
    unsigned lower:4;    // lower digit BCD  0..9 (1..7 [A*] day mode)
    unsigned upper:2;    // upper digit BCD  0..3 (combined 1..31) (??zeros [A*] day mode??)
    unsigned day_date:1; // [rtc] must be 0; [A*] alarm DY/DT selection  0..1
    unsigned alarm:1     // [rtc] must be 0; [A*] alarm type config  0..1
  } date;
  
  /* .month.   for registers:
    [rtc] month/century (0x05)   */
  struct {
    unsigned lower:4;   // lower digit BCD  0..9
    unsigned upper:1;   // upper digit BCD  0..1
    unsigned zero:2;    // [rtc] must be 0
    unsigned century:1; // [rtc] bit flips when year rolls from 99 to 00
  } month;
  
  /* .year.   for registers:
    [rtc] year (0x06)   */
  struct {
    unsigned lower:4; // lower digit BCD  0..9
    unsigned upper:4; // upper digit BCD  0..9
  } year;
  
  /* .control.   for register:
    control (0x0E)   */
  // TODO //
  
  /* .status.   for register:
    control/status (0x0F)   */
  // TODO //
  
  /* .aging, .temp_upper   for registers:
    aging offset (0x10)
    MSB of temp  (0x11)   */
  signed char aging, temp_upper // signed 8 bit int
  
  /* .temp_lower   for register:
    LSB of Temp   */
  struct {
    unsigned temp_lower:2; // unsigned 2 bit int for fractional temp, 0.25C resolution
    unsigned zero:6;       // unspecified normally zeroed
  };
} ds3231_register_t;

ds3231_register_t DS3231_Registers[19];



// PaulBags 2023-JUN-30
