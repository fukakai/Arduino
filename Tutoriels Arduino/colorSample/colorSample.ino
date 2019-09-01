/**
* 
* @Author: Fukakai - Mohorelien
* 06.06.2013
* Ping, servo, led and directions
*
*/

//color sensor declarations
int s0=3;                          //color sensor
int s1=4;                          //color sensor
int s2=5;                          //color sensor
int s3=6;                          //color sensor
int flag=0;
int counter=0;
int countR=0,countG=0,countB=0;

//for ISR void method
int i=0;

void setup(){
  Serial.begin(115200);
  pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT); 
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
}

void loop(){
   delay(10);
   TCS();
   if((countR > 15)||(countG > 15)||(countB > 15)){      // On capte au moins une couleur
     if((countR >= 18) && (countG >= 18) && (countB >= 18)){    // Beaucoup de chaque couleur = Blanc
       Serial.println("----------> BLANC");
       delay(500);
     }
     else if((countR > countG) && (countR > countB)){    // Majorité de Rouge
       Serial.println("----------> ROUGE");        
       delay(500);
     }
     else if((countG >= countR) && (countG > countB)){   // Majorité de Vert
       Serial.println("----------> VERT");         
       delay(500);
     }
     else if((countB > countG) && (countB > countR)){    // Majorité de Bleu
       Serial.println("----------> BLEU");         
       delay(500);
     }
     else{
       Serial.println("BORDEL À CUL!");
       delay(500);       
     }
   }
   else if((countR <= 15) && (countB <= 15) && (countG <= 15)){  // On capte peu de couleurs = Noir
     Serial.println("----------> NOIR");      
     delay(500);
   }
   else{
      delay(500);
   }
}

void TCS(){
  digitalWrite(s1, HIGH);
  digitalWrite(s0, LOW);
  flag=0;
  attachInterrupt(0, ISR_INTO, CHANGE);
  timer2_init();
}

void ISR_INTO(){
  counter++;
}

void timer2_init(void){
  TCCR2A=0x00;
  TCCR2B=0x07;   //the clock frequency source 1024 points
  TCNT2= 100;    //10 ms overflow again
  TIMSK2 = 0x01; //allow interrupt
}
  
ISR(TIMER2_OVF_vect){//the timer 2, 10ms interrupt overflow again. Internal overflow interrupt executive function
  TCNT2=100;
  flag++;
  
  if(flag==1){
     counter=0;
  }else if(flag==2){
     digitalWrite(s2,LOW);
     digitalWrite(s3,LOW); 
     countR=counter/1.051;
     Serial.print("red=");
     Serial.println(countR,DEC);
     digitalWrite(s2,HIGH);
     digitalWrite(s3,HIGH);   
  }else if(flag==3){
    countG=counter/1.0157;
    Serial.print("green=");
    Serial.println(countG,DEC);
    digitalWrite(s2,LOW);
    digitalWrite(s3,HIGH); 
  }else if(flag==4){
    countB=counter/1.114;
    Serial.print("blue=");
    Serial.println(countB,DEC);
    digitalWrite(s2,LOW);
    digitalWrite(s3,LOW);
  }else{
    flag=0; 
    TIMSK2 = 0x00;
  }
  counter=0;
  delay(2);
}
