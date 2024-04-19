# Exercise 6:

We must explain what these pieces of code do:

        SerialPort _serialPort =new SerialPort();  
        _serialPort.PortName = "/dev/ttyUSB0";
        _serialPort.BaudRate = 115200;
        _serialPort.DtrEnable =true;
        _serialPort.Open();

This part is declaring a port unity will communicate with, the second line is saying the name of the port, the computer will look for it, if it's wrong communication will be impossible, the third line is stablisihng the rate at which data is sent to and from the port, DtrEnable is enabling Data Terminal Ready, this means the port is ready to communicate with the computer, 