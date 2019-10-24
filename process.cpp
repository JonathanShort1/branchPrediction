#include <bits/stdc++.h>
using namespace std;

struct branch {
    int taken;
    int total;
};

void process(const char *filename, const char *csv_file)
{
    ifstream infile(filename);
    ifstream csv(csv_file);
    map<uint64_t, branch> m;
    typedef map<uint64_t, branch>::iterator It;

    int mask = 0x0000ffff;

    uint64_t addr;
    uint64_t taken;
    uint64_t index;
    while (infile >> addr >> taken) {
        index = addr & mask;
        if (m.find(addr) == m.end()) {
            branch b;
            b.taken = 0;
            b.total = 0;
            m.emplace(addr, b);
        }

        It it = m.find(addr);
        if (taken) {
            it->second.taken += 1;
        }
        it->second.total += 1;
    }
    infile.close();

    ofstream out("process.csv");
    out << "addr,taken,total,bias" << endl;
    for (auto const& x : m) {
        double acc = static_cast<double>(x.second.taken) / static_cast<double>(x.second.total);
        if (0 <= acc && acc <= 0.05 || 0.95 <= acc && acc <= 1) {
            out << x.first << "," << x.second.taken << "," << x.second.total << "," << 0 << endl;
        } else {
            out << x.first << "," << x.second.taken << "," << x.second.total << "," << 1 <<endl;
        }
    }
    out.close();
}

int main(int argc, char *argv[]) 
{
    if (argc == 3) {
        process(argv[1], argv[2]);
    }
}