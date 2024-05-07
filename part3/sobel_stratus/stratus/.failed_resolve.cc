/********************/
state0:;
/*HLS_SET_OUTPUT_OPTIONS(i_rgb_m_use_stall_reg_ip, 4ULL);*//* 52ULL */
/*HLS_SET_OUTPUT_OPTIONS(o_result_m_req_m_trig_req, 0ULL);*//* 74ULL */
/*HLS_SET_OUTPUT_OPTIONS(i_rgb_m_stalling, 11ULL);*//* 36ULL */
/*HLS_SET_OUTPUT_OPTIONS(i_rgb_m_busy_req_0, 0ULL);*//* 47ULL */
/*HLS_SET_INPUT_DELAY(i_rgb_data, -1.000000);*//* 60ULL */
/*HLS_SET_OUTPUT_OPTIONS(o_result_data, 2ULL);*//* 75ULL */
goto state1;
/********************/
state1:;
goto state2;
/********************/
state2:;
/*HLS_DEFINE_PROTOCOL("main_reset");*//* 33ULL */
i_rgb_m_busy_req_0 = 1ULL;
i_rgb_m_stalling = 0ULL;
o_result_m_req_m_trig_req = 0ULL;
goto state3;
/********************/
state3:;
/*HLS_DEFINE_PROTOCOL("main_reset");*//* 33ULL */
wait( 1LL ); // cycle_id 1
goto state4;
/********************/
state4:;
x = (sc_int<32> ) (0ULL);
y = (sc_int<32> ) (0ULL);
grey = 0.000000;
goto state5;
/********************/
state5:;
goto state6;
/********************/
state6:;
/*HLS_CONSTRAIN_LATENCY(0ULL, 1ULL, "lat00");*//* 43ULL */
val_0 = 0.000000;
goto state7;
/********************/
state7:;
v = 0ULL;
goto state8;
/********************/
state8:;
/*CYN_ITERATIONS(5ULL, "<generated>");*//* 267ULL */
u = 0ULL;
goto state9;
/********************/
state9:;
/*CYN_ITERATIONS(5ULL, "<generated>");*//* 266ULL */
logic_in_001 = ((sc_uint<32>)x).or_reduce();
condvar_001 = logic_in_001 & ((sc_uint<3> )u != 4ULL);
switch( (sc_uint<1>)(condvar_001) ) {
case 1ULL: 
  goto state15;
case 0ULL: 
  goto state10;
}
/********************/
state10:;
/*HLS_DEFINE_PROTOCOL("input");*//* 44ULL */
i_rgb_m_busy_req_0 = 0ULL;
goto state11;
/********************/
state11:;
/*HLS_DEFINE_STALL_LOOP(ALL,4096ULL, "get", (long long)0x0ULL);*//* 55ULL */
/*HLS_DEFINE_PROTOCOL("input");*//* 44ULL */
goto state12;
/********************/
state12:;
/*HLS_DEFINE_STALL_LOOP(ALL,4096ULL, "get", (long long)0x0ULL);*//* 55ULL */
/*HLS_DEFINE_PROTOCOL("input");*//* 44ULL */
wait( 1LL ); // cycle_id 2
stall0 = i_rgb_m_data_is_invalid;
goto state13;
/********************/
state13:;
/*HLS_DEFINE_PROTOCOL("input");*//* 44ULL */
/*HLS_SET_STALL_LOCAL(i_rgb_m_stalling, 1ULL, 0ULL, (long long)0x0ULL, 
(long long)0x0ULL);*//* 58ULL */
i_rgb_m_busy_req_0 = 1ULL;
u_g_n_675 = i_rgb_data;
grey = ( ((u_g_n_675.range(7,0) + u_g_n_675.range(15,8)) + u_g_n_675.range(23,16
       )) ) / 3ULL;
goto state14;
/********************/
state14:;
/*HLS_DEFINE_PROTOCOL("input");*//* 44ULL */
wait( 1LL ); // cycle_id 3
goto state15;
/********************/
state15:;
amtmp001 = ((sc_uint<32>)x).or_reduce() & ((sc_uint<32>)y).or_reduce();
if /*guard*/( amtmp001 ) /*Enable*/if (amtmp001) (buffer)[(sc_uint<5> )(( 
(/*cliff*/sc_uint<32>)((sc_uint<3> )u + (/*cliff*/sc_uint<32>)(sc_uint<3> )v * 
5ULL) ))] = /*Enable*/(amtmp001?(double )(buffer)[(sc_uint<5> )(( 
            (/*cliff*/sc_uint<32>)((/*cliff*/sc_uint<32>)((sc_uint<3> )u + 
            (/*cliff*/sc_uint<32>)(sc_uint<3> )v * 5ULL) + 1ULL) ))]:(double 
            )0ULL);
amtmp005 = ((sc_uint<64>)( (sc_uint<64> )(sc_bv<64>)((sc_bv<32>)(x), 
           (sc_bv<32>)(y)) )).or_reduce();
amtmp004 = ((sc_uint<3> )u != 4ULL) & ((sc_uint<32>)x).or_reduce();
guard_001 = ((sc_uint<3> )((sc_uint<3> )u) == 4ULL) & !amtmp004 & amtmp005;
guard_004 = ((sc_uint<3> )((sc_uint<3> )u) == 4ULL) & !amtmp004 & amtmp005;
if /*guard*/( guard_004 ) /*Enable*/if (guard_001) (buffer)[(sc_uint<5> )(( 
(/*cliff*/sc_uint<32>)((/*cliff*/sc_uint<32>)(sc_uint<3> )v * 5ULL + 4ULL) ))]
 = grey;
mux_opt0001 = grey;
guard_002 = amtmp004 & amtmp005;
dmux_ctrl_001 = amtmp005 & amtmp004;
grey = ( dmux_ctrl_001 ? (double )
       (/*Enable*/(guard_002?(double )(buffer)[(sc_uint<5> )(( 
       (/*cliff*/sc_uint<32>)((sc_uint<3> )u + (/*cliff*/sc_uint<32>)(
       sc_uint<3> )v * 5ULL) ))]:(double )0ULL)) : (double )
       (grey));
guard_003 = !amtmp005;
if /*guard*/( guard_003 ) /*Enable*/if (guard_003) (buffer)[(sc_uint<5> )(( 
(/*cliff*/sc_uint<32>)((sc_uint<3> )u + (/*cliff*/sc_uint<32>)(sc_uint<3> )v * 
5ULL) ))] = mux_opt0001;
goto state16;
/********************/
state16:;
/*HLS_CONSTRAIN_LATENCY(0ULL, 1ULL, "lat01");*//* 63ULL */
val_0 = (val_0 + grey * ( (273.000000 == 0 ? ((double ) -1) : (double ) ((mask)[
        ((/*imp*/sc_uint<5> )(((sc_uint<3> )((sc_uint<3> )u) * 5ULL + (
        sc_uint<3> )((sc_uint<3> )v))))] / 273.000000)) ));
goto state17;
/********************/
state17:;
u = (/*cliff*/sc_uint<32>)((sc_uint<3> )u + 1ULL);
condvar_002 = (/*imp*/sc_uint<1>)(u < ((/*imp*/sc_uint<3> )(5ULL)));
switch( (sc_uint<1>)(condvar_002) ) {
case 0ULL: 
  goto state18;
case 1ULL: 
  goto state9;
}
/********************/
state18:;
v = (/*cliff*/sc_uint<32>)((sc_uint<3> )v + 1ULL);
condvar_003 = (/*imp*/sc_uint<1>)(v < ((/*imp*/sc_uint<3> )(5ULL)));
switch( (sc_uint<1>)(condvar_003) ) {
case 0ULL: 
  goto state19;
case 1ULL: 
  goto state8;
}
/********************/
state19:;
x_u0 = (/*cliff*/sc_int<32>)(x + 1ULL);
y = (/*cliff*/sc_int<32>)(y + ( (x_u0 == 256ULL) ));
dmux_ctrl_002 = (x_u0 == 256ULL);
x = ( dmux_ctrl_002 ? (sc_int<32> )
    (0ULL) : (sc_int<32> )
    (x_u0));
goto state20;
/********************/
state20:;
/*HLS_CONSTRAIN_LATENCY(0ULL, 1ULL, "lat01");*//* 64ULL */
total = (0.000000 + val_0 * val_0);
goto state21;
/********************/
state21:;
/*HLS_DEFINE_PROTOCOL("output");*//* 65ULL */
o_result_data = (sc_uint<32> )total;
o_result_m_req_m_trig_req = o_result_m_req_m_next_trig_req;
goto state22;
/********************/
state22:;
/*HLS_DEFINE_STALL_LOOP(ALL,4096ULL, "put", (long long)0x0ULL);*//* 76ULL */
/*HLS_DEFINE_PROTOCOL("output");*//* 65ULL */
goto state23;
/********************/
state23:;
/*HLS_DEFINE_STALL_LOOP(ALL,4096ULL, "put", (long long)0x0ULL);*//* 76ULL */
/*HLS_DEFINE_PROTOCOL("output");*//* 65ULL */
wait( 1LL ); // cycle_id 4
stall0 = o_result_m_stalling;
goto state24;
/********************/
state24:;
/*HLS_DEFINE_PROTOCOL("output");*//* 65ULL */
goto state25;
/********************/
state25:;
/*HLS_DEFINE_PROTOCOL("output");*//* 65ULL */
wait( 1LL ); // cycle_id 5
goto state5;
