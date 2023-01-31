; Lab1_Assemblymain.asm

; This example accompanies the books
;   "Embedded Systems: Introduction to the MSP432 Microcontroller",
;       ISBN: 978-1512185676, Jonathan Valvano, copyright (c) 2017
;   "Embedded Systems: Real-Time Interfacing to the MSP432 Microcontroller",
;       ISBN: 978-1514676585, Jonathan Valvano, copyright (c) 2017
;   "Embedded Systems: Real-Time Operating Systems for ARM Cortex-M Microcontrollers",
;       ISBN: 978-1466468863, , Jonathan Valvano, copyright (c) 2017
; For more information about my classes, my research, and my books, see
; http://users.ece.utexas.edu/~valvano/
;
;Simplified BSD License (FreeBSD License)
;Copyright (c) 2017, Jonathan Valvano, All rights reserved.
;
;Redistribution and use in source and binary forms, with or without modification,
;are permitted provided that the following conditions are met:
;
;1. Redistributions of source code must retain the above copyright notice,
;   this list of conditions and the following disclaimer.
;2. Redistributions in binary form must reproduce the above copyright notice,
;   this list of conditions and the following disclaimer in the documentation
;   and/or other materials provided with the distribution.
;
;THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
;LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
;DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
;LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
;AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
;OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
;USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;
;The views and conclusions contained in the software and documentation are
;those of the authors and should not be interpreted as representing official
;policies, either expressed or implied, of the FreeBSD Project.

       .thumb
       .text
       .align 2
       .global Convert
       .global main


Inputs .long 2000,2733,3466,4199,4932,5665,6398,7131,7864,8597,9330,10063,10796,11529, 12262,12995
Expect .long 800,713,496,380,308,259,223,196,175,158,144,132,122,114,106,100


main:  .asmfunc
     MOV R4, #0          ; R4 = 0 = Correct    (0 <= error < 1) or (-1 < error <= 0)
     MOV R5, #0          ; R5 = 0 = OffByOne   (1 <= error < 2) or (-2 < error <= -1)
     MOV R6, #0          ; R6 = 0 = Errors     (2 <= error    ) or (     error <= -2)
     MOV R7, #16         ; counter
     LDR R10, InputsAddr ; R10 = &Inputs (pointer
     LDR R11, ExpectAddr ; R11 = &Expect (pointer)
Test LDR R0, [R10],#4    ; input value.  R10+=4 after ops - OHL
     BL  Convert         ; R0 = Convert()
     LDR R1, [R11],#4    ; R1 = Expect[index] (value). R11+=4 after ops - OHL
     SUB R2, R0, R1      ; Convert(Inputs[index]) - Expect[index]
     CMP R2, #0          ; is Convert(Inputs[index]) - Expect[index] (R2) == 0
     BEQ OK
     CMP R2, #1          ; is Convert(Inputs[index]) - Expect[index] (R2) == 1
     BEQ One
     CMN R2, #1          ; is Convert(Inputs[index]) - Expected[index] (R2) == -1
     BEQ One
     ADD R6, R6, #1      ; Error = Error + 1
     B   Done
OK   ADD R4, R4, #1      ; Correct = Correct + 1
     B   Done
One  ADD R5, R5, #1      ; OffByOne = OffByOne + 1
Done SUBS R7, R7, #1
     BNE Test
loop B  loop             ; stall here and observe the registers
    .endasmfunc




ExpectAddr .field Expect,32
InputsAddr .field Inputs,32

    .end
