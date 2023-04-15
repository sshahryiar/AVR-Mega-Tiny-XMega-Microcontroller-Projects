
_PCD8544_write:

;pcd8544.c,4 :: 		void PCD8544_write(unsigned char type, unsigned char value)
;pcd8544.c,6 :: 		unsigned char s = 0x08;
; s start address is: 17 (R17)
	LDI        R17, 8
;pcd8544.c,8 :: 		DC = type;
	BST        R2, 0
	IN         R27, PORTD4_bit+0
	BLD        R27, BitPos(PORTD4_bit+0)
	OUT        PORTD4_bit+0, R27
;pcd8544.c,9 :: 		CE = 0;
	IN         R27, PORTD5_bit+0
	CBR        R27, BitMask(PORTD5_bit+0)
	OUT        PORTD5_bit+0, R27
; s end address is: 17 (R17)
;pcd8544.c,11 :: 		while(s > 0)
L_PCD8544_write0:
; s start address is: 17 (R17)
	LDI        R16, 0
	CP         R16, R17
	BRLO       L__PCD8544_write214
	JMP        L_PCD8544_write1
L__PCD8544_write214:
;pcd8544.c,13 :: 		SCK = 0;
	IN         R27, PORTD2_bit+0
	CBR        R27, BitMask(PORTD2_bit+0)
	OUT        PORTD2_bit+0, R27
;pcd8544.c,15 :: 		if((value & 0x80) == 0)
	MOV        R16, R3
	ANDI       R16, 128
	CPI        R16, 0
	BREQ       L__PCD8544_write215
	JMP        L_PCD8544_write2
L__PCD8544_write215:
;pcd8544.c,17 :: 		SDO = 0;
	IN         R27, PORTD3_bit+0
	CBR        R27, BitMask(PORTD3_bit+0)
	OUT        PORTD3_bit+0, R27
;pcd8544.c,18 :: 		}
	JMP        L_PCD8544_write3
L_PCD8544_write2:
;pcd8544.c,21 :: 		SDO = 1;
	IN         R27, PORTD3_bit+0
	SBR        R27, BitMask(PORTD3_bit+0)
	OUT        PORTD3_bit+0, R27
;pcd8544.c,22 :: 		}
L_PCD8544_write3:
;pcd8544.c,24 :: 		value <<= 1;
	MOV        R16, R3
	LSL        R16
	MOV        R3, R16
;pcd8544.c,25 :: 		SCK = 1;
	IN         R27, PORTD2_bit+0
	SBR        R27, BitMask(PORTD2_bit+0)
	OUT        PORTD2_bit+0, R27
;pcd8544.c,26 :: 		s--;
	MOV        R16, R17
	SUBI       R16, 1
	MOV        R17, R16
;pcd8544.c,27 :: 		};
; s end address is: 17 (R17)
	JMP        L_PCD8544_write0
L_PCD8544_write1:
;pcd8544.c,29 :: 		CE = 1;
	IN         R27, PORTD5_bit+0
	SBR        R27, BitMask(PORTD5_bit+0)
	OUT        PORTD5_bit+0, R27
;pcd8544.c,30 :: 		}
L_end_PCD8544_write:
	RET
; end of _PCD8544_write

_PCD8544_reset:

;pcd8544.c,33 :: 		void PCD8544_reset()
;pcd8544.c,35 :: 		DC = 1;
	IN         R27, PORTD4_bit+0
	SBR        R27, BitMask(PORTD4_bit+0)
	OUT        PORTD4_bit+0, R27
;pcd8544.c,36 :: 		CE = 1;
	IN         R27, PORTD5_bit+0
	SBR        R27, BitMask(PORTD5_bit+0)
	OUT        PORTD5_bit+0, R27
;pcd8544.c,37 :: 		RST = 0;
	IN         R27, PORTD6_bit+0
	CBR        R27, BitMask(PORTD6_bit+0)
	OUT        PORTD6_bit+0, R27
;pcd8544.c,38 :: 		delay_ms(1);
	LDI        R17, 11
	LDI        R16, 99
L_PCD8544_reset4:
	DEC        R16
	BRNE       L_PCD8544_reset4
	DEC        R17
	BRNE       L_PCD8544_reset4
;pcd8544.c,39 :: 		RST = 1;
	IN         R27, PORTD6_bit+0
	SBR        R27, BitMask(PORTD6_bit+0)
	OUT        PORTD6_bit+0, R27
;pcd8544.c,40 :: 		}
L_end_PCD8544_reset:
	RET
; end of _PCD8544_reset

_PCD8544_init:

;pcd8544.c,43 :: 		void PCD8544_init()
;pcd8544.c,45 :: 		PCD8544_reset();
	PUSH       R2
	PUSH       R3
	CALL       _PCD8544_reset+0
;pcd8544.c,46 :: 		PCD8544_write(CMD, (PCD8544_extended_instruction | PCD8544_function_set));
	LDI        R27, 33
	MOV        R3, R27
	CLR        R2
	CALL       _PCD8544_write+0
;pcd8544.c,47 :: 		PCD8544_write(CMD, (PCD8544_set_bias | 0x04));
	LDI        R27, 20
	MOV        R3, R27
	CLR        R2
	CALL       _PCD8544_write+0
;pcd8544.c,48 :: 		PCD8544_set_contrast(0x38);
	LDI        R27, 56
	MOV        R2, R27
	CALL       _PCD8544_set_contrast+0
;pcd8544.c,49 :: 		PCD8544_write(CMD, PCD8544_set_temp);
	LDI        R27, 4
	MOV        R3, R27
	CLR        R2
	CALL       _PCD8544_write+0
;pcd8544.c,50 :: 		PCD8544_write(CMD, (PCD8544_display_normal | PCD8544_display_control));
	LDI        R27, 12
	MOV        R3, R27
	CLR        R2
	CALL       _PCD8544_write+0
;pcd8544.c,51 :: 		PCD8544_write(CMD, PCD8544_function_set);
	LDI        R27, 32
	MOV        R3, R27
	CLR        R2
	CALL       _PCD8544_write+0
;pcd8544.c,52 :: 		PCD8544_write(CMD, PCD8544_display_all_on);
	LDI        R27, 1
	MOV        R3, R27
	CLR        R2
	CALL       _PCD8544_write+0
;pcd8544.c,53 :: 		PCD8544_write(CMD, PCD8544_display_normal);
	LDI        R27, 4
	MOV        R3, R27
	CLR        R2
	CALL       _PCD8544_write+0
;pcd8544.c,54 :: 		delay_ms(10);
	LDI        R17, 104
	LDI        R16, 229
L_PCD8544_init6:
	DEC        R16
	BRNE       L_PCD8544_init6
	DEC        R17
	BRNE       L_PCD8544_init6
;pcd8544.c,55 :: 		PCD8544_clear_buffer(OFF);
	CLR        R2
	CALL       _PCD8544_clear_buffer+0
;pcd8544.c,56 :: 		}
L_end_PCD8544_init:
	POP        R3
	POP        R2
	RET
; end of _PCD8544_init

_PCD8544_backlight_state:

;pcd8544.c,59 :: 		void PCD8544_backlight_state(unsigned char value)
;pcd8544.c,61 :: 		BL = value;
	BST        R2, 0
	IN         R27, PORTD7_bit+0
	BLD        R27, BitPos(PORTD7_bit+0)
	OUT        PORTD7_bit+0, R27
;pcd8544.c,62 :: 		}
L_end_PCD8544_backlight_state:
	RET
; end of _PCD8544_backlight_state

_PCD8544_set_contrast:

;pcd8544.c,65 :: 		void PCD8544_set_contrast(unsigned char value)
;pcd8544.c,67 :: 		if(value >= 0x7F)
	PUSH       R2
	PUSH       R3
	LDI        R27, 127
	CP         R2, R27
	BRSH       L__PCD8544_set_contrast220
	JMP        L_PCD8544_set_contrast8
L__PCD8544_set_contrast220:
;pcd8544.c,69 :: 		value = 0x7F;
	LDI        R27, 127
	MOV        R2, R27
;pcd8544.c,70 :: 		}
L_PCD8544_set_contrast8:
;pcd8544.c,72 :: 		PCD8544_write(CMD, (PCD8544_extended_instruction | PCD8544_function_set));
	PUSH       R2
	LDI        R27, 33
	MOV        R3, R27
	CLR        R2
	CALL       _PCD8544_write+0
	POP        R2
;pcd8544.c,73 :: 		PCD8544_write(CMD, (PCD8544_set_VOP | value));
	MOV        R16, R2
	ORI        R16, 128
	MOV        R3, R16
	CLR        R2
	CALL       _PCD8544_write+0
;pcd8544.c,74 :: 		PCD8544_write(CMD, PCD8544_function_set);
	LDI        R27, 32
	MOV        R3, R27
	CLR        R2
	CALL       _PCD8544_write+0
;pcd8544.c,75 :: 		}
L_end_PCD8544_set_contrast:
	POP        R3
	POP        R2
	RET
; end of _PCD8544_set_contrast

_PCD8544_set_cursor:

;pcd8544.c,78 :: 		void PCD8544_set_cursor(unsigned char x_pos, unsigned char y_pos)
;pcd8544.c,80 :: 		PCD8544_write(CMD, (PCD8544_set_X_addr | x_pos));
	PUSH       R2
	PUSH       R3
	MOV        R16, R2
	ORI        R16, 128
	PUSH       R3
	MOV        R3, R16
	CLR        R2
	CALL       _PCD8544_write+0
	POP        R3
;pcd8544.c,81 :: 		PCD8544_write(CMD, (PCD8544_set_Y_addr | y_pos));
	MOV        R16, R3
	ORI        R16, 64
	MOV        R3, R16
	CLR        R2
	CALL       _PCD8544_write+0
;pcd8544.c,82 :: 		}
L_end_PCD8544_set_cursor:
	POP        R3
	POP        R2
	RET
; end of _PCD8544_set_cursor

_PCD8544_print_char:

;pcd8544.c,85 :: 		void PCD8544_print_char(unsigned char ch, unsigned char colour)
;pcd8544.c,87 :: 		unsigned char s = 0;
;pcd8544.c,88 :: 		unsigned char chr = 0;
;pcd8544.c,90 :: 		for(s = 0; s <= 4; s++)
; s start address is: 20 (R20)
	LDI        R20, 0
; s end address is: 20 (R20)
L_PCD8544_print_char9:
; s start address is: 20 (R20)
	LDI        R16, 4
	CP         R16, R20
	BRSH       L__PCD8544_print_char223
	JMP        L_PCD8544_print_char10
L__PCD8544_print_char223:
;pcd8544.c,92 :: 		chr = font[(ch - 0x20)][s];
	MOV        R16, R2
	LDI        R17, 0
	SUBI       R16, 32
	SBCI       R17, 0
	PUSH       R20
	LDI        R20, 5
	LDI        R21, 0
	CALL       _HWMul_16x16+0
	POP        R20
	LDI        R18, #lo_addr(nokia5510_lcd_demo_font+0)
	LDI        R19, hi_addr(nokia5510_lcd_demo_font+0)
	ADD        R16, R18
	ADC        R17, R19
	MOV        R30, R20
	LDI        R31, 0
	ADD        R30, R16
	ADC        R31, R17
	LPM        R16, Z
; chr start address is: 17 (R17)
	MOV        R17, R16
;pcd8544.c,93 :: 		if(colour == BLACK)
	LDI        R27, 0
	CP         R3, R27
	BREQ       L__PCD8544_print_char224
	JMP        L__PCD8544_print_char170
L__PCD8544_print_char224:
;pcd8544.c,95 :: 		chr = ~chr;
	MOV        R16, R17
	COM        R16
	MOV        R17, R16
; chr end address is: 17 (R17)
	MOV        R16, R17
;pcd8544.c,96 :: 		}
	JMP        L_PCD8544_print_char12
L__PCD8544_print_char170:
;pcd8544.c,93 :: 		if(colour == BLACK)
	MOV        R16, R17
;pcd8544.c,96 :: 		}
L_PCD8544_print_char12:
;pcd8544.c,97 :: 		PCD8544_write(DAT, chr);
; chr start address is: 16 (R16)
	PUSH       R3
; chr end address is: 16 (R16)
	PUSH       R2
	MOV        R3, R16
	LDI        R27, 1
	MOV        R2, R27
	CALL       _PCD8544_write+0
	POP        R2
	POP        R3
;pcd8544.c,90 :: 		for(s = 0; s <= 4; s++)
	MOV        R16, R20
	SUBI       R16, 255
	MOV        R20, R16
;pcd8544.c,98 :: 		}
; s end address is: 20 (R20)
	JMP        L_PCD8544_print_char9
L_PCD8544_print_char10:
;pcd8544.c,99 :: 		}
L_end_PCD8544_print_char:
	RET
; end of _PCD8544_print_char

_PCD8544_print_custom_char:

;pcd8544.c,102 :: 		void PCD8544_print_custom_char(unsigned char *map)
;pcd8544.c,104 :: 		unsigned char s = 0;
;pcd8544.c,106 :: 		for(s = 0; s <= 4; s++)
; s start address is: 18 (R18)
	LDI        R18, 0
; s end address is: 18 (R18)
L_PCD8544_print_custom_char13:
; s start address is: 18 (R18)
	LDI        R16, 4
	CP         R16, R18
	BRSH       L__PCD8544_print_custom_char226
	JMP        L_PCD8544_print_custom_char14
L__PCD8544_print_custom_char226:
;pcd8544.c,108 :: 		PCD8544_write(DAT, *map++);
	MOVW       R30, R2
	LD         R16, Z
	PUSH       R3
	PUSH       R2
	MOV        R3, R16
	LDI        R27, 1
	MOV        R2, R27
	CALL       _PCD8544_write+0
	POP        R2
	POP        R3
	MOVW       R16, R2
	SUBI       R16, 255
	SBCI       R17, 255
	MOVW       R2, R16
;pcd8544.c,106 :: 		for(s = 0; s <= 4; s++)
	MOV        R16, R18
	SUBI       R16, 255
	MOV        R18, R16
;pcd8544.c,109 :: 		}
; s end address is: 18 (R18)
	JMP        L_PCD8544_print_custom_char13
L_PCD8544_print_custom_char14:
;pcd8544.c,110 :: 		}
L_end_PCD8544_print_custom_char:
	RET
; end of _PCD8544_print_custom_char

_PCD8544_fill:

;pcd8544.c,113 :: 		void PCD8544_fill(unsigned char bufr)
;pcd8544.c,115 :: 		unsigned int s = 0;
	PUSH       R3
;pcd8544.c,117 :: 		PCD8544_set_cursor(0, 0);
	PUSH       R2
	CLR        R3
	CLR        R2
	CALL       _PCD8544_set_cursor+0
	POP        R2
;pcd8544.c,119 :: 		for(s = 0; s < buffer_size; s++)
; s start address is: 18 (R18)
	LDI        R18, 0
	LDI        R19, 0
; s end address is: 18 (R18)
L_PCD8544_fill16:
; s start address is: 18 (R18)
	CPI        R19, 1
	BRNE       L__PCD8544_fill228
	CPI        R18, 248
L__PCD8544_fill228:
	BRLO       L__PCD8544_fill229
	JMP        L_PCD8544_fill17
L__PCD8544_fill229:
;pcd8544.c,121 :: 		PCD8544_write(DAT, bufr);
	PUSH       R2
	MOV        R3, R2
	LDI        R27, 1
	MOV        R2, R27
	CALL       _PCD8544_write+0
	POP        R2
;pcd8544.c,119 :: 		for(s = 0; s < buffer_size; s++)
	MOVW       R16, R18
	SUBI       R16, 255
	SBCI       R17, 255
	MOVW       R18, R16
;pcd8544.c,122 :: 		}
; s end address is: 18 (R18)
	JMP        L_PCD8544_fill16
L_PCD8544_fill17:
;pcd8544.c,123 :: 		}
L_end_PCD8544_fill:
	POP        R3
	RET
; end of _PCD8544_fill

_PCD8544_clear_buffer:

;pcd8544.c,126 :: 		void PCD8544_clear_buffer(unsigned char colour)
;pcd8544.c,128 :: 		unsigned char x_pos = 0;
; x_pos start address is: 17 (R17)
	LDI        R17, 0
;pcd8544.c,129 :: 		unsigned char y_pos = 0;
; y_pos start address is: 16 (R16)
	LDI        R16, 0
; x_pos end address is: 17 (R17)
; y_pos end address is: 16 (R16)
	MOV        R20, R17
	MOV        R21, R16
;pcd8544.c,131 :: 		for(x_pos; x_pos < X_max; x_pos++)
L_PCD8544_clear_buffer19:
; y_pos start address is: 21 (R21)
; x_pos start address is: 20 (R20)
	CPI        R20, 84
	BRLO       L__PCD8544_clear_buffer231
	JMP        L_PCD8544_clear_buffer20
L__PCD8544_clear_buffer231:
; y_pos end address is: 21 (R21)
; x_pos end address is: 20 (R20)
;pcd8544.c,133 :: 		for(y_pos; y_pos < Rows; y_pos++)
L_PCD8544_clear_buffer22:
; x_pos start address is: 20 (R20)
; y_pos start address is: 21 (R21)
	CPI        R21, 6
	BRLO       L__PCD8544_clear_buffer232
	JMP        L_PCD8544_clear_buffer23
L__PCD8544_clear_buffer232:
;pcd8544.c,135 :: 		PCD8544_buffer[x_pos][y_pos] = colour;
	PUSH       R21
	PUSH       R20
	LDI        R16, 6
	LDI        R17, 0
	LDI        R21, 0
	CALL       _HWMul_16x16+0
	POP        R20
	POP        R21
	LDI        R18, #lo_addr(nokia5510_lcd_demo_PCD8544_buffer+0)
	LDI        R19, hi_addr(nokia5510_lcd_demo_PCD8544_buffer+0)
	ADD        R16, R18
	ADC        R17, R19
	MOV        R30, R21
	LDI        R31, 0
	ADD        R30, R16
	ADC        R31, R17
	ST         Z, R2
;pcd8544.c,133 :: 		for(y_pos; y_pos < Rows; y_pos++)
	MOV        R16, R21
	SUBI       R16, 255
	MOV        R21, R16
;pcd8544.c,136 :: 		}
	JMP        L_PCD8544_clear_buffer22
L_PCD8544_clear_buffer23:
;pcd8544.c,131 :: 		for(x_pos; x_pos < X_max; x_pos++)
	MOV        R16, R20
	SUBI       R16, 255
	MOV        R20, R16
;pcd8544.c,137 :: 		}
; y_pos end address is: 21 (R21)
; x_pos end address is: 20 (R20)
	JMP        L_PCD8544_clear_buffer19
L_PCD8544_clear_buffer20:
;pcd8544.c,138 :: 		}
L_end_PCD8544_clear_buffer:
	RET
; end of _PCD8544_clear_buffer

_PCD8544_clear_screen:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 2
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;pcd8544.c,141 :: 		void PCD8544_clear_screen(unsigned char colour)
;pcd8544.c,143 :: 		unsigned char x_pos = 0;
	PUSH       R3
	PUSH       R4
	PUSH       R5
	PUSH       R6
;pcd8544.c,144 :: 		unsigned char y_pos = 0;
;pcd8544.c,146 :: 		for(y_pos = 0; y_pos < Rows; y_pos++)
; y_pos start address is: 18 (R18)
	LDI        R18, 0
; y_pos end address is: 18 (R18)
L_PCD8544_clear_screen25:
; y_pos start address is: 18 (R18)
	CPI        R18, 6
	BRLO       L__PCD8544_clear_screen234
	JMP        L_PCD8544_clear_screen26
L__PCD8544_clear_screen234:
;pcd8544.c,148 :: 		for(x_pos = 0; x_pos < X_max; x_pos++)
; x_pos start address is: 19 (R19)
	LDI        R19, 0
; x_pos end address is: 19 (R19)
; y_pos end address is: 18 (R18)
L_PCD8544_clear_screen28:
; x_pos start address is: 19 (R19)
; y_pos start address is: 18 (R18)
	CPI        R19, 84
	BRLO       L__PCD8544_clear_screen235
	JMP        L_PCD8544_clear_screen29
L__PCD8544_clear_screen235:
;pcd8544.c,150 :: 		PCD8544_print_string(x_pos, y_pos, " ", colour);
	LDI        R27, 32
	STD        Y+0, R27
	LDI        R27, 0
	STD        Y+1, R27
	MOVW       R16, R28
	PUSH       R18
	PUSH       R19
	PUSH       R2
	MOV        R6, R2
	MOVW       R4, R16
	MOV        R3, R18
	MOV        R2, R19
	CALL       _PCD8544_print_string+0
	POP        R2
	POP        R19
	POP        R18
;pcd8544.c,148 :: 		for(x_pos = 0; x_pos < X_max; x_pos++)
	MOV        R16, R19
	SUBI       R16, 255
	MOV        R19, R16
;pcd8544.c,151 :: 		}
; x_pos end address is: 19 (R19)
	JMP        L_PCD8544_clear_screen28
L_PCD8544_clear_screen29:
;pcd8544.c,146 :: 		for(y_pos = 0; y_pos < Rows; y_pos++)
	MOV        R16, R18
	SUBI       R16, 255
	MOV        R18, R16
;pcd8544.c,152 :: 		}
; y_pos end address is: 18 (R18)
	JMP        L_PCD8544_clear_screen25
L_PCD8544_clear_screen26:
;pcd8544.c,153 :: 		}
L_end_PCD8544_clear_screen:
	POP        R6
	POP        R5
	POP        R4
	POP        R3
	ADIW       R28, 1
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _PCD8544_clear_screen

_PCD8544_print_image:

;pcd8544.c,156 :: 		void PCD8544_print_image(const unsigned char *bmp)
;pcd8544.c,158 :: 		unsigned int s = 0;
;pcd8544.c,160 :: 		PCD8544_set_cursor(0, 0);
	PUSH       R3
	PUSH       R2
	CLR        R3
	CLR        R2
	CALL       _PCD8544_set_cursor+0
	POP        R2
	POP        R3
;pcd8544.c,162 :: 		for(s = 0; s < buffer_size; s++)
; s start address is: 18 (R18)
	LDI        R18, 0
	LDI        R19, 0
; s end address is: 18 (R18)
L_PCD8544_print_image31:
; s start address is: 18 (R18)
	CPI        R19, 1
	BRNE       L__PCD8544_print_image237
	CPI        R18, 248
L__PCD8544_print_image237:
	BRLO       L__PCD8544_print_image238
	JMP        L_PCD8544_print_image32
L__PCD8544_print_image238:
;pcd8544.c,164 :: 		PCD8544_Write(DAT, bmp[s]);
	MOVW       R30, R18
	ADD        R30, R2
	ADC        R31, R3
	LPM        R16, Z
	PUSH       R3
	PUSH       R2
	MOV        R3, R16
	LDI        R27, 1
	MOV        R2, R27
	CALL       _PCD8544_write+0
	POP        R2
	POP        R3
;pcd8544.c,162 :: 		for(s = 0; s < buffer_size; s++)
	MOVW       R16, R18
	SUBI       R16, 255
	SBCI       R17, 255
	MOVW       R18, R16
;pcd8544.c,165 :: 		}
; s end address is: 18 (R18)
	JMP        L_PCD8544_print_image31
L_PCD8544_print_image32:
;pcd8544.c,166 :: 		}
L_end_PCD8544_print_image:
	RET
; end of _PCD8544_print_image

_PCD8544_print_string:

;pcd8544.c,169 :: 		void PCD8544_print_string(unsigned char x_pos, unsigned char y_pos, unsigned char *ch, unsigned char colour)
;pcd8544.c,171 :: 		PCD8544_set_cursor(x_pos, y_pos);
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,173 :: 		do
L_PCD8544_print_string34:
;pcd8544.c,175 :: 		PCD8544_print_char(*ch++, colour);
	MOVW       R30, R4
	LD         R16, Z
	PUSH       R3
	PUSH       R2
	MOV        R3, R6
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
	MOVW       R16, R4
	SUBI       R16, 255
	SBCI       R17, 255
	MOVW       R4, R16
;pcd8544.c,176 :: 		}while((*ch >= 0x20) && (*ch <= 0x7F));
	MOVW       R30, R16
	LD         R16, Z
	CPI        R16, 32
	BRSH       L__PCD8544_print_string240
	JMP        L__PCD8544_print_string173
L__PCD8544_print_string240:
	MOVW       R30, R4
	LD         R17, Z
	LDI        R16, 127
	CP         R16, R17
	BRSH       L__PCD8544_print_string241
	JMP        L__PCD8544_print_string172
L__PCD8544_print_string241:
	JMP        L_PCD8544_print_string34
L__PCD8544_print_string173:
L__PCD8544_print_string172:
;pcd8544.c,177 :: 		}
L_end_PCD8544_print_string:
	RET
; end of _PCD8544_print_string

_print_chr:

;pcd8544.c,180 :: 		void print_chr(unsigned char x_pos, unsigned char y_pos, signed int value, unsigned char colour)
;pcd8544.c,182 :: 		unsigned char ch = 0x00;
	PUSH       R2
	PUSH       R3
;pcd8544.c,184 :: 		if(value < 0)
	LDI        R16, 0
	LDI        R17, 0
	CP         R4, R16
	CPC        R5, R17
	BRLT       L__print_chr243
	JMP        L_print_chr39
L__print_chr243:
;pcd8544.c,186 :: 		PCD8544_set_cursor(x_pos, y_pos);
	PUSH       R3
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,187 :: 		PCD8544_print_char(0x2D, colour);
	PUSH       R2
	MOV        R3, R6
	LDI        R27, 45
	MOV        R2, R27
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,188 :: 		value = -value;
	LDI        R16, 0
	LDI        R17, 0
	SUB        R16, R4
	SBC        R17, R5
	MOVW       R4, R16
;pcd8544.c,189 :: 		}
	JMP        L_print_chr40
L_print_chr39:
;pcd8544.c,192 :: 		PCD8544_set_cursor(x_pos, y_pos);
	PUSH       R3
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,193 :: 		PCD8544_print_char(0x20, colour);
	PUSH       R2
	MOV        R3, R6
	LDI        R27, 32
	MOV        R2, R27
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,194 :: 		}
L_print_chr40:
;pcd8544.c,196 :: 		if((value > 99) && (value <= 999))
	LDI        R16, 99
	LDI        R17, 0
	CP         R16, R4
	CPC        R17, R5
	BRLT       L__print_chr244
	JMP        L__print_chr178
L__print_chr244:
	LDI        R16, 231
	LDI        R17, 3
	CP         R16, R4
	CPC        R17, R5
	BRGE       L__print_chr245
	JMP        L__print_chr177
L__print_chr245:
L__print_chr176:
;pcd8544.c,198 :: 		ch = (value / 100);
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 100
	LDI        R21, 0
	MOVW       R16, R4
	CALL       _Div_16x16_S+0
	MOVW       R16, R22
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
; ch start address is: 17 (R17)
	MOV        R17, R16
;pcd8544.c,199 :: 		PCD8544_set_cursor((x_pos + 6), y_pos);
	MOV        R16, R2
	SUBI       R16, 250
	PUSH       R17
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
	POP        R2
	POP        R3
	POP        R17
;pcd8544.c,200 :: 		PCD8544_print_char((48 + ch), colour);
	MOV        R16, R17
	SUBI       R16, 208
; ch end address is: 17 (R17)
	PUSH       R3
	PUSH       R2
	MOV        R3, R6
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,202 :: 		ch = ((value % 100) / 10);
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 100
	LDI        R21, 0
	MOVW       R16, R4
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
; ch start address is: 17 (R17)
	MOV        R17, R16
;pcd8544.c,203 :: 		PCD8544_set_cursor((x_pos + 12), y_pos);
	MOV        R16, R2
	SUBI       R16, 244
	PUSH       R17
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
	POP        R2
	POP        R3
	POP        R17
;pcd8544.c,204 :: 		PCD8544_print_char((48 + ch), colour);
	MOV        R16, R17
	SUBI       R16, 208
; ch end address is: 17 (R17)
	PUSH       R3
	PUSH       R2
	MOV        R3, R6
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,206 :: 		ch = (value % 10);
	PUSH       R6
	PUSH       R3
	PUSH       R2
	LDI        R20, 10
	LDI        R21, 0
	MOVW       R16, R4
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	POP        R2
	POP        R3
	POP        R6
; ch start address is: 17 (R17)
	MOV        R17, R16
;pcd8544.c,207 :: 		PCD8544_set_cursor((x_pos + 18), y_pos);
	MOV        R16, R2
	SUBI       R16, 238
	PUSH       R17
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
	POP        R17
;pcd8544.c,208 :: 		PCD8544_print_char((48 + ch), colour);
	MOV        R16, R17
	SUBI       R16, 208
; ch end address is: 17 (R17)
	MOV        R3, R6
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
;pcd8544.c,209 :: 		}
	JMP        L_print_chr44
;pcd8544.c,196 :: 		if((value > 99) && (value <= 999))
L__print_chr178:
L__print_chr177:
;pcd8544.c,210 :: 		else if((value > 9) && (value <= 99))
	LDI        R16, 9
	LDI        R17, 0
	CP         R16, R4
	CPC        R17, R5
	BRLT       L__print_chr246
	JMP        L__print_chr180
L__print_chr246:
	LDI        R16, 99
	LDI        R17, 0
	CP         R16, R4
	CPC        R17, R5
	BRGE       L__print_chr247
	JMP        L__print_chr179
L__print_chr247:
L__print_chr175:
;pcd8544.c,212 :: 		ch = ((value % 100) / 10);
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 100
	LDI        R21, 0
	MOVW       R16, R4
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
; ch start address is: 17 (R17)
	MOV        R17, R16
;pcd8544.c,213 :: 		PCD8544_set_cursor((x_pos + 6), y_pos);
	MOV        R16, R2
	SUBI       R16, 250
	PUSH       R17
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
	POP        R2
	POP        R3
	POP        R17
;pcd8544.c,214 :: 		PCD8544_print_char((48 + ch), colour);
	MOV        R16, R17
	SUBI       R16, 208
; ch end address is: 17 (R17)
	PUSH       R3
	PUSH       R2
	MOV        R3, R6
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,216 :: 		ch = (value % 10);
	PUSH       R6
	PUSH       R3
	PUSH       R2
	LDI        R20, 10
	LDI        R21, 0
	MOVW       R16, R4
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	POP        R2
	POP        R3
	POP        R6
; ch start address is: 17 (R17)
	MOV        R17, R16
;pcd8544.c,217 :: 		PCD8544_set_cursor((x_pos + 12), y_pos);
	MOV        R16, R2
	SUBI       R16, 244
	PUSH       R17
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
	POP        R2
	POP        R3
	POP        R17
;pcd8544.c,218 :: 		PCD8544_print_char((48 + ch), colour);
	MOV        R16, R17
	SUBI       R16, 208
; ch end address is: 17 (R17)
	PUSH       R3
	PUSH       R2
	MOV        R3, R6
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,220 :: 		PCD8544_set_cursor((x_pos + 18), y_pos);
	MOV        R16, R2
	SUBI       R16, 238
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,221 :: 		PCD8544_print_char(0x20, colour);
	MOV        R3, R6
	LDI        R27, 32
	MOV        R2, R27
	CALL       _PCD8544_print_char+0
;pcd8544.c,222 :: 		}
	JMP        L_print_chr48
;pcd8544.c,210 :: 		else if((value > 9) && (value <= 99))
L__print_chr180:
L__print_chr179:
;pcd8544.c,223 :: 		else if((value >= 0) && (value <= 9))
	LDI        R16, 0
	LDI        R17, 0
	CP         R4, R16
	CPC        R5, R17
	BRGE       L__print_chr248
	JMP        L__print_chr182
L__print_chr248:
	LDI        R16, 9
	LDI        R17, 0
	CP         R16, R4
	CPC        R17, R5
	BRGE       L__print_chr249
	JMP        L__print_chr181
L__print_chr249:
L__print_chr174:
;pcd8544.c,225 :: 		ch = (value % 10);
	PUSH       R6
	PUSH       R3
	PUSH       R2
	LDI        R20, 10
	LDI        R21, 0
	MOVW       R16, R4
	CALL       _Div_16x16_S+0
	MOVW       R16, R24
	POP        R2
	POP        R3
	POP        R6
; ch start address is: 17 (R17)
	MOV        R17, R16
;pcd8544.c,226 :: 		PCD8544_set_cursor((x_pos + 6), y_pos);
	MOV        R16, R2
	SUBI       R16, 250
	PUSH       R17
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
	POP        R2
	POP        R3
	POP        R17
;pcd8544.c,227 :: 		PCD8544_print_char((48 + ch), colour);
	MOV        R16, R17
	SUBI       R16, 208
; ch end address is: 17 (R17)
	PUSH       R3
	PUSH       R2
	MOV        R3, R6
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,229 :: 		PCD8544_set_cursor((x_pos + 12), y_pos);
	MOV        R16, R2
	SUBI       R16, 244
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,230 :: 		PCD8544_print_char(0x20, colour);
	MOV        R3, R6
	LDI        R27, 32
	MOV        R2, R27
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,232 :: 		PCD8544_set_cursor((x_pos + 18), y_pos);
	MOV        R16, R2
	SUBI       R16, 238
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,233 :: 		PCD8544_print_char(0x20, colour);
	MOV        R3, R6
	LDI        R27, 32
	MOV        R2, R27
	CALL       _PCD8544_print_char+0
;pcd8544.c,223 :: 		else if((value >= 0) && (value <= 9))
L__print_chr182:
L__print_chr181:
;pcd8544.c,234 :: 		}
L_print_chr48:
L_print_chr44:
;pcd8544.c,235 :: 		}
L_end_print_chr:
	POP        R3
	POP        R2
	RET
; end of _print_chr

_print_int:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 1
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;pcd8544.c,238 :: 		void print_int(unsigned char x_pos, unsigned char y_pos, signed long value, unsigned char colour)
;pcd8544.c,240 :: 		unsigned char ch = 0x00;
	PUSH       R2
	PUSH       R3
;pcd8544.c,242 :: 		if(value < 0)
	LDI        R16, 0
	LDI        R17, 0
	LDI        R18, 0
	LDI        R19, 0
	CP         R4, R16
	CPC        R5, R17
	CPC        R6, R18
	CPC        R7, R19
	BRLT       L__print_int251
	JMP        L_print_int52
L__print_int251:
;pcd8544.c,244 :: 		PCD8544_set_cursor(x_pos, y_pos);
	PUSH       R3
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,245 :: 		PCD8544_print_char(0x2D, colour);
	PUSH       R2
	MOV        R3, R8
	LDI        R27, 45
	MOV        R2, R27
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,246 :: 		value = -value;
	LDI        R16, 0
	LDI        R17, 0
	LDI        R18, 0
	LDI        R19, 0
	SUB        R16, R4
	SBC        R17, R5
	SBC        R18, R6
	SBC        R19, R7
	MOVW       R4, R16
	MOVW       R6, R18
;pcd8544.c,247 :: 		}
	JMP        L_print_int53
L_print_int52:
;pcd8544.c,250 :: 		PCD8544_set_cursor(x_pos, y_pos);
	PUSH       R3
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,251 :: 		PCD8544_print_char(0x20, colour);
	PUSH       R2
	MOV        R3, R8
	LDI        R27, 32
	MOV        R2, R27
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,252 :: 		}
L_print_int53:
;pcd8544.c,254 :: 		if(value > 9999)
	LDI        R16, 15
	LDI        R17, 39
	LDI        R18, 0
	LDI        R19, 0
	CP         R16, R4
	CPC        R17, R5
	CPC        R18, R6
	CPC        R19, R7
	BRLT       L__print_int252
	JMP        L_print_int54
L__print_int252:
;pcd8544.c,256 :: 		ch = (value / 10000);
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 16
	LDI        R21, 39
	LDI        R22, 0
	LDI        R23, 0
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _Div_32x32_S+0
	MOVW       R16, R18
	MOVW       R18, R20
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	STD        Y+0, R16
;pcd8544.c,257 :: 		PCD8544_set_cursor((x_pos + 6), y_pos);
	MOV        R16, R2
	SUBI       R16, 250
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,258 :: 		PCD8544_print_char((48 + ch), colour);
	LDD        R16, Y+0
	SUBI       R16, 208
	MOV        R3, R8
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,260 :: 		ch = ((value % 10000)/ 1000);
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 16
	LDI        R21, 39
	LDI        R22, 0
	LDI        R23, 0
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _Div_32x32_S+0
	MOVW       R16, R22
	MOVW       R18, R24
	LDI        R20, 232
	LDI        R21, 3
	LDI        R22, 0
	LDI        R23, 0
	CALL       _Div_32x32_S+0
	MOVW       R16, R18
	MOVW       R18, R20
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	STD        Y+0, R16
;pcd8544.c,261 :: 		PCD8544_set_cursor((x_pos + 12), y_pos);
	MOV        R16, R2
	SUBI       R16, 244
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,262 :: 		PCD8544_print_char((48 + ch), colour);
	LDD        R16, Y+0
	SUBI       R16, 208
	MOV        R3, R8
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,264 :: 		ch = ((value % 1000) / 100);
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 232
	LDI        R21, 3
	LDI        R22, 0
	LDI        R23, 0
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _Div_32x32_S+0
	MOVW       R16, R22
	MOVW       R18, R24
	LDI        R20, 100
	LDI        R21, 0
	LDI        R22, 0
	LDI        R23, 0
	CALL       _Div_32x32_S+0
	MOVW       R16, R18
	MOVW       R18, R20
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	STD        Y+0, R16
;pcd8544.c,265 :: 		PCD8544_set_cursor((x_pos + 18), y_pos);
	MOV        R16, R2
	SUBI       R16, 238
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,266 :: 		PCD8544_print_char((48 + ch), colour);
	LDD        R16, Y+0
	SUBI       R16, 208
	MOV        R3, R8
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,268 :: 		ch = ((value % 100) / 10);
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 100
	LDI        R21, 0
	LDI        R22, 0
	LDI        R23, 0
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _Div_32x32_S+0
	MOVW       R16, R22
	MOVW       R18, R24
	LDI        R20, 10
	LDI        R21, 0
	LDI        R22, 0
	LDI        R23, 0
	CALL       _Div_32x32_S+0
	MOVW       R16, R18
	MOVW       R18, R20
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	STD        Y+0, R16
;pcd8544.c,269 :: 		PCD8544_set_cursor((x_pos + 24), y_pos);
	MOV        R16, R2
	SUBI       R16, 232
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,270 :: 		PCD8544_print_char((48 + ch), colour);
	LDD        R16, Y+0
	SUBI       R16, 208
	MOV        R3, R8
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,272 :: 		ch = (value % 10);
	PUSH       R8
	PUSH       R3
	PUSH       R2
	LDI        R20, 10
	LDI        R21, 0
	LDI        R22, 0
	LDI        R23, 0
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _Div_32x32_S+0
	MOVW       R16, R22
	MOVW       R18, R24
	POP        R2
	POP        R3
	POP        R8
	STD        Y+0, R16
;pcd8544.c,273 :: 		PCD8544_set_cursor((x_pos + 30), y_pos);
	MOV        R16, R2
	SUBI       R16, 226
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,274 :: 		PCD8544_print_char((48 + ch), colour);
	LDD        R16, Y+0
	SUBI       R16, 208
	MOV        R3, R8
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
;pcd8544.c,275 :: 		}
	JMP        L_print_int55
L_print_int54:
;pcd8544.c,277 :: 		else if((value > 999) && (value <= 9999))
	LDI        R16, 231
	LDI        R17, 3
	LDI        R18, 0
	LDI        R19, 0
	CP         R16, R4
	CPC        R17, R5
	CPC        R18, R6
	CPC        R19, R7
	BRLT       L__print_int253
	JMP        L__print_int187
L__print_int253:
	LDI        R16, 15
	LDI        R17, 39
	LDI        R18, 0
	LDI        R19, 0
	CP         R16, R4
	CPC        R17, R5
	CPC        R18, R6
	CPC        R19, R7
	BRGE       L__print_int254
	JMP        L__print_int186
L__print_int254:
L__print_int185:
;pcd8544.c,279 :: 		ch = ((value % 10000)/ 1000);
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 16
	LDI        R21, 39
	LDI        R22, 0
	LDI        R23, 0
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _Div_32x32_S+0
	MOVW       R16, R22
	MOVW       R18, R24
	LDI        R20, 232
	LDI        R21, 3
	LDI        R22, 0
	LDI        R23, 0
	CALL       _Div_32x32_S+0
	MOVW       R16, R18
	MOVW       R18, R20
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	STD        Y+0, R16
;pcd8544.c,280 :: 		PCD8544_set_cursor((x_pos + 6), y_pos);
	MOV        R16, R2
	SUBI       R16, 250
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,281 :: 		PCD8544_print_char((48 + ch), colour);
	LDD        R16, Y+0
	SUBI       R16, 208
	MOV        R3, R8
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,283 :: 		ch = ((value % 1000) / 100);
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 232
	LDI        R21, 3
	LDI        R22, 0
	LDI        R23, 0
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _Div_32x32_S+0
	MOVW       R16, R22
	MOVW       R18, R24
	LDI        R20, 100
	LDI        R21, 0
	LDI        R22, 0
	LDI        R23, 0
	CALL       _Div_32x32_S+0
	MOVW       R16, R18
	MOVW       R18, R20
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	STD        Y+0, R16
;pcd8544.c,284 :: 		PCD8544_set_cursor((x_pos + 12), y_pos);
	MOV        R16, R2
	SUBI       R16, 244
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,285 :: 		PCD8544_print_char((48 + ch), colour);
	LDD        R16, Y+0
	SUBI       R16, 208
	MOV        R3, R8
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,287 :: 		ch = ((value % 100) / 10);
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 100
	LDI        R21, 0
	LDI        R22, 0
	LDI        R23, 0
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _Div_32x32_S+0
	MOVW       R16, R22
	MOVW       R18, R24
	LDI        R20, 10
	LDI        R21, 0
	LDI        R22, 0
	LDI        R23, 0
	CALL       _Div_32x32_S+0
	MOVW       R16, R18
	MOVW       R18, R20
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	STD        Y+0, R16
;pcd8544.c,288 :: 		PCD8544_set_cursor((x_pos + 18), y_pos);
	MOV        R16, R2
	SUBI       R16, 238
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,289 :: 		PCD8544_print_char((48 + ch), colour);
	LDD        R16, Y+0
	SUBI       R16, 208
	MOV        R3, R8
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,291 :: 		ch = (value % 10);
	PUSH       R8
	PUSH       R3
	PUSH       R2
	LDI        R20, 10
	LDI        R21, 0
	LDI        R22, 0
	LDI        R23, 0
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _Div_32x32_S+0
	MOVW       R16, R22
	MOVW       R18, R24
	POP        R2
	POP        R3
	POP        R8
	STD        Y+0, R16
;pcd8544.c,292 :: 		PCD8544_set_cursor((x_pos + 24), y_pos);
	MOV        R16, R2
	SUBI       R16, 232
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,293 :: 		PCD8544_print_char((48 + ch), colour);
	LDD        R16, Y+0
	SUBI       R16, 208
	MOV        R3, R8
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,295 :: 		PCD8544_set_cursor((x_pos + 30), y_pos);
	MOV        R16, R2
	SUBI       R16, 226
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,296 :: 		PCD8544_print_char(0x20, colour);
	MOV        R3, R8
	LDI        R27, 32
	MOV        R2, R27
	CALL       _PCD8544_print_char+0
;pcd8544.c,297 :: 		}
	JMP        L_print_int59
;pcd8544.c,277 :: 		else if((value > 999) && (value <= 9999))
L__print_int187:
L__print_int186:
;pcd8544.c,298 :: 		else if((value > 99) && (value <= 999))
	LDI        R16, 99
	LDI        R17, 0
	LDI        R18, 0
	LDI        R19, 0
	CP         R16, R4
	CPC        R17, R5
	CPC        R18, R6
	CPC        R19, R7
	BRLT       L__print_int255
	JMP        L__print_int189
L__print_int255:
	LDI        R16, 231
	LDI        R17, 3
	LDI        R18, 0
	LDI        R19, 0
	CP         R16, R4
	CPC        R17, R5
	CPC        R18, R6
	CPC        R19, R7
	BRGE       L__print_int256
	JMP        L__print_int188
L__print_int256:
L__print_int184:
;pcd8544.c,300 :: 		ch = ((value % 1000) / 100);
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 232
	LDI        R21, 3
	LDI        R22, 0
	LDI        R23, 0
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _Div_32x32_S+0
	MOVW       R16, R22
	MOVW       R18, R24
	LDI        R20, 100
	LDI        R21, 0
	LDI        R22, 0
	LDI        R23, 0
	CALL       _Div_32x32_S+0
	MOVW       R16, R18
	MOVW       R18, R20
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	STD        Y+0, R16
;pcd8544.c,301 :: 		PCD8544_set_cursor((x_pos + 6), y_pos);
	MOV        R16, R2
	SUBI       R16, 250
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,302 :: 		PCD8544_print_char((48 + ch), colour);
	LDD        R16, Y+0
	SUBI       R16, 208
	MOV        R3, R8
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,304 :: 		ch = ((value % 100) / 10);
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 100
	LDI        R21, 0
	LDI        R22, 0
	LDI        R23, 0
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _Div_32x32_S+0
	MOVW       R16, R22
	MOVW       R18, R24
	LDI        R20, 10
	LDI        R21, 0
	LDI        R22, 0
	LDI        R23, 0
	CALL       _Div_32x32_S+0
	MOVW       R16, R18
	MOVW       R18, R20
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	STD        Y+0, R16
;pcd8544.c,305 :: 		PCD8544_set_cursor((x_pos + 12), y_pos);
	MOV        R16, R2
	SUBI       R16, 244
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,306 :: 		PCD8544_print_char((48 + ch), colour);
	LDD        R16, Y+0
	SUBI       R16, 208
	MOV        R3, R8
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,308 :: 		ch = (value % 10);
	PUSH       R8
	PUSH       R3
	PUSH       R2
	LDI        R20, 10
	LDI        R21, 0
	LDI        R22, 0
	LDI        R23, 0
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _Div_32x32_S+0
	MOVW       R16, R22
	MOVW       R18, R24
	POP        R2
	POP        R3
	POP        R8
	STD        Y+0, R16
;pcd8544.c,309 :: 		PCD8544_set_cursor((x_pos + 18), y_pos);
	MOV        R16, R2
	SUBI       R16, 238
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,310 :: 		PCD8544_print_char((48 + ch), colour);
	LDD        R16, Y+0
	SUBI       R16, 208
	MOV        R3, R8
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,312 :: 		PCD8544_set_cursor((x_pos + 24), y_pos);
	MOV        R16, R2
	SUBI       R16, 232
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,313 :: 		PCD8544_print_char(0x20, colour);
	MOV        R3, R8
	LDI        R27, 32
	MOV        R2, R27
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,315 :: 		PCD8544_set_cursor((x_pos + 30), y_pos);
	MOV        R16, R2
	SUBI       R16, 226
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,316 :: 		PCD8544_print_char(0x20, colour);
	MOV        R3, R8
	LDI        R27, 32
	MOV        R2, R27
	CALL       _PCD8544_print_char+0
;pcd8544.c,317 :: 		}
	JMP        L_print_int63
;pcd8544.c,298 :: 		else if((value > 99) && (value <= 999))
L__print_int189:
L__print_int188:
;pcd8544.c,318 :: 		else if((value > 9) && (value <= 99))
	LDI        R16, 9
	LDI        R17, 0
	LDI        R18, 0
	LDI        R19, 0
	CP         R16, R4
	CPC        R17, R5
	CPC        R18, R6
	CPC        R19, R7
	BRLT       L__print_int257
	JMP        L__print_int191
L__print_int257:
	LDI        R16, 99
	LDI        R17, 0
	LDI        R18, 0
	LDI        R19, 0
	CP         R16, R4
	CPC        R17, R5
	CPC        R18, R6
	CPC        R19, R7
	BRGE       L__print_int258
	JMP        L__print_int190
L__print_int258:
L__print_int183:
;pcd8544.c,320 :: 		ch = ((value % 100) / 10);
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDI        R20, 100
	LDI        R21, 0
	LDI        R22, 0
	LDI        R23, 0
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _Div_32x32_S+0
	MOVW       R16, R22
	MOVW       R18, R24
	LDI        R20, 10
	LDI        R21, 0
	LDI        R22, 0
	LDI        R23, 0
	CALL       _Div_32x32_S+0
	MOVW       R16, R18
	MOVW       R18, R20
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	STD        Y+0, R16
;pcd8544.c,321 :: 		PCD8544_set_cursor((x_pos + 6), y_pos);
	MOV        R16, R2
	SUBI       R16, 250
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,322 :: 		PCD8544_print_char((48 + ch), colour);
	LDD        R16, Y+0
	SUBI       R16, 208
	MOV        R3, R8
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,324 :: 		ch = (value % 10);
	PUSH       R8
	PUSH       R3
	PUSH       R2
	LDI        R20, 10
	LDI        R21, 0
	LDI        R22, 0
	LDI        R23, 0
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _Div_32x32_S+0
	MOVW       R16, R22
	MOVW       R18, R24
	POP        R2
	POP        R3
	POP        R8
	STD        Y+0, R16
;pcd8544.c,325 :: 		PCD8544_set_cursor((x_pos + 12), y_pos);
	MOV        R16, R2
	SUBI       R16, 244
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,326 :: 		PCD8544_print_char((48 + ch), colour);
	LDD        R16, Y+0
	SUBI       R16, 208
	MOV        R3, R8
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,328 :: 		PCD8544_set_cursor((x_pos + 18), y_pos);
	MOV        R16, R2
	SUBI       R16, 238
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,329 :: 		PCD8544_print_char(0x20, colour);
	MOV        R3, R8
	LDI        R27, 32
	MOV        R2, R27
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,331 :: 		PCD8544_set_cursor((x_pos + 24), y_pos);
	MOV        R16, R2
	SUBI       R16, 232
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,332 :: 		PCD8544_print_char(0x20, colour);
	MOV        R3, R8
	LDI        R27, 32
	MOV        R2, R27
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,334 :: 		PCD8544_set_cursor((x_pos + 30), y_pos);
	MOV        R16, R2
	SUBI       R16, 226
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,335 :: 		PCD8544_print_char(0x20, colour);
	MOV        R3, R8
	LDI        R27, 32
	MOV        R2, R27
	CALL       _PCD8544_print_char+0
;pcd8544.c,336 :: 		}
	JMP        L_print_int67
;pcd8544.c,318 :: 		else if((value > 9) && (value <= 99))
L__print_int191:
L__print_int190:
;pcd8544.c,339 :: 		ch = (value % 10);
	PUSH       R8
	PUSH       R3
	PUSH       R2
	LDI        R20, 10
	LDI        R21, 0
	LDI        R22, 0
	LDI        R23, 0
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _Div_32x32_S+0
	MOVW       R16, R22
	MOVW       R18, R24
	POP        R2
	POP        R3
	POP        R8
	STD        Y+0, R16
;pcd8544.c,340 :: 		PCD8544_set_cursor((x_pos + 6), y_pos);
	MOV        R16, R2
	SUBI       R16, 250
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,341 :: 		PCD8544_print_char((48 + ch), colour);
	LDD        R16, Y+0
	SUBI       R16, 208
	MOV        R3, R8
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,343 :: 		PCD8544_set_cursor((x_pos + 12), y_pos);
	MOV        R16, R2
	SUBI       R16, 244
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,344 :: 		PCD8544_print_char(0x20, colour);
	MOV        R3, R8
	LDI        R27, 32
	MOV        R2, R27
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,346 :: 		PCD8544_set_cursor((x_pos + 18), y_pos);
	MOV        R16, R2
	SUBI       R16, 238
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,347 :: 		PCD8544_print_char(0x20, colour);
	MOV        R3, R8
	LDI        R27, 32
	MOV        R2, R27
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,349 :: 		PCD8544_set_cursor((x_pos + 24), y_pos);
	MOV        R16, R2
	SUBI       R16, 232
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,350 :: 		PCD8544_print_char(0x20, colour);
	MOV        R3, R8
	LDI        R27, 32
	MOV        R2, R27
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,352 :: 		PCD8544_set_cursor((x_pos + 30), y_pos);
	MOV        R16, R2
	SUBI       R16, 226
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,353 :: 		PCD8544_print_char(0x20, colour);
	MOV        R3, R8
	LDI        R27, 32
	MOV        R2, R27
	CALL       _PCD8544_print_char+0
;pcd8544.c,354 :: 		}
L_print_int67:
L_print_int63:
L_print_int59:
L_print_int55:
;pcd8544.c,355 :: 		}
L_end_print_int:
	POP        R3
	POP        R2
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _print_int

_print_decimal:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 1
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;pcd8544.c,358 :: 		void print_decimal(unsigned char x_pos, unsigned char y_pos, unsigned int value, unsigned char points, unsigned char colour)
;pcd8544.c,360 :: 		unsigned char ch = 0x00;
	PUSH       R2
	PUSH       R3
;pcd8544.c,362 :: 		PCD8544_set_cursor(x_pos, y_pos);
	PUSH       R3
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,363 :: 		PCD8544_print_char(0x2E, colour);
	PUSH       R2
	MOV        R3, R7
	LDI        R27, 46
	MOV        R2, R27
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,365 :: 		ch = (value / 1000);
	LDI        R20, 232
	LDI        R21, 3
	MOVW       R16, R4
	CALL       _Div_16x16_U+0
	MOVW       R16, R24
	STD        Y+0, R16
;pcd8544.c,366 :: 		PCD8544_set_cursor((x_pos + 6), y_pos);
	MOV        R16, R2
	SUBI       R16, 250
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,367 :: 		PCD8544_print_char((48 + ch), colour);
	LDD        R16, Y+0
	SUBI       R16, 208
	MOV        R3, R7
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,369 :: 		if(points > 1)
	LDI        R16, 1
	CP         R16, R6
	BRLO       L__print_decimal260
	JMP        L_print_decimal68
L__print_decimal260:
;pcd8544.c,371 :: 		ch = ((value % 1000) / 100);
	LDI        R20, 232
	LDI        R21, 3
	MOVW       R16, R4
	CALL       _Div_16x16_U+0
	MOVW       R16, R26
	LDI        R20, 100
	LDI        R21, 0
	CALL       _Div_16x16_U+0
	MOVW       R16, R24
	STD        Y+0, R16
;pcd8544.c,372 :: 		PCD8544_set_cursor((x_pos + 12), y_pos);
	MOV        R16, R2
	SUBI       R16, 244
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,373 :: 		PCD8544_print_char((48 + ch), colour);
	LDD        R16, Y+0
	SUBI       R16, 208
	MOV        R3, R7
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,376 :: 		if(points > 2)
	LDI        R16, 2
	CP         R16, R6
	BRLO       L__print_decimal261
	JMP        L_print_decimal69
L__print_decimal261:
;pcd8544.c,378 :: 		ch = ((value % 100) / 10);
	LDI        R20, 100
	LDI        R21, 0
	MOVW       R16, R4
	CALL       _Div_16x16_U+0
	MOVW       R16, R26
	LDI        R20, 10
	LDI        R21, 0
	CALL       _Div_16x16_U+0
	MOVW       R16, R24
	STD        Y+0, R16
;pcd8544.c,379 :: 		PCD8544_set_cursor((x_pos + 18), y_pos);
	MOV        R16, R2
	SUBI       R16, 238
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,380 :: 		PCD8544_print_char((48 + ch), colour);
	LDD        R16, Y+0
	SUBI       R16, 208
	MOV        R3, R7
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
	POP        R2
	POP        R3
;pcd8544.c,382 :: 		if(points > 3)
	LDI        R16, 3
	CP         R16, R6
	BRLO       L__print_decimal262
	JMP        L_print_decimal70
L__print_decimal262:
;pcd8544.c,384 :: 		ch = (value % 10);
	LDI        R20, 10
	LDI        R21, 0
	MOVW       R16, R4
	CALL       _Div_16x16_U+0
	MOVW       R16, R26
	STD        Y+0, R16
;pcd8544.c,385 :: 		PCD8544_set_cursor((x_pos + 24), y_pos);
	MOV        R16, R2
	SUBI       R16, 232
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,386 :: 		PCD8544_print_char((48 + ch), colour);;
	LDD        R16, Y+0
	SUBI       R16, 208
	MOV        R3, R7
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
;pcd8544.c,387 :: 		}
L_print_decimal70:
;pcd8544.c,388 :: 		}
L_print_decimal69:
;pcd8544.c,389 :: 		}
L_print_decimal68:
;pcd8544.c,390 :: 		}
L_end_print_decimal:
	POP        R3
	POP        R2
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _print_decimal

_print_float:
	PUSH       R28
	PUSH       R29
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 4
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;pcd8544.c,393 :: 		void print_float(unsigned char x_pos, unsigned char y_pos, float value, unsigned char points, unsigned char colour)
;pcd8544.c,395 :: 		signed long tmp = 0x00;
	PUSH       R2
	PUSH       R3
	PUSH       R4
	PUSH       R5
	PUSH       R6
	PUSH       R7
;pcd8544.c,397 :: 		tmp = ((signed long)value);
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _float_fpint+0
	STD        Y+0, R16
	STD        Y+1, R17
	STD        Y+2, R18
	STD        Y+3, R19
;pcd8544.c,398 :: 		print_int(x_pos, y_pos, tmp, colour);
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R8, R9
	MOVW       R4, R16
	MOVW       R6, R18
	CALL       _print_int+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
;pcd8544.c,399 :: 		tmp = ((value - tmp) * 10000);
	LDD        R16, Y+0
	LDD        R17, Y+1
	LDD        R18, Y+2
	LDD        R19, Y+3
	CALL       _float_slong2fp+0
	PUSH       R3
	PUSH       R2
	MOVW       R20, R16
	MOVW       R22, R18
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _float_fpsub1+0
	LDI        R20, 0
	LDI        R21, 64
	LDI        R22, 28
	LDI        R23, 70
	CALL       _float_fpmul1+0
	POP        R2
	POP        R3
	POP        R8
	POP        R9
	CALL       _float_fpint+0
	STD        Y+0, R16
	STD        Y+1, R17
	STD        Y+2, R18
	STD        Y+3, R19
;pcd8544.c,401 :: 		if(tmp < 0)
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 0
	LDI        R23, 0
	CP         R16, R20
	CPC        R17, R21
	CPC        R18, R22
	CPC        R19, R23
	BRLT       L__print_float264
	JMP        L_print_float71
L__print_float264:
;pcd8544.c,403 :: 		tmp = -tmp;
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
;pcd8544.c,404 :: 		}
L_print_float71:
;pcd8544.c,406 :: 		if((value >= 9999) && (value < 99999))
	PUSH       R9
	PUSH       R8
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 60
	LDI        R22, 28
	LDI        R23, 70
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _float_op_gequ+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_float265
	LDI        R16, 1
L__print_float265:
	POP        R2
	POP        R3
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_float266
	JMP        L__print_float197
L__print_float266:
	PUSH       R9
	PUSH       R8
	PUSH       R3
	PUSH       R2
	LDI        R20, 128
	LDI        R21, 79
	LDI        R22, 195
	LDI        R23, 71
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _float_op_less+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_float267
	LDI        R16, 1
L__print_float267:
	POP        R2
	POP        R3
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_float268
	JMP        L__print_float196
L__print_float268:
L__print_float195:
;pcd8544.c,408 :: 		print_decimal((x_pos + 36), y_pos, tmp, points, colour);
	MOV        R16, R2
	SUBI       R16, 220
	MOV        R7, R9
	MOV        R6, R8
	LDD        R4, Y+0
	LDD        R5, Y+1
	MOV        R2, R16
	CALL       _print_decimal+0
;pcd8544.c,409 :: 		}
	JMP        L_print_float75
;pcd8544.c,406 :: 		if((value >= 9999) && (value < 99999))
L__print_float197:
L__print_float196:
;pcd8544.c,410 :: 		else if((value >= 999) && (value < 9999))
	PUSH       R9
	PUSH       R8
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 192
	LDI        R22, 121
	LDI        R23, 68
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _float_op_gequ+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_float269
	LDI        R16, 1
L__print_float269:
	POP        R2
	POP        R3
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_float270
	JMP        L__print_float199
L__print_float270:
	PUSH       R9
	PUSH       R8
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 60
	LDI        R22, 28
	LDI        R23, 70
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _float_op_less+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_float271
	LDI        R16, 1
L__print_float271:
	POP        R2
	POP        R3
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_float272
	JMP        L__print_float198
L__print_float272:
L__print_float194:
;pcd8544.c,412 :: 		print_decimal((x_pos + 30), y_pos, tmp, points, colour);
	MOV        R16, R2
	SUBI       R16, 226
	MOV        R7, R9
	MOV        R6, R8
	LDD        R4, Y+0
	LDD        R5, Y+1
	MOV        R2, R16
	CALL       _print_decimal+0
;pcd8544.c,413 :: 		}
	JMP        L_print_float79
;pcd8544.c,410 :: 		else if((value >= 999) && (value < 9999))
L__print_float199:
L__print_float198:
;pcd8544.c,414 :: 		else if((value >= 99) && (value < 999))
	PUSH       R9
	PUSH       R8
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 198
	LDI        R23, 66
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _float_op_gequ+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_float273
	LDI        R16, 1
L__print_float273:
	POP        R2
	POP        R3
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_float274
	JMP        L__print_float201
L__print_float274:
	PUSH       R9
	PUSH       R8
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 192
	LDI        R22, 121
	LDI        R23, 68
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _float_op_less+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_float275
	LDI        R16, 1
L__print_float275:
	POP        R2
	POP        R3
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_float276
	JMP        L__print_float200
L__print_float276:
L__print_float193:
;pcd8544.c,416 :: 		print_decimal((x_pos + 24), y_pos, tmp, points, colour);
	MOV        R16, R2
	SUBI       R16, 232
	MOV        R7, R9
	MOV        R6, R8
	LDD        R4, Y+0
	LDD        R5, Y+1
	MOV        R2, R16
	CALL       _print_decimal+0
;pcd8544.c,417 :: 		}
	JMP        L_print_float83
;pcd8544.c,414 :: 		else if((value >= 99) && (value < 999))
L__print_float201:
L__print_float200:
;pcd8544.c,418 :: 		else if((value >= 9) && (value < 99))
	PUSH       R9
	PUSH       R8
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 16
	LDI        R23, 65
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _float_op_gequ+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_float277
	LDI        R16, 1
L__print_float277:
	POP        R2
	POP        R3
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_float278
	JMP        L__print_float203
L__print_float278:
	PUSH       R9
	PUSH       R8
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 198
	LDI        R23, 66
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _float_op_less+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_float279
	LDI        R16, 1
L__print_float279:
	POP        R2
	POP        R3
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_float280
	JMP        L__print_float202
L__print_float280:
L__print_float192:
;pcd8544.c,420 :: 		print_decimal((x_pos + 18), y_pos, tmp, points, colour);
	MOV        R16, R2
	SUBI       R16, 238
	MOV        R7, R9
	MOV        R6, R8
	LDD        R4, Y+0
	LDD        R5, Y+1
	MOV        R2, R16
	CALL       _print_decimal+0
;pcd8544.c,421 :: 		}
	JMP        L_print_float87
;pcd8544.c,418 :: 		else if((value >= 9) && (value < 99))
L__print_float203:
L__print_float202:
;pcd8544.c,422 :: 		else if(value < 9)
	PUSH       R9
	PUSH       R8
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 16
	LDI        R23, 65
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _float_op_less+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_float281
	LDI        R16, 1
L__print_float281:
	POP        R2
	POP        R3
	POP        R8
	POP        R9
	TST        R16
	BRNE       L__print_float282
	JMP        L_print_float88
L__print_float282:
;pcd8544.c,424 :: 		print_decimal((x_pos + 12), y_pos, tmp, points, colour);
	MOV        R16, R2
	SUBI       R16, 244
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R7, R9
	MOV        R6, R8
	LDD        R4, Y+0
	LDD        R5, Y+1
	MOV        R2, R16
	CALL       _print_decimal+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
;pcd8544.c,425 :: 		if((value) < 0)
	PUSH       R9
	PUSH       R3
	PUSH       R2
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 0
	LDI        R23, 0
	MOVW       R16, R4
	MOVW       R18, R6
	CALL       _float_op_less+0
	OR         R0, R0
	LDI        R16, 0
	BREQ       L__print_float283
	LDI        R16, 1
L__print_float283:
	POP        R2
	POP        R3
	POP        R9
	TST        R16
	BRNE       L__print_float284
	JMP        L_print_float89
L__print_float284:
;pcd8544.c,427 :: 		PCD8544_set_cursor(x_pos, y_pos);
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,428 :: 		PCD8544_print_char(0x2D, colour);
	MOV        R3, R9
	LDI        R27, 45
	MOV        R2, R27
	CALL       _PCD8544_print_char+0
;pcd8544.c,429 :: 		}
	JMP        L_print_float90
L_print_float89:
;pcd8544.c,432 :: 		PCD8544_set_cursor(x_pos, y_pos);
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,433 :: 		PCD8544_print_char(0x20, colour);
	MOV        R3, R9
	LDI        R27, 32
	MOV        R2, R27
	CALL       _PCD8544_print_char+0
;pcd8544.c,434 :: 		}
L_print_float90:
;pcd8544.c,435 :: 		}
L_print_float88:
L_print_float87:
L_print_float83:
L_print_float79:
L_print_float75:
;pcd8544.c,436 :: 		}
L_end_print_float:
	POP        R7
	POP        R6
	POP        R5
	POP        R4
	POP        R3
	POP        R2
	ADIW       R28, 3
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _print_float

_Draw_Pixel:

;pcd8544.c,439 :: 		void Draw_Pixel(unsigned char x_pos, unsigned char y_pos, unsigned char colour)
;pcd8544.c,441 :: 		unsigned char row = 0;
	PUSH       R2
	PUSH       R3
;pcd8544.c,442 :: 		unsigned char value = 0;
;pcd8544.c,444 :: 		if((x_pos < 0) || (x_pos >= X_max) || (y_pos < 0) || (y_pos >= Y_max))
	LDI        R27, 0
	CP         R2, R27
	BRSH       L__Draw_Pixel286
	JMP        L__Draw_Pixel208
L__Draw_Pixel286:
	LDI        R27, 84
	CP         R2, R27
	BRLO       L__Draw_Pixel287
	JMP        L__Draw_Pixel207
L__Draw_Pixel287:
	LDI        R27, 0
	CP         R3, R27
	BRSH       L__Draw_Pixel288
	JMP        L__Draw_Pixel206
L__Draw_Pixel288:
	LDI        R27, 48
	CP         R3, R27
	BRLO       L__Draw_Pixel289
	JMP        L__Draw_Pixel205
L__Draw_Pixel289:
	JMP        L_Draw_Pixel93
L__Draw_Pixel208:
L__Draw_Pixel207:
L__Draw_Pixel206:
L__Draw_Pixel205:
;pcd8544.c,446 :: 		return;
	JMP        L_end_Draw_Pixel
;pcd8544.c,447 :: 		}
L_Draw_Pixel93:
;pcd8544.c,449 :: 		row = (y_pos >> 3);
	MOV        R16, R3
	LSR        R16
	LSR        R16
	LSR        R16
; row start address is: 20 (R20)
	MOV        R20, R16
;pcd8544.c,451 :: 		value = PCD8544_buffer[x_pos][row];
	PUSH       R20
	LDI        R16, 6
	LDI        R17, 0
	MOV        R20, R2
	LDI        R21, 0
	CALL       _HWMul_16x16+0
	POP        R20
	LDI        R18, #lo_addr(nokia5510_lcd_demo_PCD8544_buffer+0)
	LDI        R19, hi_addr(nokia5510_lcd_demo_PCD8544_buffer+0)
	ADD        R16, R18
	ADC        R17, R19
	MOV        R30, R20
	LDI        R31, 0
	ADD        R30, R16
	ADC        R31, R17
	LD         R16, Z
; value start address is: 17 (R17)
	MOV        R17, R16
;pcd8544.c,453 :: 		if(colour == BLACK)
	LDI        R27, 0
	CP         R4, R27
	BREQ       L__Draw_Pixel290
	JMP        L_Draw_Pixel94
L__Draw_Pixel290:
;pcd8544.c,455 :: 		value |= (1 << (y_pos % 8));
	MOV        R16, R3
	ANDI       R16, 7
	MOV        R27, R16
	LDI        R16, 1
	TST        R27
	BREQ       L__Draw_Pixel292
L__Draw_Pixel291:
	LSL        R16
	DEC        R27
	BRNE       L__Draw_Pixel291
L__Draw_Pixel292:
	OR         R16, R17
; value end address is: 17 (R17)
; value start address is: 21 (R21)
	MOV        R21, R16
;pcd8544.c,456 :: 		}
; value end address is: 21 (R21)
	JMP        L_Draw_Pixel95
L_Draw_Pixel94:
;pcd8544.c,457 :: 		else if(colour == WHITE)
; value start address is: 17 (R17)
	LDI        R27, 1
	CP         R4, R27
	BREQ       L__Draw_Pixel293
	JMP        L_Draw_Pixel96
L__Draw_Pixel293:
;pcd8544.c,459 :: 		value &= (~(1 << (y_pos % 8)));
	MOV        R16, R3
	ANDI       R16, 7
	MOV        R27, R16
	LDI        R16, 1
	TST        R27
	BREQ       L__Draw_Pixel295
L__Draw_Pixel294:
	LSL        R16
	DEC        R27
	BRNE       L__Draw_Pixel294
L__Draw_Pixel295:
	COM        R16
	AND        R16, R17
; value end address is: 17 (R17)
; value start address is: 16 (R16)
;pcd8544.c,460 :: 		}
	MOV        R21, R16
; value end address is: 16 (R16)
	JMP        L_Draw_Pixel97
L_Draw_Pixel96:
;pcd8544.c,461 :: 		else if(colour == PIXEL_XOR)
; value start address is: 17 (R17)
	LDI        R27, 2
	CP         R4, R27
	BREQ       L__Draw_Pixel296
	JMP        L__Draw_Pixel209
L__Draw_Pixel296:
;pcd8544.c,463 :: 		value ^= (1 << (y_pos % 8));
	MOV        R16, R3
	ANDI       R16, 7
	MOV        R27, R16
	LDI        R16, 1
	TST        R27
	BREQ       L__Draw_Pixel298
L__Draw_Pixel297:
	LSL        R16
	DEC        R27
	BRNE       L__Draw_Pixel297
L__Draw_Pixel298:
	EOR        R16, R17
	MOV        R17, R16
; value end address is: 17 (R17)
	MOV        R16, R17
;pcd8544.c,464 :: 		}
	JMP        L_Draw_Pixel98
L__Draw_Pixel209:
;pcd8544.c,461 :: 		else if(colour == PIXEL_XOR)
	MOV        R16, R17
;pcd8544.c,464 :: 		}
L_Draw_Pixel98:
; value start address is: 16 (R16)
	MOV        R21, R16
; value end address is: 16 (R16)
L_Draw_Pixel97:
; value start address is: 21 (R21)
; value end address is: 21 (R21)
L_Draw_Pixel95:
;pcd8544.c,466 :: 		PCD8544_buffer[x_pos][row] = value;
; value start address is: 21 (R21)
	PUSH       R21
	PUSH       R20
	LDI        R16, 6
	LDI        R17, 0
	MOV        R20, R2
	LDI        R21, 0
	CALL       _HWMul_16x16+0
	POP        R20
	POP        R21
	LDI        R18, #lo_addr(nokia5510_lcd_demo_PCD8544_buffer+0)
	LDI        R19, hi_addr(nokia5510_lcd_demo_PCD8544_buffer+0)
	ADD        R16, R18
	ADC        R17, R19
	MOV        R30, R20
	LDI        R31, 0
	ADD        R30, R16
	ADC        R31, R17
	ST         Z, R21
;pcd8544.c,468 :: 		PCD8544_set_cursor(x_pos, row);
	MOV        R3, R20
; row end address is: 20 (R20)
	CALL       _PCD8544_set_cursor+0
;pcd8544.c,469 :: 		PCD8544_write(DAT, value);
	MOV        R3, R21
; value end address is: 21 (R21)
	LDI        R27, 1
	MOV        R2, R27
	CALL       _PCD8544_write+0
;pcd8544.c,470 :: 		}
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

;pcd8544.c,473 :: 		void Draw_Line(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char colour)
; colour start address is: 20 (R20)
	LDD        R20, Y+0
;pcd8544.c,475 :: 		signed int dx = 0x0000;
;pcd8544.c,476 :: 		signed int dy = 0x0000;
;pcd8544.c,477 :: 		signed int stepx = 0x0000;
;pcd8544.c,478 :: 		signed int stepy = 0x0000;
;pcd8544.c,479 :: 		signed int fraction = 0x0000;
;pcd8544.c,481 :: 		dy = (y2 - y1);
	MOVW       R18, R8
	SUB        R18, R4
	SBC        R19, R5
; dy start address is: 10 (R10)
	MOVW       R10, R18
;pcd8544.c,482 :: 		dx = (x2 - x1);
	MOVW       R16, R6
	SUB        R16, R2
	SBC        R17, R3
; dx start address is: 21 (R21)
	MOV        R21, R16
	MOV        R22, R17
;pcd8544.c,484 :: 		if (dy < 0)
	LDI        R16, 0
	LDI        R17, 0
	CP         R18, R16
	CPC        R19, R17
	BRLT       L__Draw_Line300
	JMP        L_Draw_Line99
L__Draw_Line300:
;pcd8544.c,486 :: 		dy = -dy;
	LDI        R16, 0
	LDI        R17, 0
	SUB        R16, R10
	SBC        R17, R11
	MOVW       R10, R16
;pcd8544.c,487 :: 		stepy = -1;
; stepy start address is: 18 (R18)
	LDI        R18, 255
	LDI        R19, 255
;pcd8544.c,488 :: 		}
; stepy end address is: 18 (R18)
	JMP        L_Draw_Line100
L_Draw_Line99:
;pcd8544.c,491 :: 		stepy = 1;
; stepy start address is: 18 (R18)
	LDI        R18, 1
	LDI        R19, 0
; stepy end address is: 18 (R18)
; dy end address is: 10 (R10)
;pcd8544.c,492 :: 		}
L_Draw_Line100:
;pcd8544.c,494 :: 		if (dx < 0)
; stepy start address is: 18 (R18)
; dy start address is: 10 (R10)
	LDI        R16, 0
	LDI        R17, 0
	CP         R21, R16
	CPC        R22, R17
	BRLT       L__Draw_Line301
	JMP        L_Draw_Line101
L__Draw_Line301:
;pcd8544.c,496 :: 		dx = -dx;
	LDI        R16, 0
	LDI        R17, 0
	SUB        R16, R21
	SBC        R17, R22
	MOV        R21, R16
	MOV        R22, R17
;pcd8544.c,497 :: 		stepx = -1;
; stepx start address is: 25 (R25)
	LDI        R25, 255
	LDI        R26, 255
;pcd8544.c,498 :: 		}
; stepx end address is: 25 (R25)
	JMP        L_Draw_Line102
L_Draw_Line101:
;pcd8544.c,501 :: 		stepx = 1;
; stepx start address is: 25 (R25)
	LDI        R25, 1
	LDI        R26, 0
; dx end address is: 21 (R21)
; stepx end address is: 25 (R25)
;pcd8544.c,502 :: 		}
L_Draw_Line102:
;pcd8544.c,504 :: 		dx <<= 0x01;
; stepx start address is: 25 (R25)
; dx start address is: 21 (R21)
	MOV        R16, R21
	MOV        R17, R22
	LSL        R16
	ROL        R17
; dx end address is: 21 (R21)
; dx start address is: 23 (R23)
	MOV        R23, R16
	MOV        R24, R17
;pcd8544.c,505 :: 		dy <<= 0x01;
	MOVW       R16, R10
	LSL        R16
	ROL        R17
; dy end address is: 10 (R10)
; dy start address is: 21 (R21)
	MOV        R21, R16
	MOV        R22, R17
;pcd8544.c,507 :: 		Draw_Pixel(x1, y1, colour);
	PUSH       R22
	PUSH       R21
	PUSH       R19
	PUSH       R18
	PUSH       R20
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R3, R4
	MOV        R4, R20
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R20
	POP        R18
	POP        R19
	POP        R21
	POP        R22
;pcd8544.c,509 :: 		if (dx > dy)
	CP         R21, R23
	CPC        R22, R24
	BRLT       L__Draw_Line302
	JMP        L_Draw_Line103
L__Draw_Line302:
;pcd8544.c,511 :: 		fraction = (dy - (dx >> 1));
	MOV        R16, R23
	MOV        R17, R24
	ASR        R17
	ROR        R16
	MOVW       R0, R16
	MOV        R16, R21
	MOV        R17, R22
	SUB        R16, R0
	SBC        R17, R1
; fraction start address is: 10 (R10)
	MOVW       R10, R16
; stepy end address is: 18 (R18)
; fraction end address is: 10 (R10)
	MOVW       R12, R18
;pcd8544.c,512 :: 		while (x1 != x2)
L_Draw_Line104:
; fraction start address is: 10 (R10)
; stepy start address is: 12 (R12)
; dy start address is: 21 (R21)
; dy end address is: 21 (R21)
; dx start address is: 23 (R23)
; dx end address is: 23 (R23)
; stepx start address is: 25 (R25)
; stepx end address is: 25 (R25)
; stepy start address is: 12 (R12)
; stepy end address is: 12 (R12)
; colour start address is: 20 (R20)
; colour end address is: 20 (R20)
	CP         R2, R6
	CPC        R3, R7
	BRNE       L__Draw_Line303
	JMP        L_Draw_Line105
L__Draw_Line303:
; dy end address is: 21 (R21)
; dx end address is: 23 (R23)
; stepx end address is: 25 (R25)
; stepy end address is: 12 (R12)
; colour end address is: 20 (R20)
;pcd8544.c,514 :: 		if (fraction >= 0)
; colour start address is: 20 (R20)
; stepy start address is: 12 (R12)
; stepx start address is: 25 (R25)
; dx start address is: 23 (R23)
; dy start address is: 21 (R21)
	LDI        R16, 0
	LDI        R17, 0
	CP         R10, R16
	CPC        R11, R17
	BRGE       L__Draw_Line304
	JMP        L__Draw_Line210
L__Draw_Line304:
;pcd8544.c,516 :: 		y1 += stepy;
	MOVW       R16, R12
	ADD        R16, R4
	ADC        R17, R5
	MOVW       R4, R16
;pcd8544.c,517 :: 		fraction -= dx;
	MOVW       R16, R10
	SUB        R16, R23
	SBC        R17, R24
	MOVW       R10, R16
; fraction end address is: 10 (R10)
;pcd8544.c,518 :: 		}
	JMP        L_Draw_Line106
L__Draw_Line210:
;pcd8544.c,514 :: 		if (fraction >= 0)
;pcd8544.c,518 :: 		}
L_Draw_Line106:
;pcd8544.c,519 :: 		x1 += stepx;
; fraction start address is: 10 (R10)
	MOV        R18, R25
	MOV        R19, R26
	ADD        R18, R2
	ADC        R19, R3
	MOVW       R2, R18
;pcd8544.c,520 :: 		fraction += dy;
	MOV        R16, R21
	MOV        R17, R22
	ADD        R16, R10
	ADC        R17, R11
	MOVW       R10, R16
;pcd8544.c,522 :: 		Draw_Pixel(x1, y1, colour);
	PUSH       R20
	PUSH       R22
	PUSH       R21
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R3, R4
	MOV        R4, R20
	MOV        R2, R18
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R21
	POP        R22
	POP        R20
;pcd8544.c,523 :: 		}
; dy end address is: 21 (R21)
; dx end address is: 23 (R23)
; stepx end address is: 25 (R25)
; stepy end address is: 12 (R12)
; colour end address is: 20 (R20)
; fraction end address is: 10 (R10)
	JMP        L_Draw_Line104
L_Draw_Line105:
;pcd8544.c,524 :: 		}
	JMP        L_Draw_Line107
L_Draw_Line103:
;pcd8544.c,527 :: 		fraction = (dx - (dy >> 1));
; colour start address is: 20 (R20)
; stepx start address is: 25 (R25)
; dx start address is: 23 (R23)
; dy start address is: 21 (R21)
; stepy start address is: 18 (R18)
	MOV        R16, R21
	MOV        R17, R22
	ASR        R17
	ROR        R16
	MOVW       R0, R16
	MOV        R16, R23
	MOV        R17, R24
	SUB        R16, R0
	SBC        R17, R1
; fraction start address is: 10 (R10)
	MOVW       R10, R16
; stepy end address is: 18 (R18)
; dy end address is: 21 (R21)
; dx end address is: 23 (R23)
; stepx end address is: 25 (R25)
; colour end address is: 20 (R20)
; fraction end address is: 10 (R10)
	PUSH       R11
	PUSH       R10
	PUSH       R22
	PUSH       R21
	MOV        R22, R23
	MOV        R23, R24
	MOV        R24, R25
	MOV        R25, R26
	MOV        R26, R20
	MOVW       R10, R18
	POP        R20
	POP        R21
	POP        R18
	POP        R19
;pcd8544.c,529 :: 		while (y1 != y2)
L_Draw_Line108:
; colour start address is: 26 (R26)
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
; colour start address is: 26 (R26)
; colour end address is: 26 (R26)
	CP         R4, R8
	CPC        R5, R9
	BRNE       L__Draw_Line305
	JMP        L_Draw_Line109
L__Draw_Line305:
; dy end address is: 20 (R20)
; dx end address is: 22 (R22)
; stepx end address is: 24 (R24)
; stepy end address is: 10 (R10)
; colour end address is: 26 (R26)
;pcd8544.c,531 :: 		if (fraction >= 0)
; colour start address is: 26 (R26)
; stepy start address is: 10 (R10)
; stepx start address is: 24 (R24)
; dx start address is: 22 (R22)
; dy start address is: 20 (R20)
	LDI        R16, 0
	LDI        R17, 0
	CP         R18, R16
	CPC        R19, R17
	BRGE       L__Draw_Line306
	JMP        L__Draw_Line211
L__Draw_Line306:
;pcd8544.c,533 :: 		x1 += stepx;
	MOVW       R16, R24
	ADD        R16, R2
	ADC        R17, R3
	MOVW       R2, R16
;pcd8544.c,534 :: 		fraction -= dy;
	MOVW       R16, R18
	SUB        R16, R20
	SBC        R17, R21
; fraction end address is: 18 (R18)
; fraction start address is: 12 (R12)
	MOVW       R12, R16
; fraction end address is: 12 (R12)
;pcd8544.c,535 :: 		}
	JMP        L_Draw_Line110
L__Draw_Line211:
;pcd8544.c,531 :: 		if (fraction >= 0)
	MOVW       R12, R18
;pcd8544.c,535 :: 		}
L_Draw_Line110:
;pcd8544.c,536 :: 		y1 += stepy;
; fraction start address is: 12 (R12)
	MOVW       R18, R10
	ADD        R18, R4
	ADC        R19, R5
	MOVW       R4, R18
;pcd8544.c,537 :: 		fraction += dx;
	MOVW       R16, R22
	ADD        R16, R12
	ADC        R17, R13
; fraction end address is: 12 (R12)
; fraction start address is: 16 (R16)
;pcd8544.c,538 :: 		Draw_Pixel(x1, y1, colour);
	PUSH       R17
	PUSH       R16
	PUSH       R21
	PUSH       R20
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R4, R26
	MOV        R3, R18
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R20
	POP        R21
	POP        R16
	POP        R17
;pcd8544.c,539 :: 		}
; dy end address is: 20 (R20)
; dx end address is: 22 (R22)
; stepx end address is: 24 (R24)
; stepy end address is: 10 (R10)
; colour end address is: 26 (R26)
; fraction end address is: 16 (R16)
	MOVW       R18, R16
	JMP        L_Draw_Line108
L_Draw_Line109:
;pcd8544.c,540 :: 		}
L_Draw_Line107:
;pcd8544.c,541 :: 		}
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
	SBIW       R28, 3
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;pcd8544.c,544 :: 		void Draw_Rectangle(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char fill, unsigned char colour)
	PUSH       R2
	PUSH       R3
; fill start address is: 17 (R17)
	LDD        R17, Y+7
	LDD        R16, Y+8
	STD        Y+8, R16
;pcd8544.c,546 :: 		unsigned char i = 0x00;
;pcd8544.c,547 :: 		unsigned char xmin = 0x00;
;pcd8544.c,548 :: 		unsigned char xmax = 0x00;
;pcd8544.c,549 :: 		unsigned char ymin = 0x00;
;pcd8544.c,550 :: 		unsigned char ymax = 0x00;
;pcd8544.c,552 :: 		if(fill != NO)
	CPI        R17, 0
	BRNE       L__Draw_Rectangle308
	JMP        L_Draw_Rectangle111
L__Draw_Rectangle308:
; fill end address is: 17 (R17)
;pcd8544.c,554 :: 		if(x1 < x2)
	CP         R2, R6
	CPC        R3, R7
	BRLT       L__Draw_Rectangle309
	JMP        L_Draw_Rectangle112
L__Draw_Rectangle309:
;pcd8544.c,556 :: 		xmin = x1;
; xmin start address is: 18 (R18)
	MOV        R18, R2
;pcd8544.c,557 :: 		xmax = x2;
	STD        Y+0, R6
;pcd8544.c,558 :: 		}
	MOV        R20, R18
; xmin end address is: 18 (R18)
	JMP        L_Draw_Rectangle113
L_Draw_Rectangle112:
;pcd8544.c,561 :: 		xmin = x2;
; xmin start address is: 18 (R18)
	MOV        R18, R6
;pcd8544.c,562 :: 		xmax = x1;
	STD        Y+0, R2
; xmin end address is: 18 (R18)
	MOV        R20, R18
;pcd8544.c,563 :: 		}
L_Draw_Rectangle113:
;pcd8544.c,565 :: 		if(y1 < y2)
; xmin start address is: 20 (R20)
	CP         R4, R8
	CPC        R5, R9
	BRLT       L__Draw_Rectangle310
	JMP        L_Draw_Rectangle114
L__Draw_Rectangle310:
;pcd8544.c,567 :: 		ymin = y1;
	STD        Y+1, R4
;pcd8544.c,568 :: 		ymax = y2;
	STD        Y+2, R8
;pcd8544.c,569 :: 		}
	JMP        L_Draw_Rectangle115
L_Draw_Rectangle114:
;pcd8544.c,572 :: 		ymin = y2;
	STD        Y+1, R8
;pcd8544.c,573 :: 		ymax = y1;
	STD        Y+2, R4
;pcd8544.c,574 :: 		}
L_Draw_Rectangle115:
;pcd8544.c,576 :: 		for(; xmin <= xmax; ++xmin)
; xmin end address is: 20 (R20)
L_Draw_Rectangle116:
; xmin start address is: 20 (R20)
	LDD        R16, Y+0
	CP         R16, R20
	BRSH       L__Draw_Rectangle311
	JMP        L_Draw_Rectangle117
L__Draw_Rectangle311:
;pcd8544.c,578 :: 		for(i = ymin; i <= ymax; ++i)
; i start address is: 22 (R22)
	LDD        R22, Y+1
; i end address is: 22 (R22)
; xmin end address is: 20 (R20)
	MOV        R17, R22
L_Draw_Rectangle119:
; i start address is: 17 (R17)
; xmin start address is: 20 (R20)
	LDD        R16, Y+2
	CP         R16, R17
	BRSH       L__Draw_Rectangle312
	JMP        L_Draw_Rectangle120
L__Draw_Rectangle312:
;pcd8544.c,580 :: 		Draw_Pixel(xmin, i, colour);
	PUSH       R20
	PUSH       R17
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	LDD        R4, Y+8
	MOV        R3, R17
	MOV        R2, R20
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R17
	POP        R20
;pcd8544.c,578 :: 		for(i = ymin; i <= ymax; ++i)
	MOV        R16, R17
	SUBI       R16, 255
; i end address is: 17 (R17)
; i start address is: 22 (R22)
	MOV        R22, R16
;pcd8544.c,581 :: 		}
; i end address is: 22 (R22)
	MOV        R17, R22
	JMP        L_Draw_Rectangle119
L_Draw_Rectangle120:
;pcd8544.c,576 :: 		for(; xmin <= xmax; ++xmin)
	MOV        R16, R20
	SUBI       R16, 255
	MOV        R20, R16
;pcd8544.c,582 :: 		}
; xmin end address is: 20 (R20)
	JMP        L_Draw_Rectangle116
L_Draw_Rectangle117:
;pcd8544.c,583 :: 		}
	JMP        L_Draw_Rectangle122
L_Draw_Rectangle111:
;pcd8544.c,587 :: 		Draw_Line(x1, y1, x2, y1, colour);
	PUSH       R9
	PUSH       R8
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R8, R4
	LDD        R16, Y+8
	PUSH       R16
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 1
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R8
	POP        R9
;pcd8544.c,588 :: 		Draw_Line(x1, y2, x2, y2, colour);
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOVW       R4, R8
	LDD        R16, Y+8
	PUSH       R16
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 1
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;pcd8544.c,589 :: 		Draw_Line(x1, y1, x1, y2, colour);
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	MOVW       R6, R2
	LDD        R16, Y+8
	PUSH       R16
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 1
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R4
	POP        R5
	POP        R6
	POP        R7
;pcd8544.c,590 :: 		Draw_Line(x2, y1, x2, y2, colour);
	MOVW       R2, R6
	LDD        R16, Y+8
	PUSH       R16
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 1
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;pcd8544.c,591 :: 		}
L_Draw_Rectangle122:
;pcd8544.c,592 :: 		}
L_end_Draw_Rectangle:
	POP        R3
	POP        R2
	ADIW       R28, 2
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

;pcd8544.c,595 :: 		void Draw_Circle(signed int xc, signed int yc, signed int radius, unsigned char fill, unsigned char colour)
;pcd8544.c,597 :: 		signed int a = 0x0000;
; a start address is: 10 (R10)
	CLR        R10
	CLR        R11
;pcd8544.c,598 :: 		signed int b = 0x0000;
;pcd8544.c,599 :: 		signed int p = 0x0000;
;pcd8544.c,601 :: 		b = radius;
; b start address is: 22 (R22)
	MOVW       R22, R6
;pcd8544.c,602 :: 		p = (1 - b);
	LDI        R16, 1
	LDI        R17, 0
	SUB        R16, R6
	SBC        R17, R7
	STD        Y+0, R16
	STD        Y+1, R17
; b end address is: 22 (R22)
; a end address is: 10 (R10)
	MOVW       R24, R10
;pcd8544.c,604 :: 		do
	JMP        L_Draw_Circle123
L__Draw_Circle212:
;pcd8544.c,633 :: 		}while(a <= b);
	MOVW       R24, R10
;pcd8544.c,604 :: 		do
L_Draw_Circle123:
;pcd8544.c,606 :: 		if(fill != NO)
; b start address is: 22 (R22)
; a start address is: 24 (R24)
	LDI        R27, 0
	CP         R8, R27
	BRNE       L__Draw_Circle314
	JMP        L_Draw_Circle126
L__Draw_Circle314:
;pcd8544.c,608 :: 		Draw_Line((xc - a), (yc + b), (xc + a), (yc + b), colour);
	MOVW       R20, R22
	ADD        R20, R4
	ADC        R21, R5
	MOVW       R18, R24
	ADD        R18, R2
	ADC        R19, R3
	MOVW       R16, R2
	SUB        R16, R24
	SBC        R17, R25
	PUSH       R25
	PUSH       R24
	PUSH       R23
	PUSH       R22
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	PUSH       R9
	MOVW       R6, R18
	MOVW       R4, R20
	MOVW       R2, R16
	MOVW       R8, R20
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 1
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R9
	POP        R22
	POP        R23
	POP        R24
	POP        R25
;pcd8544.c,609 :: 		Draw_Line((xc - a), (yc - b), (xc + a), (yc - b), colour);
	MOVW       R20, R4
	SUB        R20, R22
	SBC        R21, R23
	MOVW       R18, R24
	ADD        R18, R2
	ADC        R19, R3
	MOVW       R16, R2
	SUB        R16, R24
	SBC        R17, R25
	PUSH       R25
	PUSH       R24
	PUSH       R23
	PUSH       R22
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	PUSH       R9
	MOVW       R6, R18
	MOVW       R4, R20
	MOVW       R2, R16
	MOVW       R8, R20
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 1
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R9
	POP        R22
	POP        R23
	POP        R24
	POP        R25
;pcd8544.c,610 :: 		Draw_Line((xc - b), (yc + a), (xc + b), (yc + a), colour);
	MOVW       R20, R24
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
	PUSH       R23
	PUSH       R22
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	PUSH       R9
	MOVW       R6, R18
	MOVW       R4, R20
	MOVW       R2, R16
	MOVW       R8, R20
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 1
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R9
	POP        R22
	POP        R23
	POP        R24
	POP        R25
;pcd8544.c,611 :: 		Draw_Line((xc - b), (yc - a), (xc + b), (yc - a), colour);
	MOVW       R20, R4
	SUB        R20, R24
	SBC        R21, R25
	MOVW       R18, R22
	ADD        R18, R2
	ADC        R19, R3
	MOVW       R16, R2
	SUB        R16, R22
	SBC        R17, R23
	PUSH       R25
	PUSH       R24
	PUSH       R23
	PUSH       R22
	PUSH       R9
	PUSH       R8
	PUSH       R7
	PUSH       R6
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	PUSH       R9
	MOVW       R6, R18
	MOVW       R4, R20
	MOVW       R2, R16
	MOVW       R8, R20
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 1
	OUT        SPL+0, R26
	OUT        SPL+1, R27
	POP        R2
	POP        R3
	POP        R4
	POP        R5
	POP        R6
	POP        R7
	POP        R8
	POP        R9
	POP        R22
	POP        R23
	POP        R24
	POP        R25
;pcd8544.c,612 :: 		}
	JMP        L_Draw_Circle127
L_Draw_Circle126:
;pcd8544.c,615 :: 		Draw_Pixel((xc + a), (yc + b), colour);
	MOV        R17, R4
	ADD        R17, R22
	MOV        R16, R2
	ADD        R16, R24
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R4, R9
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;pcd8544.c,616 :: 		Draw_Pixel((xc + b), (yc + a), colour);
	MOV        R17, R4
	ADD        R17, R24
	MOV        R16, R2
	ADD        R16, R22
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R4, R9
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;pcd8544.c,617 :: 		Draw_Pixel((xc - a), (yc + b), colour);
	MOV        R17, R4
	ADD        R17, R22
	MOV        R16, R2
	SUB        R16, R24
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R4, R9
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;pcd8544.c,618 :: 		Draw_Pixel((xc - b), (yc + a), colour);
	MOV        R17, R4
	ADD        R17, R24
	MOV        R16, R2
	SUB        R16, R22
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R4, R9
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;pcd8544.c,619 :: 		Draw_Pixel((xc + b), (yc - a), colour);
	MOV        R17, R4
	SUB        R17, R24
	MOV        R16, R2
	ADD        R16, R22
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R4, R9
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;pcd8544.c,620 :: 		Draw_Pixel((xc + a), (yc - b), colour);
	MOV        R17, R4
	SUB        R17, R22
	MOV        R16, R2
	ADD        R16, R24
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R4, R9
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;pcd8544.c,621 :: 		Draw_Pixel((xc - a), (yc - b), colour);
	MOV        R17, R4
	SUB        R17, R22
	MOV        R16, R2
	SUB        R16, R24
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R4, R9
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;pcd8544.c,622 :: 		Draw_Pixel((xc - b), (yc - a), colour);
	MOV        R17, R4
	SUB        R17, R24
	MOV        R16, R2
	SUB        R16, R22
	PUSH       R5
	PUSH       R4
	PUSH       R3
	PUSH       R2
	MOV        R4, R9
	MOV        R3, R17
	MOV        R2, R16
	CALL       _Draw_Pixel+0
	POP        R2
	POP        R3
	POP        R4
	POP        R5
;pcd8544.c,623 :: 		}
L_Draw_Circle127:
;pcd8544.c,625 :: 		if(p < 0)
	LDD        R18, Y+0
	LDD        R19, Y+1
	LDI        R16, 0
	LDI        R17, 0
	CP         R18, R16
	CPC        R19, R17
	BRLT       L__Draw_Circle315
	JMP        L_Draw_Circle128
L__Draw_Circle315:
;pcd8544.c,627 :: 		p += (0x03 + (0x02 * a++));
	MOVW       R16, R24
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
	MOVW       R16, R24
	SUBI       R16, 255
	SBCI       R17, 255
; a end address is: 24 (R24)
; a start address is: 10 (R10)
	MOVW       R10, R16
;pcd8544.c,628 :: 		}
; a end address is: 10 (R10)
	JMP        L_Draw_Circle129
L_Draw_Circle128:
;pcd8544.c,631 :: 		p += (0x05 + (0x02 * ((a++) - (b--))));
; a start address is: 24 (R24)
	MOVW       R16, R24
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
	MOVW       R16, R24
	SUBI       R16, 255
	SBCI       R17, 255
; a end address is: 24 (R24)
; a start address is: 10 (R10)
	MOVW       R10, R16
	MOVW       R16, R22
	SUBI       R16, 1
	SBCI       R17, 0
	MOVW       R22, R16
; b end address is: 22 (R22)
; a end address is: 10 (R10)
;pcd8544.c,632 :: 		}
L_Draw_Circle129:
;pcd8544.c,633 :: 		}while(a <= b);
; b start address is: 22 (R22)
; a start address is: 10 (R10)
	CP         R22, R10
	CPC        R23, R11
	BRLT       L__Draw_Circle316
	JMP        L__Draw_Circle212
L__Draw_Circle316:
; b end address is: 22 (R22)
; a end address is: 10 (R10)
;pcd8544.c,634 :: 		}
L_end_Draw_Circle:
	ADIW       R28, 1
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	POP        R29
	POP        R28
	RET
; end of _Draw_Circle

_main:
	LDI        R27, 255
	OUT        SPL+0, R27
	LDI        R27, 0
	OUT        SPL+1, R27
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 22
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;nokia5510_lcd_demo.c,8 :: 		void main()
;nokia5510_lcd_demo.c,10 :: 		unsigned char g = 0;
	PUSH       R2
	PUSH       R3
	PUSH       R4
	PUSH       R5
	PUSH       R6
	PUSH       R7
	PUSH       R8
	PUSH       R9
;nokia5510_lcd_demo.c,14 :: 		signed char c = -9;
	LDI        R27, 247
	STD        Y+15, R27
	LDI        R27, 190
	STD        Y+16, R27
	LDI        R27, 255
	STD        Y+17, R27
	LDI        R27, 10
	STD        Y+18, R27
	LDI        R27, 215
	STD        Y+19, R27
	LDI        R27, 35
	STD        Y+20, R27
	LDI        R27, 189
	STD        Y+21, R27
;nokia5510_lcd_demo.c,15 :: 		signed int i = -66;
;nokia5510_lcd_demo.c,16 :: 		float f = -0.04;
;nokia5510_lcd_demo.c,18 :: 		setup();
	CALL       _setup+0
;nokia5510_lcd_demo.c,20 :: 		PCD8544_backlight_state(ON);
	LDI        R27, 1
	MOV        R2, R27
	CALL       _PCD8544_backlight_state+0
;nokia5510_lcd_demo.c,21 :: 		PCD8544_print_image(mikro_bmp);
	LDI        R27, #lo_addr(_mikro_bmp+0)
	MOV        R2, R27
	LDI        R27, hi_addr(_mikro_bmp+0)
	MOV        R3, R27
	CALL       _PCD8544_print_image+0
;nokia5510_lcd_demo.c,22 :: 		delay_ms(2000);
	LDI        R18, 82
	LDI        R17, 43
	LDI        R16, 0
L_main130:
	DEC        R16
	BRNE       L_main130
	DEC        R17
	BRNE       L_main130
	DEC        R18
	BRNE       L_main130
	NOP
	NOP
	NOP
	NOP
;nokia5510_lcd_demo.c,24 :: 		PCD8544_backlight_state(OFF);
	CLR        R2
	CALL       _PCD8544_backlight_state+0
;nokia5510_lcd_demo.c,25 :: 		delay_ms(2000);
	LDI        R18, 82
	LDI        R17, 43
	LDI        R16, 0
L_main132:
	DEC        R16
	BRNE       L_main132
	DEC        R17
	BRNE       L_main132
	DEC        R18
	BRNE       L_main132
	NOP
	NOP
	NOP
	NOP
;nokia5510_lcd_demo.c,27 :: 		PCD8544_clear_screen(WHITE);
	LDI        R27, 1
	MOV        R2, R27
	CALL       _PCD8544_clear_screen+0
;nokia5510_lcd_demo.c,29 :: 		PCD8544_backlight_state(ON);
	LDI        R27, 1
	MOV        R2, R27
	CALL       _PCD8544_backlight_state+0
;nokia5510_lcd_demo.c,30 :: 		Draw_Rectangle(2, 2, 81, 45, OFF, BLACK);
	LDI        R27, 45
	MOV        R8, R27
	LDI        R27, 0
	MOV        R9, R27
	LDI        R27, 81
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 2
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 2
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	LDI        R27, 0
	PUSH       R27
	LDI        R27, 0
	PUSH       R27
	CALL       _Draw_Rectangle+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 2
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;nokia5510_lcd_demo.c,31 :: 		delay_ms(200);
	LDI        R18, 9
	LDI        R17, 30
	LDI        R16, 229
L_main134:
	DEC        R16
	BRNE       L_main134
	DEC        R17
	BRNE       L_main134
	DEC        R18
	BRNE       L_main134
	NOP
;nokia5510_lcd_demo.c,33 :: 		Draw_Circle(6, 6, 2, ON, BLACK);
	CLR        R9
	LDI        R27, 1
	MOV        R8, R27
	LDI        R27, 2
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
	CALL       _Draw_Circle+0
;nokia5510_lcd_demo.c,34 :: 		delay_ms(200);
	LDI        R18, 9
	LDI        R17, 30
	LDI        R16, 229
L_main136:
	DEC        R16
	BRNE       L_main136
	DEC        R17
	BRNE       L_main136
	DEC        R18
	BRNE       L_main136
	NOP
;nokia5510_lcd_demo.c,35 :: 		Draw_Circle(77, 6, 2, ON, BLACK);
	CLR        R9
	LDI        R27, 1
	MOV        R8, R27
	LDI        R27, 2
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 6
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 77
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	CALL       _Draw_Circle+0
;nokia5510_lcd_demo.c,36 :: 		delay_ms(200);
	LDI        R18, 9
	LDI        R17, 30
	LDI        R16, 229
L_main138:
	DEC        R16
	BRNE       L_main138
	DEC        R17
	BRNE       L_main138
	DEC        R18
	BRNE       L_main138
	NOP
;nokia5510_lcd_demo.c,37 :: 		Draw_Circle(77, 41, 2, ON, BLACK);
	CLR        R9
	LDI        R27, 1
	MOV        R8, R27
	LDI        R27, 2
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 41
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 77
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	CALL       _Draw_Circle+0
;nokia5510_lcd_demo.c,38 :: 		delay_ms(200);
	LDI        R18, 9
	LDI        R17, 30
	LDI        R16, 229
L_main140:
	DEC        R16
	BRNE       L_main140
	DEC        R17
	BRNE       L_main140
	DEC        R18
	BRNE       L_main140
	NOP
;nokia5510_lcd_demo.c,39 :: 		Draw_Circle(6, 41, 2, ON, BLACK);
	CLR        R9
	LDI        R27, 1
	MOV        R8, R27
	LDI        R27, 2
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 41
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 6
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	CALL       _Draw_Circle+0
;nokia5510_lcd_demo.c,40 :: 		delay_ms(200);
	LDI        R18, 9
	LDI        R17, 30
	LDI        R16, 229
L_main142:
	DEC        R16
	BRNE       L_main142
	DEC        R17
	BRNE       L_main142
	DEC        R18
	BRNE       L_main142
	NOP
;nokia5510_lcd_demo.c,42 :: 		Draw_Line(2, 11, 10, 11, BLACK);
	LDI        R27, 11
	MOV        R8, R27
	LDI        R27, 0
	MOV        R9, R27
	LDI        R27, 10
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 11
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 2
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	LDI        R27, 0
	PUSH       R27
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 1
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;nokia5510_lcd_demo.c,43 :: 		Draw_Line(73, 11, 81, 11, BLACK);
	LDI        R27, 11
	MOV        R8, R27
	LDI        R27, 0
	MOV        R9, R27
	LDI        R27, 81
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 11
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 73
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	LDI        R27, 0
	PUSH       R27
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 1
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;nokia5510_lcd_demo.c,44 :: 		delay_ms(200);
	LDI        R18, 9
	LDI        R17, 30
	LDI        R16, 229
L_main144:
	DEC        R16
	BRNE       L_main144
	DEC        R17
	BRNE       L_main144
	DEC        R18
	BRNE       L_main144
	NOP
;nokia5510_lcd_demo.c,45 :: 		Draw_Line(2, 36, 10, 36, BLACK);
	LDI        R27, 36
	MOV        R8, R27
	LDI        R27, 0
	MOV        R9, R27
	LDI        R27, 10
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 36
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 2
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	LDI        R27, 0
	PUSH       R27
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 1
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;nokia5510_lcd_demo.c,46 :: 		Draw_Line(73, 36, 81, 36, BLACK);
	LDI        R27, 36
	MOV        R8, R27
	LDI        R27, 0
	MOV        R9, R27
	LDI        R27, 81
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 36
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 73
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	LDI        R27, 0
	PUSH       R27
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 1
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;nokia5510_lcd_demo.c,47 :: 		delay_ms(200);
	LDI        R18, 9
	LDI        R17, 30
	LDI        R16, 229
L_main146:
	DEC        R16
	BRNE       L_main146
	DEC        R17
	BRNE       L_main146
	DEC        R18
	BRNE       L_main146
	NOP
;nokia5510_lcd_demo.c,48 :: 		Draw_Line(11, 45, 11, 2, BLACK);
	LDI        R27, 2
	MOV        R8, R27
	LDI        R27, 0
	MOV        R9, R27
	LDI        R27, 11
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 45
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 11
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	LDI        R27, 0
	PUSH       R27
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 1
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;nokia5510_lcd_demo.c,49 :: 		Draw_Line(72, 45, 72, 2, BLACK);
	LDI        R27, 2
	MOV        R8, R27
	LDI        R27, 0
	MOV        R9, R27
	LDI        R27, 72
	MOV        R6, R27
	LDI        R27, 0
	MOV        R7, R27
	LDI        R27, 45
	MOV        R4, R27
	LDI        R27, 0
	MOV        R5, R27
	LDI        R27, 72
	MOV        R2, R27
	LDI        R27, 0
	MOV        R3, R27
	LDI        R27, 0
	PUSH       R27
	CALL       _Draw_Line+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 1
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;nokia5510_lcd_demo.c,50 :: 		delay_ms(200);
	LDI        R18, 9
	LDI        R17, 30
	LDI        R16, 229
L_main148:
	DEC        R16
	BRNE       L_main148
	DEC        R17
	BRNE       L_main148
	DEC        R18
	BRNE       L_main148
	NOP
;nokia5510_lcd_demo.c,52 :: 		PCD8544_backlight_state(OFF);
	CLR        R2
	CALL       _PCD8544_backlight_state+0
;nokia5510_lcd_demo.c,53 :: 		delay_ms(400);
	LDI        R18, 17
	LDI        R17, 60
	LDI        R16, 204
L_main150:
	DEC        R16
	BRNE       L_main150
	DEC        R17
	BRNE       L_main150
	DEC        R18
	BRNE       L_main150
;nokia5510_lcd_demo.c,55 :: 		PCD8544_backlight_state(ON);
	LDI        R27, 1
	MOV        R2, R27
	CALL       _PCD8544_backlight_state+0
;nokia5510_lcd_demo.c,57 :: 		for(g = 0; g <= 9; g++)
; g start address is: 25 (R25)
	LDI        R25, 0
; g end address is: 25 (R25)
	MOV        R18, R25
L_main152:
; g start address is: 18 (R18)
	LDI        R16, 9
	CP         R16, R18
	BRSH       L__main318
	JMP        L_main153
L__main318:
;nokia5510_lcd_demo.c,59 :: 		PCD8544_set_cursor((18 + (g * 5)), 2);
	LDI        R16, 5
	MUL        R18, R16
	MOV        R16, R0
	SUBI       R16, 238
	LDI        R27, 2
	MOV        R3, R27
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;nokia5510_lcd_demo.c,60 :: 		PCD8544_print_char(txt1[g], WHITE);
	LDI        R16, #lo_addr(main_txt1_L0+0)
	LDI        R17, hi_addr(main_txt1_L0+0)
	MOV        R30, R18
	LDI        R31, 0
	ADD        R30, R16
	ADC        R31, R17
	LPM        R16, Z
	PUSH       R18
	LDI        R27, 1
	MOV        R3, R27
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
;nokia5510_lcd_demo.c,61 :: 		delay_ms(90);
	LDI        R18, 4
	LDI        R17, 168
	LDI        R16, 12
L_main155:
	DEC        R16
	BRNE       L_main155
	DEC        R17
	BRNE       L_main155
	DEC        R18
	BRNE       L_main155
	NOP
	NOP
	POP        R18
;nokia5510_lcd_demo.c,57 :: 		for(g = 0; g <= 9; g++)
	MOV        R16, R18
	SUBI       R16, 255
; g end address is: 18 (R18)
; g start address is: 25 (R25)
	MOV        R25, R16
;nokia5510_lcd_demo.c,62 :: 		}
	MOV        R18, R25
; g end address is: 25 (R25)
	JMP        L_main152
L_main153:
;nokia5510_lcd_demo.c,64 :: 		for(g = 0; g <= 9; g++)
; g start address is: 18 (R18)
	LDI        R18, 0
; g end address is: 18 (R18)
L_main157:
; g start address is: 18 (R18)
	LDI        R16, 9
	CP         R16, R18
	BRSH       L__main319
	JMP        L_main158
L__main319:
;nokia5510_lcd_demo.c,66 :: 		PCD8544_set_cursor((18 + (g * 5)), 3);
	LDI        R16, 5
	MUL        R18, R16
	MOV        R16, R0
	SUBI       R16, 238
	LDI        R27, 3
	MOV        R3, R27
	MOV        R2, R16
	CALL       _PCD8544_set_cursor+0
;nokia5510_lcd_demo.c,67 :: 		PCD8544_print_char(txt2[g], WHITE);
	LDI        R16, #lo_addr(main_txt2_L0+0)
	LDI        R17, hi_addr(main_txt2_L0+0)
	MOV        R30, R18
	LDI        R31, 0
	ADD        R30, R16
	ADC        R31, R17
	LPM        R16, Z
	PUSH       R18
	LDI        R27, 1
	MOV        R3, R27
	MOV        R2, R16
	CALL       _PCD8544_print_char+0
;nokia5510_lcd_demo.c,68 :: 		delay_ms(90);
	LDI        R18, 4
	LDI        R17, 168
	LDI        R16, 12
L_main160:
	DEC        R16
	BRNE       L_main160
	DEC        R17
	BRNE       L_main160
	DEC        R18
	BRNE       L_main160
	NOP
	NOP
	POP        R18
;nokia5510_lcd_demo.c,64 :: 		for(g = 0; g <= 9; g++)
	MOV        R16, R18
	SUBI       R16, 255
; g end address is: 18 (R18)
; g start address is: 21 (R21)
	MOV        R21, R16
;nokia5510_lcd_demo.c,69 :: 		}
	MOV        R18, R21
; g end address is: 21 (R21)
	JMP        L_main157
L_main158:
;nokia5510_lcd_demo.c,70 :: 		delay_ms(4000);
	LDI        R18, 163
	LDI        R17, 87
	LDI        R16, 3
L_main162:
	DEC        R16
	BRNE       L_main162
	DEC        R17
	BRNE       L_main162
	DEC        R18
	BRNE       L_main162
	NOP
;nokia5510_lcd_demo.c,72 :: 		PCD8544_clear_screen(WHITE);
	LDI        R27, 1
	MOV        R2, R27
	CALL       _PCD8544_clear_screen+0
;nokia5510_lcd_demo.c,74 :: 		PCD8544_print_string(1, 2, "CHR:", WHITE);
	LDI        R27, 67
	STD        Y+0, R27
	LDI        R27, 72
	STD        Y+1, R27
	LDI        R27, 82
	STD        Y+2, R27
	LDI        R27, 58
	STD        Y+3, R27
	LDI        R27, 0
	STD        Y+4, R27
	MOVW       R16, R28
	LDI        R27, 1
	MOV        R6, R27
	MOVW       R4, R16
	LDI        R27, 2
	MOV        R3, R27
	LDI        R27, 1
	MOV        R2, R27
	CALL       _PCD8544_print_string+0
;nokia5510_lcd_demo.c,75 :: 		PCD8544_print_string(1, 3, "INT:", WHITE);
	LDI        R27, 73
	STD        Y+5, R27
	LDI        R27, 78
	STD        Y+6, R27
	LDI        R27, 84
	STD        Y+7, R27
	LDI        R27, 58
	STD        Y+8, R27
	LDI        R27, 0
	STD        Y+9, R27
	MOVW       R16, R28
	SUBI       R16, 251
	SBCI       R17, 255
	LDI        R27, 1
	MOV        R6, R27
	MOVW       R4, R16
	LDI        R27, 3
	MOV        R3, R27
	LDI        R27, 1
	MOV        R2, R27
	CALL       _PCD8544_print_string+0
;nokia5510_lcd_demo.c,76 :: 		PCD8544_print_string(1, 4, "FLT:", WHITE);
	LDI        R27, 70
	STD        Y+10, R27
	LDI        R27, 76
	STD        Y+11, R27
	LDI        R27, 84
	STD        Y+12, R27
	LDI        R27, 58
	STD        Y+13, R27
	LDI        R27, 0
	STD        Y+14, R27
	MOVW       R16, R28
	SUBI       R16, 246
	SBCI       R17, 255
	LDI        R27, 1
	MOV        R6, R27
	MOVW       R4, R16
	LDI        R27, 4
	MOV        R3, R27
	LDI        R27, 1
	MOV        R2, R27
	CALL       _PCD8544_print_string+0
;nokia5510_lcd_demo.c,78 :: 		while(1)
L_main164:
;nokia5510_lcd_demo.c,80 :: 		print_chr(26, 2, c, WHITE);
	LDI        R27, 1
	MOV        R6, R27
	LDD        R4, Y+15
	LDI        R27, 0
	SBRC       R4, 7
	LDI        R27, 255
	MOV        R5, R27
	LDI        R27, 2
	MOV        R3, R27
	LDI        R27, 26
	MOV        R2, R27
	CALL       _print_chr+0
;nokia5510_lcd_demo.c,81 :: 		print_int(26, 3, i, WHITE);
	LDI        R27, 1
	MOV        R8, R27
	LDD        R4, Y+16
	LDD        R5, Y+17
	LDI        R27, 0
	SBRC       R5, 7
	LDI        R27, 255
	MOV        R6, R27
	MOV        R7, R6
	LDI        R27, 3
	MOV        R3, R27
	LDI        R27, 26
	MOV        R2, R27
	CALL       _print_int+0
;nokia5510_lcd_demo.c,82 :: 		print_float(26, 4, f, 2, WHITE);
	LDI        R27, 1
	MOV        R9, R27
	LDI        R27, 2
	MOV        R8, R27
	LDD        R4, Y+18
	LDD        R5, Y+19
	LDD        R6, Y+20
	LDD        R7, Y+21
	LDI        R27, 4
	MOV        R3, R27
	LDI        R27, 26
	MOV        R2, R27
	CALL       _print_float+0
;nokia5510_lcd_demo.c,83 :: 		c++;
	LDD        R16, Y+15
	SUBI       R16, 255
	STD        Y+15, R16
;nokia5510_lcd_demo.c,84 :: 		i++;
	LDD        R16, Y+16
	LDD        R17, Y+17
	SUBI       R16, 255
	SBCI       R17, 255
	STD        Y+16, R16
	STD        Y+17, R17
;nokia5510_lcd_demo.c,85 :: 		f += 0.01;
	LDD        R16, Y+18
	LDD        R17, Y+19
	LDD        R18, Y+20
	LDD        R19, Y+21
	LDI        R20, 10
	LDI        R21, 215
	LDI        R22, 35
	LDI        R23, 60
	CALL       _float_fpadd1+0
	STD        Y+18, R16
	STD        Y+19, R17
	STD        Y+20, R18
	STD        Y+21, R19
;nokia5510_lcd_demo.c,86 :: 		delay_ms(400);
	LDI        R18, 17
	LDI        R17, 60
	LDI        R16, 204
L_main166:
	DEC        R16
	BRNE       L_main166
	DEC        R17
	BRNE       L_main166
	DEC        R18
	BRNE       L_main166
;nokia5510_lcd_demo.c,87 :: 		};
	JMP        L_main164
;nokia5510_lcd_demo.c,88 :: 		}
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

;nokia5510_lcd_demo.c,91 :: 		void setup()
;nokia5510_lcd_demo.c,93 :: 		CLKPR = 0x80;
	PUSH       R2
	LDI        R27, 128
	STS        CLKPR+0, R27
;nokia5510_lcd_demo.c,94 :: 		CLKPR = 0x00;
	LDI        R27, 0
	STS        CLKPR+0, R27
;nokia5510_lcd_demo.c,95 :: 		PORTB = 0x00;
	LDI        R27, 0
	OUT        PORTB+0, R27
;nokia5510_lcd_demo.c,96 :: 		DDRB = 0x00;
	LDI        R27, 0
	OUT        DDRB+0, R27
;nokia5510_lcd_demo.c,97 :: 		PORTC = 0x00;
	LDI        R27, 0
	OUT        PORTC+0, R27
;nokia5510_lcd_demo.c,98 :: 		DDRC = 0x00;
	LDI        R27, 0
	OUT        DDRC+0, R27
;nokia5510_lcd_demo.c,99 :: 		PORTD = 0x00;
	LDI        R27, 0
	OUT        PORTD+0, R27
;nokia5510_lcd_demo.c,100 :: 		DDRD = 0xFC;
	LDI        R27, 252
	OUT        DDRD+0, R27
;nokia5510_lcd_demo.c,101 :: 		TCCR0A = 0x00;
	LDI        R27, 0
	OUT        TCCR0A+0, R27
;nokia5510_lcd_demo.c,102 :: 		TCCR0B = 0x00;
	LDI        R27, 0
	OUT        TCCR0B+0, R27
;nokia5510_lcd_demo.c,103 :: 		TCNT0 = 0x00;
	LDI        R27, 0
	OUT        TCNT0+0, R27
;nokia5510_lcd_demo.c,104 :: 		OCR0A = 0x00;
	LDI        R27, 0
	OUT        OCR0A+0, R27
;nokia5510_lcd_demo.c,105 :: 		OCR0B = 0x00;
	LDI        R27, 0
	OUT        OCR0B+0, R27
;nokia5510_lcd_demo.c,106 :: 		TCCR1A = 0x00;
	LDI        R27, 0
	STS        TCCR1A+0, R27
;nokia5510_lcd_demo.c,107 :: 		TCCR1B = 0x00;
	LDI        R27, 0
	STS        TCCR1B+0, R27
;nokia5510_lcd_demo.c,108 :: 		TCNT1H = 0x00;
	LDI        R27, 0
	STS        TCNT1H+0, R27
;nokia5510_lcd_demo.c,109 :: 		TCNT1L = 0x00;
	LDI        R27, 0
	STS        TCNT1L+0, R27
;nokia5510_lcd_demo.c,110 :: 		ICR1H = 0x00;
	LDI        R27, 0
	STS        ICR1H+0, R27
;nokia5510_lcd_demo.c,111 :: 		ICR1L = 0x00;
	LDI        R27, 0
	STS        ICR1L+0, R27
;nokia5510_lcd_demo.c,112 :: 		OCR1AH = 0x00;
	LDI        R27, 0
	STS        OCR1AH+0, R27
;nokia5510_lcd_demo.c,113 :: 		OCR1AL = 0x00;
	LDI        R27, 0
	STS        OCR1AL+0, R27
;nokia5510_lcd_demo.c,114 :: 		OCR1BH = 0x00;
	LDI        R27, 0
	STS        OCR1BH+0, R27
;nokia5510_lcd_demo.c,115 :: 		OCR1BL = 0x00;
	LDI        R27, 0
	STS        OCR1BL+0, R27
;nokia5510_lcd_demo.c,116 :: 		ASSR = 0x00;
	LDI        R27, 0
	STS        ASSR+0, R27
;nokia5510_lcd_demo.c,117 :: 		TCCR2A = 0x00;
	LDI        R27, 0
	STS        TCCR2A+0, R27
;nokia5510_lcd_demo.c,118 :: 		TCCR2B = 0x00;
	LDI        R27, 0
	STS        TCCR2B+0, R27
;nokia5510_lcd_demo.c,119 :: 		TCNT2 = 0x00;
	LDI        R27, 0
	STS        TCNT2+0, R27
;nokia5510_lcd_demo.c,120 :: 		OCR2A = 0x00;
	LDI        R27, 0
	STS        OCR2A+0, R27
;nokia5510_lcd_demo.c,121 :: 		OCR2B = 0x00;
	LDI        R27, 0
	STS        OCR2B+0, R27
;nokia5510_lcd_demo.c,122 :: 		EICRA = 0x00;
	LDI        R27, 0
	STS        EICRA+0, R27
;nokia5510_lcd_demo.c,123 :: 		EIMSK = 0x00;
	LDI        R27, 0
	OUT        EIMSK+0, R27
;nokia5510_lcd_demo.c,124 :: 		PCICR = 0x00;
	LDI        R27, 0
	STS        PCICR+0, R27
;nokia5510_lcd_demo.c,125 :: 		TIMSK0 = 0x00;
	LDI        R27, 0
	STS        TIMSK0+0, R27
;nokia5510_lcd_demo.c,126 :: 		TIMSK1 = 0x00;
	LDI        R27, 0
	STS        TIMSK1+0, R27
;nokia5510_lcd_demo.c,127 :: 		TIMSK2 = 0x00;
	LDI        R27, 0
	STS        TIMSK2+0, R27
;nokia5510_lcd_demo.c,128 :: 		UCSR0B = 0x00;
	LDI        R27, 0
	STS        UCSR0B+0, R27
;nokia5510_lcd_demo.c,129 :: 		ACSR = 0x80;
	LDI        R27, 128
	OUT        ACSR+0, R27
;nokia5510_lcd_demo.c,130 :: 		ADCSRB = 0x00;
	LDI        R27, 0
	STS        ADCSRB+0, R27
;nokia5510_lcd_demo.c,131 :: 		DIDR1 = 0x00;
	LDI        R27, 0
	STS        DIDR1+0, R27
;nokia5510_lcd_demo.c,132 :: 		ADCSRA = 0x00;
	LDI        R27, 0
	STS        ADCSRA+0, R27
;nokia5510_lcd_demo.c,133 :: 		SPCR = 0x00;
	LDI        R27, 0
	OUT        SPCR+0, R27
;nokia5510_lcd_demo.c,134 :: 		TWCR = 0x00;
	LDI        R27, 0
	STS        TWCR+0, R27
;nokia5510_lcd_demo.c,135 :: 		delay_ms(10);
	LDI        R17, 104
	LDI        R16, 229
L_setup168:
	DEC        R16
	BRNE       L_setup168
	DEC        R17
	BRNE       L_setup168
;nokia5510_lcd_demo.c,137 :: 		PCD8544_init();
	CALL       _PCD8544_init+0
;nokia5510_lcd_demo.c,138 :: 		PCD8544_clear_screen(WHITE);
	LDI        R27, 1
	MOV        R2, R27
	CALL       _PCD8544_clear_screen+0
;nokia5510_lcd_demo.c,139 :: 		}
L_end_setup:
	POP        R2
	RET
; end of _setup
