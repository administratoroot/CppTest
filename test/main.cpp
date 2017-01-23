#include <iostream>

using namespace std;

int main()
{
    char a[10] = "1234";

    __asm
    {
        push eax
            push edx
            push ecx

            lea eax, a //将a的地址给eax

        mov     cl, byte ptr[eax]
        mov     dl, byte ptr[eax]
        movzx   ecx, cl
        movzx   edx, dl
        shr     ecx, 4
        shl     edx, 4
        or      ecx, edx
        mov     byte ptr[eax], cl
        inc     eax
        mov     cl, byte ptr[eax]

        pop ecx
        pop edx
        pop eax
    }
}