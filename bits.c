/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x|~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return (~(~x & ~y) & ~(x & y));
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!x && !y)return 1;   //0，0
    if(!x ^ !y)return 0;    //有一个是0
    return !(x>>31 ^ y>>31);//符号位异或比较
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int r=0;
    int temp;

    temp = ((v>>16)>0) <<4;//v的16位往上有1吗？有则temp=16；
    v >>= temp;
    r |= temp;

    temp = ((v>>8)>0) <<3;//v的24位/8位往上有1吗？有则temp=8；
    v >>= temp;
    r |= temp;

    temp = ((v>>4)>0) <<2;//+4? 4:0
    v >>= temp;
    r |= temp;

    temp = ((v>>2)>0) <<1;//+2？
    v >>= temp;
    r |= temp;

    temp = ((v>>1)>0);//+1？
    v>>= temp;
    r|=temp;

    return r;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int s_n=n<<3, s_m=m<<3; 
    //先存下来两个字节内容
    int b_n = (x>>s_n) & 0xFF;
    int b_m = (x>>s_m) & 0xFF;

    //然后把要交换的部位清空为0（赋值只能对全0赋值）
    int mask = (0xFF<<s_n) | (0xFF<<s_m);
    int x_masked = x & ~mask;

    //最后交换放入
    int swapped = (b_n << s_m) | (b_m << s_n); 
    return x_masked|swapped;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    //从后往前推
    unsigned int ans = 0;
    unsigned int cur = v;
    int last_bit = 0;
    unsigned int counter = 0x80000000;
    while(counter){
        last_bit = cur & 0x1;
        ans <<= 1;
        ans |= last_bit;
        cur >>= 1;
        counter>>=1;
    }
    return ans;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    //首先盖住所有因为首位是1而在算数左移后保持为1的东西（这n-1个1在逻辑左移中应是0）
    int mask = ~(((1<<31)>>n)<<1);
    return (x>>n)&mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12, 111111111111 00001111000011110000
 *             leftBitCount(0xFE00FF0F) = 7. 1111111 0000000001111111100001111
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    //切香肠战术：留下的越来越少：0.5-0.25-0.125....
    //要是剩下的全为0，就计数并切掉
    //递归求解
    int y=~x;
    int n=0;
    int c;

    c = !(y>>16);
    n += (c<<4);
    y <<= (c<<4);

    c = !(y>>24);
    n += (c<<3);
    y <<= (c<<3);

    c= !(y>>28);
    n += (c<<2);
    y<<= (c<<2);
    
    c = !(y>>30);
    n += (c<<1);
    y<<= (c<<1);

    c = !(y>>31);
    n += (c);

    return (n+!y);
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign = x & 0x80000000;   // 提取符号位
    unsigned ux = x;
    if (sign) ux = -ux;               // 取绝对值（无符号取负，避免 INT_MIN 溢出）
    if (ux == 0) return 0;            // 0 直接返回 0

    int e = 0;
    unsigned temp = ux;
    while (temp >>= 1) e++;           // 找到最高位 1 的位置，e 为指数偏移

    unsigned exp = e + 127;           // 加上偏置 127
    unsigned frac;

    if (e <= 23) {
        // 尾数不需要舍入，直接左移对齐到 23 位
        frac = (ux << (23 - e)) & 0x7FFFFF;
    } else {
        // 需要舍入
        int shift = e - 23;
        frac = (ux >> shift) & 0x7FFFFF;          // 只保留低 23 位尾数
        unsigned round = (ux >> (shift - 1)) & 1; // 舍入位
        unsigned sticky = ux & ((1 << (shift - 1)) - 1); // 粘滞位

        if (round) {
            if (sticky) {
                frac++;
            } else {
                if (frac & 1) {
                    frac++;
                }
            }
            // 尾数溢出（达到 24 位），指数进位
            if (frac == 0x800000) {
                frac = 0;
                exp++;
            }
        }
    }

    return sign | (exp << 23) | frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000;        // 提取符号位
    unsigned exp = (uf >> 23) & 0xFF;       // 提取指数位
    unsigned frac = uf & 0x7FFFFF;          // 提取尾数位

    if (exp == 255) {
        // 无穷大或 NaN，乘以 2 后仍返回原值
        return uf;
    }

    if (exp == 0) {
        // 非规格化数或 0
        frac = frac << 1;                   // 尾数左移一位，相当于乘以 2
        if (frac & 0x800000) {
            // 尾数最高位溢出，变为规格化数
            exp = 1;                        // 指数变为 1
            frac = frac & 0x7FFFFF;         // 只保留低 23 位
        }
        // 否则 exp 仍为 0，仍是非规格化数
    } else {
        // 规格化数
        exp = exp + 1;                      // 指数加 1
        if (exp == 255) {
            // 指数溢出，变为无穷大
            frac = 0;                       // 尾数清零
        }
    }

    return sign | (exp << 23) | frac;       // 组合成结果
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign = uf2 & 0x80000000;
    unsigned exp = (uf2 >> 20) & 0x7FF;
    unsigned frac_high = uf2 & 0xFFFFF;      // 尾数高 20 位
    unsigned frac_low = uf1;                 // 尾数低 32 位

    if (!(exp - 0x7FF)) return 0x80000000;     // 无穷大或 NaN，视为溢出
    if (!exp) return 0;                  // 非规格化数或 0，太小，返回 0

    int e = exp - 1023;                      // 真实指数
    if (e < 0) return 0;                     // 数值小于 1，向零舍入为 0
    if (e >= 31) return 0x80000000;          // 超出 32 位有符号整数范围，溢出

    unsigned mag;                            // 结果的绝对值
    if (e <= 20) {
        // 尾数的高 e 位全部在 frac_high 中
        mag = (1 << e) + (frac_high >> (20 - e));
    } else {
        // 尾数的高 e 位跨越 frac_high 和 frac_low
        mag = (1 << e) + ((frac_high << (e - 20)) | (frac_low >> (52 - e)));
    }

    if (sign) {
        return -mag;                         // 负数，返回补码表示
    }

    return mag;

    return 2;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x < -149) return 0;                 // 太小，无法表示为非规格化数
    if (x > 127)  return 0x7F800000;        // 太大，返回 +INF
    if (x < -126) {                         // 非规格化数范围：-149 <= x <= -127
        return 1 << (x + 149);              // 构造非规格化尾数
    }
    return (x + 127) << 23;
}
