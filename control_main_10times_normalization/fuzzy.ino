Fuzzy *fuzzy = new Fuzzy();
/*
// Fuzzy input eDO (error DO)
FuzzySet *eNB = new FuzzySet(-6, -6, -1.5, -1);
FuzzySet *eNK = new FuzzySet(-1.6, -1.1, -1.1, -0.65);
FuzzySet *eN = new FuzzySet(-1.3, -0.8, -0.8, 0.0);
FuzzySet *ePK = new FuzzySet(-1.3, -0.5, -0.5, 0.2);
FuzzySet *ePB = new FuzzySet(-0.1, -0.08, 6, 6);

// Fuzzy input dDO (delta error DO)
FuzzySet *dNB = new FuzzySet(-1, -1, -0.1, -0.1);
FuzzySet *dNK = new FuzzySet(-0.2, -0.1, -0.1, 0.6);
FuzzySet *dN = new FuzzySet(-0.2, -0.1, -0.1, -0);
FuzzySet *dPK = new FuzzySet(0, 0, 0, 0);
FuzzySet *dPB = new FuzzySet(0.1, 0.1, 1, 1);

*/
// Fuzzy output classoal
FuzzySet *mati = new FuzzySet(0, 0, 190, 200);
FuzzySet *lambat = new FuzzySet(180, 210, 210, 230);
FuzzySet *cepat = new FuzzySet(230, 250, 260, 260);

//////////////////////////////////////////////////////////////////
//7
/*
// Fuzzy input eDO (error DO)
FuzzySet *eNB = new FuzzySet(-60, -60, -2, -1);
FuzzySet *eNK = new FuzzySet(-1, -0.3, -0.3, -0.1);
FuzzySet *eN = new FuzzySet(-0.1, 0, 0, 0.1);
FuzzySet *ePK = new FuzzySet(0, 0.1, 0.1, 1);
FuzzySet *ePB = new FuzzySet(0.2, 2, 60, 60);

// Fuzzy input dDO (delta error DO)
FuzzySet *dNB = new FuzzySet(-10, -10, -1, -0.5);
FuzzySet *dNK = new FuzzySet(-1, -0.3, -0.3, 0);
FuzzySet *dN = new FuzzySet(-0.1, 0, 0, 1);
FuzzySet *dPK = new FuzzySet(0, 0.3, 0.3, 1);
FuzzySet *dPB = new FuzzySet(0.5, 1, 10, 10);
*/
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//8

// Fuzzy input eDO (error DO)
FuzzySet *eNB = new FuzzySet(-60, -60, -1, 0);
FuzzySet *eNK = new FuzzySet(-2, -1, -1, 0);
FuzzySet *eN = new FuzzySet(-0.1, 0, 0, 0.1);
FuzzySet *ePK = new FuzzySet(0, 1, 1, 2);
FuzzySet *ePB = new FuzzySet(0, 1, 60, 60);

// Fuzzy input dDO (delta error DO)
FuzzySet *dNB = new FuzzySet(-10, -10, -1, -0.5);
FuzzySet *dNK = new FuzzySet(-1, -0.5, -0.5, 0);
FuzzySet *dN = new FuzzySet(-0.2, 0, 0, 0.2);
FuzzySet *dPK = new FuzzySet(0, 0.5, 0.5, 1);
FuzzySet *dPB = new FuzzySet(0.5, 1, 10, 10);

//////////////////////////////////////////////////////////////////

void fuzzy_begin() {
  // input eDO
  FuzzyInput *eDO_f = new FuzzyInput(1);

  eDO_f->addFuzzySet(eNB);
  eDO_f->addFuzzySet(eNK);
  eDO_f->addFuzzySet(eN);
  eDO_f->addFuzzySet(ePK);
  eDO_f->addFuzzySet(ePB);
  fuzzy->addFuzzyInput(eDO_f);

  // input dDO
  FuzzyInput *dDO_f = new FuzzyInput(2);

  dDO_f->addFuzzySet(dNB);
  dDO_f->addFuzzySet(dNK);
  dDO_f->addFuzzySet(dN);
  dDO_f->addFuzzySet(dPK);
  dDO_f->addFuzzySet(dPB);
  fuzzy->addFuzzyInput(dDO_f);

  //setPoint = setPoint + 1;

  // ouput class
  FuzzyOutput *kecepatan = new FuzzyOutput(1);

  kecepatan->addFuzzySet(mati);
  kecepatan->addFuzzySet(lambat);
  kecepatan->addFuzzySet(cepat);
  fuzzy->addFuzzyOutput(kecepatan);

  FuzzyRuleConsequent *kecepatan_mati = new FuzzyRuleConsequent();
  kecepatan_mati->addOutput(mati);

  FuzzyRuleConsequent *kecepatan_lambat = new FuzzyRuleConsequent();
  kecepatan_lambat->addOutput(lambat);

  FuzzyRuleConsequent *kecepatan_cepat = new FuzzyRuleConsequent();
  kecepatan_cepat->addOutput(cepat);

  // Fuzzy Rule 1
  FuzzyRuleAntecedent *eNB_dNB = new FuzzyRuleAntecedent();
  eNB_dNB->joinWithAND(eNB, dNB);

  FuzzyRule *fuzzyRule1 = new FuzzyRule(1, eNB_dNB, kecepatan_mati);
  fuzzy->addFuzzyRule(fuzzyRule1);

  // Fuzzy Rule 2
  FuzzyRuleAntecedent *eNB_dNK = new FuzzyRuleAntecedent();
  eNB_dNK->joinWithAND(eNB, dNK);

  FuzzyRule *fuzzyRule2 = new FuzzyRule(2, eNB_dNK, kecepatan_mati);
  fuzzy->addFuzzyRule(fuzzyRule2);

  // Fuzzy Rule 3
  FuzzyRuleAntecedent *eNB_dN = new FuzzyRuleAntecedent();
  eNB_dN->joinWithAND(eNB, dN);

  FuzzyRule *fuzzyRule3 = new FuzzyRule(3, eNB_dN, kecepatan_mati);
  fuzzy->addFuzzyRule(fuzzyRule3);

  // Fuzzy Rule 4
  FuzzyRuleAntecedent *eNB_dPK = new FuzzyRuleAntecedent();
  eNB_dPK->joinWithAND(eNB, dPK);

  FuzzyRule *fuzzyRule4 = new FuzzyRule(4, eNB_dPK, kecepatan_mati);
  fuzzy->addFuzzyRule(fuzzyRule4);

  // Fuzzy Rule 5
  FuzzyRuleAntecedent *eNB_dPB = new FuzzyRuleAntecedent();
  eNB_dPB->joinWithAND(eNB, dPB);

  FuzzyRule *fuzzyRule5 = new FuzzyRule(5, eNB_dPB, kecepatan_mati);
  fuzzy->addFuzzyRule(fuzzyRule5);

  // Fuzzy Rule 6
  FuzzyRuleAntecedent *eNK_dNB = new FuzzyRuleAntecedent();
  eNK_dNB->joinWithAND(eNK, dNB);

  FuzzyRule *fuzzyRule6 = new FuzzyRule(6, eNK_dNB, kecepatan_mati);
  fuzzy->addFuzzyRule(fuzzyRule6);

  // Fuzzy Rule 7
  FuzzyRuleAntecedent *eNK_dNK = new FuzzyRuleAntecedent();
  eNK_dNK->joinWithAND(eNK, dNK);

  FuzzyRule *fuzzyRule7 = new FuzzyRule(7, eNK_dNK, kecepatan_mati);
  fuzzy->addFuzzyRule(fuzzyRule7);

  // Fuzzy Rule 8
  FuzzyRuleAntecedent *eNK_dN = new FuzzyRuleAntecedent();
  eNK_dN->joinWithAND(eNK, dN);

  FuzzyRule *fuzzyRule8 = new FuzzyRule(8, eNK_dN, kecepatan_mati);
  fuzzy->addFuzzyRule(fuzzyRule8);

  // Fuzzy Rule 9
  FuzzyRuleAntecedent *eNK_dPK = new FuzzyRuleAntecedent();
  eNK_dPK->joinWithAND(eNK, dPK);

  FuzzyRule *fuzzyRule9 = new FuzzyRule(9, eNK_dPK, kecepatan_mati);
  fuzzy->addFuzzyRule(fuzzyRule9);

  // Fuzzy Rule 10
  FuzzyRuleAntecedent *eNK_dPB = new FuzzyRuleAntecedent();
  eNK_dPB->joinWithAND(eNK, dPB);

  FuzzyRule *fuzzyRule10 = new FuzzyRule(10, eNK_dPB, kecepatan_mati);
  fuzzy->addFuzzyRule(fuzzyRule10);

  // Fuzzy Rule 11
  FuzzyRuleAntecedent *eN_dNB = new FuzzyRuleAntecedent();
  eN_dNB->joinWithAND(eN, dNB);

  FuzzyRule *fuzzyRule11 = new FuzzyRule(11, eN_dNB, kecepatan_lambat);
  fuzzy->addFuzzyRule(fuzzyRule11);

  // Fuzzy Rule 12
  FuzzyRuleAntecedent *eN_dNK = new FuzzyRuleAntecedent();
  eN_dNK->joinWithAND(eN, dNK);

  FuzzyRule *fuzzyRule12 = new FuzzyRule(12, eN_dNK, kecepatan_lambat);
  fuzzy->addFuzzyRule(fuzzyRule12);

  // Fuzzy Rule 13
  FuzzyRuleAntecedent *eN_dN = new FuzzyRuleAntecedent();
  eN_dN->joinWithAND(eN, dN);

  FuzzyRule *fuzzyRule13 = new FuzzyRule(13, eN_dN, kecepatan_mati);
  fuzzy->addFuzzyRule(fuzzyRule13);

  // Fuzzy Rule 14
  FuzzyRuleAntecedent *eN_dPK = new FuzzyRuleAntecedent();
  eN_dPK->joinWithAND(eN, dPK);

  FuzzyRule *fuzzyRule14 = new FuzzyRule(14, eN_dPK, kecepatan_mati);
  fuzzy->addFuzzyRule(fuzzyRule14);

  // Fuzzy Rule 15
  FuzzyRuleAntecedent *eN_dPB = new FuzzyRuleAntecedent();
  eN_dPB->joinWithAND(eN, dPB);

  FuzzyRule *fuzzyRule15 = new FuzzyRule(15, eN_dPB, kecepatan_mati);
  fuzzy->addFuzzyRule(fuzzyRule15);

  // Fuzzy Rule 16
  FuzzyRuleAntecedent *ePK_dNB = new FuzzyRuleAntecedent();
  ePK_dNB->joinWithAND(ePK, dNB);

  FuzzyRule *fuzzyRule16 = new FuzzyRule(16, ePK_dNB, kecepatan_cepat);
  fuzzy->addFuzzyRule(fuzzyRule16);

  // Fuzzy Rule 17
  FuzzyRuleAntecedent *ePK_dNK = new FuzzyRuleAntecedent();
  ePK_dNK->joinWithAND(ePK, dNK);

  FuzzyRule *fuzzyRule17 = new FuzzyRule(17, ePK_dNK, kecepatan_cepat);
  fuzzy->addFuzzyRule(fuzzyRule17);

  // Fuzzy Rule 18
  FuzzyRuleAntecedent *ePK_dN = new FuzzyRuleAntecedent();
  ePK_dN->joinWithAND(ePK, dN);

  FuzzyRule *fuzzyRule18 = new FuzzyRule(18, ePK_dN, kecepatan_lambat);
  fuzzy->addFuzzyRule(fuzzyRule18);

  // Fuzzy Rule 19
  FuzzyRuleAntecedent *ePK_dPK = new FuzzyRuleAntecedent();
  ePK_dPK->joinWithAND(ePK, dPK);

  FuzzyRule *fuzzyRule19 = new FuzzyRule(19, ePK_dPK, kecepatan_lambat);
  fuzzy->addFuzzyRule(fuzzyRule19);

  // Fuzzy Rule 20
  FuzzyRuleAntecedent *ePK_dPB = new FuzzyRuleAntecedent();
  ePK_dPB->joinWithAND(ePK, dPB);

  FuzzyRule *fuzzyRule20 = new FuzzyRule(20, ePK_dPB, kecepatan_lambat);
  fuzzy->addFuzzyRule(fuzzyRule20);

  // Fuzzy Rule 21
  FuzzyRuleAntecedent *ePB_dNB = new FuzzyRuleAntecedent();
  ePB_dNB->joinWithAND(ePB, dNB);

  FuzzyRule *fuzzyRule21 = new FuzzyRule(21, ePB_dNB, kecepatan_cepat);
  fuzzy->addFuzzyRule(fuzzyRule21);

  // Fuzzy Rule 22
  FuzzyRuleAntecedent *ePB_dNK = new FuzzyRuleAntecedent();
  ePB_dNK->joinWithAND(ePB, dNK);

  FuzzyRule *fuzzyRule22 = new FuzzyRule(22, ePB_dNK, kecepatan_cepat);
  fuzzy->addFuzzyRule(fuzzyRule22);

  // Fuzzy Rule 23
  FuzzyRuleAntecedent *ePB_dN = new FuzzyRuleAntecedent();
  ePB_dN->joinWithAND(ePB, dN);

  FuzzyRule *fuzzyRule23 = new FuzzyRule(23, ePB_dN, kecepatan_cepat);
  fuzzy->addFuzzyRule(fuzzyRule23);

  // Fuzzy Rule 24
  FuzzyRuleAntecedent *ePB_dPK = new FuzzyRuleAntecedent();
  ePB_dPK->joinWithAND(ePB, dPK);

  FuzzyRule *fuzzyRule24 = new FuzzyRule(24, ePB_dPK, kecepatan_cepat);
  fuzzy->addFuzzyRule(fuzzyRule24);

  // Fuzzy Rule 25
  FuzzyRuleAntecedent *ePB_dPB = new FuzzyRuleAntecedent();
  ePB_dPB->joinWithAND(ePB, dPB);

  FuzzyRule *fuzzyRule25 = new FuzzyRule(25, ePB_dPB, kecepatan_cepat);
  fuzzy->addFuzzyRule(fuzzyRule25);
}

float defuzzy(){
  fuzzy->setInput(1, errorDO);
  fuzzy->setInput(2, derrorDO);

  fuzzy->fuzzify();
  float state = (fuzzy->defuzzify(1));
  Serial.println(state);
  return state;
}
