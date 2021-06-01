/* Generated from 'wasm2c.c.tmpl' by wasm2c_tmpl.py, do not edit! */
const char SECTION_NAME(includes)[] =
"/* Automically generated by wasm2c */\n"
"#include <math.h>\n"
"#include <string.h>\n"
"#include <stdlib.h>\n"
;

const char SECTION_NAME(declarations)[] =
"#if defined(_MSC_VER)\n"
"  #define UNLIKELY(x) (x)\n"
"  #define LIKELY(x) (x)\n"
"#else\n"
"  #define UNLIKELY(x) __builtin_expect(!!(x), 0)\n"
"  #define LIKELY(x) __builtin_expect(!!(x), 1)\n"
"#endif\n"
"\n"
"#define TRAP(x) (wasm_rt_trap(WASM_RT_TRAP_##x), 0)\n"
"\n"
"#define FUNC_PROLOGUE\n"
"\n"
"#define FUNC_EPILOGUE\n"
"\n"
"#define UNREACHABLE TRAP(UNREACHABLE)\n"
"\n"
"#define CALL_INDIRECT(table, t, ft, x, func_types, ...) \\\n"
"  (LIKELY((x) < table.size && table.data[x].func &&     \\\n"
"          table.data[x].func_type == func_types[ft])    \\\n"
"       || TRAP(CALL_INDIRECT)                           \\\n"
"       , ((t)table.data[x].func)(__VA_ARGS__))\n"
"\n"
"#if WASM_USING_GUARD_PAGES == 1\n"
"#define MEMCHECK(mem, a, t)\n"
"#else\n"
"#define MEMCHECK(mem, a, t)  \\\n"
"  if (UNLIKELY((a) + sizeof(t) > mem->size)) TRAP(OOB)\n"
"#endif\n"
"\n"
"#if WABT_BIG_ENDIAN\n"
"static inline void load_data(void *dest, const void *src, size_t n) {\n"
"  size_t i = 0;\n"
"  u8 *dest_chars = dest;\n"
"  memcpy(dest, src, n);\n"
"  for (i = 0; i < (n>>1); i++) {\n"
"    u8 cursor = dest_chars[i];\n"
"    dest_chars[i] = dest_chars[n - i - 1];\n"
"    dest_chars[n - i - 1] = cursor;\n"
"  }\n"
"}\n"
"#define LOAD_DATA(m, o, i, s) load_data(&(m.data[m.size - o - s]), i, s)\n"
"#define DEFINE_LOAD(name, t1, t2, t3)                                                 \\\n"
"  static inline t3 name(wasm_rt_memory_t* mem, u64 addr) {                            \\\n"
"    MEMCHECK(mem, addr, t1);                                                          \\\n"
"    t1 result;                                                                        \\\n"
"    memcpy(&result, &mem->data[mem->size - addr - sizeof(t1)], sizeof(t1)); \\\n"
"    return (t3)(t2)result;                                                            \\\n"
"  }\n"
"\n"
"#define DEFINE_STORE(name, t1, t2)                                                     \\\n"
"  static inline void name(wasm_rt_memory_t* mem, u64 addr, t2 value) {                 \\\n"
"    MEMCHECK(mem, addr, t1);                                                           \\\n"
"    t1 wrapped = (t1)value;                                                            \\\n"
"    memcpy(&mem->data[mem->size - addr - sizeof(t1)], &wrapped, sizeof(t1)); \\\n"
"  }\n"
"#else\n"
"static inline void load_data(void *dest, const void *src, size_t n) {\n"
"  memcpy(dest, src, n);\n"
"}\n"
"#define LOAD_DATA(m, o, i, s) load_data(&(m.data[o]), i, s)\n"
"#define DEFINE_LOAD(name, t1, t2, t3)                        \\\n"
"  static inline t3 name(wasm_rt_memory_t* mem, u64 addr) {   \\\n"
"    MEMCHECK(mem, addr, t1);                                 \\\n"
"    t1 result;                                               \\\n"
"    memcpy(&result, &mem->data[addr], sizeof(t1)); \\\n"
"    return (t3)(t2)result;                                   \\\n"
"  }\n"
"\n"
"#define DEFINE_STORE(name, t1, t2)                                     \\\n"
"  static inline void name(wasm_rt_memory_t* mem, u64 addr, t2 value) { \\\n"
"    MEMCHECK(mem, addr, t1);                                           \\\n"
"    t1 wrapped = (t1)value;                                            \\\n"
"    memcpy(&mem->data[addr], &wrapped, sizeof(t1));          \\\n"
"  }\n"
"#endif\n"
"\n"
"DEFINE_LOAD(i32_load, u32, u32, u32);\n"
"DEFINE_LOAD(i64_load, u64, u64, u64);\n"
"DEFINE_LOAD(f32_load, f32, f32, f32);\n"
"DEFINE_LOAD(f64_load, f64, f64, f64);\n"
"DEFINE_LOAD(i32_load8_s, s8, s32, u32);\n"
"DEFINE_LOAD(i64_load8_s, s8, s64, u64);\n"
"DEFINE_LOAD(i32_load8_u, u8, u32, u32);\n"
"DEFINE_LOAD(i64_load8_u, u8, u64, u64);\n"
"DEFINE_LOAD(i32_load16_s, s16, s32, u32);\n"
"DEFINE_LOAD(i64_load16_s, s16, s64, u64);\n"
"DEFINE_LOAD(i32_load16_u, u16, u32, u32);\n"
"DEFINE_LOAD(i64_load16_u, u16, u64, u64);\n"
"DEFINE_LOAD(i64_load32_s, s32, s64, u64);\n"
"DEFINE_LOAD(i64_load32_u, u32, u64, u64);\n"
"DEFINE_STORE(i32_store, u32, u32);\n"
"DEFINE_STORE(i64_store, u64, u64);\n"
"DEFINE_STORE(f32_store, f32, f32);\n"
"DEFINE_STORE(f64_store, f64, f64);\n"
"DEFINE_STORE(i32_store8, u8, u32);\n"
"DEFINE_STORE(i32_store16, u16, u32);\n"
"DEFINE_STORE(i64_store8, u8, u64);\n"
"DEFINE_STORE(i64_store16, u16, u64);\n"
"DEFINE_STORE(i64_store32, u32, u64);\n"
"\n"
"#if defined(_MSC_VER)\n"
"  #include <intrin.h>\n"
"\n"
"  #if _M_IX86\n"
"  static inline unsigned long LowDword(unsigned __int64 value) {\n"
"    return (unsigned long)value;\n"
"  }\n"
"\n"
"  static inline unsigned long HighDword(unsigned __int64 value) {\n"
"    unsigned long high;\n"
"    memcpy(&high, (unsigned char*)&value + sizeof(high), sizeof(high));\n"
"    return high;\n"
"  }\n"
"  #endif\n"
"\n"
"  static inline int Clz(unsigned long mask) {\n"
"    if (mask == 0)\n"
"      return 32;\n"
"\n"
"    unsigned long index;\n"
"    _BitScanReverse(&index, mask);\n"
"    return sizeof(unsigned long) * 8 - (index + 1);\n"
"  }\n"
"\n"
"  static inline int Clz(unsigned int mask) {\n"
"    return Clz((unsigned long)mask);\n"
"  }\n"
"\n"
"  static inline int Clz(unsigned __int64 mask) {\n"
"  #if _M_X64\n"
"    if (mask == 0)\n"
"      return 64;\n"
"\n"
"    unsigned long index;\n"
"    _BitScanReverse64(&index, mask);\n"
"    return sizeof(unsigned __int64) * 8 - (index + 1);\n"
"  #elif _M_IX86\n"
"    int result = Clz(HighDword(mask));\n"
"    if (result == 32)\n"
"      result += Clz(LowDword(mask));\n"
"\n"
"    return result;\n"
"  #else\n"
"  #error unexpected architecture\n"
"  #endif\n"
"  }\n"
"\n"
"  static inline int Ctz(unsigned long mask) {\n"
"    if (mask == 0)\n"
"      return 32;\n"
"\n"
"    unsigned long index;\n"
"    _BitScanForward(&index, mask);\n"
"    return index;\n"
"  }\n"
"\n"
"  static inline int Ctz(unsigned int mask) {\n"
"    return Ctz((unsigned long)mask);\n"
"  }\n"
"\n"
"  static inline int Ctz(unsigned __int64 mask) {\n"
"  #if _M_X64\n"
"    if (mask == 0)\n"
"      return 64;\n"
"\n"
"    unsigned long index;\n"
"    _BitScanForward64(&index, mask);\n"
"    return index;\n"
"  #elif _M_IX86\n"
"    int result = Ctz(LowDword(mask));\n"
"    if (result == 32)\n"
"      result += Ctz(HighDword(mask));\n"
"\n"
"    return result;\n"
"  #else\n"
"  #error unexpected architecture\n"
"  #endif\n"
"  }\n"
"\n"
"  static inline int Popcount(uint8_t value) {\n"
"    return __popcnt(value);\n"
"  }\n"
"\n"
"  static inline int Popcount(unsigned long value) {\n"
"    return __popcnt(value);\n"
"  }\n"
"\n"
"  static inline int Popcount(unsigned int value) {\n"
"    return Popcount((unsigned long)value);\n"
"  }\n"
"\n"
"  static inline int Popcount(unsigned __int64 value) {\n"
"  #if _M_X64\n"
"    return __popcnt64(value);\n"
"  #elif _M_IX86\n"
"    return Popcount(HighDword(value)) + Popcount(LowDword(value));\n"
"  #else\n"
"  #error unexpected architecture\n"
"  #endif\n"
"  }\n"
"\n"
"  #define I32_CLZ(x) ((x) ? Clz(x) : 32)\n"
"  #define I64_CLZ(x) ((x) ? Clz(x) : 64)\n"
"  #define I32_CTZ(x) ((x) ? Ctz(x) : 32)\n"
"  #define I64_CTZ(x) ((x) ? Ctz(x) : 64)\n"
"  #define I32_POPCNT(x) (Popcount(x))\n"
"  #define I64_POPCNT(x) (Popcount(x))\n"
"\n"
"#else\n"
"  #define I32_CLZ(x) ((x) ? __builtin_clz(x) : 32)\n"
"  #define I64_CLZ(x) ((x) ? __builtin_clzll(x) : 64)\n"
"  #define I32_CTZ(x) ((x) ? __builtin_ctz(x) : 32)\n"
"  #define I64_CTZ(x) ((x) ? __builtin_ctzll(x) : 64)\n"
"  #define I32_POPCNT(x) (__builtin_popcount(x))\n"
"  #define I64_POPCNT(x) (__builtin_popcountll(x))\n"
"#endif\n"
"\n"
"#define DIV_S(ut, min, x, y)                                 \\\n"
"   ((UNLIKELY((y) == 0)) ?                TRAP(DIV_BY_ZERO)  \\\n"
"  : (UNLIKELY((x) == min && (y) == -1)) ? TRAP(INT_OVERFLOW) \\\n"
"  : (ut)((x) / (y)))\n"
"\n"
"#define REM_S(ut, min, x, y)                                \\\n"
"   ((UNLIKELY((y) == 0)) ?                TRAP(DIV_BY_ZERO) \\\n"
"  : (UNLIKELY((x) == min && (y) == -1)) ? 0                 \\\n"
"  : (ut)((x) % (y)))\n"
"\n"
"#define I32_DIV_S(x, y) DIV_S(u32, INT32_MIN, (s32)x, (s32)y)\n"
"#define I64_DIV_S(x, y) DIV_S(u64, INT64_MIN, (s64)x, (s64)y)\n"
"#define I32_REM_S(x, y) REM_S(u32, INT32_MIN, (s32)x, (s32)y)\n"
"#define I64_REM_S(x, y) REM_S(u64, INT64_MIN, (s64)x, (s64)y)\n"
"\n"
"#define DIVREM_U(op, x, y) \\\n"
"  ((UNLIKELY((y) == 0)) ? TRAP(DIV_BY_ZERO) : ((x) op (y)))\n"
"\n"
"#define DIV_U(x, y) DIVREM_U(/, x, y)\n"
"#define REM_U(x, y) DIVREM_U(%, x, y)\n"
"\n"
"#define ROTL(x, y, mask) \\\n"
"  (((x) << ((y) & (mask))) | ((x) >> (((mask) - (y) + 1) & (mask))))\n"
"#define ROTR(x, y, mask) \\\n"
"  (((x) >> ((y) & (mask))) | ((x) << (((mask) - (y) + 1) & (mask))))\n"
"\n"
"#define I32_ROTL(x, y) ROTL(x, y, 31)\n"
"#define I64_ROTL(x, y) ROTL(x, y, 63)\n"
"#define I32_ROTR(x, y) ROTR(x, y, 31)\n"
"#define I64_ROTR(x, y) ROTR(x, y, 63)\n"
"\n"
"#define FMIN(x, y)                                          \\\n"
"   ((UNLIKELY((x) != (x))) ? NAN                            \\\n"
"  : (UNLIKELY((y) != (y))) ? NAN                            \\\n"
"  : (UNLIKELY((x) == 0 && (y) == 0)) ? (signbit(x) ? x : y) \\\n"
"  : (x < y) ? x : y)\n"
"\n"
"#define FMAX(x, y)                                          \\\n"
"   ((UNLIKELY((x) != (x))) ? NAN                            \\\n"
"  : (UNLIKELY((y) != (y))) ? NAN                            \\\n"
"  : (UNLIKELY((x) == 0 && (y) == 0)) ? (signbit(x) ? y : x) \\\n"
"  : (x > y) ? x : y)\n"
"\n"
"#define TRUNC_S(ut, st, ft, min, minop, max, x)                             \\\n"
"  ((UNLIKELY((x) != (x)))                        ? TRAP(INVALID_CONVERSION) \\\n"
"   : (UNLIKELY(!((x)minop(min) && (x) < (max)))) ? TRAP(INT_OVERFLOW)       \\\n"
"                                                 : (ut)(st)(x))\n"
"\n"
"#define I32_TRUNC_S_F32(x) TRUNC_S(u32, s32, f32, (f32)INT32_MIN, >=, 2147483648.f, x)\n"
"#define I64_TRUNC_S_F32(x) TRUNC_S(u64, s64, f32, (f32)INT64_MIN, >=, (f32)INT64_MAX, x)\n"
"#define I32_TRUNC_S_F64(x) TRUNC_S(u32, s32, f64, -2147483649., >, 2147483648., x)\n"
"#define I64_TRUNC_S_F64(x) TRUNC_S(u64, s64, f64, (f64)INT64_MIN, >=, (f64)INT64_MAX, x)\n"
"\n"
"#define TRUNC_U(ut, ft, max, x)                                            \\\n"
"  ((UNLIKELY((x) != (x)))                       ? TRAP(INVALID_CONVERSION) \\\n"
"   : (UNLIKELY(!((x) > (ft)-1 && (x) < (max)))) ? TRAP(INT_OVERFLOW)       \\\n"
"                                                : (ut)(x))\n"
"\n"
"#define I32_TRUNC_U_F32(x) TRUNC_U(u32, f32, 4294967296.f, x)\n"
"#define I64_TRUNC_U_F32(x) TRUNC_U(u64, f32, (f32)UINT64_MAX, x)\n"
"#define I32_TRUNC_U_F64(x) TRUNC_U(u32, f64, 4294967296.,  x)\n"
"#define I64_TRUNC_U_F64(x) TRUNC_U(u64, f64, (f64)UINT64_MAX, x)\n"
"\n"
"#define TRUNC_SAT_S(ut, st, ft, min, smin, minop, max, smax, x) \\\n"
"  ((UNLIKELY((x) != (x)))         ? 0                           \\\n"
"   : (UNLIKELY(!((x)minop(min)))) ? smin                        \\\n"
"   : (UNLIKELY(!((x) < (max))))   ? smax                        \\\n"
"                                  : (ut)(st)(x))\n"
"\n"
"#define I32_TRUNC_SAT_S_F32(x) TRUNC_SAT_S(u32, s32, f32, (f32)INT32_MIN, INT32_MIN, >=, 2147483648.f, INT32_MAX, x)\n"
"#define I64_TRUNC_SAT_S_F32(x) TRUNC_SAT_S(u64, s64, f32, (f32)INT64_MIN, INT64_MIN, >=, (f32)INT64_MAX, INT64_MAX, x)\n"
"#define I32_TRUNC_SAT_S_F64(x) TRUNC_SAT_S(u32, s32, f64, -2147483649., INT32_MIN, >, 2147483648., INT32_MAX, x)\n"
"#define I64_TRUNC_SAT_S_F64(x) TRUNC_SAT_S(u64, s64, f64, (f64)INT64_MIN, INT64_MIN, >=, (f64)INT64_MAX, INT64_MAX, x)\n"
"\n"
"#define TRUNC_SAT_U(ut, ft, max, smax, x) \\\n"
"  ((UNLIKELY((x) != (x)))        ? 0      \\\n"
"   : (UNLIKELY(!((x) > (ft)-1))) ? 0      \\\n"
"   : (UNLIKELY(!((x) < (max))))  ? smax   \\\n"
"                                 : (ut)(x))\n"
"\n"
"#define I32_TRUNC_SAT_U_F32(x) TRUNC_SAT_U(u32, f32, 4294967296.f, UINT32_MAX, x)\n"
"#define I64_TRUNC_SAT_U_F32(x) TRUNC_SAT_U(u64, f32, (f32)UINT64_MAX, UINT64_MAX, x)\n"
"#define I32_TRUNC_SAT_U_F64(x) TRUNC_SAT_U(u32, f64, 4294967296., UINT32_MAX,  x)\n"
"#define I64_TRUNC_SAT_U_F64(x) TRUNC_SAT_U(u64, f64, (f64)UINT64_MAX, UINT64_MAX, x)\n"
"\n"
"#define DEFINE_REINTERPRET(name, t1, t2)  \\\n"
"  static inline t2 name(t1 x) {           \\\n"
"    t2 result;                            \\\n"
"    memcpy(&result, &x, sizeof(result));  \\\n"
"    return result;                        \\\n"
"  }\n"
"\n"
"DEFINE_REINTERPRET(f32_reinterpret_i32, u32, f32)\n"
"DEFINE_REINTERPRET(i32_reinterpret_f32, f32, u32)\n"
"DEFINE_REINTERPRET(f64_reinterpret_i64, u64, f64)\n"
"DEFINE_REINTERPRET(i64_reinterpret_f64, f64, u64)\n"
"\n"
;
