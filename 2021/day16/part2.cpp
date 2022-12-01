#include <climits>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

#define ull unsigned long long

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    string hexdec; cin >> hexdec;
    ostringstream oss;
    for(char &c : hexdec)
        switch(c) {
            case '0': oss << "0000"; break;
            case '1': oss << "0001"; break;
            case '2': oss << "0010"; break;
            case '3': oss << "0011"; break;
            case '4': oss << "0100"; break;
            case '5': oss << "0101"; break;
            case '6': oss << "0110"; break;
            case '7': oss << "0111"; break;
            case '8': oss << "1000"; break;
            case '9': oss << "1001"; break;
            case 'A': oss << "1010"; break;
            case 'B': oss << "1011"; break;
            case 'C': oss << "1100"; break;
            case 'D': oss << "1101"; break;
            case 'E': oss << "1110"; break;
            case 'F': oss << "1111"; break;
        }
    string binary = oss.str();
    int binary_length = binary.size();

    function<pair<int, ull>(int)> sum_versions = [&](int index) {
        ull value = 0;
        index+=3;
        int type_id = stoi(binary.substr(index, 3), 0, 2);
        index+=3;
        vector<ull> sub_packets;
        if(type_id == 4) {
            ostringstream oss;
            while(binary[index] != '0') {
                oss << binary.substr(index+1, 4);
                index += 5;
            }
            oss << binary.substr(index+1, 4);
            index += 5;
            value = stol(oss.str(), 0, 2);
        } else if(binary[index++] == '0') {
            int length = stoi(binary.substr(index, 15), 0, 2);
            index += 15;
            int offset = index;
            while(offset < index + length) {
                pair<int, ull> sub_packet = sum_versions(offset);
                sub_packets.push_back(sub_packet.second);
                offset = sub_packet.first;
            }
            index = offset;
        } else {
            int packets = stoi(binary.substr(index, 11), 0, 2);
            index += 11;
            for(int i = 0; i < packets; ++i) {
                pair<int, ull> sub_packet = sum_versions(index);
                sub_packets.push_back(sub_packet.second);
                index = sub_packet.first;
            }
        }
        switch(type_id) {
            case 0: // SUM
                for(auto &i : sub_packets) value += i; break;
            case 1: // PRODUCT
                value = 1;
                for(auto &i : sub_packets) value *= i; break;
            case 2: // MIN
                value = LONG_MAX;
                for(auto &i : sub_packets) value = min(value, i); break;
            case 3: // MAX
                value = 0;
                for(auto &i : sub_packets) value = max(value, i); break;
            case 4: break;
            case 5: // GT
                value = sub_packets[0] > sub_packets[1]; break;
            case 6: // LT
                value = sub_packets[0] < sub_packets[1]; break;
            case 7: // EQ
                value = sub_packets[0] == sub_packets[1]; break;
        }
        return make_pair(index, value);
    };
    cout << sum_versions(0).second << "\n";
    return 0;
}