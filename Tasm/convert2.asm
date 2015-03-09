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
mov si, bx
call scan_dec
call print_dec


mov ah, 4ch
int 20h

input_string db 30, ?, 30 dup(?)
HexTable db '0123456789ABCD'
;-----------------------------------
;write number from binary form in AX
;Enter: CX->length, DS:SI->string
;Exit: 	AX->number
;Destr: AX, DX, SI
;-----------------------------------
scan_bin	proc
		xor dx, dx
		cld
		scan_bin_str:	lodsb
				shl dx, 1
				and al, 1
				or dl, al
				loop scan_bin_str
		mov ax, dx
		ret
		endp
;-----------------------------------
;write number from oct form in AX
;Enter: CX->length, DS:SI->string
;Exit: 	AX->number
;Destr: AX, DX1, SI
;-----------------------------------
scan_oct	proc
		xor dx, dx
		cld
		scan_oct_str:	lodsb
				shl dx, 3
				sub al, 30h
				or dl, al
				loop scan_oct_str
		mov ax, dx		
		ret
		endp

;-----------------------------------
;write number from dec form in AX
;Enter: CX->length, DS:SI->string
;Exit: 	AX->number
;Destr: AX, DX, SI, BX
;-----------------------------------
scan_dec	proc
		xor dx, dx
		mov bx, 0Ah
		cld
		scan_dec_str:	mov ax, dx
				mul bx
				mov dx, ax
				lodsb
				xor ah, ah
				sub al, 30h
				add dx, ax
				loop scan_dec_str
		mov ax, dx
		ret
		endp

;-----------------------------------
;write number from hex form in AX
;Enter: CX->length, DS:SI->string
;Exit: 	AX->number
;Destr: AX, DX, SI
;-----------------------------------
scan_hex	proc
		xor dx, dx
		cld
		scan_hex_str:	lodsb
				shl dx, 4
				sub al, 30h
				cmp al, 10
				jae scan_hex_symb
				print_hex_symb:
						or dl, al
						loop scan_hex_str
		mov ax, dx		
		ret
		scan_hex_symb:
				sub al, 7
				jmp print_hex_symb
		endp


;------------------------------------------------
;Print number in dec form
;Input: AX->number
;Output: None
;Dest: DX, CX, AX
;-------------------------------------------------
;Max number length is 65535. I will decrement hight digit in number,
;while number don't negative
print_dec	proc		
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
end start
