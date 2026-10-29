# smart-railway-platform
Smart Railway Platform Display (LPC2148)

An embedded C project that works like a railway station platform information board. It runs on an LPC2148 (ARM7) microcontroller and shows live train information on a 16x2 LCD, with LED and buzzer alerts. A PIN-protected admin menu lets the operator change the clock and edit train details.


Features

Real-time clock using the on-chip RTC, with date, time and day shown on the LCD.

Train information screens that rotate automatically. Each train shows its number, name, destination, arrival time, platform and delay status.

Approaching-train alert. When a train is within 5 minutes of arrival, the LCD shows the train number and a scrolling train name. The yellow LED turns on and the buzzer beeps.

Status LEDs. Green means on time and red means delayed.

Midnight handling for arrival and departure times that cross 00:00.

Admin menu opened with an external-interrupt button and protected by a 4-digit PIN:
Set the RTC date and time.
Edit a train's delay, platform, arrival time or departure time.
Platform collision check. If two trains would overlap on the same platform, the change is rejected and the buzzer sounds.
Input validation and a confirm-before-save step.


Hardware

Component	Details
Microcontroller	LPC2148 (ARM7TDMI-S), 12 MHz crystal
Display	16x2 character LCD (HD44780), 4-bit mode
Input	4x4 keypad and one push button (admin menu)
Indicators	Green, yellow and red LEDs, and a buzzer
Board used	Vector's Advanced Development Board for ARM7

Pin connections

Signal	LPC2148 pin
LCD RS	P0.16
LCD EN	P0.17
LCD D4-D7	P0.12 - P0.15
LCD RW	GND
Keypad rows	P1.16 - P1.19 (output)
Keypad columns	P1.20 - P1.23 (input)
Admin menu button (EINT0)	P0.1 (falling edge)
Green LED	P0.4
Yellow LED	P0.5
Red LED	P0.6
Buzzer	P0.7

LEDs and the buzzer are driven active high.


Keypad layout

7  8  9  /
4  5  6  *
1  2  3  -
C  0  =  +

Key	Action
0-9	Enter digits
=	Enter / confirm
-	Backspace (admin value entry)
C	Back / cancel
*	Save change (admin menu)

How it works


On start-up the LCD, RTC, interrupt and keypad are initialised, and the RTC date and time setup screen opens.

In normal mode, main() checks every train against the RTC. A train is "active" if it is within 5 minutes of its updated arrival time and has not yet departed.

If a train is active, the approaching screen is shown with the yellow LED and buzzer. Otherwise an 18-second cycle shows the clock, then arrival and platform, then destination and status for each train.

Pressing the menu button triggers EINT0 and sets a flag. The main loop then runs the admin menu.

Admin menu

Press the menu button.

Enter the PIN and press = (default PIN: 1234).

Choose 1 to edit the RTC time, or 2 to edit trains.

For trains, select the train (1-3), then the value: 1 delay, 2 platform, 3 arrival, 4 departure.

Enter the value and press =, then press * to save or C to cancel.

Sample train data

Train	Number	Destination	Platform	Arr / Dep	Delay
Karnataka Express	12627	New Delhi	1	06:30 / 06:35	On time
Shatabdi Express	12028	Chennai	2	07:15 / 07:20	On time
Kacheguda Express	12785	Hyderabad	3	08:00 / 08:05	20 min

Train data is stored in railway.c and can be edited there.

Project structure

File	Purpose
train_main.c	Main loop, train selection and display logic
railway.c / railway.h	Train database and pin definitions
train_dprint.c / .h	Train screens, scrolling name and time helpers
admin.c / admin.h	Admin menu, PIN check and platform collision check
RTC.c / RTC.h	RTC setup, clock display and date/time editing
lcd.c / LCD.h	16x2 LCD driver (4-bit mode)
keypad.c / keypad.h	4x4 keypad scanning with debounce
interrupt.c / .h	EINT0 interrupt for the admin menu
indicator.c / .h	LED and buzzer control
delay.c / delay.h	Software delay functions
types.h	Fixed-size integer type definitions

Build and flash

Tools: Keil uVision (ARM compiler) and Flash Magic.

Open Keil and create a project for the LPC2148. Add all .c files and enable Create HEX File.

Build with 0 errors.

Put the board's LOAD/EXE switch in LOAD and flash the HEX file with Flash Magic (device LPC2148, oscillator 12 MHz).

Move the switch to EXE and press RST.

Author
Venkata Reddy Mandalapu.
