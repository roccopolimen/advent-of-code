#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

using namespace std;

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

    function<pair<int, int>(int)> sum_versions = [&](int index) {
        int version_sum = 0;
        int version = stoi(binary.substr(index, 3), 0, 2);
        index+=3;
        version_sum += version;
        int type_id = stoi(binary.substr(index, 3), 0, 2);
        index+=3;
        if(type_id == 4) {
            while(binary[index] != '0') index += 5;
            index += 5;
        } else if(binary[index++] == '0') {
            int length = stoi(binary.substr(index, 15), 0, 2);
            index += 15;
            int offset = index;
            while(offset < index + length) {
                pair<int, int> sub_packet = sum_versions(offset);
                version_sum += sub_packet.second;
                offset = sub_packet.first;
            }
            index = offset;
        } else {
            int sub_packets = stoi(binary.substr(index, 11), 0, 2);
            index += 11;
            for(int i = 0; i < sub_packets; ++i) {
                pair<int, int> sub_packet = sum_versions(index);
                version_sum += sub_packet.second;
                index = sub_packet.first;
            }
        }
        return make_pair(index, version_sum);
    };
    cout << sum_versions(0).second << "\n";
    return 0;
}