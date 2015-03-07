.model tiny
.code
org 100h
start:	
mov ah, 01h
int 21h
cmp al, 30h
je Print
mov dx, offset msgo
mov ah, 09h
int 21h
mov ah, 4ch
int 20h
msgo db "You don't enter 0$"
Print:
mov dx, offset msg
mov ah, 09h
int 21h
mov ah, 4ch
int 20h
msg db "You enter 0$"
end start
