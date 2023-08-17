# Sensor Data Visualization and Logging (MATLAB)

This MATLAB script demonstrates how to visualize and log sensor data collected from an Arduino board. The script reads pH, temperature, and distance sensor values and plots them over time.

## Requirements

- MATLAB with Arduino Hardware Support Package

## Usage

1. Install the MATLAB Arduino Hardware Support Package.
2. Connect your Arduino board to your PC.
3. Open MATLAB and run the following command to establish communication:

          a = arduino(0)

4. Copy and paste the provided MATLAB code into the MATLAB command window.
5. The script will read pH, temperature, and distance sensor values from the Arduino board and plot them over time.

## Note

- Adjust the `interv` variable to control the data collection interval.
- Customize and adapt the code for your specific sensor connections and requirements.
