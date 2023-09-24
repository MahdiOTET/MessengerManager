#include <string>
#include <iostream>
#include <stdlib.h>
#include <curl/curl.h>
#pragma warning (disable:4996)

using namespace std;
int isURLSafe(char);
char* urlEncode(const char*);
int main(int argc, char* argv[])
{
    
    //Curl declarations
    CURLcode ret;
    CURL* hnd;
    curl_mime* mime1;
    curl_mimepart* part1;
    long httpCode;
    //telegram declarations
    string telegramApiEndpoint = "https://api.telegram.org/bot";
    string telegramBotToken = "6351217913:AAEIptkNU78Zz2f9IyZlTIR2ZSm_S9eFVEg/";
    string telegramChannelId = "-1001831605308&";
    string query = telegramApiEndpoint.append(telegramBotToken).append("sendPhoto?");
    //eitaa decelarions
    string eitaaFileEndpoint = "https://eitaayar.ir/api/bot206108:0cf4e8e7-1300-4999-966d-7e2f4e13e849/sendFile?";
    string chat_id = "chat_id=Test_channell&caption=";
    string caption = u8"آزمایشگاه پژوهشی فضای سایبر";

    string encoded = urlEncode(caption.c_str());
    eitaaFileEndpoint.append(chat_id).append(encoded);

    hnd = curl_easy_init();
    //curl_easy_setopt(hnd, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(hnd, CURLOPT_URL, eitaaFileEndpoint.c_str());
    mime1 = curl_mime_init(hnd);
    part1 = curl_mime_addpart(mime1);
    curl_mime_filedata(part1, "C:/Users/MahdiOTET/Desktop/Img.jpg");
    curl_mime_name(part1, "file");
    curl_easy_setopt(hnd, CURLOPT_MIMEPOST, mime1);
 
    ret = curl_easy_perform(hnd);
    curl_easy_getinfo(hnd, CURLINFO_RESPONSE_CODE, &httpCode);
    cout << "Response code =>   " << httpCode << endl;

    curl_easy_reset(hnd);

    curl_easy_setopt(hnd, CURLOPT_URL, (query.append("chat_id="+telegramChannelId).append("caption="+encoded)).c_str());
    curl_mime_filedata(part1, "C:/Users/MahdiOTET/Desktop/Img.jpg");
    curl_mime_name(part1, "photo");
    curl_easy_setopt(hnd, CURLOPT_MIMEPOST, mime1);

    ret = curl_easy_perform(hnd);
    curl_easy_getinfo(hnd, CURLINFO_RESPONSE_CODE, &httpCode);
    cout << "Response code =>   " << httpCode << endl;


    curl_easy_cleanup(hnd);
    curl_mime_free(mime1);
    
    return (int)ret;
    
}

// Function to check if a character is URL safe
int isURLSafe(char ch) {
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') ||
        ch == '-' || ch == '_' || ch == '.' || ch == '~') {
        return 1;
    }
    return 0;
}

// Function to URL encode a UTF-8 string
char* urlEncode(const char* str) {
    size_t len = strlen(str); // Length of the input string
    char* encoded = (char*)malloc(3 * len + 1); // Allocate memory for the encoded string

    size_t j = 0; // Index for the encoded string

    for (size_t i = 0; i < len; i++) {
        if (isURLSafe(str[i])) {
            encoded[j++] = str[i]; // Append safe characters as is
        }
        else {
            // Encode unsafe characters
            sprintf(encoded + j, "%%%02X", (unsigned char)str[i]);
            j += 3;
        }
    }

    encoded[j] = '\0'; // Null-terminate the encoded string
    return encoded;
}

