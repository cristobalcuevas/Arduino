// how long does it take to print something on the serial line ?

#define SERIAL_BAUD_RATE 115200


const char* t1_desc = "stampa un carattere";
void t1(void) {
    Serial.print("a");
}


const char* t5_desc = "stampa 5 caratteri";
void t5(void) {
    Serial.print("01234");
}


const char* t10_desc = "stampa 10 caratteri";
void t10(void) {
    Serial.print("0123456789");
}


const char* t20_desc = "stampa 20 caratteri";
void t20(void) {
    Serial.print("01234567890123456789");
}


void timeThis(void (*f)(void), const char* test_name, unsigned int times = 1) {
    unsigned long duration;
    float total;

    total = 0;
    duration = 0;
    for (unsigned int i = 0; i < times; i++) {
        duration = micros();
        f();
        duration = micros() - duration;
        total += duration;
    }
    
    if (times > 1) {
        total /= (float)times;
    }
    
    Serial.println("");
    Serial.print(test_name);
    Serial.print('(');
    Serial.print(times);
    Serial.print("): ");
    Serial.print(total);
    Serial.println("us");
}


void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.print("Serial speed: ");
    Serial.println(SERIAL_BAUD_RATE, DEC);
    
    timeThis(t1, t1_desc, 100);
    timeThis(t5, t5_desc, 100);
    timeThis(t10, t10_desc, 100);
    timeThis(t20, t20_desc, 100);
}


void loop() {
}
