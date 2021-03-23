{
    //Correction of the vapor parameters based on our barotropic EOS model
    rhov =
        max
        (
            min
            (
                ((mag(p - pSat) - (p - pSat))/(2*mag(p - pSat) + rhoMin/psiv))*K*(pSat - p)/((1.0 - alphaGasPhase)/rho - (1.0 - K*(pSat - p))/rholSat),
                rhovSat
            ),
            rhoMin
        );
    pv = ((mag(p - pSat) - (p - pSat))/(2*mag(p - pSat) + rhoMin/psiv))*rhov/psiv;
    
    //The partial pressure and density of the released air
    pgr = p - pv;
    rhogr = psig*pgr;
            
    //Equation for the total volume fraction (vapor+gas)
    sourceTerm =
	((mag(p - pSol) + (p - pSol))/(2*mag(p - pSol) + rhoMin/psiv))*alphaGasPhase*Kgas*(pSol - p)/(alphaGasPhase + 0.0000000001)
      + ((mag(p - pSol) - (p - pSol))/(2*mag(p - pSol) + rhoMin/psiv))*Kgas*(pSol - p)
      + rhogr*(U & fvc::grad(alphaGasPhase));
    
    alphaGasPhase =
	max
	(
	    min
	    (
		 -sourceTerm/(fvc::div(rhogr, U)),
		 scalar(1)
	    ),
	    scalar(0)
	);
    
    Info<< "max-min alpha(vapor+gas): " << max(alphaGasPhase).value()
        << " " << min(alphaGasPhase).value() << endl;
        
    Info<< "max vapor pressure: " << max(pv).value() << endl;
        
    Info<< "max free air pressure: " << max(pgr).value() << endl;

    //psiModel->correct();

    //Info<< "min a: " << 1.0/sqrt(max(psi)).value() << endl;
    
    rho = (1.0 - alphaGasPhase)*(rholSat + psil*(p - pSat)) + alphaGasPhase*rhov;
    
    Info<< "max-min rho(liquid+vapor, apparent): " << max(rho).value()
        << " " << min(rho).value() << endl;

    rho == max(rho, rhoMin);
}
