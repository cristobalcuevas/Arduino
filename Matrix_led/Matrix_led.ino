/*
 * Archivo: Matrix_led.ino
 * Autor: Cristobal Cuevas
 * Comentarios: Make a effect  with matrix led
 * Fecha: 09-05-2019
 *
 */
int R[] = {2,7,A5,5,13,A4,12,A2};
int C[] = {6,11,10,3,A3,4,8,9};
unsigned char biglove[8][8] =
{
  0,0,0,0,0,0,0,0,
  0,1,1,0,0,1,1,0,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,0,
  0,0,1,1,1,1,0,0,
  0,0,0,1,1,0,0,0,
};  
unsigned char smalllove[8][8] =
{
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,1,0,0,1,0,0,
  0,1,1,1,1,1,1,0,
  0,1,1,1,1,1,1,0,
  0,0,1,1,1,1,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,0,0,0,0,0,
};
void setup()
{
  for(int i = 0;i<8;i++)
  {
    pinMode(R[i],OUTPUT);
    pinMode(C[i],OUTPUT);
  }
}
void loop()
{
  for(int i = 0 ; i < 100 ; i++)
  {
    Display(biglove);
  }
  for(int i = 0 ; i < 50 ; i++)
  {
    Display(smalllove);
  }
}
void Display(unsigned char dat[8][8])
{
  for(int c = 0; c<8;c++)
  {
    digitalWrite(C[c],LOW);
    for(int r = 0;r<8;r++)
    {
      digitalWrite(R[r],dat[r][c]);
    }
    delay(1);
    Clear();
  }
}
void Clear()
{
  for(int i = 0;i<8;i++)
  {
    digitalWrite(R[i],LOW);
    digitalWrite(C[i],HIGH);
  }
}
