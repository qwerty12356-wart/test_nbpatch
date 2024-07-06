#include "logging.h"
#include "main.h"
#include "patch_tools.h"
#include <cstdint>
#include <cstring>



void Patch_Permissive_Mmap_Houdini13_39190(){
    int res = 0;
    #ifdef IS32BIT 
        res = PatchHex_32(nbbase, 0x27e467, 0x0fbaf002, 0x909090f8);
    #else //default to 64 bit
        res = PatchHex_8(nbbase, 0x2efd53, 0xfb, 0xff);

    #endif
    if (res){
        error_print("Patch_Permissive_Mmap failed.");
    }

}

void Patch_Permissive_Mprotect_Houdini13_39190(){
    int res =0;
    #ifdef IS32BIT
        //These stupid hexes took fucking AGES to find because ghidra ENTIRELY miss a very important function.
        res = PatchHex_8(nbbase, 0x2829c0, 0xfb, 0xff);
    #else
        res = PatchHex_32(nbbase, 0x2f3778, 0x02F1BA0F, 0xF8909090);
    #endif
    if (res){
        error_print("Patch_Permissive_Mprotect failed.");
    }
}

void Patch_Performance_Mprotect_Houdini13_39190(){
    int res = 0;
    #ifdef IS32BIT
        res = PatchHex_32(nbbase, 0x282b64, 0xEC84A7E8, 0x90909090);
        res = res | PatchHex_8(nbbase, 0x282b68, 0xff, 0x90);
    #else
        res = PatchHex_32(nbbase, 0x2f3903, 0xED8F58E8, 0x90909090);
        res = res | PatchHex_8(nbbase,0x2f3907 , 0xff, 0x90);
    #endif
    if (res){
        error_print("Patch_Performace_Mprotect failed.");
    }
}

void Patch_Performance_Mprotect_Houdini12_38818(){
    int res = 0;
    #ifdef IS32BIT
        res = PatchHex_32(nbbase, 0x271b56, 0xEC9CE5E8, 0x90909090);
        res |= PatchHex_8(nbbase, 0x271b5a, 0xff, 0x90);
    #else
        res = PatchHex_32(nbbase, 0x2f7660, 0xEE2ABBE8, 0x90909090);
        res |= PatchHex_8(nbbase, 0x2f7664, 0xff, 0x90);
    #endif
    if (res){
        error_print("Patch_Performance_Mprotect failed.");
    }
}

void Patch_Permissive_Mprotect_Houdini12_38818(){
    int res = 0;
    #ifdef IS32BIT
        res = PatchHex_8(nbbase, 0x2719b3, 0xfb, 0xff);
    #else
       res = PatchHex_32(nbbase, 0x2f74e6, 0x02F1BA0F, 0xF8909090);
    #endif
    if (res){
        error_print("Patch_Permissive_Mprotect failed.");
    }
}

void Patch_Permissive_Mmap_Houdini12_38818(){
    int res = 0;
    #ifdef IS32BIT
        res = PatchHex_32(nbbase, 0x26d3a7, 0x02F0BA0F, 0xF8909090);
    #else
        res = PatchHex_32(nbbase, 0x2f3ae1, 0xFFFBB848, 0xFFFFB848);
        
    #endif
    if (res){
        error_print("Patch_Permissive_Mmap failed.");
    }
}

void Patch_Linker_namespace_Houdini13_39190(){
    int res = 0;
    #ifdef IS32BIT
        //No 32 bit because im too lazy
    #else
        res = PatchHex_32(nbbase, 0x460b78, 0xFFBB93E8, 0x90909090);
        res |= PatchHex_8(nbbase, 0x460b7c, 0xff, 0x90);
    #endif
    if (res){
        error_print("Patch_Linker_namespace failed.");
    }
}

void Patch_Linker_namespace_Houdini12_38818(){
    int res = 0;
     #ifdef IS32BIT

    #else
        res = PatchHex_32(nbbase, 0x335e1a, 0x0042D1E8, 0x90909090);
        res |= PatchHex_8(nbbase, 0x335e1e, 0x00, 0x90);
    #endif
    if (res){
        error_print("Patch_Linker_namespace failed.");
    }
}

void Patch_Permissive_Mmap_HOUDINI11_38765(){
    int res = 0;
    #ifdef IS32BIT
        //No 32 bit version because im too lazy. Feel free to make a pull request.
    #else
        res |= PatchHex_32(nbbase, 0x3062A5, 0xFFFBB848, 0xFFFFB848);
    #endif
    if (res){
        error_print("Patch_Permissive_Mmap Failed.");
    }
}

void Patch_Permissive_Mprotect_HOUDINI11_38765(){
    int res = 0;
     #ifdef IS32BIT
        //No 32 bit version because im too lazy. Feel free to make a pull request.
    #else
        res |= PatchHex_8(nbbase, 0x3099D8, 0xFB, 0xFF);
    #endif
     if (res){
        error_print("Patch_Permissive_Mprotect Failed.");
    }
}

void Patch_Performance_Mprotect_HOUDINI11_38765(){
    int res = 0;
    #ifdef IS32BIT

    #else
        res |= PatchHex_32(nbbase, 0x309B42, 0xEE2F89E8, 0x90909090);
        res |= PatchHex_8(nbbase, 0x309B46, 0xff, 0x90);
    #endif
    if (res){
        error_print("Patch_Performance_Mprotect failed.");
    }
}

void Patch_Permissive_Mprotect2_Houdini12_38818(){
    int res = 0;
    #ifdef IS32BIT

    #else
        
        res |= PatchHex_8(nbbase, 0x2f3cd0, 0xfb, 0xff);
    #endif
    if (res){
        error_print("Patch_Permissive_Mprotect2 failed.");
    }

}



void Patch_Permissive_pkeyMprotect2_Houdini12_38818(){
    int res = 0;
    #ifdef IS32BIT
    
    #else
        res |= PatchHex_32(nbbase, 0x2f3db7, 0x02F1BA0F, 0xF8909090);
    #endif
    if (res){
        error_print("Patch_Permissive_pkeyMprotect2 failed.");
    }
}

void Patch_Permissive_Mprotect2_Houdini11_38765(){
     int res = 0;
    #ifdef IS32BIT
    
    #else
        res |= PatchHex_8(nbbase, 0x30647a, 0xfb, 0xff);
    #endif
    if (res){
        error_print("Patch_Permissive_Mprotect2 failed.");
    }
}

void Patch_Permissive_pkeyMprotect2_Houdini11_38765(){
     int res = 0;
    #ifdef IS32BIT
    
    #else
        res |= PatchHex_8(nbbase, 0x306552, 0xfb, 0xff);
    #endif
    if (res){
        error_print("Patch_Permissive_pkeyMprotect2 failed.");
    }
}

void Patch_Permissive_Mprotect2_Houdini13_39190(){
      int res = 0;
    #ifdef IS32BIT
    
    #else
        res |= PatchHex_32(nbbase, 0x2eff38, 0xF7BA0F41, 0x90909090);
        res |= PatchHex_8(nbbase, 0x2eff3c, 0x02, 0xF8);
    #endif
    if (res){
        error_print("Patch_Permissive_Mprotect2 failed.");
    }
}

void Patch_Permissive_pkeyMprotect2_Houdini13_39190(){
     int res = 0;
    #ifdef IS32BIT
    
    #else
        res |= PatchHex_32(nbbase, 0x2f0028, 0xF6BA0F41, 0x90909090);
        res |= PatchHex_8(nbbase, 0x2f002c, 0x02, 0xF8);
    #endif
    if (res){
        error_print("Patch_Permissive_pkeyMprotect2 failed.");
    }
}
//Return 0 if we want to execute the function, 1 if we want to skip it
extern "C"
int Unk_Function_Hook_helper(void* dlhandle_idk){
    if (dlhandle_idk){
        uint8_t* workaroundvar = (uint8_t*)dlhandle_idk + 408; //This is here to workaround the compiler from multiplying the offset by 8
        char* dlname = *(char**)workaroundvar;//408 offset contains the dl name..... I think
        if (dlname){ //dlname can be null..... Who could have thought
            int isequal = strcmp(dlname, "libimg_utils.so");
            if (isequal == 0){
                debug_print("Skipped %s, dlhandle_idk is %lld", dlname, (unsigned long long)dlhandle_idk);
                return 1; //we skip it... IDK WHY
            }
        }
    }
    return 0;
}
__attribute__((naked))
void Unk_Function_Caller(){
    __asm__ volatile( ".intel_syntax\n"//Perserve Registers value and call the helper function
        "PUSH rax\n"
        "PUSH rbx\n"
        "PUSH rcx\n"
        "PUSH rdx\n"
        "PUSH rsi\n"
        "PUSH rdi\n"
        "PUSH R8\n"
        "PUSH R9\n"
        "PUSH R10\n"
        "PUSH R11\n"
        "PUSH R12\n"
        "PUSH R13\n"
        "PUSH R14\n"
        "PUSH R15\n"
        "CALL Unk_Function_Hook_helper\n"
    );
    __asm__ volatile(".intel_syntax\n" //Copy the preserved register value. And either continue executing the function or skip it
        "TEST rax,rax\n"
        "POP R15\n"
        "POP R14\n"
        "POP R13\n"
        "POP R12\n"
        "POP R11\n"
        "POP R10\n"
        "POP R9\n"
        "POP R8\n"
        "POP rdi\n"
        "POP rsi\n"
        "POP rdx\n"
        "POP rcx\n"
        "POP rbx\n"
        "POP rax\n"
        "JZ contexec\n"
        "POP rax\n"
        "RET\n"
        "contexec:\n"
        "POP rax\n"
        "PUSH rbp\n"
        "SUB rsp,0x410\n"
        "PUSH rax\n"
        "RET\n"
    );

}



void Patch_Hook_Unk_Function_Houdini11_38765(){
     int res = 0;
    #ifdef IS32BIT
    
    #else
       res |= PatchHex_8(nbbase, 0x363b60, 0x55, 0xe8); //CALL
       res |= PatchHex_32(nbbase, 0x363b61, 0x10EC8148,  (char*)Unk_Function_Caller-((char*)nbbase+0x363b65)); //WTF is this? Practically black magic
       res |= PatchHex_8(nbbase,0x363b65 , 0x04, 0x90);
       res |= PatchHex_8(nbbase,0x363b66 , 0x00, 0x90);
       res |= PatchHex_8(nbbase,0x363b67 , 0x0, 0x90);
    #endif
    if (res){
        error_print("Hook_Unk_Function failed.");
    }
}

extern "C"
int dlopen_internal_hook(char* andr_namespace,char* dlname){
    debug_print("Dlopened lib: %s", dlname);
    if (!dlname){
        return 0;
    }
    char* found = nullptr;
    found = strstr(dlname, "libneuralnetworks.so");
    if (found){
        debug_print("Skipped %s", dlname);
        return 1;
    }
    found = strstr(dlname, "librvcapture_camera.so");
    if (found){
        debug_print("Skipped %s", dlname);
        return 1;
    }

    return 0;
     //continue execution as normal
}


void dlopenext_internal_hook_func_caller(){
    __asm__ volatile( 
        ".intel_syntax\n"
        "PUSH rax\n"
        "PUSH rbx\n"
        "PUSH rcx\n"
        "PUSH rdx\n"
        "PUSH rsi\n"
        "PUSH rdi\n"
        "PUSH R8\n"
        "PUSH R9\n"
        "PUSH R10\n"
        "PUSH R11\n"
        "PUSH R12\n"
        "PUSH R13\n"
        "PUSH R14\n"
        "PUSH R15\n"
        "CALL dlopen_internal_hook\n"
        "TEST rax,rax\n"
        "POP R15\n"
        "POP R14\n"
        "POP R13\n"
        "POP R12\n"
        "POP R11\n"
        "POP R10\n"
        "POP R9\n"
        "POP R8\n"
        "POP rdi\n"
        "POP rsi\n"
        "POP rdx\n"
        "POP rcx\n"
        "POP rbx\n"
        "POP rax\n"
        "JZ contexec1\n"
        "POP rax\n"
        "XOR rax,rax\n"
        "RET\n"
        "contexec1:\n"
        "POP rax\n"
        "PUSH R12\n"
        "PUSH R13\n"
        "PUSH r14\n"
        "PUSH rax\n"
        "RET\n"
    );
}

void Patch_Hook_Internal_dlopenext_Houdini11_38765(){
     int res = 0;
    #ifdef IS32BIT
    
    #else
        res |= PatchHex_8(nbbase, 0x3614a0, 0x41, 0xe8);
        res |= PatchHex_32(nbbase, 0x3614a1, 0x41554154, (char*)dlopenext_internal_hook_func_caller-((char*)nbbase+0x3614a5));
        res |= PatchHex_8(nbbase, 0x3614a5, 0x56, 0x90);
    #endif
    if (res){
        error_print("Hook_dlopenext failed.");
    }
}

void Patch_Permissive_Mprotect3_Houdini11_38765(){
    int res = 0;
     #ifdef IS32BIT
    
    #else
        res |= PatchHex_8(nbbase, 0x30715b, 0xfb, 0xff);
    #endif
    if (res){
        error_print("Patch_Permissive_Mprotect3 failed.");
    }
}