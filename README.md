Geant4 MC simulation of a MPGD-based SDHCAL.

# Build instructions:
```
cd G4_simulaiton/build
cmake ..
make -j8
```

# Run simulation
From the ```build``` directory
```
./uMSDHCAL  $BEAM_ENERGY $MAGNETIC_FIELD $nEVENTS $PARTICLE $OUTPUTFILE  
```
```$BEAM_ENERGY```  - Beam energy in GeV <br>
```$MAGNETIC_FIELD``` - magnetic field in Tesla <br>
```$nEVENTS``` - Number of simulated events <br>
```$PARTICLE``` - mu±, e±, or pi±  <br>
```$OUTPUTFILE``` - The name of the outputfile which will be save in the ```rootfile ``` directory<br>

# PFCal_RPWELL
