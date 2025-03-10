# AVR Wireless Programmer
##### This program was written in 2023 and can be run on the Arduino platform. This program uses esp8266 wifi and arduino uno r3 devices. The connections and pins can be seen in the document. It is used in all equipment that uses micro avr, such as elevators, entry and exit equipment, control panels, ....

# Project benefits
- Save time on rebuilding
- Ease of use of this technology
- Smartening products
- The low cost of this project

# STA Mode Programmer
> In the image above, as you can see, there is a central router to which the NODES are connected wirelessly and are in a network with each other. Now in this scenario, the ESP is in STA mode and an IP has been assigned to it. When we connect to the central router with our computer, we can communicate with the ESP chip and then upload our codes to the microcontroller. In all scenarios, we must consider that we must first compile our code and send the HEX and BIN output to the ESP to upload it to the microcontroller.

# AP Mode Programmer
> In the document image, as you can see, the Esp chip is in Access Point mode and finally, after connecting the laptop to the esp ssid, we are on a network and can upload our codes to the micro

# Running APP on Windows
> AVRDUDE is an application that exists in different operating systems and can be used as CLI and GUI. The main difference of this tool is that it can be transferred to a specific IP and port as a TCP Client, which no longer requires a COM connection in the system and uploads the main program through communication networks. To use CLI, first place the file in the System32 folder and then define it as Environment in your system.After you have defined this program as an Environment in the system, to program the hex file, simply place your laptop on the same network as the ESP and enter the IP and port 328 that was in the program in the AVRDUDE command. You must also specify the path to the HEX file on your laptop in the command to transfer the file to the ESP IP from that path.


```javascript
avrdude –C C:\Windows\System32\avrdude.conf -v -p atmega328p -c arduino -P net:192.168.10.243:328 -U flash:w:E:\RGB.ino.hex:i

```

