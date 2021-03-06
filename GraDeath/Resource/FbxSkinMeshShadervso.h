#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 6.3.9600.16384
//
//
// Buffer Definitions: 
//
// cbuffer globalBuffer
// {
//
//   float4x4 world;                    // Offset:    0 Size:    64
//   float4x4 wvp;                      // Offset:   64 Size:    64
//   float4x4 constBoneWorld[255];      // Offset:  128 Size: 16320
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// globalBuffer                      cbuffer      NA          NA    0        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// POSITION                 0   xyz         0     NONE   float   xyz 
// NORMAL                   0   xyz         1     NONE   float   xyz 
// TEXCOORD                 0   xy          2     NONE   float   xy  
// BONE_INDEX               0   xyzw        3     NONE    uint   xyzw
// BONE_WEIGHT              0   xyzw        4     NONE   float   xyzw
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_Position              0   xyzw        0      POS   float   xyzw
// NORMAL                   0   xyz         1     NONE   float   xyz 
// TEXCOORD                 0   xy          2     NONE   float   xy  
// COLOR                    0   xyzw        3     NONE   float       
//
vs_4_0
dcl_constantbuffer cb0[1028], dynamicIndexed
dcl_input v0.xyz
dcl_input v1.xyz
dcl_input v2.xy
dcl_input v3.xyzw
dcl_input v4.xyzw
dcl_output_siv o0.xyzw, position
dcl_output o1.xyz
dcl_output o2.xy
dcl_temps 4
mul r0.xyz, v0.xyzx, l(-1.000000, 1.000000, 1.000000, 0.000000)
mov r0.w, l(1.000000)
ishl r1.xyzw, v3.xyzw, l(2)
dp4 r2.x, r0.xyzw, cb0[r1.y + 8].xyzw
dp4 r2.y, r0.xyzw, cb0[r1.y + 9].xyzw
dp4 r2.z, r0.xyzw, cb0[r1.y + 10].xyzw
dp4 r2.w, r0.xyzw, cb0[r1.y + 11].xyzw
mul r2.xyzw, r2.xyzw, v4.yyyy
dp4 r3.x, r0.xyzw, cb0[r1.x + 8].xyzw
dp4 r3.y, r0.xyzw, cb0[r1.x + 9].xyzw
dp4 r3.z, r0.xyzw, cb0[r1.x + 10].xyzw
dp4 r3.w, r0.xyzw, cb0[r1.x + 11].xyzw
mad r2.xyzw, v4.xxxx, r3.xyzw, r2.xyzw
dp4 r3.x, r0.xyzw, cb0[r1.z + 8].xyzw
dp4 r3.y, r0.xyzw, cb0[r1.z + 9].xyzw
dp4 r3.z, r0.xyzw, cb0[r1.z + 10].xyzw
dp4 r3.w, r0.xyzw, cb0[r1.z + 11].xyzw
mad r2.xyzw, v4.zzzz, r3.xyzw, r2.xyzw
dp4 r3.x, r0.xyzw, cb0[r1.w + 8].xyzw
dp4 r3.y, r0.xyzw, cb0[r1.w + 9].xyzw
dp4 r3.z, r0.xyzw, cb0[r1.w + 10].xyzw
dp4 r3.w, r0.xyzw, cb0[r1.w + 11].xyzw
mad r0.xyzw, v4.wwww, r3.xyzw, r2.xyzw
dp4 o0.x, r0.xyzw, cb0[4].xyzw
dp4 o0.y, r0.xyzw, cb0[5].xyzw
dp4 o0.z, r0.xyzw, cb0[6].xyzw
dp4 o0.w, r0.xyzw, cb0[7].xyzw
dp3 r0.x, v1.xyzx, cb0[r1.y + 8].xyzx
dp3 r0.y, v1.xyzx, cb0[r1.y + 9].xyzx
dp3 r0.z, v1.xyzx, cb0[r1.y + 10].xyzx
mul r0.xyz, r0.xyzx, v4.yyyy
dp3 r2.x, v1.xyzx, cb0[r1.x + 8].xyzx
dp3 r2.y, v1.xyzx, cb0[r1.x + 9].xyzx
dp3 r2.z, v1.xyzx, cb0[r1.x + 10].xyzx
mad r0.xyz, v4.xxxx, r2.xyzx, r0.xyzx
dp3 r2.x, v1.xyzx, cb0[r1.z + 8].xyzx
dp3 r2.y, v1.xyzx, cb0[r1.z + 9].xyzx
dp3 r2.z, v1.xyzx, cb0[r1.z + 10].xyzx
mad r0.xyz, v4.zzzz, r2.xyzx, r0.xyzx
dp3 r1.x, v1.xyzx, cb0[r1.w + 8].xyzx
dp3 r1.y, v1.xyzx, cb0[r1.w + 9].xyzx
dp3 r1.z, v1.xyzx, cb0[r1.w + 10].xyzx
mad r0.xyz, v4.wwww, r1.xyzx, r0.xyzx
dp3 r1.x, r0.xyzx, cb0[0].xyzx
dp3 r1.y, r0.xyzx, cb0[1].xyzx
dp3 r1.z, r0.xyzx, cb0[2].xyzx
dp3 r0.x, r1.xyzx, r1.xyzx
rsq r0.x, r0.x
mul o1.xyz, r0.xxxx, r1.xyzx
mov o2.xy, v2.xyxx
ret 
// Approximately 51 instruction slots used
#endif

const BYTE g_SkinMeshVS[] =
{
     68,  88,  66,  67, 199, 221, 
    189,  26, 227,  63, 116, 122, 
     94,  40,  89,  41, 210, 212, 
     28, 210,   1,   0,   0,   0, 
    184,  10,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
     88,   1,   0,   0,  16,   2, 
      0,   0, 164,   2,   0,   0, 
     60,  10,   0,   0,  82,  68, 
     69,  70,  28,   1,   0,   0, 
      1,   0,   0,   0,  76,   0, 
      0,   0,   1,   0,   0,   0, 
     28,   0,   0,   0,   0,   4, 
    254, 255,   0,   1,   0,   0, 
    232,   0,   0,   0,  60,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
    103, 108, 111,  98,  97, 108, 
     66, 117, 102, 102, 101, 114, 
      0, 171, 171, 171,  60,   0, 
      0,   0,   3,   0,   0,   0, 
    100,   0,   0,   0,  64,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 172,   0, 
      0,   0,   0,   0,   0,   0, 
     64,   0,   0,   0,   2,   0, 
      0,   0, 180,   0,   0,   0, 
      0,   0,   0,   0, 196,   0, 
      0,   0,  64,   0,   0,   0, 
     64,   0,   0,   0,   2,   0, 
      0,   0, 180,   0,   0,   0, 
      0,   0,   0,   0, 200,   0, 
      0,   0, 128,   0,   0,   0, 
    192,  63,   0,   0,   2,   0, 
      0,   0, 216,   0,   0,   0, 
      0,   0,   0,   0, 119, 111, 
    114, 108, 100,   0, 171, 171, 
      3,   0,   3,   0,   4,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 119, 118, 
    112,   0,  99, 111, 110, 115, 
    116,  66, 111, 110, 101,  87, 
    111, 114, 108, 100,   0, 171, 
      3,   0,   3,   0,   4,   0, 
      4,   0, 255,   0,   0,   0, 
      0,   0,   0,   0,  77, 105, 
     99, 114, 111, 115, 111, 102, 
    116,  32,  40,  82,  41,  32, 
     72,  76,  83,  76,  32,  83, 
    104,  97, 100, 101, 114,  32, 
     67, 111, 109, 112, 105, 108, 
    101, 114,  32,  54,  46,  51, 
     46,  57,  54,  48,  48,  46, 
     49,  54,  51,  56,  52,   0, 
    171, 171,  73,  83,  71,  78, 
    176,   0,   0,   0,   5,   0, 
      0,   0,   8,   0,   0,   0, 
    128,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   7,   7,   0,   0, 
    137,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   1,   0, 
      0,   0,   7,   7,   0,   0, 
    144,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0,   3,   3,   0,   0, 
    153,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   3,   0, 
      0,   0,  15,  15,   0,   0, 
    164,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   4,   0, 
      0,   0,  15,  15,   0,   0, 
     80,  79,  83,  73,  84,  73, 
     79,  78,   0,  78,  79,  82, 
     77,  65,  76,   0,  84,  69, 
     88,  67,  79,  79,  82,  68, 
      0,  66,  79,  78,  69,  95, 
     73,  78,  68,  69,  88,   0, 
     66,  79,  78,  69,  95,  87, 
     69,  73,  71,  72,  84,   0, 
     79,  83,  71,  78, 140,   0, 
      0,   0,   4,   0,   0,   0, 
      8,   0,   0,   0, 104,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0, 116,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   1,   0,   0,   0, 
      7,   8,   0,   0, 123,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   2,   0,   0,   0, 
      3,  12,   0,   0, 132,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   3,   0,   0,   0, 
     15,  15,   0,   0,  83,  86, 
     95,  80, 111, 115, 105, 116, 
    105, 111, 110,   0,  78,  79, 
     82,  77,  65,  76,   0,  84, 
     69,  88,  67,  79,  79,  82, 
     68,   0,  67,  79,  76,  79, 
     82,   0, 171, 171,  83,  72, 
     68,  82, 144,   7,   0,   0, 
     64,   0,   1,   0, 228,   1, 
      0,   0,  89,   8,   0,   4, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   4,   4,   0,   0, 
     95,   0,   0,   3, 114,  16, 
     16,   0,   0,   0,   0,   0, 
     95,   0,   0,   3, 114,  16, 
     16,   0,   1,   0,   0,   0, 
     95,   0,   0,   3,  50,  16, 
     16,   0,   2,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,   3,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,   4,   0,   0,   0, 
    103,   0,   0,   4, 242,  32, 
     16,   0,   0,   0,   0,   0, 
      1,   0,   0,   0, 101,   0, 
      0,   3, 114,  32,  16,   0, 
      1,   0,   0,   0, 101,   0, 
      0,   3,  50,  32,  16,   0, 
      2,   0,   0,   0, 104,   0, 
      0,   2,   4,   0,   0,   0, 
     56,   0,   0,  10, 114,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  18,  16,   0,   0,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0, 128, 191,   0,   0, 
    128,  63,   0,   0, 128,  63, 
      0,   0,   0,   0,  54,   0, 
      0,   5, 130,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0, 128,  63, 
     41,   0,   0,   7, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  30,  16,   0,   3,   0, 
      0,   0,   1,  64,   0,   0, 
      2,   0,   0,   0,  17,   0, 
      0,  10,  18,   0,  16,   0, 
      2,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   6,   0,   0, 
      0,   0,   8,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,  17,   0,   0,  10, 
     34,   0,  16,   0,   2,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   6,   0,   0,   0,   0, 
      9,   0,   0,   0,  26,   0, 
     16,   0,   1,   0,   0,   0, 
     17,   0,   0,  10,  66,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   6, 
      0,   0,   0,   0,  10,   0, 
      0,   0,  26,   0,  16,   0, 
      1,   0,   0,   0,  17,   0, 
      0,  10, 130,   0,  16,   0, 
      2,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   6,   0,   0, 
      0,   0,  11,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,  56,   0,   0,   7, 
    242,   0,  16,   0,   2,   0, 
      0,   0,  70,  14,  16,   0, 
      2,   0,   0,   0,  86,  21, 
     16,   0,   4,   0,   0,   0, 
     17,   0,   0,  10,  18,   0, 
     16,   0,   3,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   6, 
      0,   0,   0,   0,   8,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,  17,   0, 
      0,  10,  34,   0,  16,   0, 
      3,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   6,   0,   0, 
      0,   0,   9,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,  17,   0,   0,  10, 
     66,   0,  16,   0,   3,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   6,   0,   0,   0,   0, 
     10,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     17,   0,   0,  10, 130,   0, 
     16,   0,   3,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   6, 
      0,   0,   0,   0,  11,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,  50,   0, 
      0,   9, 242,   0,  16,   0, 
      2,   0,   0,   0,   6,  16, 
     16,   0,   4,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70,  14,  16,   0, 
      2,   0,   0,   0,  17,   0, 
      0,  10,  18,   0,  16,   0, 
      3,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   6,   0,   0, 
      0,   0,   8,   0,   0,   0, 
     42,   0,  16,   0,   1,   0, 
      0,   0,  17,   0,   0,  10, 
     34,   0,  16,   0,   3,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   6,   0,   0,   0,   0, 
      9,   0,   0,   0,  42,   0, 
     16,   0,   1,   0,   0,   0, 
     17,   0,   0,  10,  66,   0, 
     16,   0,   3,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   6, 
      0,   0,   0,   0,  10,   0, 
      0,   0,  42,   0,  16,   0, 
      1,   0,   0,   0,  17,   0, 
      0,  10, 130,   0,  16,   0, 
      3,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   6,   0,   0, 
      0,   0,  11,   0,   0,   0, 
     42,   0,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,   9, 
    242,   0,  16,   0,   2,   0, 
      0,   0, 166,  26,  16,   0, 
      4,   0,   0,   0,  70,  14, 
     16,   0,   3,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  17,   0,   0,  10, 
     18,   0,  16,   0,   3,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   6,   0,   0,   0,   0, 
      8,   0,   0,   0,  58,   0, 
     16,   0,   1,   0,   0,   0, 
     17,   0,   0,  10,  34,   0, 
     16,   0,   3,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   6, 
      0,   0,   0,   0,   9,   0, 
      0,   0,  58,   0,  16,   0, 
      1,   0,   0,   0,  17,   0, 
      0,  10,  66,   0,  16,   0, 
      3,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   6,   0,   0, 
      0,   0,  10,   0,   0,   0, 
     58,   0,  16,   0,   1,   0, 
      0,   0,  17,   0,   0,  10, 
    130,   0,  16,   0,   3,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   6,   0,   0,   0,   0, 
     11,   0,   0,   0,  58,   0, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,   9, 242,   0, 
     16,   0,   0,   0,   0,   0, 
    246,  31,  16,   0,   4,   0, 
      0,   0,  70,  14,  16,   0, 
      3,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     17,   0,   0,   8,  18,  32, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   4,   0, 
      0,   0,  17,   0,   0,   8, 
     34,  32,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      5,   0,   0,   0,  17,   0, 
      0,   8,  66,  32,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   6,   0,   0,   0, 
     17,   0,   0,   8, 130,  32, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   7,   0, 
      0,   0,  16,   0,   0,  10, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  70,  18,  16,   0, 
      1,   0,   0,   0,  70, 130, 
     32,   6,   0,   0,   0,   0, 
      8,   0,   0,   0,  26,   0, 
     16,   0,   1,   0,   0,   0, 
     16,   0,   0,  10,  34,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  18,  16,   0,   1,   0, 
      0,   0,  70, 130,  32,   6, 
      0,   0,   0,   0,   9,   0, 
      0,   0,  26,   0,  16,   0, 
      1,   0,   0,   0,  16,   0, 
      0,  10,  66,   0,  16,   0, 
      0,   0,   0,   0,  70,  18, 
     16,   0,   1,   0,   0,   0, 
     70, 130,  32,   6,   0,   0, 
      0,   0,  10,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,  56,   0,   0,   7, 
    114,   0,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  86,  21, 
     16,   0,   4,   0,   0,   0, 
     16,   0,   0,  10,  18,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  18,  16,   0,   1,   0, 
      0,   0,  70, 130,  32,   6, 
      0,   0,   0,   0,   8,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,  16,   0, 
      0,  10,  34,   0,  16,   0, 
      2,   0,   0,   0,  70,  18, 
     16,   0,   1,   0,   0,   0, 
     70, 130,  32,   6,   0,   0, 
      0,   0,   9,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,  16,   0,   0,  10, 
     66,   0,  16,   0,   2,   0, 
      0,   0,  70,  18,  16,   0, 
      1,   0,   0,   0,  70, 130, 
     32,   6,   0,   0,   0,   0, 
     10,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,   9, 114,   0, 
     16,   0,   0,   0,   0,   0, 
      6,  16,  16,   0,   4,   0, 
      0,   0,  70,   2,  16,   0, 
      2,   0,   0,   0,  70,   2, 
     16,   0,   0,   0,   0,   0, 
     16,   0,   0,  10,  18,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  18,  16,   0,   1,   0, 
      0,   0,  70, 130,  32,   6, 
      0,   0,   0,   0,   8,   0, 
      0,   0,  42,   0,  16,   0, 
      1,   0,   0,   0,  16,   0, 
      0,  10,  34,   0,  16,   0, 
      2,   0,   0,   0,  70,  18, 
     16,   0,   1,   0,   0,   0, 
     70, 130,  32,   6,   0,   0, 
      0,   0,   9,   0,   0,   0, 
     42,   0,  16,   0,   1,   0, 
      0,   0,  16,   0,   0,  10, 
     66,   0,  16,   0,   2,   0, 
      0,   0,  70,  18,  16,   0, 
      1,   0,   0,   0,  70, 130, 
     32,   6,   0,   0,   0,   0, 
     10,   0,   0,   0,  42,   0, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,   9, 114,   0, 
     16,   0,   0,   0,   0,   0, 
    166,  26,  16,   0,   4,   0, 
      0,   0,  70,   2,  16,   0, 
      2,   0,   0,   0,  70,   2, 
     16,   0,   0,   0,   0,   0, 
     16,   0,   0,  10,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  18,  16,   0,   1,   0, 
      0,   0,  70, 130,  32,   6, 
      0,   0,   0,   0,   8,   0, 
      0,   0,  58,   0,  16,   0, 
      1,   0,   0,   0,  16,   0, 
      0,  10,  34,   0,  16,   0, 
      1,   0,   0,   0,  70,  18, 
     16,   0,   1,   0,   0,   0, 
     70, 130,  32,   6,   0,   0, 
      0,   0,   9,   0,   0,   0, 
     58,   0,  16,   0,   1,   0, 
      0,   0,  16,   0,   0,  10, 
     66,   0,  16,   0,   1,   0, 
      0,   0,  70,  18,  16,   0, 
      1,   0,   0,   0,  70, 130, 
     32,   6,   0,   0,   0,   0, 
     10,   0,   0,   0,  58,   0, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,   9, 114,   0, 
     16,   0,   0,   0,   0,   0, 
    246,  31,  16,   0,   4,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   0,   0,   0,   0, 
     16,   0,   0,   8,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     70,   2,  16,   0,   0,   0, 
      0,   0,  70, 130,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  16,   0,   0,   8, 
     34,   0,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  70, 130, 
     32,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,  16,   0, 
      0,   8,  66,   0,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   0,   0,   0,   0, 
     70, 130,  32,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
     16,   0,   0,   7,  18,   0, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  68,   0, 
      0,   5,  18,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
     56,   0,   0,   7, 114,  32, 
     16,   0,   1,   0,   0,   0, 
      6,   0,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  54,   0, 
      0,   5,  50,  32,  16,   0, 
      2,   0,   0,   0,  70,  16, 
     16,   0,   2,   0,   0,   0, 
     62,   0,   0,   1,  83,  84, 
     65,  84, 116,   0,   0,   0, 
     51,   0,   0,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      8,   0,   0,   0,  47,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0
};
