# Motion Detector Arduino

## Overview
This repository contains the Arduino microcontroller code for an infrared motion sensor that interfaces with an Android application. When motion is detected, the microcontroller communicates with the Android app via Bluetooth to trigger an alert sound and display a notification.

## Features
- **Motion Detection**: Utilizes an infrared motion sensor to detect movement.
- **Bluetooth Communication**: Sends alerts to an Android application via Bluetooth.
- **Interactive Notifications**: Plays a sound and shows a notification on the Android device when motion is detected.
- **Alarm Control**: Allows the alarm to be temporarily disabled from the Android app.
- **Connection Loss Handling**: Plays a distinct sound if the Bluetooth connection is lost during operation.

## Requirements
- An Arduino microcontroller.
- An infrared motion sensor.
- The [Arduino ESP8266 Helper library] for the Wi-Fi functionality.
- A compatible Android application.

## Installation
1. Clone this repository to your local machine.
2. Open the Arduino code in the Arduino IDE.
3. Connect the infrared motion sensor to your Arduino as per the circuit diagram provided.
4. Upload the code to your Arduino microcontroller.
5. Ensure the Android application is installed and running on your device.
6. Pair your Arduino with your Android device via Bluetooth.

## Usage
Once the setup is complete, the system will automatically start detecting motion and sending notifications to the connected Android application. You can disable the alarm for 1 minute through the app interface.

## Contributing
Contributions are welcome! If you have any suggestions or improvements, please fork the repository and submit a pull request.

## License
This project is open-sourced under the MIT License. See the LICENSE file for more details.

## Contact
For any queries or issues, please open an issue on the GitHub repository or contact the maintainers directly.
