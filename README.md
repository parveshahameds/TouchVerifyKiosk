# Touch Verify Kiosk

**Touch Verify Kiosk** is a secure, self-service fingerprint-based voting system designed for quick and tamper-proof elections. The system authenticates users using biometric fingerprint verification and allows them to vote via a touchscreen or physical button interface. Ideal for college elections, surveys, and organizational voting scenarios.

## 🔐 Features

- 🔒 **Biometric Verification**: Uses fingerprint authentication for voter identity verification.
- 🗳️ **Secure Voting**: Ensures one person–one vote using unique fingerprint IDs.
- 📟 **User Interface**: Simple LCD-based interface with navigation buttons or touchscreen.
- 💾 **Data Logging**: Stores votes and results securely in microcontroller memory or connected database.
- 📊 **Result Display**: Instant viewing of election results and option to clear/reset votes.

## 🛠️ Tech Stack

- **Hardware**:
  - Arduino Uno/Nano
  - Fingerprint Sensor Module (R305 or equivalent)
  - LCD Display (16x2 or 20x4)
  - Push Buttons / Touchscreen (optional)
  - Power Supply (5V regulated)

- **Software**:
  - Arduino IDE (C/C++)
  - Python (for fingerprint enrollment on laptop, optional)
  - Web Dashboard (Flask, HTML/CSS/JS - optional for admin panel)

## 🔧 Setup Instructions

1. **Hardware Connections**:
   - Connect fingerprint sensor to Arduino via Serial.
   - Hook up LCD display and push buttons (Up, Select, Down, Result, Reset).
   - Power the board and components safely.

2. **Code Upload**:
   - Upload `TouchVerifyKiosk.ino` to your Arduino board using the Arduino IDE.
   - (Optional) Run the Python script on your laptop to enroll fingerprints if not using an onboard fingerprint module.

3. **Voting Process**:
   - Voter authenticates using fingerprint.
   - System verifies and allows one vote per fingerprint ID.
   - Voter selects candidate using buttons.
   - Vote is stored and confirmed with a message: `Vote Accepted`.

4. **Result Viewing**:
   - Admin can press the `Result` button to view live vote counts.
   - `Reset` button clears stored votes for the next election cycle.

![20250321_130507](https://github.com/user-attachments/assets/c841b428-a1c1-47cf-80d4-3d849d20b4e8)
