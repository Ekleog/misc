
template <int Col, int RFrom, int RTo, template <int, int> class Call>
struct ForRow {
    static void run() {
        Call<Col, RFrom>::run();
        ForRow<Col, RFrom + 1, RTo, Call>::run();
    }
};
template <int Col, int REnded, template <int, int> class Call>
struct ForRow<Col, REnded, REnded, Call> {
    static void run() { }
};

template <int CFrom, int CTo, int RFrom, int RTo, template <int, int> class Call>
struct For {
    static void run() {
        ForRow<CFrom, RFrom, RTo, Call>::run();
        For<CFrom + 1, CTo, RFrom, RTo, Call>::run();
    }
};
template <int CEnded, int RFrom, int RTo, template <int, int> class Call>
struct For<CEnded, CEnded, RFrom, RTo, Call> {
    static void run() { }
};

// Pour tester la compilation
#include <cstdio>
template <int Col, int Row> struct CColRowHelper {
    enum { activated = true };
    static void DoSomething() { std::printf("."); }
};
template <> struct CColRowHelper<5, 5> {
    enum { activated = false };
    static void DoSomething() { }
};

// Le foncteur
template <int Col, int Row>
struct IfActDoSth {
    static void run() {
        if (CColRowHelper<Col, Row>::activated)
            CColRowHelper<Col, Row>::DoSomething();
    }
};

// Et l'appel
void DoTheSths() {
    For<0, 10, 0, 10, IfActDoSth>::run();
    // Lance IfActDoSth::run() pour 0,1,2,3,4,5,6,7,8,9 en ligne et idem pour
    // les colonnes.
}

// Un main de test
int main(int, char**) {
    DoTheSths();
}
