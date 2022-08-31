/*
 * Archivo: Function_generator.ino
 * Autor: Cristobal Cuevas
 * Comentarios: Led RGB with classes
 * Fecha: 10-02-2021
 *
 */
void setup() {
Serial.begin(9600);
}
void loop(){
/**************** Onda Seno y Coseno ***************/
  float angle=0;
  for(angle=0;angle<=90;angle=angle+0.1){
    float sina=sin(angle);
    float cosa=cos(angle);
    Serial.print(sina);
    Serial.print("\t");
    Serial.println(cosa);
    delay(1);
  }
/***************** Diente de Sierra ****************/
  for(float i=0; i<=90; i=i+1){
    Serial.println(i);
    delay(1);
  }
/****************** Onda Cuadrada ******************/
  for(int a=0; a<=100; a++){
    int b=0;
    Serial.println(b);
    delay(1);  
  }
  for(int a=0; a<=100; a++){
    int b=100;
    Serial.println(b);
    delay(1);  
  }
/***************** Onda Triangular *****************/
  for(float i=0;i<=100;i=i+1){
    Serial.println(i);
    delay(1);
  }
  for(float i=100;i>=0;i=i-1){
    Serial.println(i);
    delay(1);  
  }
}
