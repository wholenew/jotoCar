#include <Servo.h>
#include <Wire.h>

#define R_PWM 11
#define R_IN1 5
#define R_IN2 6
#define L_PWM 10
#define L_IN1 2
#define L_IN2 4
#define STEERING_PWM 9


int SLAVE_ADDRESS = 0x04;   //I2Cのアドレス『0x04』
Servo servo;
byte value=0;
int r_pwm = 250;
int l_pwm = 250;
int steering = 0;
int stopFlag=0;

void setup() {
   Serial.begin(9600);
   //I2C接続を開始する 
   Wire.begin(SLAVE_ADDRESS);
  
    //I2Cで受信したときに呼び出す関数を登録する
   Wire.onReceive(ReceiveMassage); 
  
    //I2Cでリクエスト受信したときに呼び出す関数を登録する 
   Wire.onRequest(RequestMassage);
   
   pinMode(R_IN1, OUTPUT);
   pinMode(L_IN1, OUTPUT);
   pinMode(R_IN2, OUTPUT);
   pinMode(L_IN2, OUTPUT);
   pinMode(R_PWM, OUTPUT);
   pinMode(L_PWM, OUTPUT); 
   pinMode(STEERING_PWM, OUTPUT); 
   
   servo.attach(STEERING_PWM);
   servo.write(28);//右2中央28左53
   delay(3000);
}

void loop() {
    switch(value){
      case 'f':
        steering = 28; //右2中央28左53
        l_pwm = 250; //大きいほど強くなる
        r_pwm = 250;
  
        //左正転
        digitalWrite(L_IN1, HIGH);
        digitalWrite(L_IN2, LOW);
//        digitalWrite(L_PWM, HIGH);
//        analogWrite(L_PWM, l_pwm);
        //右正転
        digitalWrite(R_IN1, HIGH);
        digitalWrite(R_IN2, LOW);
//        digitalWrite(R_PWM, HIGH);
//        analogWrite(R_PWM, r_pwm);
        break;
        
      case 'b':
        steering = 28; //右2中央28左53
        l_pwm = 10; //小さいほど強くなる
        r_pwm = 10;
  
        //左正転
        digitalWrite(L_IN1, LOW);
        digitalWrite(L_IN2, HIGH);
//        digitalWrite(L_PWM, LOW);
//        analogWrite(L_PWM, l_pwm);
        //右正転
        digitalWrite(R_IN1, LOW);
        digitalWrite(R_IN2, HIGH);
//        digitalWrite(R_PWM, LOW);
//        analogWrite(R_PWM, r_pwm);

        break;
        
      case 'r':
        steering = 5; //右2中央28左53
        l_pwm = 0;
        r_pwm = 0; //小さいほど強くなる

        //左正転
        digitalWrite(L_IN1, HIGH);
        digitalWrite(L_IN2, LOW);
//        digitalWrite(L_PWM, HIGH);
//        analogWrite(L_PWM, l_pwm);
        //右正転
        digitalWrite(R_IN1, HIGH);
        digitalWrite(R_IN2, LOW);
//        digitalWrite(R_PWM, HIGH);
//        analogWrite(R_PWM, r_pwm);
        break;
        
      case 'l':
        steering = 53; ////右2中央28左53
        l_pwm = 0; //小さいほど強くなる
        r_pwm = 0;

        //左正転
        digitalWrite(L_IN1, HIGH);
        digitalWrite(L_IN2, LOW);
//        digitalWrite(L_PWM, HIGH);
//        analogWrite(L_PWM, l_pwm);
        //右正転
        digitalWrite(R_IN1, HIGH);
        digitalWrite(R_IN2, LOW);
//        digitalWrite(R_PWM, HIGH);
//        analogWrite(R_PWM, r_pwm);
        break;

      case 's':
        brake();
    }
    servo.write(steering);
    delay(10);
}

// ブレーキ
void brake() {
  digitalWrite(L_IN1, LOW);
  digitalWrite(L_IN2, LOW);
//  digitalWrite(L_PWM, HIGH);
  
  digitalWrite(R_IN1, LOW);
  digitalWrite(R_IN2, LOW);
//  digitalWrite(R_PWM, HIGH);

}

/*setupの後、終了するまで繰り返し呼び出される関数です*/
void ReceiveMassage(int n){
  char cmd = Wire.read();     //文字を読む
  Serial.println(cmd);       //シリアルポートにcmdを出力し表示する
  value=cmd;
}

//リクエスト要求を受けたときに「A」を送信する。
void RequestMassage(){
//  Wire.write("A");            //Aを送信
}
