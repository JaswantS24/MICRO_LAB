// -- DO NOT CHANGE ANYTHING UNTIL THE **** LINE--//
ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL TAKE_INP
CALL QUANT_ENC
CALL LED_DISP
HERE: SJMP HERE
ORG 130H
// *****************
DELAY_8s:
PUSH 00H
mov r0,#2
h4: acall delay_4s
loop3: djnz r0 , h4
POP 00H
RET

DELAY_4s:
PUSH 00H
PUSH 01H
mov r0, #20
loop:
mov r1,#199
h3: acall delay_1ms
loop2: djnz r1 , h3
djnz r0, loop
POP 01H
POP 00H
RET

delay_1ms:
push 00h
mov r0, #4
h2: acall delay_250us
djnz r0, h2
pop 00h
ret

delay_250us:
push 00h
mov r0, #244
h1: djnz r0, h1
pop 00h
ret


TAKE_INP:

mov p1, #0Fh
mov r0, #60h
setb p1.4
clr p1.5
clr p1.6
clr p1.7
mov B, #08H
mov r1, #01H

lp1: ORL p1, #0FH
acall delay_8s
mov a, p1
swap a
clr c
subb a, r1
mov @r0, a
mov a, p1
swap a
inc a
swap a
mov p1, a
inc r0
inc r1
djnz b, lp1

mov p1, #00H

mov r0, #60H
mov r1, #61H
mov r2, #04H
lp2: mov a, @r1
swap a
add a, @r0
mov @r0, a
inc r0
inc r0
inc r1
inc r1
djnz r2, lp2
ret

QUANT_ENC:

MOV R2, #04H
MOV R0, #60H
MOV R1, #70H

CASE1: MOV A, @R0
CJNE A, #0C0H, form1
form1: JC CASE2
MOV @R1, #80H
JNC generic

CASE2: CJNE A, #80H, form2
form2: JC CASE3
MOV @R1, #40H
JNC generic

CASE3: CJNE A, #40H, form3
form3: JC CASE4
MOV @R1, #20H
JNC generic

CASE4: MOV @R1, #10H
generic: INC R0
INC R0
INC R1
DJNZ R2, CASE1
RET

LED_DISP:
lop2: mov r0, #04H
mov r1, #70H
lop1: mov p1, @R1
acall delay_4s
inc r1
djnz r0, lop1
SJMP lop2

RET

END