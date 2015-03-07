.model tiny
.code
org 100h
;-----------------------------------
;scan number from console in string
;Entry: DS:DX, AH
;Exit: None
;Destr: AH
;-----------------------------------
scan_string	macro
		mov ah, 0aH
		int 21h
		endm
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
mov dx, offset input_string
scan_string
inc dx
mov bx, dx
mov ch, 0h
mov cl, [bx]
inc bx
call scan_hex
call print_dec


mov ah, 4ch
int 20h

input_string db 30, ?, 30 dup(?)
;-----------------------------------
;write number from binary form in AX
;Enter: CX->length, DS:BX->string
;Exit: 	AX->number
;Destr: AX, DX1, SI
;-----------------------------------
scan_bin	proc
		mov ax, 0h
		mov dx, 1
		add bx, cx
		dec bx
		shift_bin_number:
				push ax
				push dx
				
				mov ax, ds:[bx]
				mov ah, 0h
				mov si, ax
				sub si, 30h
				;mul dx on 2^
				
				mov ax, si
				mul dx
				mov si, ax
				pop dx
				pop ax
				
				add ax, si	
				dec bx
				shl dx, 1
				loop shift_bin_number
		ret
		endp
;-----------------------------------
;write number from oct form in AX
;Enter: CX->length, DS:BX->string
;Exit: 	AX->number
;Destr: AX, DX1, SI
;-----------------------------------
scan_oct	proc
		mov ax, 0h
		mov dx, 1
		add bx, cx
		dec bx
		shift_oct_number:
				push ax
				push dx
				
				mov ax, ds:[bx]
				mov ah, 0h
				mov si, ax
				sub si, 30h
				;mul dx on 8^
				
				mov ax, si
				mul dx
				mov si, ax
				pop dx
				pop ax
				
				add ax, si	
				dec bx
				shl dx, 3
				loop shift_oct_number
		ret
		endp

;-----------------------------------
;write number from dec form in AX
;Enter: CX->length, DS:BX->string
;Exit: 	AX->number
;Destr: AX, DX1, SI
;-----------------------------------
scan_dec	proc
		mov ax, 0h
		mov dx, 1
		add bx, cx
		dec bx
		shift_dec_number:
				push ax
				push dx
				
				mov ax, ds:[bx]
				mov ah, 0h
				mov si, ax
				sub si, 30h
				;mul dx on 10^
				
				mov ax, si
				mul dx
				mov si, ax
				pop dx
				pop ax
				
				add ax, si	
				dec bx
				
				push ax
				mov ax, 10
				mul dx
				mov dx, ax
				pop ax
				
				loop shift_dec_number
		ret
		endp

;-----------------------------------
;write number from hex form in AX
;Enter: CX->length, DS:BX->string
;Exit: 	AX->number
;Destr: AX, DX1, SI
;-----------------------------------
scan_hex	proc
		mov ax, 0h
		mov dx, 1
		add bx, cx
		dec bx
		shift_hex_number:
				push ax
				push dx
				
				mov ax, ds:[bx]
				mov ah, 0h
				mov si, ax
				
				cmp si, 40h
				jb in_si_number
				sub si, 55
				jmp in_si_string
				in_si_number:
					sub si, 30h
				in_si_string:
				;mul dx on F^
				
				mov ax, si
				mul dx
				mov si, ax
				pop dx
				pop ax
				
				add ax, si	
				dec bx
				shl dx, 4
				loop shift_hex_number
		ret
		endp


;--------------------------------------------------
;It is code for print number in dec
;--------------------------------------------------
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
