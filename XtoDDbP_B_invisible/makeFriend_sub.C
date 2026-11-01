Double_t Dir_alt(TVector3 FlightDir, TVector3 Visibles)
{
	  return TMath::ACos((Visibles.Unit()).Dot(FlightDir.Unit()));
}

Double_t Dir_alt(TLorentzVector Direction, TLorentzVector Visibles)
{
	  return Dir_alt(Direction.Vect(),Visibles.Vect());
}

Double_t Dir_alt(TVector3 Direction, TLorentzVector Visibles)
{
	  return Dir_alt(Direction,Visibles.Vect());
}

Double_t Dir_alt(TLorentzVector Direction, TVector3 Visibles)
{
	  return Dir_alt(Direction.Vect(),Visibles);
}

Double_t cosDir_alt(TVector3 FlightDir, TVector3 Visibles)
{
      return (Visibles.Unit()).Dot(FlightDir.Unit());
}

Double_t cosDir_alt(TLorentzVector Direction, TLorentzVector Visibles)
{
	  return cosDir_alt(Direction.Vect(),Visibles.Vect());
}

Double_t cosDir_alt(TVector3 Direction, TLorentzVector Visibles)
{
	  return cosDir_alt(Direction,Visibles.Vect());
}

Double_t cosDir_alt(TLorentzVector Direction, TVector3 Visibles)
{
	  return cosDir_alt(Direction.Vect(),Visibles);
}

Double_t sinDir_alt(TVector3 FlightDir, TVector3 Visibles)
{
      //Double_t theta = TMath::ACos((FlightDir.Unit()).Dot(Visibles.Unit()));
      //return TMath::Sin(theta);
      TVector3 LongVec = ((Visibles.Unit()).Dot(FlightDir.Unit())) * (FlightDir.Unit());
      TVector3 TranVec = Visibles.Unit() - LongVec;
      return ( TranVec.Mag() / Visibles.Unit().Mag() ); 
}

Double_t sinDir_alt(TLorentzVector Direction, TLorentzVector Visibles)
{
	  return sinDir_alt(Direction.Vect(),Visibles.Vect());
}

Double_t sinDir_alt(TVector3 Direction, TLorentzVector Visibles)
{
	  return sinDir_alt(Direction,Visibles.Vect());
}

Double_t sinDir_alt(TLorentzVector Direction, TVector3 Visibles)
{
	  return sinDir_alt(Direction.Vect(),Visibles);
}

Double_t pT_alt(TVector3 Direction, TVector3 Visibles)
{
      TVector3 pLongVec = Visibles.Dot(Direction.Unit()) * Direction.Unit();
      TVector3 pTranVec = Visibles - pLongVec;
      return pTranVec.Mag();
}

Double_t pT_alt(TLorentzVector Direction, TLorentzVector Visibles)
{
	  return pT_alt(Direction.Vect(),Visibles.Vect());
}

Double_t pT_alt(TVector3 Direction, TLorentzVector Visibles)
{
	  return pT_alt(Direction,Visibles.Vect());
}

Double_t pT_alt(TLorentzVector Direction, TVector3 Visibles)
{
	  return pT_alt(Direction.Vect(),Visibles);
}

Double_t pL_alt(TVector3 Direction, TVector3 Visibles)
{
      TVector3 pLongVec = Visibles.Dot(Direction.Unit()) * Direction.Unit();
      return pLongVec.Mag();
}

Double_t pL_alt(TLorentzVector Direction, TLorentzVector Visibles)
{
	  return pL_alt(Direction.Vect(),Visibles.Vect());
}

Double_t pL_alt(TVector3 Direction, TLorentzVector Visibles)
{
	  return pL_alt(Direction,Visibles.Vect());
}

Double_t pL_alt(TLorentzVector Direction, TVector3 Visibles)
{
	  return pL_alt(Direction.Vect(),Visibles);
}

Double_t mCorr_alt(TVector3 Direction, TLorentzVector Visibles)
{
      TVector3 pLongVec = Visibles.Vect().Dot(Direction.Unit()) * Direction.Unit();
      TVector3 pTranVec = Visibles.Vect() - pLongVec;
      Double_t pLong = pLongVec.Mag();
      Double_t pTran = pTranVec.Mag();
      Double_t mVis2 = Visibles.M2();
      return TMath::Sqrt( mVis2 + pTran*pTran ) + pTran;
}

Double_t mCorr_alt(TLorentzVector Direction, TLorentzVector Visibles)
{
	  return mCorr_alt(Direction.Vect(),Visibles);
}


Double_t m0maxsq_alt(TVector3 Direction, TLorentzVector Visibles, Double_t parentMassHypo=0.)
{
      TVector3 pLongVec = Visibles.Vect().Dot(Direction.Unit()) * Direction.Unit();
 	  TVector3 pTranVec = Visibles.Vect() - pLongVec;
      Double_t pLong = pLongVec.Mag();
      Double_t pTran = pTranVec.Mag();
      Double_t mVis2 = Visibles.M2();
      return (parentMassHypo)*(parentMassHypo) - 2*(parentMassHypo)*sqrt(mVis2 + pTran*pTran) + mVis2; // can be affected by FSR
}

Double_t m0maxsq_alt(TLorentzVector Direction, TLorentzVector Visibles, Double_t parentMassHypo=0.)
{
	  return m0maxsq_alt(Direction.Vect(),Visibles,parentMassHypo);
}

Double_t signed_m0max_alt(TVector3 Direction, TLorentzVector Visibles, Double_t parentMassHypo=0.)
{
      TVector3 pLongVec = Visibles.Vect().Dot(Direction.Unit()) * Direction.Unit();
      TVector3 pTranVec = Visibles.Vect() - pLongVec;
      Double_t pLong = pLongVec.Mag();
      Double_t pTran = pTranVec.Mag();
      Double_t mVis2 = Visibles.M2();

      //the maximum missing mass under the parent meson hypthesis
      Double_t parent_msq_miss_max = (parentMassHypo)*(parentMassHypo) - 2*(parentMassHypo)*sqrt(mVis2 + pTran*pTran) + mVis2; // can be affected by FSR

      Double_t parent_signed_m_miss_max = 0;
      if (parent_msq_miss_max > 0) {parent_signed_m_miss_max =  sqrt(( parent_msq_miss_max));}
      if (parent_msq_miss_max < 0) {parent_signed_m_miss_max = -sqrt((-parent_msq_miss_max));}
      return parent_signed_m_miss_max; 
}

Double_t signed_m0max_alt(TLorentzVector Direction, TLorentzVector Visibles, Double_t parentMassHypo=0.)
{
	  return signed_m0max_alt(Direction.Vect(),Visibles,parentMassHypo);
}


Double_t E_rec_alt(TVector3 Direction, TLorentzVector Visibles, Double_t parentMassHypo=0.)
{
      TVector3 pLongVec = Visibles.Vect().Dot(Direction.Unit()) * Direction.Unit();
      TVector3 pTranVec = Visibles.Vect() - pLongVec;
      Double_t pLong = pLongVec.Mag();
      Double_t pTran = pTranVec.Mag();
      Double_t mVis2 = Visibles.M2();

      //the maximum missing mass under the parent meson hypthesis
      Double_t parent_msq_miss_max = (parentMassHypo)*(parentMassHypo) - 2*(parentMassHypo)*sqrt(mVis2 + pTran*pTran) + mVis2; // can be affected by FSR

      //prepare reconstructed parent energy
      Double_t parent_m0sq = 0;
      if (parent_msq_miss_max >= 0) {parent_m0sq = parent_msq_miss_max;}
      Double_t parent_p0l = ((parentMassHypo)*(parentMassHypo) - (mVis2 + pTran*pTran) - (parent_m0sq + pTran*pTran))*pLong/(2*(mVis2 + pTran*pTran));
      return sqrt(parent_m0sq + pTran*pTran + parent_p0l*parent_p0l) + sqrt(mVis2 + pTran*pTran + pLong*pLong); // reco parent energy
}

Double_t E_rec_alt(TLorentzVector Direction, TLorentzVector Visibles, Double_t parentMassHypo=0.)
{
	  return E_rec_alt(Direction.Vect(),Visibles,parentMassHypo);
}

Double_t p_break_hypo_sq(Double_t neutralMass, TLorentzVector Visibles, Double_t parentMassHypo=0.)
{
      //Basic 2 body scenario predicts, in the rest frame of the decaying particle:
      //p^2 = (m_X^2 - (mVis + m0)^2)  (m_X^2 - (mVis - m0)^2) / (4 m_X^2)
      Double_t mVis2 = Visibles.M2();
      Double_t mVis = sqrt(mVis2);
      Double_t mVisplNeutral = mVis + neutralMass;
      Double_t mVismiNeutral = mVis - neutralMass;   
      return ( (parentMassHypo*parentMassHypo - (mVisplNeutral*mVisplNeutral) ) * ( parentMassHypo*parentMassHypo - (mVismiNeutral*mVismiNeutral) ) ) / (4*parentMassHypo);
      //Double_t p_break_hypoNeutral_sq = ( (parentMassHypo*parentMassHypo - (mVisplNeutral*mVisplNeutral) ) * ( parentMassHypo*parentMassHypo - (mVismiNeutral*mVismiNeutral) ) ) / (4*parentMassHypo);
      //return sqrt(p_break_hypoNeutral_sq);
}

Double_t Dir(TLorentzVector Direction, TLorentzVector Visibles, Double_t fuzz=0.)
{
	  if (fuzz == 0.)
	  {
		  return Dir_alt(Direction,Visibles);
	  }
	  else
	  {
	      Double_t cosDir = Direction.Vect().Dot(Visibles.Vect())/(Direction.P()*Visibles.P());
	      return TMath::ACos(cosDir) + fuzz;	  
	  }
}

Double_t cosDir(TLorentzVector Direction, TLorentzVector Visibles, Double_t fuzz=0.)
{
	  if (fuzz == 0.)
	  {
		  return cosDir_alt(Direction,Visibles);
	  }
	  else
	  {
	      Double_t cosDir = Direction.Vect().Dot(Visibles.Vect())/(Direction.P()*Visibles.P());
	      Double_t dir = TMath::ACos(cosDir) + fuzz;
	      return TMath::Cos(dir);
	  }
}

Double_t sinDir(TLorentzVector Direction, TLorentzVector Visibles, Double_t fuzz=0.)
{
	  if (fuzz == 0.)
	  {
		  return sinDir_alt(Direction,Visibles);
	  }
	  else
	  {
		  Double_t cosDir = Direction.Vect().Dot(Visibles.Vect())/(Direction.P()*Visibles.P());
		  Double_t dir = TMath::ACos(cosDir) + fuzz;
		  return TMath::Sin(dir);
	  }
}

Double_t pT(TLorentzVector Direction, TLorentzVector Visibles, Double_t fuzz=0.)
{
	  if (fuzz == 0.)
	  {
		  return pT_alt(Direction,Visibles);
	  }
	  else
	  {
		  Double_t cosDir = Direction.Vect().Dot(Visibles.Vect())/(Direction.P()*Visibles.P());
		  Double_t dir = TMath::ACos(cosDir) + fuzz;
		  Double_t sinDir = TMath::Sin(dir);
	
		  //get the longitudinal and transverse momentum of the Visibles w.r.t. the Direction flight direction
		  return (Double_t)TMath::Abs(sinDir * Visibles.P());
	  }
}

Double_t pL(TLorentzVector Direction, TLorentzVector Visibles, Double_t fuzz=0.)
{
	  if (fuzz == 0.)
	  {
		  return pL_alt(Direction,Visibles);
	  }
	  else
	  {
		  Double_t cosDir = Direction.Vect().Dot(Visibles.Vect())/(Direction.P()*Visibles.P());
		  Double_t dir = TMath::ACos(cosDir) + fuzz;
		  cosDir = TMath::Cos(dir);
		  
		  //get the longitudinal and transverse momentum of the Visibles w.r.t. the Direction flight direction
		  return (Double_t)TMath::Abs(cosDir * Visibles.P());
	  }
}

Double_t mCorr(TLorentzVector Direction, TLorentzVector Visibles, Double_t fuzz=0.)
{
	  if (fuzz == 0.)
	  {
		  return mCorr_alt(Direction,Visibles);
	  }
	  else
	  {
		  Double_t cosDir = Direction.Vect().Dot(Visibles.Vect())/(Direction.P()*Visibles.P());
		  Double_t dir = TMath::ACos(cosDir) + fuzz;
		  Double_t sinDir = TMath::Sin(dir);
	
		  //get the longitudinal and transverse momentum of the Visibles w.r.t. the Direction flight direction
		  Double_t pTran = (Double_t)TMath::Abs(sinDir * Visibles.P());
		  Double_t mVis2 = Visibles.M2();
		  return TMath::Sqrt( mVis2 + pTran*pTran ) + pTran;
	  }
}

Double_t m0maxsq(TLorentzVector Direction, TLorentzVector Visibles, Double_t fuzz=0., Double_t parentMassHypo=0.)
{
	  if (fuzz == 0.)
	  {
		  return m0maxsq_alt(Direction,Visibles,parentMassHypo);
	  }
	  else
	  {
		  //the maximum missing mass under the parent meson hypthesis
		  Double_t cosDir = Direction.Vect().Dot(Visibles.Vect())/(Direction.P()*Visibles.P());
		  Double_t dir = TMath::ACos(cosDir) + fuzz;
		  Double_t sinDir = TMath::Sin(dir);
	
		  //get the longitudinal and transverse momentum of the Visibles w.r.t. the Direction flight direction
		  Double_t pTran = (Double_t)TMath::Abs(sinDir * Visibles.P());
		  Double_t mVis2 = Visibles.M2();
		  return (parentMassHypo)*(parentMassHypo) - 2*(parentMassHypo)*sqrt(mVis2 + pTran*pTran) + mVis2; // can be affected by FSR
	  }
}

Double_t signed_m0max(TLorentzVector Direction, TLorentzVector Visibles, Double_t fuzz=0., Double_t parentMassHypo=0.)
{
	  if (fuzz == 0.)
	  {
		  return signed_m0max_alt(Direction,Visibles,parentMassHypo);
	  }
	  else
	  {
	      //the maximum missing mass under the parent meson hypthesis
	      Double_t cosDir = Direction.Vect().Dot(Visibles.Vect())/(Direction.P()*Visibles.P());
	      Double_t dir = TMath::ACos(cosDir) + fuzz;
	      Double_t sinDir = TMath::Sin(dir);

	      //get the longitudinal and transverse momentum of the Visibles w.r.t. the Direction flight direction
	      Double_t pTran = (Double_t)TMath::Abs(sinDir * Visibles.P());
	      Double_t mVis2 = Visibles.M2();

	      //the maximum missing mass under the parent meson hypthesis
	      Double_t parent_msq_miss_max = (parentMassHypo)*(parentMassHypo) - 2*(parentMassHypo)*sqrt(mVis2 + pTran*pTran) + mVis2; // can be affected by FSR

	      Double_t parent_signed_m_miss_max = 0;
	      if (parent_msq_miss_max > 0) {parent_signed_m_miss_max =  sqrt(( parent_msq_miss_max));}
	      if (parent_msq_miss_max < 0) {parent_signed_m_miss_max = -sqrt((-parent_msq_miss_max));}
	      return parent_signed_m_miss_max; 
	  }
}

Double_t E_rec(TLorentzVector Direction, TLorentzVector Visibles, Double_t fuzz=0., Double_t parentMassHypo=0.)
{
	  if (fuzz == 0.)
	  {
		  return E_rec_alt(Direction,Visibles,parentMassHypo);
	  }
	  else
	  {
		     //the maximum missing mass under the parent meson hypthesis
		      Double_t cosDir = Direction.Vect().Dot(Visibles.Vect())/(Direction.P()*Visibles.P());
		      Double_t dir = TMath::ACos(cosDir) + fuzz;
		      Double_t sinDir = TMath::Sin(dir);
		      cosDir = TMath::Cos(dir);
		      
		      //get the longitudinal and transverse momentum of the Visibles w.r.t. the Direction flight direction
		      Double_t pTran = (Double_t)TMath::Abs(sinDir * Visibles.P());
		      Double_t pLong = (Double_t)TMath::Abs(cosDir * Visibles.P());
		      Double_t mVis2 = Visibles.M2();

		      //the maximum missing mass under the parent meson hypthesis
		      Double_t parent_msq_miss_max = (parentMassHypo)*(parentMassHypo) - 2*(parentMassHypo)*sqrt(mVis2 + pTran*pTran) + mVis2; // can be affected by FSR

		      //prepare reconstructed parent energy
		      Double_t parent_m0sq = 0;
		      if (parent_msq_miss_max >= 0) {parent_m0sq = parent_msq_miss_max;}
		      Double_t parent_p0l = ((parentMassHypo)*(parentMassHypo) - (mVis2 + pTran*pTran) - (parent_m0sq + pTran*pTran))*pLong/(2*(mVis2 + pTran*pTran));
		      return sqrt(parent_m0sq + pTran*pTran + parent_p0l*parent_p0l) + sqrt(mVis2 + pTran*pTran + pLong*pLong); // reco parent energy
	  }
}

Double_t delDir(TVector3 SimDir, TVector3 TrueDir, TLorentzVector Visibles)
{
      TVector3 unit_Visibles = (Visibles.Vect()).Unit();
	  // Get angle between True Direction and Visibles
      Double_t trueAngle = TMath::ACos((TrueDir.Unit()).Dot(unit_Visibles));
	  // Get angle between Simulated Direction/Momentum and Visibles
      Double_t simAngle = TMath::ACos((SimDir.Unit()).Dot(unit_Visibles));
      Double_t angle = simAngle - trueAngle;
      // return a signed version 
      TVector3 trueNormal = (TrueDir.Unit()).Cross(unit_Visibles);
      TVector3 simNormal = (SimDir.Unit()).Cross(unit_Visibles);
      if (simNormal.Dot(trueNormal) < 0) 
      { 
        angle = -angle;
      }
      return angle;
}

Double_t delDirTot(TVector3 SimDir, TVector3 TrueDir, TLorentzVector Visibles, TLorentzVector TrueVisibles)
{
      TVector3 unit_Visibles = (Visibles.Vect()).Unit();
      TVector3 unit_TrueVisibles = (TrueVisibles.Vect()).Unit();
	  // Get angle between True Direction and True Visibles
      Double_t trueAngle = TMath::ACos((TrueDir.Unit()).Dot(unit_TrueVisibles));
	  // Get angle between Simulated Direction/Momentum and Visibles
      Double_t simAngle = TMath::ACos((SimDir.Unit()).Dot(unit_Visibles));
      Double_t angle = simAngle - trueAngle;
      // return a signed version 
      TVector3 trueNormal = (TrueDir.Unit()).Cross(unit_TrueVisibles);
      TVector3 simNormal = (SimDir.Unit()).Cross(unit_Visibles);
      if (simNormal.Dot(trueNormal) < 0) 
      { 
        angle = -angle;
      }
      return angle;
}

Double_t delSinDir(TVector3 SimDir, TVector3 TrueDir, TLorentzVector Visibles)
{
      TVector3 unit_Visibles = (Visibles.Vect()).Unit();
      return TMath::Sin(TMath::ACos((SimDir.Unit()).Dot(unit_Visibles))) - TMath::Sin(TMath::ACos((TrueDir.Unit()).Dot(unit_Visibles)));
}

Double_t delCosDir(TVector3 SimDir, TVector3 TrueDir, TLorentzVector Visibles)
{
      TVector3 unit_Visibles = (Visibles.Vect()).Unit();
      Double_t CosDir_Sim = (SimDir.Unit()).Dot(unit_Visibles);
      Double_t CosDir_True = (TrueDir.Unit()).Dot(unit_Visibles);
      return CosDir_Sim - CosDir_True;
}

Double_t calc_D_p_Alt(Double_t m2_DmDb)
{
      Double_t D_p_Alt;
      if (m2_DmDb > 0.0)
	  {
        D_p_Alt = 0.0;
        //std::cout << "Illegal point made 0.0" << std::endl; 
	  }
      else
	  {
        D_p_Alt = (sqrt(-m2_DmDb))/2;
	  }
      return D_p_Alt;
}