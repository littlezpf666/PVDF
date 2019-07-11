#include "timer.h"


//////////////////////////////////////////////////////////////////////////////////	 
//1,增加TIM3_PWM_Init函数。
//2,增加LED0_PWM_VAL宏定义，控制TIM3_CH2脉宽									  
//////////////////////////////////////////////////////////////////////////////////  
   	  
//通用定时器3中断初始化

//这里时钟选择为APB1的2倍，而APB1为36M

//arr：自动重装值。 
//psc：时钟预分频数

//这里使用的是定时器3!
uint16_t si[][256]=
{
	//峰峰值500mV
	{
		2400,2400,2400,2401,2402,2403,2405,2407,2409,2411,2413,2416,2419,2422,2425,2429,2433,2437,2441,2445,2450,2455,2460,2465,2471,2477,2483,2489,2495,2502,2508,2515,2522,2529,2537,2544,2552,2560,2567,2576,2584,2592,2601,2609,2618,2627,2636,2645,2654,2663,2672,2682,2691,2701,2710,2720,2730,2739,2749,2759,2769,2779,2788,2798,2808,2818,2828,2838,2847,2857,2867,2877,2886,2896,2905,2915,2924,2933,2943,2952,2961,2970,2979,2988,2996,3005,3013,3021,3029,3037,3045,3053,3061,3068,3075,3082,3089,3096,3102,3109,3115,3121,3127,3132,3137,3143,3148,3152,3157,3161,3165,3169,3173,3176,3179,3182,3185,3188,3190,3192,3194,3195,3197,3198,3198,3199,3199,3199,3199,3199,3198,3197,3196,3195,3193,3192,3190,3187,3185,3182,3179,3176,3172,3169,3165,3160,3156,3152,3147,3142,3137,3131,3126,3120,3114,3108,3101,3095,3088,3081,3074,3067,3059,3052,3044,3036,3028,3020,3012,3003,2995,2986,2977,2968,2959,2950,2941,2932,2923,2913,2904,2894,2884,2875,2865,2855,2846,2836,2826,2816,2806,2796,2787,2777,2767,2757,2747,2738,2728,2718,2709,2699,2690,2680,2671,2661,2652,2643,2634,2625,2616,2608,2599,2591,2582,2574,2566,2558,2550,2543,2535,2528,2521,2514,2507,2500,2494,2488,2482,2476,2470,2465,2459,2454,2449,2445,2440,2436,2432,2428,2425,2421,2418,2415,2413,2410,2408,2406,2405,2403,2402,2401,2400,2400,2400,2400
	},//峰峰值1000mV
};

uint16_t triangle[][256]=
{
	 //峰峰值500mV
	{
  2400,2406,2412,2418,2425,2431,2437,2443,2450,2456,2462,2468,2475,2481,2487,2493,2500,2506,2512,2518,2525,2531,2537,2543,2550,2556,2562,2568,2575,2581,2587,2593,2600,2606,2612,2618,2625,2631,2637,2643,2650,2656,2662,2668,2675,2681,2687,2693,2700,2706,2712,2718,2725,2731,2737,2743,2750,2756,2762,2768,2775,2781,2787,2793,2800,2806,2812,2818,2825,2831,2837,2843,2850,2856,2862,2868,2875,2881,2887,2893,2900,2906,2912,2918,2925,2931,2937,2943,2950,2956,2962,2968,2975,2981,2987,2993,3000,3006,3012,3018,3025,3031,3037,3043,3050,3056,3062,3068,3075,3081,3087,3093,3100,3106,3112,3118,3125,3131,3137,3143,3150,3156,3162,3168,3175,3181,3187,3193,3193,3187,3181,3174,3168,3162,3155,3149,3143,3137,3130,3124,3118,3111,3105,3099,3092,3086,3080,3074,3067,3061,3055,3048,3042,3036,3029,3023,3017,3011,3004,2998,2992,2985,2979,2973,2966,2960,2954,2948,2941,2935,2929,2922,2916,2910,2903,2897,2891,2885,2878,2872,2866,2859,2853,2847,2840,2834,2828,2822,2815,2809,2803,2796,2790,2784,2777,2771,2765,2759,2752,2746,2740,2733,2727,2721,2714,2708,2702,2696,2689,2683,2677,2670,2664,2658,2651,2645,2639,2633,2626,2620,2614,2607,2601,2595,2588,2582,2576,2570,2563,2557,2551,2544,2538,2532,2525,2519,2513,2507,2500,2494,2488,2481,2475,2469,2462,2456,2450,2444,2437,2431,2425,2418,2412,2406,2400,2393,
	},
};
uint16_t square[][256]=
{
	 //峰峰值500mV
	{
  2400,2406,2412,2418,2425,2431,2437,2443,2450,2456,2462,2468,2475,2481,2487,2493,2500,2506,2512,2518,2525,2531,2537,2543,2550,2556,2562,2568,2575,2581,2587,2593,2600,2606,2612,2618,2625,2631,2637,2643,2650,2656,2662,2668,2675,2681,2687,2693,2700,2706,2712,2718,2725,2731,2737,2743,2750,2756,2762,2768,2775,2781,2787,2793,2800,2806,2812,2818,2825,2831,2837,2843,2850,2856,2862,2868,2875,2881,2887,2893,2900,2906,2912,2918,2925,2931,2937,2943,2950,2956,2962,2968,2975,2981,2987,2993,3000,3006,3012,3018,3025,3031,3037,3043,3050,3056,3062,3068,3075,3081,3087,3093,3100,3106,3112,3118,3125,3131,3137,3143,3150,3156,3162,3168,3175,3181,3187,3193,3193,3187,3181,3174,3168,3162,3155,3149,3143,3137,3130,3124,3118,3111,3105,3099,3092,3086,3080,3074,3067,3061,3055,3048,3042,3036,3029,3023,3017,3011,3004,2998,2992,2985,2979,2973,2966,2960,2954,2948,2941,2935,2929,2922,2916,2910,2903,2897,2891,2885,2878,2872,2866,2859,2853,2847,2840,2834,2828,2822,2815,2809,2803,2796,2790,2784,2777,2771,2765,2759,2752,2746,2740,2733,2727,2721,2714,2708,2702,2696,2689,2683,2677,2670,2664,2658,2651,2645,2639,2633,2626,2620,2614,2607,2601,2595,2588,2582,2576,2570,2563,2557,2551,2544,2538,2532,2525,2519,2513,2507,2500,2494,2488,2481,2475,2469,2462,2456,2450,2444,2437,2431,2425,2418,2412,2406,2400,2393,
	},
};
uint16_t ex[][256]=
{
	//峰峰值500mV
	{
		2801,2801,2801,2801,2801,2801,2801,2801,2801,2801,2801,2801,2801,2801,2801,2802,2802,2802,2802,2802,2802,2802,2802,2802,2803,2803,2803,2803,2803,2803,2804,2804,2804,2804,2804,2805,2805,2805,2805,2806,2806,2806,2807,2807,2807,2808,2808,2809,2809,2809,2810,2810,2811,2811,2812,2813,2813,2814,2815,2815,2816,2817,2818,2819,2819,2820,2821,2822,2824,2825,2826,2827,2829,2830,2831,2833,2835,2836,2838,2840,2842,2844,2846,2848,2850,2853,2855,2858,2861,2864,2867,2870,2874,2877,2881,2885,2889,2893,2898,2902,2907,2912,2918,2923,2929,2936,2942,2949,2956,2964,2972,2980,2988,2997,3007,3017,3027,3038,3050,3062,3074,3087,3101,3116,3131,3147,3163,3181,2799,2798,2798,2798,2798,2798,2798,2798,2798,2798,2798,2798,2798,2798,2798,2797,2797,2797,2797,2797,2797,2797,2797,2797,2796,2796,2796,2796,2796,2796,2795,2795,2795,2795,2795,2794,2794,2794,2794,2793,2793,2793,2792,2792,2792,2791,2791,2790,2790,2790,2789,2789,2788,2788,2787,2786,2786,2785,2784,2784,2783,2782,2781,2780,2780,2779,2778,2777,2775,2774,2773,2772,2770,2769,2768,2766,2764,2763,2761,2759,2757,2755,2753,2751,2749,2746,2744,2741,2738,2735,2732,2729,2725,2722,2718,2714,2710,2706,2701,2697,2692,2687,2681,2676,2670,2663,2657,2650,2643,2635,2627,2619,2611,2602,2592,2582,2572,2561,2549,2537,2525,2512,2498,2483,2468,2452,2436,2418,
	},
	
};
void TIM_Init(u16 crr2_val,u16 crr3_val)
{
	TIM3_GPIO_config();
	TIM3_Mode_config(crr2_val,crr3_val);
	TIM4_Mode_config(400,71);
}
void TIM3_GPIO_config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO , ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
  //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
	
	//设置该引脚为复用输出功能,输出TIM3 CH3的PWM脉冲波形	GPIOB.0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
}
void TIM3_Mode_config(u16 crr2_val,u16 crr3_val)
{ 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
	/*********************时基结构体初始化*************************/
	
	//因为PB5的默认复用功能没有Timer      所以Timer3要部分重映射  TIM3_CH2->PB5
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);      
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = GENERAL_TIM_Period; //设置重装初值  ARR控制脉冲周期
	TIM_TimeBaseStructure.TIM_Prescaler =GENERAL_TIM_Prescaler; //设置分频系数
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分频因子；时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //定时器3初始化
	
	
	/********************输出比较结构体初始化*********************/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1  CNT<CCRX 时为有效电平
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高  CC1P设为0 高电平为有效电平
	//输出比较通道2
	TIM_OCInitStructure.TIM_Pulse = crr2_val; 
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	//输出比较通道3
	TIM_OCInitStructure.TIM_Pulse = crr3_val;
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	//TIM_ARRPreloadConfig(TIM3, ENABLE);
	/*********************中断设置***************************/
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
  TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE);
	TIM_NVIC_Configuration();
	
	TIM_Cmd(TIM3, ENABLE);//使能计数器
}


void TIM4_Mode_config(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
 

  	/*********************中断设置***************************/
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
  TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE);
	TIM_Cmd(TIM4, DISABLE);
	TIM_NVIC_Configuration();
						 
}
//void TIM6_Mode_config()
//{
//	
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStucture;
////	TIM_OCInitTypeDef TIM_OCInitStucture;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
//	 //390us溢出一次256次0.1s
//	TIM_TimeBaseStucture.TIM_Period=390; 
//	TIM_TimeBaseStucture.TIM_Prescaler=71;
////	TIM_TimeBaseStucture.TIM_ClockDivision=TIM_CKD_DIV1;
////	TIM_TimeBaseStucture.TIM_CounterMode=TIM_CounterMode_Up;
//	
//	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStucture);
//	TIM_SelectOutputTrigger(TIM6,TIM_TRGOSource_Update);
//	TIM_Cmd(TIM6, ENABLE);
//	/*********************中断设置***************************/
//	TIM_ClearFlag(TIM6, TIM_FLAG_Update);
//  TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
//	TIM_NVIC_Configuration();
//}
//void TIM7_Mode_config()
//{
//	
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStucture;
////	TIM_OCInitTypeDef TIM_OCInitStucture;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);
//	TIM_TimeBaseStucture.TIM_Period=1000;//最大计数值 
//	TIM_TimeBaseStucture.TIM_Prescaler=71;//72MHz（71+1）分频为1MHz
////	TIM_TimeBaseStucture.TIM_ClockDivision=TIM_CKD_DIV1;//除6，7定时器其他定时器都有
////	TIM_TimeBaseStucture.TIM_CounterMode=TIM_CounterMode_Up;//基础定时器只有向上计数一种模式
//	
//	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseStucture);
///*********************中断设置***************************/
//	TIM_ClearFlag(TIM7, TIM_FLAG_Update);
//  TIM_ITConfig(TIM7,TIM_IT_Update,DISABLE);
//	TIM_Cmd(TIM7, DISABLE);
//	TIM_NVIC_Configuration();
//}



