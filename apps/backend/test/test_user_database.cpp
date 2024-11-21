#include <boost/test/unit_test.hpp>
#include <hiddenframe_headers.h>
#include <sqlite3.h>
#include <iostream>
#include <stdexcept>

BOOST_AUTO_TEST_SUITE(UserDatabaseTestSuite)

BOOST_AUTO_TEST_CASE(TestCreateAndAuthenticateUser)
{
    try
    {
        sqlite3 *db = createDB("bin/test/database/testuserdatabase.db");
        createNewAdmin(db, "amitoj", "meow");
        BOOST_CHECK_THROW(createNewAdmin(db, "amitoj", "notmeow"), std::runtime_error);

        // Test authentications
        bool auth1 = authenticateUser(db, "NotPat", "meow");
        bool auth2 = authenticateUser(db, "amitoj", "me0w");
        bool auth3 = authenticateUser(db, "amitoj", "meow");

        BOOST_CHECK(!auth1);
        BOOST_CHECK(!auth2);
        BOOST_CHECK(auth3);

        if (!auth1 && !auth2 && auth3)
        {
            BOOST_TEST_MESSAGE("Authorized a user correctly!");
        }
        else
        {
            BOOST_FAIL("Authentication was not OK! Test of UAC FAILED");
        }

        int id1 = createInvite(db, "amitoj");
        int id2 = createInvite(db, "amitoj");
        int id3 = createInvite(db, "amitoj");
        createNewUser(db, "1", "p1", id1);
        createNewUser(db, "2", "p2", id2);
        createNewUser(db, "3", "p3", id3);
        BOOST_CHECK_THROW(createNewUser(db, "4", "p4", 0000), std::runtime_error);
        BOOST_TEST_MESSAGE("Created new users successfully!");
        if (db != nullptr){
            closeDB(db);
        }
    }
    catch (const std::runtime_error &e)
    {
        BOOST_FAIL(e.what());
    }
}

BOOST_AUTO_TEST_SUITE_END()