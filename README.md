## __Release v1.0.1__
#### Doesn't really do much other that implement at skeleton version of the ARM CPU present in the GBA as well as the beginnings of a prototype debugger.


## __Release v1.0.2__
### Tasks:
- [20%] Finish implementing ARM 32-bit instruction set

- [40%] Implement IPC between DBA and DBA_Debugger (Probably shared memory model)
- [30%] Decode .gba opcodes for translation phase
    - [33%] Recognize specific ARM7TDMI opcodes
    
    - [ 0%] Properly parse each opcode for arguments and flags
- [10%] Cleanup and improve CMake process to use Conan (potentially not necessary given that the project doesn't have many 3rd party libraries)