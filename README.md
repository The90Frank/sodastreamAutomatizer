# sodastreamAutomatizer

An Arduino project that automates SodaStream carbonation by controlling a servo motor based on pressure sensor readings, with a rotary encoder for threshold adjustment and a 7-segment display.

## How it works

1. Set the desired pressure threshold using the rotary encoder (displayed on the 7-segment screen)
2. Press the trigger button to start carbonation - the servo activates (90°)
3. The pressure sensor continuously monitors the CO2 pressure
4. When pressure reaches the threshold, the servo automatically disengages (0°) and the LED turns off

## Pin mapping

| Pin | Component | Function |
|---|---|---|
| A0 | Pressure sensor | Analog pressure reading (128-sample average) |
| 1 | Trigger button | Start/stop carbonation (interrupt) |
| 2, 3 | Rotary encoder | Adjust pressure threshold (interrupt) |
| 5 | LED | Active indicator |
| 7 | Servo | Controls the SodaStream push mechanism |
| 8, 9 | TM1637 display | Shows pressure or threshold value |

## Features

- **Automatic shutoff** when target pressure is reached
- **Stable readings** via 128-sample averaging on the pressure sensor
- **Interrupt-driven controls** for responsive encoder and button input
- **Live display** showing current pressure (active) or threshold (idle)

## Dependencies

- Arduino IDE
- `Servo.h` (built-in)
- `TM1637.h` - 7-segment display driver

## License

Apache License 2.0 - see [LICENSE](LICENSE) for details.
