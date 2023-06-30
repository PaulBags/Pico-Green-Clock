/* Very preliminary work on a new DS3231 library. */
#include <stdio.h>

typedef unsigned char Byte;

Byte dec_to_bcd(int number) {
  return (number % 10) + (number / 10 * 16);
}

Byte build_second(int number, int alarm) {
    
    // Truncate input to valid values
    if (number > 59) { number = 59; }
    else if (number < 0) { number = 0; };
    if (alarm > 1) { alarm = 1; }
    else if (alarm < 0) { alarm = 0; };
    
    //return byte
    return dec_to_bcd(number) + (alarm << 7);
}
Byte build_minute(int number, int alarm) {
    return build_second(number, alarm);
}

int main() {
  const Byte
  	Num1_addr = 0x00,
    Num2_addr = 0x01,
  	Num3_addr = 0x02,
  	Num4_addr = 0x03;
  
  Byte Numbers[4] = {0};
  
  Byte
  	*Num1 = &Numbers[Num1_addr],
    *Num2 = &Numbers[Num2_addr],
    *Num3 = &Numbers[Num3_addr],
    *Num4 = &Numbers[Num4_addr];
  
  *Num1 = build_second(59, 0);
  *Num2 = build_minute(25, 0);
  *Num3 = build_minute(60, 2);
  *Num4 = build_minute(-1, -1);
  
  printf("%d\n%d\n%d\n%d\n", *Num1, *Num2, *Num3, *Num4);
 
  return 0;
}



// # PaulBags 2023-JUN-30
