#include <TimerOne.h>

#define PWM_PIN 10
#define ANALOG_PIN 9
#define PWM_RESOLUTION 8
#define BAUD_RATE 1000000

int PWM_MAX = 1.0*pow(2,PWM_RESOLUTION);
double IDEAL_PWM_FREQ = F_BUS/pow(2,PWM_RESOLUTION);

int freqs[8] = {9375/2, 9375, 0, 0, 0, 0, 0, 0};
int avg_val = 0;
int cur_val = 0;
double alpha = 0.01;
double sfreq = 1.0;
unsigned long curr_time = 0;
unsigned long analog_read_time = 0;
unsigned long freq = IDEAL_PWM_FREQ;
void setup() {
  // setup PWM
  analogWriteResolution(PWM_RESOLUTION);
  analogWriteFrequency(PWM_PIN,IDEAL_PWM_FREQ);
  analogWrite(PWM_PIN, (int)PWM_MAX/2);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  Serial.begin(BAUD_RATE);
  curr_time = millis();
  analog_read_time = micros();
}

void loop(){
  //int angle = (int)(PWM_MAX*(0.35*sin(2*PI*freqs[0]*micros()*1000000)+0.5));
  //analogWrite(PWM_PIN, angle);
  if (millis() - curr_time > 100){
    curr_time = millis();

    //Serial.print("Avg on analog 0 is: ");
    //Serial.println(avg_val);
    
    Serial.println(sfreq);
  }

  sfreq = 1000000.0/(micros() - analog_read_time);
  analog_read_time = micros();
  cur_val = analogRead(ANALOG_PIN);
  avg_val = (int) ( ((float)cur_val*alpha) + ((float)avg_val*(1-alpha)) );
  
}
