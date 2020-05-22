# Branch Predictor
This is a correlating branch predictor that makes use of 2-bit saturating counters. You are provided with a text file containing a trace of branch instructions consisting of the PC at which each branch occurs, and whether the branch is Taken or Not Taken. 
The code is to evaluate the performance of a correlating branch predictor on this trace. Output file indicates, for each branch in the trace, whether it was predicted as Taken or Not Taken. 
## Branch Predictor Architecture
The design consists of 2m+k 2-bit saturating counters indexed using m LSBs of each branch instruction and a k bit Branch History Register (BHR) that records the outcomes of the previous k branches. Each 2-bit saturating predictor starts in the 11 (Predict Taken with High Confidence) state and is updated as per the finite state machine. Further, the BHR is initialized assuming the previous k branches were Taken.  
The values of m and k are specified in a config file config.txt. 
The maximum values of m = 20 and k = 8.
## Config File
The config file config.txt contains a single line with the value of m and k. A sample file for m=12 and k=2 is provided.
## Trace File
The trace file, trace.txt, contains one branch per line. Each line has the PC for the corresponding branch (in hex format) followed by a single bit indicating Taken (1) or Not Taken (0). A sample trace file is provided.  A sample trace file is provided.
## Output Format
The output is a file trace.out that has one line per branch. Each line has a single bit which indicates whether that branch was predicted as Taken (1) or Not Taken (0).
## compile the source code
g++ -o branchsimulator_skeleton.out branchsimulator_skeleton.cpp
## execute with config & trace file
./branchsimulator_skeleton.out config.txt trace.txt
