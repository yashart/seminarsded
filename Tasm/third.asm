.model tiny
.code
org 100h
start:
mov ah, 0ah
mov bx, offset pas
mov si, offset string
mov dx, offset string
add si, 02h
int 21h
check:
mov cl , ds:[bx]
mov ch , ds:[si]
cmp cl, ch
jne bad
cmp ch, 64h	;symbol d
je success
add si, 01h
add bx, 01h
jmp check
pas db "Password$"
success:
mov dx, offset msg
mov ah, 09h
int 21h
mov ah, 4ch
int 20h
msg db "Yes!!$"
bad:
mov dx, offset msgo
mov ah, 09h
int 21h
mov ah, 4ch
int 20h
msgo db "No$"
string db 80,?,80 dup(?)
end start