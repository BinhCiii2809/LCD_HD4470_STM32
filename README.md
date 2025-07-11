## 📘Overview

### 🔍Review

- How to initialize and operate an **HD44780-based LCD** in **4-bit interface mode**
- How to connect the LCD to STM32
- How to send commands and data using custom functions
- How to display:
  - Strings and characters
  - Integers
  - Time in HH:MM:SS format with button-based control
- How to create a **modular LCD library** for reuse across projects
- How to create a project in **STM32CubeMX**
- How to add and include `.c/.h` LCD driver files in **Keil µVision**

## 📚 Reference Documentation

For more detailed technical specifications and operational guidance, refer to the official datasheet:

🔗 **Hitachi HD44780U LCD Controller Datasheet**  
[View Datasheet (PDF)](https://www.sparkfun.com/datasheets/LCD/HD44780.pdf)

This datasheet includes:
- Electrical characteristics
- Initialization procedures
- Memory map and command functions

📌 Make sure to review page 24 onward for insights into 4-bit data transfer and control logic.

---
## 📲 LCD to Microcontroller Wiring Table

This table outlines the pin connections between the LCD module and the microcontroller. Each pin is labeled with its function and corresponding microcontroller assignment.

| No.   |  LCD Pin      |  Microcontroller Pin   |  Function Description                            | GPIO             |
|-------|---------------|------------------------|--------------------------------------------------|------------------|
| 1     | LCDRS         | PD.7                   | Register Select: 0 → Command, 1 → Data           | `OUTPUT`         |
| 2     | LCDRW         | PD.6                   | Read/Write Control: 0 → Write, 1 → Read          | `OUTPUT`         |
| 3     | LCDE          | PD.5                   | Enable: Triggers data read/write on LCD          | `OUTPUT`         |
| 4     | LCDD4         | PD.0                   | Data Line D4                                     | `OUTPUT`         |
| 5     | LCDD5         | PD.1                   | Data Line D5                                     | `OUTPUT`         |
| 6     | LCDD6         | PD.2                   | Data Line D6                                     | `OUTPUT`         |
| 7     | LCDD7         | PD.3                   | Data Line D7                                     | `OUTPUT`         |
| 8     | LCDLED(pin A) | PD.4                   | LED Backlight Control                            | `OUTPUT`         |

---

## 🔧 LCD Initialization: Switching from 8-bit to 4-bit Mode

When power is first applied, the **HD44780 LCD controller** starts in **8-bit mode** by default.  
To use the **4-bit interface**, the host MCU must send a specific initialization sequence to "switch" the LCD into 4-bit mode.

📌 This process is outlined in the **HD44780U datasheet, page 46** , and implemented in the `LCD_Init()` function in the `myLCD` library.

---
## ⚙️ Principle of Operation – 4-Bit LCD Interface

### 📦 Register Roles

| Register | Function                                                               |
|----------|------------------------------------------------------------------------|
| IR       | Instruction Register – stores commands                                 |
| DR       | Data Register – holds character data for display                       |
| BF       | Busy Flag – indicates LCD is still processing                          |
| AC       | Address Counter – points to current memory/register location           |

### 📎 Data Transmission: HD44780U LCD Controller Datasheet – Page 22
- Only DB4–DB7 are used; D0–D3 are disabled.
- Each 8-bit instruction is sent in **two 4-bit operations**:
  - First: **High nibble** (D7–D4)
  - Then: **Low nibble**
- Data is latched on the **falling edge of the Enable (E)** signal.
- After sending both nibbles, the **busy flag** must be checked.
- Transfer the busy flag and address counter requires **two additional 4-bit reads**.

---
## 🧾 LCD Instruction Set – 4-bit Mode

| No. |  Command Meaning             | Binary Code (D7-D0)    |    HEX Code |     Notes                            |
|-----|------------------------------|------------------------|-------------|--------------------------------------|
| 1   | Clear Display                | `0000 0001`            | `0x01`      | Clears screen, cursor to home        |
| 2   | Return Home                  | `0000 0011`            | `0x03`      | Cursor to origin                     |
| 3   | Entry Mode Set               | `0000 0110`            | `0x06`      | Cursor moves right after each character |
| 4   | Display ON, Cursor OFF       | `0000 1100`            | `0x0C`      | Display ON, cursor hidden            |
| 5   | Display ON, Cursor ON        | `0000 1110`            | `0x0E`      | Cursor visible, no blink             |
| 6   | Display ON, Cursor Blink     | `0000 1111`            | `0x0F`      | Cursor blinking                      |
| 7   | Display OFF                  | `0000 1000`            | `0x08`      | Turns off display                    |
| 8   | Shift Cursor Left            | `0001 0000`            | `0x10`      | Moves cursor one position left       |
| 9   | Shift Cursor Right           | `0001 0100`            | `0x14`      | Moves cursor one position right      |
| 10  | Shift Display Left           | `0001 1000`            | `0x18`      | Moves entire display left            |
| 11  | Shift Display Right          | `0001 1100`            | `0x1C`      | Moves entire display right           |
| 12  | Function Set (4-bit, 2-line) | `0010 1000`            | `0x28`      | 4-bit interface, 2-line, 5x8 dots    |

📌 This process is outlined in the **HD44780U datasheet, page 46** 

---
## 📚 myLCD Library

### 📁 Files

- `myLCD.h` – Header file containing function prototypes and macros.
- `myLCD.c` – Source file implementing the functions.

---

### 🧰 Available Functions

| Function                   | Description                                                                |
|---------------------------|----------------------------------------------------------------------------|
| `LCD_Init()`              | Initializes the LCD in 4-bit mode. Sets function, display, entry mode.     |
| `LCD_Clear()`             | Clears the LCD display and returns the cursor to home position.            |
| `LCD_Command(uint8_t cmd)`        | Sends a raw command byte to the LCD (internal use or advanced control).    |
| `LCD_Write(uint8_t data)`         | Sends one byte of data to the LCD.                                         |
| `LCD_Send(uint8_t Reg, uint8_t data)`     | Sends `data` to `Reg of LCD` (either command register:`0` or data register:`1`).          |
| `LCD_GotoXY(uint8_t x, uint8_t y)`        | Moves the cursor to the specified column `x` (0–15), row `y` (0 or 1).     |
| `LCD_PutChar(uint8_t ch)`         | Displays a single character `ch` at the current cursor position.           |
| `LCD_PutString(char* s)`        | Displays a null-terminated string `s` at the current cursor position.      |
| `LCD_PutNumber(int* number)`  | Displays a signed integer number on the LCD at current position.           |
| `LCD_Clock(uint8_t *hours, uint8_t *minutes, uint8_t *second)`   | Displays the current time in **HH:MM:SS** format (24-hour clock).          |

#### Example:
```c
int num = 1234;
LCD_PutNumber(&num); //Show 1234

LCD_Command(0x01); //Send "Clear display" command (same as LCD_Clear())

LCD_Send(0, 0x01); //Send "Clear display" command (same as LCD_Clear())
LCD_Send(1, 'A');  //Display character 'A' at current cursor position

LCD_Write('H'); // Writes character 'H'

LCD_GotoXY(0, 0);                   // First row, first column

LCD_PutString("Hello, World!");     // Display string Hello, World!

LCD_Clock(&hour, &min, &sec);      // Show time in HH:MM:SS
```

## 🧪 Application Examples

All the following demo applications are implemented in the file:

📁 demo_LCD_HD44780_STM32.c

### 🔘 Button Interface (P1–P4)

Four **active-low push buttons** (normally open) are used for user interaction. Each button should be connected with a **pull-up resistor** via STM32.

| Button | Connected To STM32 Pin  | Circuit Note               | GPIO             |
|--------|-------------------------|----------------------------|------------------|
| `P1`   |       `PB4`             | Pull-up resistor required  | `INPUT`          |
| `P2`   |       `PB5`             | Pull-up resistor required  | `INPUT`          |
| `P3`   |       `PB8`             | Pull-up resistor required  | `INPUT`          |
| `P4`   |       `PB9`             | Pull-up resistor required  | `INPUT`          |

---

### 🧭 Application 2 – Digital Clock (Auto Incrementing)

📌 **Objective:** Create a simple digital clock that automatically counts time.

- When powered on, the LCD displays the current time in the format:  
  🕒 `"CLOCK: HH:MM:SS"`  
  Example: `CLOCK: 14:03:05`
- The time increases automatically **every 1 second**.
- Time counting follows standard rules:
  - After `SS = 59` → `MM` increases by 1
  - After `MM = 59` → `HH` increases by 1
- You can reset or adjust time values manually if needed.

---

### 🧭 Application 3 – Product Counter (Manual + Auto Count)

📌 **Objective:** Build a production counter using buttons.

- On startup, the LCD shows:  
  📦 `"San pham: 0"`
- Each time **button P1** is pressed → product count increases by 1  
  (`San pham: 1`, `San pham: 2`, etc.)
- Each time **button P2** is pressed → product count decreases by 1
- Each time **button P3** is **tapped once** → auto-increment mode is activated:  
  LCD automatically increases count every **1 second**
- Each time **button P4** is pressed → auto-increment is **stopped**

> 📝 Useful for learning **state control**, **button debouncing**, and **timed loops**.

---

### 🧭 Application 4 – Adjustable Real-Time Clock

📌 **Objective:** Build a real-time clock with adjustable hours, minutes, and seconds.

- On power-up, the LCD displays time in format:  
  ⏰ `"HH:MM:SS"` (e.g. `14:03:05`)
- **Button P1**: Toggle **auto time counting** mode:
  - Time increases every second
  - Seconds overflow (`SS = 59`) → minutes (`MM`) increase
  - Minutes overflow (`MM = 59`) → hours (`HH`) increase
- **Button P2**: Increase current **hour** by 1
- **Button P3**: Increase current **minute** by 1
- **Button P4**: Increase current **second** by 1

---
## 📂 How to `Create Project` in STM32CubeMX.

### 🧩 Step 1: Create a project using **STM32F103RCT**.

<img width="324" height="370" alt="Image" src="https://github.com/user-attachments/assets/76bd85b9-2821-4eb9-b4e0-5cb0401417e0" />

<img width="869" height="335" alt="Image" src="https://github.com/user-attachments/assets/26d74456-a805-4144-bfbc-11c77b1c77ba" />

### 🧩 Step 2: Set up INPUT pull-up

<img width="1327" height="547" alt="Image" src="https://github.com/user-attachments/assets/561263d6-38e4-497b-9b9e-24f392084240" />

### 🧩 Step 3: Set up OUTPUT

<img width="1169" height="524" alt="Image" src="https://github.com/user-attachments/assets/ab6b09af-f995-4437-9680-76c1395ac6ff" />

### 🧩 Step 4: Enable Serial Wire Debug (SWD)

<img width="1114" height="492" alt="Image" src="https://github.com/user-attachments/assets/0bdff256-ecb8-44e6-bc37-f0f51115f2a5" />

### 🧩 Step 5: Generate Code in **Keil uVision**

<img width="1333" height="446" alt="Image" src="https://github.com/user-attachments/assets/2b0bda3c-dbff-41e2-86db-6e9893051405" />


