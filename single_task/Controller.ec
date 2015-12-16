const
  pi : real;
  kp_teta : real;
  ki_teta : real;
  
node Controller
  (Cg: real;
  Cd: real;
  Co: real)
returns
  (u_d: real;
  u_g: real);

var
  V12_w_002: bool;
  V14_w_004: real;
  V16_w_006: real;
  V18_w_008: bool;
  V19_w_009: bool;
  V21_w_011: real;
  V23_w_013: real;
  V304_w_001: bool;
  V305_w_002: bool;
  V306_w_003: bool;
  V307_w_004: bool;
  V308_w_000: bool;
  V309_w_000: bool;
  V310_w_004: bool;
  V311_w_005: bool;
  V312_w_000: bool;
  V313_w_000: bool;
  V314_w_004: bool;
  V315_w_005: bool;
  V316_w_000: bool;
  V317_w_000: bool;
  V318_w_004: bool;
  V319_w_005: bool;
  V328_w_000: bool;
  V329_w_001: bool;
  V330_w_004: bool;
  V331_w_005: bool;
  V344_w_004: real;
  V366_w_003: real;
  V367_w_004: real;
  V368_w_005: real;
  V369_w_006: real;
  V370_w_007: real;
  V371_w_008: real;
  V372_w_009: real;
  V373_w_011: real;
  V374_w_012: real;
  V375_w_013: real;
  V376_w_014: real;
  V377_w_015: real;
  V378_w_016: real;

let
  u_d = (if V12_w_002 then 0.100000 else V16_w_006);
  u_g = (if V12_w_002 then -0.100000 else V14_w_004);
  V12_w_002 = (V331_w_005 and V329_w_001);
  V14_w_004 = ((1.000000 / 2.000000) * V375_w_013);
  V16_w_006 = ((1.000000 / 2.000000) * V376_w_014);
  V18_w_008 = (false -> (pre V19_w_009));
  V19_w_009 = (V304_w_001 and V305_w_002);
  V21_w_011 = ((pi / 200.000000) * V344_w_004);
  V23_w_013 = (Cd + Cg);
  V304_w_001 = (V315_w_005 and V313_w_000);
  V305_w_002 = (V307_w_004 and V306_w_003);
  V306_w_003 = (V311_w_005 and V309_w_000);
  V307_w_004 = (V319_w_005 and V317_w_000);
  V308_w_000 = (Cg >= 90.000000);
  V309_w_000 = (not V18_w_008);
  V310_w_004 = (false -> (pre V306_w_003));
  V311_w_005 = (V308_w_000 or V310_w_004);
  V312_w_000 = (Cg >= 90.000000);
  V313_w_000 = (not V18_w_008);
  V314_w_004 = (false -> (pre V304_w_001));
  V315_w_005 = (V312_w_000 or V314_w_004);
  V316_w_000 = (Cg <= 10.000000);
  V317_w_000 = (not V18_w_008);
  V318_w_004 = (false -> (pre V307_w_004));
  V319_w_005 = (V316_w_000 or V318_w_004);
  V328_w_000 = (Co < 20.000000);
  V329_w_001 = (not V18_w_008);
  V330_w_004 = (false -> (pre V12_w_002));
  V331_w_005 = (V330_w_004 or V328_w_000);
  V344_w_004 = (Cd - Cg);
  V366_w_003 = (0.000000 -> (pre V367_w_004));
  V367_w_004 = (V368_w_005 + V366_w_003);
  V368_w_005 = (0.002000 * V21_w_011);
  V369_w_006 = (V378_w_016 + V377_w_015);
  V370_w_007 = ((-V372_w_009) + V373_w_011);
  V371_w_008 = (2.000000 * V370_w_007);
  V372_w_009 = (if (V374_w_012 < 0.000000) then (-V374_w_012) else V374_w_012);
  V373_w_011 = (0.005000 * V23_w_013);
  V374_w_012 = (2.000000 * V369_w_006);
  V375_w_013 = ((-V369_w_006) + V371_w_008);
  V376_w_014 = (V369_w_006 + V371_w_008);
  V377_w_015 = (kp_teta * V21_w_011);
  V378_w_016 = (ki_teta * V367_w_004);
tel

