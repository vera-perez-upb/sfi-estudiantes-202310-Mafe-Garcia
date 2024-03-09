# Exercise 16

1. **What do you think will happen when Serial.available() is used?** It will check if there's anything to read, but won't read yet

2. **What do you think will happen when Serial.read() is used?** What is being sent will actually be read by the machine.

3. **What do you think will happen if Serial.read() is used but there's nothing in the reception buffer?** It will return -1, because it sees there's no data.

4. **A common pattern when working with the serial port is this:**
```
if(Serial.available() > 0)
{
    int dataRx = Serial.read()
}
```
**How many pieces of data does Serial.read() read?** one, because that's the immediate number of possible ones after 0.

5. **What if I want to send more than one piece of data?** I would use a while before the if asking if the user wants to store more data, then I would also usa a for and make a cycle with the amount of data the user wants to store, and create an array with that same lenght, then the if would be used the same way it was presented before.

6. **What happens if there's data being sent to the serial port but you forget to call Serial.read()?** Then they won't be read.


