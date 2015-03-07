.model tiny
.code
org 100h
start:
mov ah, 01h
int 21h
mov ah, 0h
mov bl, 2
div bl
cmp ah, 0
je yes
mov ah, 09h
mov dx, offset msg
int 21h
mov ah, 4ch
int 20h
msg db "No$"
yes:
mov ah, 09h
mov dx, offset msgo
int 21h
mov ah, 4ch
int 20h
msgo db "Yes$"
end start