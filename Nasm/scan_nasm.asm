SECTION .data
msg     db "Hello, world!",0xa  
len     equ $ - msg

HexTable db "0123456789ABCDEF"

number db "0"

SECTION .bss
input_string resb 33

SECTION .text

%macro _print_hello 0
        mov eax, 4      ; 'write' syscall
        mov ebx, 1      ; file descr. 1 (stdout)
        mov ecx, msg    ; pointer to the data
        mov edx, len    ; amount of data
        int 0x80        ; call to the kernel
%endmacro
;---------------------------------------------------------
;print number in console
;Entry: None
;Exit:	None
;Destr:	EAX, EBX, ECX, EDX
;---------------------------------------------------------
%macro _print_num 1
        mov eax, 4
        mov ebx, 1
        mov ecx, number
        mov [ecx], word %1
        mov edx, 1
        int 0x80
%endmacro
;--------------------------------------------------------
;Scan string
;Entry: 1 - str label, 2 - str len
;Exit: None
;Destr: EAX, EBX, ECX, EDX
;--------------------------------------------------------
%macro _scan_str 2
        mov eax, 3
        mov ebx, 2
        mov ecx, %1
        mov edx, %2
        int 0x80
%endmacro
;--------------------------------------------------------
;print number in binary form
;Entry: EAX->number
;Exit: None
;Destr: EAX, ECX, DL, EBX
;--------------------------------------------------------
_print_bin:
        mov ecx, 32    ;size of register
        ;for(int i=0, i<32; i++)
        .shift:    
                shl eax, 1
                mov dl, 0x30
                adc dl, 0
                push eax
                push ecx
                _print_num dl
                pop ecx
                pop eax
                        loop .shift
        ret
;--------------------------------------------------------
;print number in oct form
;Entry: EAX->number
;Exit: None
;Destr: EAX, ECX, DL, EBX
;--------------------------------------------------------
_print_oct:
        ;it is because 32 don't divide on 3
        mov ebx, eax
        and ebx, 0xC0000000    ;it is 2 bin '1' in 32 bit register
        shr ebx, 30            ;known offset for Hex Table
        add ebx, HexTable
        mov dl, [ebx]
        push eax
        _print_num dl
        pop eax
        shl eax, 2
        ;for(int i=0, i<10; i++)
        mov ecx, 10
        .shift:
                mov ebx, eax
                and ebx, 0xE0000000    ;it is 3 bin '1' in 32 bit register
                shr ebx, 29            ;known offset for Hex Table
                add ebx, HexTable
                mov dl, [ebx]
                push eax
                push ecx
                _print_num dl
                pop ecx
                pop eax
                shl eax, 3
                    loop .shift
        ret
;--------------------------------------------------------
;print number in hex form
;Entry: AX->number
;Exit:	None
;Destr: AX, CX, DL, BX
;--------------------------------------------------------
_print_hex:
        mov ecx, 8
        .shift:
                mov ebx, eax
                and ebx, 0xF0000000    ;it is 3 bin '1' in 32 bit register
                shr ebx, 28            ;known offset for Hex Table
                add ebx, HexTable
                mov dl, [ebx]
                push eax
                push ecx
                _print_num dl
                pop ecx
                pop eax
                shl eax, 4
                    loop .shift
        ret
;------------------------------------------------
;Print number in dec form
;Input: EAX->number
;Output: None
;Dest: EDX, ECX, EAX, BX
;-------------------------------------------------
_print_dec:
        ;divide on 10, while number isn't negative
        
        mov ebx, 10
        xor ecx, ecx
        .div_on_10:
                xor edx, edx
                cmp eax, 10
                div ebx
                inc ecx
                push edx
                jb .del_last_push
                jmp .div_on_10
        .del_last_push
                ;pop eax
                ;dec ecx
                .print_num
                        pop edx
                        push ecx
                        add dx, 0x30
                        _print_num dl
                        pop ecx
                            loop .print_num
        ret
;---------------------------------------------------------------
;Block for scan numbers
;---------------------------------------------------------------

;-----------------------------------
;write number from binary form in EAX
;Enter: ESI:bss->string
;Exit: 	EAX->number
;Destr: EAX, EDX
;-----------------------------------
_scan_bin:
        xor edx, edx
        xor eax, eax
        mov cx, 32
        .scan_str
                lodsb
                cmp al, 0x30
                jb .end
                shl edx, 1
                sub al, 0x30
                add dl, al
                    loop .scan_str
        .end
            mov eax, edx
            ret
;-----------------------------------
;write number from oct form in EAX
;Enter: ESI:bss->string
;Exit: 	EAX->number
;Destr: EAX, EDX
;-----------------------------------
_scan_oct:
        xor edx, edx
        xor eax, eax
        mov cx, 10
        .scan_str
                lodsb
                cmp al, 0x30
                jb .end
                shl edx, 3
                sub al, 0x30
                add dl, al
                    loop .scan_str
        .end
            mov eax, edx
            ret
;-----------------------------------
;write number from hex form in EAX
;Enter: ESI:bss->string
;Exit: 	EAX->number
;Destr: EAX, EDX
;-----------------------------------
_scan_hex:
        xor edx, edx
        xor eax, eax
        mov cx, 8
        .scan_str
                lodsb
                cmp al, 0x30
                jb .end
                shl edx, 4
                sub al, 0x30
                cmp al, 10
                jae .scan_hex
                .next
                add dl, al
                    loop .scan_str
        .end
            mov eax, edx
            ret
        .scan_hex
            sub al, 7
            jmp .next            
;-----------------------------------
;write number from dec form in EAX
;Enter: ESI:bss->string
;Exit: 	EAX->number
;Destr: EAX, EDX
;-----------------------------------
_scan_dec:
        xor edx, edx
        xor eax, eax
        mov ebx, 10
        xor ecx, ecx
        .scan_str
                lodsb
                cmp al, 0x30
                jb .end
                xor edx, edx
                sub al, 0x30
                push eax
                mov eax, ecx
                mul ebx
                mov ecx, eax
                pop eax
                add cl, al
                    jmp .scan_str
        .end
            mov eax, ecx
            ret
global _start           ; the program entry point
_start:
        
        _scan_str input_string, 32
        mov esi, input_string
        call _scan_dec
        
        call _print_dec
        mov eax, 1      ; '_exit' syscall
        mov ebx, 0      ; zero exit code (success)
        int 0x80        ; call to the kernel