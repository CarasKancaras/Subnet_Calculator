#include <iostream>
#include <sstream>
#include <string>
#include <vector>



using namespace std;



//Function to split the address into octets and to store them in a vector
vector<int> split_Address (const string& address){
    vector<int>temp_Address;
    istringstream stream(address);
    string octet;
    while (getline(stream, octet, '.')){
        temp_Address.push_back(stoi(octet));   
    }
return temp_Address;
}



//Function for calculating the network address
vector<int>calculate_NetworkAddress(const vector<int>& ip_Segments, const vector<int>& mask_Segments){
    vector<int> network_Address;
    for(size_t i = 0; i < ip_Segments.size(); i++){
        network_Address.push_back(ip_Segments[i] & mask_Segments[i]);
    }
return network_Address;
}



//Function for calculating the broadcast address
vector<int>calculate_BroadcastAddress(const vector<int>& network_Address, const vector<int>& mask_Segments){
    vector<int> broadcast_Address;
    for (size_t i = 0; i < network_Address.size(); i++) {
        int inverted_Mask = 255 - mask_Segments[i];
        broadcast_Address.push_back(network_Address[i] + inverted_Mask);
    }
return broadcast_Address;
}



// Function for calculating the first usable IP address
vector<int> calculate_FirstUsableIP(const vector<int>& network_Address) {
    vector<int> first_UsableIP = network_Address;
    first_UsableIP[3]++;
return first_UsableIP;
}



// Function for calculating last usable IP address
vector<int> calculate_LastUsableIP(const vector<int>& broadcast_Address) {
    vector<int> last_UsableIP = broadcast_Address;
    last_UsableIP[3]--;
return last_UsableIP;
}



//Function for displaying an address
void display_Address(const string& text, const vector<int>& address) {
    cout << text;
    for (size_t i = 0; i < address.size(); i++) {
        cout << address[i];
        if (i < 3) {
            cout << ".";
        }
    }
    cout << endl;
}


int main(){
 
    string ip_Address;
    string subnet_Mask;
    int choice;



    cout<< "Enter the IP address: ";
    cin>> ip_Address;
    


    cout<< "Enter the Subnet Mask: ";
    cin>>  subnet_Mask;



    //First of all, the IP address and the Subnet mask needs to be split into octects so that it could be stored into a vectors as integers.
    vector<int> ip_Segments =split_Address(ip_Address) ; //function to split the octects
    vector<int> mask_Segments = split_Address(subnet_Mask) ; //function to split the octects



    // Menu for selecting what to calculate
     do {
        cout << "Select what to display:"<<endl;
        cout << "1. Network address"<<endl;
        cout << "2. Broadcast address"<<endl;
        cout << "3. First usable IP address"<<endl;
        cout << "4. Last usable IP address"<<endl;
        cout << "5. All"<<endl;
        cout << "6. Change IP Address and Subnet Mask"<<endl;
        cout << "7. Exit"<<endl;
        cout << "Enter your choice: "<<endl;
        cin >> choice;

        switch (choice) {
            case 1: {
                vector<int> network_Address = calculate_NetworkAddress(ip_Segments, mask_Segments);
                display_Address("Network address is: ", network_Address);
                break;
            }

            case 2: {
                vector<int> network_Address = calculate_NetworkAddress(ip_Segments, mask_Segments);
                vector<int> broadcast_Address = calculate_BroadcastAddress(network_Address, mask_Segments);
                display_Address("Broadcast address is: ", broadcast_Address);
                break;
            }

            case 3: {
                vector<int> network_Address = calculate_NetworkAddress(ip_Segments, mask_Segments);
                vector<int> first_UsableIP = calculate_FirstUsableIP(network_Address);
                display_Address("First usable IP address is: ", first_UsableIP);
                break;
            }

            case 4: {
                vector<int> network_Address = calculate_NetworkAddress(ip_Segments, mask_Segments);
                vector<int> broadcast_Address = calculate_BroadcastAddress(network_Address, mask_Segments);
                vector<int> last_UsableIP = calculate_LastUsableIP(broadcast_Address);
                display_Address("Last usable IP address is: ", last_UsableIP);
                break;
            }

            case 5: {
                vector<int> network_Address = calculate_NetworkAddress(ip_Segments, mask_Segments);
                vector<int> broadcast_Address = calculate_BroadcastAddress(network_Address, mask_Segments);
                vector<int> first_UsableIP = calculate_FirstUsableIP(network_Address);
                vector<int> last_UsableIP = calculate_LastUsableIP(broadcast_Address);
                display_Address("Network address is: ", network_Address);
                display_Address("Broadcast address is: ", broadcast_Address);
                display_Address("First usable IP address is: ", first_UsableIP);
                display_Address("Last usable IP address is: ", last_UsableIP);
                break;
            }

            case 6:
                cout << "Enter new IP Address: ";
                cin >> ip_Address;
                cout << "Enter new Subnet Mask: ";
                cin >> subnet_Mask;

                ip_Segments = split_Address(ip_Address);
                mask_Segments = split_Address(subnet_Mask);

                cout << "IP Address and Subnet Mask changed!!!." << endl;
                break;

            case 7:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } 
    while (choice != 7);


return 0;
}
