#!bin/sh

echo "" > commands.sh
for i in `seq 0 200`;
do
  echo "/random/setSeeds $RANDOM$RANDOM $RANDOM$RANDOM " > runs/run_v${i}.mac
  echo "/run/initialize" >> runs/run_v${i}.mac
  echo "/gun/particle proton" >> runs/run_v${i}.mac
  echo "/gun/direction 0 0 1 # momentum direction" >> runs/run_v${i}.mac
  echo "/gun/position 0 0 0 mm  # starting position" >> runs/run_v${i}.mac
  echo "/gun/number   1      # number of particles" >> runs/run_v${i}.mac
  echo "/SHiP/generator/energy 30 GeV" >> runs/run_v${i}.mac
  echo "/SHiP/generator/randomizePrimary FALSE" >> runs/run_v${i}.mac
  echo "/SHiP/generator/sigmaMomentum 0." >> runs/run_v${i}.mac
  echo "/SHiP/generator/sigmaAngle 0." >> runs/run_v${i}.mac
  echo "/run/verbose 1" >> runs/run_v${i}.mac
  echo "/run/printProgress 1" >> runs/run_v${i}.mac
  echo "/analysis/setFileName T2K_target_sim_v${i}" >> runs/run_v${i}.mac
  echo "/run/beamOn 1000 " >> runs/run_v${i}.mac
  echo "../build/T2K_target_sim runs/run_v${i}.mac 2>&1 | tee ../log/log_v${i}.log" >>  commands.sh
done
nice -n 19 parallel -j 15 -a commands.sh

hadd -f T2K_target_sim_tot.root T2K_target_sim_v*.root
rm T2K_target_sim_v*.root
email "G4 done" "T2K target G4 done"