#pragma once
#include <cstdint>
#include <vector>
#include <functional>
#include <CTRPluginFramework.hpp>

namespace arm11 {

enum Reg {
    R0=0, R1, R2, R3, R4, R5, R6, R7,
    R8, R9, R10, R11, R12, SP, LR, PC
};

class Arm {
public:
    Arm(uint32_t baseAddr);

    // ---- 基本命令 ----
    void Add(Reg rd, Reg rn, Reg rm);       // rd = rn + rm
    void Sub(Reg rd, Reg rn, Reg rm);       // rd = rn - rm
    void Mov(Reg rd, Reg rm);               // rd = rm
    void MovImm(Reg rd, uint32_t imm);      // rd = #imm (0-255など制限あり)
    void Cmp(Reg rn, Reg rm);               // cmp rn, rm
    void Bx(Reg rm);                        // bx rm
    void Push(uint16_t regList);            // push {rlist}
    void Pop(uint16_t regList);             // pop {rlist}
    void B(uint32_t target);     // 無条件分岐
    void BL(uint32_t target);    // サブルーチン呼び出し

    // ---- DSL ----
    void Write(const std::function<void(Arm&)>& fn);

    // メモリへ反映
    void Flush();

    const std::vector<uint32_t>& GetCode() const { return code; }

private:
    uint32_t base;
    std::vector<uint32_t> code;
};

} 