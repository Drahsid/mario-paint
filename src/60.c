#include "common.h"

void func_80000460(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80000468.s")

void func_80000994(void) {
    func_80101454();
    D_8019360C = 1;
    func_80134F28(0);
}

void func_800009C8(int arg0, int arg1) {
}

void func_800009D4(void) {
    func_8011BFE8();
}

// OK except arg0 usage at the bottom should use v1, not v0
#ifdef NON_MATCHING
void func_800009F4(func_800009F4_a0* arg0) {
    uint32_t sp24;
    func_800009F4_a0_0x20* sp20;
    func_800009F4_a0_0x20* sp1C;

    sp20 = arg0->unk_0x20;
    sp24 = sp20->unk_0x04;
    sp1C = func_8011BDFC(sp24, 0);
    func_8017D3B0(sp20, sp1C);
    func_8011BEC8(sp20);
    arg0->unk_0x20 = sp1C;
    arg0->unk_0x24 = (uint32_t)sp1C + sp24;
    func_8011BB00(arg0->unk_0x04, sp1C);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/60/func_800009F4.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80000A60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80000AF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80000B6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80000B98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80000C18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80000C88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80000CB4.s")

void func_80000D24(void) {
    while (func_80135C40() == 0) {
        func_80101498();
        func_80135518();
    }
    func_8016A2E0(5);
}

int32_t func_80000D74(int32_t arg0) {
    func_8016A2E0(4);
    func_80100818(arg0);
    func_80100924();
    return 0;
}

int32_t func_80000DAC(int32_t arg0) {
    func_8016A2E0(4);
    func_80100888(arg0);
    func_80100924();
    return 0;
}

int32_t func_80000DE4(int32_t arg0, int32_t arg1) {
    func_8016A2E0(4);
    func_801008B4(arg0, arg1);
    func_80100924();
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80000E24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80000E9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80000F18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80000F50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80000F9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80000FCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_800010B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_800010EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80001120.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80001170.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_800011D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_800011EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80001200.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80001280.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_800012FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_800013B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_800013DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80001478.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80001518.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80001634.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_800016B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_800016F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80001750.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_8000175C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80001768.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_800017A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80001854.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80001898.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80001904.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80001954.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80001994.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_800019F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80001A40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80001A8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80001AD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80001B3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/60/func_80001B6C.s")
