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

| No.   |  LCD Pin      |  Microcontroller Pin   |  Function Description                            |
|-------|---------------|------------------------|--------------------------------------------------|
| 1     | LCDRS         | PD.7                   | Register Select: 0 → Command, 1 → Data           |
| 2     | LCDRW         | PD.6                   | Read/Write Control: 0 → Write, 1 → Read          |
| 3     | LCDE          | PD.5                   | Enable: Triggers data read/write on LCD          |
| 4     | LCDD4         | PD.0                   | Data Line D4                                     |
| 5     | LCDD5         | PD.1                   | Data Line D5                                     |
| 6     | LCDD6         | PD.2                   | Data Line D6                                     |
| 7     | LCDD7         | PD.3                   | Data Line D7                                     |
| 8     | LCDLED(pin A) | PD.4                   | LED Backlight Control                            |

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
- Only DB4–DB7 are used; DB0–DB3 are disabled.
- Each 8-bit instruction is sent in **two 4-bit operations**:
  - First: **High nibble** (DB7–DB4)
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
| `LCD_Command(cmd)`        | Sends a raw command byte to the LCD (internal use or advanced control).    |
| `LCD_Write(data)`         | Sends one byte of data to the LCD.                                         |
| `LCD_Send(Reg, data)`     | Sends `data` to `Reg of LCD` (either command register:`0` or data register:`1`).          |
| `LCD_GotoXY(x, y)`        | Moves the cursor to the specified column `x` (0–15), row `y` (0 or 1).     |
| `LCD_PutChar(ch)`         | Displays a single character `ch` at the current cursor position.           |
| `LCD_PutString(s)`        | Displays a null-terminated string `s` at the current cursor position.      |
| `LCD_PutNumber(&number)`  | Displays a signed integer number on the LCD at current position.           |
| `LCD_Clock(&h, &m, &s)`   | Displays the current time in **HH:MM:SS** format (24-hour clock).          |

#### Example:
```c
int num = 1234;
LCD_PutNumber(&num); //Show 1234

LCD_Command(0x01); //clear


```
