ORG 100h

_init PROC
  CALL main
  RET
_init ENDP

main PROC
  MOV AX, [main_array_size]
  LEA BX, main_array
  MOV CX, -50
  MOV DX, 10
  CALL generate_array

  LEA AX, main_array
  LEA BX, main_second_array
  MOV CX, [main_array_size]
  CALL copy_array

  MOV AX, 30
  LEA BX, main_second_array
  MOV CX, [main_array_size]
  CALL search_element

  MOV AX, 5
  LEA BX, main_second_array
  MOV CX, [main_array_size]
  CALL search_element
  
  MOV AX, 0
  LEA BX, main_array
  MOV CX, [main_array_size]
  CALL array_sum
  
  RET
main ENDP

; Register arguments
; AX -> array size
; BX -> array address
; CX -> initialize value
; DX -> step
generate_array PROC
  ga_loop:
    MOV [BX], CX
    ADD CX, DX
    INC BX
    INC BX
    DEC AX
    JNZ ga_loop
  RET
generate_array ENDP

; Register arguments
; AX -> "from" array
; BX -> "to" array
; CX -> array size
copy_array PROC
  PUSH SI
  PUSH DI

  CLD
  MOV SI, AX
  MOV DI, BX
  REP MOVSW

  POP DI
  POP SI
  RET
copy_array ENDP

; Register arguments
; AX -> value
; BX -> array address
; CX -> array size
; RETURN
; AX -> index. -1 if element is not found.
search_element PROC
  MOV _se_element, AX
  MOV _se_array_start, BX

  se_loop:
    MOV AX, [_se_element]
    XOR AX, [BX]
    JZ se_loop_found
    INC BX
    INC BX
    DEC CX
    JNZ se_loop
      MOV AX, -1
    JMP se_loop_end
    se_loop_found:
      MOV AX, BX
      SUB AX, _se_array_start
      SHR AX, 1
  se_loop_end:

  RET
search_element ENDP

; Register arguments
; AX -> None
; BX -> array address
; CX -> array size
; RETURN
; AX -> sum.
array_sum PROC
	PUSH DX

	MOV AX, 0
	as_loop:
		MOV DX, [BX]
		ADD AX, DX
    ADD BX, 2
		DEC CX
		JNZ as_loop
	as_loop_end:
	
	POP DX
	RET
array_sum ENDP

main_array DW 10 DUP(0)
main_second_array DW 10 DUP(0)
main_array_size DW 10

_se_element DW ?
_se_array_start DW ?

END _init
