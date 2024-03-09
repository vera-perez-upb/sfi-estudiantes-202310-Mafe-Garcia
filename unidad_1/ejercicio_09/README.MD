# Exercise 9:

I must create two other tasks, the task 2 must send a message every 2 seconds, meaning in a 0.5 Hz frequency, and the third must be every 4 seconds, at a 0.25 Hz frequency

I will try to make every task work for 8 seconds and then go to th next until it resets to task 1

The version i created works at 8 seconds the first task, 16 the second, and 24 the third.

I basically copied the first one, created a counter that keeps counting how many times a message has been sent and when it's been sent 7 times it changes to the next task, when the counter gets to 25 it reverst to 0 and goes back to the first task.

I also added multiple if statements i the loop so it decides what the next task is.

