
.global ActorBgCollisionCheck_entry

ActorBgCollisionCheck_entry:
    mr        r3, r28

    lmw       r21, 0xC(r1)
    lfs       f31, 0x40(r1)
    lfd       f31, 0x38(r1)
    isync
    lwz       r0, 0x4C(r1)
    mtspr     LR, r0
    addi      r1, r1, 0x48

    b         ActorBgCollisionCheckMgr_entry
