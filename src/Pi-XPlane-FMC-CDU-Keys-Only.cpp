#include <iostream>
#include <string.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <vector>
#include <unistd.h>
#include <map>
#include <string>

#include <XPlaneBeaconListener.h>
#include <XPlaneUDPClient.h>


/*
 This file is part of Pi-XPlane-FMC-CDU-Keys-Only
 A Raspberry Pi-based External FMC for XPlane

 Copyright (C) 2019 shahada abubakar
 <shahada@abubakar.net>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.

 */

using namespace std;

// this determines what command to send when which key is pressed

std::map<int, std::map <int, std::string > > keyInfo;

// columns are outputs. All are set to HIGH except the column being scanned.
std::vector<int> columnPins = { 15, // p.8  BCM.14 	BLACK UART TX
		16, // p.10 BCM.15 	WHITE UART RX
		1, 	// p.12 BCM.18 	GRAY  PWM0
		4, 	// p.16 BCM.23 	PURPLE
		5, 	// p.18 BCM.24 	BLUE
		6,	// p.22 BCM.25 	GREEN
		10,	// p.24	BCM.8	YELLOW CE0
		11,	// p.26 BCM.7	ORANGE CE1
		27	// p.36 BCM.16	RED
		};

// 	// rows are inputs.
std::vector<int> rowPins = { 29,	//	p.40 BCM.21	GRAY SCLK
		8,	//	p.3	BCM.2 PURPLE I2C SDA (fixed pull-up)
		9,	// 	p.5	BCM.3 BLUE I2C SCL (fixed pull-up)
		7,	// 	p.7 BCM.4 GREEN GPCLK0
		0,	//	p.11 BCM.17 YELLOW
		2, 	// 	p.13 BCM.27 ORANGE
		3,	//	p.15 BCM.22 RED
		12	// 	p.19 BCM.10 BROWN MOSI
		};


// globals

bool found = false;
string host;
uint16_t port;


// callbacks

void receiverBeaconCallback(XPlaneBeaconListener::XPlaneServer server,
		bool exists) {
	cout << "receiverBeaconCallback got [" << server.toString() << " is "
			<< (exists ? "alive" : "dead") << "]" << endl;
	host = server.host;
	port = server.receivePort;
	found = true;
}



int main(int argc, char * argv[]) {

	keyInfo[1][1] = "sim/FMS/ls_1l"; 	// sw-1
	keyInfo[2][1] = "sim/FMS/ls_2l";	// sw-2
	keyInfo[3][1] = "sim/FMS/ls_3l"; 	// sw-3
	keyInfo[4][1] = "sim/FMS/ls_4l"; 	// sw-4
	keyInfo[5][1] = "sim/FMS/ls_5l"; 	// sw-5
	keyInfo[6][1] = "sim/FMS/ls_6l"; 	// sw-6
	keyInfo[7][1] = "sim/FMS/ls_1r"; 	// sw-7
	keyInfo[8][1] = "sim/FMS/ls_2r"; 	// sw-8
	keyInfo[1][2] = "sim/FMS/ls_3r";; 	// sw-9
	keyInfo[2][2] = "sim/FMS/ls_4r";	// sw-10
	keyInfo[3][2] = "sim/FMS/ls_5r"; 	// sw-11
	keyInfo[4][2] = "sim/FMS/ls_6r"; 	// sw-12
	keyInfo[5][2] = "sim/FMS/index"; 	// sw-13
	keyInfo[6][2] = "sim/FMS/fpln";		// sw-14
	keyInfo[7][2] = "sim/FMS/clb"; 		// sw-15
	keyInfo[8][2] = "sim/FMS/crz";		// sw-16
	keyInfo[1][3] = "sim/FMS/des";		// sw-17
	keyInfo[2][3] = "sim/fms_direct";	// sw-18
	keyInfo[3][3] = "sim/FMS/legs"; 	// sw-19
	keyInfo[4][3] = "sim/FMS/dep_arr";	// sw-20
	keyInfo[5][3] = "sim/FMS/hold";		// sw-21
	keyInfo[6][3] = "sim/FMS/prog";		// sw-22
	keyInfo[7][3] = "sim/FMS/exec";		// sw-23
	keyInfo[8][3] = "sim/fms_type_fix"; // sw-24
	keyInfo[1][4] = "sim/FMS/fix";		// sw-25
	keyInfo[2][4] = "sim/FMS/prev";		// sw-26
	keyInfo[3][4] = "sim/FMS/next"; 	// sw-27
	keyInfo[4][4] = "sim/FMS/key_A";	// sw-28
	keyInfo[5][4] = "sim/FMS/key_B";	// sw-29
	keyInfo[6][4] = "sim/FMS/key_C";	// sw-30
	keyInfo[7][4] = "sim/FMS/key_D";	// sw-31
	keyInfo[8][4] = "sim/FMS/key_E";	// sw32
	keyInfo[1][5] = "sim/FMS/key_F";	// sw-33
	keyInfo[2][5] = "sim/FMS/key_G";	// sw-34
	keyInfo[3][5] = "sim/FMS/key_H";	// sw-35
	keyInfo[4][5] = "sim/FMS/key_I";	// sw-36
	keyInfo[5][5] = "sim/FMS/key_J";	// sw-37
	keyInfo[6][5] = "sim/FMS/key_K";	// sw-38
	keyInfo[7][5] = "sim/FMS/key_L";	// sw-39
	keyInfo[8][5] = "sim/FMS/key_M";	// sw-40
	keyInfo[1][6] = "sim/FMS/key_N";	// sw-41
	keyInfo[2][6] = "sim/FMS/key_O";	// sw-42
	keyInfo[3][6] = "sim/FMS/key_P";	// sw-43
	keyInfo[4][6] = "sim/FMS/key_Q";	// sw-44
	keyInfo[5][6] = "sim/FMS/key_R";	// sw-45
	keyInfo[6][6] = "sim/FMS/key_S";	// sw-46
	keyInfo[7][6] = "sim/FMS/key_T";	// sw-47
	keyInfo[8][6] = "sim/FMS/key_U";	// sw-48
	keyInfo[1][7] = "sim/FMS/key_V";	// sw-49
	keyInfo[2][7] = "sim/FMS/key_W";	// sw-50
	keyInfo[3][7] = "sim/FMS/key_X";	// sw-51
	keyInfo[4][7] = "sim/FMS/key_Y";	// sw-52
	keyInfo[5][7] = "sim/FMS/key_Z";;	// sw-53
	keyInfo[6][7] = "sim/FMS/key_space"; 	// sw-54
	keyInfo[7][7] = "sim/FMS/key_delete";	// sw-55
	keyInfo[8][7] = "sim/FMS/key_slash";	// sw-56
	keyInfo[1][8] = "sim/FMS/key_clear";	// sw-57
	keyInfo[2][8] = "sim/FMS/key_period";	// sw-58
	keyInfo[3][8] = "sim/FMS/key_0";	// sw-59
	keyInfo[4][8] = "sim/FMS/key_minus";	// sw-60
	keyInfo[5][8] = "sim/FMS/key_7"; 	// sw-61
	keyInfo[6][8] = "sim/FMS/key_8";	// sw-62
	keyInfo[7][8] = "sim/FMS/key_9";	// sw-63
	keyInfo[8][8] = "sim/FMS/key_4";	// sw-64
	keyInfo[1][9] = "sim/FMS/key_5";	// sw-65
	keyInfo[2][9] = "sim/FMS/key_6";	// sw-66
	keyInfo[3][9] = "sim/FMS/key_1";	// sw-67
	keyInfo[4][9] = "sim/FMS/key_2";	// sw-68
	keyInfo[5][9] = "sim/FMS/key_3";	// sw-69

	wiringPiSetup();

	XPlaneBeaconListener::getInstance()->registerNotificationCallback(
			std::bind(receiverBeaconCallback, std::placeholders::_1,
					std::placeholders::_2));
	XPlaneBeaconListener::getInstance()->setDebug(0);

	cout << "Waiting for X-Plane ... Press Control-C to abort." << endl;

	// wait for a server
	while (!found) {
		sleep(1);
	}

	cout << "Found server " << host << ":" << port << endl;

	XPlaneUDPClient xp(host, port, NULL, NULL);
	xp.setDebug(0);

	// set columns as outputs, HIGH by default
	for (size_t pin = 0; pin < columnPins.size(); pin++) {
		digitalWrite(columnPins[pin], 1);
		pinMode(columnPins[pin], OUTPUT);
	}

	// set rows as inputs, with Pull-UP enabled.
	for (size_t pin = 0; pin < rowPins.size(); pin++) {
		pinMode(rowPins[pin], INPUT);
		pullUpDnControl(rowPins[pin], PUD_UP);
	}

	unsigned int pressedRow;
	unsigned int pressedCol;
	bool somethingPressed = false;

	printf(
			"Scanning keyboard ... press any key on the FMC keypad to test.\nPress Control-C (on the regular keyboard) to abort.\n");

	while (true) {

		// iterate through the columns
		bool gotPress = false;
		for (size_t nowCol = 0; nowCol < columnPins.size(); nowCol++) {

			// set the current column to LOW
			digitalWrite(columnPins[nowCol], 0);

			// go through the rows, see who is low (pressed)

			for (size_t nowRow = 0; nowRow < rowPins.size(); nowRow++) {

				// delay a bit for the GPIO state to settle
				delayMicroseconds(5);
				int status = digitalRead(rowPins[nowRow]);

				// something pressed
				if (status == 0) {
					gotPress = true;
					if (somethingPressed == true) {
						if (pressedRow == nowRow && pressedCol == nowCol) {

							// previous key still being held down.

						} else {
							// multiple keys being pressed or another key pressed
							// without the earlier being released. Do nothing.

							printf("Multiple keys pressed.\n");
						}
					} else {
						// looks like a new key has been pressed
						pressedRow = nowRow;
						pressedCol = nowCol;
						somethingPressed = true;

						printf("KEY PRESS   row=%02d col=%02d\n", nowRow + 1,
								nowCol + 1);

						// look it up in our keysToCommands table

						auto r = keyInfo.find(nowRow);
						if ( r != keyInfo.end()) {
							auto c = r->second.find (nowCol);
							if (c != r->second.end()) {
								printf ("  SENDING COMMAND \"%s\" to X-Plane", c->second.c_str());
								xp.sendCommand(c->second);
							}
						}

						// quick and dirty delay for 5ms to debounce
						delayMicroseconds(5000);
					}

				}

			}
			// restore the current column to HIGH
			digitalWrite(columnPins[nowCol], 1);

		}

		if (!gotPress) {
			// nothing pressed this scan. If something was pressed before, consider
			// it released.
			if (somethingPressed) {
				somethingPressed = false;

				printf("KEY RELEASE row=%02d col=%02d\n", pressedRow + 1,
						pressedCol + 1);
			}
		}

	}

}
