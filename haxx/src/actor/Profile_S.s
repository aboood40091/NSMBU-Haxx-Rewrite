
.global SpriteToProfileList_r3
.global SpriteToProfileList_r3_2
.global SpriteToProfileList_r19
.global SpriteToProfileList_r22
.global SpriteToProfileList_r24
.global SpriteToProfileList_r26
.global SpriteToProfileList_r30
.global SpriteToProfileList_r31
.global loadNumProfiles_r29
.global loadNumProfiles_r30

SpriteToProfileList_r3:
    addis     r7, r12, cProfileID__12MapActorHaxx@ha
    lwz       r3, cProfileID__12MapActorHaxx@l(r7)
    blr

SpriteToProfileList_r3_2:
    addis     r8, r10, cProfileID__12MapActorHaxx@ha
    addi      r3, r8, cProfileID__12MapActorHaxx@l
    blr

SpriteToProfileList_r19:
    lis       r19, cProfileID__12MapActorHaxx@ha
    addi      r19, r19, cProfileID__12MapActorHaxx@l
    blr

SpriteToProfileList_r22:
    lis       r22, cProfileID__12MapActorHaxx@ha
    addi      r22, r22, cProfileID__12MapActorHaxx@l
    blr

SpriteToProfileList_r24:
    lis       r24, cProfileID__12MapActorHaxx@ha
    addi      r24, r24, cProfileID__12MapActorHaxx@l
    blr

SpriteToProfileList_r26:
    lis       r26, cProfileID__12MapActorHaxx@ha
    addi      r26, r26, cProfileID__12MapActorHaxx@l
    blr

SpriteToProfileList_r30:
    lis       r30, cProfileID__12MapActorHaxx@ha
    addi      r30, r30, cProfileID__12MapActorHaxx@l
    blr

SpriteToProfileList_r31:
    lis       r31, cProfileID__12MapActorHaxx@ha
    addi      r31, r31, cProfileID__12MapActorHaxx@l
    blr

loadNumProfiles_r29:
    mflr      r0
    addi      r1, r1, -0x20
    stw       r0, 0x24(r1)

    mr        r30, r3
    bl        getProfileNumAll__11ProfileHaxxSFv
    mr        r29, r3
    mr        r3, r30

    lwz       r0, 0x24(r1)
    addi      r1, r1, 0x20
    mtlr      r0
    blr

loadNumProfiles_r30:
    mflr      r0
    addi      r1, r1, -0x20
    stw       r0, 0x24(r1)

    mr        r29, r3
    bl        getProfileNumAll__11ProfileHaxxSFv
    mr        r30, r3
    mr        r3, r29

    lwz       r0, 0x24(r1)
    addi      r1, r1, 0x20
    mtlr      r0
    blr
