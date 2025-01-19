#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Function
void subnet_Calculator(const string& ip_address, const string& subnet_Mask)
{
    // Divide ip address and subnetMask into segments.
    vector<int> ip_Segments;
    vector<int> mask_Segments;

    istringstream ip_Stream(ip_address); // Create a string stream for the entire address
    istringstream mask_Stream(subnet_Mask); // Create a string stream for the entire subnet mask
    string ip_Part;
    string mask_Part;

    while (getline(ip_Stream, ip_Part, '.')) {
        int part;
        istringstream partStream(ip_Part); // Create a string stream for each part
        partStream >> part; // Extract integer from the stream
        ip_Segments.push_back(part);
    }

    while (getline(mask_Stream, mask_Part, '.')) {
        int part;
        istringstream partStream(mask_Part); // Create a string stream for each part
        partStream >> part; // Extract integer from the stream
        mask_Segments.push_back(part);
    }

    // Calculate network address
    vector<int> network_Address;
    for (size_t i = 0; i < ip_Segments.size(); i++) {
        network_Address.push_back(ip_Segments[i] & mask_Segments[i]);
    }

    // Calculate broadcast address
    vector<int> broadcast_Address;
    for (size_t i = 0; i < ip_Segments.size(); i++) {
        int inverted_Mask = 255 - mask_Segments[i]; // Calculate host bits for this octet
        broadcast_Address.push_back(network_Address[i] + inverted_Mask);
    }

    // Calculate first and last usable ip addresses
    vector<int> first_UsableIP = network_Address;
    vector<int> last_UsableIP = broadcast_Address;
    
    // Add and divide by 1 from first and last usable IP addresses
    first_UsableIP[3]++;
    last_UsableIP[3]--;

    // Display the network address
    cout << "Network address is: ";
    for (int i = 0; i < 4; i++) {
        cout << network_Address[i];
        if (i < 3) {
            cout << ".";
        }
    }
    cout << endl;

    //Display the Broadcast address
    cout << "Broadcast address is: ";
    for (int i = 0; i < 4; i++) {
        cout << broadcast_Address[i];
        if (i < 3) {
            cout << ".";
        }

    }
    cout << endl;

    //Display first usable ip address
    cout << "First usable IP address is: ";
    for (int i = 0; i < 4; i++){
        cout << first_UsableIP[i];
        if (i < 3) {
            cout << ".";
        }
    }
    cout << endl;

    //Display last usable ip address
    cout << "Last usable IP address is: ";
    for (int i = 0; i < 4; i++){
        cout << last_UsableIP[i];
        if (i < 3) {
            cout << ".";
        }
    }
    cout << endl;
}


int main()
{
    string ip_address; 
    string subnet_Mask;

    cout << "Enter IP Address: ";
    cin >> ip_address;

    cout << "Enter Subnet Mask: ";
    cin >> subnet_Mask;
    
    subnet_Calculator(ip_address, subnet_Mask);
    return 0;
}
