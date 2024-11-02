#include <stdio.h>
#include <sqlite3.h>
#include <hiddenframe_headers.h>
#include <iostream>
#include <stdexcept>

int main(){
    sqlite3 *db=nullptr;
    try{
        db=createDB();
        createNewUser(db,"Pat", "password");
        //test authentications
        bool auth1=authenticateUser(db,"NotPat","password");
        bool auth2=authenticateUser(db,"Pat","passw0rd");
        bool auth3=authenticateUser(db,"Pat","password");
        if (!auth1 && !auth2 && auth3){
            std::cout<< "Authorized a user correctly!" << std::endl;
        }
        else{
            std::cerr<< "Authentication was not OK! Test of UAC FAILED" << std::endl;
        }
    }
    catch (const std::runtime_error& e){
        std::cerr<<e.what() << std::endl;
    }
    sqlite3_close(db);
    return 0;
}