# state-machine
### My AVR project made to check the corectness of university problem solution in reality
Board contains 4 buttons and 4 LEDs.
### Manual:
<ol>
  <li>Setup vairables in first block</li>
  <li>Write your own code in loop</li>
  <li>Don't forget to assign proper variables to keys(aKx) and LEDs (LDx)</li>
</ol>
Built using CMake  (make sure to set flag <b>-DCMAKE_SYSTEM_NAME=Generic</b>)
### Used hardware:
<ul>
  <li>MCU: ATMega48PA</li>
  <li>Programmer: USBasp</li>
</ul>
(If you want to use other AVR MCU remember to change MCU in CMAKE file)

Programmed using AVRdude

Sheet:
Sheet:<br>
![Image of board sheet](https://github.com/KrystianSoltys/state-machine/blob/master/img/Schematic_state_machine_v1_2023-11-01.png)

Photo:<br>
![Board photo](https://github.com/KrystianSoltys/state-machine/blob/master/img/Photo_state_machine_v1_2024-03-25.png)
