#include <assert.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint64_t ull;

typedef struct _string {
    ull len;
    ull cap;
    char *ptr;
} string;

string string_new(ull cap) {
    string s;
    s.cap = cap;
    s.ptr = realloc(NULL, sizeof(*s.ptr) * cap);
    if (!s.ptr) assert(0);
    s.len = 0;
    return s;
}

void string_free(string s) { free(s.ptr); }

void string_push(string *s, char ch) {
    if (s->len == s->cap) {
        s->ptr = realloc(s->ptr, sizeof(*s->ptr) * (s->cap *= 2));
        if (!s->ptr) assert(0);
    }
    s->ptr[s->len++] = ch;
}

void string_shrink(string* s) {
    s->cap = s->len;
    s->ptr = realloc(s->ptr, sizeof(*s->ptr) * s->cap);
    if (!s->ptr) assert(0);
}

string string_read() {
    int ch;
    string s = string_new(64);
    while (EOF != (ch = getchar()) && !isspace(ch)) string_push(&s, ch);
    string_push(&s, '\0');
    string_shrink(&s);
    return s;
}

void string_rev(string* s) {
    for (ull i = 0; i < s->len - 2 - i; i++) {  // '\0' at the end
        char tmp = s->ptr[i];
        s->ptr[i] = s->ptr[s->len - 2 - i];
        s->ptr[s->len - 2 - i] = tmp;
    }
}

typedef struct _bigNum {
    ull cap;
    ull *ptr;
    // bits are used as follow:
    // - the least significant is in the rightmost bit of the first element
    // - the most significant is in the leftmost bit of the last element
} bigNum;

void bignum_free(bigNum n) { free(n.ptr); }

bigNum bignum_clone(bigNum n) {
    bigNum m;
    m.cap = n.cap;
    m.ptr = malloc(m.cap / 8);
    memcpy(m.ptr, n.ptr, m.cap / 8);
    return m;
}

string bignum_to_string(bigNum n) {
    n = bignum_clone(n);
    string s = string_new(n.cap >= 6 ? n.cap / 3 : 2);  // 3 < log2(10)
    int right_most = n.cap / 64;
    while (1) {
        ull carry = 0;
        while (right_most > 0 && n.ptr[right_most - 1] == 0) right_most--;
        if (right_most <= 0) break;
        for (int i = right_most - 1; i >= 0; i--) {
            ull x = (n.ptr[i] >> 32) + carry * (1ull << 32);
            carry = x % 10;
            n.ptr[i] &= (ull)UINT32_MAX;
            n.ptr[i] |= (x / 10) << 32;

            x = (n.ptr[i] & (ull)UINT32_MAX) + carry * (1ull << 32);
            carry = x % 10;
            n.ptr[i] &= ~(ull)UINT32_MAX;
            n.ptr[i] |= x / 10;
        }
        string_push(&s, carry + '0');
    }
    bignum_free(n);
    if (s.len == 0) string_push(&s, '0');
    string_push(&s, '\0');
    string_shrink(&s);
    string_rev(&s);
    return s;
}

bigNum bignum_new(ull bits) {
    bigNum n;
    n.cap = (bits + 63) / 64 * 64;
    n.ptr = malloc(bits / 8);
    if (n.ptr == NULL) assert(0);
    return n;
}

// does not realloc
void bignum_set(bigNum *n, ull pos, ull val) {
    if (pos >= n->cap) assert(0);
    if (val) n->ptr[(pos) / 64] |= 1ull << ((pos) % 64);
    else n->ptr[(pos) / 64] &= ~(1ull << ((pos) % 64));
}

void bignum_shrink(bigNum* n, ull cap) {
    if (cap % 64) n->ptr[(cap - 1) / 64] &= (UINT64_MAX >> (64 - cap % 64));
    cap = (cap + 63) / 64 * 64;
    if (cap != n->cap) {
        n->ptr = realloc(n->ptr, n->cap / 8);
        if (!n->ptr) assert(0);
        n->cap = cap;
    }
}

bigNum bignum_read() {
    string s = string_read();
    for (ull i = 0; i < s.len - 1; i++) assert(s.ptr[i] >= '0' && s.ptr[i] <= '9');
    bigNum n = bignum_new(s.len * 4);  // 4 > log2(10)
    ull left_most = 0, pos = 0;
    while (left_most <= s.len - 2) {
        bignum_set(&n, pos++, (s.ptr[s.len - 2] - '0') % 2);
        s.ptr[s.len - 2] = (s.ptr[s.len - 2] - '0') / 2 + '0';
        for (ull i = s.len - 3; i >= left_most && i != UINT64_MAX; i--) {
            s.ptr[i + 1] += 5 * ((s.ptr[i] - '0') % 2);
            s.ptr[i] = (s.ptr[i] - '0') / 2 + '0';
        }
        left_most += (s.ptr[left_most] == '0');
    }
    string_free(s);
    bignum_shrink(&n, pos);
    return n;
}

void bignum_cpy_increase_cap(bigNum a, ull cap) {
    bigNum b = bignum_new(cap);
    memcpy(b.ptr, a.ptr, a.cap / 8);
    memset(b.ptr + a.cap / 64, 0, b.cap / 8 - a.cap / 8);
}

void bignum_sub_eq(bigNum *a, bigNum b) {
    assert(a->cap >= b.cap);
    ull carry = 0;
    for (ull i = 0; i < a->cap / 64; i++) {
        ull res = a->ptr[i] - carry;
        if (i < b.cap / 64) res -= b.ptr[i];
        carry = res > a->ptr[i];
        a->ptr[i] = res;
    }
}

void bignum_sum_eq_uncheked(bigNum *a, bigNum b) {
    ull carry = 0;
    for (ull i = 0; i < a->cap / 64; i++) {
        ull res = a->ptr[i] + carry;
        if (i < b.cap / 64) res += b.ptr[i];
        carry = res < a->ptr[i];
        a->ptr[i] = res;
    }
    assert(carry == 0);
}

void bignum_sum(bigNum a, bigNum b, bigNum *c) {
    if (a.cap < b.cap) {
        bigNum tmp = a;
        a = b;
        b = tmp;
    }
    assert(c->cap >= a.cap);
    int carry = 0;
    for (ull i = 0; i < a.cap / 64; i++) {
        c->ptr[i] = a.ptr[i] + carry;
        carry = (c->ptr[i] == 0);
        if (i < b.cap / 64) {
            c->ptr[i] += b.ptr[i];
            carry |= c->ptr[i] < b.ptr[i];
        }
    }
    if (carry) {
        assert(c->cap >= a.cap + 64);
        c->cap = a.cap + 64;
        c->ptr[a.cap / 64] = 1ull;
    } else c->cap = a.cap;
}

void karastuba(bigNum a, bigNum b, bigNum *c) {
    // `*c` so i avoid memory allocations. I use it as a buffer
    assert(c->cap >= a.cap + b.cap);

    if (a.cap == 0 || b.cap == 0) {
        c->cap = 0;
        return;
    }

    if (a.cap <= 64 && b.cap <= 64) {
        c->ptr[0] = (*a.ptr & UINT32_MAX) * (*b.ptr & UINT32_MAX);
        c->ptr[1] = (*a.ptr >> 32) * (*b.ptr >> 32);
        ull tmp = (*a.ptr & UINT32_MAX) * (*b.ptr >> 32) + (*b.ptr & UINT32_MAX) * (*a.ptr >> 32);
        ull prev = c->ptr[0];
        c->ptr[0] += ((tmp & UINT32_MAX) << 32);
        ull carry = c->ptr[0] < prev;
        c->ptr[1] += carry + (tmp >> 32);
        return;
    }

    ull two_pow = 0;
    for (int i = 7; i < 60; i++) {  // two_pow >= 64
        if ((1ull << i) >= a.cap && (1ull << i) >= b.cap) {
            two_pow = (1ull << (i - 1));
            break;
        }
    }
    assert(two_pow);

    bigNum x, y, z, w;
    x.ptr = &a.ptr[two_pow / 64];
    x.cap = (a.cap > two_pow ? a.cap - two_pow : 0);
    y.ptr = &a.ptr[0];
    y.cap = (a.cap > two_pow ? two_pow : a.cap);
    z.ptr = &b.ptr[two_pow / 64];
    z.cap = (b.cap > two_pow ? b.cap - two_pow : 0);
    w.ptr = &b.ptr[0];
    w.cap = (b.cap > two_pow ? two_pow : b.cap);

    bigNum h1, h2;
    h1.cap = a.cap;
    h1.ptr = c->ptr;  // avoid malloc
    h2.cap = b.cap;
    h2.ptr = c->ptr + h1.cap / 64;  // avoid malloc
    bignum_sum(x, y, &h1);
    bignum_sum(z, w, &h2);

    bigNum mid = bignum_new(h1.cap + h2.cap);
    karastuba(h1, h2, &mid);

    bigNum xz, yw;
    yw.cap = y.cap + w.cap;
    yw.ptr = c->ptr;  // avoid malloc
    xz.cap = x.cap + z.cap;
    xz.ptr = c->ptr + two_pow / 32;  // avoid malloc

    karastuba(x, z, &xz);
    karastuba(y, w, &yw);
    bignum_sub_eq(&mid, xz);
    bignum_sub_eq(&mid, yw);

    if (yw.cap < two_pow * 2) memset(c->ptr + yw.cap / 64, 0, (two_pow * 2 - yw.cap) / 8);
    if (xz.cap < c->cap - two_pow * 2)
        memset(c->ptr + two_pow / 32, 0, (c->cap - two_pow * 2 - xz.cap) / 8);

    bigNum tmp;
    tmp.cap = c->cap - two_pow;
    tmp.ptr = &c->ptr[two_pow / 64];
    bignum_sum_eq_uncheked(&tmp, mid);

    bignum_free(mid);
    return;
}

int main() {
    bigNum a = bignum_read();
    bigNum b = bignum_read();
    bigNum c = bignum_new(a.cap + b.cap);
    karastuba(a, b, &c);

    string sa = bignum_to_string(a);
    printf("%s\n*\n", sa.ptr);
    string_free(sa);
    string sb = bignum_to_string(b);
    printf("%s\n=\n", sb.ptr);
    string_free(sb);

    string sc = bignum_to_string(c);
    printf("%s\n", sc.ptr);
    string_free(sc);

    bignum_free(a);
    bignum_free(b);
    bignum_free(c);
    return 0;
}
