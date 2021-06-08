#include <LiquidCrystal.h>
#include <HashMap.h>
#include <IRremote.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const byte HASHSIZE = 8;
int RECV_PIN = 9;

IRrecv irrecv(RECV_PIN);
decode_results results; 


enum Person {
  Jack, Chris, Mason, Will, Evan, Nick, Declan, Mehdi 
};

enum Stat {
  AverageCups, Wins
};


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

HashType<Person,int> hashRawArray[HASHSIZE];
HashMap<Person,int> wins = HashMap<Person,int>(hashRawArray, HASHSIZE);
HashMap<Person,int> avgCups = HashMap<Person,int>(hashRawArray, HASHSIZE);
HashMap<Person,int> gamesPlayed = HashMap<Person,int>(hashRawArray, HASHSIZE);

Person currPlayer = Jack;
Stat currStat = Wins; 


Person findNextPlayer(Person currPlayer) {
  
  switch(currPlayer){
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

String evalEnum2(Stat s) {
  
  switch(s) {
    case Wins:
      return "Wins: ";
    case AverageCups:
      return "Average Cups: ";
    default:
      return "No Stat Selected";
  }
  
}

String evalEnum(Person p) {
  
  switch(p) {
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


void setup() {
  
  wins[0](Jack, 0);
  wins[1](Chris, 0);
  wins[2](Mason, 0);
  wins[3](Will, 0);
  wins[4](Evan, 0);
  wins[5](Nick, 0);
  wins[6](Declan, 0);
  wins[7](Mehdi, 0);


  avgCups[0](Jack, 0);
  avgCups[1](Chris, 0);
  avgCups[2](Mason, 0);
  avgCups[3](Will, 0);
  avgCups[4](Evan, 0);
  avgCups[5](Nick, 0);
  avgCups[6](Declan, 0);
  avgCups[7](Mehdi, 0);

  gamesPlayed[0](Jack, 0);
  gamesPlayed[1](Chris, 0);
  gamesPlayed[2](Mason, 0);
  gamesPlayed[3](Will, 0);
  gamesPlayed[4](Evan, 0);
  gamesPlayed[5](Nick, 0);
  gamesPlayed[6](Declan, 0);
  gamesPlayed[7](Mehdi, 0);

  Serial.begin(9600);
  Serial.print("output");
  irrecv.enableIRIn();
  
  Person goat = Jack;
  lcd.begin(16, 2);
  lcd.print(evalEnum2(currStat));
  lcd.setCursor(0, 1);
  lcd.print(evalEnum(Jack));
    
  
  
}

void loop() {

    if (irrecv.decode(&results)) {
      Serial.println(results.value, HEX);
      Serial.println("hello");
      irrecv.resume();
    }
}
