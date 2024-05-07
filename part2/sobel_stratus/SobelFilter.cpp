#include <cmath>
#ifndef NATIVE_SYSTEMC
#include "stratus_hls.h"
#endif


/*  can't work
/// for length & width
#include "Testbench.h"
extern unsigned int width;
extern unsigned int height;
*/
#include "SobelFilter.h"

/// for buffer
#include <iostream>

const int SIZE = 25;
sc_fixed<14,10> buffer[SIZE];

SobelFilter::SobelFilter( sc_module_name n ): sc_module( n )
{
#ifndef NATIVE_SYSTEMC
	HLS_FLATTEN_ARRAY(val);
#endif
	SC_THREAD( do_filter );
	sensitive << i_clk.pos();
	dont_initialize();
	reset_signal_is(i_rst, false);
        
#ifndef NATIVE_SYSTEMC   // cynw_p2p 標準寫法，因為cynw_p2p library內要求要把clock & rst 接過去
	i_rgb.clk_rst(i_clk, i_rst);
  	o_result.clk_rst(i_clk, i_rst);
#endif
}

SobelFilter::~SobelFilter() {}
/*
// sobel mask
const int mask[MASK_N][MASK_X][MASK_Y] = {{{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}},

                                    {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}};
*/
// Gaussian Blur Filter
const sc_fixed_fast<14,10> mask[MASK_N][MASK_X][MASK_Y] = {{{1, 4, 7, 4, 1},
                                           	 				{4, 16, 26, 16, 4},
                                              				{7, 26, 41, 26, 7},
                                              				{4, 16, 26, 16, 4},
                                              				{1, 4, 7, 4, 1}}};

void SobelFilter::do_filter() {
	{
#ifndef NATIVE_SYSTEMC
		HLS_DEFINE_PROTOCOL("main_reset"); // ？ protocol：協定
		i_rgb.reset();
		o_result.reset();
#endif
		wait();
	}
	int x = 0, y = 0;
  	sc_fixed_fast<14,10> grey = 0;
	while (true) {
		for (unsigned int i = 0; i<MASK_N; ++i) {  /// initialization
			//HLS_CONSTRAIN_LATENCY(0, 1, "lat00");
			val[i] = 0;  
		}
		for (unsigned int v = 0; v<MASK_Y; ++v) {
			for (unsigned int u = 0; u<MASK_X; ++u) {
				sc_dt::sc_uint<24> rgb;
#ifndef NATIVE_SYSTEMC
				{
					if (x == 0 || u == MASK_X-1){ /// MASK_X-1 為最右邊的mask
						HLS_DEFINE_PROTOCOL("input");
						//std::cout << "before read sobel.cpp" << endl;
						//std::cout << "time = " << sc_time_stamp() <<endl;
						rgb = i_rgb.get();
						//std::cout << "after read sobel.cpp" << endl;
						//std::cout << "time = " << sc_time_stamp() <<endl;
						grey = (rgb.range(7,0) + rgb.range(15,8) + rgb.range(23, 16)) /3;
						wait();	
					}
				}
#else
				rgb = i_rgb.read();
#endif
				if (x != 0 && y != 0){   // 滿了
					//buffer[u+v*5]=buffer[u+v*5+1];	// (x,y)換後應該先重排
					buffer[u+(v<<2)+v]=buffer[u+(v<<2)+v+1];	// (x,y)換後應該先重排
				}
				/// 0~24  一開始全放
				//if (x == 0 && y == 0) buffer[u+5*v] = grey;  
				if (x == 0 && y == 0) buffer[u+(v<<2)+v] = grey;
				/// 從buffer給值  (非一開始，也非最右邊)
				//else if (u != MASK_X - 1 && x != 0) grey = buffer[u+5*v];
				else if (u != MASK_X - 1 && x != 0) grey = buffer[u+(v<<2)+v];
				// 將新值放入buffer
				//else if (u == MASK_X - 1) buffer[u+5*v] = grey;   
				else if (u == MASK_X - 1) buffer[u+(v<<2)+v] = grey; 
				for (unsigned int i = 0; i != MASK_N; ++i) {
					//HLS_CONSTRAIN_LATENCY(0, 1, "lat01");
					val[i] += grey * (mask[i][u][v]/273);
					//std::cout << "val[0] = " << val[0] << endl;
				}
			}
		}
		// counter for pixels 256 * 256
    	x++;    // 0~255 
    	if(x == 256) {  // if the pixels is 512 need to change to 512;
			y++;
			x = 0;
      	}
  		sc_fixed_fast<23,17> total = 0;
		for (unsigned int i = 0; i != MASK_N; ++i) {
			//HLS_CONSTRAIN_LATENCY(0, 1, "lat01");
			total += val[i] * val[i];
			//std::cout << "total = " << total << endl;
		}
#ifndef NATIVE_SYSTEMC
		{	
			//std::cout << "width = " << width << endl;
			//std::cout << "height = " << height << endl;
			HLS_DEFINE_PROTOCOL("output");
			o_result.put(total);
			//std::cout << "total = " << total << endl;
			wait();
		}
#else
		o_result.write(total);
#endif
	}
}
