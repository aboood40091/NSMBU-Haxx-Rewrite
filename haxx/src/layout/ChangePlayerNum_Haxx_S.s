
.global ChangePlayerNumHaxx_LoadInstToR3
.global ChangePlayerNumHaxx_LoadInstToR29
.global ChangePlayerNumHaxx_LoadIsCharacterTakenArrIntoR6
.global ChangePlayerNumHaxx_LoadBtnLoopNoConnectFrameInfoF1
.global ChangePlayerNumHaxx_LoadIsCharacterTakenArrIntoR12
.global ChangePlayerNumHaxx_LoadPlayerCharacterNoMiiArrIntoR12
.global ChangePlayerNumHaxx_LoadIsVisibleIntoR0

ChangePlayerNumHaxx_LoadInstToR3:
    lis   r3, sInstance__19ChangePlayerNumHaxx@ha
    lwz   r3, sInstance__19ChangePlayerNumHaxx@l(r3)
    blr

ChangePlayerNumHaxx_LoadInstToR29:
    lis   r29, sInstance__19ChangePlayerNumHaxx@ha
    lwz   r29, sInstance__19ChangePlayerNumHaxx@l(r29)
    blr

ChangePlayerNumHaxx_LoadIsCharacterTakenArrIntoR6:
    lis   r6, sInstance__19ChangePlayerNumHaxx@ha
    lwz   r6, sInstance__19ChangePlayerNumHaxx@l(r6)
    addi  r6, r6, 0x5A58
    b     ChangePlayerNumBtn_HandleTakenCharacter_Continue

ChangePlayerNumHaxx_LoadBtnLoopNoConnectFrameInfoF1:
    lis   r5, sInstance__19ChangePlayerNumHaxx@ha
    lwz   r5, sInstance__19ChangePlayerNumHaxx@l(r5)
    addi  r5, r5, 0x7FFC
    lfs   f1, 0x3798(r5)
    blr

ChangePlayerNumHaxx_LoadIsCharacterTakenArrIntoR12:
    lis   r12, sInstance__19ChangePlayerNumHaxx@ha
    lwz   r12, sInstance__19ChangePlayerNumHaxx@l(r12)
    addi  r12, r12, 0x5A58
    b     ChangePlayerNumBtn_IsCharacterTaken_Continue

ChangePlayerNumHaxx_LoadPlayerCharacterNoMiiArrIntoR12:
    lis   r12, sInstance__19ChangePlayerNumHaxx@ha
    lwz   r12, sInstance__19ChangePlayerNumHaxx@l(r12)
    addi  r12, r12, 0x5A48
    b     ChangePlayerNumBtn_InitializeState_PostDecide_Continue

ChangePlayerNumHaxx_LoadIsVisibleIntoR0:
    lis   r11, sInstance__19ChangePlayerNumHaxx@ha
    lwz   r11, sInstance__19ChangePlayerNumHaxx@l(r11)
    addi  r11, r11, 0x7FFC
    lbz   r0, 0x379E(r11)
    b     CourseSelectMenu_ExecuteState_ChangePlayerNum_Continue
