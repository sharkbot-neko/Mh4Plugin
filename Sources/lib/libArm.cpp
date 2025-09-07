#include "lib/libArm.hpp"
#include <CTRPluginFramework.hpp>

namespace arm11 {

    Arm::Arm(uint32_t baseAddr) : base(baseAddr) {}

    void Arm::Add(Reg rd, Reg rn, Reg rm) {
        uint32_t instr = 0xE0800000;
        instr |= (rn << 16) | (rd << 12) | rm;
        code.push_back(instr);
    }

    void Arm::Sub(Reg rd, Reg rn, Reg rm) {
        uint32_t instr = 0xE0400000; // SUB
        instr |= (rn << 16) | (rd << 12) | rm;
        code.push_back(instr);
    }

    void Arm::Mov(Reg rd, Reg rm) {
        uint32_t instr = 0xE1A00000; // MOV Rd, Rm
        instr |= (rd << 12) | rm;
        code.push_back(instr);
    }

    void Arm::MovImm(Reg rd, uint32_t imm) {
        // 即値MOVは 8bit rotate encoding (0-255, rotate可)
        // とりあえず単純に imm < 256 のみ対応
        if (imm > 255) {
            return;
        }
        uint32_t instr = 0xE3A00000; // MOV Rd, #imm
        instr |= (rd << 12) | (imm & 0xFF);
        code.push_back(instr);
    }

    void Arm::Cmp(Reg rn, Reg rm) {
        uint32_t instr = 0xE1500000; // CMP Rn, Rm
        instr |= (rn << 16) | rm;
        code.push_back(instr);
    }

    void Arm::Bx(Reg rm) {
        uint32_t instr = 0xE12FFF10; // BX Rm
        instr |= rm;
        code.push_back(instr);
    }

    void Arm::Push(uint16_t regList) {
        uint32_t instr = 0xE92D0000; // STMFD SP!, {reglist}
        instr |= regList;
        code.push_back(instr);
    }

    void Arm::Pop(uint16_t regList) {
        uint32_t instr = 0xE8BD0000; // LDMFD SP!, {reglist}
        instr |= regList;
        code.push_back(instr);
    }

    void Arm::B(uint32_t target) {
        uint32_t pc = base + code.size() * 4;
        int32_t offset = (int32_t(target) - int32_t(pc + 8)) >> 2;
        uint32_t instr = 0xEA000000;  // B (AL)
        instr |= (offset & 0x00FFFFFF);
        code.push_back(instr);
    }

    void Arm::BL(uint32_t target) {
        uint32_t pc = base + code.size() * 4;
        int32_t offset = (int32_t(target) - int32_t(pc + 8)) >> 2;
        uint32_t instr = 0xEB000000;  // BL (AL)
        instr |= (offset & 0x00FFFFFF);
        code.push_back(instr);
    }

    void Arm::Write(const std::function<void(Arm&)>& fn) {
        fn(*this);
    }

    void Arm::Flush() {
        if (code.empty()) return;
        CTRPluginFramework::Process::Patch(base, code.data(), code.size() * sizeof(uint32_t));
    }

}