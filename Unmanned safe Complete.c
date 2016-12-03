/*******************************************************************************
���ϸ� :   Exam4_3.c
 
�� ��  :    ATmega128�� PORTB�� ����� LED�� PB0(LSB)���� PB7(MSB) ��������
           �� ĭ�� �̵��ϴ� ���α׷��� �ۼ��� ����.

Device    : Atmega128-16AI
Clock     : 16MHz
���� ȯ�� : IAR EWAVR 2.28A
*******************************************************************************/

#include<mega128.h>  // ATMEGA128 IO REGISTER ����
#include<delay.h>

#define MOTOR_PORT  PORTC
#define MOTOR_DDR   DDRC
#define PWM1_ON     (MOTOR_PORT|=0x01)
#define PWM1_OFF    (MOTOR_PORT&=0xFE)
#define DIR1_ON     (MOTOR_PORT|=0x02)
#define DIR1_OFF    (MOTOR_PORT&=0xFD)
#define ENABLE1_OFF (MOTOR_PORT|=0x04)
#define ENABLE1_ON  (MOTOR_PORT&=0xFB)
#define BREAK1_ON   (MOTOR_PORT|=0x08)
#define BREAK1_OFF  (MOTOR_PORT&=0xF7)
#define PWM2_ON     (MOTOR_PORT|=0x10)
#define PWM2_OFF    (MOTOR_PORT&=0xEF)
#define DIR2_ON     (MOTOR_PORT|=0x20)
#define DIR2_OFF    (MOTOR_PORT&=0xDF)
#define ENABLE2_ON  (MOTOR_PORT|=0x40)
#define ENABLE2_OFF (MOTOR_PORT&=0xBF)

// �ܺκ��� ���� ���� //
int num = 0;
int i = 0; // �ݸ��� ���� ����
int j = 0; // ��й�ȣ ī��Ʈ üũ
int gar = 0; // ���ȣ �ޱ� ����
int call = 0; // ������ ������ �Լ� 


      unsigned char key = 0xFF; // Ű��ĵ �Է� �޴� ����
      unsigned char room = 0xFF; //���ȣ
      unsigned char code = 0xFF; // ��üũ��
      unsigned char recheck = 0xFF; // ������ ����
      unsigned char recheck1 = 0xFF; // ������2 ����
      
      unsigned char pass[] = {1, 0, 0, 4, 10};  // �н����� ����
      //unsigned char pass2[] = {2, 5, 0, 0, 10};
      unsigned char pass3[] = {2, 1, 6, 5, 10};
      
      unsigned char input[] = {0, 0, 0, 0}; // �н����� ���� ����

// �ܺκ��� ���� ���� //

  
char KeyScan(void)
{
  char KeyBuf=0xFF;  // Ű ���� �� ����, �ʱⰪ 0xFF

  PORTD=0x15;         // ��Ʈ �ʱⰪ, �Է��� ����Ǯ������ ���
  DDRD=0xAA;         // ��Ʈ0,1,2,3 ������� ����
                     
  PORTD.1=0; // 1��° �� ����
  if(!PIND.2)KeyBuf=1;
  if(!PIND.0)KeyBuf=2;
  if(!PIND.4)KeyBuf=3;
  PORTD.1=1; // 1��° �� ����

  PORTD.7=0; // 2��° �� ����
  if(!PIND.2)KeyBuf=4;
  if(!PIND.0)KeyBuf=5;
  if(!PIND.4)KeyBuf=6;
  PORTD.7=1; // 2��° �� ����

  PORTD.5=0; // 3��° �� ����
  if(!PIND.2)KeyBuf=7;
  if(!PIND.0)KeyBuf=8;
  if(!PIND.4)KeyBuf=9;
  PORTD.5=0; // 3��° �� ����

  PORTD.3=0; // 4��° �� ����
  if(!PIND.2)KeyBuf=11;
  if(!PIND.0)KeyBuf=0;
  if(!PIND.4)KeyBuf=10;
  PORTD.3=1; // 4��° �� ����

  return KeyBuf; // Key ������ 0xFF ����
}

void Move1(void)
{
                                // B��Ʈ E��Ʈ�� ���� ���� ��Ʈ�� 151 ������ġ 
                                // A.0 A.1 A.2 �� y,x,z ������ JK ��ġ

        PORTA.0 = 1;
        PORTA.1 = 0;
        delay_ms(5700);
        PORTA.0 = 0;
        PORTA.1 = 0;
        delay_ms(1000);
       
        PORTA.2 = 1;
        PORTA.3 = 0;
        delay_ms(5000);
        PORTA.2 = 0;
        PORTA.3 = 0;
        delay_ms(1000);
        
        PWM1_ON;
        PORTA.4 = 1;
        PORTA.5 = 0;
        delay_ms(3400);
        PORTA.4 = 0;
        PORTA.5 = 0;
        delay_ms(1000);
        
        PORTA.4 = 0;
        PORTA.5 = 1;
        delay_ms(3600);
        PORTA.4 = 0;
        PORTA.5 = 0;
        delay_ms(1000);
      
        PORTA.2 = 0;
        PORTA.3 = 1;
        delay_ms(5000);
        PORTA.2 = 0;
        PORTA.3 = 0;
        delay_ms(1000);
          
        PORTA.0 = 0;
        PORTA.1 = 1;
        delay_ms(6500);
        PORTA.0 = 0;
        PORTA.1 = 0;
        delay_ms(1000);

        PORTA.4 = 1;
        PORTA.5 = 0;
        delay_ms(3400);
        PORTA.4 = 0;
        PORTA.5 = 0;
        delay_ms(1000);
        
                PWM1_OFF;
                delay_ms(1000);
        
        PORTA.4 = 0;
        PORTA.5 = 1;
        delay_ms(3600);
        PORTA.4 = 0;
        PORTA.5 = 0;
        delay_ms(1000);
                                                                    
 /*                               
                                //y�� jk����                                   
                                PORTB = 0x7D;
                                PORTE = 0x00;
                                PORTA.0 = 1; 
                                delay_ms(8000);
                                PORTA.0 = 0;
                                delay_ms(1000);
                                
                                                                                               
                                //x�� ���°�                                   
                                PORTB = 0x78;
                                PORTE = 0x00;
                                PORTA.1 = 1; 
                                delay_ms(6000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //z��  //���°� 
                                PWM1_ON; 	// ���ڼ� ��
                                                     
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                                                   
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                //x��                                   
                                PORTB = 0x00;
                                PORTE = 0x78;
                                PORTA.1 = 1; 
                                delay_ms(6000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //y�� jk����                                   
                                PORTB = 0x00;
                                PORTE = 0x7D;
                                PORTA.0 = 1; 
                                delay_ms(8000);
                                PORTA.0 = 0;
                                delay_ms(1000);
                                
                                //z��
                                                                   
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                PWM1_OFF; // ���ڼ� ����
                                                                   
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);          
*/                                
} /*
void Move2(void)
{
                                // B��Ʈ E��Ʈ�� ���� ���� ��Ʈ�� 151 ������ġ 
                                // A.0 A.1 A.2 �� y,x,z ������ JK ��ġ
 
                                //x�� ���°�
                                PORTB = 0x40;
                                PORTE = 0x00;
                                PORTA.1 = 1; 
                                delay_ms(3000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //y�� jk����                                   
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.0 = 1; 
                                delay_ms(5000);
                                PORTA.0 = 0;
                                delay_ms(1000);
                                                                                               
                                //x�� ���°�                                   
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.1 = 1; 
                                delay_ms(5000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //z��  //���°� 
                                PWM1_ON; 	// ���ڼ� ��
                                                     
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                                                   
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                //x�� ���°�                                   
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.1 = 1; 
                                delay_ms(5000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //y�� jk����                                   
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.0 = 1; 
                                delay_ms(5000);
                                PORTA.0 = 0;
                                delay_ms(1000);
                                
                                //x�� ���°�
                                PORTB = 0x00;
                                PORTE = 0x40;
                                PORTA.1 = 1; 
                                delay_ms(3000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //z��
                                                                   
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                PWM1_OFF; // ���ڼ� ����
                                                                   
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000); 

}   */
void Move3(void)
{
                                // B��Ʈ E��Ʈ�� ���� ���� ��Ʈ�� 151 ������ġ 
                                // A.0 A.1 A.2 �� y,x,z ������ JK ��ġ
                                
                               PORTA.2 = 1;
        PORTA.3 = 0;
        delay_ms(5000);
        PORTA.2 = 0;
        PORTA.3 = 0;
        delay_ms(1000);
        
        PWM1_ON;
        
        PORTA.4 = 1;
        PORTA.5 = 0;
        delay_ms(3400);
        PORTA.4 = 0;
        PORTA.5 = 0;
        delay_ms(1000);
        
        PORTA.4 = 0;
        PORTA.5 = 1;
        delay_ms(3600);
        PORTA.4 = 0;
        PORTA.5 = 0;
        delay_ms(1000);
      
        PORTA.2 = 0;
        PORTA.3 = 1;
        delay_ms(5000);
        PORTA.2 = 0;
        PORTA.3 = 0;
        delay_ms(1000);
        
        PORTA.4 = 1;
        PORTA.5 = 0;
        delay_ms(3400);
        PORTA.4 = 0;
        PORTA.5 = 0;
        delay_ms(1000);
        
                PWM1_OFF;
                delay_ms(1000);
        
        PORTA.4 = 0;
        PORTA.5 = 1;
        delay_ms(3600);
        PORTA.4 = 0;
        PORTA.5 = 0;
        delay_ms(1000);
        

                                
                                                                 
 /*                                                                                                                      
                                //x�� ���°�                                   
                                PORTB = 0x78;
                                PORTE = 0x00;
                                PORTA.1 = 1; 
                                delay_ms(6000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //z��  //���°� 
                                PWM1_ON; 	// ���ڼ� ��
                                                     
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                                                   
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                //x��                                   
                                PORTB = 0x00;
                                PORTE = 0x78;
                                PORTA.1 = 1; 
                                delay_ms(6000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                        
                                
                                //z��
                                                                   
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                PWM1_OFF; // ���ڼ� ����
                                                                   
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000); 
                                */

}


void Compare(void)
{                    
                for( i = 0; i < 5; i++ ) // A ���� ����
                {
                        if( input[i] == pass[i] )
                        {
                                j++;
                        }
                } // A ���� ����
                
                        if( j == 5 )
                        { // ������ ���� 
                                PORTA.6 = 1;
                                PORTA.7 = 0;
                                delay_ms(300);
                                PORTA.6 = 0;
                                PORTA.7 = 0;
                                delay_ms(500);
                                
                                
                                Move1();
                                
                                gar = room;                  
                                for( i = 0; i < 5; i++ ){
                                                input[i] = 0;
                                                num = 0;
                                                j = 0;
                                                code = 0;
                                                room = 0;
                                        } //B ���� ����
                        } // ������ ����
                        else
                        { // ������ ����
                                PORTA.6 = 1;
                                PORTA.7 = 0;
                                delay_ms(1300);
                                PORTA.6 = 0;
                                PORTA.7 = 0;
                                delay_ms(500);

                                for( i = 0; i < 5; i++ ) // C ���� ����
                                        {
                                                input[i] = 0;
                                                num = 0;
                                                j = 0;
                                                room = 0;
                                                code = 0;
                                        } // C ���� ����
                        } // ������ ����   
} /*
void Compare2(void)
{
                for( i = 0; i < 5; i++ ) // A ���� ����
                {
                        if( input[i] == pass2[i] )
                        {
                                j++;
                        }
                } // A ���� ���� 
                
                        if( j == 5 ) // ������ ����
                        {      
                                PORTE.6 = 1; // ȿ���� 
                                PORTE.7 = 0;
                                delay_ms(300);
                                PORTE.6 = 0;
                                PORTE.7 = 0;
                                delay_ms(5);
                                
                                PORTA = 0x06;
                                Move2();
                                
                                PORTA = 0x6D;
                                
                                gar = room;
                                for( i = 0; i < 5; i++ ) // B ���� ����
                                        {
                                                input[i] = 0;
                                                num = 0;
                                                j = 0;
                                                code = 0;
                                                room = 0;
                                        } //B ���� ����
                        } // ������ ����
                        else
                        { // ������ ����
                                PORTB.6 = 1; // ȿ���� 
                                PORTB.7 = 0;
                                delay_ms(1350);
                                PORTB.6 = 0;
                                PORTB.7 = 0;
                                delay_ms(100);
                                for( i = 0; i < 5; i++ ) // C ���� ����
                                        {
                                                input[i] = 0;
                                                num = 0;
                                                j = 0;
                                                room = 0;
                                                code = 0;
                                        } // C ���� ����
                        } // ������ ����    
} */
void Compare3(void)
{
                for( i = 0; i < 5; i++ ) // A ���� ����
                {
                        if( input[i] == pass3[i] )
                        {
                                j++;
                        }
                } // A ���� ���� 
                
                        if( j == 5 ) // ������ ����
                        {
                               PORTA.6 = 1;
                                PORTA.7 = 0;
                                delay_ms(300);
                                PORTA.6 = 0;
                                PORTA.7 = 0;
                                delay_ms(500);

                                Move3();
	 	                
                                gar = room;
                                for( i = 0; i < 5; i++ ) // B ���� ����
                                        {
                                                input[i] = 0;
                                                num = 0;
                                                j = 0;
                                                code = 0;
                                                room = 0;
                                        } //B ���� ����
                        } // ������ ����
                        else
                        { // ������ ����
                                PORTA.6 = 1;
                                PORTA.7 = 0;
                                delay_ms(1300);
                                PORTA.6 = 0;
                                PORTA.7 = 0;
                                delay_ms(500);
                                
                                for( i = 0; i < 5; i++ ) // C ���� ����
                                        {
                                                input[i] = 0;
                                                num = 0;
                                                j = 0;
                                                room = 0;
                                                code = 0;
                                        } // C ���� ����
                        } // ������ ����    
}  


void Remove1(void)
{  
                                                                 
                                                           
                                // B��Ʈ E��Ʈ�� ���� ���� ��Ʈ�� 151 ������ġ 
                                // A.0 A.1 A.2 �� y,x,z ������ JK ��ġ                                                     
                                //z��  //���°�
                                
                               PWM1_ON;
                               PORTA.4 = 1;
                                PORTA.5 = 0;
                                delay_ms(3400);
                                PORTA.4 = 0;
                                PORTA.5 = 0;
                                delay_ms(1000);
        
                                PORTA.4 = 0;
                                PORTA.5 = 1;
                                delay_ms(3600);
                                PORTA.4 = 0;
                                PORTA.5 = 0;
                                delay_ms(1000);
                                PORTA.0 = 1;
        PORTA.1 = 0;
        delay_ms(5700);
        PORTA.0 = 0;
        PORTA.1 = 0;
        delay_ms(1000);
       
        PORTA.2 = 1;
        PORTA.3 = 0;
        delay_ms(5000);
        PORTA.2 = 0;
        PORTA.3 = 0;
        delay_ms(1000);
        
        PORTA.4 = 1;
        PORTA.5 = 0;
        delay_ms(3400);
        PORTA.4 = 0;
        PORTA.5 = 0;
        delay_ms(1000);
        
        PWM1_OFF;
        delay_ms(1000);
        
        PORTA.4 = 0;
        PORTA.5 = 1;
        delay_ms(3600);
        PORTA.4 = 0;
        PORTA.5 = 0;
        delay_ms(1000);
      
        PORTA.2 = 0;
        PORTA.3 = 1;
        delay_ms(5000);
        PORTA.2 = 0;
        PORTA.3 = 0;
        delay_ms(1000);
          
        PORTA.0 = 0;
        PORTA.1 = 1;
        delay_ms(6500);
        PORTA.0 = 0;
        PORTA.1 = 0;
        delay_ms(1000);
                                
                                  
                               
                                /*
                                 PWM1_ON; 	// ���ڼ� ��
                                                     
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                                                   
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                //y�� jk����                                   
                                PORTB = 0x7D;
                                PORTE = 0x00;
                                PORTA.0 = 1; 
                                delay_ms(8000);
                                PORTA.0 = 0;
                                delay_ms(1000);
                                                                                               
                                //x�� ���°�                                   
                                PORTB = 0x78;
                                PORTE = 0x00;
                                PORTA.1 = 1; 
                                delay_ms(6000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //z��  //���°� 
                                                                                     
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                PWM1_OFF;               //���ڼ� ����
                                                                  
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                //x��                                   
                                PORTB = 0x00;
                                PORTE = 0x78;
                                PORTA.1 = 1; 
                                delay_ms(6000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //y�� jk����                                   
                                PORTB = 0x00;
                                PORTE = 0x7D;
                                PORTA.0 = 1; 
                                delay_ms(8000);
                                PORTA.0 = 0;
                                delay_ms(1000);
                                                */
                                                                
                                call = 1;

} /* 
void Remove2(void)
{  
                // B��Ʈ E��Ʈ�� ���� ���� ��Ʈ�� 151 ������ġ 
                                // A.0 A.1 A.2 �� y,x,z ������ JK ��ġ

                                //z��  //���°� 
                                PWM1_ON; 	// ���ڼ� ��
                                                     
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                                                   
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                //x�� ���°�
                                PORTB = 0x40;
                                PORTE = 0x00;
                                PORTA.1 = 1; 
                                delay_ms(3000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //y�� jk����                                   
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.0 = 1; 
                                delay_ms(5000);
                                PORTA.0 = 0;
                                delay_ms(1000);
                                                                                               
                                //x�� ���°�                                   
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.1 = 1; 
                                delay_ms(5000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //z��
                                                                   
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                PWM1_OFF; // ���ڼ� ����
                                                                   
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                //x�� ���°�                                   
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.1 = 1; 
                                delay_ms(5000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //y�� jk����                                   
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.0 = 1; 
                                delay_ms(5000);
                                PORTA.0 = 0;
                                delay_ms(1000);
                                
                                //x�� ���°�
                                PORTB = 0x00;
                                PORTE = 0x40;
                                PORTA.1 = 1; 
                                delay_ms(3000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                
                                call = 1;

}    */
void Remove3(void)
{  
                // B��Ʈ E��Ʈ�� ���� ���� ��Ʈ�� 151 ������ġ 
                                // A.0 A.1 A.2 �� y,x,z ������ JK ��ġ
                                
                                PWM1_ON;
                                
                                  PORTA.4 = 1;
        PORTA.5 = 0;
        delay_ms(3400);
        PORTA.4 = 0;
        PORTA.5 = 0;
        delay_ms(1000);
        
        PORTA.4 = 0;
        PORTA.5 = 1;
        delay_ms(3800);
        PORTA.4 = 0;
        PORTA.5 = 0;
        delay_ms(1000);
        
                PORTA.2 = 1;
        PORTA.3 = 0;
        delay_ms(5000);
        PORTA.2 = 0;
        PORTA.3 = 0;
        delay_ms(1000);
        
        PORTA.4 = 1;
        PORTA.5 = 0;
        delay_ms(3400);
        PORTA.4 = 0;
        PORTA.5 = 0;
        delay_ms(1000);
        
        PWM1_OFF;
        delay_ms(1000);
        
        PORTA.4 = 0;
        PORTA.5 = 1;
        delay_ms(3600);
        PORTA.4 = 0;
        PORTA.5 = 0;
        delay_ms(1000);
        
                PORTA.2 = 0;
        PORTA.3 = 1;
        delay_ms(5000);
        PORTA.2 = 0;
        PORTA.3 = 0;
        delay_ms(1000);
        
        
                                
                                
                                
                                
                                /*
                                                                 
                                //z��  //���°� 
                                PWM1_ON; 	// ���ڼ� ��
                                                     
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                                                   
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                                                                                                       
                                //x�� ���°�                                   
                                PORTB = 0x78;
                                PORTE = 0x00;
                                PORTA.1 = 1; 
                                delay_ms(6000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                               
                                //z��
                                                                   
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                PWM1_OFF; // ���ڼ� ����
                                                                   
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);                                  
                                
                                //x��                                   
                                PORTB = 0x00;
                                PORTE = 0x78;
                                PORTA.1 = 1; 
                                delay_ms(6000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                          */
                                call = 1;     
}


void main(void)
{
      
       MOTOR_DDR = 0xFF; // ���� ���� ���� �ʱⰪ
       ENABLE1_ON;       // ���� ���� ���� �ʱⰪ
       DDRB = 0xFE;
       PORTB = 0xFF;
       DDRE = 0xFF;
       PORTE = 0xFF;
       DDRF = 0xFF;
       DDRA = 0xFF;
       PORTA = 0xFF;
                        
        while(1) // A ���� ����
        {      
                if(gar == 1 || gar == 2 || gar == 3) // Remove ����
                {
                        while(1)
                        {
                                recheck1 = KeyScan(); 
                                delay_ms(500);
                                if(recheck1 == 11)
                                {
                                        while(1)
                                        {
                                                recheck = KeyScan();
                                                delay_ms(500);
                                                if(recheck == 10)
                                                {
                                                        recheck = 0;
                                                        recheck = 0;
                                                        switch(gar)
                                                        {
                                                                case 1:
                                                                Remove1();
                                                                break;
                                                                case 2:
                                                                //Remove2();
                                                                break;
                                                                case 3:
                                                                Remove3();
                                                                break;
                                                        }
                                                if(call == 1)
                                                {
                                                        break;
                                                }
                                                }
                                        if(call == 1)
                                        {
                                                break;
                                        }
                                        }
                                if(call == 1)
                                {
                                        break;
                                }
                                }
                        if(call == 1)
                        {
                                gar = 0;
                                break;
                        }
                        }
                }       
                else
                {
                              
                        while(1) // B ���� ����
                        {
                                call = 0;
                                room = KeyScan();
                                if(room == 0x01||room==0x02||room==0x03) // 1, 2, 3 ������ ���� 
                                {
                                        delay_ms(500);
                                        while(1) // C ���Ϲ� ����
                                        {
                                                code = KeyScan();                           
                                                if(code==10) // #Ű��ĵ ������ ����
                                                {
                                                        delay_ms(500);
                                                        while(1) // D ���Ϲ� ����
                                                        {
                                                                key = KeyScan();
                                                                input[num] = key;
                                                                switch(key)
                                                                {
                                                                        case 1:
                                                                        num++;                                                                                              
                                                                        delay_ms(500);
                                                                        break;
                                                                
                                                                        case 2:
                                                                        num++;                                                             
                                                                        delay_ms(500);
                                                                        break;
                                                                
                                                                        case 3:
                                                                        num++;
                                                                        delay_ms(500);
                                                                        break;
                                                                
                                                                        case 4:
                                                                        num++;
                                                                        delay_ms(500);
                                                                        break;
                                                                
                                                                        case 5:
                                                                        num++;
                                                                        delay_ms(500);
                                                                        break;
                                                                
                                                                        case 6:
                                                                        num++;
                                                                        delay_ms(500);
                                                                        break;
                                                                
                                                                        case 7:
                                                                        num++;
                                                                        delay_ms(500);
                                                                        break;
                                                                
                                                                        case 8:
                                                                        num++;
                                                                        delay_ms(500);
                                                                        break;
                                                                
                                                                        case 9:
                                                                        num++;
                                                                        delay_ms(500);
                                                                        break;
                                                                
                                                                        case 0:
                                                                        num++;
                                                                        delay_ms(500);
                                                                        break;
                                                                
                                                                        case 10:
                                                                        num++;
                                                                        delay_ms(500);
                                                                        break;
                                                                
                                                                        case 11:
                                                                        num++;
                                                                        delay_ms(500);
                                                                        break;
                                                                
                                                                }
                                                                if(num == 5)
                                                                {     
                                                                        break;
                                                                }
                                                        } // D ���Ϲ� ���� 
                                                } // #Ű��ĵ ������ ����
                                                if( num == 5)
                                                {
                                                        break;
                                                }              
                                        } // C ���Ϲ� ����        
                                } // 1, 2, 3 ������ ����
                        
                                if( num == 5)
                                {
                                        break;
                                } 
                        } // B���� ���� 
               
                        // üũ ����
                          if( num == 5 )
                        {       
                                switch (room)
                                {
                                case 1:
                                        Compare();
                                        break;
                                case 2:
                                        //Compare2();
                                        break;
                                case 3:
                                        Compare3();
                                        break; 
                                }
                        }
                }     
        }
        
        

}

        
         



