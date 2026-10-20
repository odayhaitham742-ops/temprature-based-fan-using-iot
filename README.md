# IoT Temperature-Based Cooling Controller

An ESP32-based cooling controller that monitors temperature with a DS18B20 digital sensor and controls two 12 V DC fans using configurable temperature thresholds. The project also integrates Wi-Fi, Blynk monitoring, and email notifications for remote awareness of high-temperature conditions.

## Project Overview

The controller reads temperature from the DS18B20 sensor and evaluates it against three thresholds: **30°C, 40°C, and 55°C**. The ESP32 controls the fan outputs and reports temperature data to Blynk. At the critical threshold, the firmware is intended to raise an alert through Blynk and email.

This repository currently includes the project report, presentation, and this README. Add the final source code, verified schematic, and real prototype photos as separate files to make the project easier to reproduce and review.

## Features

- Digital temperature sensing with DS18B20
- Threshold-based control for two 12 V DC fans
- ESP32 Wi-Fi connectivity
- Blynk temperature monitoring and event notifications
- Email notifications, as described in the project report
- Power conversion and interface circuitry for the hardware prototype

## System Architecture

```text
DS18B20 Temperature Sensor
            |
            v
           ESP32
        /    |     \
       v     v      v
 Fan outputs Wi-Fi  Critical alert
       |      |       /      \
       v      v      v        v
  12 V Fans  Blynk  Blynk app  Email
```

Update this diagram if it differs from the final implemented wiring or notification flow.

## Hardware Components

| Component | Purpose |
|---|---|
| ESP32 development board | Main controller and Wi-Fi connectivity |
| DS18B20 digital temperature sensor | Temperature measurement |
| Two 12 V DC fans | Cooling |
| 12 V-to-5 V regulator | Power conversion for compatible components |
| Fan switching/driver circuit | Interface between ESP32 control outputs and fan loads |
| Supporting components | Pull-up resistor, wiring, and other circuit components used in the prototype |

Refer to the final schematic and bill of materials for the exact part numbers and connections.

## Temperature Thresholds

The project uses three thresholds: **30°C, 40°C, and 55°C**.

| Temperature | Intended behavior described in the project |
|---|---|
| Below 30°C | Normal monitoring; fans remain off |
| 30°C to below 40°C | Activate Fan 1 |
| 40°C to below 55°C | Activate both fans |
| 55°C and above | Trigger the critical-temperature alert |

**Firmware note:** The sample code previously included in this README sets both relay outputs LOW when the temperature reaches 55°C. Confirm that this is the intended safety behavior for your actual relay module and cooling application before relying on the system. For many cooling applications, maintaining cooling during a high-temperature alert may be preferable, but the correct response depends on the system's safety requirements.

## Software

The project description references:

- Arduino IDE and ESP32 board support
- OneWire and DallasTemperature libraries for the DS18B20
- Blynk library for monitoring and events
- ESP32 Wi-Fi support
- An SMTP/email integration for email notifications

Confirm the exact libraries and versions against the final firmware before publishing them as tested requirements.

## Getting Started

1. Install the Arduino IDE and the ESP32 board support package.
2. Install the libraries used by the final firmware.
3. Assemble the hardware using the verified schematic.
4. Configure Wi-Fi, Blynk, and email settings locally.
5. Select the correct ESP32 board and serial port.
6. Upload the firmware and open the Serial Monitor.
7. Test sensor readings, fan switching at each threshold, Blynk updates, and email alerts.

Never commit real Wi-Fi passwords, Blynk tokens, email passwords, or other credentials. Keep private configuration outside version control and use placeholder values in any example configuration.

## Repository Files

- [Project report](./Applied%20Project%20Report%20final..docx)
- [Project presentation](./Applied%20project%20final%20presentation.pdf)

The repository also contains `project_done_with_web.zip`. Add a short description of its contents or replace it with a clearly named folder/file if it is relevant to the project.

## Testing and Validation

Record results from the actual prototype and keep claims reproducible. A useful test record includes the measured temperature, expected fan state, actual fan state, and whether notifications were received.

| Test | What to record |
|---|---|
| Sensor reading | Reading compared with a reference thermometer, if available |
| 30°C threshold | Fan 1 switching behavior |
| 40°C threshold | Fan 2 switching behavior |
| 55°C threshold | Alert and fan behavior |
| Blynk integration | Whether dashboard updates and events arrive |
| Email integration | Whether the notification is received |
| Power circuit | Measured regulator output and fan supply current |

Only publish accuracy, current-consumption, and repeated-test figures when you have measurements or test records to support them.

## Recommended Repository Structure

As you improve the repository, consider organizing it like this:

```text
.
├── README.md
├── src/          # Final ESP32 firmware
├── hardware/     # Verified schematic and pinout
├── docs/         # Project report and presentation
└── media/        # Prototype photos and demo video
```

Move the existing report and presentation into `docs/` only when you're ready to update their links and preserve the files.

## Possible Future Improvements

- Temperature history and data logging
- Configurable thresholds through the dashboard
- Sensor-disconnection detection and fail-safe behavior
- Over-the-air firmware updates
- Fan speed control, if supported by the selected driver and fan hardware

## Author

**Oday Haitham Metwalli**  
Electronics Engineering Student  
Interests: IoT, Embedded Systems, Networking, and Cloud Computing

## License

Add a license if you want to specify how others may use, modify, and redistribute this project.
