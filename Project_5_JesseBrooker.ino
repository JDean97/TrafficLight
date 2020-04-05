//Project 5
//Bridge Stoplight
//Jesse Brooker

#define carWest 2
#define pedCross 3
#define redWestLED 4
#define yellowWestLED 5
#define greenWestLED 6

#define carEast 7
#define redEastLED 9
#define yellowEastLED 10
#define greenEastLED 11

#define whitePedLED 12
#define redPedLED 13

bool trafficWest = true;// true traffic is coming from West

int trafficDelay = 3000;
int pedDelay = 8000;
int flashDelay = 500;

void setup() {
  pinMode(carWest, INPUT);
  pinMode(pedCross, INPUT);
  pinMode(carEast, INPUT);

  pinMode(redWestLED, OUTPUT);
  pinMode(yellowWestLED, OUTPUT);
  pinMode(greenWestLED, OUTPUT);

  pinMode(redEastLED, OUTPUT);
  pinMode(yellowEastLED, OUTPUT);
  pinMode(greenEastLED, OUTPUT);

  pinMode(whitePedLED, OUTPUT);
  pinMode(redPedLED, OUTPUT);

  //West Light Green, East Light Red
  digitalWrite(greenWestLED, HIGH);
  digitalWrite(redEastLED, HIGH);
  //Pedestrian Light Red
  digitalWrite(redPedLED, HIGH);
}

void loop() {
  if (digitalRead(pedCross) == HIGH)
  {
    PEDWalk();
  }
  else if (trafficWest && digitalRead(carEast) == HIGH)
  {
    TrafficGoWest();
  }
  else if (!trafficWest && digitalRead(carWest) == HIGH)
  {
    TrafficGoEast();
  }
}

void PEDWalk()
{
    if (trafficWest)
    {
      digitalWrite(greenWestLED, LOW);
      digitalWrite(yellowWestLED, HIGH);
      delay(trafficDelay);
      digitalWrite(yellowWestLED, LOW);
      digitalWrite(redWestLED, HIGH);
    }
    else if (!trafficWest)
    {
      digitalWrite(greenEastLED, LOW);
      digitalWrite(yellowEastLED, HIGH);
      delay(trafficDelay);
      digitalWrite(yellowEastLED, LOW);
      digitalWrite(redEastLED, HIGH);
    }
    delay(trafficDelay);
    digitalWrite(redPedLED, LOW);
    digitalWrite(whitePedLED, HIGH);
    delay(pedDelay);
    for (int i = 0; i < 5; i++)
    {
      digitalWrite(whitePedLED, LOW);
      delay(flashDelay);
      digitalWrite(whitePedLED, HIGH);
      delay(flashDelay);
    }
    digitalWrite(whitePedLED, LOW);
    digitalWrite(redPedLED, HIGH);
    delay(trafficDelay);
    if (trafficWest)
    {
      digitalWrite(greenWestLED, HIGH);
      digitalWrite(redWestLED, LOW);
    }
    else if (!trafficWest)
    {
      digitalWrite(greenEastLED, HIGH);
      digitalWrite(redEastLED, LOW);
    }
}

void TrafficGoWest()
{
    digitalWrite(greenWestLED, LOW); //Turn Green to Yellow Light
    digitalWrite(yellowWestLED, HIGH);
    delay(trafficDelay);
    digitalWrite(yellowWestLED, LOW); //Turn Yellow to Red Light
    digitalWrite(redWestLED, HIGH);
    delay(trafficDelay);
    digitalWrite(redEastLED, LOW); //Turn Opposite End Red to Green Light
    digitalWrite(greenEastLED, HIGH);
    trafficWest = false; //Reverse Direction
}

void TrafficGoEast()
{
    digitalWrite(greenEastLED, LOW); //Turn Green to Yellow Light
    digitalWrite(yellowEastLED, HIGH);
    delay(trafficDelay);
    digitalWrite(yellowEastLED, LOW); //Turn Yellow to Red Light
    digitalWrite(redEastLED, HIGH);
    delay(trafficDelay);
    digitalWrite(redWestLED, LOW); //Turn Opposite End Red to Green Light
    digitalWrite(greenWestLED, HIGH);
    trafficWest = true; //Reverse Direction
}
