#include "tile.h"
#include "testMenu.h"
#include "constants.h"
#include "Arduino.h"
#include "connect_4.h"

char* testMenuOptions[] = {
  "Skip Test",
  "Test Entire Board",
  "Test Entire Row",
  "Test Entire Column",
  "Test Individual Tile",
  "Read Column Switches",
  "Read Start/Reset Switch",
  "Read AI Switch",
  "Turn on indicator for white",
  "Turn on indicator for green"
};

int option = -1;

/*
 * Print out the menu and parses for a response. 
 * This function is in an infinite loop unless the user manually enters
 * the option to quit
 */
void runTestMenu(){
  printTestMenu();
  while(option != 0){
    parseResponse();  
  }
  Serial.println("Exiting Test");
}

/*
 * Prints out the options based on the array defined at the top. 
 */
void printTestMenu(){
  Serial.println("----------Connect 4 x100 Boot Menu-----------");
  for(int i=0; i<5; i++){
    char option[100]; 
    sprintf(option, "%i - %s", i, testMenuOptions[i]);
    Serial.println(option);
  }
  Serial.println("---------------------------------------------");
}

/*
 * Parses the option the user selects. The number associated to the menu option 
 * are based on the order in which the options are in the array 
 */
void parseResponse(){ 
  Serial.print("> ");
  
  while(Serial.available() <= 0){
  }

  option = Serial.read();
  Serial.println((char) option);
  switch ((char) option){
    case '0':
      Serial.println("Quitting...");
      break;
    case '1':
      break;
    case '2':
      break;
    case '3':
      break;
    case '4':
      break;
    default:
      Serial.println("Invalid option entered");
      break;
  }
}

void testBoard(){
  for(int row = 0; row < ROWS; row++){
    testRow(row); 
  }
}

void testRow(int row){
  for(int column = 0; column < COLUMNS; column++){
     testTile(row, column); 
  }
}

void testColumn(int column){
  for(int row = 0; row < ROWS; row++){
    testTile(row, column); 
  }
}

void testTile(int row, int col){
  Tile tile = TILES_ARRAY[row][col];
  tile.setColour(WHITE);
  delay(500);
  tile.setColour(NO_COLOUR);
  delay(500);
  tile.setColour(GREEN);
  delay(500);
}

int testSwitch(int *buttonObj){
  return switchToggled(buttonObj[0], &buttonObj[1], &buttonObj[2]) ? 1 : 0;
}

void voidSwitchResult(bool isMultiple, bool isReset){
  Serial.print("This will print out when the switch transitioned from 0->1 over the span of 10 seconds");

  unsigned long endTime = millis() + 10000;
  while( millis() < endTime){
    int *result;

    if(isMultiple){
      int value[] = {
        testSwitch(columnButtons[0]), testSwitch(columnButtons[1]), 
        testSwitch(columnButtons[2]), testSwitch(columnButtons[3]), 
        testSwitch(columnButtons[4]), testSwitch(columnButtons[5]), 
        testSwitch(columnButtons[6]), 
      };

      result = value;
    } else {
      int value[] = {
        testSwitch(startResetButton), testSwitch(AIButton), 
        -1, -1, -1, -1, -1
      };
      result = value; 
    }

    char option[100]; 
    sprintf(option, "%d -%d -%d -%d -%d -%d -%d", result[0], result[1], result[2],
    result[3], result[4], result[5], result[6]);
    Serial.println(option);
  }
}

void turnOnGreen(){
  Serial.println("Turning on green");
  displayTurn(GREEN);
  delay(1000);
  digitalWrite(PLAYER_G_INDICATOR_PIN, LOW); 
}

void turnOnWhite(){
  Serial.println("Turning on white");
  displayTurn(WHITE);
  delay(1000);
  digitalWrite(PLAYER_W_INDICATOR_PIN, LOW); 
}

