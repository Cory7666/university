org 100h    

CALL main                          
RET

.code
main PROC
    MOV AX, 257                     ; + 4
    MOV BX, 0                       ; + 4
    MOV CX, -257                    ; + 4
    
    CALL f                          ; + 19
    RET     
main ENDP

f PROC
    MOV f_c, CX                     ; + 10
    SAL AX, 1   ; AX = 2 * a        ; + 2
    SUB CX, AX  ; CX = c - 2 * a    ; + 4
    MOV AX, CX  ; move result to AX ; + 2
    ; AX = AX * CX, where CX = 3
    MOV CX, 3                       ; + 4
    IMUL CX                         ; + (128~154)
    SUB BX, f_c ; b -= c            ; + 16
    INC BX      ; ++b               ; + 2
    SAR BX, 1   ; b /= 2            ; + 2
    ADD AX, BX                      ; + 3
    MOV BX, 0                       ; + 4
    MOV CX, 0                       ; + 4
    
    RET
f ENDP

.data
    f_c dw ?
