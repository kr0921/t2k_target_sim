# T2K target simulation package

Simple G4 simulation package for the T2K target.

## Ouput
Neutral particle production points

output_root_file.root:

    |-- TTree T2K_neutral   # contains the information about neutral particles production
        |-- ekin        # momentum [MeV]
        |-- pid         # PDG code
        |-- dir_x       # direction x
        |-- dir_y       # direction y
        |-- dir_z       # direction z
        |-- pos_x       # production position x [mm]
        |-- pos_y       # production position y [mm]
        |-- pos_z       # production position z [mm]

## Target geometry
Cylinder 91.4 cm length 2.6 cm diameter, 1.8g/cm^3 graphite

