# TTGO_T-Display-Environment-Monitor

I wanted a small portable device that would show me the Air quality around me. Since I'd like to bring it with (when cycling) it had to be battery operated and work without internet connection.
When close to a known wifi network, it will connect and upload the data to the mqtt server.

**Functionality:**
- Works Online and Offline
- When online pushes data to MQTT 
- Buttons to Sleep and Reset/Start
- Battery powered for outdoors

**Parts List:**
- TTGO T-Display ESP32
- 1000mHa Battery
- BME280
- CCS811

**To DO**
- Humidity values are not coming through. Sensor failing? need to test
- Make a nice box
