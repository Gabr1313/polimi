#include <stdio.h>
#include <math.h>

typedef long double f128;
typedef long long int i64;

const f128 PI  = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

#define FUNC(x) sinl(x)
const i64  REP        = 10000;
const f128 START      = 0;
const f128 END        = PI;
const f128 EXPTECTED  = 2;

// #define FUNC(x) tanl(x)
// const i64  REP        = 10000;
// const f128 START      = 0;
// const f128 END        = PI/4;
// const f128 EXPTECTED  = logl(2)/2;

f128 standard() {
    f128 step = (END-START) / REP;
    f128 area = 0;
    for (i64 i = 0; i < REP; i++) {
        f128 x0 = START + step * i;
        f128 x1 = x0 + step;
        area += (FUNC(x0) + FUNC(x1))/2;
    }
    return area * step;
}

f128 simpson() {
    f128 step = (END-START) / (REP/2);
    f128 area = 0;
    for (i64 i = 0; i < (REP/2); i++) {
        f128 x0 = START + step * i;
        f128 x1 = x0 + step/2;
        f128 x2 = x0 + step;
        area += FUNC(x0) + 4*FUNC(x1) + FUNC(x2);
    }
    return area * step / 6;
}

f128 standard_opt() {
    f128 step = (END-START) / REP;
    f128 area = 0;
    area += FUNC(START)/2;
    area += FUNC(END)  /2;

    for (i64 i = 1; i < REP; i++) {
        f128 x = START + step * i;
        area += FUNC(x);
    }

    return area * step;
}

f128 simpson_opt() {
    f128 step = (END-START) / REP;
    f128 area = 0;
    area += FUNC(START)/3;
    area += FUNC(END)  /3;

    for (i64 i = 1; i < REP; i++) {
        f128 x = START + step * i;
        if (i % 2) {
            area += FUNC(x) * 4/3;
        } else {
            area += FUNC(x) * 2/3;
        }
    }

    return area * step;
}

int main() {
    printf("Standard     : %Le\n", fabsl(standard()     - EXPTECTED));
    printf("Simpson      : %Le\n", fabsl(simpson()      - EXPTECTED));
    printf("Standard_opt : %Le\n", fabsl(standard_opt() - EXPTECTED));
    printf("Simpson_opt  : %Le\n", fabsl(simpson_opt()  - EXPTECTED));
}
