    char  keypadPort at PORTD;

     unsigned short kp;
     unsigned short cnt;    // counts how many digits user entered
     unsigned short right;  // counts how many digits is matched with password

    
    sbit LCD_RS at RB0_bit;
    sbit LCD_EN at RB1_bit;
    sbit LCD_D4 at RB2_bit;
    sbit LCD_D5 at RC5_bit;
    sbit LCD_D6 at RB4_bit;
    sbit LCD_D7 at RB5_bit;

    sbit LCD_RS_DIRECTION at TRISB0_bit;
    sbit LCD_EN_DIRECTION at TRISB1_bit;
    sbit LCD_D4_DIRECTION at TRISB2_bit;
    sbit LCD_D5_DIRECTION at TRISC5_bit;
    sbit LCD_D6_DIRECTION at TRISB4_bit;
    sbit LCD_D7_DIRECTION at TRISB5_bit;
    
//    checks if password is 1234
void check_password(){
    
         switch(cnt){

         case 1: if (kp == 49)  right++; break;
         case 2: if (kp == 50) right++; break;
         case 3: if (kp == 51) right++; break;
         case 4: if (kp == 52) right++; break;
         default: break;
         
         }
}
    

void main() {




 Lcd_INIT();
 LCD_CMD(_LCD_CURSOR_OFF);
 LCD_CMD(_LCD_CLEAR);

 LCD_OUT(1,1, "Enter password");
 LCD_OUT(2,1, "to open door");
 Delay_ms(1000);

 LCD_CMD(_LCD_CLEAR);
 Delay_ms(500);

 lable1: 
         LCD_CMD(_LCD_CLEAR);
         LCD_OUT(1,1, "Door Locked");
         Delay_ms(500);
         LCD_CMD(_LCD_CLEAR);
         LCD_OUT(1,1, "Enter password:");


Keypad_Init();
TRISB = 0;


while(1)
{




    

    kp = 0;
    do{
     kp = Keypad_Key_Click();
    }while (!kp);

    switch (kp) {

      case  1: kp = 49; break; // 1
      case  2: kp = 50; break; // 2
      case  3: kp = 51; break; // 3
      
      case  5: kp = 52; break; // 4
      case  6: kp = 53; break; // 5
      case  7: kp = 54; break; // 6
      
      case  9: kp = 55; break; // 7
      case 10: kp = 56; break; // 8
      case 11: kp = 57; break; // 9

      case 13: kp = 42; break; // *
      case 14: kp = 48; break; // 0
      case 15: kp = 35; break; // #


    }
    cnt++;
    
    Lcd_Chr(2, cnt, 42);
    check_password();
    
    
    if(kp == 35){
      if(right == 4 && cnt == 5){
         LCD_CMD(_LCD_CLEAR);
         LCD_OUT(1,1, "Door unlocked");
         RB7_BIT = 1;
         

      }
      else {
         LCD_CMD(_LCD_CLEAR);
         LCD_OUT(1,1, "Wrong Password");
       }

       Delay_ms(2000);
       RB7_BIT = 0;
       cnt = 0;
       right = 0;
       goto lable1;
    }

}

}