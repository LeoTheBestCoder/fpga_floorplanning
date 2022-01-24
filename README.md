# CS 516000 FPGA Architecture & CAD Final Project: </br> **Floorplanning for FPGAs with Heterogeneous Resources**

## Project Description
I implement a fixed-outline floorplanner for FPGAs with heterogeneous resources. </br>
For this project, I assume that a FPGA contains two types of logic resources, **CLBs** and **multipliers**, and each module is to be placed in a rectangular region satisfying its resource requirement within the FPGA.  </br>
I want to find a feasible floorplan that all modules must be placed within the given chip area with no overlap.

## Getting Started
1. clone the repository
    ``` bash
    git clone https://github.com/LeoTheBestCoder/fpga_floorplanning
    ```
2. compile the file
    ``` bash
    cd fpga_floorplanning
    cd src
    make clean
    make
    ```
3. execute (remember to replace {CASE_NUM} to a number between 1 ~ 6)
    ``` bash 
    cd ../bin
    ./main ../benchmarks/case{CASE_NUM}.arch ../benchmarks/case{CASE_NUM}.module ../benchmarks/case{CASE_NUM}.net ../outputs/case{CASE_NUM}.floorplan
    ```
4. check the result
    ``` bash
    cd ../outputs
    cat case{CASE_NUM}.floorplan
    ```