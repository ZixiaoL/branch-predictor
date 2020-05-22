#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <string>
#include <bitset>
using namespace std;


bitset<8> update_bhr(bitset<8> bhr, bool taken, int k) {
	if (k == 0)return bhr;
	string imm = bhr.to_string();
	imm.insert(8 - k, taken ? "1" : "0");
	imm = imm.substr(0, k);
	return bitset<8>(imm);
}

bool predict(bitset<8> bhr, unsigned long pc, vector<vector<bitset<2>>> saturatingCounters) {
	string imm = saturatingCounters[bhr.to_ulong()][pc].to_string();
	if (imm[0] == '1') {
		return true;
	}
	return false;
}

void update_saturatingCounters(bitset<8> bhr, unsigned long pc, bool taken, vector<vector<bitset<2>>> saturatingCounters) {
	string imm = saturatingCounters[bhr.to_ulong()][pc].to_string();
	if (taken) {
		if (imm == "11") {

		}
		else if (imm == "10") {
			saturatingCounters[bhr.to_ulong()][pc] = bitset<2>("11");
		}
		else if (imm == "00") {
			saturatingCounters[bhr.to_ulong()][pc] = bitset<2>("01");
		}
		else {
			saturatingCounters[bhr.to_ulong()][pc] = bitset<2>("11");
		}
	}
	else {
		if (imm == "11") {
			saturatingCounters[bhr.to_ulong()][pc] = bitset<2>("10");
		}
		else if (imm == "10") {
			saturatingCounters[bhr.to_ulong()][pc] = bitset<2>("00");
		}
		else if (imm == "00") {

		}
		else {
			saturatingCounters[bhr.to_ulong()][pc] = bitset<2>("00");
		}
	}
}
int main(int argc, char** argv) {
	ifstream config;
	config.open(argv[1]);

	int m, k;
	config >> m >> k;

	config.close();

	ofstream out;
	string out_file_name = string(argv[2]) + ".out";
	out.open(out_file_name.c_str());

	ifstream trace;
	trace.open(argv[2]);

	vector<vector<bitset<2>>> saturatingCounters(pow(2, k), vector<bitset<2>>(pow(2, m), bitset<2>("11")));

	bitset<8> bhr;

	for (int i = 0; i < k; i++) {
		bhr.set(8 - i - 1, 1);
	}

	while (!trace.eof()) {
		unsigned long pc; bool taken;
		trace >> std::hex >> pc >> taken;
		bool prediction;
		prediction = true;
		bhr = update_bhr(bhr, taken, k);
		prediction = predict(bhr, pc, saturatingCounters);
		update_saturatingCounters(bhr, pc, taken, saturatingCounters);
		out << prediction;
	}

	trace.close();
	out.close();
}