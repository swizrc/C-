; @file: project1.asm
; @authors: Vincent Allen, Sam Itchner, Dakota Ewigman
; @date: 3/31/2014
;
; @registers:
; R0 - Bits 0 thru 4 track previous button states each iteration.
;    - Bit 7 tracks whether or not there was overflow from operation.
; R3 - Count stored here

;==========================================================================
;                                                                 MAIN LOOP
;==========================================================================
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
CheckIncBtn:        JNB P0.1, IncNotPressed     ; If pressed:
                        SETB R0.0               ;     Change state to pressed
                        SJMP CheckIncBtnRET     ;     Skip to next button
IncNotPressed:      NOP                         ; (added delay - consistent frequency)
                    JNB R0.0, CheckIncBtnRET    ; Else, if not pressed last check:
                        LCALL IncMethod         ;     Increment counter
                        LCALL CheckForOverflow  ;     If overflow, R0.7 set, else clr
                        LCALL SetStateMethod    ;     Update LEDs, alarm
                        CLR R0.0                ;     Change state to released
CheckIncBtnRET:     RET

;-----------------------------------------------
; @name: CheckDecBtn
;-----------------------------------------------
CheckDecBtn:        JNB P0.3, DecNotPressed
                        SETB R0.1
                        SJMP CheckDecBtnRET
DecNotPressed:      NOP
                    JNB R0.1, CheckDecBtnRET
                        LCALL DecMethod
                        LCALL CheckForOverflow
                        LCALL SetStateMethod
                        CLR R0.1
CheckDecBtnRET:     RET

;-----------------------------------------------
; @name: CheckVincesBtn
;-----------------------------------------------
CheckVincesBtn:     JNB P0.2, VincesNotPressed
                        SETB R0.2
                        SJMP CheckVincesBtnRET
VincesNotPressed:   NOP
                    JNB R0.2, CheckVincesBtnRET
                        LCALL VincesMethod
                        LCALL CheckForOverflow
                        LCALL SetStateMethod
                        CLR R0.2
CheckVincesBtnRET:  RET

;-----------------------------------------------
; @name: CheckSamsBtn
;-----------------------------------------------
CheckSamsBtn:       JNB P1.4, SamsNotPressed
                        SETB R0.3
                        SJMP CheckSamsBtnRET
SamsNotPressed:     NOP
                    JNB R0.3, CheckSamsBtnRET
                        LCALL SamsMethod
                        LCALL CheckForOverflow
                        LCALL SetStateMethod
                        CLR R0.3
CheckSamsBtnRET:    RET

;-----------------------------------------------
; @name: CheckDakotasBtn
;-----------------------------------------------
CheckDakotasBtn:    JNB P0.2, DakotasNotPressed
                        SETB R0.4
                        SJMP CheckDakotasBtnRET
DakotasNotPressed:  NOP
                    JNB R0.4, CheckDakotasBtnRET
                        LCALL DakotasMethod
                        LCALL CheckForOverflow
                        LCALL SetStateMethod
                        CLR R0.4
CheckDakotasBtnRET: RET

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
VincesMethod:       CPL R3.0
                    CPL R3.1
                    CPL R3.2
                    CPL R3.3
                    RET

;-----------------------------------------------
; @name: SamsMethod
; @brief: Clears Acumulator, Register R3, Register R0
;-----------------------------------------------
SamsMethod:         
                    MOV R3,0
                    MOV R0,0
                    MOV A,0
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
                    CLR R0.7
                    JNB ACC.4,Over
                    SETB R0.7
                    CLR ACC.4
                    CLR ACC.5
                    CLR ACC.6
                    CLR ACC.7
                    MOV R3,A
Over:                    
                    JNB ACC.7,Under
                    SETB R0.7
                    CLR ACC.4
                    CLR ACC.5
                    CLR ACC.6
                    CLR ACC.7
                    MOV R3,A
Under:                    
                    RET ;
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
