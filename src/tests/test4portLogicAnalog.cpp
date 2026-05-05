#include "test4portLogicAnalog.h"

TestResult test4portLogicAnalog(int powerPin, int powerPolarity, int input1, int input2, int input3, int input4, int output, int numberofHigh, float targetMin, float targetHigh){
    TestResult result;
    result.test_name = "4 Port Logic Analog";
    result.passed = false;
    result.details = "";

    //initialize 4 input pins and 1 output pin
    pinMode(input1, OUTPUT);
    pinMode(input2, OUTPUT);
    pinMode(input3, OUTPUT);
    pinMode(input4, OUTPUT);
    pinMode(output, INPUT);

    //power on the circuit
    if(powerPolarity != -1){
        pinMode(powerPin,OUTPUT);
        digitalWrite(powerPin,powerPolarity);
        delay(10);
    }

    int count = 0;
    for (int i= 0; i < 16; ++i){
        int inp1 = (i >> 3) & 1;
        int inp2 = (i >> 2) & 1;
        int inp3 = (i >> 1) & 1;
        int inp4 = i & 1;

        digitalWrite(input1,inp1);
        digitalWrite(input2,inp2);
        digitalWrite(input3,inp3);
        digitalWrite(input4,inp4);
        delay(10);

        //convert analog reading to voltage
        float voltageVal = analogRead(output) * adcVoltageFactor;
        bool readHigh = (voltageVal >= targetHigh);
        bool readLow = (voltageVal <= targetMin);
        bool middleValue = (!readHigh && !readLow);
        if (readHigh) count++;

        result.details += "Inp1: "; 
        result.details += inp1; 
        result.details += ", Inp2: "; 
        result.details += inp2; 
        result.details += ", Inp3: "; 
        result.details += inp3; 
        result.details += ", Inp4: "; 
        result.details += inp4; 
        result.details += ", Output voltage: "; 
        result.details += voltageVal;
        if(readHigh) result.details += ", HIGH ";
        if(readLow) result.details += ", LOW ";
        if(middleValue) result.details += ", NOT IN RANGE ";
        if(i < 15) result.details += "\n";
    }

    result.passed = (count == numberofHigh);

    if(powerPolarity != -1){
        digitalWrite(powerPin, !powerPolarity);
    }

    return result;
}