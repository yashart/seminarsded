.model tiny
.code
org 100h
start:
mov ah, 01h
int 21h
mov ah, 0h
mov bl, al
mov cl, al;cl - dividend
check:
mov al, cl
mov ah, 0h
dec bl
div bl
cmp bl, 01h
je yes
cmp ah, 00h
je no
jmp check
no:
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
mov ah, 09h
int 20h
msgo db "Yes!!$"
end start