#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "Database.hpp"
#include "list.hpp"
#include "binary_search_tree.hpp"

struct Entry {
    std::string title;
    std::string author;
    int pubYear;
};


TEST_CASE("Test Construction", "[construction]") {
    Database<std::string> testdb;

    REQUIRE(testdb.isEmpty());
}


TEST_CASE("Test Add", "[add]") {
    Database<std::string> testdb;
    std::string e1 = "entry";

    testdb.add("key1", "key2", e1);
    REQUIRE(!testdb.isEmpty());
    REQUIRE(testdb.contains("key1"));
    REQUIRE(testdb.contains("key2"));
}


TEST_CASE("Test Duplicate Add", "[duplicate add]") {
    Database<std::string> testdb;
    std::string e1 = "entry";
    
    testdb.add("key1", "key2", e1);
    REQUIRE(!testdb.add("key1", "key2", e1));
}


TEST_CASE("Test Retrieve", "[retrieve]") {
    Database<std::string> testdb;
    std::string e1 = "entry";

    testdb.add("key1", "key2", e1);
    
    REQUIRE(testdb.getValue("key1") == e1);
    REQUIRE(testdb.getValue("key2") == e1);
}


TEST_CASE("Test Add 2", "[add 2]") {
    Database<std::string> testdb;
    std::string e1 = "entry1";
    std::string e2 = "entry2";
    
    testdb.add("key1a", "key1b", e1);
    testdb.add("key2a", "key2b", e2);

    REQUIRE(testdb.getNumberOfEntries() == 2);

    REQUIRE(testdb.getValue("key1a") == e1);
    REQUIRE(testdb.getValue("key1b") == e1);
    REQUIRE(testdb.getValue("key2a") == e2);
    REQUIRE(testdb.getValue("key2b") == e2);
}


TEST_CASE("Test Remove", "[remove]") {
    Database<std::string> testdb;
    std::string e1 = "entry";

    testdb.add("key1", "key2", e1);
    
    testdb.remove("key1");
    REQUIRE(!testdb.contains("key1"));
    REQUIRE(!testdb.contains("key2"));

    testdb.add("key1", "key2", e1);
    
    testdb.remove("key2");
    REQUIRE(!testdb.contains("key1"));
    REQUIRE(!testdb.contains("key2"));

    REQUIRE(testdb.isEmpty());
}


TEST_CASE("Test Copy Construct", "[copy]") {
    Database<std::string> testdb;
    std::string e1 = "entry";

    testdb.add("key1", "key2", e1);

    Database<std::string> testdb_copy(testdb);

    REQUIRE(testdb_copy.getValue("key1") == e1);
    REQUIRE(testdb_copy.getValue("key2") == e1); 
}


TEST_CASE("Test Copy Assign", "[copy assign]") {
    Database<std::string> testdb;
    std::string e1 = "entry";

    testdb.add("key1", "key2", e1);

    Database<std::string> testdb_copy;

    testdb_copy = testdb;

    REQUIRE(testdb_copy.getValue("key1") == e1);
    REQUIRE(testdb_copy.getValue("key2") == e1); 
}


TEST_CASE("Test Entry Types", "[entry type]") {
    Database<Entry> testdb;

    Entry e1;
    std::string isbn1 = "000-0-00-000000-1";
    std::string catalog_id1 = "0000001";
    e1.title = "The Winds of Winter";
    e1.author = "George R. R. Martin";
    e1.pubYear = 2031;

    testdb.add(isbn1, catalog_id1, e1);

    Entry e2;

    std::string isbn2 = "000-0-00-000000-2";
    std::string catalog_id2 = "0000002";
    e1.title = "A Dream of Spring";
    e1.author = "George R. R. Martin";
    e1.pubYear = 2032;

    testdb.add(isbn2, catalog_id2, e2);

    // TODO
    
}

TEST_CASE("test list class", "[list]") {
    List<int> l, l2;
    
    for(int i = 1; i <= 100; i++)
        REQUIRE(l.insert(i, i));

    for(int i = 1; i <= 100; i++)
        REQUIRE(l.getEntry(i) == i);

    l2 = l;
    for(int i = 1; i <= 100; i++)
        REQUIRE(l2.getEntry(i) == i);

    for(int i = 1; i <= 10; i++)
        l.setEntry(i, i + 1);

    for(int i = 1; i <= 10; i++)
        REQUIRE(l.getEntry(i) == i + 1);

    for(int i = 100; i > 0; i--)
        REQUIRE(l.remove(i));

    REQUIRE(l.isEmpty());
}

TEST_CASE("test binary search tree", "[bst]") {
    BinarySearchTree<std::string, int> bst;
    REQUIRE(bst.insert("key", 1));

    BinarySearchTree<std::string, int> testdb;
    std::string e1 = "entry";

    testdb.insert("key1", 1);
    testdb.remove("key1");

    int item;
    REQUIRE(!testdb.retrieve("key1", item));

    testdb.insert("key3", 3); 
    testdb.remove("key3");

    REQUIRE(!testdb.retrieve("key3", item));

    REQUIRE(testdb.isEmpty());
}

TEST_CASE("test getAllEntries", "[getAllEntries]") {
    Database<std::string> testdb;
    std::string e1 = "entry1";
    std::string e2 = "entry2";
    
    testdb.add("key1a", "key1b", e1);
    testdb.add("key2a", "key2b", e2);
}

