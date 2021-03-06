//todo: 
/*
 * 
 * get on the screen the total games played for each person 
 * save the stuff to the memory
 * actually calculate the averages
 */


 //should i have a total win and win percent array to make things easier to calculate?? probably lets do that
#include <LiquidCrystal.h>
#include <HashMap.h>
#include <IRremote.h>
#include <EEPROM.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 6;
const byte HASHSIZE = 8;
const byte IR_RECEIVE_PIN = 2;


enum Person {
  Jack, Chris, Mason, Will, Evan, Nick, Declan, Mehdi
};

enum Stat {
  AverageCups, Wins
};


String cupsMade = "-1";


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

HashType<Person, float> hashRawArray[HASHSIZE];
HashType<Person, float> hashRawArray2[HASHSIZE];
HashType<Person, int> hashRawArray3[HASHSIZE]; 
HashType<Person, float> hashRawArray4[HASHSIZE];
HashType<Person, float> hashRawArray5[HASHSIZE];

HashMap<Person, float> wins = HashMap<Person, float>(hashRawArray, HASHSIZE);
HashMap<Person, float> avgCups = HashMap<Person, float>(hashRawArray2, HASHSIZE);
HashMap<Person, int> gamesPlayed = HashMap<Person, int>(hashRawArray3, HASHSIZE);
HashMap<Person, float> winPercentage = HashMap<Person, float>(hashRawArray4, HASHSIZE);
HashMap<Person, float> totalCups = HashMap<Person, float>(hashRawArray5, HASHSIZE);




Person currPlayer = Jack;
Stat currStat = Wins;


Person findNextPlayer(Person currPlayer) {

  switch (currPlayer) {
    case Jack:
      return Chris;
    case Chris:
      return Mason;
    case Mason:
      return Will;
    case Will:
      return Evan;
    case Evan:
      return Nick;
    case Nick:
      return Declan;
    case Declan:
      return Mehdi;
    case Mehdi:
      return Jack;
    default:
      return Jack;
  }

}


Person findPrevPerson(Person currPlayer) {

  switch (currPlayer) {
    case Jack:
      return Mehdi;
    case Mehdi:
      return Declan;
    case Declan:
      return Nick;
    case Nick:
      return Evan;
    case Evan:
      return Will;
    case Will:
      return Mason;
    case Mason:
      return Chris;
    case Chris:
      return Jack;
    default:
      return Jack;
  }

}

String evalEnum2(Stat s) {

  switch (s) {
    case Wins:
      return "Wins: ";
    case AverageCups:
      return "Average Cups: ";
    default:
      return "No Stat Selected";
  }

}

String evalEnum(Person p) {

  switch (p) {
    case 0:
      return "Jack";
    case 1:
      return "Chris";
    case 2:
      return "Mason";
    case 3:
      return "Will";
    case 4:
      return "Evan";
    case 5:
      return "Nick";
    case 6:
      return "Declan";
    case 7:
      return "Mehdi";
    default:
      return "err";
  }

}

void displayCorrectInformation(Person p) {

  lcd.clear();
  String person = evalEnum(p) + ":"; 
  String averageCups = (String)avgCups.getValueOf(p);
  String winNum = (String)winPercentage.getValueOf(p);
  String tPlayed = (String)gamesPlayed.getValueOf(p);
  lcd.print(person);
  lcd.setCursor(person.length()+1, 0);
  lcd.print("Cups:" + averageCups);
  lcd.setCursor(0, 1);
  lcd.print("Wins:" + winNum);
  lcd.setCursor(12, 1); 
  lcd.print("T:" + tPlayed);

  
}


enum Command {
  NEXTPERSON = 67, PREVPERSON = 68, SELECT = 64, NEXTSTAT = 70, PREVSTAT = 21
};

int cursorPosX = 0;

void setup() {

  lcd.begin(16, 2);
  
  wins[0](Jack, EEPROM.read(0));
  wins[1](Chris, EEPROM.read(1));
  wins[2](Mason, EEPROM.read(2));
  wins[3](Will, EEPROM.read(3));
  wins[4](Evan, EEPROM.read(4));
  wins[5](Nick, EEPROM.read(5))
  wins[6](Declan, EEPROM.read(6));
  wins[7](Mehdi, EEPROM.read(7));

  avgCups[0](Jack, EEPROM.read(8));
  avgCups[1](Chris, EEPROM.read(9));
  avgCups[2](Mason, EEPROM.read(10));
  avgCups[3](Will, EEPROM.read(11));
  avgCups[4](Evan, EEPROM.read(12));
  avgCups[5](Nick, EEPROM.read(13));
  avgCups[6](Declan, EEPROM.read(14));
  avgCups[7](Mehdi, EEPROM.read(15));

  gamesPlayed[0](Jack, EEPROM.read(16));
  gamesPlayed[1](Chris, EEPROM.read(17));
  gamesPlayed[2](Mason, EEPROM.read(18));
  gamesPlayed[3](Will, EEPROM.read(19));
  gamesPlayed[4](Evan, EEPROM.read(20));
  gamesPlayed[5](Nick, EEPROM.read(21));
  gamesPlayed[6](Declan, EEPROM.read(22));
  gamesPlayed[7](Mehdi, EEPROM.read(23));

  winPercentage[0](Jack, EEPROM.read(24));
  winPercentage[1](Chris, EEPROM.read(25));
  winPercentage[2](Mason, EEPROM.read(26));
  winPercentage[3](Will, EEPROM.read(27));
  winPercentage[4](Evan, EEPROM.read(28));
  winPercentage[5](Nick, EEPROM.read(29));
  winPercentage[6](Declan, EEPROM.read(30));
  winPercentage[7](Mehdi, EEPROM.read(31));

  totalCups[0](Jack, EEPROM.read(32));
  totalCups[1](Chris, EEPROM.read(33));
  totalCups[2](Mason, EEPROM.read(34));
  totalCups[3](Will, EEPROM.read(35));
  totalCups[4](Evan, EEPROM.read(36));
  totalCups[5](Nick, EEPROM.read(37));
  totalCups[6](Declan, EEPROM.read(38));
  totalCups[7](Mehdi, EEPROM.read(39));


  Serial.begin(9600);
  Serial.print("IR Receive test");
  IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);

  displayCorrectInformation(Jack);

}

boolean editingCups = false;
boolean editingWins = false;

void editCups(Person p) {
  editingCups = true;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Cups Made? ");
  lcd.setCursor(11,0);
  cursorPosX = 11;
  lcd.cursor();
}

void editWins(Person p) {
  editingWins = true;
  lcd.clear(); 
  lcd.setCursor(0,0);
  cursorPosX = 0;
  lcd.print("W or L");
  lcd.setCursor(0,0);
  lcd.cursor();
}


void loop() {

  if (IrReceiver.decode()) {
    
    Serial.println(IrReceiver.decodedIRData.command);

    switch(IrReceiver.decodedIRData.command) {
      case NEXTPERSON:
      if (editingWins == false) {
        currPlayer = findNextPlayer(currPlayer); 
        displayCorrectInformation(currPlayer);
        lcd.noCursor();
        editingCups = false;
        editingWins = false;
      } else {
        lcd.cursor();
        if (cursorPosX == 0) {
          lcd.setCursor(5, 0);
          cursorPosX = 5;
        } else if (cursorPosX = 5) {
          lcd.setCursor(0, 0);
          cursorPosX = 0; 
        }
      }
        break;
      case PREVPERSON:
      if (editingWins == false) {
        currPlayer = findPrevPerson(currPlayer);
        displayCorrectInformation(currPlayer);
        lcd.noCursor();
        editingCups = false;
        editingWins = false;
      } else {
        lcd.cursor();
        if (cursorPosX == 0) {
          lcd.setCursor(5, 0);
          cursorPosX = 5;
        } else if (cursorPosX = 5) {
          lcd.setCursor(0, 0);
          cursorPosX = 0; 
        }
      }
        break;
      case SELECT:
        if (!editingCups && !editingWins) {
          editCups(currPlayer);
        }
        if (editingCups && !editingWins && !cupsMade.equals("-1")) { 
          editingCups = false;
          editWins(currPlayer);
        }
        else if (editingWins && !editingCups) {
          gamesPlayed[currPlayer](currPlayer, gamesPlayed.getValueOf(currPlayer) + 1);
          totalCups[currPlayer](currPlayer, totalCups.getValueOf(currPlayer) + cupsMade.toInt());
          if (cursorPosX == 0) {
            wins[currPlayer](currPlayer, (wins.getValueOf(currPlayer) + 1.0));
          }
          avgCups[currPlayer](currPlayer, totalCups.getValueOf(currPlayer) / gamesPlayed.getValueOf(currPlayer));
          winPercentage[currPlayer](currPlayer, wins.getValueOf(currPlayer) / gamesPlayed.getValueOf(currPlayer));

          
          switch(currPlayer) {
            case Jack:
              EEPROM.write(0, wins.getValueOf(currPlayer));
              EEPROM.write(8, avgCups.getValueOf(currPlayer));
              EEPROM.write(16, gamesPlayed.getValueOf(currPlayer));
              EEPROM.write(24, winPercentage.getValueOf(currPlayer));
              EEPROM.write(32, totalCups.getValueOf(currPlayer));
              break;
            case Chris:
              EEPROM.write(1, wins.getValueOf(currPlayer));
              EEPROM.write(9, avgCups.getValueOf(currPlayer));
              EEPROM.write(17, gamesPlayed.getValueOf(currPlayer));
              EEPROM.write(25, winPercentage.getValueOf(currPlayer));
              EEPROM.write(33, totalCups.getValueOf(currPlayer));
              break; 
            case Mason:
              EEPROM.write(2, wins.getValueOf(currPlayer));
              EEPROM.write(10, avgCups.getValueOf(currPlayer));
              EEPROM.write(18, gamesPlayed.getValueOf(currPlayer));
              EEPROM.write(26, winPercentage.getValueOf(currPlayer));
              EEPROM.write(34, totalCups.getValueOf(currPlayer));
              break; 
            case Will:
              EEPROM.write(3, wins.getValueOf(currPlayer));
              EEPROM.write(11, avgCups.getValueOf(currPlayer));
              EEPROM.write(19, gamesPlayed.getValueOf(currPlayer));
              EEPROM.write(27, winPercentage.getValueOf(currPlayer));
              EEPROM.write(35, totalCups.getValueOf(currPlayer));
              break; 
            case Evan:
              EEPROM.write(4, wins.getValueOf(currPlayer));
              EEPROM.write(12, avgCups.getValueOf(currPlayer));
              EEPROM.write(20, gamesPlayed.getValueOf(currPlayer));
              EEPROM.write(28, winPercentage.getValueOf(currPlayer));
              EEPROM.write(36, totalCups.getValueOf(currPlayer));
              break; 
            case Nick:
              EEPROM.write(5, wins.getValueOf(currPlayer));
              EEPROM.write(13, avgCups.getValueOf(currPlayer));
              EEPROM.write(21, gamesPlayed.getValueOf(currPlayer));
              EEPROM.write(29, winPercentage.getValueOf(currPlayer));
              EEPROM.write(37, totalCups.getValueOf(currPlayer));
              break; 
            case Declan:
              EEPROM.write(6, wins.getValueOf(currPlayer));
              EEPROM.write(14, avgCups.getValueOf(currPlayer));
              EEPROM.write(22, gamesPlayed.getValueOf(currPlayer));
              EEPROM.write(30, winPercentage.getValueOf(currPlayer));
              EEPROM.write(38, totalCups.getValueOf(currPlayer));
              break; 
            case Mehdi:
              EEPROM.write(7, wins.getValueOf(currPlayer));
              EEPROM.write(15, avgCups.getValueOf(currPlayer));
              EEPROM.write(23, gamesPlayed.getValueOf(currPlayer));
              EEPROM.write(31, winPercentage.getValueOf(currPlayer));
              EEPROM.write(39, totalCups.getValueOf(currPlayer));
              break; 
            default:
              break;
          }
          cupsMade = "-1";
          editingWins = false;
          editingCups = false;
          displayCorrectInformation(currPlayer);
          lcd.noCursor();
        }

        break;
      case 22:
        if (editingCups) {
          if (cupsMade == "-1") {
            cupsMade = "1";
          } else {
            cupsMade += "1";
          }
          lcd.print("1");
        }
        break;
      case 25:
        if (editingCups) {
          lcd.print("2");
          if (cupsMade == "-1") {
            cupsMade = "2";
          } else {
            cupsMade += "2";
          }
        }
        break;
      case 13:
        if (editingCups) {
          lcd.print("3");
          if (cupsMade == "-1") {
            cupsMade = "3";
          } else {
            cupsMade += "3";
          }
        }
        break;
      case 12:
        if (editingCups) {
          lcd.print("4");
          if (cupsMade == "-1") {
            cupsMade = "4";
          } else {
            cupsMade += "4";
          }
        }
        break;
      case 24:
        if (editingCups) {
          lcd.print("5");
          if (cupsMade == "-1") {
            cupsMade = "5";
          } else {
            cupsMade += "5";
          }
        }
        break;
      case 94:
        if (editingCups) {
          lcd.print("6");
          if (cupsMade == "-1") {
            cupsMade = "6";
          } else {
            cupsMade += "6";
          }
        }
        break;
      case 8:
        if (editingCups) {
          lcd.print("7");
          if (cupsMade == "-1") {
            cupsMade = "7";
          } else {
            cupsMade += "7";
          }
        }
        break;
      case 28:
        if (editingCups) {
          lcd.print("8");
          if (cupsMade == "-1") {
            cupsMade = "8";
          } else {
            cupsMade += "8";
          }
        }
        break;
      case 90:
        if (editingCups) {
          lcd.print("9");
          if (cupsMade == "-1") {
            cupsMade = "9";
          } else {
            cupsMade += "9";
          }
        }
        break;
      case 82:
        if (editingCups) {
          lcd.print("0");
          if (cupsMade == "-1") {
            cupsMade = "0";
          } else {
            cupsMade += "0";
          }
        }
        break;
      case 74:
          lcd.noCursor();
          displayCorrectInformation(currPlayer);
          cupsMade = "-1";
          editingWins = false; 
          editingCups = false;

      default:
        Serial.println("not mapped");
        break;
    }
      
    delay(500);
    IrReceiver.resume();
  }
  
}
