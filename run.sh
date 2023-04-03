#!/bin/bash
#Run: sh run.sh [I_last_segment] [Nactive_tasks-1] [I_first_segment]
#Example: sh run.sh 5 2 1
#Example: sh run.sh 10000 99 1
#Example: sh run.sh 20000 99 10001
#Need for CAF: cp ~/geant4_workdir/tmp/Linux-g++/T2K_target_sim/libT2K_target_sim.so .

function mynjobs {
 qstat| grep t2k_target_sim| wc -l
}

function mywait {
  njobs=`mynjobs`
  while [ "$njobs" -gt $1 ]
  do
    sleep $2
    njobs=`mynjobs`
  done
}

pregion="pall"
for (( i=$3; i <= $1; i++ ))
do
 echo "Run number is $i"
 myname=t2k_target_sim_run${i}_roomega_${pregion}_pot5e4
 sed "s/setSeeds 2 2/setSeeds $i $i/" run/run.000.mac|sed "s/setFileName T2K_target_sim/setFileName run\/${myname}/" > run/${myname}.mac
# T2K_target_sim run/${myname}.mac > run/${myname}.log 2>&1 &

 echo "#!/bin/bash" > run/${myname}.sh
 echo ". setup.sh" >> run/${myname}.sh
 echo "LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH" >> run/${myname}.sh
 echo "./T2K_target_sim run/${myname}.mac > run/${myname}.log 2>&1 " >> run/${myname}.sh
# echo "T2K_target_sim run/${myname}.mac " >> run/${myname}.sh
 echo "echo Done" >> run/${myname}.sh
 echo "exit" >> run/${myname}.sh
 
 sbatch --mem=8000 run/${myname}.sh
 pid=$!
 sleep 5
 mywait $2 60
done

