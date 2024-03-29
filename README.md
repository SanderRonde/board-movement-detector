# Arduino board movement detector

This repo contains the code for an arduino board that detects movement and reports it to a server. It works by using an infrared radar motion sensor to detect any movement. Since this project is built to accomodate a bunch of different types of sensors (proximity-only, human-specific, long-range), there are a bunch of different configurations.

This project uses [PlatformIO](https://platformio.org/) for simple uploading and interfacing with the board itself.

This project is part of the larger [home-automation](https://github.com/SanderRonde/home-automation) project, where this is part of the movement module.

## PCB

PCB source file (in format of [EasyEda](https://easyeda.com)) can be found at `pcb/board-easyeda.json`.

It takes an ESP8266 devkit board (can be either the wide or narrower one), a simple screw terminal and a `US-016` ultrasonic movement sensor

![PCB](./pcb/board.png)

## License

```text
Copyright 2020 Sander Ronde

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```