src equ 30h
dst equ 40h
cnt equ 5

mov r0,#src
mov r1,#dst
mov r2,#cnt

back: mov a,@r0
	mov @r1,a
	inc r0
	inc r1
	
djnz r2,back

loop: sjmp loop

end

