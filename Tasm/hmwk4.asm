.model tiny
.code
org 100h
start:
	mov ah, 08h
	int 21h
	mov ah, 0
	jmp prime
end_prime:
	mov ah, 09h               ; I should print something anyway
	cmp cx, 1
	jne no_prime
	mov dx, offset true_msg
	jmp end_program
no_prime:
	mov dx, offset false_msg
end_program:
	int 21h
	mov ah, 08h
	int 21h                   ; key press delay
	int 20h
prime:	
	mov dx, 0h
	mov dl, al                ; save number in dx
	shr al, 1                 ; divide by 2
	mov cl, al
check_cycle:
	cmp cl, 1
	je end_prime
;	mov al, dl
	mov ax, dx
	div cl
	test ah, ah
	je end_prime
	dec cx
	jne check_cycle
	
true_msg db "Number is prime", 0Ah, 0Dh, "$"
false_msg db "Number is not prime", 0Ah, 0Dh, "$"
end     start

	
	
	
	
	
	
	
	
	
	