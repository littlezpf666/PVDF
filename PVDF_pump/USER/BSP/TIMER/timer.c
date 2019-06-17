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
		800,800,800,801,802,803,805,807,809,811,813,816,819,822,825,829,833,837,841,845,850,855,860,865,871,877,883,889,895,902,908,915,922,929,937,944,952,960,967,976,984,992,1001,1009,1018,1027,1036,1045,1054,1063,1072,1082,1091,1101,1110,1120,1130,1139,1149,1159,1169,1179,1188,1198,1208,1218,1228,1238,1247,1257,1267,1277,1286,1296,1305,1315,1324,1333,1343,1352,1361,1370,1379,1388,1396,1405,1413,1421,1429,1437,1445,1453,1461,1468,1475,1482,1489,1496,1502,1509,1515,1521,1527,1532,1537,1543,1548,1552,1557,1561,1565,1569,1573,1576,1579,1582,1585,1588,1590,1592,1594,1595,1597,1598,1598,1599,1599,1599,	
	},	
		//峰峰值1000mV
  {
		2048,2065,2082,2099,2116,2133,2151,2168,2185,2201,2218,2235,2251,2268,2284,2300,2316,2332,2348,2363,2379,2394,2408,2423,2438,2452,2466,2479,2493,2506,2519,2531,2544,2556,2568,2579,2590,2601,2611,2621,2631,2640,2649,2658,2666,2674,2681,2689,2695,2702,2708,2713,2718,2723,2727,2731,2735,2738,2740,2743,2744,2746,2747,2747,2747,2747,2746,2745,2744,2742,2739,2736,2733,2730,2725,2721,2716,2711,2705,2699,2692,2686,2678,2671,2663,2654,2645,2636,2627,2617,2607,2596,2585,2574,2562,2551,2538,2526,2513,2500,2487,2473,2460,2446,2431,2417,2402,2387,2372,2357,2341,2325,2309,2293,2277,2261,2244,2228,2211,2194,2177,2160,2143,2126,2109,2092,2074,2057,2040,2023,2006,1988,1971,1954,1937,1920,1903,1886,1870,1853,1836,1820,1804,1788,1772,1756,1740,1725,1710,1695,1680,1666,1651,1637,1623,1610,1596,1583,1571,1558,1546,1534,1523,1511,1500,1490,1480,1470,1460,1451,1442,1434,1425,1418,1410,1403,1397,1391,1385,1380,1375,1370,1366,1362,1359,1356,1354,1352,1350,1349,1348,1348,1348,1348,1349,1350,1352,1354,1357,1360,1363,1367,1371,1376,1381,1387,1393,1399,1406,1413,1420,1428,1436,1445,1454,1463,1473,1483,1493,1504,1515,1526,1538,1550,1562,1574,1587,1600,1614,1628,1641,1656,1670,1685,1699,1715,1730,1745,1761,1777,1793,1809,1825,1841,1858,1875,1891,1908,1925,1942,1959,1976,1994,2011,2028,2045
	},
	//峰峰值1500mV
	{
		2048,2074,2101,2127,2154,2180,2207,2233,2259,2285,2311,2337,2362,2387,2413,2437,2462,2487,2511,2535,2558,2581,2604,2627,2649,2671,2693,2714,2735,2755,2775,2794,2813,2832,2850,2867,2884,2901,2917,2933,2947,2962,2976,2989,3002,3014,3026,3037,3047,3057,3066,3074,3082,3090,3096,3102,3108,3112,3117,3120,3123,3125,3126,3127,3127,3127,3126,3124,3122,3119,3115,3110,3105,3100,3093,3087,3079,3071,3062,3053,3042,3032,3021,3009,2996,2983,2970,2956,2941,2926,2910,2894,2877,2860,2842,2824,2805,2786,2766,2746,2726,2705,2683,2662,2640,2617,2594,2571,2548,2524,2500,2476,2451,2427,2402,2376,2351,2325,2300,2274,2248,2221,2195,2169,2142,2116,2089,2063,2036,2009,1983,1956,1930,1903,1877,1851,1825,1799,1773,1747,1722,1697,1672,1647,1622,1598,1574,1550,1527,1503,1481,1458,1436,1414,1393,1372,1352,1331,1312,1292,1274,1255,1238,1220,1203,1187,1171,1156,1141,1127,1113,1100,1088,1076,1065,1054,1044,1034,1025,1017,1009,1002,996,990,985,981,977,974,971,969,968,968,968,968,970,972,975,978,982,987,992,998,1004,1012,1020,1028,1037,1047,1057,1068,1079,1092,1104,1117,1131,1146,1161,1176,1192,1208,1225,1243,1261,1279,1298,1318,1337,1358,1378,1400,1421,1443,1465,1488,1511,1534,1557,1581,1605,1630,1654,1679,1704,1730,1755,1781,1807,1833,1859,1885,1911,1938,1964,1991,2017,2044
	},
	//峰峰值2000mV
  {
		2048,2082,2117,2152,2187,2222,2257,2291,2325,2360,2394,2427,2461,2494,2527,2560,2593,2625,2657,2688,2719,2750,2780,2810,2839,2868,2896,2924,2951,2978,3004,3029,3054,3079,3102,3125,3148,3170,3191,3211,3231,3250,3268,3286,3302,3318,3333,3348,3362,3374,3386,3398,3408,3418,3426,3434,3441,3448,3453,3458,3461,3464,3466,3467,3467,3467,3465,3463,3460,3456,3451,3445,3439,3431,3423,3414,3404,3393,3381,3369,3356,3342,3327,3311,3295,3278,3260,3242,3222,3202,3182,3160,3138,3115,3092,3068,3043,3018,2992,2966,2939,2912,2884,2855,2826,2797,2767,2736,2706,2674,2643,2611,2579,2546,2513,2480,2446,2413,2379,2345,2311,2276,2241,2207,2172,2137,2102,2067,2032,1997,1962,1928,1893,1858,1823,1789,1755,1720,1687,1653,1619,1586,1553,1521,1488,1456,1425,1393,1363,1332,1302,1273,1244,1215,1187,1159,1132,1106,1080,1055,1030,1006,983,960,938,916,895,875,856,837,819,802,786,770,755,741,728,715,704,693,683,673,665,657,651,645,640,636,632,630,628,628,628,629,631,633,637,641,647,653,660,667,676,686,696,707,719,732,745,760,775,791,807,825,843,862,881,902,923,944,967,990,1013,1038,1062,1088,1114,1141,1168,1196,1224,1252,1282,1311,1341,1372,1403,1434,1466,1498,1531,1563,1596,1630,1663,1697,1731,1765,1799,1834,1869,1903,1938,1973,2008,2043
	},
	//峰峰值2500mV
	{
		2048,2092,2136,2180,2224,2267,2311,2355,2398,2441,2484,2527,2569,2611,2653,2694,2735,2775,2815,2855,2894,2933,2971,3008,3045,3081,3117,3152,3186,3220,3253,3285,3317,3347,3377,3406,3435,3462,3489,3514,3539,3563,3586,3608,3629,3649,3669,3687,3704,3720,3735,3750,3763,3775,3786,3796,3805,3813,3819,3825,3830,3833,3836,3837,3837,3837,3835,3832,3828,3823,3817,3809,3801,3792,3781,3770,3757,3743,3729,3713,3697,3679,3660,3641,3620,3599,3576,3553,3528,3503,3477,3450,3422,3394,3364,3334,3303,3271,3239,3205,3171,3137,3101,3066,3029,2992,2954,2916,2877,2838,2798,2758,2717,2676,2634,2593,2550,2508,2465,2422,2379,2336,2292,2248,2204,2160,2116,2072,2028,1984,1940,1896,1852,1809,1765,1722,1678,1635,1593,1550,1508,1466,1424,1383,1343,1302,1262,1223,1184,1146,1108,1071,1034,998,963,928,894,861,828,796,765,735,705,676,648,621,595,570,545,522,499,478,457,437,418,401,384,368,353,340,327,315,305,295,287,279,273,268,264,260,258,258,258,259,261,265,269,275,281,289,298,308,319,331,344,358,373,389,406,424,443,463,484,506,529,553,577,603,629,657,685,714,744,774,806,838,871,904,939,974,1009,1045,1082,1120,1158,1196,1235,1275,1315,1355,1396,1437,1479,1521,1563,1606,1648,1692,1735,1778,1822,1866,1910,1954,1998,2042
	},
	//峰峰值3000mV
	{
		2048,2097,2146,2195,2244,2293,2342,2391,2439,2487,2535,2583,2630,2677,2723,2770,2815,2861,2905,2950,2993,3036,3079,3121,3162,3203,3242,3282,3320,3358,3394,3430,3465,3500,3533,3566,3597,3628,3658,3686,3714,3741,3767,3791,3815,3837,3859,3879,3898,3916,3933,3949,3964,3977,3990,4001,4011,4020,4027,4034,4039,4043,4046,4047,4047,4047,4045,4041,4037,4031,4024,4016,4007,3996,3985,3972,3958,3942,3926,3909,3890,3870,3850,3828,3805,3781,3756,3729,3702,3674,3645,3615,3584,3552,3519,3485,3450,3415,3378,3341,3303,3265,3225,3185,3144,3103,3060,3018,2974,2930,2886,2841,2795,2750,2703,2657,2609,2562,2514,2466,2418,2369,2321,2272,2223,2174,2125,2075,2026,1977,1928,1878,1829,1781,1732,1683,1635,1587,1539,1492,1445,1398,1351,1305,1260,1215,1170,1126,1083,1040,998,956,915,875,835,797,759,721,685,649,614,581,548,515,484,454,425,396,369,343,318,293,270,248,227,207,189,171,155,139,125,112,100,90,80,72,65,59,54,51,49,48,48,49,52,56,61,67,74,83,93,104,116,129,144,159,176,194,213,234,255,277,301,325,351,377,405,434,463,494,525,558,591,625,660,696,733,770,808,848,887,928,969,1011,1053,1096,1140,1184,1229,1274,1319,1366,1412,1459,1506,1554,1602,1650,1698,1747,1796,1844,1894,1943,1992,2041
	}
};
uint16_t sawtooth[][256]=
{
	//峰峰值500mV
  {
		1668,1670,1672,1674,1676,1678,1680,1682,1684,1686,1688,1690,1692,1694,1696,1698,1700,1702,1704,1706,1708,1710,1712,1714,1716,1718,1720,1722,1724,1726,1728,1730,1732,1734,1736,1738,1740,1742,1744,1746,1748,1750,1752,1754,1756,1758,1760,1762,1764,1766,1768,1770,1772,1774,1776,1778,1780,1782,1784,1786,1788,1790,1792,1794,1796,1798,1800,1802,1804,1806,1808,1810,1812,1814,1816,1818,1820,1822,1824,1826,1828,1830,1832,1834,1836,1838,1840,1842,1844,1846,1848,1850,1852,1854,1856,1858,1860,1862,1864,1866,1868,1870,1872,1874,1876,1878,1880,1882,1884,1886,1888,1890,1892,1894,1896,1898,1900,1902,1904,1906,1908,1910,1912,1914,1916,1918,1920,1922,1924,1926,1928,1930,1932,1934,1936,1938,1940,1942,1944,1946,1948,1950,1952,1954,1956,1958,1960,1962,1964,1966,1968,1970,1972,1974,1976,1978,1980,1982,1984,1986,1988,1990,1992,1994,1996,1998,2000,2002,2004,2006,2008,2010,2012,2014,2016,2018,2020,2022,2024,2026,2028,2030,2032,2034,2036,2038,2040,2042,2044,2046,2048,2050,2052,2054,2056,2058,2060,2062,2064,2066,2068,2070,2072,2074,2076,2078,2080,2082,2084,2086,2088,2090,2092,2094,2096,2098,2100,2102,2104,2106,2108,2110,2112,2114,2116,2118,2120,2122,2124,2126,2128,2130,2132,2134,2136,2138,2140,2142,2144,2146,2148,2150,2152,2154,2156,2158,2160,2162,2164,2166,2168,2170,2172,2174,2176,2178
	},
		//峰峰值1000mV
  {
		1348,1353,1358,1363,1368,1373,1378,1383,1388,1393,1398,1403,1408,1413,1418,1423,1428,1433,1438,1443,1448,1453,1458,1463,1468,1473,1478,1483,1488,1493,1498,1503,1508,1513,1518,1523,1528,1533,1538,1543,1548,1553,1558,1563,1568,1573,1578,1583,1588,1593,1598,1603,1608,1613,1618,1623,1628,1633,1638,1643,1648,1653,1658,1663,1668,1673,1678,1683,1688,1693,1698,1703,1708,1713,1718,1723,1728,1733,1738,1743,1748,1753,1758,1763,1768,1773,1778,1783,1788,1793,1798,1803,1808,1813,1818,1823,1828,1833,1838,1843,1848,1853,1858,1863,1868,1873,1878,1883,1888,1893,1898,1903,1908,1913,1918,1923,1928,1933,1938,1943,1948,1953,1958,1963,1968,1973,1978,1983,1988,1993,1998,2003,2008,2013,2018,2023,2028,2033,2038,2043,2048,2053,2058,2063,2068,2073,2078,2083,2088,2093,2098,2103,2108,2113,2118,2123,2128,2133,2138,2143,2148,2153,2158,2163,2168,2173,2178,2183,2188,2193,2198,2203,2208,2213,2218,2223,2228,2233,2238,2243,2248,2253,2258,2263,2268,2273,2278,2283,2288,2293,2298,2303,2308,2313,2318,2323,2328,2333,2338,2343,2348,2353,2358,2363,2368,2373,2378,2383,2388,2393,2398,2403,2408,2413,2418,2423,2428,2433,2438,2443,2448,2453,2458,2463,2468,2473,2478,2483,2488,2493,2498,2503,2508,2513,2518,2523,2528,2533,2538,2543,2548,2553,2558,2563,2568,2573,2578,2583,2588,2593,2598,2603,2608,2613,2618,2623
	},
		//峰峰值1500mV
	{
		1098,1105,1112,1119,1126,1133,1140,1147,1154,1161,1168,1175,1182,1189,1196,1203,1210,1217,1224,1231,1238,1245,1252,1259,1266,1273,1280,1287,1294,1301,1308,1315,1322,1329,1336,1343,1350,1357,1364,1371,1378,1385,1392,1399,1406,1413,1420,1427,1434,1441,1448,1455,1462,1469,1476,1483,1490,1497,1504,1511,1518,1525,1532,1539,1546,1553,1560,1567,1574,1581,1588,1595,1602,1609,1616,1623,1630,1637,1644,1651,1658,1665,1672,1679,1686,1693,1700,1707,1714,1721,1728,1735,1742,1749,1756,1763,1770,1777,1784,1791,1798,1805,1812,1819,1826,1833,1840,1847,1854,1861,1868,1875,1882,1889,1896,1903,1910,1917,1924,1931,1938,1945,1952,1959,1966,1973,1980,1987,1994,2001,2008,2015,2022,2029,2036,2043,2050,2057,2064,2071,2078,2085,2092,2099,2106,2113,2120,2127,2134,2141,2148,2155,2162,2169,2176,2183,2190,2197,2204,2211,2218,2225,2232,2239,2246,2253,2260,2267,2274,2281,2288,2295,2302,2309,2316,2323,2330,2337,2344,2351,2358,2365,2372,2379,2386,2393,2400,2407,2414,2421,2428,2435,2442,2449,2456,2463,2470,2477,2484,2491,2498,2505,2512,2519,2526,2533,2540,2547,2554,2561,2568,2575,2582,2589,2596,2603,2610,2617,2624,2631,2638,2645,2652,2659,2666,2673,2680,2687,2694,2701,2708,2715,2722,2729,2736,2743,2750,2757,2764,2771,2778,2785,2792,2799,2806,2813,2820,2827,2834,2841,2848,2855,2862,2869,2876,2883
	},
	//峰峰值2000mV
	{
		748,758,768,778,788,798,808,818,828,838,848,858,868,878,888,898,908,918,928,938,948,958,968,978,988,998,1008,1018,1028,1038,1048,1058,1068,1078,1088,1098,1108,1118,1128,1138,1148,1158,1168,1178,1188,1198,1208,1218,1228,1238,1248,1258,1268,1278,1288,1298,1308,1318,1328,1338,1348,1358,1368,1378,1388,1398,1408,1418,1428,1438,1448,1458,1468,1478,1488,1498,1508,1518,1528,1538,1548,1558,1568,1578,1588,1598,1608,1618,1628,1638,1648,1658,1668,1678,1688,1698,1708,1718,1728,1738,1748,1758,1768,1778,1788,1798,1808,1818,1828,1838,1848,1858,1868,1878,1888,1898,1908,1918,1928,1938,1948,1958,1968,1978,1988,1998,2008,2018,2028,2038,2048,2058,2068,2078,2088,2098,2108,2118,2128,2138,2148,2158,2168,2178,2188,2198,2208,2218,2228,2238,2248,2258,2268,2278,2288,2298,2308,2318,2328,2338,2348,2358,2368,2378,2388,2398,2408,2418,2428,2438,2448,2458,2468,2478,2488,2498,2508,2518,2528,2538,2548,2558,2568,2578,2588,2598,2608,2618,2628,2638,2648,2658,2668,2678,2688,2698,2708,2718,2728,2738,2748,2758,2768,2778,2788,2798,2808,2818,2828,2838,2848,2858,2868,2878,2888,2898,2908,2918,2928,2938,2948,2958,2968,2978,2988,2998,3008,3018,3028,3038,3048,3058,3068,3078,3088,3098,3108,3118,3128,3138,3148,3158,3168,3178,3188,3198,3208,3218,3228,3238,3248,3258,3268,3278,3288,3298
	},
	//峰峰值2500mV
	{
		448,460,472,484,496,508,520,532,544,556,568,580,592,604,616,628,640,652,664,676,688,700,712,724,736,748,760,772,784,796,808,820,832,844,856,868,880,892,904,916,928,940,952,964,976,988,1000,1012,1024,1036,1048,1060,1072,1084,1096,1108,1120,1132,1144,1156,1168,1180,1192,1204,1216,1228,1240,1252,1264,1276,1288,1300,1312,1324,1336,1348,1360,1372,1384,1396,1408,1420,1432,1444,1456,1468,1480,1492,1504,1516,1528,1540,1552,1564,1576,1588,1600,1612,1624,1636,1648,1660,1672,1684,1696,1708,1720,1732,1744,1756,1768,1780,1792,1804,1816,1828,1840,1852,1864,1876,1888,1900,1912,1924,1936,1948,1960,1972,1984,1996,2008,2020,2032,2044,2056,2068,2080,2092,2104,2116,2128,2140,2152,2164,2176,2188,2200,2212,2224,2236,2248,2260,2272,2284,2296,2308,2320,2332,2344,2356,2368,2380,2392,2404,2416,2428,2440,2452,2464,2476,2488,2500,2512,2524,2536,2548,2560,2572,2584,2596,2608,2620,2632,2644,2656,2668,2680,2692,2704,2716,2728,2740,2752,2764,2776,2788,2800,2812,2824,2836,2848,2860,2872,2884,2896,2908,2920,2932,2944,2956,2968,2980,2992,3004,3016,3028,3040,3052,3064,3076,3088,3100,3112,3124,3136,3148,3160,3172,3184,3196,3208,3220,3232,3244,3256,3268,3280,3292,3304,3316,3328,3340,3352,3364,3376,3388,3400,3412,3424,3436,3448,3460,3472,3484,3496,3508
	},
	//峰峰值3000mV
	{
		48,63,78,93,108,123,138,153,168,183,198,213,228,243,258,273,288,303,318,333,348,363,378,393,408,423,438,453,468,483,498,513,528,543,558,573,588,603,618,633,648,663,678,693,708,723,738,753,768,783,798,813,828,843,858,873,888,903,918,933,948,963,978,993,1008,1023,1038,1053,1068,1083,1098,1113,1128,1143,1158,1173,1188,1203,1218,1233,1248,1263,1278,1293,1308,1323,1338,1353,1368,1383,1398,1413,1428,1443,1458,1473,1488,1503,1518,1533,1548,1563,1578,1593,1608,1623,1638,1653,1668,1683,1698,1713,1728,1743,1758,1773,1788,1803,1818,1833,1848,1863,1878,1893,1908,1923,1938,1953,1968,1983,1998,2013,2028,2043,2058,2073,2088,2103,2118,2133,2148,2163,2178,2193,2208,2223,2238,2253,2268,2283,2298,2313,2328,2343,2358,2373,2388,2403,2418,2433,2448,2463,2478,2493,2508,2523,2538,2553,2568,2583,2598,2613,2628,2643,2658,2673,2688,2703,2718,2733,2748,2763,2778,2793,2808,2823,2838,2853,2868,2883,2898,2913,2928,2943,2958,2973,2988,3003,3018,3033,3048,3063,3078,3093,3108,3123,3138,3153,3168,3183,3198,3213,3228,3243,3258,3273,3288,3303,3318,3333,3348,3363,3378,3393,3408,3423,3438,3453,3468,3483,3498,3513,3528,3543,3558,3573,3588,3603,3618,3633,3648,3663,3678,3693,3708,3723,3738,3753,3768,3783,3798,3813,3828,3843,3858,3873
	},
};

uint16_t triangle[][256]=
{
	 //峰峰值500mV
	{
   1691,1696,1701,1706,1711,1716,1721,1726,1731,1736,1741,1746,1751,1756,1761,1766,1771,1776,1781,1786,1791,1796,1801,1806,1811,1816,1821,1826,1831,1836,1841,1846,1851,1856,1861,1866,1871,1876,1881,1886,1891,1896,1901,1906,1911,1916,1921,1926,1931,1936,1941,1946,1951,1956,1961,1966,1971,1976,1981,1986,1991,1996,2001,2006,2011,2016,2021,2026,2031,2036,2041,2046,2051,2056,2061,2066,2071,2076,2081,2086,2091,2096,2101,2106,2111,2116,2121,2126,2131,2136,2141,2146,2151,2156,2161,2166,2171,2176,2181,2186,2191,2196,2201,2206,2211,2216,2221,2226,2231,2236,2241,2246,2251,2256,2261,2266,2271,2276,2281,2286,2291,2296,2301,2306,2311,2316,2321,2326,2349,2344,2339,2334,2329,2324,2319,2314,2309,2304,2299,2294,2289,2284,2279,2274,2269,2264,2259,2254,2249,2244,2239,2234,2229,2224,2219,2214,2209,2204,2199,2194,2189,2184,2179,2174,2169,2164,2159,2154,2149,2144,2139,2134,2129,2124,2119,2114,2109,2104,2099,2094,2089,2084,2079,2074,2069,2064,2059,2054,2049,2044,2039,2034,2029,2024,2019,2014,2009,2004,1999,1994,1989,1984,1979,1974,1969,1964,1959,1954,1949,1944,1939,1934,1929,1924,1919,1914,1909,1904,1899,1894,1889,1884,1879,1874,1869,1864,1859,1854,1849,1844,1839,1834,1829,1824,1819,1814,1809,1804,1799,1794,1789,1784,1779,1774,1769,1764,1759,1754,1749,1744,1739,1734,1729,1724,1719,1714
	},
	//峰峰值1000mV
	{
	1334,1345,1356,1367,1378,1389,1400,1411,1422,1433,1444,1455,1466,1477,1488,1499,1510,1521,1532,1543,1554,1565,1576,1587,1598,1609,1620,1631,1642,1653,1664,1675,1686,1697,1708,1719,1730,1741,1752,1763,1774,1785,1796,1807,1818,1829,1840,1851,1862,1873,1884,1895,1906,1917,1928,1939,1950,1961,1972,1983,1994,2005,2016,2027,2038,2049,2060,2071,2082,2093,2104,2115,2126,2137,2148,2159,2170,2181,2192,2203,2214,2225,2236,2247,2258,2269,2280,2291,2302,2313,2324,2335,2346,2357,2368,2379,2390,2401,2412,2423,2434,2445,2456,2467,2478,2489,2500,2511,2522,2533,2544,2555,2566,2577,2588,2599,2610,2621,2632,2643,2654,2665,2676,2687,2698,2709,2720,2731,2752,2741,2730,2719,2708,2697,2686,2675,2664,2653,2642,2631,2620,2609,2598,2587,2576,2565,2554,2543,2532,2521,2510,2499,2488,2477,2466,2455,2444,2433,2422,2411,2400,2389,2378,2367,2356,2345,2334,2323,2312,2301,2290,2279,2268,2257,2246,2235,2224,2213,2202,2191,2180,2169,2158,2147,2136,2125,2114,2103,2092,2081,2070,2059,2048,2037,2026,2015,2004,1993,1982,1971,1960,1949,1938,1927,1916,1905,1894,1883,1872,1861,1850,1839,1828,1817,1806,1795,1784,1773,1762,1751,1740,1729,1718,1707,1696,1685,1674,1663,1652,1641,1630,1619,1608,1597,1586,1575,1564,1553,1542,1531,1520,1509,1498,1487,1476,1465,1454,1443,1432,1421,1410,1399,1388,1377,1366,1355
	},
	//峰峰值1500mV
	{
		1257,1273,1289,1305,1321,1337,1353,1369,1385,1401,1417,1433,1449,1465,1481,1497,1513,1529,1545,1561,1577,1593,1609,1625,1641,1657,1673,1689,1705,1721,1737,1753,1769,1785,1801,1817,1833,1849,1865,1881,1897,1913,1929,1945,1961,1977,1993,2009,2025,2041,2057,2073,2089,2105,2121,2137,2153,2169,2185,2201,2217,2233,2249,2265,2281,2297,2313,2329,2345,2361,2377,2393,2409,2425,2441,2457,2473,2489,2505,2521,2537,2553,2569,2585,2601,2617,2633,2649,2665,2681,2697,2713,2729,2745,2761,2777,2793,2809,2825,2841,2857,2873,2889,2905,2921,2937,2953,2969,2985,3001,3017,3033,3049,3065,3081,3097,3113,3129,3145,3161,3177,3193,3209,3225,3241,3257,3273,3289,3213,3197,3181,3165,3149,3133,3117,3101,3085,3069,3053,3037,3021,3005,2989,2973,2957,2941,2925,2909,2893,2877,2861,2845,2829,2813,2797,2781,2765,2749,2733,2717,2701,2685,2669,2653,2637,2621,2605,2589,2573,2557,2541,2525,2509,2493,2477,2461,2445,2429,2413,2397,2381,2365,2349,2333,2317,2301,2285,2269,2253,2237,2221,2205,2189,2173,2157,2141,2125,2109,2093,2077,2061,2045,2029,2013,1997,1981,1965,1949,1933,1917,1901,1885,1869,1853,1837,1821,1805,1789,1773,1757,1741,1725,1709,1693,1677,1661,1645,1629,1613,1597,1581,1565,1549,1533,1517,1501,1485,1469,1453,1437,1421,1405,1389,1373,1357,1341,1325,1309,1293,1277,1261,1245,1229,1213,1197,1181
	},
	//峰峰值2000mV
	{
		679,701,723,745,767,789,811,833,855,877,899,921,943,965,987,1009,1031,1053,1075,1097,1119,1141,1163,1185,1207,1229,1251,1273,1295,1317,1339,1361,1383,1405,1427,1449,1471,1493,1515,1537,1559,1581,1603,1625,1647,1669,1691,1713,1735,1757,1779,1801,1823,1845,1867,1889,1911,1933,1955,1977,1999,2021,2043,2065,2087,2109,2131,2153,2175,2197,2219,2241,2263,2285,2307,2329,2351,2373,2395,2417,2439,2461,2483,2505,2527,2549,2571,2593,2615,2637,2659,2681,2703,2725,2747,2769,2791,2813,2835,2857,2879,2901,2923,2945,2967,2989,3011,3033,3055,3077,3099,3121,3143,3165,3187,3209,3231,3253,3275,3297,3319,3341,3363,3385,3407,3429,3451,3473,3517,3495,3473,3451,3429,3407,3385,3363,3341,3319,3297,3275,3253,3231,3209,3187,3165,3143,3121,3099,3077,3055,3033,3011,2989,2967,2945,2923,2901,2879,2857,2835,2813,2791,2769,2747,2725,2703,2681,2659,2637,2615,2593,2571,2549,2527,2505,2483,2461,2439,2417,2395,2373,2351,2329,2307,2285,2263,2241,2219,2197,2175,2153,2131,2109,2087,2065,2043,2021,1999,1977,1955,1933,1911,1889,1867,1845,1823,1801,1779,1757,1735,1713,1691,1669,1647,1625,1603,1581,1559,1537,1515,1493,1471,1449,1427,1405,1383,1361,1339,1317,1295,1273,1251,1229,1207,1185,1163,1141,1119,1097,1075,1053,1031,1009,987,965,943,921,899,877,855,833,811,789,767,745,723
	},
	//峰峰值2500mV
	{
		448,473,498,523,548,573,598,623,648,673,698,723,748,773,798,823,848,873,898,923,948,973,998,1023,1048,1073,1098,1123,1148,1173,1198,1223,1248,1273,1298,1323,1348,1373,1398,1423,1448,1473,1498,1523,1548,1573,1598,1623,1648,1673,1698,1723,1748,1773,1798,1823,1848,1873,1898,1923,1948,1973,1998,2023,2048,2073,2098,2123,2148,2173,2198,2223,2248,2273,2298,2323,2348,2373,2398,2423,2448,2473,2498,2523,2548,2573,2598,2623,2648,2673,2698,2723,2748,2773,2798,2823,2848,2873,2898,2923,2948,2973,2998,3023,3048,3073,3098,3123,3148,3173,3198,3223,3248,3273,3298,3323,3348,3373,3398,3423,3448,3473,3498,3523,3548,3573,3598,3623,3648,3623,3598,3573,3548,3523,3498,3473,3448,3423,3398,3373,3348,3323,3298,3273,3248,3223,3198,3173,3148,3123,3098,3073,3048,3023,2998,2973,2948,2923,2898,2873,2848,2823,2798,2773,2748,2723,2698,2673,2648,2623,2598,2573,2548,2523,2498,2473,2448,2423,2398,2373,2348,2323,2298,2273,2248,2223,2198,2173,2148,2123,2098,2073,2048,2023,1998,1973,1948,1923,1898,1873,1848,1823,1798,1773,1748,1723,1698,1673,1648,1623,1598,1573,1548,1523,1498,1473,1448,1423,1398,1373,1348,1323,1298,1273,1248,1223,1198,1173,1148,1123,1098,1073,1048,1023,998,973,948,923,898,873,848,823,798,773,748,723,698,673,648,623,598,573,548,523,498,473
	},
	//峰峰值3000mV
	{
		148,177,206,235,264,293,322,351,380,409,438,467,496,525,554,583,612,641,670,699,728,757,786,815,844,873,902,931,960,989,1018,1047,1076,1105,1134,1163,1192,1221,1250,1279,1308,1337,1366,1395,1424,1453,1482,1511,1540,1569,1598,1627,1656,1685,1714,1743,1772,1801,1830,1859,1888,1917,1946,1975,2004,2033,2062,2091,2120,2149,2178,2207,2236,2265,2294,2323,2352,2381,2410,2439,2468,2497,2526,2555,2584,2613,2642,2671,2700,2729,2758,2787,2816,2845,2874,2903,2932,2961,2990,3019,3048,3077,3106,3135,3164,3193,3222,3251,3280,3309,3338,3367,3396,3425,3454,3483,3512,3541,3570,3599,3628,3657,3686,3715,3744,3773,3802,3831,4036,4007,3978,3949,3920,3891,3862,3833,3804,3775,3746,3717,3688,3659,3630,3601,3572,3543,3514,3485,3456,3427,3398,3369,3340,3311,3282,3253,3224,3195,3166,3137,3108,3079,3050,3021,2992,2963,2934,2905,2876,2847,2818,2789,2760,2731,2702,2673,2644,2615,2586,2557,2528,2499,2470,2441,2412,2383,2354,2325,2296,2267,2238,2209,2180,2151,2122,2093,2064,2035,2006,1977,1948,1919,1890,1861,1832,1803,1774,1745,1716,1687,1658,1629,1600,1571,1542,1513,1484,1455,1426,1397,1368,1339,1310,1281,1252,1223,1194,1165,1136,1107,1078,1049,1020,991,962,933,904,875,846,817,788,759,730,701,672,643,614,585,556,527,498,469,440,411,382,353
	}
};

uint16_t ex[][256]=
{
	//峰峰值500mV
	{
		2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2050,2050,2050,2050,2050,2050,2050,2050,2050,2051,2051,2051,2051,2051,2051,2052,2052,2052,2052,2052,2053,2053,2053,2053,2054,2054,2054,2055,2055,2055,2056,2056,2056,2057,2057,2058,2058,2059,2059,2060,2060,2061,2061,2062,2063,2063,2064,2065,2066,2067,2067,2068,2069,2070,2071,2072,2074,2075,2076,2077,2079,2080,2082,2083,2085,2087,2089,2090,2092,2095,2097,2099,2101,2104,2107,2109,2112,2115,2118,2122,2125,2129,2132,2136,2140,2145,2149,2154,2159,2164,2169,2175,2181,2187,2194,2200,2207,2215,2223,2231,2239,2248,2257,2267,2277,2288,2299,2311,2323,2336,2349,2363,2047,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2045,2045,2045,2045,2045,2045,2045,2045,2045,2044,2044,2044,2044,2044,2044,2043,2043,2043,2043,2043,2042,2042,2042,2042,2041,2041,2041,2040,2040,2040,2039,2039,2039,2038,2038,2037,2037,2036,2036,2035,2035,2034,2034,2033,2032,2032,2031,2030,2029,2028,2028,2027,2026,2025,2024,2023,2021,2020,2019,2018,2016,2015,2013,2012,2010,2008,2006,2005,2003,2000,1998,1996,1994,1991,1988,1986,1983,1980,1977,1973,1970,1966,1963,1959,1955,1950,1946,1941,1936,1931,1926,1920,1914,1908,1901,1895,1888,1880,1872,1864,1856,1847,1838,1828,1818,1807,1796,1784,1772,1759,1746,1732
	},
	//峰峰值1000mV
	{
		2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2050,2050,2050,2050,2050,2050,2050,2050,2051,2051,2051,2051,2051,2051,2052,2052,2052,2052,2053,2053,2053,2053,2054,2054,2054,2055,2055,2056,2056,2056,2057,2057,2058,2058,2059,2060,2060,2061,2062,2062,2063,2064,2065,2066,2067,2068,2069,2070,2071,2072,2073,2075,2076,2078,2079,2081,2082,2084,2086,2088,2090,2093,2095,2097,2100,2103,2106,2109,2112,2115,2119,2122,2126,2130,2135,2139,2144,2149,2154,2160,2166,2172,2178,2185,2192,2200,2208,2216,2225,2234,2244,2254,2265,2276,2288,2301,2314,2328,2343,2358,2374,2391,2409,2428,2448,2469,2491,2514,2538,2563,2590,2619,2648,2680,2047,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2045,2045,2045,2045,2045,2045,2045,2045,2044,2044,2044,2044,2044,2044,2043,2043,2043,2043,2042,2042,2042,2042,2041,2041,2041,2040,2040,2039,2039,2039,2038,2038,2037,2037,2036,2035,2035,2034,2033,2033,2032,2031,2030,2029,2028,2027,2026,2025,2024,2023,2022,2020,2019,2017,2016,2014,2013,2011,2009,2007,2005,2002,2000,1998,1995,1992,1989,1986,1983,1980,1976,1973,1969,1965,1960,1956,1951,1946,1941,1935,1929,1923,1917,1910,1903,1895,1887,1879,1870,1861,1851,1841,1830,1819,1807,1794,1781,1767,1752,1737,1721,1704,1686,1667,1647,1626,1604,1581,1557,1532,1505,1476,1447,1415
	},
	//峰峰值1500mV
	{
		2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2050,2050,2050,2050,2050,2050,2050,2050,2051,2051,2051,2051,2051,2052,2052,2052,2052,2053,2053,2053,2053,2054,2054,2054,2055,2055,2056,2056,2057,2057,2058,2058,2059,2059,2060,2061,2062,2062,2063,2064,2065,2066,2067,2068,2069,2070,2072,2073,2074,2076,2077,2079,2081,2083,2085,2087,2089,2091,2093,2096,2099,2102,2104,2108,2111,2114,2118,2122,2126,2131,2135,2140,2145,2151,2156,2162,2169,2175,2183,2190,2198,2206,2215,2224,2234,2244,2255,2267,2279,2292,2305,2320,2335,2351,2367,2385,2404,2424,2444,2466,2490,2514,2540,2567,2596,2626,2658,2692,2728,2766,2805,2847,2892,2938,2988,2047,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2045,2045,2045,2045,2045,2045,2045,2045,2044,2044,2044,2044,2044,2043,2043,2043,2043,2042,2042,2042,2042,2041,2041,2041,2040,2040,2039,2039,2038,2038,2037,2037,2036,2036,2035,2034,2033,2033,2032,2031,2030,2029,2028,2027,2026,2025,2023,2022,2021,2019,2018,2016,2014,2012,2010,2008,2006,2004,2002,1999,1996,1993,1991,1987,1984,1981,1977,1973,1969,1964,1960,1955,1950,1944,1939,1933,1926,1920,1912,1905,1897,1889,1880,1871,1861,1851,1840,1828,1816,1803,1790,1775,1760,1744,1728,1710,1691,1671,1651,1629,1605,1581,1555,1528,1499,1469,1437,1403,1367,1329,1290,1248,1203,1157,1107
	},
	//峰峰值2000mV
  {
		2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2050,2050,2050,2050,2050,2050,2050,2051,2051,2051,2051,2051,2052,2052,2052,2052,2053,2053,2053,2054,2054,2054,2055,2055,2056,2056,2056,2057,2058,2058,2059,2059,2060,2061,2062,2062,2063,2064,2065,2066,2067,2068,2070,2071,2072,2074,2075,2077,2078,2080,2082,2084,2086,2088,2091,2093,2096,2099,2102,2105,2108,2112,2115,2119,2124,2128,2133,2138,2143,2148,2154,2160,2167,2174,2181,2189,2197,2205,2215,2224,2235,2245,2257,2269,2282,2295,2310,2325,2341,2358,2376,2395,2415,2436,2459,2482,2508,2534,2562,2592,2624,2657,2692,2729,2769,2811,2855,2902,2951,3003,3059,3117,3179,3244,3314,2047,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2045,2045,2045,2045,2045,2045,2045,2044,2044,2044,2044,2044,2043,2043,2043,2043,2042,2042,2042,2041,2041,2041,2040,2040,2039,2039,2039,2038,2037,2037,2036,2036,2035,2034,2033,2033,2032,2031,2030,2029,2028,2027,2025,2024,2023,2021,2020,2018,2017,2015,2013,2011,2009,2007,2004,2002,1999,1996,1993,1990,1987,1983,1980,1976,1971,1967,1962,1957,1952,1947,1941,1935,1928,1921,1914,1906,1898,1890,1880,1871,1860,1850,1838,1826,1813,1800,1785,1770,1754,1737,1719,1700,1680,1659,1636,1613,1587,1561,1533,1503,1471,1438,1403,1366,1326,1284,1240,1193,1144,1092,1036,978,916,851,781
	},
  //峰峰值2500mV
  {
	 2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2050,2050,2050,2050,2050,2050,2050,2050,2051,2051,2051,2051,2052,2052,2052,2052,2053,2053,2053,2054,2054,2054,2055,2055,2056,2056,2056,2057,2058,2058,2059,2060,2060,2061,2062,2063,2064,2064,2066,2067,2068,2069,2070,2072,2073,2074,2076,2078,2080,2082,2084,2086,2088,2090,2093,2096,2098,2102,2105,2108,2112,2116,2120,2124,2128,2133,2138,2144,2150,2156,2162,2169,2176,2184,2192,2200,2209,2219,2229,2240,2252,2264,2277,2290,2305,2320,2336,2353,2372,2391,2411,2433,2456,2480,2506,2533,2562,2593,2625,2660,2696,2735,2776,2819,2865,2914,2965,3020,3078,3139,3204,3273,3346,3423,3505,3592,2047,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2045,2045,2045,2045,2045,2045,2045,2045,2044,2044,2044,2044,2043,2043,2043,2043,2042,2042,2042,2041,2041,2041,2040,2040,2039,2039,2039,2038,2037,2037,2036,2035,2035,2034,2033,2032,2031,2031,2029,2028,2027,2026,2025,2023,2022,2021,2019,2017,2015,2013,2011,2009,2007,2005,2002,1999,1997,1993,1990,1987,1983,1979,1975,1971,1967,1962,1957,1951,1945,1939,1933,1926,1919,1911,1903,1895,1886,1876,1866,1855,1843,1831,1818,1805,1790,1775,1759,1742,1723,1704,1684,1662,1639,1615,1589,1562,1533,1502,1470,1435,1399,1360,1319,1276,1230,1181,1130,1075,1017,956,891,822,749,672,590,503
	},
  //峰峰值3000mV
  {
	 2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2050,2050,2050,2050,2050,2050,2050,2051,2051,2051,2051,2051,2052,2052,2052,2052,2053,2053,2053,2054,2054,2055,2055,2055,2056,2056,2057,2058,2058,2059,2060,2060,2061,2062,2063,2064,2065,2066,2067,2068,2069,2071,2072,2074,2075,2077,2079,2081,2083,2085,2087,2090,2092,2095,2098,2101,2104,2108,2111,2115,2119,2124,2128,2133,2139,2144,2150,2156,2163,2170,2178,2186,2194,2203,2213,2223,2233,2245,2257,2270,2283,2298,2313,2329,2346,2365,2384,2405,2426,2450,2474,2500,2528,2557,2589,2622,2657,2694,2734,2776,2820,2868,2918,2971,3027,3087,3151,3219,3290,3366,3447,3532,3623,3720,3822,3931,2047,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2045,2045,2045,2045,2045,2045,2045,2044,2044,2044,2044,2044,2043,2043,2043,2043,2042,2042,2042,2041,2041,2040,2040,2040,2039,2039,2038,2037,2037,2036,2035,2035,2034,2033,2032,2031,2030,2029,2028,2027,2026,2024,2023,2021,2020,2018,2016,2014,2012,2010,2008,2005,2003,2000,1997,1994,1991,1987,1984,1980,1976,1971,1967,1962,1956,1951,1945,1939,1932,1925,1917,1909,1901,1892,1882,1872,1862,1850,1838,1825,1812,1797,1782,1766,1749,1730,1711,1690,1669,1645,1621,1595,1567,1538,1506,1473,1438,1401,1361,1319,1275,1227,1177,1124,1068,1008,944,876,805,729,648,563,472,375,273,164
	}
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



