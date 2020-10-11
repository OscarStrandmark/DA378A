#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
//#include <stdlib.h>
#include <crtdbg.h>

//#define VG

//#include "UnsignedTest.h"
#include "String.h"

#include <string>
#include <iostream>
#include <cassert>
#include <utility>
using namespace std;

void AssertStrEqual(const String& lhs, const char* rhs) {
    for (size_t i = 0; i < lhs.size() && *rhs != '\0'; ++i) {
        assert(lhs[i] == rhs[i]);
        assert(rhs[i] != 0);
    }
    assert(rhs[lhs.size()] == 0);
}

void TestPushBackReallocation() {
    String str("hej");
    assert(str.size() <= str.capacity());
    assert(str.size() == 3);
    auto hej = "hej";
    //AssertStrEqual(str, hej);
    AssertStrEqual(str, "hej");
#ifdef VG
    //If VG we try to take 20 empty places: (size+1 < capacity)
    while (str.size() + 20 >= str.capacity() && str.size() < 1000)
        str.push_back('A' + rand() % 32);
    assert(str.size() < 1000);	//If this fail it prbably the case that capacity is increased with a constant.
#endif //VG

    auto internalBuf = &str[0];
    auto cap = str.capacity();
    auto siz = str.size();
    size_t i;
    for (i = siz + 1; i <= cap; ++i) {
        str.push_back(char(i) + 'a');
        assert(internalBuf == &str[0]);
        assert(cap == str.capacity());
        assert(i == str.size());
    }
    str.push_back(char(i));
    assert(internalBuf != &str[0]);
    assert(cap < str.capacity());
    assert(i == str.size());
}

void TestFörGodkäntString() {
    //-	String()
    String str0;	AssertStrEqual(str0, "");

    //-	String(Sträng sträng)
    String s1("foo"); assert(s1 == "foo");
    String str(s1); assert(str == "foo");
    String s3("bar");  assert(s3 == "bar");

    //-	~String() Kom ihåg destruktorn!
    delete new String("hej");

    //	-	operator =(Sträng sträng)
    str = "hej";
    assert((str = s3) == s3);
    assert((str = str) == s3);	//self assignment
    
    //Ej samma buffert
    str = "hej"; s3 = str;
    str[0] = 'x'; assert(s3[0] == 'h');
    s3[1] = 'y'; assert(str[1] == 'e');


    String str1("foo"), str2("bar"), str3("hej");
    str3 = str = str1;
    assert(str3 == str);
    assert(str1 == str);

    //No extra realloc
    AssertStrEqual(str1, "foo");
    auto xxx = str1.data();
    str1 = String("huj");
    assert(xxx == str1.data());

    //-	operator==
    //testas överallt!

    //- operator!=
    assert(str1 != str);
    assert(!(str1 != str1));

    //-	operator[](size_t i) som indexerar utan range check.
    str = "bar";
    str[-1]; str[1000];	//No error
    assert(str[1] == 'a');
    str[1] = 'y';
    assert(str[1] == 'y');

    const String sc(str);
    assert(sc[1] == 'y');
    assert(std::is_const<std::remove_reference< decltype(sc[1])>::type>::value); //Kolla att det blir en const resultat av indexering

    //-	push_back(char c) lägger till ett tecken sist.
    str = "bar";
    str.push_back('a');
    assert(str == "bara");

    // data
    const char* temp = str.data();
    assert(temp == &str[0]);

    //-	size(), capacity() and reloccation test;
    TestPushBackReallocation();

    cout << String("hej\n");
    cout << "Om det står hej på föregående rad så är TestFörGodkänt klar\n";

}

void TestFörVälGodkäntString() {
#ifdef VG
    String str("bar");

    //-	at(size_t i) som indexerar med range check
    try {
        str.at(-1);
        assert(false);
    }
    catch (std::out_of_range&) {};
    try {
        str.at(3);
        assert(false);
    }
    catch (std::out_of_range&) {};

    //- at indexerar

    //-	at(size_t i) 
    str = "bar";
    assert(str.at(1) == 'a');
    str.at(1) = 'y';
    assert(str.at(1) == 'y');

    const String strC(str);
    assert(strC.at(1) == 'y');
    assert(std::is_const<std::remove_reference< decltype(strC.at(1))>::type>::value); //Kolla att det blir en const resultat av indexering


    //	reserve()
    auto internalBuf = &str[0];
    auto cap = str.capacity();
    auto siz = str.size();

    str.reserve(cap);
    assert(internalBuf == &str[0]);
    assert(cap == str.capacity());
    assert(siz == str.size());

    str.reserve(cap + 1);
    assert(internalBuf != &str[0]);
    assert(cap < str.capacity());
    assert(siz == str.size());

    // shrink_to_fit
    str = "hej";
    str.reserve(10);
    internalBuf = &str[0];
    cap = str.capacity();
    siz = str.size();

    str.shrink_to_fit();
    assert(internalBuf != &str[0]);
    assert(str.capacity() == str.size());
    AssertStrEqual(str, "hej");

    /////////////////
    //-	operator+=(Sträng sträng) som tolkas som konkatenering.
    //foo, bar, hej
    String str1("foo"), str2("bar"), str3("hej");
    ((str = "xyz") += str1) += (str3 += str1);
    assert(str3 == "hejfoo" && str == "xyzfoohejfoo" && str1 == "foo");

    //+= som får plats;
    str = "bar"; str.reserve(10);
    str += "foo";
    assert(str == "barfoo");

    //+= som inte får plats;
    str.reserve(10);
    str = "";
    size_t i;
    for (i = 0; str.size() < str.capacity(); ++i)
        str.push_back(char('0' + i));
    str1 = "bar";
    str += str1;
    for (size_t k = 0; k < i; ++k)
        assert(str[k] == '0' + k);
    assert(str[i] == 'b');
    //+= Själv assignment	//Borde testa med att capacity tar slut!
    str = "foo";
    str += str;
    assert(str == "foofoo");

    //-	operator+
    str = "bar";
    assert(str + "foo" == "barfoo");
    AssertStrEqual(str, "bar");

    cout << "\nTestFörVälGodkänt klar\n";
#endif //VG
}



int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    locale::global(locale("swedish"));
    //TestUnsigned();
    TestFörGodkäntString();
    cout << "G test klart\n";
#ifdef VG
    TestFörVälGodkäntString();
    cout << "VG test klart\n";
#endif
    new int;
    cout << "det finns en minnesläcka i main, avsiktligt!\n så ni kan se att er minnesläckstest fungerar\n";
    cin.get();
}

