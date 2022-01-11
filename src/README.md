# CS 5160 FPGA Final Project
## Title
Floorplanning for FPGAs with Heterogeneous Resources

## Execution
```
g++ main.cpp
```
```
./a.out case{i}.arch case{i}.module case{i}.net case{i}.floorplan
```
**Remember to replace {i} with the case number!**
## Verification
```
./verifier benchmarks/case{i}.arch benchmarks/case{i}.module benchmarks/case{i}.net outputs/case{i}.floorplan
```