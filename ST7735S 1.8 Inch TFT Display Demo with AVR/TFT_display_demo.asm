
_ST7735_Write:

;st7735.c,4 :: 		void ST7735_Write(unsigned char value, unsigned char mode)
;st7735.c,6 :: 		signed char i = 0x08;
; i start address is: 17 (R17)
	LDI        R17, 8
;st7735.c,8 :: 		CS_pin = 0;
	IN         R27, PORTB0_bit+0
	CBR        R27, BitMask(PORTB0_bit+0)
	OUT        PORTB0_bit+0, R27
;st7735.c,10 :: 		if(mode)
	TST        R3
	BRNE       L__ST7735_Write189
	JMP        L_ST7735_Write0
L__ST7735_Write189:
;st7735.c,12 :: 		RS_pin = 1;
	IN         R27, PORTB2_bit+0
	SBR        R27, BitMask(PORTB2_bit+0)
	OUT        PORTB2_bit+0, R27
;st7735.c,13 :: 		}
	JMP        L_ST7735_Write1
L_ST7735_Write0:
;st7735.c,16 :: 		RS_pin = 0;
	IN         R27, PORTB2_bit+0
	CBR        R27, BitMask(PORTB2_bit+0)
	OUT        PORTB2_bit+0, R27
;st7735.c,17 :: 		}
L_ST7735_Write1:
;st7735.c,19 :: 		while(i > 0)
L_ST7735_Write2:
; i end address is: 17 (R17)
; i start address is: 17 (R17)
	LDI        R16, 0
	CP         R16, R17
	BRLT       L__ST7735_Write190
	JMP        L_ST7735_Write3
L__ST7735_Write190:
;st7735.c,21 :: 		SCK_pin = 0;
	IN         R27, PORTB4_bit+0
	CBR        R27, BitMask(PORTB4_bit+0)
	OUT        PORTB4_bit+0, R27
;st7735.c,23 :: 		if((value & 0x80) != 0)
	MOV        R16, R2
	ANDI       R16, 128
	CPI        R16, 0
	BRNE       L__ST7735_Write191
	JMP        L_ST7735_Write4
L__ST7735_Write191:
;st7735.c,25 :: 		SDA_pin = 1;
	IN         R27, PORTB3_bit+0
	SBR        R27, BitMask(PORTB3_bit+0)
	OUT        PORTB3_bit+0, R27
;st7735.c,26 :: 		}
	JMP        L_ST7735_Write5
L_ST7735_Write4:
;st7735.c,29 :: 		SDA_pin = 0;
	IN         R27, PORTB3_bit+0
	CBR        R27, BitMask(PORTB3_bit+0)
	OUT        PORTB3_bit+0, R27
;st7735.c,30 :: 		}
L_ST7735_Write5:
;st7735.c,32 :: 		SCK_pin = 1;
	IN         R27, PORTB4_bit+0
	SBR        R27, BitMask(PORTB4_bit+0)
	OUT        PORTB4_bit+0, R27
;st7735.c,34 :: 		value <<= 1;
	MOV        R16, R2
	LSL        R16
	MOV        R2, R16
;st7735.c,35 :: 		i--;
	MOV        R16, R17
	SUBI       R16, 1
	MOV        R17, R16
;st7735.c,36 :: 		};
; i end address is: 17 (R17)
	JMP        L_ST7735_Write2
L_ST7735_Write3:
;st7735.c,38 :: 		CS_pin = 1;
	IN         R27, PORTB0_bit+0
	SBR        R27, BitMask(PORTB0_bit+0)
	OUT        PORTB0_bit+0, R27
;st7735.c,39 :: 		}
L_end_ST7735_Write:
	RET
; end of _ST7735_Write

_ST7735_Reset:

;st7735.c,42 :: 		void ST7735_Reset()
;st7735.c,44 :: 		RST_pin = 0;
	IN         R27, PORTB1_bit+0
	CBR        R27, BitMask(PORTB1_bit+0)
	OUT        PORTB1_bit+0, R27
;st7735.c,45 :: 		delay_ms(2);
	LDI        R17, 42
	LDI        R16, 142
L_ST7735_Reset6:
	DEC        R16
	BRNE       L_ST7735_Reset6
	DEC        R17
	BRNE       L_ST7735_Reset6
	NOP
;st7735.c,46 :: 		RST_pin = 1;
	IN         R27, PORTB1_bit+0
	SBR        R27, BitMask(PORTB1_bit+0)
	OUT        PORTB1_bit+0, R27
;st7735.c,47 :: 		delay_ms(2);
	LDI        R17, 42
	LDI        R16, 142
L_ST7735_Reset8:
	DEC        R16
	BRNE       L_ST7735_Reset8
	DEC        R17
	BRNE       L_ST7735_Reset8
	NOP
;st7735.c,48 :: 		}
L_end_ST7735_Reset:
	RET
; end of _ST7735_Reset

_ST7735_init:

;st7735.c,51 :: 		void ST7735_init()
;st7735.c,53 :: 		ST7735_Reset();
	PUSH       R2
	PUSH       R3
	CALL       _ST7735_Reset+0
;st7735.c,55 :: 		ST7735_Write(ST7735_SWRESET, CMD);
	CLR        R3
	LDI        R27, 1
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,56 :: 		delay_us(150);
	LDI        R17, 4
	LDI        R16, 29
L_ST7735_init10:
	DEC        R16
	BRNE       L_ST7735_init10
	DEC        R17
	BRNE       L_ST7735_init10
;st7735.c,57 :: 		ST7735_Write(ST7735_SLPOUT, CMD);
	CLR        R3
	LDI        R27, 17
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,58 :: 		delay_us(150);
	LDI        R17, 4
	LDI        R16, 29
L_ST7735_init12:
	DEC        R16
	BRNE       L_ST7735_init12
	DEC        R17
	BRNE       L_ST7735_init12
;st7735.c,60 :: 		ST7735_Write(ST7735_FRMCTR1, CMD);
	CLR        R3
	LDI        R27, 177
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,61 :: 		ST7735_Write(0x01, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 1
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,62 :: 		ST7735_Write(0x2C, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 44
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,63 :: 		ST7735_Write(0x2D, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 45
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,65 :: 		ST7735_Write(ST7735_FRMCTR2, CMD);
	CLR        R3
	LDI        R27, 178
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,66 :: 		ST7735_Write(0x01, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 1
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,67 :: 		ST7735_Write(0x2C, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 44
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,68 :: 		ST7735_Write(0x2D, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 45
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,70 :: 		ST7735_Write(ST7735_FRMCTR3, CMD);
	CLR        R3
	LDI        R27, 179
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,71 :: 		ST7735_Write(0x01, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 1
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,72 :: 		ST7735_Write(0x2C, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 44
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,73 :: 		ST7735_Write(0x2D, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 45
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,74 :: 		ST7735_Write(0x01, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 1
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,75 :: 		ST7735_Write(0x2C, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 44
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,76 :: 		ST7735_Write(0x2D, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 45
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,78 :: 		ST7735_Write(ST7735_INVCTR, CMD);
	CLR        R3
	LDI        R27, 180
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,79 :: 		ST7735_Write(0x07, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 7
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,81 :: 		ST7735_Write(ST7735_PWCTR1, CMD);
	CLR        R3
	LDI        R27, 192
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,82 :: 		ST7735_Write(0xA2, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 162
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,83 :: 		ST7735_Write(0x02, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 2
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,84 :: 		ST7735_Write(0x84, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 132
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,86 :: 		ST7735_Write(ST7735_PWCTR1, CMD);
	CLR        R3
	LDI        R27, 192
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,87 :: 		ST7735_Write(0xC5, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 197
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,89 :: 		ST7735_Write(ST7735_PWCTR2, CMD);
	CLR        R3
	LDI        R27, 193
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,90 :: 		ST7735_Write(0x0A, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 10
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,91 :: 		ST7735_Write(0x00, DAT);
	LDI        R27, 1
	MOV        R3, R27
	CLR        R2
	CALL       _ST7735_Write+0
;st7735.c,93 :: 		ST7735_Write(ST7735_PWCTR3, CMD);
	CLR        R3
	LDI        R27, 194
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,94 :: 		ST7735_Write(0x8A, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 138
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,95 :: 		ST7735_Write(0x2A, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 42
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,97 :: 		ST7735_Write(ST7735_PWCTR4, CMD);
	CLR        R3
	LDI        R27, 195
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,98 :: 		ST7735_Write(0x8A, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 138
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,99 :: 		ST7735_Write(0xEE, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 238
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,101 :: 		ST7735_Write(ST7735_PWCTR5, CMD);
	CLR        R3
	LDI        R27, 196
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,102 :: 		ST7735_Write(0x0E, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 14
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,104 :: 		ST7735_Write(ST7735_VMCTR1, CMD);
	CLR        R3
	LDI        R27, 197
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,105 :: 		ST7735_Write(0x00, DAT);
	LDI        R27, 1
	MOV        R3, R27
	CLR        R2
	CALL       _ST7735_Write+0
;st7735.c,107 :: 		ST7735_Write(ST7735_COLMOD, CMD);
	CLR        R3
	LDI        R27, 58
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,108 :: 		ST7735_Write(0x05, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 5
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,110 :: 		ST7735_Write(ST7735_MADCTL, CMD);
	CLR        R3
	LDI        R27, 54
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,111 :: 		ST7735_Write(0xC8, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 200
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,113 :: 		RAM_Address_Set();
	CALL       _RAM_Address_Set+0
;st7735.c,115 :: 		ST7735_Write(ST7735_GMCTRP1, CMD);
	CLR        R3
	LDI        R27, 224
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,116 :: 		ST7735_Write(0x02, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 2
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,117 :: 		ST7735_Write(0x1C, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 28
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,118 :: 		ST7735_Write(0x07, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 7
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,119 :: 		ST7735_Write(0x12, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 18
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,120 :: 		ST7735_Write(0x37, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 55
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,121 :: 		ST7735_Write(0x32, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 50
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,122 :: 		ST7735_Write(0x29, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 41
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,123 :: 		ST7735_Write(0x2D, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 45
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,124 :: 		ST7735_Write(0x29, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 41
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,125 :: 		ST7735_Write(0x25, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 37
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,126 :: 		ST7735_Write(0x2B, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 43
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,127 :: 		ST7735_Write(0x39, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 57
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,128 :: 		ST7735_Write(0x00, DAT);
	LDI        R27, 1
	MOV        R3, R27
	CLR        R2
	CALL       _ST7735_Write+0
;st7735.c,129 :: 		ST7735_Write(0x01, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 1
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,130 :: 		ST7735_Write(0x03, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 3
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,131 :: 		ST7735_Write(0x10, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 16
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,133 :: 		ST7735_Write(ST7735_GMCTRN1, CMD);
	CLR        R3
	LDI        R27, 225
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,134 :: 		ST7735_Write(0x03, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 3
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,135 :: 		ST7735_Write(0x1D, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 29
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,136 :: 		ST7735_Write(0x07, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 7
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,137 :: 		ST7735_Write(0x06, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 6
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,138 :: 		ST7735_Write(0x2E, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 46
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,139 :: 		ST7735_Write(0x2C, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 44
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,140 :: 		ST7735_Write(0x29, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 41
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,141 :: 		ST7735_Write(0x2D, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 45
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,142 :: 		ST7735_Write(0x2E, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 46
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,143 :: 		ST7735_Write(0x2E, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 46
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,144 :: 		ST7735_Write(0x37, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 55
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,145 :: 		ST7735_Write(0x3F, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 63
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,146 :: 		ST7735_Write(0x00, DAT);
	LDI        R27, 1
	MOV        R3, R27
	CLR        R2
	CALL       _ST7735_Write+0
;st7735.c,147 :: 		ST7735_Write(0x00, DAT);
	LDI        R27, 1
	MOV        R3, R27
	CLR        R2
	CALL       _ST7735_Write+0
;st7735.c,148 :: 		ST7735_Write(0x02, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 2
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,149 :: 		ST7735_Write(0x10, DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 16
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,151 :: 		ST7735_Write(ST7735_NORON, CMD);
	CLR        R3
	LDI        R27, 19
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,152 :: 		delay_ms(10);
	LDI        R17, 208
	LDI        R16, 202
L_ST7735_init14:
	DEC        R16
	BRNE       L_ST7735_init14
	DEC        R17
	BRNE       L_ST7735_init14
	NOP
;st7735.c,154 :: 		ST7735_Write(ST7735_DISPON, CMD);
	CLR        R3
	LDI        R27, 41
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,155 :: 		delay_ms(100);
	LDI        R18, 9
	LDI        R17, 30
	LDI        R16, 229
L_ST7735_init16:
	DEC        R16
	BRNE       L_ST7735_init16
	DEC        R17
	BRNE       L_ST7735_init16
	DEC        R18
	BRNE       L_ST7735_init16
	NOP
;st7735.c,157 :: 		ST7735_Write(ST7735_RAMWR, CMD);
	CLR        R3
	LDI        R27, 44
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,158 :: 		delay_ms(100);
	LDI        R18, 9
	LDI        R17, 30
	LDI        R16, 229
L_ST7735_init18:
	DEC        R16
	BRNE       L_ST7735_init18
	DEC        R17
	BRNE       L_ST7735_init18
	DEC        R18
	BRNE       L_ST7735_init18
	NOP
;st7735.c,159 :: 		}
L_end_ST7735_init:
	POP        R3
	POP        R2
	RET
; end of _ST7735_init

_ST7735_Word_Write:

;st7735.c,162 :: 		void ST7735_Word_Write(unsigned int value)
;st7735.c,164 :: 		ST7735_Write(((value & 0xFF00) >> 0x08), DAT);
	PUSH       R2
	PUSH       R3
	MOVW       R16, R2
	ANDI       R16, 0
	ANDI       R17, 255
	MOV        R16, R17
	LDI        R17, 0
	PUSH       R3
	PUSH       R2
	LDI        R27, 1
	MOV        R3, R27
	MOV        R2, R16
	CALL       _ST7735_Write+0
	POP        R2
	POP        R3
;st7735.c,165 :: 		ST7735_Write((value & 0x00FF), DAT);
	MOV        R16, R2
	ANDI       R16, 255
	LDI        R27, 1
	MOV        R3, R27
	MOV        R2, R16
	CALL       _ST7735_Write+0
;st7735.c,166 :: 		}
L_end_ST7735_Word_Write:
	POP        R3
	POP        R2
	RET
; end of _ST7735_Word_Write

_ST7735_Data_Write:

;st7735.c,169 :: 		void ST7735_Data_Write(unsigned char DataH, unsigned char DataL)
;st7735.c,171 :: 		ST7735_Write(DataH, DAT);
	PUSH       R2
	PUSH       R3
	PUSH       R3
	LDI        R27, 1
	MOV        R3, R27
	CALL       _ST7735_Write+0
	POP        R3
;st7735.c,172 :: 		ST7735_Write(DataL, DAT);
	MOV        R2, R3
	LDI        R27, 1
	MOV        R3, R27
	CALL       _ST7735_Write+0
;st7735.c,173 :: 		}
L_end_ST7735_Data_Write:
	POP        R3
	POP        R2
	RET
; end of _ST7735_Data_Write

_ST7735_Data_Write_4k:

;st7735.c,176 :: 		void ST7735_Data_Write_4k(unsigned char DataH, unsigned char DataM, unsigned char DataL)
;st7735.c,178 :: 		ST7735_Write(DataH, DAT);
	PUSH       R2
	PUSH       R3
	PUSH       R3
	LDI        R27, 1
	MOV        R3, R27
	CALL       _ST7735_Write+0
	POP        R3
;st7735.c,179 :: 		ST7735_Write(DataM, DAT);
	MOV        R2, R3
	LDI        R27, 1
	MOV        R3, R27
	CALL       _ST7735_Write+0
;st7735.c,180 :: 		ST7735_Write(DataL, DAT);
	LDI        R27, 1
	MOV        R3, R27
	MOV        R2, R4
	CALL       _ST7735_Write+0
;st7735.c,181 :: 		}
L_end_ST7735_Data_Write_4k:
	POP        R3
	POP        R2
	RET
; end of _ST7735_Data_Write_4k

_Set_Addr_Window:

;st7735.c,184 :: 		void Set_Addr_Window(unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye)
;st7735.c,186 :: 		ST7735_Write(ST7735_CASET, CMD);
	PUSH       R2
	PUSH       R3
	PUSH       R3
	PUSH       R2
	CLR        R3
	LDI        R27, 42
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,187 :: 		ST7735_Write(0x00, DAT);
	LDI        R27, 1
	MOV        R3, R27
	CLR        R2
	CALL       _ST7735_Write+0
	POP        R2
;st7735.c,188 :: 		ST7735_Write(xs, DAT);
	LDI        R27, 1
	MOV        R3, R27
	CALL       _ST7735_Write+0
;st7735.c,189 :: 		ST7735_Write(0x00, DAT);
	LDI        R27, 1
	MOV        R3, R27
	CLR        R2
	CALL       _ST7735_Write+0
;st7735.c,190 :: 		ST7735_Write(xe, DAT);
	LDI        R27, 1
	MOV        R3, R27
	MOV        R2, R4
	CALL       _ST7735_Write+0
;st7735.c,192 :: 		ST7735_Write(ST7735_RASET, CMD);
	CLR        R3
	LDI        R27, 43
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,193 :: 		ST7735_Write(0x00, DAT);
	LDI        R27, 1
	MOV        R3, R27
	CLR        R2
	CALL       _ST7735_Write+0
	POP        R3
;st7735.c,194 :: 		ST7735_Write(ys, DAT);
	MOV        R2, R3
	LDI        R27, 1
	MOV        R3, R27
	CALL       _ST7735_Write+0
;st7735.c,195 :: 		ST7735_Write(0x00, DAT);
	LDI        R27, 1
	MOV        R3, R27
	CLR        R2
	CALL       _ST7735_Write+0
;st7735.c,196 :: 		ST7735_Write(ye, DAT);
	LDI        R27, 1
	MOV        R3, R27
	MOV        R2, R5
	CALL       _ST7735_Write+0
;st7735.c,198 :: 		ST7735_Write(ST7735_RAMWR, CMD);
	CLR        R3
	LDI        R27, 44
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,199 :: 		}
L_end_Set_Addr_Window:
	POP        R3
	POP        R2
	RET
; end of _Set_Addr_Window

_RAM_Address_Set:

;st7735.c,202 :: 		void RAM_Address_Set()
;st7735.c,204 :: 		Set_Addr_Window(0x00, 0x00, 0x7F, 0x9F);
	PUSH       R2
	PUSH       R3
	PUSH       R4
	PUSH       R5
	LDI        R27, 159
	MOV        R5, R27
	LDI        R27, 127
	MOV        R4, R27
	CLR        R3
	CLR        R2
	CALL       _Set_Addr_Window+0
;st7735.c,205 :: 		}
L_end_RAM_Address_Set:
	POP        R5
	POP        R4
	POP        R3
	POP        R2
	RET
; end of _RAM_Address_Set

_Invert_Display:

;st7735.c,208 :: 		void Invert_Display(unsigned char i)
;st7735.c,210 :: 		if(i == ST7735_INVON)
	PUSH       R2
	PUSH       R3
	LDI        R27, 33
	CP         R2, R27
	BREQ       L__Invert_Display200
	JMP        L_Invert_Display20
L__Invert_Display200:
;st7735.c,212 :: 		ST7735_Write(ST7735_INVON, CMD);
	CLR        R3
	LDI        R27, 33
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,213 :: 		}
	JMP        L_Invert_Display21
L_Invert_Display20:
;st7735.c,216 :: 		ST7735_Write(ST7735_INVOFF, CMD);
	CLR        R3
	LDI        R27, 32
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,217 :: 		}
L_Invert_Display21:
;st7735.c,218 :: 		}
L_end_Invert_Display:
	POP        R3
	POP        R2
	RET
; end of _Invert_Display

_Swap_Colour:

;st7735.c,221 :: 		unsigned int Swap_Colour(unsigned int colour)
;st7735.c,223 :: 		return ((colour << 0x000B) | (colour & 0x07E0) | (colour >> 0x000B));
	LDI        R27, 11
	MOVW       R18, R2
L__Swap_Colour202:
	LSL        R18
	ROL        R19
	DEC        R27
	BRNE       L__Swap_Colour202
L__Swap_Colour203:
	MOVW       R16, R2
	ANDI       R16, 224
	ANDI       R17, 7
	OR         R18, R16
	OR         R19, R17
	LDI        R27, 11
	MOVW       R16, R2
L__Swap_Colour204:
	LSR        R17
	ROR        R16
	DEC        R27
	BRNE       L__Swap_Colour204
L__Swap_Colour205:
	OR         R16, R18
	OR         R17, R19
;st7735.c,224 :: 		}
L_end_Swap_Colour:
	RET
; end of _Swap_Colour

_Color565:

;st7735.c,227 :: 		unsigned int Color565(unsigned char r, unsigned char g, unsigned char b)
;st7735.c,229 :: 		return (((r & 0xF8) << 0x08) | ((g & 0xFC) << 0x03) | (b >> 0x03));
	MOV        R16, R2
	ANDI       R16, 248
	MOV        R19, R16
	CLR        R18
	MOV        R16, R3
	ANDI       R16, 252
	LDI        R17, 0
	LSL        R16
	ROL        R17
	LSL        R16
	ROL        R17
	LSL        R16
	ROL        R17
	OR         R18, R16
	OR         R19, R17
	MOV        R16, R4
	LSR        R16
	LSR        R16
	LSR        R16
	LDI        R17, 0
	OR         R16, R18
	OR         R17, R19
;st7735.c,230 :: 		}
L_end_Color565:
	RET
; end of _Color565

_Set_Rotation:

;st7735.c,233 :: 		void Set_Rotation(unsigned char m)
;st7735.c,235 :: 		unsigned char rotation = 0x00;
	PUSH       R2
	PUSH       R3
;st7735.c,237 :: 		ST7735_Write(ST7735_MADCTL, CMD);
	PUSH       R2
	CLR        R3
	LDI        R27, 54
	MOV        R2, R27
	CALL       _ST7735_Write+0
	POP        R2
;st7735.c,238 :: 		rotation = (m % 4);
	MOV        R16, R2
	ANDI       R16, 3
; rotation start address is: 16 (R16)
;st7735.c,240 :: 		switch(rotation)
	JMP        L_Set_Rotation22
; rotation end address is: 16 (R16)
;st7735.c,242 :: 		case 0:
L_Set_Rotation24:
;st7735.c,244 :: 		ST7735_Write((MADCTL_MX | MADCTL_MY | MADCTL_RGB), DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 200
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,245 :: 		w = ST7735_TFTWIDTH;
	LDI        R27, 128
	STS        _w+0, R27
;st7735.c,246 :: 		l = ST7735_TFTLENGTH;
	LDI        R27, 160
	STS        _l+0, R27
;st7735.c,247 :: 		break;
	JMP        L_Set_Rotation23
;st7735.c,249 :: 		case 1:
L_Set_Rotation25:
;st7735.c,251 :: 		ST7735_Write((MADCTL_MY | MADCTL_MV | MADCTL_RGB), DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 168
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,252 :: 		w = ST7735_TFTLENGTH;
	LDI        R27, 160
	STS        _w+0, R27
;st7735.c,253 :: 		l = ST7735_TFTWIDTH;
	LDI        R27, 128
	STS        _l+0, R27
;st7735.c,254 :: 		break;
	JMP        L_Set_Rotation23
;st7735.c,256 :: 		case 2:
L_Set_Rotation26:
;st7735.c,258 :: 		ST7735_Write((MADCTL_RGB), DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 8
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,259 :: 		w = ST7735_TFTWIDTH;
	LDI        R27, 128
	STS        _w+0, R27
;st7735.c,260 :: 		l = ST7735_TFTLENGTH;
	LDI        R27, 160
	STS        _l+0, R27
;st7735.c,261 :: 		break;
	JMP        L_Set_Rotation23
;st7735.c,263 :: 		case 3:
L_Set_Rotation27:
;st7735.c,265 :: 		ST7735_Write((MADCTL_MX | MADCTL_MV | MADCTL_RGB), DAT);
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 104
	MOV        R2, R27
	CALL       _ST7735_Write+0
;st7735.c,266 :: 		w = ST7735_TFTLENGTH;
	LDI        R27, 160
	STS        _w+0, R27
;st7735.c,267 :: 		l = ST7735_TFTWIDTH;
	LDI        R27, 128
	STS        _l+0, R27
;st7735.c,268 :: 		break;
	JMP        L_Set_Rotation23
;st7735.c,270 :: 		}
L_Set_Rotation22:
; rotation start address is: 16 (R16)
	CPI        R16, 0
	BRNE       L__Set_Rotation208
	JMP        L_Set_Rotation24
L__Set_Rotation208:
	CPI        R16, 1
	BRNE       L__Set_Rotation209
	JMP        L_Set_Rotation25
L__Set_Rotation209:
	CPI        R16, 2
	BRNE       L__Set_Rotation210
	JMP        L_Set_Rotation26
L__Set_Rotation210:
	CPI        R16, 3
	BRNE       L__Set_Rotation211
	JMP        L_Set_Rotation27
L__Set_Rotation211:
; rotation end address is: 16 (R16)
L_Set_Rotation23:
;st7735.c,271 :: 		}
L_end_Set_Rotation:
	POP        R3
	POP        R2
	RET
; end of _Set_Rotation

_TFT_fill:

;st7735.c,274 :: 		void TFT_fill(unsigned int colour)
;st7735.c,276 :: 		unsigned char i = 0x00;
	PUSH       R4
	PUSH       R5
;st7735.c,277 :: 		unsigned char j = 0x00;
;st7735.c,279 :: 		Set_Addr_Window(0, 0, (w - 1), (l - 1));
	LDS        R17, _l+0
	SUBI       R17, 1
	LDS        R16, _w+0
	SUBI       R16, 1
	PUSH       R3
	PUSH       R2
	MOV        R5, R17
	MOV        R4, R16
	CLR        R3
	CLR        R2
	CALL       _Set_Addr_Window+0
	POP        R2
	POP        R3
;st7735.c,281 :: 		for(j = l; j > 0; j--)
; j start address is: 17 (R17)
	LDS        R17, _l+0
; j end address is: 17 (R17)
L_TFT_fill28:
; j start address is: 17 (R17)
	LDI        R16, 0
	CP         R16, R17
	BRLO       L__TFT_fill213
	JMP        L_TFT_fill29
L__TFT_fill213:
;st7735.c,283 :: 		for(i = w; i > 0; i--)
; i start address is: 16 (R16)
	LDS        R16, _w+0
; i end address is: 16 (R16)
; j end address is: 17 (R17)
	MOV        R18, R16
L_TFT_fill31:
; i start address is: 18 (R18)
; j start address is: 17 (R17)
	LDI        R16, 0
	CP         R16, R18
	BRLO       L__TFT_fill214
	JMP        L_TFT_fill32
L__TFT_fill214:
;st7735.c,285 :: 		ST7735_Word_Write(colour);
	PUSH       R17
	PUSH       R3
	PUSH       R2
	CALL       _ST7735_Word_Write+0
	POP        R2
	POP        R3
	POP        R17
;st7735.c,283 :: 		for(i = w; i > 0; i--)
	MOV        R16, R18
	SUBI       R16, 1
	MOV        R18, R16
;st7735.c,286 :: 		}
; i end address is: 18 (R18)
	JMP        L_TFT_fill31
L_TFT_fill32:
;st7735.c,281 :: 		for(j = l; j > 0; j--)
	MOV        R16, R17
	SUBI       R16, 1
	MOV        R17, R16
;st7735.c,287 :: 		}
; j end address is: 17 (R17)
	JMP        L_TFT_fill28
L_TFT_fill29:
;st7735.c,288 :: 		}
L_end_TFT_fill:
	POP        R5
	POP        R4
	RET
; end of _TFT_fill

_Draw_Pixel:

;st7735.c,291 :: 		void Draw_Pixel(unsigned char x_pos, unsigned char y_pos, unsigned int colour)
;st7735.c,293 :: 		Set_Addr_Window(x_pos, y_pos, (1 + x_pos), (1 + y_pos));
	PUSH       R2
	PUSH       R3
	MOV        R17, R3
	SUBI       R17, 255
	MOV        R16, R2
	SUBI       R16, 255
	PUSH       R5
	PUSH       R4
	MOV        R5, R17
	MOV        R4, R16
	CALL       _Set_Addr_Window+0
	POP        R4
	POP        R5
;st7735.c,294 :: 		ST7735_Word_Write(colour);
	MOVW       R2, R4
	CALL       _ST7735_Word_Write+0
;st7735.c,295 :: 		}
L_end_Draw_Pixel:
	POP        R3
	POP        R2
	RET
; end of _Draw_Pixel

_Draw_Line:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	ADIW       R28, 5

;st7735.c,298 :: 		void Draw_Line(signed int x1, signed int y1, signed int x2, signed int y2, unsigned int colour)
; colour start address is: 20 (R20)
	LDD        R20, Y+0
	LDD        R21, Y+1
;st7735.c,300 :: 		signed int dx = 0x0000;
;st7735.c,301 :: 		signed int dy = 0x0000;
;st7735.c,302 :: 		signed int stepx = 0x0000;
;st7735.c,303 :: 		signed int stepy = 0x0000;
;st7735.c,304 :: 		signed int fraction = 0x0000;
;st7735.c,306 :: 		dy = (y2 - y1);
	MOVW       R18, R8
	SUB        R18, R4
	SBC        R19, R5
; dy start address is: 12 (R12)
	MOVW       R12, R18
;st7735.c,307 :: 		dx = (x2 - x1);
	MOVW       R16, R6
	SUB        R16, R2
	SBC        R17, R3
; dx start address is: 22 (R22)
	MOVW       R22, R16
;st7735.c,309 :: 		if (dy < 0)
	LDI        R16, 0
	LDI        R17, 0
	CP         R18, R16
	CPC        R19, R17
	BRLT       L__Draw_Line217
	JMP        L_Draw_Line34
L__Draw_Line217:
;st7735.c,311 :: 		dy = -dy;
	LDI        R16, 0
	LDI        R17, 0
	SUB        R16, R12
	SBC        R17, R13
	MOVW       R12, R16
;st7735.c,312 :: 		stepy = -1;
; stepy start address is: 18 (R18)
	LDI        R18, 255
	LDI        R19, 255
;st7735.c,313 :: 		}
; stepy end address is: 18 (R18)
	JMP        L_Draw_Line35
L_Draw_Line34:
;st7735.c,316 :: 		stepy = 1;
; stepy start address is: 18 (R18)
	LDI        R18, 1
	LDI        R19, 0
; stepy end address is: 18 (R18)
; dy end address is: 12 (R12)
;st7735.c,317 :: 		}
L_Draw_Line35:
;st7735.c,319 :: 		if (dx < 0)
; stepy start address is: 18 (R18)
; dy start address is: 12 (R12)
	LDI        R16, 0
	LDI        R17, 0
	CP         R22, R16
	CPC        R23, R17
	BRLT       L__Draw_Line218
	JMP        L_Draw_Line36
L__Draw_Line218:
;st7735.c,321 :: 		dx = -dx;
	LDI        R16, 0
	LDI        R17, 0
	SUB        R16, R22
	SBC        R17, R23
	MOVW       R22, R16
;st7735.c,322 :: 		stepx = -1;
; stepx start address is: 10 (R10)
	LDI        R27, 255
	MOV        R10, R27
	MOV        R11, R27
;st7735.c,323 :: 		}
; stepx end address is: 10 (R10)
	JMP        L_Draw_Line37
L_Draw_Line36:
;st7735.c,326 :: 		stepx = 1;
; stepx start address is: 10 (R10)
	LDI        R27, 1
	MOV        R10, R27
	LDI        R27, 0
	MOV        R11, R27
; stepx end address is: 10 (R10)
; dx end address is: 22 (R22)
;st7735.c,327 :: 		}
L_Draw_Line37:
;st7735.c,329 :: 		dx <<= 0x01;
; stepx start address is: 10 (R10)
; dx start address is: 22 (R22)
	MOVW       R16, R22
	LSL        R16
	ROL        R17
; dx end address is: 22 (R22)
; dx start address is: 24 (R24)
	MOVW       R24, R16
;st7735.c,330 :: 		dy <<= 0x01;
	MOVW       R16, R12
	LSL        R16
	ROL        R17
; dy end address is: 12 (R12)
; dy start address is: 22 (R22)
	MOVW       R22, R16
;st7735.c,332 :: 		Draw_Pixel(x1, y1, colour);
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R3, R4
	MOVW       R4, R20
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,334 :: 		if (dx > dy)
	CP         R22, R24
	CPC        R23, R25
	BRLT       L__Draw_Line219
	JMP        L_Draw_Line38
L__Draw_Line219:
;st7735.c,336 :: 		fraction = (dy - (dx >> 1));
	MOVW       R16, R24
	ASR        R17
	ROR        R16
	MOVW       R0, R16
	MOVW       R16, R22
	SUB        R16, R0
	SBC        R17, R1
; fraction start address is: 12 (R12)
	MOVW       R12, R16
; stepy end address is: 18 (R18)
; fraction end address is: 12 (R12)
	MOVW       R14, R18
;st7735.c,337 :: 		while (x1 != x2)
L_Draw_Line39:
; fraction start address is: 12 (R12)
; stepy start address is: 14 (R14)
; dy start address is: 22 (R22)
; dy end address is: 22 (R22)
; dx start address is: 24 (R24)
; dx end address is: 24 (R24)
; stepx start address is: 10 (R10)
; stepx end address is: 10 (R10)
; stepy start address is: 14 (R14)
; stepy end address is: 14 (R14)
; colour start address is: 20 (R20)
; colour end address is: 20 (R20)
	CP         R2, R6
	CPC        R3, R7
	BRNE       L__Draw_Line220
	JMP        L_Draw_Line40
L__Draw_Line220:
; dy end address is: 22 (R22)
; dx end address is: 24 (R24)
; stepx end address is: 10 (R10)
; stepy end address is: 14 (R14)
; colour end address is: 20 (R20)
;st7735.c,339 :: 		if (fraction >= 0)
; colour start address is: 20 (R20)
; stepy start address is: 14 (R14)
; stepx start address is: 10 (R10)
; dx start address is: 24 (R24)
; dy start address is: 22 (R22)
	LDI        R16, 0
	LDI        R17, 0
	CP         R12, R16
	CPC        R13, R17
	BRGE       L__Draw_Line221
	JMP        L__Draw_Line152
L__Draw_Line221:
;st7735.c,341 :: 		y1 += stepy;
	MOVW       R16, R14
	ADD        R16, R4
	ADC        R17, R5
	MOVW       R4, R16
;st7735.c,342 :: 		fraction -= dx;
	MOVW       R16, R12
	SUB        R16, R24
	SBC        R17, R25
	MOVW       R12, R16
; fraction end address is: 12 (R12)
;st7735.c,343 :: 		}
	JMP        L_Draw_Line41
L__Draw_Line152:
;st7735.c,339 :: 		if (fraction >= 0)
;st7735.c,343 :: 		}
L_Draw_Line41:
;st7735.c,344 :: 		x1 += stepx;
; fraction start address is: 12 (R12)
	MOVW       R18, R10
	ADD        R18, R2
	ADC        R19, R3
	MOVW       R2, R18
;st7735.c,345 :: 		fraction += dy;
	MOVW       R16, R22
	ADD        R16, R12
	ADC        R17, R13
	MOVW       R12, R16
;st7735.c,347 :: 		Draw_Pixel(x1, y1, colour);
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R3, R4
	MOVW       R4, R20
	MOV        R2, R18
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,348 :: 		}
; dy end address is: 22 (R22)
; dx end address is: 24 (R24)
; stepx end address is: 10 (R10)
; stepy end address is: 14 (R14)
; colour end address is: 20 (R20)
; fraction end address is: 12 (R12)
	JMP        L_Draw_Line39
L_Draw_Line40:
;st7735.c,349 :: 		}
	JMP        L_Draw_Line42
L_Draw_Line38:
;st7735.c,352 :: 		fraction = (dx - (dy >> 1));
; colour start address is: 20 (R20)
; stepx start address is: 10 (R10)
; dx start address is: 24 (R24)
; dy start address is: 22 (R22)
; stepy start address is: 18 (R18)
	MOVW       R16, R22
	ASR        R17
	ROR        R16
	MOVW       R0, R16
	MOVW       R16, R24
	SUB        R16, R0
	SBC        R17, R1
; fraction start address is: 12 (R12)
	MOVW       R12, R16
; stepy end address is: 18 (R18)
; dy end address is: 22 (R22)
; dx end address is: 24 (R24)
; stepx end address is: 10 (R10)
; colour end address is: 20 (R20)
; fraction end address is: 12 (R12)
	PUSH       R23
	PUSH       R22
	MOVW       R22, R24
	MOVW       R24, R10
	MOVW       R10, R18
	MOVW       R18, R12
	MOVW       R12, R20
	POP        R20
	POP        R21
;st7735.c,354 :: 		while (y1 != y2)
L_Draw_Line43:
; colour start address is: 12 (R12)
; stepy start address is: 10 (R10)
; stepx start address is: 24 (R24)
; dx start address is: 22 (R22)
; dy start address is: 20 (R20)
; fraction start address is: 18 (R18)
; dy start address is: 20 (R20)
; dy end address is: 20 (R20)
; dx start address is: 22 (R22)
; dx end address is: 22 (R22)
; stepx start address is: 24 (R24)
; stepx end address is: 24 (R24)
; stepy start address is: 10 (R10)
; stepy end address is: 10 (R10)
; colour start address is: 12 (R12)
; colour end address is: 12 (R12)
	CP         R4, R8
	CPC        R5, R9
	BRNE       L__Draw_Line222
	JMP        L_Draw_Line44
L__Draw_Line222:
; dy end address is: 20 (R20)
; dx end address is: 22 (R22)
; stepx end address is: 24 (R24)
; stepy end address is: 10 (R10)
; colour end address is: 12 (R12)
;st7735.c,356 :: 		if (fraction >= 0)
; colour start address is: 12 (R12)
; stepy start address is: 10 (R10)
; stepx start address is: 24 (R24)
; dx start address is: 22 (R22)
; dy start address is: 20 (R20)
	LDI        R16, 0
	LDI        R17, 0
	CP         R18, R16
	CPC        R19, R17
	BRGE       L__Draw_Line223
	JMP        L__Draw_Line153
L__Draw_Line223:
;st7735.c,358 :: 		x1 += stepx;
	MOVW       R16, R24
	ADD        R16, R2
	ADC        R17, R3
	MOVW       R2, R16
;st7735.c,359 :: 		fraction -= dy;
	MOVW       R16, R18
	SUB        R16, R20
	SBC        R17, R21
; fraction end address is: 18 (R18)
; fraction start address is: 14 (R14)
	MOVW       R14, R16
; fraction end address is: 14 (R14)
;st7735.c,360 :: 		}
	JMP        L_Draw_Line45
L__Draw_Line153:
;st7735.c,356 :: 		if (fraction >= 0)
	MOVW       R14, R18
;st7735.c,360 :: 		}
L_Draw_Line45:
;st7735.c,361 :: 		y1 += stepy;
; fraction start address is: 14 (R14)
	MOVW       R18, R10
	ADD        R18, R4
	ADC        R19, R5
	MOVW       R4, R18
;st7735.c,362 :: 		fraction += dx;
	MOVW       R16, R22
	ADD        R16, R14
	ADC        R17, R15
; fraction end address is: 14 (R14)
; fraction start address is: 16 (R16)
;st7735.c,363 :: 		Draw_Pixel(x1, y1, colour);
	PUSH       R17
	PUSH       R16
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R12
	MOV        R3, R18
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R16
	POP        R17
;st7735.c,364 :: 		}
; dy end address is: 20 (R20)
; dx end address is: 22 (R22)
; stepx end address is: 24 (R24)
; stepy end address is: 10 (R10)
; colour end address is: 12 (R12)
; fraction end address is: 16 (R16)
	MOVW       R18, R16
	JMP        L_Draw_Line43
L_Draw_Line44:
;st7735.c,365 :: 		}
L_Draw_Line42:
;st7735.c,366 :: 		}
L_end_Draw_Line:
	POP        R29
	POP        R28
	RET
; end of _Draw_Line

_Draw_Rectangle:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 2
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;st7735.c,369 :: 		void Draw_Rectangle(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char fill, unsigned char type, unsigned int colour, unsigned int back_colour)
; fill start address is: 18 (R18)
	LDD        R18, Y+6
	LDD        R16, Y+7
	STD        Y+7, R16
	LDD        R16, Y+8
	LDD        R17, Y+9
	STD        Y+8, R16
	STD        Y+9, R17
	LDD        R16, Y+10
	LDD        R17, Y+11
	STD        Y+10, R16
	STD        Y+11, R17
;st7735.c,371 :: 		unsigned char i = 0x00;
;st7735.c,372 :: 		unsigned char xmin = 0x00;
;st7735.c,373 :: 		unsigned char xmax = 0x00;
;st7735.c,374 :: 		unsigned char ymin = 0x00;
;st7735.c,375 :: 		unsigned char ymax = 0x00;
;st7735.c,377 :: 		if(fill != NO)
	CPI        R18, 0
	BRNE       L__Draw_Rectangle225
	JMP        L_Draw_Rectangle46
L__Draw_Rectangle225:
; fill end address is: 18 (R18)
;st7735.c,379 :: 		if(x1 < x2)
	CP         R2, R6
	CPC        R3, R7
	BRLT       L__Draw_Rectangle226
	JMP        L_Draw_Rectangle47
L__Draw_Rectangle226:
;st7735.c,381 :: 		xmin = x1;
; xmin start address is: 22 (R22)
	MOV        R22, R2
;st7735.c,382 :: 		xmax = x2;
; xmax start address is: 21 (R21)
	MOV        R21, R6
;st7735.c,383 :: 		}
	MOV        R20, R22
; xmin end address is: 22 (R22)
; xmax end address is: 21 (R21)
	MOV        R24, R21
	JMP        L_Draw_Rectangle48
L_Draw_Rectangle47:
;st7735.c,386 :: 		xmin = x2;
; xmin start address is: 22 (R22)
	MOV        R22, R6
;st7735.c,387 :: 		xmax = x1;
; xmax start address is: 21 (R21)
	MOV        R21, R2
; xmin end address is: 22 (R22)
; xmax end address is: 21 (R21)
	MOV        R20, R22
	MOV        R24, R21
;st7735.c,388 :: 		}
L_Draw_Rectangle48:
;st7735.c,390 :: 		if(y1 < y2)
; xmax start address is: 24 (R24)
; xmin start address is: 20 (R20)
	CP         R4, R8
	CPC        R5, R9
	BRLT       L__Draw_Rectangle227
	JMP        L_Draw_Rectangle49
L__Draw_Rectangle227:
;st7735.c,392 :: 		ymin = y1;
	STD        Y+0, R4
;st7735.c,393 :: 		ymax = y2;
	STD        Y+1, R8
;st7735.c,394 :: 		}
	JMP        L_Draw_Rectangle50
L_Draw_Rectangle49:
;st7735.c,397 :: 		ymin = y2;
	STD        Y+0, R8
;st7735.c,398 :: 		ymax = y1;
	STD        Y+1, R4
;st7735.c,399 :: 		}
L_Draw_Rectangle50:
;st7735.c,401 :: 		for(; xmin <= xmax; ++xmin)
	MOV        R16, R24
; xmin end address is: 20 (R20)
; xmax end address is: 24 (R24)
	MOV        R26, R20
L_Draw_Rectangle51:
; xmin start address is: 26 (R26)
; xmax start address is: 16 (R16)
	CP         R16, R26
	BRSH       L__Draw_Rectangle228
	JMP        L_Draw_Rectangle52
L__Draw_Rectangle228:
;st7735.c,403 :: 		for(i = ymin; i <= ymax; ++i)
; i start address is: 18 (R18)
	LDD        R18, Y+0
; xmax end address is: 16 (R16)
; i end address is: 18 (R18)
; xmin end address is: 26 (R26)
	MOV        R24, R16
	MOV        R17, R18
L_Draw_Rectangle54:
; i start address is: 17 (R17)
; xmax start address is: 24 (R24)
; xmin start address is: 26 (R26)
	LDD        R16, Y+1
	CP         R16, R17
	BRSH       L__Draw_Rectangle229
	JMP        L_Draw_Rectangle55
L__Draw_Rectangle229:
;st7735.c,405 :: 		Draw_Pixel(xmin, i, colour);
	PUSH       R17
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDD        R4, Y+8
	LDD        R5, Y+9
	MOV        R3, R17
	MOV        R2, R26
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R17
;st7735.c,403 :: 		for(i = ymin; i <= ymax; ++i)
	MOV        R16, R17
	SUBI       R16, 255
; i end address is: 17 (R17)
; i start address is: 18 (R18)
	MOV        R18, R16
;st7735.c,406 :: 		}
; i end address is: 18 (R18)
	MOV        R17, R18
	JMP        L_Draw_Rectangle54
L_Draw_Rectangle55:
;st7735.c,401 :: 		for(; xmin <= xmax; ++xmin)
	MOV        R16, R26
	SUBI       R16, 255
	MOV        R26, R16
;st7735.c,407 :: 		}
	MOV        R16, R24
; xmax end address is: 24 (R24)
; xmin end address is: 26 (R26)
	JMP        L_Draw_Rectangle51
L_Draw_Rectangle52:
;st7735.c,408 :: 		}
	JMP        L_Draw_Rectangle57
L_Draw_Rectangle46:
;st7735.c,412 :: 		Draw_Line(x1, y1, x2, y1, colour);
	PUSH       R9
	PUSH       R8
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R8, R4
	LDD        R16, Y+8
	LDD        R17, Y+9
	PUSH       R17
	PUSH       R16
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R8
	POP        R9
;st7735.c,413 :: 		Draw_Line(x1, y2, x2, y2, colour);
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R8
	LDD        R16, Y+8
	LDD        R17, Y+9
	PUSH       R17
	PUSH       R16
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,414 :: 		Draw_Line(x1, y1, x1, y2, colour);
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R6, R2
	LDD        R16, Y+8
	LDD        R17, Y+9
	PUSH       R17
	PUSH       R16
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
;st7735.c,415 :: 		Draw_Line(x2, y1, x2, y2, colour);
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R2, R6
	LDD        R16, Y+8
	LDD        R17, Y+9
	PUSH       R17
	PUSH       R16
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,416 :: 		}
L_Draw_Rectangle57:
;st7735.c,418 :: 		if(type != SQUARE)
	LDD        R16, Y+7
	CPI        R16, 0
	BRNE       L__Draw_Rectangle230
	JMP        L_Draw_Rectangle58
L__Draw_Rectangle230:
;st7735.c,420 :: 		Draw_Pixel(x1, y1, back_colour);
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R3, R4
	LDD        R4, Y+10
	LDD        R5, Y+11
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
;st7735.c,421 :: 		Draw_Pixel(x1, y2, back_colour);
	PUSH       R3
	PUSH       R2
	LDD        R4, Y+10
	LDD        R5, Y+11
	MOV        R3, R8
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,422 :: 		Draw_Pixel(x2, y1, back_colour);
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R3, R4
	LDD        R4, Y+10
	LDD        R5, Y+11
	MOV        R2, R6
	CALL       _Draw_Pixel+0
;st7735.c,423 :: 		Draw_Pixel(x2, y2, back_colour);
	LDD        R4, Y+10
	LDD        R5, Y+11
	MOV        R3, R8
	MOV        R2, R6
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,424 :: 		}
L_Draw_Rectangle58:
;st7735.c,425 :: 		}
L_end_Draw_Rectangle:
	ADIW       R28, 1
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _Draw_Rectangle

_Draw_Circle:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 2
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;st7735.c,428 :: 		void Draw_Circle(signed int xc, signed int yc, signed int radius, unsigned char fill, unsigned int colour)
	PUSH       R9
; colour start address is: 18 (R18)
	LDD        R18, Y+6
	LDD        R19, Y+7
;st7735.c,430 :: 		signed int a = 0x0000;
; a start address is: 11 (R11)
	CLR        R11
	CLR        R12
;st7735.c,431 :: 		signed int b = 0x0000;
;st7735.c,432 :: 		signed int p = 0x0000;
;st7735.c,434 :: 		b = radius;
; b start address is: 24 (R24)
	MOVW       R24, R6
;st7735.c,435 :: 		p = (1 - b);
	LDI        R16, 1
	LDI        R17, 0
	SUB        R16, R6
	SBC        R17, R7
	STD        Y+0, R16
	STD        Y+1, R17
; colour end address is: 18 (R18)
; b end address is: 24 (R24)
; a end address is: 11 (R11)
	MOVW       R22, R24
	MOVW       R24, R18
	MOV        R9, R11
	MOV        R10, R12
;st7735.c,437 :: 		do
	JMP        L_Draw_Circle59
L__Draw_Circle154:
;st7735.c,466 :: 		}while(a <= b);
	MOV        R9, R11
	MOV        R10, R12
;st7735.c,437 :: 		do
L_Draw_Circle59:
;st7735.c,439 :: 		if(fill != NO)
; colour start address is: 24 (R24)
; b start address is: 22 (R22)
; a start address is: 9 (R9)
; colour start address is: 24 (R24)
; colour end address is: 24 (R24)
	LDI        R27, 0
	CP         R8, R27
	BRNE       L__Draw_Circle232
	JMP        L_Draw_Circle62
L__Draw_Circle232:
; colour end address is: 24 (R24)
;st7735.c,441 :: 		Draw_Line((xc - a), (yc + b), (xc + a), (yc + b), colour);
; colour start address is: 24 (R24)
	MOVW       R20, R22
	ADD        R20, R4
	ADC        R21, R5
	MOV        R18, R9
	MOV        R19, R10
	ADD        R18, R2
	ADC        R19, R3
	MOVW       R16, R2
	SUB        R16, R9
	SBC        R17, R10
	PUSH       R25
	PUSH       R24
	PUSH       R10
	PUSH       R9
	PUSH       R23
	PUSH       R22
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R8, R20
	MOVW       R6, R18
	MOVW       R4, R20
	MOVW       R2, R16
	PUSH       R25
	PUSH       R24
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R22
	POP        R23
	POP        R9
	POP        R10
	POP        R24
	POP        R25
;st7735.c,442 :: 		Draw_Line((xc - a), (yc - b), (xc + a), (yc - b), colour);
	MOVW       R20, R4
	SUB        R20, R22
	SBC        R21, R23
	MOV        R18, R9
	MOV        R19, R10
	ADD        R18, R2
	ADC        R19, R3
	MOVW       R16, R2
	SUB        R16, R9
	SBC        R17, R10
	PUSH       R25
	PUSH       R24
	PUSH       R10
	PUSH       R9
	PUSH       R23
	PUSH       R22
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R8, R20
	MOVW       R6, R18
	MOVW       R4, R20
	MOVW       R2, R16
	PUSH       R25
	PUSH       R24
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R22
	POP        R23
	POP        R9
	POP        R10
	POP        R24
	POP        R25
;st7735.c,443 :: 		Draw_Line((xc - b), (yc + a), (xc + b), (yc + a), colour);
	MOV        R20, R9
	MOV        R21, R10
	ADD        R20, R4
	ADC        R21, R5
	MOVW       R18, R22
	ADD        R18, R2
	ADC        R19, R3
	MOVW       R16, R2
	SUB        R16, R22
	SBC        R17, R23
	PUSH       R25
	PUSH       R24
	PUSH       R10
	PUSH       R9
	PUSH       R23
	PUSH       R22
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R8, R20
	MOVW       R6, R18
	MOVW       R4, R20
	MOVW       R2, R16
	PUSH       R25
	PUSH       R24
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R22
	POP        R23
	POP        R9
	POP        R10
	POP        R24
	POP        R25
;st7735.c,444 :: 		Draw_Line((xc - b), (yc - a), (xc + b), (yc - a), colour);
	MOVW       R20, R4
	SUB        R20, R9
	SBC        R21, R10
	MOVW       R18, R22
	ADD        R18, R2
	ADC        R19, R3
	MOVW       R16, R2
	SUB        R16, R22
	SBC        R17, R23
	PUSH       R25
	PUSH       R24
	PUSH       R10
	PUSH       R9
	PUSH       R23
	PUSH       R22
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R8, R20
	MOVW       R6, R18
	MOVW       R4, R20
	MOVW       R2, R16
	PUSH       R25
	PUSH       R24
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R22
	POP        R23
	POP        R9
	POP        R10
	POP        R24
	POP        R25
;st7735.c,445 :: 		}
	JMP        L_Draw_Circle63
L_Draw_Circle62:
;st7735.c,448 :: 		Draw_Pixel((xc + a), (yc + b), colour);
	MOV        R17, R4
	ADD        R17, R22
	MOV        R16, R2
	ADD        R16, R9
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R24
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,449 :: 		Draw_Pixel((xc + b), (yc + a), colour);
	MOV        R17, R4
	ADD        R17, R9
	MOV        R16, R2
	ADD        R16, R22
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R24
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,450 :: 		Draw_Pixel((xc - a), (yc + b), colour);
	MOV        R17, R4
	ADD        R17, R22
	MOV        R16, R2
	SUB        R16, R9
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R24
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,451 :: 		Draw_Pixel((xc - b), (yc + a), colour);
	MOV        R17, R4
	ADD        R17, R9
	MOV        R16, R2
	SUB        R16, R22
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R24
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,452 :: 		Draw_Pixel((xc + b), (yc - a), colour);
	MOV        R17, R4
	SUB        R17, R9
	MOV        R16, R2
	ADD        R16, R22
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R24
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,453 :: 		Draw_Pixel((xc + a), (yc - b), colour);
	MOV        R17, R4
	SUB        R17, R22
	MOV        R16, R2
	ADD        R16, R9
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R24
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,454 :: 		Draw_Pixel((xc - a), (yc - b), colour);
	MOV        R17, R4
	SUB        R17, R22
	MOV        R16, R2
	SUB        R16, R9
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R24
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,455 :: 		Draw_Pixel((xc - b), (yc - a), colour);
	MOV        R17, R4
	SUB        R17, R9
	MOV        R16, R2
	SUB        R16, R22
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R24
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;st7735.c,456 :: 		}
L_Draw_Circle63:
;st7735.c,458 :: 		if(p < 0)
	LDD        R18, Y+0
	LDD        R19, Y+1
	LDI        R16, 0
	LDI        R17, 0
	CP         R18, R16
	CPC        R19, R17
	BRLT       L__Draw_Circle233
	JMP        L_Draw_Circle64
L__Draw_Circle233:
;st7735.c,460 :: 		p += (0x03 + (0x02 * a++));
	MOV        R16, R9
	MOV        R17, R10
	LSL        R16
	ROL        R17
	MOVW       R18, R16
	SUBI       R18, 253
	SBCI       R19, 255
	LDD        R16, Y+0
	LDD        R17, Y+1
	ADD        R16, R18
	ADC        R17, R19
	STD        Y+0, R16
	STD        Y+1, R17
	MOV        R16, R9
	MOV        R17, R10
	SUBI       R16, 255
	SBCI       R17, 255
; a end address is: 9 (R9)
; a start address is: 11 (R11)
	MOV        R11, R16
	MOV        R12, R17
;st7735.c,461 :: 		}
; a end address is: 11 (R11)
	JMP        L_Draw_Circle65
L_Draw_Circle64:
;st7735.c,464 :: 		p += (0x05 + (0x02 * ((a++) - (b--))));
; a start address is: 9 (R9)
	MOV        R16, R9
	MOV        R17, R10
	SUB        R16, R22
	SBC        R17, R23
	LSL        R16
	ROL        R17
	MOVW       R18, R16
	SUBI       R18, 251
	SBCI       R19, 255
	LDD        R16, Y+0
	LDD        R17, Y+1
	ADD        R16, R18
	ADC        R17, R19
	STD        Y+0, R16
	STD        Y+1, R17
	MOV        R16, R9
	MOV        R17, R10
	SUBI       R16, 255
	SBCI       R17, 255
; a end address is: 9 (R9)
; a start address is: 11 (R11)
	MOV        R11, R16
	MOV        R12, R17
	MOVW       R16, R22
	SUBI       R16, 1
	SBCI       R17, 0
	MOVW       R22, R16
; b end address is: 22 (R22)
; a end address is: 11 (R11)
;st7735.c,465 :: 		}
L_Draw_Circle65:
;st7735.c,466 :: 		}while(a <= b);
; b start address is: 22 (R22)
; a start address is: 11 (R11)
	CP         R22, R11
	CPC        R23, R12
	BRLT       L__Draw_Circle234
	JMP        L__Draw_Circle154
L__Draw_Circle234:
; colour end address is: 24 (R24)
; b end address is: 22 (R22)
; a end address is: 11 (R11)
;st7735.c,467 :: 		}
L_end_Draw_Circle:
	POP        R9
	ADIW       R28, 1
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _Draw_Circle

_Draw_Font_Pixel:

;st7735.c,470 :: 		void Draw_Font_Pixel(unsigned char x_pos, unsigned char y_pos, unsigned int colour, unsigned char pixel_size)
;st7735.c,472 :: 		unsigned char i = 0x00;
;st7735.c,474 :: 		Set_Addr_Window(x_pos, y_pos, (x_pos + pixel_size - 1), (y_pos + pixel_size - 1));
	MOV        R16, R3
	ADD        R16, R6
	MOV        R17, R16
	SUBI       R17, 1
	MOV        R16, R2
	ADD        R16, R6
	SUBI       R16, 1
	PUSH       R5
	PUSH       R4
	MOV        R5, R17
	MOV        R4, R16
	CALL       _Set_Addr_Window+0
	POP        R4
	POP        R5
;st7735.c,476 :: 		for(i = 0x00; i < (pixel_size * pixel_size); i++)
; i start address is: 20 (R20)
	LDI        R20, 0
; i end address is: 20 (R20)
L_Draw_Font_Pixel66:
; i start address is: 20 (R20)
	MUL        R6, R6
	MOVW       R18, R0
	MOV        R16, R20
	LDI        R17, 0
	CP         R16, R18
	CPC        R17, R19
	BRLT       L__Draw_Font_Pixel236
	JMP        L_Draw_Font_Pixel67
L__Draw_Font_Pixel236:
;st7735.c,478 :: 		ST7735_Word_Write(colour);
	PUSH       R3
	PUSH       R2
	MOVW       R2, R4
	CALL       _ST7735_Word_Write+0
	POP        R2
	POP        R3
;st7735.c,476 :: 		for(i = 0x00; i < (pixel_size * pixel_size); i++)
	MOV        R16, R20
	SUBI       R16, 255
	MOV        R20, R16
;st7735.c,479 :: 		}
; i end address is: 20 (R20)
	JMP        L_Draw_Font_Pixel66
L_Draw_Font_Pixel67:
;st7735.c,480 :: 		}
L_end_Draw_Font_Pixel:
	RET
; end of _Draw_Font_Pixel

_print_char:

;st7735.c,483 :: 		void print_char(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char ch)
;st7735.c,485 :: 		unsigned char i = 0x00;
;st7735.c,486 :: 		unsigned char j = 0x00;
;st7735.c,488 :: 		unsigned char value = 0x00;
;st7735.c,490 :: 		if(font_size < 0)
	LDI        R27, 0
	CP         R4, R27
	BRLO       L__print_char238
	JMP        L_print_char69
L__print_char238:
;st7735.c,492 :: 		font_size = 1;
	LDI        R27, 1
	MOV        R4, R27
;st7735.c,493 :: 		}
L_print_char69:
;st7735.c,495 :: 		if(x_pos < font_size)
	CP         R2, R4
	BRLO       L__print_char239
	JMP        L_print_char70
L__print_char239:
;st7735.c,497 :: 		x_pos = font_size;
	MOV        R2, R4
;st7735.c,498 :: 		}
L_print_char70:
;st7735.c,500 :: 		for (i = 0x00; i < 0x05; i++)
; i start address is: 20 (R20)
	LDI        R20, 0
; i end address is: 20 (R20)
L_print_char71:
; i start address is: 20 (R20)
	CPI        R20, 5
	BRLO       L__print_char240
	JMP        L_print_char72
L__print_char240:
;st7735.c,502 :: 		for (j = 0x00; j < 0x08; j++)
; j start address is: 21 (R21)
	LDI        R21, 0
; j end address is: 21 (R21)
; i end address is: 20 (R20)
L_print_char74:
; j start address is: 21 (R21)
; i start address is: 20 (R20)
	CPI        R21, 8
	BRLO       L__print_char241
	JMP        L_print_char75
L__print_char241:
;st7735.c,505 :: 		value = ((font[((unsigned char)ch) - 0x20][i]));
	MOV        R16, R9
	LDI        R17, 0
	SUBI       R16, 32
	SBCI       R17, 0
	PUSH       R20
	PUSH       R21
	LDI        R20, 5
	LDI        R21, 0
	CALL       _HWMul_16x16+0
	POP        R21
	POP        R20
	LDI        R18, #lo_addr(TFT_display_demo_font+0)
	LDI        R19, hi_addr(TFT_display_demo_font+0)
	ADD        R16, R18
	ADC        R17, R19
	MOV        R30, R20
	LDI        R31, 0
	ADD        R30, R16
	ADC        R31, R17
	LPM        R16, Z
;st7735.c,507 :: 		if((value >> j)  & 0x01)
	MOV        R27, R21
	TST        R27
	BREQ       L__print_char243
L__print_char242:
	LSR        R16
	DEC        R27
	BRNE       L__print_char242
L__print_char243:
	SBRS       R16, 0
	JMP        L_print_char77
;st7735.c,509 :: 		Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
	PUSH       R20
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R2
	PUSH       R6
	PUSH       R5
	MOV        R6, R4
	POP        R4
	POP        R5
	CALL       _Draw_Font_Pixel+0
	POP        R2
	POP        R4
	POP        R5
	POP        R6
	POP        R20
;st7735.c,510 :: 		}
	JMP        L_print_char78
L_print_char77:
;st7735.c,513 :: 		Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
	PUSH       R20
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R2
	MOV        R6, R4
	MOV        R4, R7
	MOV        R5, R8
	CALL       _Draw_Font_Pixel+0
	POP        R2
	POP        R4
	POP        R5
	POP        R6
	POP        R20
;st7735.c,514 :: 		}
L_print_char78:
;st7735.c,516 :: 		y_pos = y_pos + font_size;
	MOV        R16, R3
	ADD        R16, R4
	MOV        R3, R16
;st7735.c,502 :: 		for (j = 0x00; j < 0x08; j++)
	MOV        R16, R21
	SUBI       R16, 255
	MOV        R21, R16
;st7735.c,517 :: 		}
; j end address is: 21 (R21)
	JMP        L_print_char74
L_print_char75:
;st7735.c,518 :: 		y_pos -= (font_size << 0x03);
	MOV        R16, R4
	LSL        R16
	LSL        R16
	LSL        R16
	MOV        R0, R16
	MOV        R16, R3
	SUB        R16, R0
	MOV        R3, R16
;st7735.c,519 :: 		x_pos += font_size;
	MOV        R16, R2
	ADD        R16, R4
	MOV        R2, R16
;st7735.c,500 :: 		for (i = 0x00; i < 0x05; i++)
	MOV        R16, R20
	SUBI       R16, 255
	MOV        R20, R16
;st7735.c,521 :: 		}
; i end address is: 20 (R20)
	JMP        L_print_char71
L_print_char72:
;st7735.c,522 :: 		x_pos += font_size;
	MOV        R17, R2
	ADD        R17, R4
	MOV        R2, R17
;st7735.c,524 :: 		if(x_pos > w)
	LDS        R16, _w+0
	CP         R16, R17
	BRLO       L__print_char244
	JMP        L_print_char79
L__print_char244:
;st7735.c,526 :: 		x_pos = (font_size + 0x01);
	MOV        R16, R4
	SUBI       R16, 255
	MOV        R2, R16
;st7735.c,527 :: 		y_pos += (font_size << 0x03);
	MOV        R16, R4
	LSL        R16
	LSL        R16
	LSL        R16
	ADD        R16, R3
	MOV        R3, R16
;st7735.c,528 :: 		}
L_print_char79:
;st7735.c,529 :: 		}
L_end_print_char:
	RET
; end of _print_char

_print_str:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	ADIW       R28, 5

;st7735.c,532 :: 		void print_str(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char *ch)
	PUSH       R9
; ch start address is: 19 (R19)
; ch start address is: 19 (R19)
	LDD        R19, Y+0
	LDD        R20, Y+1
; ch end address is: 19 (R19)
;st7735.c,534 :: 		do
L_print_str80:
;st7735.c,536 :: 		print_char(x_pos, y_pos, font_size, colour, back_colour, *ch++);
; ch start address is: 19 (R19)
	MOV        R30, R19
	MOV        R31, R20
	LD         R16, Z
	PUSH       R20
	PUSH       R19
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R9, R16
	CALL       _print_char+0
	POP        R2
	POP        R3
	POP        R4
	POP        R19
	POP        R20
	MOV        R17, R19
	MOV        R18, R20
	SUBI       R17, 255
	SBCI       R18, 255
	MOV        R19, R17
	MOV        R20, R18
; ch end address is: 19 (R19)
;st7735.c,537 :: 		x_pos += (font_size * 0x06);
	LDI        R16, 6
	MUL        R4, R16
	MOV        R16, R0
	ADD        R16, R2
	MOV        R2, R16
;st7735.c,538 :: 		}while((*ch >= 0x20) && (*ch <= 0x7F));
	MOV        R30, R17
	MOV        R31, R18
	LD         R16, Z
	CPI        R16, 32
	BRSH       L__print_str246
	JMP        L__print_str157
L__print_str246:
; ch end address is: 19 (R19)
; ch start address is: 19 (R19)
	MOV        R30, R19
	MOV        R31, R20
	LD         R17, Z
	LDI        R16, 127
	CP         R16, R17
	BRSH       L__print_str247
	JMP        L__print_str156
L__print_str247:
; ch end address is: 19 (R19)
	JMP        L_print_str80
L__print_str157:
L__print_str156:
;st7735.c,539 :: 		}
L_end_print_str:
	POP        R9
	POP        R29
	POP        R28
	RET
; end of _print_str

_print_C:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 8
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;st7735.c,542 :: 		void print_C(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, signed int value)
; value start address is: 19 (R19)
	LDD        R19, Y+12
	LDD        R20, Y+13
;st7735.c,544 :: 		unsigned char ch[6] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20};
	LDI        R27, 32
	STD        Y+0, R27
	LDI        R27, 32
	STD        Y+1, R27
	LDI        R27, 32
	STD        Y+2, R27
	LDI        R27, 32
	STD        Y+3, R27
	LDI        R27, 32
	STD        Y+4, R27
	LDI        R27, 32
	STD        Y+5, R27
;st7735.c,546 :: 		if(value < 0x00)
	LDI        R16, 0
	LDI        R17, 0
	CP         R19, R16
	CPC        R20, R17
	BRLT       L__print_C249
	JMP        L_print_C85
L__print_C249:
;st7735.c,549 :: 		ch[0] = 0x2D;
	MOVW       R30, R28
	LDI        R27, 45
	ST         Z, R27
;st7735.c,550 :: 		value = -value;
	LDI        R16, 0
	LDI        R17, 0
	SUB        R16, R19
	SBC        R17, R20
	MOV        R19, R16
	MOV        R20, R17
;st7735.c,551 :: 		}
	JMP        L_print_C86
L_print_C85:
;st7735.c,554 :: 		ch[0] = 0x20;
	MOVW       R30, R28
	LDI        R27, 32
	ST         Z, R27
; value end address is: 19 (R19)
;st7735.c,555 :: 		}
L_print_C86:
;st7735.c,557 :: 		if((value > 99) && (value <= 999))
; value start address is: 19 (R19)
	LDI        R16, 99
	LDI        R17, 0
	CP         R16, R19
	CPC        R17, R20
	BRLT       L__print_C250
	JMP        L__print_C162
L__print_C250:
	LDI        R16, 231
	LDI        R17, 3
	CP         R16, R19
	CPC        R17, R20
	BRGE       L__print_C251
	JMP        L__print_C161
L__print_C251:
L__print_C160:
;st7735.c,559 :: 		ch[1] = ((value / 100) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 255
	SBCI       R17, 255
	STD        Y+6, R16
	STD        Y+7, R17
	PUSH       R20
	PUSH       R19
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R16, R19
	MOV        R17, R20
	LDI        R20, 100
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R19
	POP        R20
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+6
	LDD        R17, Y+7
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,560 :: 		ch[2] = (((value % 100) / 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 254
	SBCI       R17, 255
	STD        Y+6, R16
	STD        Y+7, R17
	PUSH       R20
	PUSH       R19
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R16, R19
	MOV        R17, R20
	LDI        R20, 100
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	LDI        R20, 10
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R19
	POP        R20
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+6
	LDD        R17, Y+7
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,561 :: 		ch[3] = ((value % 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 253
	SBCI       R17, 255
	STD        Y+6, R16
	STD        Y+7, R17
	PUSH       R8
	PUSH       R7
; value end address is: 19 (R19)
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R16, R19
	MOV        R17, R20
	LDI        R20, 10
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+6
	LDD        R17, Y+7
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,562 :: 		}
	JMP        L_print_C90
;st7735.c,557 :: 		if((value > 99) && (value <= 999))
L__print_C162:
; value start address is: 19 (R19)
L__print_C161:
;st7735.c,563 :: 		else if((value > 9) && (value <= 99))
	LDI        R16, 9
	LDI        R17, 0
	CP         R16, R19
	CPC        R17, R20
	BRLT       L__print_C252
	JMP        L__print_C164
L__print_C252:
	LDI        R16, 99
	LDI        R17, 0
	CP         R16, R19
	CPC        R17, R20
	BRGE       L__print_C253
	JMP        L__print_C163
L__print_C253:
L__print_C159:
;st7735.c,565 :: 		ch[1] = (((value % 100) / 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 255
	SBCI       R17, 255
	STD        Y+6, R16
	STD        Y+7, R17
	PUSH       R20
	PUSH       R19
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R16, R19
	MOV        R17, R20
	LDI        R20, 100
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	LDI        R20, 10
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R19
	POP        R20
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+6
	LDD        R17, Y+7
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,566 :: 		ch[2] = ((value % 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 254
	SBCI       R17, 255
	STD        Y+6, R16
	STD        Y+7, R17
	PUSH       R8
	PUSH       R7
; value end address is: 19 (R19)
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R16, R19
	MOV        R17, R20
	LDI        R20, 10
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+6
	LDD        R17, Y+7
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,567 :: 		ch[3] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 3
	LDI        R27, 32
	ST         Z, R27
;st7735.c,568 :: 		}
	JMP        L_print_C94
;st7735.c,563 :: 		else if((value > 9) && (value <= 99))
L__print_C164:
; value start address is: 19 (R19)
L__print_C163:
;st7735.c,569 :: 		else if((value >= 0) && (value <= 9))
	LDI        R16, 0
	LDI        R17, 0
	CP         R19, R16
	CPC        R20, R17
	BRGE       L__print_C254
	JMP        L__print_C166
L__print_C254:
	LDI        R16, 9
	LDI        R17, 0
	CP         R16, R19
	CPC        R17, R20
	BRGE       L__print_C255
	JMP        L__print_C165
L__print_C255:
L__print_C158:
;st7735.c,571 :: 		ch[1] = ((value % 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 255
	SBCI       R17, 255
	STD        Y+6, R16
	STD        Y+7, R17
	PUSH       R8
	PUSH       R7
; value end address is: 19 (R19)
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R16, R19
	MOV        R17, R20
	LDI        R20, 10
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+6
	LDD        R17, Y+7
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,572 :: 		ch[2] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 2
	LDI        R27, 32
	ST         Z, R27
;st7735.c,573 :: 		ch[3] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 3
	LDI        R27, 32
	ST         Z, R27
;st7735.c,569 :: 		else if((value >= 0) && (value <= 9))
L__print_C166:
L__print_C165:
;st7735.c,574 :: 		}
L_print_C94:
L_print_C90:
;st7735.c,576 :: 		print_str(x_pos, y_pos, font_size, colour, back_colour, ch);
	MOVW       R16, R28
	PUSH       R17
	PUSH       R16
	CALL       _print_str+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,577 :: 		}
L_end_print_C:
	ADIW       R28, 7
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _print_C

_print_I:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 10
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;st7735.c,580 :: 		void print_I(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, signed int value)
	LDD        R16, Y+14
	LDD        R17, Y+15
	STD        Y+14, R16
	STD        Y+15, R17
;st7735.c,582 :: 		unsigned char ch[6] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20};
	LDI        R27, 32
	STD        Y+0, R27
	LDI        R27, 32
	STD        Y+1, R27
	LDI        R27, 32
	STD        Y+2, R27
	LDI        R27, 32
	STD        Y+3, R27
	LDI        R27, 32
	STD        Y+4, R27
	LDI        R27, 32
	STD        Y+5, R27
;st7735.c,584 :: 		if(value < 0)
	LDD        R18, Y+14
	LDD        R19, Y+15
	LDI        R16, 0
	LDI        R17, 0
	CP         R18, R16
	CPC        R19, R17
	BRLT       L__print_I257
	JMP        L_print_I98
L__print_I257:
;st7735.c,586 :: 		ch[0] = 0x2D;
	MOVW       R30, R28
	LDI        R27, 45
	ST         Z, R27
;st7735.c,587 :: 		value = -value;
	LDD        R0, Y+14
	LDD        R1, Y+15
	LDI        R16, 0
	LDI        R17, 0
	SUB        R16, R0
	SBC        R17, R1
	STD        Y+14, R16
	STD        Y+15, R17
;st7735.c,588 :: 		}
	JMP        L_print_I99
L_print_I98:
;st7735.c,591 :: 		ch[0] = 0x20;
	MOVW       R30, R28
	LDI        R27, 32
	ST         Z, R27
;st7735.c,592 :: 		}
L_print_I99:
;st7735.c,594 :: 		if(value > 9999)
	LDD        R18, Y+14
	LDD        R19, Y+15
	LDI        R16, 15
	LDI        R17, 39
	CP         R16, R18
	CPC        R17, R19
	BRLT       L__print_I258
	JMP        L_print_I100
L__print_I258:
;st7735.c,596 :: 		ch[1] = ((value / 10000) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 255
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 16
	LDI        R21, 39
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,597 :: 		ch[2] = (((value % 10000)/ 1000) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 254
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 16
	LDI        R21, 39
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	LDI        R20, 232
	LDI        R21, 3
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,598 :: 		ch[3] = (((value % 1000) / 100) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 253
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 232
	LDI        R21, 3
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	LDI        R20, 100
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,599 :: 		ch[4] = (((value % 100) / 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 252
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 100
	LDI        R21, 0
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	LDI        R20, 10
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,600 :: 		ch[5] = ((value % 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 251
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 10
	LDI        R21, 0
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,601 :: 		}
	JMP        L_print_I101
L_print_I100:
;st7735.c,603 :: 		else if((value > 999) && (value <= 9999))
	LDD        R18, Y+14
	LDD        R19, Y+15
	LDI        R16, 231
	LDI        R17, 3
	CP         R16, R18
	CPC        R17, R19
	BRLT       L__print_I259
	JMP        L__print_I171
L__print_I259:
	LDD        R18, Y+14
	LDD        R19, Y+15
	LDI        R16, 15
	LDI        R17, 39
	CP         R16, R18
	CPC        R17, R19
	BRGE       L__print_I260
	JMP        L__print_I170
L__print_I260:
L__print_I169:
;st7735.c,605 :: 		ch[1] = (((value % 10000)/ 1000) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 255
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 16
	LDI        R21, 39
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	LDI        R20, 232
	LDI        R21, 3
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,606 :: 		ch[2] = (((value % 1000) / 100) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 254
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 232
	LDI        R21, 3
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	LDI        R20, 100
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,607 :: 		ch[3] = (((value % 100) / 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 253
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 100
	LDI        R21, 0
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	LDI        R20, 10
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,608 :: 		ch[4] = ((value % 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 252
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 10
	LDI        R21, 0
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,609 :: 		ch[5] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 5
	LDI        R27, 32
	ST         Z, R27
;st7735.c,610 :: 		}
	JMP        L_print_I105
;st7735.c,603 :: 		else if((value > 999) && (value <= 9999))
L__print_I171:
L__print_I170:
;st7735.c,611 :: 		else if((value > 99) && (value <= 999))
	LDD        R18, Y+14
	LDD        R19, Y+15
	LDI        R16, 99
	LDI        R17, 0
	CP         R16, R18
	CPC        R17, R19
	BRLT       L__print_I261
	JMP        L__print_I173
L__print_I261:
	LDD        R18, Y+14
	LDD        R19, Y+15
	LDI        R16, 231
	LDI        R17, 3
	CP         R16, R18
	CPC        R17, R19
	BRGE       L__print_I262
	JMP        L__print_I172
L__print_I262:
L__print_I168:
;st7735.c,613 :: 		ch[1] = (((value % 1000) / 100) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 255
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 232
	LDI        R21, 3
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	LDI        R20, 100
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,614 :: 		ch[2] = (((value % 100) / 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 254
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 100
	LDI        R21, 0
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	LDI        R20, 10
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,615 :: 		ch[3] = ((value % 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 253
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 10
	LDI        R21, 0
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,616 :: 		ch[4] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 4
	LDI        R27, 32
	ST         Z, R27
;st7735.c,617 :: 		ch[5] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 5
	LDI        R27, 32
	ST         Z, R27
;st7735.c,618 :: 		}
	JMP        L_print_I109
;st7735.c,611 :: 		else if((value > 99) && (value <= 999))
L__print_I173:
L__print_I172:
;st7735.c,619 :: 		else if((value > 9) && (value <= 99))
	LDD        R18, Y+14
	LDD        R19, Y+15
	LDI        R16, 9
	LDI        R17, 0
	CP         R16, R18
	CPC        R17, R19
	BRLT       L__print_I263
	JMP        L__print_I175
L__print_I263:
	LDD        R18, Y+14
	LDD        R19, Y+15
	LDI        R16, 99
	LDI        R17, 0
	CP         R16, R18
	CPC        R17, R19
	BRGE       L__print_I264
	JMP        L__print_I174
L__print_I264:
L__print_I167:
;st7735.c,621 :: 		ch[1] = (((value % 100) / 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 255
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 100
	LDI        R21, 0
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	LDI        R20, 10
	LDI        R21, 0
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,622 :: 		ch[2] = ((value % 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 254
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 10
	LDI        R21, 0
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,623 :: 		ch[3] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 3
	LDI        R27, 32
	ST         Z, R27
;st7735.c,624 :: 		ch[4] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 4
	LDI        R27, 32
	ST         Z, R27
;st7735.c,625 :: 		ch[5] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 5
	LDI        R27, 32
	ST         Z, R27
;st7735.c,626 :: 		}
	JMP        L_print_I113
;st7735.c,619 :: 		else if((value > 9) && (value <= 99))
L__print_I175:
L__print_I174:
;st7735.c,629 :: 		ch[1] = ((value % 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 255
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 10
	LDI        R21, 0
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,630 :: 		ch[2] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 2
	LDI        R27, 32
	ST         Z, R27
;st7735.c,631 :: 		ch[3] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 3
	LDI        R27, 32
	ST         Z, R27
;st7735.c,632 :: 		ch[4] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 4
	LDI        R27, 32
	ST         Z, R27
;st7735.c,633 :: 		ch[5] = 0x20;
	MOVW       R16, R28
	MOVW       R30, R16
	ADIW       R30, 5
	LDI        R27, 32
	ST         Z, R27
;st7735.c,634 :: 		}
L_print_I113:
L_print_I109:
L_print_I105:
L_print_I101:
;st7735.c,636 :: 		print_str(x_pos, y_pos, font_size, colour, back_colour, ch);
	MOVW       R16, R28
	PUSH       R17
	PUSH       R16
	CALL       _print_str+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,637 :: 		}
L_end_print_I:
	ADIW       R28, 9
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _print_I

_print_D:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 10
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;st7735.c,640 :: 		void print_D(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, unsigned int value, unsigned char points)
	LDD        R16, Y+14
	LDD        R17, Y+15
	STD        Y+14, R16
	STD        Y+15, R17
;st7735.c,642 :: 		unsigned char ch[6] = {0x2E, 0x20, 0x20, 0x20, 0x20, 0x20};
	LDI        R27, 46
	STD        Y+0, R27
	LDI        R27, 32
	STD        Y+1, R27
	LDI        R27, 32
	STD        Y+2, R27
	LDI        R27, 32
	STD        Y+3, R27
	LDI        R27, 32
	STD        Y+4, R27
	LDI        R27, 32
	STD        Y+5, R27
;st7735.c,644 :: 		ch[1] = ((value / 1000) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 255
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 232
	LDI        R21, 3
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_U+0
	MOVW       R16, R24
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,646 :: 		if(points > 1)
	LDI        R16, 1
	CP         R16, R9
	BRLO       L__print_D266
	JMP        L_print_D114
L__print_D266:
;st7735.c,648 :: 		ch[2] = (((value % 1000) / 100) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 254
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 232
	LDI        R21, 3
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_U+0
	MOVW       R16, R26
	LDI        R20, 100
	LDI        R21, 0
	CALL       _Div_16x16_U+0
	MOVW       R16, R24
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,650 :: 		if(points > 2)
	LDI        R16, 2
	CP         R16, R9
	BRLO       L__print_D267
	JMP        L_print_D115
L__print_D267:
;st7735.c,652 :: 		ch[3] = (((value % 100) / 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 253
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 100
	LDI        R21, 0
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_U+0
	MOVW       R16, R26
	LDI        R20, 10
	LDI        R21, 0
	CALL       _Div_16x16_U+0
	MOVW       R16, R24
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,654 :: 		if(points > 3)
	LDI        R16, 3
	CP         R16, R9
	BRLO       L__print_D268
	JMP        L_print_D116
L__print_D268:
;st7735.c,656 :: 		ch[4] = ((value % 10) + 0x30);
	MOVW       R16, R28
	SUBI       R16, 252
	SBCI       R17, 255
	STD        Y+8, R16
	STD        Y+9, R17
	LDI        R20, 10
	LDI        R21, 0
	LDD        R16, Y+14
	LDD        R17, Y+15
	CALL       _Div_16x16_U+0
	MOVW       R16, R26
	MOV        R18, R16
	SUBI       R18, 208
	LDD        R16, Y+8
	LDD        R17, Y+9
	MOVW       R30, R16
	ST         Z, R18
;st7735.c,657 :: 		}
L_print_D116:
;st7735.c,658 :: 		}
L_print_D115:
;st7735.c,659 :: 		}
L_print_D114:
;st7735.c,661 :: 		print_str(x_pos, y_pos, font_size, colour, back_colour, ch);
	MOVW       R16, R28
	PUSH       R17
	PUSH       R16
	CALL       _print_str+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,662 :: 		}
L_end_print_D:
	ADIW       R28, 9
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _print_D

_print_F:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 8
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;st7735.c,665 :: 		void print_F(unsigned char x_pos, unsigned char y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, float value, unsigned char points)
	PUSH       R2
	PUSH       R9
	LDD        R16, Y+12
	LDD        R17, Y+13
	LDD        R18, Y+14
	LDD        R19, Y+15
	STD        Y+12, R16
	STD        Y+13, R17
	STD        Y+14, R18
	STD        Y+15, R19
;st7735.c,667 :: 		signed long tmp = 0x0000;
;st7735.c,669 :: 		tmp = value;
	LDD        R16, Y+12
	LDD        R17, Y+13
	LDD        R18, Y+14
	LDD        R19, Y+15
	CALL       _float_fpint+0
	STD        Y+0, R16
	STD        Y+1, R17
	STD        Y+2, R18
	STD        Y+3, R19
;st7735.c,670 :: 		print_I(x_pos, y_pos, font_size, colour, back_colour, tmp);
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	PUSH       R17
	PUSH       R16
	CALL       _print_I+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
;st7735.c,671 :: 		tmp = ((value - tmp) * 10000);
	LDD        R16, Y+0
	LDD        R17, Y+1
	LDD        R18, Y+2
	LDD        R19, Y+3
	CALL       _float_slong2fp+0
	STD        Y+4, R16
	STD        Y+5, R17
	STD        Y+6, R18
	STD        Y+7, R19
	PUSH       R3
	PUSH       R2
	LDD        R20, Y+4
	LDD        R21, Y+5
	LDD        R22, Y+6
	LDD        R23, Y+7
	LDD        R16, Y+12
	LDD        R17, Y+13
	LDD        R18, Y+14
	LDD        R19, Y+15
	CALL       _float_fpsub1+0
	LDI        R20, 0
	LDI        R21, 64
	LDI        R22, 28
	LDI        R23, 70
	CALL       _float_fpmul1+0
	POP        R2
	POP        R3
	POP        R7
	POP        R8
	POP        R9
	CALL       _float_fpint+0
	STD        Y+0, R16
	STD        Y+1, R17
	STD        Y+2, R18
	STD        Y+3, R19
;st7735.c,673 :: 		if(tmp < 0)
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 0
	LDI        R23, 0
	CP         R16, R20
	CPC        R17, R21
	CPC        R18, R22
	CPC        R19, R23
	BRLT       L__print_F270
	JMP        L_print_F117
L__print_F270:
;st7735.c,675 :: 		tmp = -tmp;
	LDD        R0, Y+0
	LDD        R1, Y+1
	LDI        R16, 0
	LDI        R17, 0
	SUB        R16, R0
	SBC        R17, R1
	LDD        R0, Y+2
	LDD        R1, Y+3
	LDI        R18, 0
	LDI        R19, 0
	SBC        R18, R0
	SBC        R19, R1
	STD        Y+0, R16
	STD        Y+1, R17
	STD        Y+2, R18
	STD        Y+3, R19
;st7735.c,676 :: 		}
L_print_F117:
;st7735.c,678 :: 		if((value >= 9999) && (value < 99999))
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 60
	LDI        R22, 28
	LDI        R23, 70
	LDD        R16, Y+12
	LDD        R17, Y+13
	LDD        R18, Y+14
	LDD        R19, Y+15
	CALL       _float_op_gequ+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_F271
	LDI        R16, 1
L__print_F271:
	POP        R2
	POP        R3
	POP        R7
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_F272
	JMP        L__print_F181
L__print_F272:
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R3
	PUSH       R2
	LDI        R20, 128
	LDI        R21, 79
	LDI        R22, 195
	LDI        R23, 71
	LDD        R16, Y+12
	LDD        R17, Y+13
	LDD        R18, Y+14
	LDD        R19, Y+15
	CALL       _float_op_less+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_F273
	LDI        R16, 1
L__print_F273:
	POP        R2
	POP        R3
	POP        R7
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_F274
	JMP        L__print_F180
L__print_F274:
L__print_F179:
;st7735.c,680 :: 		print_D((x_pos + (0x24 * font_size)), y_pos, font_size, colour, back_colour, tmp, points);
	LDI        R16, 36
	MUL        R16, R4
	MOV        R16, R0
	ADD        R16, R2
	MOV        R2, R16
	LDD        R16, Y+0
	LDD        R17, Y+1
	PUSH       R17
	PUSH       R16
	CALL       _print_D+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,681 :: 		}
	JMP        L_print_F121
;st7735.c,678 :: 		if((value >= 9999) && (value < 99999))
L__print_F181:
L__print_F180:
;st7735.c,682 :: 		else if((value >= 999) && (value < 9999))
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 192
	LDI        R22, 121
	LDI        R23, 68
	LDD        R16, Y+12
	LDD        R17, Y+13
	LDD        R18, Y+14
	LDD        R19, Y+15
	CALL       _float_op_gequ+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_F275
	LDI        R16, 1
L__print_F275:
	POP        R2
	POP        R3
	POP        R7
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_F276
	JMP        L__print_F183
L__print_F276:
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 60
	LDI        R22, 28
	LDI        R23, 70
	LDD        R16, Y+12
	LDD        R17, Y+13
	LDD        R18, Y+14
	LDD        R19, Y+15
	CALL       _float_op_less+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_F277
	LDI        R16, 1
L__print_F277:
	POP        R2
	POP        R3
	POP        R7
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_F278
	JMP        L__print_F182
L__print_F278:
L__print_F178:
;st7735.c,684 :: 		print_D((x_pos + (0x1E * font_size)), y_pos, font_size, colour, back_colour, tmp, points);
	LDI        R16, 30
	MUL        R16, R4
	MOV        R16, R0
	ADD        R16, R2
	MOV        R2, R16
	LDD        R16, Y+0
	LDD        R17, Y+1
	PUSH       R17
	PUSH       R16
	CALL       _print_D+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,685 :: 		}
	JMP        L_print_F125
;st7735.c,682 :: 		else if((value >= 999) && (value < 9999))
L__print_F183:
L__print_F182:
;st7735.c,686 :: 		else if((value >= 99) && (value < 999))
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 198
	LDI        R23, 66
	LDD        R16, Y+12
	LDD        R17, Y+13
	LDD        R18, Y+14
	LDD        R19, Y+15
	CALL       _float_op_gequ+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_F279
	LDI        R16, 1
L__print_F279:
	POP        R2
	POP        R3
	POP        R7
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_F280
	JMP        L__print_F185
L__print_F280:
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 192
	LDI        R22, 121
	LDI        R23, 68
	LDD        R16, Y+12
	LDD        R17, Y+13
	LDD        R18, Y+14
	LDD        R19, Y+15
	CALL       _float_op_less+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_F281
	LDI        R16, 1
L__print_F281:
	POP        R2
	POP        R3
	POP        R7
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_F282
	JMP        L__print_F184
L__print_F282:
L__print_F177:
;st7735.c,688 :: 		print_D((x_pos + (0x18 * font_size)), y_pos, font_size, colour, back_colour, tmp, points);
	LDI        R16, 24
	MUL        R16, R4
	MOV        R16, R0
	ADD        R16, R2
	MOV        R2, R16
	LDD        R16, Y+0
	LDD        R17, Y+1
	PUSH       R17
	PUSH       R16
	CALL       _print_D+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,689 :: 		}
	JMP        L_print_F129
;st7735.c,686 :: 		else if((value >= 99) && (value < 999))
L__print_F185:
L__print_F184:
;st7735.c,690 :: 		else if((value >= 9) && (value < 99))
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 16
	LDI        R23, 65
	LDD        R16, Y+12
	LDD        R17, Y+13
	LDD        R18, Y+14
	LDD        R19, Y+15
	CALL       _float_op_gequ+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_F283
	LDI        R16, 1
L__print_F283:
	POP        R2
	POP        R3
	POP        R7
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_F284
	JMP        L__print_F187
L__print_F284:
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 198
	LDI        R23, 66
	LDD        R16, Y+12
	LDD        R17, Y+13
	LDD        R18, Y+14
	LDD        R19, Y+15
	CALL       _float_op_less+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_F285
	LDI        R16, 1
L__print_F285:
	POP        R2
	POP        R3
	POP        R7
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_F286
	JMP        L__print_F186
L__print_F286:
L__print_F176:
;st7735.c,692 :: 		print_D((x_pos + (0x12 * font_size)), y_pos, font_size, colour, back_colour, tmp, points);
	LDI        R16, 18
	MUL        R16, R4
	MOV        R16, R0
	ADD        R16, R2
	MOV        R2, R16
	LDD        R16, Y+0
	LDD        R17, Y+1
	PUSH       R17
	PUSH       R16
	CALL       _print_D+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;st7735.c,693 :: 		}
	JMP        L_print_F133
;st7735.c,690 :: 		else if((value >= 9) && (value < 99))
L__print_F187:
L__print_F186:
;st7735.c,694 :: 		else if(value < 9)
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 16
	LDI        R23, 65
	LDD        R16, Y+12
	LDD        R17, Y+13
	LDD        R18, Y+14
	LDD        R19, Y+15
	CALL       _float_op_less+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_F287
	LDI        R16, 1
L__print_F287:
	POP        R2
	POP        R3
	POP        R7
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_F288
	JMP        L_print_F134
L__print_F288:
;st7735.c,696 :: 		print_D((x_pos + (0x0C * font_size)), y_pos, font_size, colour, back_colour, tmp, points);
	LDI        R16, 12
	MUL        R16, R4
	MOV        R16, R0
	ADD        R16, R2
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	LDD        R16, Y+0
	LDD        R17, Y+1
	PUSH       R17
	PUSH       R16
	CALL       _print_D+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
;st7735.c,698 :: 		if((value) < 0)
	PUSH       R8
	PUSH       R7
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 0
	LDI        R23, 0
	LDD        R16, Y+12
	LDD        R17, Y+13
	LDD        R18, Y+14
	LDD        R19, Y+15
	CALL       _float_op_less+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_F289
	LDI        R16, 1
L__print_F289:
	POP        R2
	POP        R3
	POP        R7
	POP        R8
	TST        R16
	BRNE       L__print_F290
	JMP        L_print_F135
L__print_F290:
;st7735.c,700 :: 		print_char(x_pos, y_pos, font_size, colour, back_colour, 0x2D);
	LDI        R27, 45
	MOV        R9, R27
	CALL       _print_char+0
;st7735.c,701 :: 		}
	JMP        L_print_F136
L_print_F135:
;st7735.c,704 :: 		print_char(x_pos, y_pos, font_size, colour, back_colour, 0x20);
	LDI        R27, 32
	MOV        R9, R27
	CALL       _print_char+0
;st7735.c,705 :: 		}
L_print_F136:
;st7735.c,706 :: 		}
L_print_F134:
L_print_F133:
L_print_F129:
L_print_F125:
L_print_F121:
;st7735.c,707 :: 		}
L_end_print_F:
	POP        R9
	POP        R2
	ADIW       R28, 7
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _print_F

_main:
	LDI        R27, 255
	OUT        SPL+0, R27
	LDI        R27, 0
	OUT        SPL+1, R27
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 40
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;TFT_display_demo.c,7 :: 		void main()
;TFT_display_demo.c,9 :: 		float f = -0.09;
	PUSH       R2
	PUSH       R3
	PUSH       R4
	PUSH       R5
	PUSH       R6
	PUSH       R7
	PUSH       R8
	PUSH       R9
	LDI        R27, 236
	STD        Y+33, R27
	LDI        R27, 81
	STD        Y+34, R27
	LDI        R27, 184
	STD        Y+35, R27
	LDI        R27, 189
	STD        Y+36, R27
	LDI        R27, 247
	STD        Y+37, R27
	LDI        R27, 255
	STD        Y+38, R27
	LDI        R27, 127
	STD        Y+39, R27
;TFT_display_demo.c,10 :: 		signed int i = -9;
;TFT_display_demo.c,11 :: 		signed char c = 127;
;TFT_display_demo.c,13 :: 		setup();
	CALL       _setup+0
;TFT_display_demo.c,15 :: 		Set_Rotation(0x01);
	LDI        R27, 1
	MOV        R2, R27
	CALL       _Set_Rotation+0
;TFT_display_demo.c,17 :: 		TFT_fill(Swap_Colour(GREEN));
	LDI        R27, 224
	MOV        R2, R27
	LDI        R27, 7
	MOV        R3, R27
	CALL       _Swap_Colour+0
	MOVW       R2, R16
	CALL       _TFT_fill+0
;TFT_display_demo.c,18 :: 		Draw_Circle(79, 63, 20, YES, Swap_Colour(RED));
	LDI        R27, 0
	MOV        R2, R27
	LDI        R27, 248
	MOV        R3, R27
	CALL       _Swap_Colour+0
	LDI        R27, 1
	MOV        R8, R27
	LDI        R27, 20
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 63
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 79
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	PUSH       R17
	PUSH       R16
	CALL       _Draw_Circle+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;TFT_display_demo.c,19 :: 		delay_ms(4000);
	LDI        R19, 2
	LDI        R18, 69
	LDI        R17, 173
	LDI        R16, 7
L_main137:
	DEC        R16
	BRNE       L_main137
	DEC        R17
	BRNE       L_main137
	DEC        R18
	BRNE       L_main137
	DEC        R19
	BRNE       L_main137
;TFT_display_demo.c,21 :: 		TFT_fill(Swap_Colour(WHITE));
	LDI        R27, 255
	MOV        R2, R27
	MOV        R3, R27
	CALL       _Swap_Colour+0
	MOVW       R2, R16
	CALL       _TFT_fill+0
;TFT_display_demo.c,23 :: 		Draw_Circle(6, 6, 4, YES, RED);
	LDI        R27, 1
	MOV        R8, R27
	LDI        R27, 4
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 6
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 6
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	LDI        R27, 248
	PUSH       R27
	LDI        R27, 0
	PUSH       R27
	CALL       _Draw_Circle+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;TFT_display_demo.c,24 :: 		Draw_Circle(153, 6, 4, YES, RED);
	LDI        R27, 1
	MOV        R8, R27
	LDI        R27, 4
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 6
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 153
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	LDI        R27, 248
	PUSH       R27
	LDI        R27, 0
	PUSH       R27
	CALL       _Draw_Circle+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;TFT_display_demo.c,25 :: 		Draw_Circle(6, 121, 4, YES, RED);
	LDI        R27, 1
	MOV        R8, R27
	LDI        R27, 4
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 121
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 6
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	LDI        R27, 248
	PUSH       R27
	LDI        R27, 0
	PUSH       R27
	CALL       _Draw_Circle+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;TFT_display_demo.c,26 :: 		Draw_Circle(153, 121, 4, YES, RED);
	LDI        R27, 1
	MOV        R8, R27
	LDI        R27, 4
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 121
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 153
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	LDI        R27, 248
	PUSH       R27
	LDI        R27, 0
	PUSH       R27
	CALL       _Draw_Circle+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;TFT_display_demo.c,28 :: 		delay_ms(1000);
	LDI        R18, 82
	LDI        R17, 43
	LDI        R16, 0
L_main139:
	DEC        R16
	BRNE       L_main139
	DEC        R17
	BRNE       L_main139
	DEC        R18
	BRNE       L_main139
	NOP
	NOP
	NOP
	NOP
;TFT_display_demo.c,30 :: 		Draw_Line(14, 0, 14, 127, CYAN);
	LDI        R27, 127
	MOV        R8, R27
	LDI        R27, 0
	MOV        R9, R27
	LDI        R27, 14
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	CLR        R4
	CLR        R5
	LDI        R27, 14
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	LDI        R27, 7
	PUSH       R27
	LDI        R27, 255
	PUSH       R27
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;TFT_display_demo.c,31 :: 		Draw_Line(145, 0, 145, 127, CYAN);
	LDI        R27, 127
	MOV        R8, R27
	LDI        R27, 0
	MOV        R9, R27
	LDI        R27, 145
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	CLR        R4
	CLR        R5
	LDI        R27, 145
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	LDI        R27, 7
	PUSH       R27
	LDI        R27, 255
	PUSH       R27
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;TFT_display_demo.c,32 :: 		Draw_Line(0, 14, 159, 14, CYAN);
	LDI        R27, 14
	MOV        R8, R27
	LDI        R27, 0
	MOV        R9, R27
	LDI        R27, 159
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 14
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	CLR        R2
	CLR        R3
	LDI        R27, 7
	PUSH       R27
	LDI        R27, 255
	PUSH       R27
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;TFT_display_demo.c,33 :: 		Draw_Line(0, 113, 159, 113, CYAN);
	LDI        R27, 113
	MOV        R8, R27
	LDI        R27, 0
	MOV        R9, R27
	LDI        R27, 159
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 113
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	CLR        R2
	CLR        R3
	LDI        R27, 7
	PUSH       R27
	LDI        R27, 255
	PUSH       R27
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;TFT_display_demo.c,35 :: 		delay_ms(1000);
	LDI        R18, 82
	LDI        R17, 43
	LDI        R16, 0
L_main141:
	DEC        R16
	BRNE       L_main141
	DEC        R17
	BRNE       L_main141
	DEC        R18
	BRNE       L_main141
	NOP
	NOP
	NOP
	NOP
;TFT_display_demo.c,37 :: 		Draw_Rectangle(17, 17, 142, 110, YES, ROUND, BLUE, WHITE);
	LDI        R27, 110
	MOV        R8, R27
	LDI        R27, 0
	MOV        R9, R27
	LDI        R27, 142
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 17
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 17
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	LDI        R27, 255
	PUSH       R27
	PUSH       R27
	LDI        R27, 0
	PUSH       R27
	LDI        R27, 31
	PUSH       R27
	LDI        R27, 1
	PUSH       R27
	LDI        R27, 1
	PUSH       R27
	CALL       _Draw_Rectangle+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 6
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;TFT_display_demo.c,38 :: 		delay_ms(1000);
	LDI        R18, 82
	LDI        R17, 43
	LDI        R16, 0
L_main143:
	DEC        R16
	BRNE       L_main143
	DEC        R17
	BRNE       L_main143
	DEC        R18
	BRNE       L_main143
	NOP
	NOP
	NOP
	NOP
;TFT_display_demo.c,40 :: 		print_str(22, 58, 2, YELLOW, BLUE, "MicroArena");
	LDI        R30, #lo_addr(?ICS?lstr1_TFT_display_demo+0)
	LDI        R31, hi_addr(?ICS?lstr1_TFT_display_demo+0)
	MOVW       R26, R28
	LDI        R24, 11
	LDI        R25, 0
	CALL       ___CC2DW+0
	MOVW       R16, R28
	LDI        R27, 31
	MOV        R7, R27
	LDI        R27, 0
	MOV        R8, R27
	LDI        R27, 224
	MOV        R5, R27
	LDI        R27, 255
	MOV        R6, R27
	LDI        R27, 2
	MOV        R4, R27
	LDI        R27, 58
	MOV        R3, R27
	LDI        R27, 22
	MOV        R2, R27
	PUSH       R17
	PUSH       R16
	CALL       _print_str+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;TFT_display_demo.c,41 :: 		delay_ms(4000);
	LDI        R19, 2
	LDI        R18, 69
	LDI        R17, 173
	LDI        R16, 7
L_main145:
	DEC        R16
	BRNE       L_main145
	DEC        R17
	BRNE       L_main145
	DEC        R18
	BRNE       L_main145
	DEC        R19
	BRNE       L_main145
;TFT_display_demo.c,43 :: 		TFT_fill(BLACK);
	CLR        R2
	CLR        R3
	CALL       _TFT_fill+0
;TFT_display_demo.c,44 :: 		print_str(20, 90, 1, YELLOW, BLACK, "www.fb.com/MicroArena");
	LDI        R30, #lo_addr(?ICS?lstr2_TFT_display_demo+0)
	LDI        R31, hi_addr(?ICS?lstr2_TFT_display_demo+0)
	MOVW       R26, R28
	ADIW       R26, 11
	LDI        R24, 22
	LDI        R25, 0
	CALL       ___CC2DW+0
	MOVW       R16, R28
	SUBI       R16, 245
	SBCI       R17, 255
	CLR        R7
	CLR        R8
	LDI        R27, 224
	MOV        R5, R27
	LDI        R27, 255
	MOV        R6, R27
	LDI        R27, 1
	MOV        R4, R27
	LDI        R27, 90
	MOV        R3, R27
	LDI        R27, 20
	MOV        R2, R27
	PUSH       R17
	PUSH       R16
	CALL       _print_str+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;TFT_display_demo.c,46 :: 		while(1)
L_main147:
;TFT_display_demo.c,48 :: 		print_F(60, 20, 1, BLUE, BLACK, f, 2);
	LDI        R27, 2
	MOV        R9, R27
	CLR        R7
	CLR        R8
	LDI        R27, 31
	MOV        R5, R27
	LDI        R27, 0
	MOV        R6, R27
	LDI        R27, 1
	MOV        R4, R27
	LDI        R27, 20
	MOV        R3, R27
	LDI        R27, 60
	MOV        R2, R27
	LDD        R16, Y+33
	LDD        R17, Y+34
	LDD        R18, Y+35
	LDD        R19, Y+36
	PUSH       R19
	PUSH       R18
	PUSH       R17
	PUSH       R16
	CALL       _print_F+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;TFT_display_demo.c,49 :: 		print_C(60, 40, 1, RED, BLACK, c);
	CLR        R7
	CLR        R8
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 248
	MOV        R6, R27
	LDI        R27, 1
	MOV        R4, R27
	LDI        R27, 40
	MOV        R3, R27
	LDI        R27, 60
	MOV        R2, R27
	LDD        R16, Y+39
	LDI        R27, 0
	SBRC       R16, 7
	LDI        R27, 255
	PUSH       R27
	PUSH       R16
	CALL       _print_C+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;TFT_display_demo.c,50 :: 		print_I(60, 60, 1, GREEN, BLACK, i);
	CLR        R7
	CLR        R8
	LDI        R27, 224
	MOV        R5, R27
	LDI        R27, 7
	MOV        R6, R27
	LDI        R27, 1
	MOV        R4, R27
	LDI        R27, 60
	MOV        R3, R27
	LDI        R27, 60
	MOV        R2, R27
	LDD        R16, Y+37
	LDD        R17, Y+38
	PUSH       R17
	PUSH       R16
	CALL       _print_I+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;TFT_display_demo.c,51 :: 		f += 0.01;
	LDD        R16, Y+33
	LDD        R17, Y+34
	LDD        R18, Y+35
	LDD        R19, Y+36
	LDI        R20, 10
	LDI        R21, 215
	LDI        R22, 35
	LDI        R23, 60
	CALL       _float_fpadd1+0
	STD        Y+33, R16
	STD        Y+34, R17
	STD        Y+35, R18
	STD        Y+36, R19
;TFT_display_demo.c,52 :: 		c -= 1;
	LDD        R18, Y+39
	SUBI       R18, 1
	STD        Y+39, R18
;TFT_display_demo.c,53 :: 		i += 1;
	LDD        R16, Y+37
	LDD        R17, Y+38
	SUBI       R16, 255
	SBCI       R17, 255
	STD        Y+37, R16
	STD        Y+38, R17
;TFT_display_demo.c,54 :: 		if(c < -128)
	CPI        R18, 128
	BRLT       L__main292
	JMP        L_main149
L__main292:
;TFT_display_demo.c,56 :: 		c = 127;
	LDI        R27, 127
	STD        Y+39, R27
;TFT_display_demo.c,57 :: 		}
L_main149:
;TFT_display_demo.c,58 :: 		delay_ms(60);
	LDI        R18, 5
	LDI        R17, 223
	LDI        R16, 188
L_main150:
	DEC        R16
	BRNE       L_main150
	DEC        R17
	BRNE       L_main150
	DEC        R18
	BRNE       L_main150
	NOP
	NOP
;TFT_display_demo.c,59 :: 		};
	JMP        L_main147
;TFT_display_demo.c,60 :: 		}
L_end_main:
	POP        R9
	POP        R8
	POP        R7
	POP        R6
	POP        R5
	POP        R4
	POP        R3
	POP        R2
L__main_end_loop:
	JMP        L__main_end_loop
; end of _main

_setup:

;TFT_display_demo.c,63 :: 		void setup()
;TFT_display_demo.c,65 :: 		CLKPR = 0x80;
	LDI        R27, 128
	STS        CLKPR+0, R27
;TFT_display_demo.c,66 :: 		CLKPR = 0x00;
	LDI        R27, 0
	STS        CLKPR+0, R27
;TFT_display_demo.c,67 :: 		PORTB = 0x00;
	LDI        R27, 0
	OUT        PORTB+0, R27
;TFT_display_demo.c,68 :: 		DDRB = 0x1F;
	LDI        R27, 31
	OUT        DDRB+0, R27
;TFT_display_demo.c,69 :: 		PORTC = 0x00;
	LDI        R27, 0
	OUT        PORTC+0, R27
;TFT_display_demo.c,70 :: 		DDRC = 0x00;
	LDI        R27, 0
	OUT        DDRC+0, R27
;TFT_display_demo.c,71 :: 		PORTD = 0x00;
	LDI        R27, 0
	OUT        PORTD+0, R27
;TFT_display_demo.c,72 :: 		DDRD = 0x00;
	LDI        R27, 0
	OUT        DDRD+0, R27
;TFT_display_demo.c,73 :: 		TCCR0A = 0x00;
	LDI        R27, 0
	OUT        TCCR0A+0, R27
;TFT_display_demo.c,74 :: 		TCCR0B = 0x00;
	LDI        R27, 0
	OUT        TCCR0B+0, R27
;TFT_display_demo.c,75 :: 		TCNT0 = 0x00;
	LDI        R27, 0
	OUT        TCNT0+0, R27
;TFT_display_demo.c,76 :: 		OCR0A = 0x00;
	LDI        R27, 0
	OUT        OCR0A+0, R27
;TFT_display_demo.c,77 :: 		OCR0B = 0x00;
	LDI        R27, 0
	OUT        OCR0B+0, R27
;TFT_display_demo.c,78 :: 		TCCR1A = 0x00;
	LDI        R27, 0
	STS        TCCR1A+0, R27
;TFT_display_demo.c,79 :: 		TCCR1B = 0x00;
	LDI        R27, 0
	STS        TCCR1B+0, R27
;TFT_display_demo.c,80 :: 		TCNT1H = 0x00;
	LDI        R27, 0
	STS        TCNT1H+0, R27
;TFT_display_demo.c,81 :: 		TCNT1L = 0x00;
	LDI        R27, 0
	STS        TCNT1L+0, R27
;TFT_display_demo.c,82 :: 		ICR1H = 0x00;
	LDI        R27, 0
	STS        ICR1H+0, R27
;TFT_display_demo.c,83 :: 		ICR1L = 0x00;
	LDI        R27, 0
	STS        ICR1L+0, R27
;TFT_display_demo.c,84 :: 		OCR1AH = 0x00;
	LDI        R27, 0
	STS        OCR1AH+0, R27
;TFT_display_demo.c,85 :: 		OCR1AL = 0x00;
	LDI        R27, 0
	STS        OCR1AL+0, R27
;TFT_display_demo.c,86 :: 		OCR1BH = 0x00;
	LDI        R27, 0
	STS        OCR1BH+0, R27
;TFT_display_demo.c,87 :: 		OCR1BL = 0x00;
	LDI        R27, 0
	STS        OCR1BL+0, R27
;TFT_display_demo.c,88 :: 		ASSR = 0x00;
	LDI        R27, 0
	STS        ASSR+0, R27
;TFT_display_demo.c,89 :: 		TCCR2A = 0x00;
	LDI        R27, 0
	STS        TCCR2A+0, R27
;TFT_display_demo.c,90 :: 		TCCR2B = 0x00;
	LDI        R27, 0
	STS        TCCR2B+0, R27
;TFT_display_demo.c,91 :: 		TCNT2 = 0x00;
	LDI        R27, 0
	STS        TCNT2+0, R27
;TFT_display_demo.c,92 :: 		OCR2A = 0x00;
	LDI        R27, 0
	STS        OCR2A+0, R27
;TFT_display_demo.c,93 :: 		OCR2B = 0x00;
	LDI        R27, 0
	STS        OCR2B+0, R27
;TFT_display_demo.c,94 :: 		EICRA = 0x00;
	LDI        R27, 0
	STS        EICRA+0, R27
;TFT_display_demo.c,95 :: 		EIMSK = 0x00;
	LDI        R27, 0
	OUT        EIMSK+0, R27
;TFT_display_demo.c,96 :: 		PCICR = 0x00;
	LDI        R27, 0
	STS        PCICR+0, R27
;TFT_display_demo.c,97 :: 		TIMSK0 = 0x00;
	LDI        R27, 0
	STS        TIMSK0+0, R27
;TFT_display_demo.c,98 :: 		TIMSK1 = 0x00;
	LDI        R27, 0
	STS        TIMSK1+0, R27
;TFT_display_demo.c,99 :: 		TIMSK2 = 0x00;
	LDI        R27, 0
	STS        TIMSK2+0, R27
;TFT_display_demo.c,100 :: 		UCSR0B = 0x00;
	LDI        R27, 0
	STS        UCSR0B+0, R27
;TFT_display_demo.c,101 :: 		ACSR = 0x80;
	LDI        R27, 128
	OUT        ACSR+0, R27
;TFT_display_demo.c,102 :: 		ADCSRB = 0x00;
	LDI        R27, 0
	STS        ADCSRB+0, R27
;TFT_display_demo.c,103 :: 		DIDR1 = 0x00;
	LDI        R27, 0
	STS        DIDR1+0, R27
;TFT_display_demo.c,104 :: 		ADCSRA = 0x00;
	LDI        R27, 0
	STS        ADCSRA+0, R27
;TFT_display_demo.c,105 :: 		SPCR = 0x00;
	LDI        R27, 0
	OUT        SPCR+0, R27
;TFT_display_demo.c,106 :: 		TWCR = 0x00;
	LDI        R27, 0
	STS        TWCR+0, R27
;TFT_display_demo.c,108 :: 		ST7735_init();
	CALL       _ST7735_init+0
;TFT_display_demo.c,109 :: 		}
L_end_setup:
	RET
; end of _setup
