ORG 0000h
_f_main:
	
	; ������ ��������� ������ � ��������
	LXI H, IN_ARRAY_START
	SHLD IN_ARRAY_COUNTER
	
	LXI H, OUT_ARRAY_START
	SHLD OUT_ARRAY_COUNTER
	
	; ���� �������� ���� �������� �� �������� �������
	_loop1_start:
		LHLD IN_ARRAY_COUNTER      ; ��������� ����� ���
		MOV B, M                   ;   ������ �� ���.�.
		
		LXI H, HASH_TABLE_START
		
		; ���� ������ ����� � ���-�������
		_loop2_start:
			XCHG
			LDAX D               ; �������� ���� � B
			XCHG
			SUI 0
			JZ _loop2_end
			CMP B
			JNZ _C
				INX H          ; ���������, ����
				MOV B, M       ;   ������� (������
				               ;   ������ ����� � B)
				JMP _loop2_end ; � ��������� ����
			_C:
			INX H                ; ���� �� �������, ��
			INX H                ;   ������. ���. �� 2
			JMP _loop2_start
		_loop2_end:
		
		LHLD OUT_ARRAY_COUNTER     ; ������ �����������
		MOV M, B                   ;   ����� �� ���.�.
		
		INX H                      ; ����������
		SHLD OUT_ARRAY_COUNTER     ;   ���������
		                           ;   ��������
		LHLD IN_ARRAY_COUNTER
		INX H
		SHLD IN_ARRAY_COUNTER
		
		XCHG
		LDAX D                     ; �������� �� ����
		XCHG                       ;   ��������� ������
		SUI 0                      ;   ������ ��
		                           ;   ����. �������
		JNZ _loop1_start           ; � ������ �����
		                           ;   ��������, ����
		                           ;   ������ ��� ����
		
	_loop1_end:
	
	HLT

; ======================================================= ;
; �������� ���-�������
; ======================================================= ;

ORG 0050h;
HASH_TABLE_START:
	MOV H, C
	MOV B, C

	MOV H, D
	MOV B, D

	MOV H, E
	MOV B, E

	MOV H, H
	MOV B, H

	MOV H, L
	MOV B, L

	MOV H, M
	MOV B, M

	LXI SP, 2E3Fh
	MVI L, 3Fh
	MVI L, 2Ch
	MVI L, 7Bh
	LXI H, 5B21h
	MOV A, L
	LXI H, 5D29h
	
	NOP
	NOP

NOP
NOP

; ======================================================= ;
; �������� ������� ������� ������
; ======================================================= ;

IN_ARRAY_COUNTER:
	NOP
	NOP
IN_ARRAY_START:
	MOV C, B
	MOV H, L
	MOV L, H
	MOV L, H
	MOV L, A
	INR L
	MOV M, A
	MOV M, A
	NOP

NOP
NOP

; ======================================================= ;
; �������������� ������� � ������������� �������
; ======================================================= ;

OUT_ARRAY_COUNTER:
	NOP
	NOP
OUT_ARRAY_START:
	NOP