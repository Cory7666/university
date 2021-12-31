ORG 0000h
_f_main:
	
	; Запись начальных данных в счётчики
	LXI H, IN_ARRAY_START
	SHLD IN_ARRAY_COUNTER
	
	LXI H, OUT_ARRAY_START
	SHLD OUT_ARRAY_COUNTER
	
	; Цикл перебора всех значений во входящем массиве
	_loop1_start:
		LHLD IN_ARRAY_COUNTER      ; Возможное число для
		MOV B, M                   ;   записи во вых.м.
		
		LXI H, HASH_TABLE_START
		
		; Цикл поиска ключа в хэш-таблице
		_loop2_start:
			XCHG
			LDAX D               ; Сравнить ключ с B
			XCHG
			SUI 0
			JZ _loop2_end
			CMP B
			JNZ _C
				INX H          ; Выполнить, если
				MOV B, M       ;   совпало (запись
				               ;   нового числа в B)
				JMP _loop2_end ; И завершить цикл
			_C:
			INX H                ; Если не совпало, то
			INX H                ;   передв. адр. на 2
			JMP _loop2_start
		_loop2_end:
		
		LHLD OUT_ARRAY_COUNTER     ; Запись полученного
		MOV M, B                   ;   числа во вых.м.
		
		INX H                      ; Обновление
		SHLD OUT_ARRAY_COUNTER     ;   счётчиков
		                           ;   массивов
		LHLD IN_ARRAY_COUNTER
		INX H
		SHLD IN_ARRAY_COUNTER
		
		XCHG
		LDAX D                     ; Проверка на нуль
		XCHG                       ;   следующей ячейки
		SUI 0                      ;   памяти во
		                           ;   вход. массиве
		JNZ _loop1_start           ; И начать новую
		                           ;   итерацию, если
		                           ;   данные ещё есть
		
	_loop1_end:
	
	HLT

; ======================================================= ;
; Создание хэш-таблицы
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
; Создание массива входных данных
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
; Местоположение массива с обработанными данными
; ======================================================= ;

OUT_ARRAY_COUNTER:
	NOP
	NOP
OUT_ARRAY_START:
	NOP