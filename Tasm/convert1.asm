.model tiny
.code
org 100h
;-------------------------------------------------------
;print number in console
;Entry: None
;Exit:	None
;Destr:	DL, AH
;---------------------------------------------------------
print_num	macro	num
		mov dl, num
		mov ah, 02h
		int 21h
		endm

start:
mov ax, 0FFFFh
call print_dec

mov ah, 4ch
int 20h


;--------------------------------------------------------
;print number in binary form
;Entry: AX->number
;Exit: None
;Destr: AX, CX, DL, AH, BX
;--------------------------------------------------------
print_bin	proc
		mov cx, 16
		;for(int i=0, i<16; i++)
		shift:		shl ax, 1
				mov dl, 30h
				adc dl, 0	;add cf to dc
				push ax
				print_num dl 
				pop ax
					loop shift
		ret
		endp
;--------------------------------------------------------
;print number in oct form
;Entry: AX->number
;Exit:	None
;Destr: AX, CX, DL, AH, BX
;--------------------------------------------------------
print_oct	proc
		mov cx, 5
		;need move ax to 15 bit
		mov dl, 0h
		shl ax, 1
		adc dl, 0
		add dl, 30h ;0 - symbol
		push ax
		print_num dl
		pop ax
		;for(int i=0, i<16; i++)
		shift_oct:	mov dl, 0h

				shl dl, 1
				shl ax, 1
				adc dl, 0	;add cf to dc
				
				shl dl, 1
				shl ax, 1
				adc dl, 0	;add cf to dc
				
				shl dl, 1
				shl ax, 1
				adc dl, 0	;add cf to dc
								
				add dl, 30h
				
				push ax
				print_num dl 
				pop ax
					loop shift_oct
		ret
		endp
		
;--------------------------------------------------------
;print number in hex form
;Entry: AX->number
;Exit:	None
;Destr: AX, CX, DL, AH, BX
;--------------------------------------------------------		
print_hex	proc
		mov cx, 4
		;for(int i=0, i<16; i++)
		shift_hex:	mov dl, 0h

				shl dl, 1
				shl ax, 1
				adc dl, 0	;add cf to dc
				
				shl dl, 1
				shl ax, 1
				adc dl, 0	;add cf to dc
				
				shl dl, 1
				shl ax, 1
				adc dl, 0	;add cf to dc
				
				shl dl, 1
				shl ax, 1
				adc dl, 0	;add cf to dc
				
				cmp dl, 10
				jae print_num10
								
				add dl, 30h
				push ax
				print_num dl 
				pop ax
					loop shift_hex
		ret
				print_num10:	add dl, 37h;41h is symbol A
						push ax
						print_num dl
						pop ax
					loop shift_hex
		ret
		endp

;------------------------------------------------
;Print number in dec form
;Input: AX->number
;Output: None
;Dest: DL, CX, AX
;-------------------------------------------------
;Max number length is 65535. I will decrement hight digit in number,
;while number don't negative
print_dec	proc		
		;start_inc_digit_5:
				mov dl, 0h
				mov cx, 10000
				call dec_digit_in_number
				push ax
				add dl, 30h
				print_num dl
				pop ax
		;start_inc_digit_4:
				mov dl, 0h
				mov cx, 1000
				call dec_digit_in_number
				push ax
				add dl, 30h
				print_num dl
				pop ax
		;start_inc_digit_3:
				mov dl, 0h
				mov cx, 100
				call dec_digit_in_number
				push ax
				add dl, 30h
				print_num dl
				pop ax
		;start_inc_digit_2:
				mov dl, 0h
				mov cx, 10
				call dec_digit_in_number
				push ax
				add dl, 30h
				print_num dl
				pop ax
		;start_inc_digit_1:
				mov dl, 0h
				add ax, 30h
				mov dl, al
				print_num dl
		ret
		endp		
;------------------------------------------------------
;Function for decrement digits in number.
;Input: AX->number, CL->digit, DL->digit for print
;Output: AX->new_number
;Destr: DL, AX
;------------------------------------------------------
dec_digit_in_number	proc
			cmp ax, cx
			jb other_digit
			sub ax, cx
			inc dl
			call dec_digit_in_number
			ret
			
			other_digit:	ret
			endp
end start