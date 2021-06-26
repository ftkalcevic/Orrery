#include <math.h>
#include <time.h>
#include <stdio.h>
#include "Planets.h"

#define M_PI       3.14159265358979323846   // pi
#define M_PI_2     1.57079632679489661923   // pi/2

// http://neoprogrammics.com/vsop87/source_code_generator_tool/

/*
 ----------------------------------------------------------------------------
 Hard-Coded CPP Implementation of the VSOP87 Theory - Series Version B

 Body Name              : Mars
 VSOP87 Series Version  : B
 Coordinates Type/Epoch : Spherical LBR-Coordinates
                          HELIOCENTRIC DYNAMICAL ECLIPTIC/EQUINOX J2000

 Ephemeris Date Span    : 2000 BC < Date < 6000 AD

 These functions collectively compute the spherical space-time coordinates
 of the planet Mars according to the VSOP87 theory, series version B.

 JDTT = Standard Julian Date (JD) for any given moment on the TT scale.

    t = Julian millennia reckoned from J2000 (2000-Jan-01-Sat 12:00:00 TT)
      = (JDTT - 2451545.0) / 365250

 Source Code Generator Author:
 Jay Tanner - 2020

 License:
 This CPP program source code is released under the provisions of the
 Creative Commons Attribution-ShareAlike 4.0 International license.

 https://creativecommons.org/licenses/by-sa/4.0/legalcode
 ----------------------------------------------------------------------------
*/



static double Mercury(double t)
{
    double  L0 = 0.0;
    L0 += 4.40250710144;
    L0 += 0.40989414977 * cos(1.48302034195 + 26087.90314157420 * t);
    L0 += 0.05046294200 * cos(4.47785489551 + 52175.80628314840 * t);
    L0 += 0.00855346844 * cos(1.16520322459 + 78263.70942472259 * t);
    L0 += 0.00165590362 * cos(4.11969163423 + 104351.61256629678 * t);
    L0 += 0.00034561897 * cos(0.77930768443 + 130439.51570787099 * t);
    L0 += 0.00007583476 * cos(3.71348404924 + 156527.41884944518 * t);
    L0 += 0.00003559745 * cos(1.51202675145 + 1109.37855209340 * t);
    L0 += 0.00001726011 * cos(0.35832267096 + 182615.32199101939 * t);
    L0 += 0.00001803464 * cos(4.10333184211 + 5661.33204915220 * t);
    L0 += 0.00001364681 * cos(4.59918328256 + 27197.28169366760 * t);
    L0 += 0.00001589923 * cos(2.99510423560 + 25028.52121138500 * t);
    L0 += 0.00001017332 * cos(0.88031393824 + 31749.23519072640 * t);

    double  L1 = 0.0;
    L1 += 26087.90313685529;
    L1 += 0.01131199811 * cos(6.21874197797 + 26087.90314157420 * t);
    L1 += 0.00292242298 * cos(3.04449355541 + 52175.80628314840 * t);
    L1 += 0.00075775081 * cos(6.08568821653 + 78263.70942472259 * t);
    L1 += 0.00019676525 * cos(2.80965111777 + 104351.61256629678 * t);
    L1 += 0.00005119883 * cos(5.79432353574 + 130439.51570787099 * t);
    L1 += 0.00001336324 * cos(2.47909947012 + 156527.41884944518 * t);

    double  L2 = 0.0;
    L2 += 0.00016395129 * cos(4.67759555504 + 26087.90314157420 * t);
    L2 += 0.00008123865 * cos(1.40305644134 + 52175.80628314840 * t);
    L2 += 0.00003208170 * cos(4.49577853102 + 78263.70942472259 * t);
    L2 += 0.00001128209 * cos(1.27901273779 + 104351.61256629678 * t);

    double t2 = t * t;
    return L0 + L1 * t + L2 * t2;
}

static double Venus(double t)
{
    double  L0 = 0.0;
    L0 += 3.17614666774;
    L0 += 0.01353968419 * cos(5.59313319619 + 10213.28554621100 * t);
    L0 += 0.00089891645 * cos(5.30650047764 + 20426.57109242200 * t);
    L0 += 0.00005477194 * cos(4.41630661466 + 7860.41939243920 * t);
    L0 += 0.00003455741 * cos(2.69964447820 + 11790.62908865880 * t);
    L0 += 0.00002372061 * cos(2.99377542079 + 3930.20969621960 * t);
    L0 += 0.00001317168 * cos(5.18668228402 + 26.29831979980 * t);
    L0 += 0.00001664146 * cos(4.25018630147 + 1577.34354244780 * t);
    L0 += 0.00001438387 * cos(4.15745084182 + 9683.59458111640 * t);
    L0 += 0.00001200521 * cos(6.15357116043 + 30639.85663863300 * t);

    double  L1 = 0.0;
    L1 += 10213.28554621638;
    L1 += 0.00095617813 * cos(2.46406511110 + 10213.28554621100 * t);
    L1 += 0.00007787201 * cos(0.62478482220 + 20426.57109242200 * t);

    double  L2 = 0.0;
    L2 += 0.00003894209 * cos(0.34823650721 + 10213.28554621100 * t);

    double t2 = t * t;
    return L0 + L1 * t + L2 * t2;
}

static double Earth(double t)
{
    double  L0 = 0.0;
    L0 += 1.75347045673;
    L0 += 0.03341656453 * cos(4.66925680415 + 6283.07584999140 * t);
    L0 += 0.00034894275 * cos(4.62610242189 + 12566.15169998280 * t);
    L0 += 0.00003417572 * cos(2.82886579754 + 3.52311834900 * t);
    L0 += 0.00003497056 * cos(2.74411783405 + 5753.38488489680 * t);
    L0 += 0.00003135899 * cos(3.62767041756 + 77713.77146812050 * t);
    L0 += 0.00002676218 * cos(4.41808345438 + 7860.41939243920 * t);
    L0 += 0.00002342691 * cos(6.13516214446 + 3930.20969621960 * t);
    L0 += 0.00001273165 * cos(2.03709657878 + 529.69096509460 * t);
    L0 += 0.00001324294 * cos(0.74246341673 + 11506.76976979360 * t);

    double  L1 = 0.0;
    L1 += 6283.07584999140;
    L1 += 0.00206058863 * cos(2.67823455808 + 6283.07584999140 * t);
    L1 += 0.00004303419 * cos(2.63512233481 + 12566.15169998280 * t);

    double  L2 = 0.0;
    L2 += 0.00008721859 * cos(1.07253635559 + 6283.07584999140 * t);

    double t2 = t * t;
    return L0 + L1 * t + L2 * t2;
}

static double Mars(double t)
{
    double  L0 = 0.0;
    L0 += 6.20347711581;
    L0 += 0.18656368093 * cos(5.05037100270 + 3340.61242669980 * t);
    L0 += 0.01108216816 * cos(5.40099836344 + 6681.22485339960 * t);
    L0 += 0.00091798406 * cos(5.75478744667 + 10021.83728009940 * t);
    L0 += 0.00027744987 * cos(5.97049513147 + 3.52311834900 * t);
    L0 += 0.00010610235 * cos(2.93958560338 + 2281.23049651060 * t);
    L0 += 0.00012315897 * cos(0.84956094002 + 2810.92146160520 * t);
    L0 += 0.00008926784 * cos(4.15697846427 + 0.01725365220 * t);
    L0 += 0.00008715691 * cos(6.11005153139 + 13362.44970679920 * t);
    L0 += 0.00006797556 * cos(0.36462229657 + 398.14900340820 * t);
    L0 += 0.00007774872 * cos(3.33968761376 + 5621.84292321040 * t);
    L0 += 0.00003575078 * cos(1.66186505710 + 2544.31441988340 * t);
    L0 += 0.00004161108 * cos(0.22814971327 + 2942.46342329160 * t);
    L0 += 0.00003075252 * cos(0.85696614132 + 191.44826611160 * t);
    L0 += 0.00002628117 * cos(0.64806124465 + 3337.08930835080 * t);
    L0 += 0.00002937546 * cos(6.07893711402 + 0.06731030280 * t);
    L0 += 0.00002389414 * cos(5.03896442664 + 796.29800681640 * t);
    L0 += 0.00002579844 * cos(0.02996736156 + 3344.13554504880 * t);
    L0 += 0.00001528141 * cos(1.14979301996 + 6151.53388830500 * t);
    L0 += 0.00001798806 * cos(0.65634057445 + 529.69096509460 * t);
    L0 += 0.00001264357 * cos(3.62275122593 + 5092.15195811580 * t);
    L0 += 0.00001286228 * cos(3.06796065034 + 2146.16541647520 * t);
    L0 += 0.00001546404 * cos(2.91579701718 + 1751.53953141600 * t);
    L0 += 0.00001024902 * cos(3.69334099279 + 8962.45534991020 * t);

    double  L1 = 0.0;
    L1 += 3340.61242700512;
    L1 += 0.01457554523 * cos(3.60433733236 + 3340.61242669980 * t);
    L1 += 0.00168414711 * cos(3.92318567804 + 6681.22485339960 * t);
    L1 += 0.00020622975 * cos(4.26108844583 + 10021.83728009940 * t);
    L1 += 0.00003452392 * cos(4.73210393190 + 3.52311834900 * t);
    L1 += 0.00002586332 * cos(4.60670058555 + 13362.44970679920 * t);

    double  L2 = 0.0;
    L2 += 0.00058152577 * cos(2.04961712429 + 3340.61242669980 * t);
    L2 += 0.00013459579 * cos(2.45738706163 + 6681.22485339960 * t);
    L2 += 0.00002432575 * cos(2.79737979284 + 10021.83728009940 * t);

    double  L3 = 0.0;
    L3 += 0.00001467867 * cos(0.44429839460 + 3340.61242669980 * t);

    double t2 = t * t;
    double t3 = t2 * t;
    return L0 + L1 * t + L2 * t2 + L3 * t3;
}


static double Jupiter(double t)
{
    double  L0 = 0.0;
    L0 += 0.59954691494;
    L0 += 0.09695898719 * cos(5.06191793158 + 529.69096509460 * t);
    L0 += 0.00573610142 * cos(1.44406205629 + 7.11354700080 * t);
    L0 += 0.00306389205 * cos(5.41734730184 + 1059.38193018920 * t);
    L0 += 0.00097178296 * cos(4.14264726552 + 632.78373931320 * t);
    L0 += 0.00072903078 * cos(3.64042916389 + 522.57741809380 * t);
    L0 += 0.00064263975 * cos(3.41145165351 + 103.09277421860 * t);
    L0 += 0.00039806064 * cos(2.29376740788 + 419.48464387520 * t);
    L0 += 0.00038857767 * cos(1.27231755835 + 316.39186965660 * t);
    L0 += 0.00027964629 * cos(1.78454591820 + 536.80451209540 * t);
    L0 += 0.00013589730 * cos(5.77481040790 + 1589.07289528380 * t);
    L0 += 0.00008246349 * cos(3.58227925840 + 206.18554843720 * t);
    L0 += 0.00008768704 * cos(3.63000308199 + 949.17560896980 * t);
    L0 += 0.00007368042 * cos(5.08101194270 + 735.87651353180 * t);
    L0 += 0.00006263150 * cos(0.02497628807 + 213.29909543800 * t);
    L0 += 0.00006114062 * cos(4.51319998626 + 1162.47470440780 * t);
    L0 += 0.00004905396 * cos(1.32084470588 + 110.20632121940 * t);
    L0 += 0.00005305285 * cos(1.30671216791 + 14.22709400160 * t);
    L0 += 0.00005305441 * cos(4.18625634012 + 1052.26838318840 * t);
    L0 += 0.00004647248 * cos(4.69958103684 + 3.93215326310 * t);
    L0 += 0.00003045023 * cos(4.31676431084 + 426.59819087600 * t);
    L0 += 0.00002609999 * cos(1.56667394063 + 846.08283475120 * t);
    L0 += 0.00002028191 * cos(1.06376530715 + 3.18139373770 * t);
    L0 += 0.00001764763 * cos(2.14148655117 + 1066.49547719000 * t);
    L0 += 0.00001722972 * cos(3.88036268267 + 1265.56747862640 * t);
    L0 += 0.00001920945 * cos(0.97168196472 + 639.89728631400 * t);
    L0 += 0.00001633223 * cos(3.58201833555 + 515.46387109300 * t);
    L0 += 0.00001431999 * cos(4.29685556046 + 625.67019231240 * t);

    double  L1 = 0.0;
    L1 += 529.69096508814;
    L1 += 0.00489503243 * cos(4.22082939470 + 529.69096509460 * t);
    L1 += 0.00228917222 * cos(6.02646855621 + 7.11354700080 * t);
    L1 += 0.00030099479 * cos(4.54540782858 + 1059.38193018920 * t);
    L1 += 0.00020720920 * cos(5.45943156902 + 522.57741809380 * t);
    L1 += 0.00012103653 * cos(0.16994816098 + 536.80451209540 * t);
    L1 += 0.00006067987 * cos(4.42422292017 + 103.09277421860 * t);
    L1 += 0.00005433968 * cos(3.98480737746 + 419.48464387520 * t);
    L1 += 0.00004237744 * cos(5.89008707199 + 14.22709400160 * t);
    L1 += 0.00002211974 * cos(5.26766687382 + 206.18554843720 * t);
    L1 += 0.00001983502 * cos(4.88600705699 + 1589.07289528380 * t);
    L1 += 0.00001295769 * cos(5.55132752171 + 3.18139373770 * t);
    L1 += 0.00001163416 * cos(0.51450634873 + 3.93215326310 * t);
    L1 += 0.00001007167 * cos(0.46474690033 + 735.87651353180 * t);
    L1 += 0.00001174094 * cos(5.84238857133 + 1052.26838318840 * t);

    double  L2 = 0.0;
    L2 += 0.00047233601 * cos(4.32148536482 + 7.11354700080 * t);
    L2 += 0.00030649436 * cos(2.92977788700 + 529.69096509460 * t);
    L2 += 0.00014837605 * cos(3.14159265359);
    L2 += 0.00003189359 * cos(1.05515491122 + 522.57741809380 * t);
    L2 += 0.00002728901 * cos(4.84555421873 + 536.80451209540 * t);
    L2 += 0.00002547440 * cos(3.42720888976 + 1059.38193018920 * t);
    L2 += 0.00001721046 * cos(4.18734600902 + 14.22709400160 * t);

    double  L3 = 0.0;
    L3 += 0.00006501673 * cos(2.59862923650 + 7.11354700080 * t);
    L3 += 0.00001355012 * cos(1.34692775915 + 529.69096509460 * t);

    double t2 = t * t;
    double t3 = t2 * t;
    return L0 + L1 * t + L2 * t2 + L3 * t3;
}

static double Saturn(double t)
{
    double  L0 = 0.0;
    L0 += 0.87401354025;
    L0 += 0.11107659762 * cos(3.96205090159 + 213.29909543800 * t);
    L0 += 0.01414150957 * cos(4.58581516874 + 7.11354700080 * t);
    L0 += 0.00398379389 * cos(0.52112032699 + 206.18554843720 * t);
    L0 += 0.00350769243 * cos(3.30329907896 + 426.59819087600 * t);
    L0 += 0.00206816305 * cos(0.24658372002 + 103.09277421860 * t);
    L0 += 0.00079271300 * cos(3.84007056878 + 220.41264243880 * t);
    L0 += 0.00023990355 * cos(4.66976924553 + 110.20632121940 * t);
    L0 += 0.00016573588 * cos(0.43719228296 + 419.48464387520 * t);
    L0 += 0.00014906995 * cos(5.76903183869 + 316.39186965660 * t);
    L0 += 0.00015820290 * cos(0.93809155235 + 632.78373931320 * t);
    L0 += 0.00014609559 * cos(1.56518472000 + 3.93215326310 * t);
    L0 += 0.00013160301 * cos(4.44891291899 + 14.22709400160 * t);
    L0 += 0.00015053543 * cos(2.71669915667 + 639.89728631400 * t);
    L0 += 0.00013005299 * cos(5.98119023644 + 11.04570026390 * t);
    L0 += 0.00010725067 * cos(3.12939523827 + 202.25339517410 * t);
    L0 += 0.00005863206 * cos(0.23656938524 + 529.69096509460 * t);
    L0 += 0.00005227757 * cos(4.20783365759 + 3.18139373770 * t);
    L0 += 0.00006126317 * cos(1.76328667907 + 277.03499374140 * t);
    L0 += 0.00005019687 * cos(3.17787728405 + 433.71173787680 * t);
    L0 += 0.00004592550 * cos(0.61977744975 + 199.07200143640 * t);
    L0 += 0.00004005867 * cos(2.24479718502 + 63.73589830340 * t);
    L0 += 0.00002953796 * cos(0.98280366998 + 95.97922721780 * t);
    L0 += 0.00003873670 * cos(3.22283226966 + 138.51749687070 * t);
    L0 += 0.00002461186 * cos(2.03163875071 + 735.87651353180 * t);
    L0 += 0.00003269484 * cos(0.77492638211 + 949.17560896980 * t);
    L0 += 0.00001758145 * cos(3.26580109940 + 522.57741809380 * t);
    L0 += 0.00001640172 * cos(5.50504453050 + 846.08283475120 * t);
    L0 += 0.00001391327 * cos(4.02333150505 + 323.50541665740 * t);
    L0 += 0.00001580648 * cos(4.37265307169 + 309.27832265580 * t);
    L0 += 0.00001123498 * cos(2.83726798446 + 415.55249061210 * t);
    L0 += 0.00001017275 * cos(3.71700135395 + 227.52618943960 * t);
    L0 += 0.00000848642 * cos(3.19150170830 + 209.36694217490 * t);
    L0 += 0.00001087229 * cos(4.18343257560 + 2.44768055480 * t);

    double  L1 = 0.0;
    L1 += 213.29909521690;
    L1 += 0.01297370862 * cos(1.82834923978 + 213.29909543800 * t);
    L1 += 0.00564345393 * cos(2.88499717272 + 7.11354700080 * t);
    L1 += 0.00093734369 * cos(1.06311793502 + 426.59819087600 * t);
    L1 += 0.00107674962 * cos(2.27769131009 + 206.18554843720 * t);
    L1 += 0.00040244455 * cos(2.04108104671 + 220.41264243880 * t);
    L1 += 0.00019941774 * cos(1.27954390470 + 103.09277421860 * t);
    L1 += 0.00010511678 * cos(2.74880342130 + 14.22709400160 * t);
    L1 += 0.00006416106 * cos(0.38238295041 + 639.89728631400 * t);
    L1 += 0.00004848994 * cos(2.43037610229 + 419.48464387520 * t);
    L1 += 0.00004056892 * cos(2.92133209468 + 110.20632121940 * t);
    L1 += 0.00003768635 * cos(3.64965330780 + 3.93215326310 * t);
    L1 += 0.00003384691 * cos(2.41694503459 + 3.18139373770 * t);
    L1 += 0.00003231693 * cos(1.26149969158 + 433.71173787680 * t);
    L1 += 0.00003071405 * cos(2.32739504783 + 199.07200143640 * t);
    L1 += 0.00001953179 * cos(3.56378136497 + 11.04570026390 * t);
    L1 += 0.00001249468 * cos(2.62810757084 + 95.97922721780 * t);

    double  L2 = 0.0;
    L2 += 0.00116441330 * cos(1.17988132879 + 7.11354700080 * t);
    L2 += 0.00091841837 * cos(0.07325195840 + 213.29909543800 * t);
    L2 += 0.00036661728;
    L2 += 0.00015274496 * cos(4.06493179167 + 206.18554843720 * t);
    L2 += 0.00010987259 * cos(5.44479188310 + 426.59819087600 * t);
    L2 += 0.00010629830 * cos(0.25764306189 + 220.41264243880 * t);
    L2 += 0.00004265404 * cos(1.04596041482 + 14.22709400160 * t);
    L2 += 0.00001215447 * cos(2.91866579609 + 103.09277421860 * t);
    L2 += 0.00001142595 * cos(4.63711665368 + 639.89728631400 * t);
    L2 += 0.00001061494 * cos(5.68896768215 + 433.71173787680 * t);
    L2 += 0.00001020102 * cos(0.63368457250 + 3.18139373770 * t);
    L2 += 0.00001044759 * cos(4.04202827818 + 199.07200143640 * t);

    double  L3 = 0.0;
    L3 += 0.00016038732 * cos(5.73945573267 + 7.11354700080 * t);
    L3 += 0.00004254737 * cos(4.58877599687 + 213.29909543800 * t);
    L3 += 0.00001906379 * cos(4.76070843570 + 220.41264243880 * t);
    L3 += 0.00001464959 * cos(5.91328884284 + 206.18554843720 * t);
    L3 += 0.00001162062 * cos(5.61974313217 + 14.22709400160 * t);
    L3 += 0.00001044765 * cos(3.57813061587 + 426.59819087600 * t);

    double  L4 = 0.0;
    L4 += 0.00001661877 * cos(3.99824447634 + 7.11354700080 * t);

    double t2 = t * t;
    double t3 = t2 * t;
    double t4 = t3 * t;
    return L0 + L1 * t + L2 * t2 + L3 * t3 + L4 * t4;
}

static double Uranus(double t)
{
    double  L0 = 0.0;
    L0 += 5.48129294297;
    L0 += 0.09260408234 * cos(0.89106421507 + 74.78159856730 * t);
    L0 += 0.01504247898 * cos(3.62719260920 + 1.48447270830 * t);
    L0 += 0.00365981674 * cos(1.89962179044 + 73.29712585900 * t);
    L0 += 0.00272328168 * cos(3.35823706307 + 149.56319713460 * t);
    L0 += 0.00070328461 * cos(5.39254450063 + 63.73589830340 * t);
    L0 += 0.00068892678 * cos(6.09292483287 + 76.26607127560 * t);
    L0 += 0.00061998615 * cos(2.26952066061 + 2.96894541660 * t);
    L0 += 0.00061950719 * cos(2.85098872691 + 11.04570026390 * t);
    L0 += 0.00026468770 * cos(3.14152083966 + 71.81265315070 * t);
    L0 += 0.00025710476 * cos(6.11379840493 + 454.90936652730 * t);
    L0 += 0.00021078850 * cos(4.36059339067 + 148.07872442630 * t);
    L0 += 0.00017818647 * cos(1.74436930289 + 36.64856292950 * t);
    L0 += 0.00014613507 * cos(4.73732166022 + 3.93215326310 * t);
    L0 += 0.00011162509 * cos(5.82681796350 + 224.34479570190 * t);
    L0 += 0.00010997910 * cos(0.48865004018 + 138.51749687070 * t);
    L0 += 0.00009527478 * cos(2.95516862826 + 35.16409022120 * t);
    L0 += 0.00007545601 * cos(5.23626582400 + 109.94568878850 * t);
    L0 += 0.00004220241 * cos(3.23328220918 + 70.84944530420 * t);
    L0 += 0.00004051900 * cos(2.27755017300 + 151.04766984290 * t);
    L0 += 0.00003354596 * cos(1.06549007380 + 4.45341812490 * t);
    L0 += 0.00002926718 * cos(4.62903718891 + 9.56122755560 * t);
    L0 += 0.00003490340 * cos(5.48306144511 + 146.59425171800 * t);
    L0 += 0.00003144069 * cos(4.75199570434 + 77.75054398390 * t);
    L0 += 0.00002922333 * cos(5.35235361027 + 85.82729883120 * t);
    L0 += 0.00002272788 * cos(4.36600400036 + 70.32818044240 * t);
    L0 += 0.00002051219 * cos(1.51773566586 + 0.11187458460 * t);
    L0 += 0.00002148602 * cos(0.60745949945 + 38.13303563780 * t);
    L0 += 0.00001991643 * cos(4.92437588682 + 277.03499374140 * t);
    L0 += 0.00001376226 * cos(2.04283539351 + 65.22037101170 * t);
    L0 += 0.00001666902 * cos(3.62744066769 + 380.12776796000 * t);
    L0 += 0.00001284107 * cos(3.11347961505 + 202.25339517410 * t);
    L0 += 0.00001150429 * cos(0.93343589092 + 3.18139373770 * t);
    L0 += 0.00001533221 * cos(2.58594681212 + 52.69019803950 * t);
    L0 += 0.00001281604 * cos(0.54271272721 + 222.86032299360 * t);
    L0 += 0.00001372139 * cos(4.19641530878 + 111.43016149680 * t);
    L0 += 0.00001221029 * cos(0.19900650030 + 108.46121608020 * t);
    L0 += 0.00000946181 * cos(1.19253165736 + 127.47179660680 * t);
    L0 += 0.00001150989 * cos(4.17898916639 + 33.67961751290 * t);
    L0 += 0.00001244347 * cos(0.91614441731 + 2.44768055480 * t);
    L0 += 0.00001072013 * cos(0.23566016888 + 62.25142559510 * t);
    L0 += 0.00001090463 * cos(1.77501500531 + 12.53017297220 * t);

    double  L1 = 0.0;
    L1 += 74.78159860910;
    L1 += 0.00154332863 * cos(5.24158770553 + 74.78159856730 * t);
    L1 += 0.00024456474 * cos(1.71260334156 + 1.48447270830 * t);
    L1 += 0.00009258442 * cos(0.42829732350 + 11.04570026390 * t);
    L1 += 0.00008265977 * cos(1.50218091379 + 63.73589830340 * t);
    L1 += 0.00009150160 * cos(1.41213765216 + 149.56319713460 * t);
    L1 += 0.00003899108 * cos(0.46483579160 + 3.93215326310 * t);
    L1 += 0.00002277065 * cos(4.17199181523 + 76.26607127560 * t);
    L1 += 0.00001927470 * cos(0.52976188479 + 2.96894541660 * t);
    L1 += 0.00001232725 * cos(1.58632088145 + 70.84944530420 * t);

    double  L2 = 0.0;
    L2 += 0.00002349469 * cos(2.26708640433 + 74.78159856730 * t);

    double t2 = t * t;
    return L0 + L1 * t + L2 * t2;
}

static double Neptune(double t)
{
    double  L0 = 0.0;
    L0 += 5.31188633046;
    L0 += 0.01798475530 * cos(2.90101273890 + 38.13303563780 * t);
    L0 += 0.01019727652 * cos(0.48580922867 + 1.48447270830 * t);
    L0 += 0.00124531845 * cos(4.83008090676 + 36.64856292950 * t);
    L0 += 0.00042064466 * cos(5.41054993053 + 2.96894541660 * t);
    L0 += 0.00037714584 * cos(6.09221808686 + 35.16409022120 * t);
    L0 += 0.00033784738 * cos(1.24488874087 + 76.26607127560 * t);
    L0 += 0.00016482741 * cos(0.00007727998 + 491.55792945680 * t);
    L0 += 0.00009198584 * cos(4.93747051954 + 39.61750834610 * t);
    L0 += 0.00008994250 * cos(0.27462171806 + 175.16605980020 * t);
    L0 += 0.00004216242 * cos(1.98711875978 + 73.29712585900 * t);
    L0 += 0.00003364807 * cos(1.03590060915 + 33.67961751290 * t);
    L0 += 0.00002284800 * cos(4.20606949415 + 4.45341812490 * t);
    L0 += 0.00001433516 * cos(2.78339802539 + 74.78159856730 * t);

    double  L1 = 0.0;
    L1 += 38.13303563957;
    L1 += 0.00016604172 * cos(4.86323329249 + 1.48447270830 * t);
    L1 += 0.00015744045 * cos(2.27887427527 + 38.13303563780 * t);
    L1 += 0.00001306261 * cos(3.67285209620 + 2.96894541660 * t);

    return L0 + L1 * t;
}

double Degrees(double a) { return a / M_PI * 180; } // Rad -> Deg
double Radians(double a) { return a / 180 * M_PI; } // Deg -> Rad
double rev(double a) { return a - floor(a / 360.0) * 360.0; }   // normalise angle 0-360
double sind(double a) { return sin(Radians(a));}
double cosd(double a) { return cos(Radians(a));}
double atan2d(double y, double x) { return Degrees(atan2(y,x));}

double Sun(double d, double &L, double &M)
{
    double w = 282.9404 + 4.70935E-5 * d;           // (longitude of perihelion)
    double a = 1.000000;                            // (mean distance, a.u.)
    double e = 0.016709 - 1.151E-9 * d;             // (eccentricity)
    M = 356.0470 + 0.9856002585 * d;         // (mean anomaly)
    double oblecl = 23.4393 - 3.563E-7 * d;

    M = rev(M);

    L = rev(w + M);

    double E = M + (180 / M_PI) * e * sind(M) * (1 + e * cosd(M));

    double x = cosd(E) - e;
    double y = sind(E) * sqrt(1 - e * e);

    double r = sqrt(x * x + y * y);
    double v = atan2d(y, x);

    double lon = v + w;

    return lon;
}

// Returns 
//      lonm - longitude of earth to moon
//      lons - longitute of earth to sun
// return value lonm
static double Moon(double d, double &lonm, double &lons)
{
    // http://www.stjarnhimlen.se/comp/tutorial.html#7
    // Orbital elements of the Moon :
    double N = 125.1228 - 0.0529538083 * d;     // (Long asc.node)
    double i = 5.1454;                          // (Inclination)
    double w = 318.0634 + 0.1643573223 * d;     // (Arg.of perigee)
    double a = 60.2666;                         // (Mean distance)
    double e = 0.054900;                        // (Eccentricity)
    double M = 115.3654 + 13.0649929509 * d;    // (Mean anomaly)

    N = rev(N);
    w = rev(w);
    M = rev(M);

    double E0 = M + (180 / M_PI) * e * sind(M) * (1 + e * cosd(M));
    double E1 = E0 - (E0 - (180 / M_PI) * e * sind(E0) - M) / (1 - e * cosd(E0));
    double E = E1;;

    double x = a * (cosd(E) - e);
    double y = a * sqrt(1 - e * e) * sind(E);

    double r = sqrt(x * x + y * y);
    double v = atan2d(y, x);

    double xeclip = r * (cosd(N) * cosd(v + w) - sind(N) * sind(v + w) * cosd(i));
    double yeclip = r * (sind(N) * cosd(v + w) + cosd(N) * sind(v + w) * cosd(i));
    double zeclip = r * sind(v + w) * sind(i);

    double lon = atan2d(yeclip, xeclip);
    double lat = atan2d(zeclip, sqrt(xeclip * xeclip + yeclip * yeclip));
    double radius = sqrt(xeclip * xeclip + yeclip * yeclip + zeclip * zeclip); 

    double Ms, Ls;
    lons = Sun(d, Ls, Ms );

    double Lm = rev(N + w + M);
    double Mm = M;
    double D = rev(Lm - Ls);
    double F = rev(Lm - N);

    double Plon =  -1.274 * sind(Mm - 2 * D)    // (Evection)
                  + 0.658 * sind(2 * D)         // (Variation)
                  - 0.186 * sind(Ms)            // (Yearly equation)
                  - 0.059 * sind(2 * Mm - 2 * D)
                  - 0.057 * sind(Mm - 2 * D + Ms)
                  + 0.053 * sind(Mm + 2 * D)
                  + 0.046 * sind(2 * D - Ms)
                  + 0.041 * sind(Mm - Ms)
                  - 0.035 * sind(D)            // (Parallactic equation)
                  - 0.031 * sind(Mm + Ms)
                  - 0.015 * sind(2 * F - 2 * D)
                  + 0.011 * sind(Mm - 4 * D);

    lonm = rev(lon + Plon);

    return lonm;
}

//static double mod2pi(double x) {
//    const double tpi = 2.0 * M_PI;
//    return x - tpi * floor((x + M_PI) / tpi);
//}

// Compute JD - http://neoprogrammics.com/perpetual_calendar_algorithms/jd_number/

// y - eg 2021
// m - 1-12
// d - 1-31
// h:m:s
static double ymdhms2jd(int y, int m, int d, int hh, int mm, int ss)
{
    int CalMode = 1;

    double w = abs(y);

    if (y < 0)
        w = y + 1;
    else
        w = y;

    double a = floor((14 - m) / 12);
    double b = w - a;
    double c = floor(b / 100);

    double JD = floor(30.6001 * (12 * a + m + 1))
        + floor(365.25 * (b + 4716)) - 1524
        + CalMode * (floor(c / 4) - c + 2) + d;

    JD += -0.5 + (3600 * hh + 60 * mm + ss) / 86400.0;

    return JD;
}

int CalculatePlanets( struct tm *st, double *planet_positions, int planet_count )
{
	
	double JD = ymdhms2jd(st->tm_year+1900, st->tm_mon+1, st->tm_mday, st->tm_hour, st->tm_min, st->tm_sec );
	printf("JD=%d.%02d ", (int)JD,(int)(JD*100-((int)JD)*100));
	double d = (JD) - 2451543.5;
	double t = (JD - 2451545.0) / 365250;
	double Su,Mo;

	switch (planet_count)
	{
		default:
		case Planets::Jupiter:
			planet_positions[Planets::Jupiter] = rev(Degrees(Jupiter(t)));
		case Planets::Mars:
			planet_positions[Planets::Mars] = rev(Degrees(Mars(t)));
		case Planets::Moon:
			planet_positions[Planets::Moon] = rev(Moon(d, Mo, Su));
		case Planets::Earth:
			planet_positions[Planets::Earth] = rev(Degrees(Earth(t)));
		case Planets::Venus:
			planet_positions[Planets::Venus] = rev(Degrees(Venus(t)));
		case Planets::Mercury:
			planet_positions[Planets::Mercury] = rev(Degrees(Mercury(t)));
	}

	return 0;
}

