# IoT Temperature-Based Cooling Controller

An ESP32-based IoT prototype that monitors temperature with a DS18B20 digital sensor and controls two 12 V DC cooling fans using temperature thresholds. The project combines embedded control with Wi-Fi connectivity and Blynk-based remote monitoring and alerts.

## Project at a Glance

- **Controller:** ESP32
- **Temperature sensor:** DS18B20
- **Cooling outputs:** Two 12 V DC fans controlled through relay outputs
- **Thresholds:** 30°C, 40°C, and 55°C
- **IoT platform:** Blynk
- **Development environment:** Arduino framework / Arduino IDE

## How It Works

1. The DS18B20 measures the surrounding temperature and sends readings to the ESP32 over the OneWire bus.
2. The ESP32 compares each reading against the configured thresholds.
3. At 30°C, the firmware requests Fan 1 to turn on.
4. At 40°C, the firmware requests Fan 2 to turn on as well.
5. At 55°C, the current code sends a Blynk event named `fire_alert`. **The current code also sets both relay outputs LOW at this threshold**, which may turn the fans off depending on the relay module. Review this behavior before using the controller in a real heat-critical environment.

The firmware uses GPIO 4 for the DS18B20 data line and GPIO 18 and GPIO 19 for the two relay outputs. Confirm these pins against the actual assembled circuit before wiring or reproducing the project.

## System Architecture

```text
DS18B20 Sensor
      |
      | OneWire
      v
    ESP32 ---------------- Wi-Fi ---------------- Blynk
      |
      +---- GPIO 18 ---- Relay 1 ---- Fan 1 (12 V)
      |
      +---- GPIO 19 ---- Relay 2 ---- Fan 2 (12 V)
      |
      +---- Critical-temperature event ---- Blynk notification
```

## Hardware

The project documentation describes the following components:

| Component | Purpose |
|---|---|
| ESP32 development board | Reads the sensor, controls outputs, and provides Wi-Fi connectivity |
| DS18B20 digital sensor | Temperature measurement |
| Two 12 V DC fans | Cooling airflow |
| Relay module / fan switching circuit | Switches the fan loads from ESP32 control signals |
| 12 V-to-5 V regulator | Supplies compatible low-voltage components, according to the final circuit |
| Pull-up resistor and wiring | Supports the DS18B20 bus and hardware connections |

**Hardware note:** Check the final schematic and component ratings before powering the circuit. Do not drive 12 V fans directly from ESP32 GPIO pins.

## Software and Libraries

The firmware uses these Arduino libraries:

- `Blynk` for IoT connectivity and event notifications
- `OneWire` for communication with the DS18B20
- `DallasTemperature` for temperature readings
- ESP32 Wi-Fi support provided by the ESP32 Arduino core

Install the ESP32 board package and required libraries through Arduino IDE's Boards Manager and Library Manager.

## Repository Contents

- [Project report](./Applied%20Project%20Report%20final..docx)
- [Final project presentation](./Applied%20project%20final%20presentation.pdf)
- [Project firmware archive](./project_done_with_web.zip)

The firmware is currently provided in the ZIP archive. A cleaned, credential-free source file and a verified circuit schematic should be added as separate files to make the project easier to review and reproduce.

## Testing and Validation

The project report describes hardware prototyping and simulation. For a stronger technical portfolio, add evidence from your own tests, such as prototype photos, a wiring diagram, Blynk dashboard screenshots, and measured temperature / fan-state results.

Do not report numerical accuracy, current consumption, or test counts unless you have measurements or test records to support them.

## Security

Do not commit real Wi-Fi passwords, Blynk authentication tokens, or email credentials. Keep secrets outside the public source code and rotate any real credentials that were previously published in a public repository.

## Future Improvements

- Keep cooling outputs in a clearly defined safe state during critical temperatures
- Add sensor-disconnection detection and fail-safe behavior
- Log temperature readings and fan states over time
- Add a verified schematic and real prototype photos
- Move configuration values into a local, untracked configuration file
- Document repeatable test cases and actual results

## Author

**Oday Haitham Metwalli**  
Electronics Engineering Student  
Interests: IoT, Embedded Systems, Networking, and Cloud Computing
