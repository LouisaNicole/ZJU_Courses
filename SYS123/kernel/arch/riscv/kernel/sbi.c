#include "types.h"
#include "sbi.h"

struct sbiret sbi_ecall(int ext, int fid, uint64 arg0,
                        uint64 arg1, uint64 arg2,
                        uint64 arg3, uint64 arg4,
                        uint64 arg5)
{
  // struct  sbiret ret_str;
  // long err;
  // long value;

  // int ext_t,fid_t;
  // uint64 arg01,arg11,arg21,arg31,arg41,arg51;

  // __asm__ volatile(
  //   "mv a7, %[ext]\n"
  //   "mv a6, %[fid]\n"
  //   "mv a0, %[arg0]\n"
  //   "mv a1, %[arg1]\n"
  //   "mv a2, %[arg2]\n"
  //   "mv a3, %[arg3]\n"
  //   "mv a4, %[arg4]\n"
  //   "mv a5, %[arg5]\n"
  //   "ecall\n"
  //   "mv %[err], a0\n"
  //   "mv %[value], a1\n"
  //   :[err]"=r"(err),[value]"=r"(value)
  //   :[ext]"r"(ext),[fid]"r"(fid),[arg0]"r"(arg0),[arg1]"r"(arg1),[arg2]"r"(arg2),[arg3]"r"(arg3),[arg4]"r"(arg4),[arg5]"r"(arg5)
  //   :"memory"
  // );
  // ret_str.error = err;
  // ret_str.value = value;
  // return ret_str;
  struct sbiret ret;
  register uint64 a0 asm("a0") = (uint64)(arg0);
  register uint64 a1 asm("a1") = (uint64)(arg1);
  register uint64 a2 asm("a2") = (uint64)(arg2);
  register uint64 a3 asm("a3") = (uint64)(arg3);
  register uint64 a4 asm("a4") = (uint64)(arg4);
  register uint64 a5 asm("a5") = (uint64)(arg5);
  register uint64 a6 asm("a6") = (uint64)(fid);
  register uint64 a7 asm("a7") = (uint64)(ext);
  asm volatile (
      "ecall"
      : "+r" (a0), "+r" (a1)
      : "r" (a2), "r" (a3), "r" (a4), "r" (a5), "r" (a6), "r" (a7)
      : "memory"
  );
  ret.error = a0;
  ret.value = a1;
  return ret;
}
void sbi_set_timer(uint64 time){
  sbi_ecall(0,0,time,0,0,0,0,0);
}