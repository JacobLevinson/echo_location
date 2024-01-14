// echo location Idea Hacks LA 2024 Project

#define NUM_SENSORS 6
const int trigPins[NUM_SENSORS] = {2, 4, 7, 8, 12, 13};
const int echoPins[NUM_SENSORS] = {14, 15, 16, 17, 18, 19};
const int vibrationPins[NUM_SENSORS] = {3, 5, 6, 9, 10, 11};

long durations[NUM_SENSORS];
int distances[NUM_SENSORS];
int vibration[NUM_SENSORS];

void setup()
{
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
    pinMode(vibrationPins[i], OUTPUT);
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print("Sensor ");
    Serial.println(i);
    digitalWrite(trigPins[i], LOW);
    delayMicroseconds(2);

    // Send a 10 microsecond pulse to the trigger pin
    digitalWrite(trigPins[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPins[i], LOW);

    // Read the duration of the pulse from the echo pin
    durations[i] = pulseIn(echoPins[i], HIGH);

    // Calculate the distance in centimeters
    distances[i] = durations[i] * 0.034 / 2;

    // Print the distance to the serial monitor
    Serial.print("Distance ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(distances[i]);
    Serial.println(" cm");

    int vib = min(distances[i], 250);
    vibration[i] = map(vib, 0, 250, 255, 128);
    analogWrite(vibrationPins[i], vibration[i]);
    Serial.print("Vibration ");
    Serial.println(vibration[i]);
    // Wait for a short time before taking the next measurement
    delay(10);
  }
}
