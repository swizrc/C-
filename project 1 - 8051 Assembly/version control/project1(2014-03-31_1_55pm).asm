; @file: project1.asm
; @authors: Vincent Allen, Sam Itchner, Dakota Ewigman
; @date: 3/31/2014
;
; @registers:
; R0 - Bits track previous button states each iteration
; R3 - Count stored here

;=============================================
;                                    MAIN LOOP
;=============================================
MainLoop:           LCALL PreProcessing
                    LCALL CheckIncBtn
                    LCALL CheckDecBtn
                    LCALL CheckVincesBtn
                    LCALL CheckSamsBtn
                    LCALL CheckDakotasBtn
                    LCALL PostProcessing
                    SJMP MainLoop

;=============================================
;                    PRE, POST, and BTN CHECKS
;=============================================

;-----------------------
; @name: PreProcessing
;-----------------------
PreProcessing:      RET

;-----------------------
; @name: CheckIncBtn
;-----------------------
CheckIncBtn:        JNB P0.1, IncNotPressed     ; If pressed:
                        SETB R0.0               ;     Change state to pressed
                        SJMP CheckIncBtnRET     ;     Skip to next button
IncNotPressed:      JNB R0.0, CheckIncBtnRET    ; Else, if not pressed last check:
                        LCALL IncMethod         ;     Increment counter
                        LCALL SetStateMethod    ;     Update LEDs, alarm
                        CLR R0.0                ;     Change state to released
CheckIncBtnRET:     RET

;-----------------------
; @name: CheckDecBtn
;-----------------------
CheckDecBtn:        JNB P0.3, DecNotPressed
                        SETB R0.1
                        SJMP CheckDecBtnRET
DecNotPressed:      JNB R0.1, CheckDecBtnRET
                        LCALL DecMethod
                        LCALL SetStateMethod
                        CLR R0.1
CheckDecBtnRET:     RET

;-----------------------
; @name: CheckVincesBtn
;-----------------------
CheckVincesBtn:     JNB P0.2, VincesNotPressed
                        SETB R0.2
                        SJMP CheckVincesBtnRET
VincesNotPressed:   JNB R0.2, CheckVincesBtnRET
                        LCALL VincesMethod
                        LCALL SetStateMethod
                        CLR R0.2
CheckVincesBtnRET:  RET

;-----------------------
; @name: CheckSamsBtn
;-----------------------
CheckSamsBtn:       JNB P1.4, SamsNotPressed
                        SETB R0.3
                        SJMP CheckSamsBtnRET
SamsNotPressed:     JNB R0.3, CheckSamsBtnRET
                        LCALL SamsMethod
                        LCALL SetStateMethod
                        CLR R0.3
CheckSamsBtnRET:    RET

;-----------------------
; @name: CheckDakotasBtn
;-----------------------
CheckDakotasBtn:    JNB P0.2, DakotasNotPressed
                        SETB R0.4
                        SJMP CheckDakotasBtnRET
DakotasNotPressed:  JNB R0.4, CheckDakotasBtnRET
                        LCALL DakotasMethod
                        LCALL SetStateMethod
                        CLR R0.4
CheckDakotasBtnRET: RET

;-----------------------
; @name: PostProcessing
;-----------------------
PostProcessing:     RET
                    
;=============================================
;                       INC, DEC, USER METHODS
;=============================================

;-----------------------
; @name: SetStateMethod
;-----------------------
SetStateMethod:     RET ; Just a placeholder for now

;-----------------------
; @name: IncMethod
;-----------------------
IncMethod:          RET ; Just a placeholder for now

;-----------------------
; @name: DecMethod
;-----------------------
DecMethod:          RET ; Just a placeholder for now

;-----------------------
; @name: VincesMethod
; @brief: 
;-----------------------
VincesMethod:       CPL R3.0
                    CPL R3.1
                    CPL R3.2
                    CPL R3.3
                    RET

;-----------------------
;@name: SamsMethod
;-----------------------
SamsMethod:         RET ; Just a placeholder for now

;-----------------------
; @name: DakotasMethod
;-----------------------
DakotasMethod:      RET ; Just a placeholder for now

;=============================================
;                           MISC OTHER METHODS
;=============================================



