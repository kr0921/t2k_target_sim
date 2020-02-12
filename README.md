# T2K target simulation package

Simple G4 simulation package for the T2K target.

## Ouput
Neutral particle production points

output_root_file.root:

    |-- TTree T2K_neutral   # contains the information about neutral particles production
        |-- mom         # momentum [MeV]
        |-- pid         # PDG code
        |-- dir_x       # direction x
        |-- dir_y       # direction y
        |-- dir_z       # direction z
        |-- pos_x       # production position x [mm]
        |-- pos_y       # production position y [mm]
        |-- pos_z       # production position z [mm]

## Target station geometry

## Baffle
Box 29 cm x 40 cm x 171.145 cm, 1.8g/cm^3 graphite

## He volume

Cylinder 223.813 cm length 3 cm diameter helium

## Target
Cylinder 91.4 cm length 2.6 cm diameter, 1.8g/cm^3 graphite


