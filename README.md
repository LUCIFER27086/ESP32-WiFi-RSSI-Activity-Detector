# ESP32 Wi-Fi RSSI Activity Detection Experiment

A small ESP32 electronics experiment exploring whether changes in nearby Wi-Fi
signal strength (RSSI) can be used as an indicator of activity.

## What it does

The ESP32 periodically scans for nearby Wi-Fi networks and finds the strongest
RSSI value. It compares the current value with the previous reading. If the
change is larger than a selected threshold, the program reports an activity
change over the Serial Monitor.

## Hardware

- ESP32 development board
- USB cable
- Computer with Arduino IDE

No additional sensor is required for this experiment.

## How it works

1. The ESP32 performs a Wi-Fi scan.
2. It finds the strongest detected RSSI value.
3. The value is compared with the previous reading.
4. A sufficiently large change is reported as an activity change.
5. A short cooldown prevents repeated messages from being generated too
   frequently.

## Important limitation

This project does **not** reliably identify a particular phone.

RSSI is affected by many factors, including distance, orientation, walls,
other wireless devices and normal fluctuations in the environment. Therefore,
this project should be considered an experiment into using wireless signal
changes for activity detection rather than a reliable phone-detection system.

## What I learned

- How an ESP32 can scan nearby Wi-Fi networks.
- How RSSI values can be obtained and compared.
- How noisy real-world wireless measurements can be.
- Why thresholds and cooldown periods are useful when working with sensor-like
  data.
- That a simple prototype may need filtering and more controlled experiments
  before it can become a reliable system.

## Possible improvements

- Collect and store RSSI data for analysis.
- Test the system at different distances and orientations.
- Use filtering or averaging to reduce noise.
- Track specific devices instead of only the strongest network.
- Compare multiple measurements before deciding that activity occurred.

## Files

- `ESP32_WiFi_RSSI_Activity_Detector.ino` - Arduino IDE source code.
