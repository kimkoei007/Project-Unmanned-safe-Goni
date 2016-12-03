/*******************************************************************************
파일명 :   Exam4_3.c
 
동 작  :    ATmega128의 PORTB에 연결된 LED가 PB0(LSB)에서 PB7(MSB) 방향으로
           한 칸씩 이동하는 프로그램을 작성해 보자.

Device    : Atmega128-16AI
Clock     : 16MHz
개발 환경 : IAR EWAVR 2.28A
*******************************************************************************/

#include<mega128.h>  // ATMEGA128 IO REGISTER 정의
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

// 외부변수 선언 시작 //
int num = 0;
int i = 0; // 반목문을 위한 변수
int j = 0; // 비밀번호 카운트 체크
int gar = 0; // 방번호 받기 변수
int call = 0; // 리무브 이프문 함수 


      unsigned char key = 0xFF; // 키스캔 입력 받는 변수
      unsigned char room = 0xFF; //방번호
      unsigned char code = 0xFF; // 샾체크용
      unsigned char recheck = 0xFF; // 리무브 변수
      unsigned char recheck1 = 0xFF; // 리무브2 변수
      
      unsigned char pass[] = {1, 0, 0, 4, 10};  // 패스워드 변수
      //unsigned char pass2[] = {2, 5, 0, 0, 10};
      unsigned char pass3[] = {2, 1, 6, 5, 10};
      
      unsigned char input[] = {0, 0, 0, 0}; // 패스워드 받을 변수

// 외부변수 선언 종료 //

  
char KeyScan(void)
{
  char KeyBuf=0xFF;  // 키 값이 들어갈 버퍼, 초기값 0xFF

  PORTD=0x15;         // 포트 초기값, 입력핀 내부풀업저항 사용
  DDRD=0xAA;         // 비트0,1,2,3 출력으로 지정
                     
  PORTD.1=0; // 1번째 줄 선택
  if(!PIND.2)KeyBuf=1;
  if(!PIND.0)KeyBuf=2;
  if(!PIND.4)KeyBuf=3;
  PORTD.1=1; // 1번째 줄 해제

  PORTD.7=0; // 2번째 줄 선택
  if(!PIND.2)KeyBuf=4;
  if(!PIND.0)KeyBuf=5;
  if(!PIND.4)KeyBuf=6;
  PORTD.7=1; // 2번째 줄 해제

  PORTD.5=0; // 3번째 줄 선택
  if(!PIND.2)KeyBuf=7;
  if(!PIND.0)KeyBuf=8;
  if(!PIND.4)KeyBuf=9;
  PORTD.5=0; // 3번째 줄 해제

  PORTD.3=0; // 4번째 줄 선택
  if(!PIND.2)KeyBuf=11;
  if(!PIND.0)KeyBuf=0;
  if(!PIND.4)KeyBuf=10;
  PORTD.3=1; // 4번째 줄 해제

  return KeyBuf; // Key 없으면 0xFF 리턴
}

void Move1(void)
{
                                // B포트 E포트는 모터 동작 컨트롤 151 제어장치 
                                // A.0 A.1 A.2 는 y,x,z 순서의 JK 장치

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
                                //y축 jk연결                                   
                                PORTB = 0x7D;
                                PORTE = 0x00;
                                PORTA.0 = 1; 
                                delay_ms(8000);
                                PORTA.0 = 0;
                                delay_ms(1000);
                                
                                                                                               
                                //x축 가는거                                   
                                PORTB = 0x78;
                                PORTE = 0x00;
                                PORTA.1 = 1; 
                                delay_ms(6000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //z축  //가는거 
                                PWM1_ON; 	// 전자석 온
                                                     
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
                                
                                //x축                                   
                                PORTB = 0x00;
                                PORTE = 0x78;
                                PORTA.1 = 1; 
                                delay_ms(6000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //y축 jk연결                                   
                                PORTB = 0x00;
                                PORTE = 0x7D;
                                PORTA.0 = 1; 
                                delay_ms(8000);
                                PORTA.0 = 0;
                                delay_ms(1000);
                                
                                //z축
                                                                   
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                PWM1_OFF; // 전자석 오프
                                                                   
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
                                // B포트 E포트는 모터 동작 컨트롤 151 제어장치 
                                // A.0 A.1 A.2 는 y,x,z 순서의 JK 장치
 
                                //x축 가는거
                                PORTB = 0x40;
                                PORTE = 0x00;
                                PORTA.1 = 1; 
                                delay_ms(3000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //y축 jk연결                                   
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.0 = 1; 
                                delay_ms(5000);
                                PORTA.0 = 0;
                                delay_ms(1000);
                                                                                               
                                //x축 가는거                                   
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.1 = 1; 
                                delay_ms(5000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //z축  //가는거 
                                PWM1_ON; 	// 전자석 온
                                                     
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
                                
                                //x축 가는거                                   
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.1 = 1; 
                                delay_ms(5000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //y축 jk연결                                   
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.0 = 1; 
                                delay_ms(5000);
                                PORTA.0 = 0;
                                delay_ms(1000);
                                
                                //x축 가는거
                                PORTB = 0x00;
                                PORTE = 0x40;
                                PORTA.1 = 1; 
                                delay_ms(3000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //z축
                                                                   
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                PWM1_OFF; // 전자석 오프
                                                                   
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000); 

}   */
void Move3(void)
{
                                // B포트 E포트는 모터 동작 컨트롤 151 제어장치 
                                // A.0 A.1 A.2 는 y,x,z 순서의 JK 장치
                                
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
                                //x축 가는거                                   
                                PORTB = 0x78;
                                PORTE = 0x00;
                                PORTA.1 = 1; 
                                delay_ms(6000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //z축  //가는거 
                                PWM1_ON; 	// 전자석 온
                                                     
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
                                
                                //x축                                   
                                PORTB = 0x00;
                                PORTE = 0x78;
                                PORTA.1 = 1; 
                                delay_ms(6000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                        
                                
                                //z축
                                                                   
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                PWM1_OFF; // 전자석 오프
                                                                   
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
                for( i = 0; i < 5; i++ ) // A 포문 시작
                {
                        if( input[i] == pass[i] )
                        {
                                j++;
                        }
                } // A 포문 종료
                
                        if( j == 5 )
                        { // 이프문 시작 
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
                                        } //B 포문 종료
                        } // 이프문 종료
                        else
                        { // 엘스문 시작
                                PORTA.6 = 1;
                                PORTA.7 = 0;
                                delay_ms(1300);
                                PORTA.6 = 0;
                                PORTA.7 = 0;
                                delay_ms(500);

                                for( i = 0; i < 5; i++ ) // C 포문 시작
                                        {
                                                input[i] = 0;
                                                num = 0;
                                                j = 0;
                                                room = 0;
                                                code = 0;
                                        } // C 포문 종료
                        } // 엘스문 종료   
} /*
void Compare2(void)
{
                for( i = 0; i < 5; i++ ) // A 포문 시작
                {
                        if( input[i] == pass2[i] )
                        {
                                j++;
                        }
                } // A 포문 종료 
                
                        if( j == 5 ) // 이프문 시작
                        {      
                                PORTE.6 = 1; // 효과음 
                                PORTE.7 = 0;
                                delay_ms(300);
                                PORTE.6 = 0;
                                PORTE.7 = 0;
                                delay_ms(5);
                                
                                PORTA = 0x06;
                                Move2();
                                
                                PORTA = 0x6D;
                                
                                gar = room;
                                for( i = 0; i < 5; i++ ) // B 포문 종료
                                        {
                                                input[i] = 0;
                                                num = 0;
                                                j = 0;
                                                code = 0;
                                                room = 0;
                                        } //B 포문 종료
                        } // 이프문 종료
                        else
                        { // 엘스문 시작
                                PORTB.6 = 1; // 효과음 
                                PORTB.7 = 0;
                                delay_ms(1350);
                                PORTB.6 = 0;
                                PORTB.7 = 0;
                                delay_ms(100);
                                for( i = 0; i < 5; i++ ) // C 포문 시작
                                        {
                                                input[i] = 0;
                                                num = 0;
                                                j = 0;
                                                room = 0;
                                                code = 0;
                                        } // C 포문 종료
                        } // 엘스문 종료    
} */
void Compare3(void)
{
                for( i = 0; i < 5; i++ ) // A 포문 시작
                {
                        if( input[i] == pass3[i] )
                        {
                                j++;
                        }
                } // A 포문 종료 
                
                        if( j == 5 ) // 이프문 시작
                        {
                               PORTA.6 = 1;
                                PORTA.7 = 0;
                                delay_ms(300);
                                PORTA.6 = 0;
                                PORTA.7 = 0;
                                delay_ms(500);

                                Move3();
	 	                
                                gar = room;
                                for( i = 0; i < 5; i++ ) // B 포문 종료
                                        {
                                                input[i] = 0;
                                                num = 0;
                                                j = 0;
                                                code = 0;
                                                room = 0;
                                        } //B 포문 종료
                        } // 이프문 종료
                        else
                        { // 엘스문 시작
                                PORTA.6 = 1;
                                PORTA.7 = 0;
                                delay_ms(1300);
                                PORTA.6 = 0;
                                PORTA.7 = 0;
                                delay_ms(500);
                                
                                for( i = 0; i < 5; i++ ) // C 포문 시작
                                        {
                                                input[i] = 0;
                                                num = 0;
                                                j = 0;
                                                room = 0;
                                                code = 0;
                                        } // C 포문 종료
                        } // 엘스문 종료    
}  


void Remove1(void)
{  
                                                                 
                                                           
                                // B포트 E포트는 모터 동작 컨트롤 151 제어장치 
                                // A.0 A.1 A.2 는 y,x,z 순서의 JK 장치                                                     
                                //z축  //가는거
                                
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
                                 PWM1_ON; 	// 전자석 온
                                                     
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
                                
                                //y축 jk연결                                   
                                PORTB = 0x7D;
                                PORTE = 0x00;
                                PORTA.0 = 1; 
                                delay_ms(8000);
                                PORTA.0 = 0;
                                delay_ms(1000);
                                                                                               
                                //x축 가는거                                   
                                PORTB = 0x78;
                                PORTE = 0x00;
                                PORTA.1 = 1; 
                                delay_ms(6000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //z축  //가는거 
                                                                                     
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                PWM1_OFF;               //전자석 오프
                                                                  
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                //x축                                   
                                PORTB = 0x00;
                                PORTE = 0x78;
                                PORTA.1 = 1; 
                                delay_ms(6000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //y축 jk연결                                   
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
                // B포트 E포트는 모터 동작 컨트롤 151 제어장치 
                                // A.0 A.1 A.2 는 y,x,z 순서의 JK 장치

                                //z축  //가는거 
                                PWM1_ON; 	// 전자석 온
                                                     
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
                                
                                //x축 가는거
                                PORTB = 0x40;
                                PORTE = 0x00;
                                PORTA.1 = 1; 
                                delay_ms(3000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //y축 jk연결                                   
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.0 = 1; 
                                delay_ms(5000);
                                PORTA.0 = 0;
                                delay_ms(1000);
                                                                                               
                                //x축 가는거                                   
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.1 = 1; 
                                delay_ms(5000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //z축
                                                                   
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                PWM1_OFF; // 전자석 오프
                                                                   
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                //x축 가는거                                   
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.1 = 1; 
                                delay_ms(5000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                                
                                //y축 jk연결                                   
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.0 = 1; 
                                delay_ms(5000);
                                PORTA.0 = 0;
                                delay_ms(1000);
                                
                                //x축 가는거
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
                // B포트 E포트는 모터 동작 컨트롤 151 제어장치 
                                // A.0 A.1 A.2 는 y,x,z 순서의 JK 장치
                                
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
                                                                 
                                //z축  //가는거 
                                PWM1_ON; 	// 전자석 온
                                                     
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
                                                                                                                       
                                //x축 가는거                                   
                                PORTB = 0x78;
                                PORTE = 0x00;
                                PORTA.1 = 1; 
                                delay_ms(6000);
                                PORTA.1 = 0;
                                delay_ms(1000);
                               
                                //z축
                                                                   
                                PORTB = 0x70;
                                PORTE = 0x00;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);
                                
                                PWM1_OFF; // 전자석 오프
                                                                   
                                PORTB = 0x00;
                                PORTE = 0x70;
                                PORTA.2 = 1; 
                                delay_ms(5000);
                                PORTA.2 = 0;
                                delay_ms(1000);                                  
                                
                                //x축                                   
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
      
       MOTOR_DDR = 0xFF; // 모터 동작 위한 초기값
       ENABLE1_ON;       // 모터 동작 위한 초기값
       DDRB = 0xFE;
       PORTB = 0xFF;
       DDRE = 0xFF;
       PORTE = 0xFF;
       DDRF = 0xFF;
       DDRA = 0xFF;
       PORTA = 0xFF;
                        
        while(1) // A 와일 시작
        {      
                if(gar == 1 || gar == 2 || gar == 3) // Remove 시작
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
                              
                        while(1) // B 와일 시작
                        {
                                call = 0;
                                room = KeyScan();
                                if(room == 0x01||room==0x02||room==0x03) // 1, 2, 3 이프문 시작 
                                {
                                        delay_ms(500);
                                        while(1) // C 와일문 시작
                                        {
                                                code = KeyScan();                           
                                                if(code==10) // #키스캔 이프문 시작
                                                {
                                                        delay_ms(500);
                                                        while(1) // D 와일문 시작
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
                                                        } // D 와일문 종료 
                                                } // #키스캔 이프문 종료
                                                if( num == 5)
                                                {
                                                        break;
                                                }              
                                        } // C 와일문 종료        
                                } // 1, 2, 3 이프문 종료
                        
                                if( num == 5)
                                {
                                        break;
                                } 
                        } // B와일 종료 
               
                        // 체크 시작
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

        
         



