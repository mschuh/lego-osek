node obst_detector
  (Co: real;
  Cg: real)
returns
  (obstacle: bool);

var
  V8_w_003: bool;
  V9_w_004: bool;
  V235_w_001: bool;
  V236_w_002: bool;
  V237_w_003: bool;
  V238_w_004: bool;
  V239_w_000: bool;
  V240_w_000: bool;
  V241_w_004: bool;
  V242_w_005: bool;
  V243_w_000: bool;
  V244_w_000: bool;
  V245_w_004: bool;
  V246_w_005: bool;
  V247_w_000: bool;
  V248_w_000: bool;
  V249_w_004: bool;
  V250_w_005: bool;
  V259_w_000: bool;
  V260_w_000: bool;
  V261_w_004: bool;
  V262_w_005: bool;

let
  obstacle = (V262_w_005 and V260_w_000);
  V8_w_003 = (false -> (pre V9_w_004));
  V9_w_004 = (V235_w_001 and V236_w_002);
  V235_w_001 = (V246_w_005 and V244_w_000);
  V236_w_002 = (V238_w_004 and V237_w_003);
  V237_w_003 = (V242_w_005 and V240_w_000);
  V238_w_004 = (V250_w_005 and V248_w_000);
  V239_w_000 = (Cg >= 90.000000);
  V240_w_000 = (not V8_w_003);
  V241_w_004 = (false -> (pre V237_w_003));
  V242_w_005 = (V239_w_000 or V241_w_004);
  V243_w_000 = (Cg >= 90.000000);
  V244_w_000 = (not V8_w_003);
  V245_w_004 = (false -> (pre V235_w_001));
  V246_w_005 = (V243_w_000 or V245_w_004);
  V247_w_000 = (Cg <= 35.000000);
  V248_w_000 = (not V8_w_003);
  V249_w_004 = (false -> (pre V238_w_004));
  V250_w_005 = (V247_w_000 or V249_w_004);
  V259_w_000 = (Co < 10.000000);
  V260_w_000 = (not V8_w_003);
  V261_w_004 = (false -> (pre obstacle));
  V262_w_005 = (V259_w_000 or V261_w_004);
tel

