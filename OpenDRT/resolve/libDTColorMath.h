/* ##########################################################################
    libColorMath
    --------------------------------------
    Library of commonly used functions for the Open Display Transform project
    Written by Jed Smith
      https://github.com/jedypod/open-display-transform

*/


/* ##########################################################################
    Custom Structs
    ---------------------------
*/

// Custom 3x3 matrix struct float3x3
typedef struct {
  float3 x, y, z;
} float3x3;

// Struct to hold whitepoint normalization
typedef struct {
  float rec2020, p3d65, p3d60, p3dci, rec709, dcdm;
} wpnorm;




/* ##########################################################################
    Color Conversion Matrices
    ---------------------------
*/


// Gamut conversion Matrices
#define identity_mtx make_float3x3(make_float3(1.0f, 0.0f, 0.0f), make_float3(0.0f, 1.0f, 0.0f), make_float3(0.0f, 0.0f, 1.0f))
#define matrix_ap0_to_xyz make_float3x3(make_float3(0.950362384319f, 0.000000000000f, 0.000093463248f), make_float3(0.343966454268f, 0.728166162968f, -0.072132542729f), make_float3(0.000000000000f, 0.000000000000, 1.089057803154f))
#define matrix_ap1_to_xyz make_float3x3(make_float3(0.660931229591f, 0.133696138859f, 0.155828580260f), make_float3(0.272228747606f, 0.674081742764f, 0.053689509630f), make_float3(-0.006018006243f, 0.004383686464, 1.090692043304f))
#define matrix_p3d65_to_xyz make_float3x3(make_float3(0.486571133137f, 0.265667706728f, 0.198217317462f), make_float3(0.228974640369f, 0.691738605499f, 0.079286918044f), make_float3(-0.000000000000f, 0.045113388449, 1.043944478035f))
#define matrix_p3d60_to_xyz make_float3x3(make_float3(0.504949748516f, 0.264681518078f, 0.183015048504f), make_float3(0.237623393536f, 0.689170777798f, 0.073206014931f), make_float3(-0.000000000000f, 0.044945921749f, 0.963879227638f))
#define matrix_p3dci_to_xyz make_float3x3(make_float3(0.445170015097f, 0.277134418488f, 0.172282665968f), make_float3(0.209491759539f, 0.721595287323f, 0.068913064897f), make_float3(-0.000000000000f, 0.047060567886f, 0.907355427742f))
#define matrix_rec2020_to_xyz make_float3x3(make_float3(0.636958122253f, 0.144616916776f, 0.168880969286f), make_float3(0.262700229883f, 0.677998125553f, 0.059301715344f), make_float3(0.000000000000f, 0.028072696179, 1.060985088348f))
#define matrix_rec709_to_xyz make_float3x3(make_float3(0.412390917540f, 0.357584357262f, 0.180480793118f), make_float3(0.212639078498f, 0.715168714523f, 0.072192311287f), make_float3(0.019330825657f, 0.119194783270f, 0.950532138348f))
#define matrix_arriwg_to_xyz make_float3x3(make_float3(0.638007640839f, 0.214703813195f, 0.097744457424f), make_float3(0.291953772306f, 0.823840856552f, -0.115794822574f), make_float3(0.002798279049f, -0.067034222186, 1.153293848038f))
#define matrix_redwg_to_xyz make_float3x3(make_float3(0.735275208950f, 0.068609409034f, 0.146571278572f), make_float3(0.286694079638f, 0.842979073524f, -0.129673242569f), make_float3(-0.079680845141f, -0.347343206406, 1.516081929207f))
#define matrix_sonysgamut3 make_float3x3(make_float3(0.599083900452f, 0.248925492167f, 0.102446496487f), make_float3(0.215075820684f, 0.885068416595f, -0.100144319236f), make_float3(-0.032065849751f, -0.027658388019, 1.148782014847f))
#define matrix_egamut_to_xyz make_float3x3(make_float3(0.705396831036f, 0.164041340351f, 0.081017754972f), make_float3(0.280130714178f, 0.820206701756f, -0.100337378681f), make_float3(-0.103781513870f, -0.072907261550, 1.265746593475f))
#define matrix_davinciwg_to_xyz make_float3x3(make_float3(0.700622320175f, 0.148774802685f, 0.101058728993f), make_float3(0.274118483067f, 0.873631775379f, -0.147750422359f), make_float3(-0.098962903023f, -0.137895315886, 1.325916051865f))
#define matrix_blackmagicwg_to_xyz make_float3x3(make_float3(0.606538414955f, 0.220412746072f, 0.123504832387f), make_float3(0.267992943525f, 0.832748472691f, -0.100741356611f), make_float3(-0.029442556202f, -0.086612440646, 1.205112814903f))

// "Truelight LMS" or "Truelight RGB" colorspace, described in "Chromaticity coordinates for graphic arts based on CIE 2006 LMS with even spacing of Munsell colours" by Richard Kirk
// https://doi.org/10.2352/issn.2169-2629.2019.27.38
#define matrix_xyz_to_truelightlms make_float3x3(make_float3(0.257085f, 0.859943f, -0.031061f), make_float3(-0.394427, 1.175800f, 0.106423f), make_float3(0.064856f, -0.07625f, 0.559067f))


// Whitepoint scaling factors for Truelight LMS
// eg: (1, 1, 1) in RGB (D65 whitepoint) -> XYZ -> TLMS /= catd65 *= catd55 -> XYZ -> Yxy == D65 white
#define catd50 make_float3(1.08221f, 0.883260f, 0.447579f)
#define catd55 make_float3(1.07730f, 0.896467f, 0.500927f)
#define catd60 make_float3(1.07344f, 0.907523f, 0.549381f)
#define catd65 make_float3(1.07046f, 0.916817f, 0.594251f)
#define catd75 make_float3(1.06600f, 0.931715f, 0.670839f)
#define catd93 make_float3(1.06098f, 0.950462f, 0.776150f)








/* ##########################################################################
    Functions
    ---------------------------------
*/


// Helper functions to perform math operations on a float3 vector
__DEVICE__ float3 sqrtf3(float3 a) { 
  return make_float3(_sqrtf(a.x), _sqrtf(a.y), _sqrtf(a.z));
}
__DEVICE__ float3 clamp_min_f3(float3 a, float b) {
  // For each component of float3 a, return max of component and float b
  return make_float3(_fmaxf(a.x, b), _fmaxf(a.y, b), _fmaxf(a.z, b));
}
__DEVICE__ float3 clamp_max_f3(float3 a, float b) { 
  // For each component of float3 a, return min of component and float b
  return make_float3(_fminf(a.x, b), _fminf(a.y, b), _fminf(a.z, b));
}
__DEVICE__ float3 clamp_f3(float3 a, float mn, float mx) { 
  // Clamp each component of float3 a to be between float mn and float mx
  return make_float3(
    _fmaxf(_fminf(a.x, mx), mn),
    _fmaxf(_fminf(a.y, mx), mn),
    _fmaxf(_fminf(a.z, mx), mn));
}
__DEVICE__ float _sign(float x) {
  // Return the sign of float x
  if (x > 0.0f) return 1.0f; 
  if (x < 0.0f) return -1.0f; 
  return 0.0f; 
}
__DEVICE__ float3 powf3(float3 a, float b) { 
  // Raise each component of float3 a to power b
  return make_float3(_powf(a.x, b), _powf(a.y, b), _powf(a.z, b));
}
__DEVICE__ float3 spowf3(float3 a, float b) {
  // Compute "safe" power of float3 a, reflected over the origin
  return make_float3(
    _sign(a.x)*_powf(_fabs(a.x), b), 
    _sign(a.y)*_powf(_fabs(a.y), b), 
    _sign(a.z)*_powf(_fabs(a.z), b));
}

// __DEVICE__ float __mix(float a float b float f) {
    // Linear interpolation between a and b by factor f. Extrapolates.
// }

// Helper function to create a float3x3
__DEVICE__ float3x3 make_float3x3(float3 a, float3 b, float3 c) {
  float3x3 d;
  d.x = a, d.y = b, d.z = c;
  return d;
}


// Multiply float3 vector a and 3x3 matrix m
__DEVICE__ float3 mult_f3_f33(float3 a, float3x3 m) {
  return make_float3(
    m.x.x * a.x + m.x.y * a.y + m.x.z * a.z,
    m.y.x * a.x + m.y.y * a.y + m.y.z * a.z,
    m.z.x * a.x + m.z.y * a.y + m.z.z * a.z);
}


// Calculate inverse of 3x3 matrix: https://stackoverflow.com/questions/983999/simple-3x3-matrix-inverse-code-c
__DEVICE__ float3x3 inv_f33(float3x3 m) {
  float d = m.x.x * (m.y.y * m.z.z - m.z.y * m.y.z) -
            m.x.y * (m.y.x * m.z.z - m.y.z * m.z.x) +
            m.x.z * (m.y.x * m.z.y - m.y.y * m.z.x);
  float id = 1.0f / d;
  float3x3 c = identity_mtx;
  c.x.x = id * (m.y.y * m.z.z - m.z.y * m.y.z);
  c.x.y = id * (m.x.z * m.z.y - m.x.y * m.z.z);
  c.x.z = id * (m.x.y * m.y.z - m.x.z * m.y.y);
  c.y.x = id * (m.y.z * m.z.x - m.y.x * m.z.z);
  c.y.y = id * (m.x.x * m.z.z - m.x.z * m.z.x);
  c.y.z = id * (m.y.x * m.x.z - m.x.x * m.y.z);
  c.z.x = id * (m.y.x * m.z.y - m.z.x * m.y.y);
  c.z.y = id * (m.z.x * m.x.y - m.x.x * m.z.y);
  c.z.z = id * (m.x.x * m.y.y - m.y.x * m.x.y);
  return c;
}






/* ##########################################################################
    Transfer Functions
    ---------------------------------
*/



__DEVICE__ float3 lin2log(float3 rgb, int tf) {
  if (tf == 0) return rgb;
  else if (tf == 1) { // ACEScct
    rgb.x = rgb.x > 0.0078125f ? (_log2f(rgb.x) + 9.72f) / 17.52f : 10.5402377416545f * rgb.x + 0.0729055341958355f;
    rgb.y = rgb.y > 0.0078125f ? (_log2f(rgb.y) + 9.72f) / 17.52f : 10.5402377416545f * rgb.y + 0.0729055341958355f;
    rgb.z = rgb.z > 0.0078125f ? (_log2f(rgb.z) + 9.72f) / 17.52f : 10.5402377416545f * rgb.z + 0.0729055341958355f;
  } else if (tf == 2) { // Arri V3 LogC EI 800
    rgb.x = rgb.x > 0.010591f ? 0.24719f * _log10f(5.555556f * rgb.x + 0.052272f) + 0.385537f : 5.367655f * rgb.x + 0.092809f;
    rgb.y = rgb.y > 0.010591f ? 0.24719f * _log10f(5.555556f * rgb.y + 0.052272f) + 0.385537f : 5.367655f * rgb.y + 0.092809f;
    rgb.z = rgb.z > 0.010591f ? 0.24719f * _log10f(5.555556f * rgb.z + 0.052272f) + 0.385537f : 5.367655f * rgb.z + 0.092809f;
  } else if (tf == 3) { // Red Log3G10
    rgb.x = rgb.x > -0.01f ? 0.224282f * _log10f(((rgb.x + 0.01f) * 155.975327f) + 1.0f) : (rgb.x + 0.01f) * 15.1927f;
    rgb.y = rgb.y > -0.01f ? 0.224282f * _log10f(((rgb.y + 0.01f) * 155.975327f) + 1.0f) : (rgb.y + 0.01f) * 15.1927f;
    rgb.z = rgb.z > -0.01f ? 0.224282f * _log10f(((rgb.z + 0.01f) * 155.975327f) + 1.0f) : (rgb.z + 0.01f) * 15.1927f;
  } else if (tf == 4) { // Sony SLog3
    rgb.x = rgb.x >= 0.01125f ? (420.0f + _log10f((rgb.x + 0.01f) / (0.18f + 0.01f)) * 261.5f) / 1023.0f : (rgb.x * (171.2102946929f - 95.0f) / 0.01125000f + 95.0f) / 1023.0f;
    rgb.y = rgb.y >= 0.01125f ? (420.0f + _log10f((rgb.y + 0.01f) / (0.18f + 0.01f)) * 261.5f) / 1023.0f : (rgb.y * (171.2102946929f - 95.0f) / 0.01125000f + 95.0f) / 1023.0f;
    rgb.z = rgb.z >= 0.01125f ? (420.0f + _log10f((rgb.z + 0.01f) / (0.18f + 0.01f)) * 261.5f) / 1023.0f : (rgb.z * (171.2102946929f - 95.0f) / 0.01125000f + 95.0f) / 1023.0f;
  } else if (tf == 5) { // Filmlight T-Log
    rgb.x = rgb.x < 0.0f ? 16.18437649f * rgb.x + 0.075f : _logf(rgb.x + 0.00570482f) * 0.09232903f + 0.55201266f;
    rgb.y = rgb.y < 0.0f ? 16.18437649f * rgb.y + 0.075f : _logf(rgb.y + 0.00570482f) * 0.09232903f + 0.55201266f;
    rgb.z = rgb.z < 0.0f ? 16.18437649f * rgb.z + 0.075f : _logf(rgb.z + 0.00570482f) * 0.09232903f + 0.55201266f;
  } else if (tf == 6) { // DaVinci Intermediate
    rgb.x = rgb.x <= 0.00262409f ? rgb.x * 10.44426855f : (_log2f(rgb.x + 0.0075f) + 7.0f) * 0.07329248f;
    rgb.y = rgb.y <= 0.00262409f ? rgb.y * 10.44426855f : (_log2f(rgb.y + 0.0075f) + 7.0f) * 0.07329248f;
    rgb.z = rgb.z <= 0.00262409f ? rgb.z * 10.44426855f : (_log2f(rgb.z + 0.0075f) + 7.0f) * 0.07329248f;
  } else if (tf == 7) { // Blackmagic Film Gen5
    rgb.x = rgb.x < 0.005f ? rgb.x * 8.283605932402494f : 0.08692876065491224f * _log2f(rgb.x + 0.005494072432257808f) + 0.5300133392291939f;
    rgb.y = rgb.y < 0.005f ? rgb.y * 8.283605932402494f : 0.08692876065491224f * _log2f(rgb.y + 0.005494072432257808f) + 0.5300133392291939f;
    rgb.z = rgb.z < 0.005f ? rgb.z * 8.283605932402494f : 0.08692876065491224f * _log2f(rgb.z + 0.005494072432257808f) + 0.5300133392291939f;
  }
  return rgb;
}

__DEVICE__ float3 log2lin(float3 rgb, int tf) {
  if (tf == 0) return rgb;
  else if (tf == 1) { // ACEScct
    rgb.x = rgb.x > 0.155251141552511f ? _powf(2.0f, rgb.x * 17.52f - 9.72f) : (rgb.x - 0.0729055341958355f) / 10.5402377416545f;
    rgb.y = rgb.y > 0.155251141552511f ? _powf(2.0f, rgb.y * 17.52f - 9.72f) : (rgb.y - 0.0729055341958355f) / 10.5402377416545f;
    rgb.z = rgb.z > 0.155251141552511f ? _powf(2.0f, rgb.z * 17.52f - 9.72f) : (rgb.z - 0.0729055341958355f) / 10.5402377416545f;
  } else if (tf == 2) { // Arri V3 LogC EI 800
    rgb.x = rgb.x > 0.149658f ? (_powf(10.0f, (rgb.x - 0.385537f) / 0.24719f) - 0.052272f) / 5.555556f : (rgb.x - 0.092809f) / 5.367655f;
    rgb.y = rgb.y > 0.149658f ? (_powf(10.0f, (rgb.y - 0.385537f) / 0.24719f) - 0.052272f) / 5.555556f : (rgb.y - 0.092809f) / 5.367655f;
    rgb.z = rgb.z > 0.149658f ? (_powf(10.0f, (rgb.z - 0.385537f) / 0.24719f) - 0.052272f) / 5.555556f : (rgb.z - 0.092809f) / 5.367655f;
  } else if (tf == 3) { // Red Log3G10
    rgb.x = rgb.x > 0.0f ? (_powf(10.0f, rgb.x / 0.224282f) - 1.0f) / 155.975327f - 0.01f : (rgb.x / 15.1927f) - 0.01f;
    rgb.y = rgb.y > 0.0f ? (_powf(10.0f, rgb.y / 0.224282f) - 1.0f) / 155.975327f - 0.01f : (rgb.y / 15.1927f) - 0.01f;
    rgb.z = rgb.z > 0.0f ? (_powf(10.0f, rgb.z / 0.224282f) - 1.0f) / 155.975327f - 0.01f : (rgb.z / 15.1927f) - 0.01f;
  } else if (tf == 4) { // Sony SLog3
    rgb.x = rgb.x >= 171.2102946929f / 1023.0f ? _powf(10.0f, ((rgb.x * 1023.0f - 420.0f) / 261.5f)) * (0.18f + 0.01f) - 0.01f : (rgb.x * 1023.0f - 95.0f) * 0.01125000f / (171.2102946929f - 95.0f);
    rgb.y = rgb.y >= 171.2102946929f / 1023.0f ? _powf(10.0f, ((rgb.y * 1023.0f - 420.0f) / 261.5f)) * (0.18f + 0.01f) - 0.01f : (rgb.y * 1023.0f - 95.0f) * 0.01125000f / (171.2102946929f - 95.0f);
    rgb.z = rgb.z >= 171.2102946929f / 1023.0f ? _powf(10.0f, ((rgb.z * 1023.0f - 420.0f) / 261.5f)) * (0.18f + 0.01f) - 0.01f : (rgb.z * 1023.0f - 95.0f) * 0.01125000f / (171.2102946929f - 95.0f);
  } else if (tf == 5) { // Filmlight T-Log
    rgb.x = rgb.x < 0.075f ? (rgb.x - 0.075f) / 16.18437649f : _expf((rgb.x - 0.55201266f) / 0.09232903f) - 0.00570482f;
    rgb.y = rgb.y < 0.075f ? (rgb.y - 0.075f) / 16.18437649f : _expf((rgb.y - 0.55201266f) / 0.09232903f) - 0.00570482f;
    rgb.z = rgb.z < 0.075f ? (rgb.z - 0.075f) / 16.18437649f : _expf((rgb.z - 0.55201266f) / 0.09232903f) - 0.00570482f;
  } else if (tf == 6) { // DaVinci Intermediate
    rgb.x = rgb.x <= 0.02740668f ? rgb.x / 10.44426855f : _powf(2.0f, (rgb.x / 0.07329248f) - 7.0f) - 0.0075f;
    rgb.y = rgb.y <= 0.02740668f ? rgb.y / 10.44426855f : _powf(2.0f, (rgb.y / 0.07329248f) - 7.0f) - 0.0075f;
    rgb.z = rgb.z <= 0.02740668f ? rgb.z / 10.44426855f : _powf(2.0f, (rgb.z / 0.07329248f) - 7.0f) - 0.0075f;
  } else if (tf == 7) { // Blackmagic Film Gen5
    rgb.x = rgb.x < 0.13388378f ? (rgb.x - 0.09246575342465753f) / 8.283605932402494f : _expf((rgb.x - 0.5300133392291939f) / 0.08692876065491224f) - 0.005494072432257808f;
    rgb.y = rgb.y < 0.13388378f ? (rgb.y - 0.09246575342465753f) / 8.283605932402494f : _expf((rgb.y - 0.5300133392291939f) / 0.08692876065491224f) - 0.005494072432257808f;
    rgb.z = rgb.z < 0.13388378f ? (rgb.z - 0.09246575342465753f) / 8.283605932402494f : _expf((rgb.z - 0.5300133392291939f) / 0.08692876065491224f) - 0.005494072432257808f;
  }
  return rgb;
}


__DEVICE__ float3 eotf_hlg(float3 rgb, int inverse) {
  // Aply the HLG Forward or Inverse EOTF. Implements the full ambient surround illumination model
  // ITU-R Rec BT.2100-2 https://www.itu.int/rec/R-REC-BT.2100
  // ITU-R Rep BT.2390-8: https://www.itu.int/pub/R-REP-BT.2390
  // Perceptual Quantiser (PQ) to Hybrid Log-Gamma (HLG) Transcoding: https://www.bbc.co.uk/rd/sites/50335ff370b5c262af000004/assets/592eea8006d63e5e5200f90d/BBC_HDRTV_PQ_HLG_Transcode_v2.pdf

  const float HLG_Lw = 1000.0f;
//   const float HLG_Lb = 0.0f;
  const float HLG_Ls = 5.0f;
  const float h_a = 0.17883277f;
  const float h_b = 1.0f - 4.0f * 0.17883277f;
  const float h_c = 0.5f - h_a * _logf(4.0f * h_a);
  const float h_g = 1.2f * _powf(1.111f, _log2f(HLG_Lw / 1000.0f)) * _powf(0.98f, _log2f(_fmaxf(1e-6f, HLG_Ls) / 5.0f));
  if (inverse == 1) {
    float Yd = 0.2627f * rgb.x + 0.6780f * rgb.y + 0.0593f * rgb.z;
    // HLG Inverse OOTF
    rgb = rgb * _powf(Yd, (1.0f - h_g) / h_g);
    // HLG OETF
    rgb.x = rgb.x <= 1.0f / 12.0f ? _sqrtf(3.0f * rgb.x) : h_a * _logf(12.0f * rgb.x - h_b) + h_c;
    rgb.y = rgb.y <= 1.0f / 12.0f ? _sqrtf(3.0f * rgb.y) : h_a * _logf(12.0f * rgb.y - h_b) + h_c;
    rgb.z = rgb.z <= 1.0f / 12.0f ? _sqrtf(3.0f * rgb.z) : h_a * _logf(12.0f * rgb.z - h_b) + h_c;
  } else {
    // HLG Inverse OETF
    rgb.x = rgb.x <= 0.5f ? rgb.x * rgb.x / 3.0f : (_expf((rgb.x - h_c) / h_a) + h_b) / 12.0f;
    rgb.y = rgb.y <= 0.5f ? rgb.y * rgb.y / 3.0f : (_expf((rgb.y - h_c) / h_a) + h_b) / 12.0f;
    rgb.z = rgb.z <= 0.5f ? rgb.z * rgb.z / 3.0f : (_expf((rgb.z - h_c) / h_a) + h_b) / 12.0f;
    // HLG OOTF
    float Ys = 0.2627f * rgb.x + 0.6780f * rgb.y + 0.0593f * rgb.z;
    rgb = rgb * _powf(Ys, h_g - 1.0f);
  }
  return rgb;
}


__DEVICE__ float3 eotf_pq(float3 rgb, int inverse, int jz) {
  // Apply the ST-2084 PQ Forward or Inverse EOTF
  // Normalized such that input display linear light code value 1.0 equals 10,000 nits
  // ITU-R Rec BT.2100-2 https://www.itu.int/rec/R-REC-BT.2100
  // ITU-R Rep BT.2390-9 https://www.itu.int/pub/R-REP-BT.2390
  
  
  
  float Lp = 1.0f; // We normalize for hdr peak display luminance elsewhere.
  const float m1 = 2610.0f / 16384.0f;
  float m2 = 2523.0f / 32.0f;
  
  // Custom values for JzAzBz colorspace
  if (jz == 1) {
    m2 *= 1.7f;
    Lp = 10000.0f;
  }

  const float c1 = 107.0f / 128.0f;
  const float c2 = 2413.0f / 128.0f;
  const float c3 = 2392.0f / 128.0f;
  
  if (inverse == 1) {
    rgb /= Lp;
    rgb = powf3(rgb, m1);
    rgb = powf3((c1 + c2 * rgb) / (1.0f + c3 * rgb), m2);
    return rgb;
  } else {
    rgb = powf3(rgb, 1.0f / m2);
    rgb = powf3((rgb - c1) / (c2 - c3 * rgb), 1.0f / m1) * Lp;
    return rgb;
  }
}


/* ########################################################################## 
    Color Models
    ---------------------------------
*/



/*
  ICtCp perceptual colorspace
  -----------------------------------
  ITU-R Rec BT.2100-2: https://www.itu.int/rec/R-REC-BT.2100
  ITU-R Rep BT.2390-9: https://www.itu.int/pub/R-REP-BT.2390
*/
#define matrix_ictcp_rec2020_to_lms make_float3x3(make_float3(1688.0f, 2146.0f, 262.0f) / 4096.0f, make_float3(683.0f, 2951.0f, 462.0f) / 4096.0f, make_float3(99.0f, 309.0f, 3688.0f) / 4096.0f)
#define matrix_ictcp_lms_to_ictcp make_float3x3(make_float3(0.5f, 0.5f, 0.0f), make_float3(6610.0f, -13613.0f, 7003.0f) / 4096.0f, make_float3(17933.0f, -17390.0f, -543.0f) / 4096.0f)

__DEVICE__ float3 xyz_to_ictcp(float3 xyz, float Lw, int cyl) {
  // Convert from XYZ to ICtCp colorspace, with optional cylindrical output conversion
  xyz = mult_f3_f33(xyz, inv_f33(matrix_rec2020_to_xyz));
  xyz = mult_f3_f33(xyz, matrix_ictcp_rec2020_to_lms);
  xyz = eotf_pq(xyz / Lw, 1, 0);
  xyz = mult_f3_f33(xyz, matrix_ictcp_lms_to_ictcp);
  if (cyl == 1) // Convert to cylindrical
    xyz = make_float3(xyz.x, _hypotf(xyz.y, xyz.z), _atan2f(xyz.z, xyz.y));
  return xyz;
}

__DEVICE__ float3 ictcp_to_xyz(float3 xyz, float Lw, int cyl) {
  // Convert from ICtCp colorspace to XYZ, with optional cylindrical input conversion
  if (cyl == 1) // Convert to cartesian
    xyz = make_float3(xyz.x, xyz.y * _cosf(xyz.z), xyz.y * _sinf(xyz.z));
  xyz = mult_f3_f33(xyz, inv_f33(matrix_ictcp_lms_to_ictcp));
  xyz = eotf_pq(xyz, 0, 0) * Lw;
  xyz = mult_f3_f33(xyz, inv_f33(matrix_ictcp_rec2020_to_lms));
  xyz = mult_f3_f33(xyz, matrix_rec2020_to_xyz);
  return xyz;
}

/*
  JzAzBz perceptual colorspace
  ----------------------------------
  Safdar, M., Cui, G., Kim, Y. J., & Luo, M. R. (2017).
      Perceptually uniform color space for image signals including high dynamic
      range and wide gamut. Optics Express, 25(13), 15131.
      doi:10.1364/OE.25.015131
  https://www.osapublishing.org/oe/fulltext.cfm?uri=oe-25-13-15131&id=368272
  https://observablehq.com/@jrus/jzazbz
*/
# define matrix_jzazbz_xyz_to_lms make_float3x3(make_float3(0.41479f, 0.579999f, 0.014648f), make_float3(-0.20151f, 1.12065f, 0.0531008f), make_float3(-0.0166008f, 0.2648f, 0.66848f))
# define matrix_jzazbz_lms_p_to_izazbz make_float3x3(make_float3(0.5f, 0.5f, 0.0f), make_float3(3.524f, -4.06671f, 0.542708f), make_float3(0.199076f, 1.0968f, -1.29588f))

__DEVICE__ float3 jzazbz(float3 input, int inverse, int cyl) {
  // Convert input XYZ D65 aligned tristimulus values into JzAzBz perceptual colorspace, 
  // if cyl==1: output cylindrical JCh : J = luma, C = chroma, h = hue in radians
  const float b = 1.15f;
  const float g = 0.66f;
  const float d = -0.56f;
  const float d_0 = 1.6295499532821565e-11f;
  const float3x3 mtx_xyz_to_lms = matrix_jzazbz_xyz_to_lms;
  const float3x3 mtx_lmsp_to_izazbz = matrix_jzazbz_lms_p_to_izazbz;
  
  if (inverse == 0) {

    float3 xyz = input;
    xyz = make_float3(
      b * xyz.x - (b - 1.0f) * xyz.z,
      g * xyz.y - (g-1.0f) * xyz.x,
      xyz.z);
    float3 lms = mult_f3_f33(xyz, matrix_jzazbz_xyz_to_lms);
    lms = eotf_pq(lms, 1, 1);
    lms = mult_f3_f33(lms, matrix_jzazbz_lms_p_to_izazbz);
    lms.x = lms.x * (1.0f + d) / (1.0f + d * lms.x) - d_0;
    // Convert to cylindrical
    if (cyl == 1) 
      lms = make_float3(lms.x, _hypotf(lms.y, lms.z), _atan2f(lms.z, lms.y));

    return lms;

  } else {
    const float3x3 mtx_izazbz_to_lmsp = inv_f33(mtx_lmsp_to_izazbz);
    const float3x3 mtx_lms_to_xyz = inv_f33(mtx_xyz_to_lms);

    float3 lms = input;
    if (cyl == 1) // Convert to cartesian
      lms = make_float3(lms.x, lms.y * _cosf(lms.z), lms.y * _sinf(lms.z));
    lms.x = (lms.x + d_0) / (1.0f + d - d * (lms.x + d_0));
    lms = mult_f3_f33(lms, mtx_izazbz_to_lmsp);
    lms = eotf_pq(lms, 0, 1);
    lms = mult_f3_f33(lms, mtx_lms_to_xyz);
    lms.x = (lms.x + (b-1.0f) * lms.z) / b;
    lms.y = (lms.y + (g - 1.0f) * ((lms.x + (b - 1.0f) * lms.z) / b)) / g;

    return lms;
  }
}





/* ########################################################################## 
    Utility Functions 
    --------------------
*/

__DEVICE__ float compress_parabolic(float x, float t0, float x0, float y0) {
  /* Parabolic Compression Function
      Threshold
        Only values above threshold point (t0, t0) will be compressed.
      Intersection constraint
        The coordinate (x0, y0) specifies the compression function intersection
        constraint. The input x value x0 is compressed to the output y value y0.
      https://www.desmos.com/calculator/khowxlu6xh
  */
  const float s = (y0 - t0)/_sqrtf(x0 - y0);
  const float ox = t0 - s * s / 4.0f;
  const float oy = t0 - s * sqrt(s * s / 4.0f);

  return (x < t0 ? x : s * _sqrtf(x - ox) + oy);
}

__DEVICE__ float3 gamut_compress_rgb(float3 xyz, float th, float ds, int av) {
  // Chromaticity-linear gamut compression, given threshold th and distance ds.
  // if av==1, average of rgb will be used as achromatic axis instead of max of rgb
  
  float3 rgb = mult_f3_f33(xyz, inv_f33(matrix_rec2020_to_xyz));

  float mx = _fmaxf(rgb.x, _fmaxf(rgb.y, rgb.z));
  float mn = _fminf(rgb.x, _fminf(rgb.y, rgb.z));
  float ch = mx == 0.0f ? 0.0f : (mx - mn) / mx; // classic chroma
  float ch_c = compress_parabolic(ch, th, ds, 1.0f);
  float f = ch == 0.0f ? 0.0f : ch_c / ch;

  // Gamut compress
  if (av == 0) {
    rgb = mx * (1.0f - f) + rgb * f;
  } else {
    float mean = (rgb.x + rgb.y + rgb.z) / 3.0f;
    rgb = mean * (1.0f - f) + rgb * f;
  }

  rgb = mult_f3_f33(rgb, matrix_rec2020_to_xyz);

  return rgb;
}