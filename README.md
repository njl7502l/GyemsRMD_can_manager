# GyemsRMD_manager
<!--
## control command list

1. Read PID data command
```
(0x30,{0}) -> Motor -> (0x30,val)
```
2. Write PID to RAM command 0x31
```
(0x31,val) -> Motor -> (0x31,val)
```
3. Write PID to ROM command 0x32
```
(0x32,val) -> Motor -> (0x32,val)
```
4. Read acceleration data command 0x33
```
(0x33,{0}) -> Motor -> (0x33,val)
```
5. Write acceleration data to RAM command 0x34
```
(0x34,val) -> Motor -> (0x34,val)
```
6. Read encoder data command 0x90
```
(0x90,{0}) -> Motor -> (0x90,val)
```
7. Write encoder offset command 0x91
```
(0x91,val) -> Motor -> (0x91,New Encoder Offset)
```
8. Write current position to ROM as motor zero command 0x19
```
(0x19,{0}) -> Motor -> (0x19,val)

notice :
1. This command needs to be powered on again to take effect. 
2．This command will write the zero position to ROM. Multiple writes will affect the chip life. so not recommended to use it frequently.
```
9. Read multi turns angle command 0x92
```
(0x92,{0}) -> Motor -> (0x92,val)
```
10. Read single circle angle command 0x94
11. Read motor status 1 and error flag commands 0x9A
12. Clear motor error flag command 0x9B
13. Read motor status 2 0x9C
14. Read motor status 3 0x9D
15. Motor off command 0x80
16. Motor stop command 0x81
17. Motor running command 0x88
18. Torque closed-loop command 0xA1
19. Speed closed-loop command 0xA2
20. Position closed-loop command 1 0xA3
21. Position closed-loop command 2 0xA4
22. Position closed-loop command 3 0xA5
23. Position closed-loop command 4 0xA6
-->