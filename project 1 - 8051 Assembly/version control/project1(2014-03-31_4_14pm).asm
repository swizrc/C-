; @file: project1.asm
; @authors: Vincent Allen, Sam Itchner, Dakota Ewigman
; @date: 3/31/2014
;
; @registers:
; R0 - Bits 0 thru 4 track previous button states each iteration.
;    - Bit 7 tracks whether or not there was overflow from operation.
; R3 - Count stored here
; R1 - Least significant counter for delay
; R2 - Most significant counter for delay
; R4 - Oscilator counter

;==========================================================================
;                                                                 MAIN LOOP
;==========================================================================
                    ORG 0
                    
                    mov 0xA4,#0		; set Port 2 to bi-directional
            	    mov 0x91,#0		; set Port 1 to bi-directional
            	    mov 0x84,#0		; set Port 0 to bi-directional
                    
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
                    JNB P0.1, IncNotPressed     ; If pressed:
                        SETB ACC.0              ;     Change state to pressed
                        SJMP CheckIncBtnRET     ;     Skip to next button
IncNotPressed:      NOP                         ; (added delay - consistent frequency)
                    JNB ACC.0, CheckIncBtnRET   ; Else, if not pressed last check:
                        LCALL IncMethod         ;     Increment counter
                        LCALL CheckForOverflow  ;     If overflow, R0.7 set, else clr
                        LCALL SetStateMethod    ;     Update LEDs, alarm
                        CLR ACC.0               ;     Change state to released
CheckIncBtnRET:     MOV R0, A
                    RET

;-----------------------------------------------
; @name: CheckDecBtn
;-----------------------------------------------
CheckDecBtn:        MOV A, R0
                    JNB P0.3, DecNotPressed
                        SETB ACC.1
                        SJMP CheckDecBtnRET
DecNotPressed:      NOP
                    JNB ACC.1, CheckDecBtnRET
                        LCALL DecMethod
                        LCALL CheckForOverflow
                        LCALL SetStateMethod
                        CLR ACC.1
CheckDecBtnRET:     MOV R0, A
                    RET

;-----------------------------------------------
; @name: CheckVincesBtn
;-----------------------------------------------
CheckVincesBtn:     MOV A, R0
                    JNB P0.2, VincesNotPressed
                        SETB ACC.2
                        SJMP CheckVincesBtnRET
VincesNotPressed:   NOP
                    JNB ACC.2, CheckVincesBtnRET
                        LCALL VincesMethod
                        LCALL CheckForOverflow
                        LCALL SetStateMethod
                        CLR ACC.2
CheckVincesBtnRET:  MOV R0, A
                    RET

;-----------------------------------------------
; @name: CheckSamsBtn
;-----------------------------------------------
CheckSamsBtn:       MOV A, R0
                    JNB P1.4, SamsNotPressed
                        SETB ACC.3
                        SJMP CheckSamsBtnRET
SamsNotPressed:     NOP
                    JNB ACC.3, CheckSamsBtnRET
                        LCALL SamsMethod
                        LCALL CheckForOverflow
                        LCALL SetStateMethod
                        CLR ACC.3
CheckSamsBtnRET:    MOV R0, A
                    RET

;-----------------------------------------------
; @name: CheckDakotasBtn
;-----------------------------------------------
CheckDakotasBtn:    MOV A, R0
                    JNB P0.2, DakotasNotPressed
                        SETB ACC.4
                        SJMP CheckDakotasBtnRET
DakotasNotPressed:  NOP
                    JNB ACC.4, CheckDakotasBtnRET
                        LCALL DakotasMethod
                        LCALL CheckForOverflow
                        LCALL SetStateMethod
                        CLR ACC.4
CheckDakotasBtnRET: MOV R0, A
                    RET

;-----------------------------------------------
; @name: PostProcessing
;-----------------------------------------------
PostProcessing:     RET
                    
;==========================================================================
;                                                             OTHER METHODS
;==========================================================================

;-----------------------------------------------
; @name: SetStateMethod
; @brief: Sets the LEDs to represent Register 3
;-----------------------------------------------
SetStateMethod:     
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
; @name: CheckForOverflow
; @brief: If overflow from operation, set R0.7
;         to 1. Else to 0. Clear R3.4 thru R3.7
;-----------------------------------------------
CheckForOverflow:   
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
                    MOV A,R1
                    JZ ChkR2
                    
                    MOV A,R4
                    
                    JNZ OscDec
                    DEC R1
                    CMP P1.7
                    MOV R4 #32
                    
OscDec:             DEC R4
                    SJMP DelayRet
                    
ChkR2:              MOV A,R2
                    
                    JZ DelayEnd
                    DEC R2
                    MOV R1, #0FF;
                    SJMP Delay
DelayEnd:
                    CLR P1.7
DelayRet:           
                    RET
                    
                    
                    
                    
end        
                    
                    
                    
                    
                    
                    
                    
