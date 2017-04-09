#include <SoftwareSerial.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
char num[12];
int i = 0;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
	{ '1', '2', '3', 'A' },
	{ '4', '5', '6', 'B' },
	{ '7', '8', '9', 'C' },
	{ '#', '0', '*', 'D' }
};
byte rowPins[ROWS] = { 5, 4, 3, 2 };
byte colPins[COLS] = { 9, 8, 7, 6 };

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
void setup() {
	lcd.begin(16, 2);

	Serial.begin(9600);

}
void loop() {
	call();



	//if(Serial.find("RING")){
	// Serial.println("AT+CLIP=1");
	// }
}








void call() {

	String atd;
	String number;

	atd = "ATD";
	char key = keypad.getKey();

	if (key) {
		lcd.print(key);
		num[i] = key;
		i++;
	}

	if (key == 'C') {

		for (int k = 0; k <= i; k++) {
			number += num[k];
		}
		atd += number;
		atd.replace("C", ";");
		lcd.print(atd);
		Serial.print(atd);
		i = 0;
		/*for (;;) {
		lcd.print("DIAL");
		delay(500);
		lcd.clear();
		lcd.print(number);
		delay(500);
		lcd.clear();
		if (Serial.find("D")) {
		break;
		}


		}
		*/

	}
	stat(number, key);
}

void stat(String number, char key) {

	if (key == 'C') {
		for (;;) {
			char keyd = keypad.getKey();

			if (keyd == 'D') {

				lcd.print("Call ended");

				delay(1000);

				lcd.clear();
				break;

			}

			lcd.print("DIAL");
			delay(500);
			lcd.clear();
			lcd.print(number);
			delay(500);
			lcd.clear();



		}
	}
}