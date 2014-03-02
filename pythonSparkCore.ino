char resultstr[64];
int white = D0;
int blue = D1;
int red = D2;
int yellow = D3;
int green = D4;


void setup()
{
    pinMode(A0, INPUT); // setup A0 as analog input
    pinMode(A1, INPUT); // setup A1 as analog input
    pinMode(white, OUTPUT);
    pinMode(blue, OUTPUT);
    pinMode(red, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(green, OUTPUT);


    Serial.begin(9600);

    Spark.variable("result", &resultstr, STRING);
    Spark.function("blink", blink);
    Spark.function("allOff", allOff);
    Spark.function("allOn", allOn);
}

void loop()
{
    int data1 = analogRead(A0);
    int data2 = analogRead(A1);

    sprintf(resultstr, "{\"data1\":%d,\"data2\":%d}", data1, data2);

}


String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

int blink(String args){
    Serial.println();
    Serial.println("args: " + args);

    args.trim();
    args.toLowerCase();

    String state = getValue(args, ',', 0);
    String color = getValue(args, ',', 1);

    Serial.println("state: " + state);
    Serial.println("color: " + color);


    if (state == "on" ){

        digitalWrite(map(color), HIGH);


    } else if (state == "off")  {

        digitalWrite(map(color), LOW);
    }

    return 200;
}

int allOff(String args){
    digitalWrite(white, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);

    return 200;
}


int allOn(String args){
    digitalWrite(white, HIGH);
    digitalWrite(blue, HIGH);
    digitalWrite(red, HIGH);
    digitalWrite(yellow, HIGH);
    digitalWrite(green, HIGH);

    return 200;
}

int map(String color){
    if(color == "white") {
        return D0;
    } else if (color == "blue"){
        return D1;
    } else if (color == "red"){
        return D2;
    } else if (color == "yellow"){
        return D3;
    } else if (color == "green"){
        return D4;
    }

}