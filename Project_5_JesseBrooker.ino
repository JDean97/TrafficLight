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

int pedDelay = 8000;
int flashDelay = 500;
int trafficDelay = 3000;

void setup()
{
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

void loop()
{
  if (digitalRead(pedCross) == HIGH)
  {
    PEDWalk(trafficWest);
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

void PEDWalk(bool _trafficWest)
{
  ChangeLightsStop(_trafficWest);
  PEDLight(pedDelay, flashDelay);
  delay(trafficDelay);
  ChangeLightsGo(trafficWest, true);
}

void TrafficGoWest()
{
  ChangeLightsStop(trafficWest);
  ChangeLightsGo(trafficWest, false); //Turn Opposite End Red to Green Light
  trafficWest = false; //Reverse Direction
}

void TrafficGoEast()
{
  ChangeLightsStop(trafficWest);
  ChangeLightsGo(trafficWest, false); //Turn Opposite End Red to Green Light
  trafficWest = true; //Reverse Direction
}

void PEDLight(int _pedDelay, int _flashDelay)
{
  digitalWrite(redPedLED, LOW);
  digitalWrite(whitePedLED, HIGH);
  delay(_pedDelay);
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(whitePedLED, LOW);
    delay(_flashDelay);
    digitalWrite(whitePedLED, HIGH);
    delay(_flashDelay);
  }
  digitalWrite(whitePedLED, LOW);
  digitalWrite(redPedLED, HIGH);
}

void ChangeLightsStop(bool _trafficWest)
{
  if (_trafficWest)
  {
    digitalWrite(greenWestLED, LOW); //Turn Green to Yellow Light
    digitalWrite(yellowWestLED, HIGH);
    delay(trafficDelay);
    digitalWrite(yellowWestLED, LOW); //Turn Yellow to Red Light
    digitalWrite(redWestLED, HIGH);
    delay(trafficDelay);
  }
  else if (!_trafficWest)
  {
    digitalWrite(greenEastLED, LOW); //Turn Green to Yellow Light
    digitalWrite(yellowEastLED, HIGH);
    delay(trafficDelay);
    digitalWrite(yellowEastLED, LOW); //Turn Yellow to Red Light
    digitalWrite(redEastLED, HIGH);
    delay(trafficDelay);
  }
}

void ChangeLightsGo(bool _trafficWest, bool resumeDirection)
{
  // resumeDirection = true traffic will return to direction it was moving before
  // resumeDireciton = false traffic will move opposite direction as before
  if ((_trafficWest && resumeDirection) || (!_trafficWest && !resumeDirection))
  {
    digitalWrite(redWestLED, LOW);
    digitalWrite(greenWestLED, HIGH);
  }
  else if ((!_trafficWest && resumeDirection) || (_trafficWest && !resumeDirection))
  {
    digitalWrite(redEastLED, LOW);
    digitalWrite(greenEastLED, HIGH);
  }
}
