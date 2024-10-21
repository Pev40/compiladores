
_main:

;prueba1.c,1 :: 		void main() {
;prueba1.c,2 :: 		TRISB = 0;
	CLRF       TRISB+0
;prueba1.c,3 :: 		for (;;)
L_main0:
;prueba1.c,5 :: 		PORTB.F4 = 1;
	BSF        PORTB+0, 4
;prueba1.c,6 :: 		PORTB.F5 = 1;
	BSF        PORTB+0, 5
;prueba1.c,7 :: 		PORTB.F6 = 1;
	BSF        PORTB+0, 6
;prueba1.c,8 :: 		PORTB.F7 = 1;
	BSF        PORTB+0, 7
;prueba1.c,9 :: 		Delay_ms(2000);
	MOVLW      11
	MOVWF      R11+0
	MOVLW      38
	MOVWF      R12+0
	MOVLW      93
	MOVWF      R13+0
L_main3:
	DECFSZ     R13+0, 1
	GOTO       L_main3
	DECFSZ     R12+0, 1
	GOTO       L_main3
	DECFSZ     R11+0, 1
	GOTO       L_main3
	NOP
	NOP
;prueba1.c,10 :: 		PORTB.F4 = 0;
	BCF        PORTB+0, 4
;prueba1.c,11 :: 		PORTB.F5 = 0;
	BCF        PORTB+0, 5
;prueba1.c,12 :: 		PORTB.F6 = 0;
	BCF        PORTB+0, 6
;prueba1.c,13 :: 		PORTB.F7 = 0;
	BCF        PORTB+0, 7
;prueba1.c,14 :: 		Delay_ms(2000);
	MOVLW      11
	MOVWF      R11+0
	MOVLW      38
	MOVWF      R12+0
	MOVLW      93
	MOVWF      R13+0
L_main4:
	DECFSZ     R13+0, 1
	GOTO       L_main4
	DECFSZ     R12+0, 1
	GOTO       L_main4
	DECFSZ     R11+0, 1
	GOTO       L_main4
	NOP
	NOP
;prueba1.c,16 :: 		}
	GOTO       L_main0
;prueba1.c,18 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
