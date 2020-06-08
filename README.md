## __Release v1.0.1__
#### Doesn't really do much other that implement at skeleton version of the ARM CPU present in the GBA as well as the beginnings of a prototype debugger.


## __Release v1.0.2__
##### Current goal for v1.0.2 release is proper recognition and parsing of opcodes which should set me up for handling the implementation of the opcodes themselves.
### Tasks:

- [40%] Finish implementing ARM 32-bit instruction set
- [40%] Implement IPC between DBA and DBA_Debugger (Probably shared memory model)
- [60%] Decode .gba opcodes for translation phase
    - [21/21] Recognize specific ARM7TDMI opcodes
    
    - [8/21] Properly parse each opcode for arguments and flags
- [10%] Cleanup and improve CMake process to use Conan (potentially not necessary given that the project doesn't have many 3rd party libraries)
### Changelog v1.0.2

- Changed how ALU functions work, no longer pass register and immediate flag, now just pass the data in and have the callee function properly pass in data.

### Table of tasks, intended release version of task, and progress

| Task | Release Version | Progress |
| ---- | ----------------|----------|
| Implement the opcodes listed in ARM documentation + GBATEK| v1.0.3| 30%|
| Add communication between DBA and DBA-Debugger| v1.0.3 | 40%|
| Recognize all opcodes in Pokemon Emerald | v1.0.2 | 100%|
| Parse all opcodes for arguments, flags, and conditions | v1.0.2 | 50% |
