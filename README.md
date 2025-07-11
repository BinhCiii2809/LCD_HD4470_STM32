## 📚 Reference Documentation

For more detailed technical specifications and operational guidance, refer to the official datasheet:

🔗 **Hitachi HD44780U LCD Controller Datasheet**  
[View Datasheet (PDF)](https://www.sparkfun.com/datasheets/LCD/HD44780.pdf)

This datasheet includes:
- Electrical characteristics
- Instruction set
- Timing diagrams
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
