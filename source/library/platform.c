#include "platform.h"

#ifdef _WIN32
    #define WINDOWS_OS
    #include <windows.h>
#else
    #error
#endif

typedef uptr* va_args;
#define PlatformVaGet(arguments, type) *(type *)PlatformVaGetArgument(arguments)

typedef struct
{
    u64 Value[2048];
    uptr Size;
} big_integer;

typedef union
{
    f64 Value;
    u64 ValueU64;
} double_precision;

PLATFORM_API uptr PlatformFormatString(char *Buffer, uptr BufferSize, char *Format, ...);

internal_function void PlatformSetBigInteger(big_integer *BigInteger, u64 Value)
{
    BigInteger->Value[0] = Value;
}

// initialize va_args
internal_function va_args PlatformVaBegin(void *Format)
{
    va_args Result = (va_args)Format + 1;
    return Result;
}

// finalize va_args
internal_function va_args PlatformVaEnd()
{
    va_args Result = 0;
    return Result;
}

// get the argument and increment to the next argument
internal_function void *PlatformVaGetArgument(va_args *Arguments)
{
    void *Result = (*Arguments)++;
    return Result;
}

// get the string length
PLATFORM_API uptr PlatformStringLength(char *String)
{
    uptr Result = 0;

    while(*String++ != '\0')
    {
        Result++;
    }

    return Result;
}

// write a buffer to the console output
PLATFORM_API void PlatformWriteConsole(void *Buffer, u32 BufferSize)
{
#ifdef WINDOWS_OS
    // get a handle to the output console so we can write to it
    HANDLE OutputConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    if(!OutputConsoleHandle || (OutputConsoleHandle == INVALID_HANDLE_VALUE))
    {
        Log("GetStdHandle() failed: 0x%X\n", GetLastError());
        return;
    }

    // write to the console
    if(!WriteConsoleA(OutputConsoleHandle, Buffer, BufferSize, 0, 0))
    {
        Log("WriteConsoleA() failed: 0x%X\n", GetLastError());
        return;
    }
#else
    #error
#endif
}

// Copy one character to buffer
PLATFORM_API uptr PlatformCopyCharacter(char *Buffer, uptr BufferSize, int Character)
{
    uptr Result = 0;

    if(BufferSize < (2 * sizeof(char)))
    {
        Log("BufferSize is %llu\n", BufferSize);
        return Result;
    }

    Buffer[0] = (char)Character;
    Buffer[1] = '\0';

    return 1;
}

// copy string to buffer
PLATFORM_API uptr PlatformCopyString(char *Buffer, uptr BufferSize, char *String, uptr Length)
{
    uptr Result = 0;
    uptr MaxLength = PlatformStringLength(String);

    if(Length > MaxLength)
    {
        Log("String %s has length %llu of max length %llu\n", String, Length, MaxLength);
        return Result;
    }

    for(uptr Index = 0; Index < Length; Index++)
    {
        Result += PlatformCopyCharacter(Buffer + Index, BufferSize - Index, String[Index]);
    }

    return Result;
}

// copy s32 to buffer
PLATFORM_API uptr PlatformCopySigned32(char *Buffer, uptr BufferSize, s32 Value, int Base, char *Representation)
{
    uptr Result = 0;

    if(!Value)
    {
        Result = PlatformCopyCharacter(Buffer, BufferSize, '0');
        return Result;
    }

    bool IsNegative = Value < 0;

    if(IsNegative)
    {
        Value = -Value;
    }

    char WorkBuffer[sizeof(s32) * 8] = {0};
    int WorkBufferIndex = ArrayCount(WorkBuffer) - 2;

    for(; Value; Value /= Base)
    {
        WorkBuffer[WorkBufferIndex--] = Representation[Value % Base];
    }

    if(IsNegative)
    {
        WorkBuffer[WorkBufferIndex] = '-';
    }
    else
    {
        WorkBufferIndex++;
    }

    Result = PlatformCopyString(Buffer, BufferSize, WorkBuffer + WorkBufferIndex, PlatformStringLength(WorkBuffer + WorkBufferIndex));
    return Result;
}

// copy u32 to buffer
PLATFORM_API uptr PlatformCopyUnsigned32(char *Buffer, uptr BufferSize, u32 Value, int Base, char *Representation)
{
    uptr Result = 0;

    if(!Value)
    {
        Result = PlatformCopyCharacter(Buffer, BufferSize, '0');
        return Result;
    }
    
    char WorkBuffer[sizeof(s32) * 8] = {0};
    int WorkBufferIndex = ArrayCount(WorkBuffer) - 2;

    for(; Value; Value /= Base)
    {
        WorkBuffer[WorkBufferIndex--] = Representation[Value % Base];
    }
    
    WorkBufferIndex++;

    Result = PlatformCopyString(Buffer, BufferSize, WorkBuffer + WorkBufferIndex, PlatformStringLength(WorkBuffer + WorkBufferIndex));
    return Result;
}

// copy s64 to buffer
PLATFORM_API uptr PlatformCopySigned64(char *Buffer, uptr BufferSize, s64 Value, int Base, char *Representation)
{
    uptr Result = 0;

    if(!Value)
    {
        Result = PlatformCopyCharacter(Buffer, BufferSize, '0');
        return Result;
    }

    bool IsNegative = Value < 0;

    if(IsNegative)
    {
        Value = -Value;
    }

    char WorkBuffer[sizeof(s32) * 8] = {0};
    int WorkBufferIndex = ArrayCount(WorkBuffer) - 2;

    for(; Value; Value /= Base)
    {
        WorkBuffer[WorkBufferIndex--] = Representation[Value % Base];
    }

    if(IsNegative)
    {
        WorkBuffer[WorkBufferIndex] = '-';
    }
    else
    {
        WorkBufferIndex++;
    }

    Result = PlatformCopyString(Buffer, BufferSize, WorkBuffer + WorkBufferIndex, PlatformStringLength(WorkBuffer + WorkBufferIndex));
    return Result;
}

// copy u64 to buffer
PLATFORM_API uptr PlatformCopyUnsigned64(char *Buffer, uptr BufferSize, u64 Value, int Base, char *Representation)
{
    uptr Result = 0;

    if(!Value)
    {
        Result = PlatformCopyCharacter(Buffer, BufferSize, '0');
        return Result;
    }
    
    char WorkBuffer[sizeof(s32) * 8] = {0};
    int WorkBufferIndex = ArrayCount(WorkBuffer) - 2;

    for(; Value; Value /= Base)
    {
        WorkBuffer[WorkBufferIndex--] = Representation[Value % Base];
    }
    
    WorkBufferIndex++;

    Result = PlatformCopyString(Buffer, BufferSize, WorkBuffer + WorkBufferIndex, PlatformStringLength(WorkBuffer + WorkBufferIndex));
    return Result;
}

// string to float
internal_function f64 PlatformStringToFloat(char *Buffer, uptr BufferSize)
{
    f64 Result = 0.0;

    return Result;
}

// pow
internal_function int PlatformPower(int Base, int Exponent)
{
    return 0;
}

// memcpy
internal_function void PlatformMemorySet(void *Memory, uptr MemoryCount, u8 Value)
{
    u8 *memory = Memory;

    for(uptr Index = 0; Index < MemoryCount; Index++)
    {
        *memory++ = Value;
    }
}

// set a big int to u64
internal_function void BigIntegerFromU64(big_integer *BigInteger, u64 Value)
{
    PlatformMemorySet(BigInteger->Value, ArrayCount(BigInteger->Value), 0);
    BigInteger->Value[ArrayCount(BigInteger->Value) - 1] = Value;
    
    while(Value)
    {
        BigInteger->Size++;
        Value /= 10;
    }
}

// BigInteger multiply U64
internal_function void BigIntegerMultiplyU64(big_integer *BigInteger, u64 Value)
{
    //@TODO: Test it
    for(uptr I = BigInteger->Size - 1; I >= 0; I--)
    {
        u64 Multiplier = Value;

        for(uptr J = BigInteger->Size - 1; Multiplier > 0; J--)
        {
            u64 Multiplicand = BigInteger->Value[J];
            int Carry = 0;
            
            while(Multiplicand > 0)
            {                
                int MultiplicandDigit = Multiplicand % 10;
                int MultiplierDigit = Multiplier % 10;
                int Product = (MultiplicandDigit * MultiplierDigit) + Carry;
                Carry = Product >= 10;
                Multiplicand /= 10;

                //@TODO: Store it
            }

            Multiplier /= 10;
        }
    }
}

// BigInteger divide U64
internal_function void BigIntegerDivideBigInteger(big_integer *A, big_integer *B, big_integer *C)
{
    //@TODO: Test it
    // 9999 8888 7777
    // ---- ---- 6666
}

// float to string
internal_function uptr PlatformFloatToString(f64 Value, int Precision, char *Buffer, uptr BufferSize)
{
    //@TODO: Why 10^17 when scaling numerator/denominator big int
    uptr Result = Precision;

    // use a union to analyze or manipulate float with bitwise operations
    double_precision Double = {0};
    Double.Value = Value;

    // get sign [63], exponent [62:52], significand [0:51] from double
    uptr Sign = Double.ValueU64 >> 63;
    sptr Exponent = (Double.ValueU64 >> 52) & ((1ULL << 11) - 1);
    uptr Significand = Double.ValueU64 & ((1ULL << 52) - 1);

    // some constants
    uptr ExponentMax = 1023;
    uptr ExponentMin = 1 - ExponentMax;

    // unbiase the exponent and update the significand with or without the leading 1
    if(!Exponent)
    {
        // subnormal number has exponent fixed 2^-1074
        Exponent = ExponentMin - 52;
    }
    else
    {
        // normal number
        Exponent = Exponent - ExponentMax - 52;
        Significand = (1ULL << 52) | Significand;
    }

    // we ignore the sign in both for now...

    // normal number
    // d ~= m * 2^e
    // d ~= (1 + (f/2^52)) * 2^e
    // d ~= (2^52 + f)/2^52 * 2^e
    // i = (2^52 + f) / 2^e-52

    // subnormal number has exponent fixed 2^-1074
    // d ~= m * 2^-e
    // i = m * 2^-1074
    // i = m / 2^1074

    big_integer Numerator = {0};
    big_integer Denominator = {0};

    if(Exponent > 0)
    {
        BigIntegerFromU64(&Numerator, Significand); //@TODO:
        BigIntegerFromU64(&Denominator, 1ULL << (Exponent - 52));
        Assert((Exponent - 52) > 0);
    }
    else
    {
        BigIntegerFromU64(&Numerator, Significand); //@TODO:
        BigIntegerFromU64(&Denominator, 1ULL << -Exponent);
    }

    // what operations do i need for numerator/denominator? division, multiplication
    // i scaled by 10^17 because log10(2^53) ~= 15.95 and we need 17 digits because 16 + 1 for round trip stuff
    // n / d
    // n*10^17 / d
    big_integer C = {0};
    BigIntegerMultiplyU64(&Numerator, 0x16345785D8A0000);
    BigIntegerDivideBigInteger(&Numerator, &Denominator, &C);

    return Result;
}

// float to string then copy to buffer
PLATFORM_API uptr PlatformCopyFloat64(char *Buffer, uptr BufferSize, f64 Value, int Precision)
{
    uptr Result = 0;

    Result = PlatformFloatToString(Value, Precision, Buffer, BufferSize);
    return Result;
}

// format the string
PLATFORM_API uptr PlatformFormatString(char *Buffer, uptr BufferSize, char *Format, ...)
{
    uptr Result = 0;
    va_args Arguments = PlatformVaBegin(&Format);
    char *Octal = "01234567";
    char *Decimal = "0123456789";
    char *HexadecimalLowerCase = "0123456789abcdef";
    char *HexadecimalUpperCase = "0123456789ABCDEF";

    for(char *c = Format; *c != '\0';)
    {
        if(*c != '%')
        {
            Result += PlatformCopyCharacter(Buffer + Result, BufferSize - Result, *c);
            c++;
            continue;
        }

        if(*++c == '%')
        {
            Result += PlatformCopyCharacter(Buffer + Result, BufferSize - Result, *c);
            c++;
        }
        else if(*c == 'c')
        {
            int Value = PlatformVaGet(&Arguments, int);
            Result += PlatformCopyCharacter(Buffer + Result, BufferSize - Result, Value);
            c++;
        }
        else if((*c == 'd') || (*c == 'i'))
        {
            s32 Value = PlatformVaGet(&Arguments, s32);
            Result += PlatformCopySigned32(Buffer + Result, BufferSize - Result, Value, 10, Decimal);
            c++;
        }
        else if(*c == 'f')
        {
            f64 Value = PlatformVaGet(&Arguments, f64);
            Result += PlatformCopyFloat64(Buffer + Result, BufferSize - Result, Value, 17);
            c++;
        }
        else if((c[0] == 'l') && (c[1] == 'l') && ((c[2] == 'd') || (c[2] == 'i')))
        {
            s64 Value = PlatformVaGet(&Arguments, s64);
            Result += PlatformCopySigned64(Buffer + Result, BufferSize - Result, Value, 10, Decimal);
            c += 3;
        }
        else if((c[0] == 'l') && (c[1] == 'l') && (c[2] == 'u'))
        {
            u64 Value = PlatformVaGet(&Arguments, u64);
            Result += PlatformCopyUnsigned64(Buffer + Result, BufferSize - Result, Value, 10, Decimal);
            c += 3;
        }
        else if(*c == 'o')
        {
            u32 Value = PlatformVaGet(&Arguments, u32);
            Result += PlatformCopyUnsigned32(Buffer + Result, BufferSize - Result, Value, 8, Octal);
            c++;
        }
        else if(*c == 'p')
        {
            void *Value = PlatformVaGet(&Arguments, void *);
            Result += PlatformCopyUnsigned64(Buffer + Result, BufferSize - Result, (u64)Value, 16, HexadecimalLowerCase);
            c++;
        }
        else if(*c == 's')
        {
            char *Value = PlatformVaGet(&Arguments, char *);
            Result += PlatformCopyString(Buffer + Result, BufferSize - Result, Value, PlatformStringLength(Value));
            c++;
        }
        else if(*c == 'u')
        {
            u32 Value = PlatformVaGet(&Arguments, u32);
            Result += PlatformCopyUnsigned32(Buffer + Result, BufferSize - Result, Value, 10, Decimal);
            c++;
        }
        else if((*c == 'x') || (*c == 'X'))
        {
            u32 Value = PlatformVaGet(&Arguments, u32);
            
            if(*c == 'x')
            {
                Result += PlatformCopyUnsigned32(Buffer + Result, BufferSize - Result, Value, 16, HexadecimalLowerCase);
            }
            else
            {
                Result += PlatformCopyUnsigned32(Buffer + Result, BufferSize - Result, Value, 16, HexadecimalUpperCase);
            }

            c++;
        }
        else
        {
            Assert(0);
        }
    }

    Arguments = PlatformVaEnd();

    return Result;
}
