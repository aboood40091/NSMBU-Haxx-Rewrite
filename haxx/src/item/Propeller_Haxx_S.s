
.global PropellerHaxx__startGlideSound_Hook

PropellerHaxx__startGlideSound_Hook:
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 0xC(r1)

    stfs    f11, 0x74(r31)
    mr      r3, r31
    bl      startGlideSound__13PropellerHaxxCFv

    lwz     r0, 0xC(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
