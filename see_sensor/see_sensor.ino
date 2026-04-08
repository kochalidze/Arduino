// პინების განსაზღვრა
const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 13; // გამოიყენება Arduino-ს ჩაშენებული LED ან დამატებითი მე-13 პინზე

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT); // აგზავნის სიგნალს
  pinMode(echoPin, INPUT);  // იღებს სიგნალს
  pinMode(ledPin, OUTPUT);  // მართავს შუქს
  
  Serial.begin(9600);       // მონიტორინგისთვის
}

void loop() {
  // სენსორის გასუფთავება და სიგნალის გაშვება
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // ექოს მოსვლის დროის გაზომვა
  duration = pulseIn(echoPin, HIGH);

  // მანძილის გამოთვლა სანტიმეტრებში
  distance = duration * 0.034 / 2;

  // ლოგიკა: თუ ხელი 20 სმ-ზე ახლოსაა, შუქი ჩააქრე
  if (distance > 0 && distance < 20) {
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, HIGH);
  }

  // მონაცემების გამოტანა კომპიუტერში (შესამოწმებლად)
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(100); // მცირე პაუზა სტაბილურობისთვის
}