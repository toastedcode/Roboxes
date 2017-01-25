#pragma once

#include "BlynkSimpleEsp8266.h"

class BlinkLCD
{

public:

   BlinkLCD();

   BlinkLCD(
      const int& virtualPin);

   ~BlinkLCD();

   void attach(
      const int& virtualPin);

   void clear();

   void printf();

   void println();

   void print();

   void printAt();

   int getRow();

   int getColumn();

   static const int MAX_COLUMNS = 15;

   static const int MAX_ROWS = 1;

private:

   void refresh();

};
