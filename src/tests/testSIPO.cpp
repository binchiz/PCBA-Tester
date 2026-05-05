#include "testSIPO.h"

void sendByte(int byte, int dataPin, int clockPin, int latchPin){
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, byte);
    digitalWrite(latchPin, HIGH);
}

TestResult testSIPO(int dataPin, int clockPin, int latchPin, int enablePin, int resetPin, int output, int numBits){
    TestResult result;
    result.test_name = "SIPO Test";
    result.passed = false; 
    result.details = "";

    //sum for successful tests
    int sum = 0;

    //initialization of different pins
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(enablePin, OUTPUT);
    pinMode(resetPin, OUTPUT);

    //enable enablePin and disable reset pin
    digitalWrite(enablePin, LOW); 
    digitalWrite(resetPin, HIGH);


    //testing each led separately
    for(int i = 0; i < numBits; ++i){
        int val = 1 << i;
        sendByte(val,dataPin,clockPin,latchPin);
        delay(100);

        float voltage = analogRead(output) * adcVoltageFactor;
        result.details += "Single test: Number " + String(i);
        if(voltage > 2.0 && voltage < 3.0){
            result.details += " OK. ";
            ++sum;
        }else{
            result.details += " Not OK. ";
        }
        result.details += "Voltage: " + String(voltage) + "\n";
    }

    //testing all on
    sendByte((1 << numBits) - 1,dataPin,clockPin,latchPin);
    delay(100);
    float voltage = analogRead(output) * adcVoltageFactor;
    result.details += "ALL ON test ";
    if(voltage > 2.5 && voltage < 3.5){
        result.details += "OK. ";
        ++sum;
    }else{
        result.details += "Not OK. ";
    }
    result.details += "Voltage: " + String(voltage) + "\n";

        //testing all off
    sendByte(0,dataPin,clockPin,latchPin);
    delay(100);

    voltage = analogRead(output) * adcVoltageFactor;
    result.details += "ALL OFF test ";
    if(voltage < 2.0){
        result.details += "OK. ";
        ++sum;
    }else{
        result.details += "Not OK. ";
    }
    result.details += "Voltage: " + String(voltage) + "\n";


    if(sum == (numBits + 2)){
        result.passed = true;
    }

    return result;
}