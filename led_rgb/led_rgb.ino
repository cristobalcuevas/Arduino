const byte r = 6;
const byte g = 5;
const byte b = 3; 

typedef struct{
  byte red;
  byte green;
  byte blue; 
}RGB; 

RGB rgb = {255, 255, 255}; 

//Function prototype
void setColor(RGB color);
void setup() {
  pinMode(r,OUTPUT); 
  pinMode(g,OUTPUT); 
  pinMode(b,OUTPUT); 
} 

void loop() { 
  setColor(rgb); 
} 

void setColor(RGB color){
  analogWrite(r,color.red);
  analogWrite(g,color.green);
  analogWrite(b,color.blue); 
}
