; @file: project1.asm
; @authors: Vincent Allen, Sam Itchner, Dakota Ewigman
; @date: 3/31/2014
;
; @registers:
; R0 - Bits 0 thru 4 track previous button states each iteration.
;    - Bit 7 tracks whether or not the 4 bit value R3 turned over.
; R3 - Count stored here (4 bit)
; R1 - Least significant counter for delay
; R2 - Most significant counter for delay
; R4 - Oscilator counter

;==========================================================================
;                                                                 MAIN LOOP
;==========================================================================
                    ORG 0
                    
                    MOV 0xA4, #0	; Set Port 2 to bi-directional
            	    MOV 0x91, #0	; Set Port 1 to bi-directional
            	    MOV 0x84, #0	; Set Port 0 to bi-directional
                    
                    MOV R0, #0      ; R0.7: no turn over, R0.0-R0.4: not pressed 
                    MOV R3, #0      ; Count set to 0
                    
MainLoop:           LCALL CheckIncBtn
                    LCALL CheckDecBtn
                    LCALL CheckVincesBtn
                    LCALL CheckSamsBtn
                    LCALL CheckDakotasBtn
                    LCALL PostProcessing
                    SJMP MainLoop

;==========================================================================
;                                                 PRE, POST, and BTN CHECKS
;==========================================================================

;-----------------------------------------------
; @name: CheckIncBtn
; @brief: If button is being held down, set the
;         state to 1. Else check if was set to 1
;         last iteration. If so, it was just
;         released and we need to increment,
;         update LEDs, the duration of the alarm
;         and set the state to 0 (for this btn).
;-----------------------------------------------
CheckIncBtn:        MOV A, R0
                    JB  P0.1, IncNotPressed     ; If pressed:
                        SETB ACC.0              ;     Change state to pressed
                        MOV R0, A
                        SJMP CheckIncBtnRET
IncNotPressed:      NOP                         ; For consistant frequency between clock cycles
                    NOP
                    JNB ACC.0, CheckIncBtnRET   ; Else, if not pressed last check:
                        CLR ACC.0               ;     Change state to released
                        MOV R0, A
                        LCALL IncMethod         ;     Increment counter
                        LCALL CheckForTurnOver  ;     If turned over, R0.7 set, else clr
                        LCALL SetLEDs           ;     Update LEDs
CheckIncBtnRET:     RET

;-----------------------------------------------
; @name: CheckDecBtn
;-----------------------------------------------
CheckDecBtn:        MOV A, R0
                    JB  P0.3, DecNotPressed
                        SETB ACC.1
                        MOV R0, A
                        SJMP CheckDecBtnRET
DecNotPressed:      NOP
                    NOP
                    JNB ACC.1, CheckDecBtnRET
                        CLR ACC.1
                        MOV R0, A
                        LCALL DecMethod
                        LCALL CheckForTurnOver
                        LCALL SetLEDs
CheckDecBtnRET:     RET

;-----------------------------------------------
; @name: CheckVincesBtn
;-----------------------------------------------
CheckVincesBtn:     MOV A, R0
                    JB  P0.2, VincesNotPressed
                        SETB ACC.2
                        MOV R0, A
                        SJMP CheckVincesBtnRET
VincesNotPressed:   NOP
                    NOP
                    JNB ACC.2, CheckVincesBtnRET
                        CLR ACC.2
                        MOV R0, A
                        LCALL VincesMethod
                        LCALL CheckForTurnOver
                        LCALL SetLEDs
CheckVincesBtnRET:  RET

;-----------------------------------------------
; @name: CheckSamsBtn
;-----------------------------------------------
CheckSamsBtn:       MOV A, R0
                    JB  P1.4, SamsNotPressed
                        SETB ACC.3
                        MOV R0, A
                        SJMP CheckSamsBtnRET
SamsNotPressed:     NOP
                    NOP
                    JNB ACC.3, CheckSamsBtnRET
                        CLR ACC.3
                        MOV R0, A
                        LCALL SamsMethod
                        LCALL CheckForTurnOver
                        LCALL SetLEDs
CheckSamsBtnRET:    RET

;-----------------------------------------------
; @name: CheckDakotasBtn
;-----------------------------------------------
CheckDakotasBtn:    MOV A, R0
                    JB  P0.2, DakotasNotPressed
                        SETB ACC.4
                        MOV R0, A
                        SJMP CheckDakotasBtnRET
DakotasNotPressed:  NOP
                    NOP
                    JNB ACC.4, CheckDakotasBtnRET
                        CLR ACC.4
                        MOV R0, A
                        LCALL DakotasMethod
                        LCALL CheckForTurnOver
                        LCALL SetLEDs
CheckDakotasBtnRET: RET

;-----------------------------------------------
; @name: PostProcessing
;-----------------------------------------------
PostProcessing:     RET
                    
;==========================================================================
;                                                             OTHER METHODS
;==========================================================================

;-----------------------------------------------
; @name: SetLEDs
; @brief: Sets the LEDs to represent Register 3
;-----------------------------------------------
SetLEDs:     
                    MOV A,R3
                    CPL A        ; Account for active low
                    MOV C,ACC.3
                    MOV P2.4,C
                    MOV C,ACC.2
                    MOV P2.7,C
                    MOV C,ACC.1
                    MOV P2.5,C
                    MOV C,ACC.0
                    MOV P2.6,C
                    RET 

;-----------------------------------------------
; @name: IncMethod
; @brief: Increments Register 3
;-----------------------------------------------
IncMethod:          INC R3
                    RET

;-----------------------------------------------
; @name: DecMethod
; @brief: Decrements Register 3
;-----------------------------------------------
DecMethod:          DEC R3
                    RET

;-----------------------------------------------
; @name: VincesMethod
; @brief: Flip the bits of the current counter
;         value (R3)
;-----------------------------------------------
VincesMethod:       MOV A, R3
                    CPL ACC.0
                    CPL ACC.1
                    CPL ACC.2
                    CPL ACC.3
                    MOV R3, A
                    RET

;-----------------------------------------------
; @name: SamsMethod
; @brief: Clears Acumulator, Register R3, Register R0
;-----------------------------------------------
SamsMethod:         
                    MOV A,0
                    MOV R3,A
                    RET

;-----------------------------------------------
; @name: DakotasMethod
;-----------------------------------------------
DakotasMethod:      RET ; Just a placeholder for now

;-----------------------------------------------
; @name: CheckForTurnOver
; @brief: If operation casued turn over, set
;         R0.7 to 1. Else to 0. Clear R3.4 thru R3.7
;-----------------------------------------------
CheckForTurnOver:   
                    MOV A,R3
                    MOV B,R0
                    CLR B.7         ; default to no overflow
                    JNB ACC.4,Over  ; if R3.4 is 0, jump to Over
                    SETB B.7
                    CLR ACC.4       ; clear excess bits
                    CLR ACC.5
                    CLR ACC.6
                    CLR ACC.7
                    MOV R3,A
Over:                    
                    JNB ACC.7,Under ; if R3.7 is 0, jump to Under
                    SETB B.7
                    CLR ACC.4
                    CLR ACC.5
                    CLR ACC.6
                    CLR ACC.7
                    MOV R3,A
Under:                    
                    MOV R0,B
                    RET
             
                    
                    
                    
;-----------------------------------------------
; @name: Delay
; @brief: Oscilate the speaker between on and
;               off for a brief period of time
;-----------------------------------------------                    
Delay:
;                     MOV A,R1
;                     JZ ChkR2
                    
;                     MOV A,R4
                    
;                     JNZ OscDec
;                     DEC R1
;                     CMP P1.7
;                     MOV R4 #32
                    
; OscDec:             DEC R4
;                     SJMP DelayRet
                    
; ChkR2:              MOV A,R2
                    
;                     JZ DelayEnd
;                     DEC R2
;                     MOV R1, #0FF;
;                     SJMP Delay
; DelayEnd:
;                     CLR P1.7
; DelayRet:           
                    RET
                    
                    
                    
                    
end        
                    
                    
                    
                    
                    
                    
                    
