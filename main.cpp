#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <curl/curl.h>

//#include "request.h"

using namespace std;

class Request {
private:
    string container;
    string hostname;
    string endpoint;

public:
    void display();
    string get();

    Request(string c)
    {
        container = c;
        hostname = "https://en.cppreference.com/w/cpp/";
        endpoint = hostname + container;
    }
};

void Request::display()
{
    cout << "Printing container from Request class" << container << endl;
}

size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string Request::get()
{
    curl_global_init(CURL_GLOBAL_ALL);

    CURL* curl = curl_easy_init();

    string readBuffer;
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, endpoint.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_perform(curl);

        cout << readBuffer << endl;
    }
    return readBuffer;
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cout << "Please provide more information " << endl;
        return -1;
    }
    else{
        Request r(argv[1]);
        r.display();
    }

    return 0;
}
