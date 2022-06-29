#ifndef _SIM800L_H_
#define _SIM800L_H_

#include <Arduino.h>


// If using software serial
#ifndef SoftwareSerial_h
#include <SoftwareSerial.h>
#endif

#define SIM800L_COMM_BUF_SIZE 32
#define SIM800L_READ_BUF_SIZE 256
#define SIM800L_READ_CHAR_TIMEOUT 50    // single char read timeout (ms)

#define DEBUG

#ifdef DEBUG 
#define DEBUG_PRINT(a) Serial.println(a);
#else
#define DEBUG_PRINT(a)
#endif

class SIM800L
{
public:
    SIM800L(){}

    void begin(SoftwareSerial* simModule, void (*rstFunc)(void));

    void run();

    void printBuffer();

    ~SIM800L(){}

private:
    unsigned long timeout = 12000L;  // Default timeout (12000ms)

    SoftwareSerial *sim_module = NULL;

    void (*resetCallback)(void) = NULL; // Reset callback

    char buffer[SIM800L_READ_BUF_SIZE];
    unsigned int bufferSize = 0;

    void printAndWaitOK(const __FlashStringHelper * msg); // Print null-terminated string and wait for OK response

    char* read_module_bytes(size_t nbytes, char terminator); // read n bytes from module or until terminator has been found
};


#endif