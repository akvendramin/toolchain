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
} big_integer;

PLATFORM_API uptr PlatformFormatString(char *Buffer, uptr BufferSize, char *Format, ...);

internal_function void PlatformSetBigInteger(big_integer *BigInteger, f64 Value)
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

internal_function int PlatformPower(int Base, int Exponent)
{
    return 0;
}

// float to string
internal_function uptr PlatformFloatToString(f64 Value, int Precision, char *Buffer, uptr BufferSize)
{
    uptr Result = (uptr)Precision;

    // extract the sign (1), biased-exponent (11) and significant (52)
    bool s = Value < 0;
    int e = (Value >> 52) & ((1 << 11) - 1);
    uptr m = Value & ((1 << 52) - 1);

    // unbiased the exponent and compute the new mantissa/significand
    int e2;
    uptr m2;
    
    if(!e)
    {
        // subnormal number
        e2 = 1 - 1023 - 52;
        m2 = m;
    }
    else
    {
        // normalized number
        e2 = e - 1023 - 52;
        m2 = (1 << 52) | m;
    }

    // mantissa and exponent -> d ~= m2 * 2^e2 
    uptr n;
    uptr d;

    if(e2 >= 0)
    {
        n = m2 << e2;
        d = 1;
    }
    else
    {
        // v ~= m2 / 2^-e2 
        // v ~= (m2 * 5^-e2) / (2^-e2 * 5^-e2)
        // v ~= m2 * (5^-e2 / (10^-e2)
        n = m2 * PlatformPower(5, -e2);
        d = 1 << -e2;
    }

    
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
