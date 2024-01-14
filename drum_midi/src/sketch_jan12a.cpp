// /*
// int inPin = A0;
// int sw = 2;
// int led = 3;
// bool i = false;
// bool activated = false;
// long t = 0;
// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);
//   pinMode(inPin,INPUT);
//   pinMode(sw,INPUT);
//   pinMode(led,OUTPUT);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
// //  if(activated)
// //    digitalWrite(led,HIGH);
// //  else
// //    digitalWrite(led,LOW);

//   if(digitalRead(sw)==1){
//     int val = analogRead(inPin);
//     if(val>850&&i==false)
//     {
//       long tnew = millis();
//       i=true;    
//       if((tnew-t)>90){
//          Serial.println((tnew-t));
//          t = tnew;
//       }
//     }
//     else if(val<750&&i==true)
//     {
//       //Serial.println(micros());
//       //Serial.print("low");
//       //Serial.println(val);
//       i=false;    
//     }
//   }
//  ;

// }
// */

// int inPinA = A0;
// int inPinB = A3;
// int sw = 2;
// int led = 3;
// bool iA = false;
// bool iB = false;
// bool activated = false;
// long tA = 0;
// long tB = 0;
// int instrNum = 0;
// int maxInstr = 2;
 
// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);
//   pinMode(inPinA,INPUT);
//   pinMode(inPinB,INPUT);
//   pinMode(sw,INPUT);
//   pinMode(led,OUTPUT);

// }

// void loop() {
//   // put your main code here, to run repeatedly:
// //  if(activated)
// //    digitalWrite(led,HIGH);
// //  else
// //    digitalWrite(led,LOW);

//   if(digitalRead(sw)==1){
//     int valA = analogRead(inPinA);
//     if(valA>850&&iA==false)
//     {
//       long tnewA = millis();
//       iA=true;
//       if((tnewA-tA  )>90){
//          Serial.print(1);
//          Serial.println((tnewA-tA));
//          tA = tnewA;
//       }
//     }
//     else if(valA<750&&iA==true)
//     {
//       //Serial.println(micros());
//       //Serial.print("low");
//       //Serial.println(val);
//       iA=false;
//     }

//     int valB = analogRead(inPinB);
//     if(valB>850&&iB==false)
//     {
//       long tnewB = millis();
//       iB=true;
//       if((tnewB-tB)>90){
//          Serial.print(2);
//          Serial.println((tnewB-tB));
//          tB = tnewB;
//       }
//     }
//         else if(valB<750&&iB==true)
//     {
//       //Serial.println(micros());
//       //Serial.print("low");
//       //Serial.println(val);
//       iB=false;
//     }
//   }
// }
