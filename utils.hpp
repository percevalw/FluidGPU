#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdlib>
#include <cstdint>

/*
BMI2(Bit Manipulation Instruction Set 2) is a special set of instructions available for intel core i5, i7(since Haswell architecture) and Xeon E3.
Some instructions are not available for Microsoft Visual Studio older than 2013.
*/
#if _MSC_VER
#define USE_BMI2
#endif

#ifndef USE_BMI2
//mortonkey(x+1) = (mortonkey(x) - MAXMORTONKEY) & MAXMORTONKEY
static const uint32_t morton2dLUT[256] =
{ 0x0000, 0x0001, 0x0004, 0x0005, 0x0010, 0x0011, 0x0014, 0x0015,
  0x0040, 0x0041, 0x0044, 0x0045, 0x0050, 0x0051, 0x0054, 0x0055,
  0x0100, 0x0101, 0x0104, 0x0105, 0x0110, 0x0111, 0x0114, 0x0115,
  0x0140, 0x0141, 0x0144, 0x0145, 0x0150, 0x0151, 0x0154, 0x0155,
  0x0400, 0x0401, 0x0404, 0x0405, 0x0410, 0x0411, 0x0414, 0x0415,
  0x0440, 0x0441, 0x0444, 0x0445, 0x0450, 0x0451, 0x0454, 0x0455,
  0x0500, 0x0501, 0x0504, 0x0505, 0x0510, 0x0511, 0x0514, 0x0515,
  0x0540, 0x0541, 0x0544, 0x0545, 0x0550, 0x0551, 0x0554, 0x0555,
  0x1000, 0x1001, 0x1004, 0x1005, 0x1010, 0x1011, 0x1014, 0x1015,
  0x1040, 0x1041, 0x1044, 0x1045, 0x1050, 0x1051, 0x1054, 0x1055,
  0x1100, 0x1101, 0x1104, 0x1105, 0x1110, 0x1111, 0x1114, 0x1115,
  0x1140, 0x1141, 0x1144, 0x1145, 0x1150, 0x1151, 0x1154, 0x1155,
  0x1400, 0x1401, 0x1404, 0x1405, 0x1410, 0x1411, 0x1414, 0x1415,
  0x1440, 0x1441, 0x1444, 0x1445, 0x1450, 0x1451, 0x1454, 0x1455,
  0x1500, 0x1501, 0x1504, 0x1505, 0x1510, 0x1511, 0x1514, 0x1515,
  0x1540, 0x1541, 0x1544, 0x1545, 0x1550, 0x1551, 0x1554, 0x1555,
  0x4000, 0x4001, 0x4004, 0x4005, 0x4010, 0x4011, 0x4014, 0x4015,
  0x4040, 0x4041, 0x4044, 0x4045, 0x4050, 0x4051, 0x4054, 0x4055,
  0x4100, 0x4101, 0x4104, 0x4105, 0x4110, 0x4111, 0x4114, 0x4115,
  0x4140, 0x4141, 0x4144, 0x4145, 0x4150, 0x4151, 0x4154, 0x4155,
  0x4400, 0x4401, 0x4404, 0x4405, 0x4410, 0x4411, 0x4414, 0x4415,
  0x4440, 0x4441, 0x4444, 0x4445, 0x4450, 0x4451, 0x4454, 0x4455,
  0x4500, 0x4501, 0x4504, 0x4505, 0x4510, 0x4511, 0x4514, 0x4515,
  0x4540, 0x4541, 0x4544, 0x4545, 0x4550, 0x4551, 0x4554, 0x4555,
  0x5000, 0x5001, 0x5004, 0x5005, 0x5010, 0x5011, 0x5014, 0x5015,
  0x5040, 0x5041, 0x5044, 0x5045, 0x5050, 0x5051, 0x5054, 0x5055,
  0x5100, 0x5101, 0x5104, 0x5105, 0x5110, 0x5111, 0x5114, 0x5115,
  0x5140, 0x5141, 0x5144, 0x5145, 0x5150, 0x5151, 0x5154, 0x5155,
  0x5400, 0x5401, 0x5404, 0x5405, 0x5410, 0x5411, 0x5414, 0x5415,
  0x5440, 0x5441, 0x5444, 0x5445, 0x5450, 0x5451, 0x5454, 0x5455,
  0x5500, 0x5501, 0x5504, 0x5505, 0x5510, 0x5511, 0x5514, 0x5515,
  0x5540, 0x5541, 0x5544, 0x5545, 0x5550, 0x5551, 0x5554, 0x5555
};
#endif

const uint64_t x2_mask = 0xAAAAAAAAAAAAAAAA; //0b...10101010
const uint64_t y2_mask = 0x5555555555555555; //0b...01010101

class Utils {
    // Methods to return a random value between ranges
    // Yes, it probably would make more sense to templatise it, but the integer version
    // works slightly differenly. Maybe if that was placed first and THEN the templatised
    // version it would use the specific version for ints but the generic version for all
    // other data types - feel free to experiment and let me know how it works out ;-).

    public:
        static double randRange(double min, double max) {
            return min + (((double) rand() / (double) RAND_MAX) * (max - min));
        }

        static float randRange(float min, float max) {
            return min + (((float) rand() / (float) RAND_MAX) * (max - min));
        }

        static int randRange(int min, int max) {
            return ((int) rand() % (max - min + 1)) + min;
        }

        template <typename T_in=uint32_t, typename T_out=uint64_t>
        static T_out morton2d(T_in x, T_in y) {
#ifdef USE_BMI2
		T_out key = static_cast<T>(_pdep_u64(y, y2_mask) | _pdep_u64(x, x2_mask));
#else
		T_out key = morton2dLUT[(x >> 24) & 0xFF] << 1 |
			morton2dLUT[(y >> 24) & 0xFF];
		key = key << 16 |
			morton2dLUT[(x >> 16) & 0xFF] << 1 |
			morton2dLUT[(y >> 16) & 0xFF];
		key = key << 16 |
			morton2dLUT[(x >> 8) & 0xFF] << 1 |
			morton2dLUT[(y >> 8) & 0xFF];
		key = key << 16 |
			morton2dLUT[x & 0xFF] << 1 |
			morton2dLUT[y & 0xFF];
        return key;
#endif
	    }

        template <typename T>
        inline static T morton_inc_y(T key) {
            const T x_sum = static_cast<T>((key | y2_mask) + 2);
            return ((x_sum & x2_mask) | (key & y2_mask));
        }

        template <typename T>
        inline static T morton_inc_x(T key) {
            const T y_sum = static_cast<T>((key | x2_mask) + 1);
            return ((y_sum & y2_mask) | (key & x2_mask));
        }

        template <typename T>
        inline static T morton_dec_y(T key) {
            const T x_diff = static_cast<T>((key & x2_mask) - 2);
            return ((x_diff & x2_mask) | (key & y2_mask));
        }

        template <typename T>
        inline static T morton_dec_x    (T key) {
            const T y_diff = static_cast<T>((key & y2_mask) - 1);
            return ((y_diff & y2_mask) | (key & x2_mask));
        }

        static uint32_t upper_power_of_two(uint32_t v) {
            v--;
            v |= v >> 1;
            v |= v >> 2;
            v |= v >> 4;
            v |= v >> 8;
            v |= v >> 16;
            v++;
            return v;
        }

        static void radix_sort(uint32_t * a, uint32_t *sorted_index, size_t count) {
            size_t mIndex[4][256] = {0};            // count / index matrix
            size_t i,j,m,n,p;
            uint32_t u;
            uint32_t *tmp = new uint32_t[count];
            uint32_t *tmp_b = new uint32_t[count];
            uint32_t *index_b = new uint32_t[count];
            for(i = 0; i < count; i++){         // generate histograms
                sorted_index[i] = i;
                u = a[i];
                tmp[i] = u;
                for(j = 0; j < 4; j++){
                    mIndex[j][(size_t)(u & 0xff)]++;
                    u >>= 8;
                }
            }
            for(j = 0; j < 4; j++){             // convert to indices
                m = 0;
                for(i = 0; i < 256; i++){
                    n = mIndex[j][i];
                    mIndex[j][i] = m;
                    m += n;
                }
            }
            for(j = 0; j < 4; j++){             // radix sort
                for(i = 0; i < count; i++){     //  sort by current lsb
                    u = tmp[i];
                    m = (size_t)(u>>(j<<3))&0xff;
                    p = mIndex[j][m]++;
                    tmp_b[p] = u;

                    index_b[p] = sorted_index[i];
                }

                std::swap(tmp, tmp_b);                //  swap ptrs
                std::swap(sorted_index, index_b);                //  swap ptrs
            }
            delete[] tmp;
            delete[] tmp_b;
            delete[] index_b;
        }

};

#endif