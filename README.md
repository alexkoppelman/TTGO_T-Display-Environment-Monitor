# TTGO_T-Display ESP32 Environment Monitor

I wanted a small portable device that would show me the Air quality around me. Since I'd like to bring it with (when cycling) it had to be battery operated and work without internet connection.

When close to a known wifi network, it will connect and upload the data to the mqtt server.

A to do item is to store the sensor data when offline and upload "backlog" when online again.

The most tricky part was to find the combination of Sensor libraries that would actually work. Many don't.

Both of the sensors will share the I2C, so the code for the BME280 has been moved to an external file as an include from the main .ino. Taking the work of http://kstobbe.dk/2019/01/28/first-sensor-array/ as example. The CCCS811 code is embedded in the main .ino file.


**Functionality:**
- Shows Temperature, Humidity, Air pressure, eCO2 and TVOC values
- Works Online and Offline
- When online pushes data to MQTT 
- Buttons to Sleep and Reset/Start
- Battery powered for outdoors
- Icons, Startup screen and Go to sleep screen

**Parts List:**
- TTGO T-Display ESP32
- 1000mHa Battery
- BME280
- CCS811

**To Do**
- Humidity values are not coming through. Sensor failing? need to test
- Make a nice box
- Store data when offline and upload "backlog" when online

**Icons / Images**
Created images in Gimp and save in the target size as BMP using the 16bit R5G6B5 profile
Converted the images to .c files using the LCD Image Converter (https://github.com/riuson/lcd-image-converter)


![setup](https://github.com/alexkoppelman/TTGO_T-Display-Environment-Monitor/blob/master/images/setup.jpg?raw=true)

![ui](https://github.com/alexkoppelman/TTGO_T-Display-Environment-Monitor/blob/master/images/screen.jpg?raw=true)

![Startup screen](https://github.com/alexkoppelman/TTGO_T-Display-Environment-Monitor/blob/master/images/startup.jpg?raw=true)
