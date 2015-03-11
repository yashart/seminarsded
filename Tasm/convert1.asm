.model tiny, C
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
push 0FFFFh
call print_dec
pop cx
push 0FFFFh
call print_hex
pop cx
push 0FFFFh
call print_oct
pop cx
push 0FFFFh
call print_bin
pop cx

mov ah, 4ch
int 20h


;--------------------------------------------------------
;print number in binary form
;Entry: AX->number
;Exit: None
;Destr: AX, CX, DL, AH, BX
;--------------------------------------------------------
print_bin	proc number:word
		mov ax, number
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
;Destr: AX, CX, DL, BX
;--------------------------------------------------------
print_oct	proc number:word
		mov ax, number
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
		shift_oct:	mov bx, ax
				and bx, 0E000h
				shr bx, 13
				mov dl, [offset HexTable + bx]
				shl ax, 3
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
;Destr: AX, CX, DL, BX
;--------------------------------------------------------		
print_hex	proc number:word
		mov ax, number
		mov cx, 4
		;for(int i=0, i<16; i++)
		shift_hex:	mov bx, ax
				and bx, 0f000h
				shr bx, 12
				mov dl, [offset HexTable + bx]
				shl ax, 4
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
;Dest: DX, CX, AX
;-------------------------------------------------
;Max number length is 65535. I will decrement hight digit in number,
;while number don't negative
print_dec	proc number:word
		mov ax, number	
		xor cx, cx
		mov bx, 10
		div_on_10:	
				xor dx, dx
				div bx
				push dx
				inc cx
				cmp dx, 0h
				je pop_end_nul_dx
				jmp div_on_10
		pop_end_nul_dx:
		pop dx
		dec cx
		print_num_in_dec:
				pop dx
				xor dh, dh
				add dl, 30h
				print_num dl
				loop print_num_in_dec
		ret
		endp			
HexTable db '0123456789ABCDEF'
end start