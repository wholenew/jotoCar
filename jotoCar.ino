#include <Servo.h>
#include <Wire.h>

#define R_PWM 6
#define R_IN 12
#define L_PWM 5
#define L_IN 13
#define STEERING_PWM 3


int SLAVE_ADDRESS = 0x04;   //I2Cのアドレス『0x04』
Servo servo;
byte value=0;
int r_pwm = 250;
int l_pwm = 250;
int steering = 0;

void setup() {
   Serial.begin(9600);
   //I2C接続を開始する 
   Wire.begin(SLAVE_ADDRESS);
  
    //I2Cで受信したときに呼び出す関数を登録する
   Wire.onReceive(ReceiveMassage); 
  
    //I2Cでリクエスト受信したときに呼び出す関数を登録する 
   Wire.onRequest(RequestMassage);
   
   pinMode(R_IN, OUTPUT);
   pinMode(L_IN, OUTPUT);
   pinMode(R_PWM, OUTPUT);
   pinMode(L_PWM, OUTPUT); 
   pinMode(STEERING_PWM, OUTPUT); 
   
   servo.attach(STEERING_PWM);
   servo.write(28);//右2中央28左53
   delay(3000);
}

void loop() {
  if(Serial.available()>0){
    value = Serial.read();
    
    switch(value){
      case 'forward':
        steering = 28; //右2中央28左53
        l_pwm = 220;
        r_pwm = 220;
  
        //左正転
        digitalWrite(L_IN, LOW);
        analogWrite(L_PWM, l_pwm);
  
        //右正転
        digitalWrite(R_IN, LOW);
        analogWrite(R_PWM, r_pwm);

        break;
      case 'back':
        steering = 28; //右2中央28左53
        l_pwm = 220;
        r_pwm = 220;
  
        //左後転
        digitalWrite(L_IN, HIGH);
        analogWrite(L_PWM, l_pwm);
  
        //右後転
        digitalWrite(R_IN, HIGH);
        analogWrite(R_PWM, r_pwm);

        break;
        
      case 'right':
        steering = 5; //右2中央28左53
        l_pwm = 200;
        r_pwm = 125; //小さいほど強くなる

        //左正転
        digitalWrite(L_IN, LOW);
        analogWrite(L_PWM, l_pwm);
        //右停止
        digitalWrite(R_IN, HIGH);
        digitalWrite(R_PWM, HIGH);
        break;
        
      case 'left':
        steering = 53; ////右2中央28左53
        l_pwm = 125; //小さいほど強くなる
        r_pwm = 200;

        //左ブレーキ
        digitalWrite(L_IN, HIGH);
        digitalWrite(L_PWM, HIGH);
  
        //右正転
        digitalWrite(R_IN, LOW);
        analogWrite(R_PWM, r_pwm);
        break;
    }

    servo.write(steering);
    delay(1);
  }else{
    brake();
  }
}

// ブレーキ
void brake() {
  digitalWrite(L_IN, HIGH);
  digitalWrite(L_PWM, HIGH);
  digitalWrite(R_IN, HIGH);
  digitalWrite(R_PWM, HIGH);

}

/*setupの後、終了するまで繰り返し呼び出される関数です*/
void ReceiveMassage(int n){
  char cmd = Wire.read();     //文字を読む
  Serial.println(cmd);       //シリアルポートにcmdを出力し表示する
}

//リクエスト要求を受けたときに「A」を送信する。
void RequestMassage(){
  Wire.write("A");            //Aを送信
}
