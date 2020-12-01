#include "pug.hh"
/* GCC: g++ -g vm.cc -o vm1 */
int main() {
    using namespace PugVM;

    // Recursive faculty program.
    int res = 5;
    std::vector<Instruction> program{{LoadInt, &res},  // +1
                                     {Call, 5},
                                     {PopReduce},
                                     {StoreInt, &res},
                                     {Exit},

                                     // fac(x)
                                     {LoadArg, 0},
                                     {PushInt, 1},
                                     {NotEqualsII},
                                     {JumpRelIfTrue, 3},
                                     {PushInt, 1},
                                     {ReturnTos},

                                     {LoadArg, 0},
                                     {DecrementI},
                                     {Call, 5},
                                     {PopReduce},
                                     {LoadArg, 0},
                                     {MulII},
                                     {ReturnTos}};

    /*
    // Iterative faculty program.
    std::vector<Instruction> program{
        {LoadInt, &res},  // [local 0]
        {Dup},            // [local 1] duplicate input to be used as counter

        // start of while loop
        {Dup},              // \
        {PushInt,1},        // | compare counter to 1
        {EqualsII},         // /      \
        {JumpRelIfTrue, 7}, //      quit if counter is 1

        {DecrementI},

        {LoadLocal, 0},
        {LoadLocal, 1},
        {MulII},
        {StoreLocal, 0},
        {Jump, 2},
        // loop end

        {Pop},
        {StoreInt, &res},
        {Exit}
    };*/

    PugVM::StackMachine<true> m(program);
    while (!m.halted()) {
        m.tick();
    }
    std::cout << "res: " << res << std::endl;
}
