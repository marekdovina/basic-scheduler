# basic-scheduler
ESP8266 Arduino task scheduler based on NTPClient 

You can run any functions in a loop() but additionaly you have special schedulers to run specific functions only once in 5/15/30 minutes and on midnight.

EXAMPLE:
- run movement sensor all the time but run temperature sensor only every 5 minutes
